/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_slabinfo.c
    
    @brief: 读取slabinfo的内容
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/stddef.h>
#include <linux/seq_file.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 0, 8))
#include <linux/swap.h> /* struct reclaim_state */
#include <linux/bit_spinlock.h>
#include <linux/interrupt.h>
#include <linux/bitops.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kmemtrace.h>
#include <linux/kmemcheck.h>
#include <linux/cpu.h>
#include <linux/cpuset.h>
#include <linux/mempolicy.h>
#include <linux/ctype.h>
#include <linux/debugobjects.h>
#include <linux/kallsyms.h>
#include <linux/memory.h>
#include <linux/math64.h>
#include <linux/fault-inject.h>
#endif

#include <linux/memcontrol.h>
#include <asm/uaccess.h>

#include "../include/srecorder_slabinfo.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_snprintf.h"


#if defined(CONFIG_DUMP_SLAB_INFO)

/*----local macroes------------------------------------------------------------------*/

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0))
#ifdef CONFIG_SLAB
#define check_irq_on()    do { } while(0)
#endif
#endif

#ifdef CONFIG_SLUB
#define OO_SHIFT 16
#define OO_MASK ((1 << OO_SHIFT) - 1)
#endif


/*----local prototypes----------------------------------------------------------------*/

/*
* struct array_cache
*
* Purpose:
* - LIFO ordering, to hand out cache-warm objects from _alloc
* - reduce the number of linked list operations
* - reduce spinlock operations
*
* The limit is stored in the per-cpu structure to reduce the data cache
* footprint.
*
*/
struct array_cache 
{
    unsigned int avail;
    unsigned int limit;
    unsigned int batchcount;
    unsigned int touched;
    spinlock_t lock;
    
    /*
    * Must have this definition in here for the proper
    * alignment of array_cache. Also simplifies accessing
    * the entries.
    */
    void *entry[];    

};


typedef unsigned int kmem_bufctl_t;

/*
* struct slab_rcu
*
* slab_destroy on a SLAB_DESTROY_BY_RCU cache uses this structure to
* arrange for kmem_freepages to be called via RCU.  This is useful if
* we need to approach a kernel structure obliquely, from its address
* obtained without the usual locking.  We can lock the structure to
* stabilize it and check it's still at the given address, only if we
* can be sure that the memory has not been meanwhile reused for some
* other kind of object (which our subsystem's lock might corrupt).
*
* rcu_read_lock before reading the address, then rcu_read_unlock after
* taking the spinlock within the structure expected at that address.
*/
struct slab_rcu 
{
    struct rcu_head head;
    struct kmem_cache *cachep;
    void *addr;
};

#if 0
/*
* struct slab
*
* Manages the objs in a slab. Placed either at the beginning of mem allocated
* for a slab, or allocated from an general cache.
* Slabs are chained into three list: fully used, partial, fully free slabs.
*/
struct slab 
{
    struct list_head list;
    unsigned long colouroff;
    void *s_mem;        /* including colour offset */
    unsigned int inuse;    /* num of objs active in slab */
    kmem_bufctl_t free;
    unsigned short nodeid;
};
#else
/*
 * struct slab
 *
 * Manages the objs in a slab. Placed either at the beginning of mem allocated
 * for a slab, or allocated from an general cache.
 * Slabs are chained into three list: fully used, partial, fully free slabs.
 */
struct slab 
{
    union 
    {
        struct 
        {
            struct list_head list;
            unsigned long colouroff;
            void *s_mem;        /* including colour offset */
            unsigned int inuse;    /* num of objs active in slab */
            kmem_bufctl_t free;
            unsigned short nodeid;
        };
        
        struct slab_rcu __slab_cover_slab_rcu;
    };
};
#endif

/*
* The slab lists for all objects.
*/
struct kmem_list3 
{
    struct list_head slabs_partial;    /* partial list first, better asm code */
    struct list_head slabs_full;
    struct list_head slabs_free;
    unsigned long free_objects;
    unsigned int free_limit;
    unsigned int colour_next;    /* Per-node cache coloring */
    spinlock_t list_lock;
    struct array_cache *shared;    /* shared per node */
    struct array_cache **alien;    /* on other nodes */
    unsigned long next_reap;    /* updated without locking */
    int free_touched;        /* updated without locking */
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
struct slabinfo
{
    unsigned long active_objs;
    unsigned long num_objs;
    unsigned long active_slabs;
    unsigned long num_slabs;
    unsigned long shared_avail;
    unsigned int limit;
    unsigned int batchcount;
    unsigned int shared;
    unsigned int objects_per_slab;
    unsigned int cache_order;
};

/*
 * The slab lists for all objects.
 */
struct kmem_cache_node 
{
    spinlock_t list_lock;

#ifdef CONFIG_SLAB
    struct list_head slabs_partial;	/* partial list first, better asm code */
    struct list_head slabs_full;
    struct list_head slabs_free;
    unsigned long free_objects;
    unsigned int free_limit;
    unsigned int colour_next;	/* Per-node cache coloring */
    struct array_cache *shared;	/* shared per node */
    struct array_cache **alien;	/* on other nodes */
    unsigned long next_reap;	/* updated without locking */
    int free_touched;		/* updated without locking */
#endif

#ifdef CONFIG_SLUB
    unsigned long nr_partial;
    struct list_head partial;
#ifdef CONFIG_SLUB_DEBUG
    atomic_long_t nr_slabs;
    atomic_long_t total_objects;
    struct list_head full;
#endif
#endif
};
#endif


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static int srecorder_format_slabinfo_header(srecorder_reserved_mem_info_t *pmem_info);
static int srecorder_dump_slabinfo(srecorder_reserved_mem_info_t *pmem_info, void *p);
static void* srecorder_slabinfo_start(srecorder_reserved_mem_info_t *pmem_info, 
    struct list_head *cache_chain, loff_t *pos);
static void* srecorder_slabinfo_next(void *p, struct list_head *cache_chain, loff_t *pos);

#ifdef CONFIG_SLUB
static unsigned long srecorder_count_partial(struct kmem_cache_node *n, int (*get_count)(struct page *));
static inline struct kmem_cache_node *srecorder_get_node(struct kmem_cache *s, int node);
static int srecorder_count_free(struct page *page);
static inline int srecorder_oo_order(struct kmem_cache_order_objects x);
static inline int srecorder_oo_objects(struct kmem_cache_order_objects x);
#endif


/*----function definitions--------------------------------------------------------------*/

/**
    @function: static int srecorder_format_slabinfo_header(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 组织slabinfo的头部信息

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败。一般都会成功

    @note: 
*/
static int srecorder_format_slabinfo_header(srecorder_reserved_mem_info_t *pmem_info)
{
    int bytes_read = 0;
    
    if (unlikely(NULL == pmem_info) || unlikely(NULL == pmem_info->start_addr))/* [false alarm]:there is pmem_info protect  */
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s\n", 
        "slabinfo - version: 2.1\n"
        "# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab>"
        " : tunables <limit> <batchcount> <sharedfactor>"
        " : slabdata <active_slabs> <num_slabs> <sharedavail>");
    
    srecorder_renew_meminfo(pmem_info, bytes_read);    
    
    return 0;
}


/**
    @function: static void* srecorder_slabinfo_start(srecorder_reserved_mem_info_for_log_t *pmem_info, 
                struct list_head *cache_chain, loff_t *pos)
    @brief: 填充slabinfo的头部信息，返回cache_chain的第*pos个节点

    @param: pmem_info SRecorder的保留内存信息
    @param: cache_chain 链表头指针
    @param: pos 链表的游标的当前位置
    
    @return: 满足条件的节点的地址

    @note: 
*/
static void* srecorder_slabinfo_start(srecorder_reserved_mem_info_t *pmem_info, 
    struct list_head *cache_chain, loff_t *pos)
{
    srecorder_format_slabinfo_header(pmem_info);
    
    return seq_list_start(cache_chain, *pos);
}


/**
    @function: static void* srecorder_slabinfo_next(void *p, struct list_head *cache_chain, loff_t *pos)
    @brief: 查找cache_chain链表中的另外一个节点

    @param: p 当前节点
    @param: cache_chain 链表头指针
    @param: pos 链表的游标
    
    @return: 满足条件的节点的地址

    @note: 
*/
static void* srecorder_slabinfo_next(void *p, struct list_head *cache_chain, loff_t *pos)
{
    return seq_list_next(p, cache_chain, pos);
}


#ifdef CONFIG_SLUB
static inline int srecorder_oo_order(struct kmem_cache_order_objects x)
{
    return x.x >> OO_SHIFT;
}

static inline int srecorder_oo_objects(struct kmem_cache_order_objects x)
{
    return x.x & OO_MASK;
}


static int srecorder_count_free(struct page *page)
{
    if (unlikely(NULL == page))
    {
        return 0;
    }
    
    return page->objects - page->inuse;/* [false alarm]:there is page protect before  */
}


static unsigned long srecorder_count_partial(struct kmem_cache_node *n, int (*get_count)(struct page *))
{
    unsigned long flags;
    unsigned long x = 0;
    struct page *page;
    
    if (unlikely(NULL == n || NULL == get_count))
    {
        return 0;
    }
/*lint -e666 */    
    if (spin_trylock_irqsave(&n->list_lock, flags))
/*lint +e666 */
    {
        list_for_each_entry(page, &n->partial, lru)
        {
            x += get_count(page);
        }
        spin_unlock_irqrestore(&n->list_lock, flags);
    }
    
    return x;
}


static inline struct kmem_cache_node *srecorder_get_node(struct kmem_cache *s, int node)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37))
#ifdef CONFIG_NUMA
    return s->node[node];
#else
    return &s->local_node;
#endif
#else
    return s->node[node];
#endif
}
#endif


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
#ifdef CONFIG_MEMCG_KMEM
static inline bool srecorder_is_root_cache(struct kmem_cache *s)
{
    return !s->memcg_params || s->memcg_params->srecorder_is_root_cache;
}

static inline const char *srecorder_cache_name(struct kmem_cache *s)
{
    if (!srecorder_is_root_cache(s))
    {
        return s->memcg_params->root_cache->name;
    }
    
    return s->name;
}

static inline struct kmem_cache *srecorder_cache_from_memcg(struct kmem_cache *s, int idx)
{
    if (NULL == s->memcg_params)
    {
        return NULL;
    }
    
    return s->memcg_params->memcg_caches[idx];
}
#else
static inline bool srecorder_is_root_cache(struct kmem_cache *s)
{
    return true;
}

static inline const char *srecorder_cache_name(struct kmem_cache *s)
{
	return s->name;
}

static inline struct kmem_cache *srecorder_cache_from_memcg(struct kmem_cache *s, int idx)
{
    return NULL;
}
#endif

#ifdef CONFIG_SLAB
void srecorder_do_get_slabinfo(struct kmem_cache *cachep, struct slabinfo *sinfo)
{
    struct slab *slabp = NULL;
    unsigned long active_objs;
    unsigned long num_objs;
    unsigned long active_slabs = 0;
    unsigned long num_slabs, free_objects = 0, shared_avail = 0;
    const char *name = NULL;
    char *error = NULL;
    int node;
    struct kmem_cache_node *n = NULL;

    if (NULL == cachep || NULL == sinfo)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
    
    active_objs = 0;
    num_slabs = 0;
    for_each_online_node(node)
    {
        n = cachep->node[node];
        if (NULL == n)
        {
            continue;
        }

        check_irq_on();
        
        if (!spin_trylock_irq(&n->list_lock))
        {
            return;
        }

        list_for_each_entry(slabp, &n->slabs_full, list)
        {
            if (slabp->inuse != cachep->num && !error)
            {
                error = "slabs_full accounting error";
            }
            active_objs += cachep->num;
            active_slabs++;
        }
        
        list_for_each_entry(slabp, &n->slabs_partial, list)
        {
            if (slabp->inuse == cachep->num && !error)
            {
                error = "slabs_partial inuse accounting error";
            }
            
            if (!slabp->inuse && !error)
            {
                error = "slabs_partial/inuse accounting error";
            }
            active_objs += slabp->inuse;
            active_slabs++;
        }
        
        list_for_each_entry(slabp, &n->slabs_free, list)
        {
            if (slabp->inuse && !error)
            {
                error = "slabs_free/inuse accounting error";
            }
            num_slabs++;
        }
        free_objects += n->free_objects;
        if (n->shared)
        {
            shared_avail += n->shared->avail;
        }

        spin_unlock_irq(&n->list_lock);
    }
    num_slabs += active_slabs;
    num_objs = num_slabs * cachep->num;
    if (num_objs - active_objs != free_objects && !error)
    {
        error = "free_objects accounting error";
    }

    name = cachep->name;
    if (error)
    {
        printk(KERN_ERR "slab: cache %s error: %s\n", name, error);
    }

    sinfo->active_objs = active_objs;
    sinfo->num_objs = num_objs;
    sinfo->active_slabs = active_slabs;
    sinfo->num_slabs = num_slabs;
    sinfo->shared_avail = shared_avail;
    sinfo->limit = cachep->limit;
    sinfo->batchcount = cachep->batchcount;
    sinfo->shared = cachep->shared;
    sinfo->objects_per_slab = cachep->num;
    sinfo->cache_order = cachep->gfporder;
}
#endif


#ifdef CONFIG_SLUB
static void srecorder_do_get_slabinfo(struct kmem_cache *s, struct slabinfo *sinfo)
{
    unsigned long nr_partials = 0;
    unsigned long nr_slabs = 0;
    unsigned long nr_objs = 0;
    unsigned long nr_free = 0;
    int node;
    
    if (NULL == s || NULL == sinfo)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
    
    for_each_online_node(node)
    {
        struct kmem_cache_node *n = srecorder_get_node(s, node);
        if (NULL == n)
        {
            continue;
        }

        nr_partials += n->nr_partial;
#ifdef CONFIG_SLUB_DEBUG
        nr_slabs += atomic_long_read(&n->nr_slabs);
        nr_objs += atomic_long_read(&n->total_objects);
#endif
        nr_free += srecorder_count_partial(n, srecorder_count_free);
    }

    sinfo->active_objs = nr_objs - nr_free;
    sinfo->num_objs = nr_objs;
    sinfo->active_slabs = nr_slabs;
    sinfo->num_slabs = nr_slabs;
    sinfo->objects_per_slab = srecorder_oo_objects(s->oo);
    sinfo->cache_order = srecorder_oo_order(s->oo);
}
#endif


static void srecorder_memcg_accumulate_slabinfo(struct kmem_cache *s, struct slabinfo *info)
{
    struct kmem_cache *c;
    struct slabinfo sinfo;
    int i;
    
    if (NULL == s || NULL == info)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }

    if (!srecorder_is_root_cache(s))
    {
        return;
    }

    for_each_memcg_cache_index(i)
    {
        c = srecorder_cache_from_memcg(s, i);
        if (NULL == c)
        {
            continue;
        }

        memset(&sinfo, 0, sizeof(sinfo));
        srecorder_do_get_slabinfo(c, &sinfo);

        info->active_slabs += sinfo.active_slabs;
        info->num_slabs += sinfo.num_slabs;
        info->shared_avail += sinfo.shared_avail;
        info->active_objs += sinfo.active_objs;
        info->num_objs += sinfo.num_objs;
    }
}
#endif


/**
    @function: static int srecorder_dump_slabinfo(srecorder_reserved_mem_info_for_log_t *pmem_info, void *p)
    @brief: 读取每个slab节点的信息

    @param: pmem_info SRecorder的保留内存信息
    @param: p cache_chain链表中的一个节点
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
static int srecorder_dump_slabinfo(srecorder_reserved_mem_info_t *pmem_info, void *p)
{
    int bytes_read = 0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
    struct slabinfo sinfo = {0};
    struct kmem_cache *s = list_entry(p, struct kmem_cache, list);
    
    memset(&sinfo, 0, sizeof(sinfo));
    srecorder_do_get_slabinfo(s, &sinfo);
    srecorder_memcg_accumulate_slabinfo(s, &sinfo);
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%-17s %6lu %6lu %6u %4u %4d"
        " : tunables %4u %4u %4u"
        " : slabdata %6lu %6lu %6lu\n", 
        srecorder_cache_name(s), sinfo.active_objs, sinfo.num_objs, s->size, sinfo.objects_per_slab, (1 << sinfo.cache_order), 
        sinfo.limit, sinfo.batchcount, sinfo.shared, 
        sinfo.active_slabs, sinfo.num_slabs, sinfo.shared_avail);
#else
#ifdef CONFIG_SLAB
    struct kmem_cache *cachep = list_entry(p, struct kmem_cache, next);
    struct slab *slabp;
    unsigned long active_objs = 0;
    unsigned long num_objs = 0;
    unsigned long active_slabs = 0;
    unsigned long num_slabs = 0;
    unsigned long free_objects = 0;
    unsigned long shared_avail = 0;
    const char *name = NULL;
    char *error = NULL;
    int node;
    struct kmem_list3 *l3 = NULL;
    
    if (NULL == pmem_info || NULL == cachep)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    for_each_online_node(node) 
    {
        l3 = cachep->nodelists[node];
        if (NULL == l3)
        {
            continue;
        }
        
        check_irq_on();
        if (spin_trylock_irq(&l3->list_lock))
        {
            list_for_each_entry(slabp, &l3->slabs_full, list) 
            {
                if (slabp->inuse != cachep->num && NULL == error)
                {
                    error = "slabs_full accounting error";
                }
                active_objs += cachep->num;
                active_slabs++;
            }
            
            list_for_each_entry(slabp, &l3->slabs_partial, list) 
            {
                if (slabp->inuse == cachep->num && NULL == error)
                {
                    error = "slabs_partial inuse accounting error";
                }
                
                if (!slabp->inuse && NULL == error)
                {
                    error = "slabs_partial/inuse accounting error";
                }
                active_objs += slabp->inuse;
                active_slabs++;
            }
            
            list_for_each_entry(slabp, &l3->slabs_free, list) 
            {
                if (slabp->inuse && NULL == error)
                {
                    error = "slabs_free/inuse accounting error";
                }
                num_slabs++;
            }
            
            free_objects += l3->free_objects;
            if (l3->shared)
            {
                shared_avail += l3->shared->avail;
            }

            spin_unlock_irq(&l3->list_lock);
        }
    }
    
    num_slabs += active_slabs;
    num_objs = num_slabs * cachep->num;
    if ((num_objs - active_objs) != free_objects && NULL == error)
    {
        error = "free_objects accounting error";
    }

    name = cachep->name;
    if (NULL != error)
    {
        PRINT_INFO((KERN_ERR "slab: cache %s error: %s\n", name, error), DEBUG_SLAB_INFO);
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%-17s %6lu %6lu %6u %4u %4d"
        " : tunables %4u %4u %4u"
        " : slabdata %6lu %6lu %6lu\n", 
        name, active_objs, num_objs, cachep->buffer_size, cachep->num, (1 << cachep->gfporder), 
        cachep->limit, cachep->batchcount, cachep->shared, 
        active_slabs, num_slabs, shared_avail);
#elif defined(CONFIG_SLUB)
    unsigned long nr_partials = 0;
    
#ifdef CONFIG_SLUB_DEBUG
    unsigned long nr_slabs = 0;
#endif
    
    unsigned long nr_inuse = 0;
    unsigned long nr_objs = 0;
    unsigned long nr_free = 0;
    struct kmem_cache *s = NULL;
    int node;

    s = list_entry(p, struct kmem_cache, list);

    for_each_online_node(node)
    {
        struct kmem_cache_node *n = srecorder_get_node(s, node);

        if (NULL == n)
        {
            continue;
        }

        nr_partials += n->nr_partial;
#ifdef CONFIG_SLUB_DEBUG
        nr_slabs += atomic_long_read(&n->nr_slabs);
        nr_objs += atomic_long_read(&n->total_objects);
#endif
        nr_free += srecorder_count_partial(n, srecorder_count_free);
    }

    nr_inuse = (0 == nr_objs) ? (0UL) : (nr_objs - nr_free);
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%-17s %6lu %6lu %6u %4u %4d"
        " : tunables %4u %4u %4u"
        " : slabdata %6lu %6lu %6lu\n", 
        s->name, 
        nr_inuse, 
#ifdef CONFIG_SLUB_DEBUG
        nr_objs, 
#else
        0UL, 
#endif
        s->size, srecorder_oo_objects(s->oo), (1 << srecorder_oo_order(s->oo)), 
        0UL, 0UL, 0UL, 
#ifdef CONFIG_SLUB_DEBUG
        nr_slabs, nr_slabs, 0UL
#else
        0UL, 0UL, 0UL
#endif
        );
#endif
#endif

    srecorder_renew_meminfo(pmem_info, bytes_read);

    return 0;
}


/**
    @function: int srecorder_get_slabinfo(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取slabinfo

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_slabinfo(srecorder_reserved_mem_info_t *pmem_info)
{
    int ret;
    loff_t pos = 0;
    void *ptr = NULL;
    psrecorder_info_header_t pinfo_header = NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
    /* The slab cache mutex protects the management structures during changes */
    extern struct mutex slab_mutex;

    /* The list of all slab caches on the system */
    extern struct list_head slab_caches;
#else
#ifdef CONFIG_SLAB
    struct mutex *cache_chain_mutex = (struct mutex *)srecorder_get_cache_chain_mutex();
    struct list_head *cache_chain = (struct list_head *)srecorder_get_cache_chain();
#elif defined(CONFIG_SLUB)
    struct rw_semaphore *slub_lock = (struct rw_semaphore *)srecorder_get_slub_lock();
    struct list_head *slab_caches = (struct list_head *)srecorder_get_slab_caches(); 
#endif
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0))
    if (NULL == pmem_info 
#ifdef CONFIG_SLAB
        || NULL == cache_chain_mutex 
        || NULL == cache_chain 
#elif defined(CONFIG_SLUB)
        || NULL == slub_lock 
        || NULL == slab_caches 
#endif
        )
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return -1;
    }
#endif

    if (srecorder_log_has_been_dumped(SLABINFO_BIT6) || pmem_info->dump_modem_crash_log_only)
    {
        SRECORDER_PRINTK("slab info has been dumped successfully!\n");
        return 0;
    }
    
    if (0 != srecorder_write_info_header(pmem_info, SLABINFO_BIT6, &pinfo_header))
    {
        return -1;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
    if (mutex_trylock(&slab_mutex))
#else
#ifdef CONFIG_SLAB
    if (mutex_trylock(cache_chain_mutex))
#elif defined(CONFIG_SLUB)
    if (down_read_trylock(slub_lock))
#endif
#endif
    {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
        ptr = srecorder_slabinfo_start(pmem_info, &slab_caches, &pos);
#else
#ifdef CONFIG_SLAB
        ptr = srecorder_slabinfo_start(pmem_info, cache_chain, &pos);
#elif defined(CONFIG_SLUB)
        ptr = srecorder_slabinfo_start(pmem_info, slab_caches, &pos);
#endif
#endif
        while (1)
        {
            if (NULL == ptr || 0 == pmem_info->bytes_left)
            {
                break;
            }
            
            ret = srecorder_dump_slabinfo(pmem_info, ptr);
            if (ret < 0)
            {
                break;
            }
            
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
            ptr = srecorder_slabinfo_next(ptr, &slab_caches, &pos);
#else
#ifdef CONFIG_SLAB
            ptr = srecorder_slabinfo_next(ptr, cache_chain, &pos);
#elif defined(CONFIG_SLUB)
            ptr = srecorder_slabinfo_next(ptr, slab_caches, &pos);
#endif
#endif
        }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
        mutex_unlock(&slab_mutex);
#else
#ifdef CONFIG_SLAB
        mutex_unlock(cache_chain_mutex);
#elif defined(CONFIG_SLUB)
        up_read(slub_lock);
#endif
#endif
    }
    
    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_init_slabinfo(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化slabinfo模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_slabinfo(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(SLABINFO_BIT6);
    
    return 0;
}


/**
    @function: void srecorder_exit_slabinfo(void)
    @brief: 退出slabinfo模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_slabinfo(void)
{
    srecorder_set_log_dumped_bit(SLABINFO_BIT6);
}
#else
int srecorder_get_slabinfo(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_slabinfo(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_slabinfo(void)
{
    return;
}
#endif

