#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/version.h>
long long ras_div(long long num, long long den)
{
 #define RAS_DIV
#ifndef RAS_DIV
        return num / den;
#else
        unsigned long long ret = 0;
        while(num >= den)
        {
                ret++;
                num-=den;
        }
        return ret;

#endif
//	return do_div(n, base);
}
#if !defined(__VMKLNX__)
#include "rasbase.h"
#include <linux/file.h>
#include <linux/sched.h>
#include <linux/delay.h>
static int ras_readline(struct file *filp, char *buf, int len)
{
	int ret = 0;
    int readlen = 0;
    mm_segment_t oldfs;
    ras_retn_if(0 == filp, -ENOENT);
    ras_retn_if(0 == filp->f_op->read, -ENOSYS);
    ras_retn_if(((filp->f_flags & O_ACCMODE) & O_RDONLY), -EACCES);
	
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    for(; readlen < len; buf++, readlen++)
    {
    	ret = filp->f_op->read(filp, buf, 1, &filp->f_pos);
    	if(ret <= 0)
    	{
    		break;
    	}
		if('\n' == *buf)
		{
			*buf = 0;
			readlen++;
			break;
		}
    }
    
    set_fs(oldfs);
    return ret < 0 ? ret : readlen;
}

int ras_read(const char* filename, int (*line)(void*, const char*), void* data)
{
	int ret = 0;
	char buf[512];
	struct file* filp = filp_open(filename, O_RDONLY, 0);
	ras_retn_if(IS_ERR(filp), PTR_ERR(filp));
	while((ret = ras_readline(filp, buf, sizeof(buf))) > 0) {
		if(0 != (ret = line(data, buf)))
		{
			break;
		}
	}
	fput(filp);
	ras_retn(ret);
}
#endif
///////////////////// raslist //////////////////////////////

struct RasList
{
	struct RasList* nxt;
};
int raslist_create(struct RasList** list, void (*dtor)(const void*));
int raslist_add(struct RasList* list, void* addr);
int raslist_remove(struct RasList* list, void* addr);
int raslist_size(struct RasList* list);
void* raslist_get(struct RasList* list, int idx);
void raslist_destroy(struct RasList* list);

///////////////////// rasmap //////////////////////////////
struct RasMapElement
{
	struct RasMapElement* nxt;
	struct RasMapElement* rme;
	void* key;
	void* val;
	loff_t tm;
};

struct RasMap
{
	struct RasMapElement* nxt; // valid RME
	struct RasMapElement* rme; // destroyed RME
	rasmap_free_t *destroy;
	rasmap_less_t *less;
	void* data;
};

int rasmap_create(struct RasMap** rm, rasmap_less_t *less,
	rasmap_free_t *destroy, void* data)
{
	struct RasMap* m = 0;
	ras_retn_if(0 == rm, -EINVAL);
	ras_retn_iferr(ras_malloc((void**)&m, sizeof(struct RasMap)));
	m->less = less;
	m->destroy = destroy;
	m->data = data;
	m->nxt = 0;
	m->rme = 0;
	*rm = m;
	return 0;
}

static struct RasMapElement* rasmap_findrme(struct RasMap* rm)
{
	struct RasMapElement* rme;
	loff_t tm = ras_ms() - 60000; // 1m
	if(0 == rm || 0 == (rme = rm->rme))
	{
		return 0;
	}
	if(rme->tm < tm)
	{
		rm->rme = rme->rme;
		return rme;
	}
	for(; 0 != rme->rme; rme = rme->rme)
	{
		if(rme->rme->tm < tm)
		{
			struct RasMapElement* ele = rme->rme;
			rme->rme = ele->rme;
			ele->rme = 0;
			return ele;
		}
	}
	return 0;
}

static inline int rasmap_desrme(void* data, void* key, void* val)
{
	struct RasMap* rm = data;
	if(0 != rm->destroy)
	{
		rm->destroy(rm->data, key, val);
	}
	return 0;
}

int rasmap_add(struct RasMap* rm, void* key, void* val)
{
	struct RasMapElement* rme = rasmap_findrme(rm);
	if(0 != rme)
	{
		rasmap_desrme(rm, rme->key, rme->val);
	}
	else if(0 != ras_malloc((void**)&rme, 
		sizeof(struct RasMapElement)))
	{
		ras_retn(-ENOMEM);
	}
	rme->tm = 0;
	rme->key = key;
	rme->val = val;	
	rme->nxt = rm->nxt;
	rm->nxt = rme;
	return 0;
}

static inline int rasmap_equals(struct RasMap* rm, void* k1, void* k2)
{
	if(0 != rm->less)
	{
		return !rm->less(rm->data, k1, k2) && !rm->less(rm->data, k2, k1);
	}
	
	return k1 == k2;
}

static struct RasMapElement* rasmap_find(struct RasMap* rm, 
	void* key, int del)
{
	struct RasMapElement* rme;
	if(0 == rm || 0 == (rme = rm->nxt))
	{
		return 0;
	}
	if(rasmap_equals(rm, rme->key, key))
	{
		if(0 != del)
		{
			rm->nxt = rme->nxt;
		}
		return rme;
	}
	for(; 0 != rme->nxt; rme = rme->nxt)
	{
		if(rasmap_equals(rm, rme->nxt->key, key))
		{
			struct RasMapElement* tmp = rme->nxt;
			if(0 != del)
			{
				rme->nxt = tmp->nxt;
			}
			return tmp;
		}
	}
	return 0;
}

int rasmap_each(struct RasMap* rm, rasmap_each_t* each, void* data)
{
	struct RasMapElement* rme;
	ras_retn_if((0 == rm || 0 == each), -EINVAL);
	
	for(rme = rm->nxt; 0 != rme; rme = rme->nxt)
	{
		ras_retn_iferr(each(data, rme->key, rme->val));
	}
	return 0;
	
}

int rasmap_size(struct RasMap* rm)
{
	int cnt = 0;
	struct RasMapElement* rme;
	ras_retn_if(0 == rm, cnt);
	for(rme = rm->nxt; 0 != rme; rme = rme->nxt)
	{
		cnt++;
	}
	return cnt;
}

static int rasmap_eachrme(struct RasMap* rm, int (*each)(void* data, 
	void* key, void* val), void* data)
{
	struct RasMapElement* rme = rm->rme;
	for(; 0 != rme; rme = rme->rme)
	{
		ras_retn_iferr(each(data, rme->key, rme->val));
	}
	return 0;
}

void* rasmap_get(struct RasMap* rm, void* key)
{
	struct RasMapElement* rme = rasmap_find(rm, key, 0);
	return (0 != rme && 0 == rme->tm) ? rme->val : 0;
}

static inline void rasmap_addrme(struct RasMap* rm, 
	struct RasMapElement* rme)
{
	rme->tm = ras_ms();
	rme->rme = rm->rme;
	rm->rme = rme;
}

void rasmap_del(struct RasMap* rm, void* key)
{
	struct RasMapElement* rme = rasmap_find(rm, key, 1);
	if(0 != rme)
	{
		rasmap_addrme(rm, rme);
	}
}

void rasmap_clear(struct RasMap* rm)
{
	struct RasMapElement* rme = rm->nxt;
	for(rm->nxt = 0/* clear */; 0 != rme; rme = rme->nxt)
	{
		// add to rme
		rasmap_addrme(rm, rme);
	}
}

void rasmap_destroy(struct RasMap* rm)
{
	if(0 == rm)
	{
		return;
	}
	if(0 != rm->destroy)
	{
		rasmap_clear(rm);
		rasmap_eachrme(rm, rasmap_desrme, rm);
	}
	ras_free(rm);
}
////////////////////////////////////////////////////////
struct RasBff
{
	struct RasBff* prv;
	struct RasBff* nxt;
	int length;
	char bff[1024-sizeof(int)-2*sizeof(struct RasBff*)];
};

struct RasVector
{
	int page;
	int length;
	rwlock_t rwk;
	struct RasBff* bff;
};

int rasvector_create(struct RasVector** self)
{
	struct RasVector* vec = 0;
	int len = sizeof(struct RasBff);
	ras_retn_iferr(ras_malloc((void**)&vec, sizeof(struct RasVector)));
	ras_retn_iferr_then(ras_malloc((void**)&vec->bff, len), ras_free(vec));
	vec->bff->nxt = vec->bff;
	vec->bff->prv = vec->bff;
	rwlock_init(&vec->rwk);
	*self = vec;
	return 0;
}

static inline struct RasBff* rasvector_tail(struct RasVector* vec)
{
	int len = vec->length;
	struct RasBff* bff = vec->bff;
	while(len > bff->length)
	{
		len -= bff->length;
		bff = bff->nxt;
	}
	return bff;
}

static inline int rasvector_grow(struct RasVector* vec, 
	struct RasBff* trb, int length)
{
	while(trb->length + length >= sizeof(trb->bff))
	{
		length = length - sizeof(trb->bff) + trb->length;
		if(trb->nxt == vec->bff)
		{
			struct RasBff* nrb = 0;
			ras_retn_iferr(ras_malloc((void**)&nrb, sizeof(struct RasBff)));
			vec->page++;
			nrb->nxt = trb->nxt;
			nrb->nxt->prv = nrb;
			nrb->prv = trb;
			trb->nxt = nrb;
		}
		else
		{
			trb = trb->nxt;				
		}
	}
	return 0;
}
static inline int rasvector_copy(struct RasVector* vec, 
	struct RasBff* rb, const char* str)
{
	int i, len = strlen(str);
	ras_retn_iferr(rasvector_grow(vec, rb, len));
	for(i = 0; i < len; i++)
	{
		if(rb->length == sizeof(rb->bff))
		{
			rb = rb->nxt;
			rb->length = 0;
		}
		rb->bff[rb->length++] = str[i];
	}
	vec->length += len;
	return 0;
}

int rasvector_append(struct RasVector* vec, const char* str)
{
	int ret;
	write_lock(&vec->rwk);
	ret = rasvector_copy(vec, rasvector_tail(vec), str);
	write_unlock(&vec->rwk);
	ras_retn(ret);
}

static inline int rasvector_sub(struct RasVector* vec, int idx, int len, char* buf)
{
	int i = 0;
	struct RasBff* bff = vec->bff;
	if(idx + len > vec->length)
	{
		ras_retn(-ESPIPE);
	}
	while(idx - bff->length >= 0)
	{
		idx -= bff->length;
		bff = bff->nxt;
	}
	for(i = 0; i < len; i++)
	{
		buf[i]=bff->bff[idx+i];
		if(idx+i+1 == bff->length)
		{
			bff = bff->nxt;
			idx = -i - 1;
		}
	}
	return 0;
}

int rasvector_substr(struct RasVector* vec, int beginIndex, int length, char* savedbuf)
{
	int ret;
	read_lock(&vec->rwk);
	ret = rasvector_sub(vec, beginIndex, length, savedbuf);
	read_unlock(&vec->rwk);
	return ret;
}

int rasvector_reset(struct RasVector* vec)
{
	struct RasBff* nxt;
	write_lock(&vec->rwk);
	for(nxt = vec->bff->nxt; nxt != vec->bff; nxt = nxt->nxt)
	{
		nxt->length = 0;
	}
	vec->length = 0;
	vec->bff->length = 0;
	write_unlock(&vec->rwk);
	return 0;
}

int rasvector_length(struct RasVector* vec)
{
	int len;
	read_lock(&vec->rwk);
	len = vec->length;
	read_unlock(&vec->rwk);
	return len;
}

int rasvector_destroy(struct RasVector* vec)
{
	struct RasBff* nxt;
	struct RasBff* prv;
	write_lock(&vec->rwk);
	nxt = vec->bff->nxt; 
	while(nxt != vec->bff)
	{
		prv = nxt;
		nxt = prv->nxt;
		ras_free(prv);
	}
	ras_free(vec->bff);
	write_unlock(&vec->rwk);
	ras_free(vec);
	return 0;
}

void rasvector_display(struct RasVector* vec)
{
	char buf[128];
	int len = 0;
	snprintf(buf, sizeof(buf), "length=%d, bffsize=%d\n", 
		vec->length, vec->page+1);
	len = ras_debugset(0);
	ras_info(buf);
	ras_debugset(len);
}

///////////////////////////////////////////////////////
struct RasProc {
	struct RasVector* vec;
	struct proc_dir_entry* pde;
	void* data;
};
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
int rasproc_create(struct RasProc** self, const char* name, 
	read_proc_t* pread, write_proc_t* pwrite, void* data)
{
	struct proc_dir_entry* pde = 0;
	struct RasProc* rp = 0;
	ras_retn_iferr(ras_malloc((void**)&rp, sizeof(struct RasProc)));
	ras_retn_iferr_then(rasvector_create(&rp->vec), ras_free(rp));
	pde = create_proc_entry(name, S_IFREG | 0666, 0);
	if(unlikely(0 == pde))
	{
		rasvector_destroy(rp->vec);
		ras_free(rp);
		ras_retn(-ENOMEM);
	}
	pde->data = data;
	pde->read_proc = pread;
	pde->write_proc = pwrite;
	pde->mode = S_IFREG | 0666;
#if !defined(__VMKLNX__)

	pde->uid = 0;
	pde->gid = 0;
#endif
	pde->size= 0;
	rp->data = data;
	rp->pde = pde;
	*self = rp;
	return 0;
}
#endif
int rasproc_read(struct RasProc* self, void (*update)(struct RasProc*), 
	char* buf, char** bl, off_t offset, int len, int* eof)
{
	int used;
	if(0 == offset)
	{
		rasvector_reset(self->vec);
		update(self);
//		rasvector_display(self->vec);
	}
	used = rasvector_length(self->vec);
	if(offset >= used)
	{
		*eof = 1;
		return 0;
	} 
	len--; // TODO delete this?
	if(used - offset < len)
	{
		len = used - offset;
	}
	rasvector_substr(self->vec, offset, len, buf);
	return len;

}

void* rasproc_data(struct RasProc* proc)
{
	return proc->data;
}

int rasproc_append(struct RasProc* self, const char* str)
{
	return rasvector_append(self->vec, str);
}
/////////////////////////////////////////////////////
struct RasArgs
{
	int argc;
	char** args;
	char* arg;
	int len;
};

static void rasargs_cut(struct RasArgs* rargs)
{
	const char* arg = rargs->arg;
	rargs->argc = 1;
	
	while(1)
	{
		arg = ras_skipnull(arg, rargs->len - (arg - rargs->arg));
		if(0 == arg)
		{
			return;
		}
		arg = ras_skipword(arg, rargs->len - (arg - rargs->arg));
		if(0 == arg || 0 == *arg)
		{
			return;
		}
		rargs->arg[arg-rargs->arg] = 0;
		rargs->argc++;
	}
}

static char* rasargs_nextword(struct RasArgs* rargs, int* i)
{
	const char* tmp;
	const char* arg = rargs->arg + *i;
	arg = ras_skipnull(arg, rargs->len - (arg - rargs->arg));
	tmp = ras_skipword(arg, rargs->len - (arg - rargs->arg));
	*i = 0 == tmp ? rargs->len : tmp - rargs->arg;
	return (char*)arg;
}

static int rasargs_ctor(struct RasArgs* rargs,
	const char* args, int len)
{
	int i, j;
	rargs->len = len + 1;
	ras_retn_iferr(ras_malloc((void**)&rargs->arg, rargs->len));
	memcpy(rargs->arg, args, len);
	rargs->arg[len] = 0;
	
	rasargs_cut(rargs);
	ras_retn_iferr_then(ras_malloc((void**)&rargs->args,
		rargs->argc*sizeof(char*)),	ras_free(rargs->arg));
	for(i = 0, j = 0; j < rargs->argc && i < rargs->len;)
	{
		rargs->args[j++] = rasargs_nextword(rargs, &i);
	}
	if(0 == rargs->args[rargs->argc-1])
	{
		rargs->argc--;
	}
	return 0;
}

static void rasargs_dtor(struct RasArgs* rargs)
{
	ras_free(rargs->arg);
	ras_free(rargs->args);
}

int ras_args(const char* args, unsigned long len, 
	int (*process)(void* dt, int argc, char* args[]), void* dt)
{
	int ret;	
	struct RasArgs rargs;
	if(0 == args || 0 >= len || 0 == process)
	{
		ras_retn(-EINVAL);
	}
	ras_retn_iferr(rasargs_ctor(&rargs, args, len));
	ret = process(dt, rargs.argc, rargs.args);
	rasargs_dtor(&rargs);
	ras_retn(ret);
}


unsigned long long ras_ns(void)
{
	struct timespec ts = current_kernel_time();
	return ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

unsigned long long ras_ms(void)
{
	struct timespec ts = current_kernel_time();
	return ts.tv_sec * 1000ULL + ras_div(ts.tv_nsec,1000000);
}

static inline int ras_getbase(char c)
{
	return ('x' == c || 'X' == c) ? 16 : 8;
}
static inline int rfiler_isdigit(char c)
{
	return c >= '0' && c <= '9';
}

static inline int ras_isxdigit(char c)
{
	return (c >= '0' && c <= '9') ||
		(c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F');
}

static inline int ras_xtoi(char c)
{
	if(rfiler_isdigit(c)) 
	{
		return c - '0';
	}
	return c - ((c >= 'a' && c <= 'f') ? 'a' : 'A') + 10 ;
}

static inline int ras_invalidparam(const char* a, unsigned long pos)
{
	char bff[256];
	snprintf(bff, sizeof(bff), "%s[%lu] is a invalid parameter", a, pos);
	ras_fail(bff);
	ras_retn(-EINVAL);
}

static inline int ras_isxbyte(char c)
{
	static char bcs[] = {'k','K','m','M','g','G','t','T'};
	int i, len = ARRAY_SIZE(bcs);
	for(i = 0; i < len; i++)
	{
		if(c == bcs[i])
		{
			return 1 + i/2;
		}
	}
	return 0;
}
static inline long long ras_getbyte(int count)
{
	long long val = 1LL;
	int i;
	for(i = 0; i < count; i++)
	{
		val *= 1024LL;
	}
	return val;
}

int ras_equal(const char* exp, const char* act)
{
	while(*exp && *exp==*act) {
		exp++;
		act++;
	}
	return *exp == *act;
}

int ras_atoll(long long *ll, const char* a, long len, long* ppos)
{
	char c = 0;
	int cv = 0;
	int base = 10;
	long long rlt = 0LL;
	unsigned long pos = 0;
	char is_negative = 0;
	if(0 == ll || 0 == a || 0 == len)
	{
		ras_retn(-EINVAL);
	}

	if(0 != ppos) 
	{
		pos = *ppos;
	}
	
	while(ras_isspace(a[pos]))
	{
		if(++pos >= len)
		{
			ras_retn(-EPERM);
		}
	}
	if(0 == a[pos])
	{
		ras_retn(-EPERM);
	}
	
	//init base
	if(('0' == a[pos]) && (pos + 1 < len))
	{
		c = a[pos+1];
		if(!ras_isspace(c))
		{
			base = ras_getbase(c);
			pos += (base >> 3);
		}
	}

	//init signed
	if(('-' == a[pos]) && (pos + 1 < len)) {
		is_negative = 1;
		pos++;
	}
	else if(('+' == a[pos]) && (pos + 1 < len)) {
		is_negative = 0;
		pos++;
	}

	for(; pos < len; pos++)
	{
		c = a[pos];
		if(ras_isxdigit(c))
		{
			cv = ras_xtoi(c);
		}
		else if(0 != (cv = ras_isxbyte(c)))
		{
			rlt = rlt*ras_getbyte(cv);
			c = a[pos+1];
			if(0 == c || ras_isspace(c))
			{
				break;
			} 
			else
			{
				ras_retn(ras_invalidparam(a, pos+1));
			}
		}
		else if(0 == c || ras_isspace(c))
		{
			break;
		}
		else
		{
			ras_retn(ras_invalidparam(a, pos));
		}
		if(cv >= base)
		{
			ras_retn(ras_invalidparam(a, pos));
		}
		rlt = rlt * base + cv;
	}
	
	*ll = is_negative ? -rlt:rlt;
	if(0 != ppos) 
	{
		*ppos = pos;
	}
	return 0;
}

int ras_isspace(char c)
{
	static char cs[] = {' ', '\t', '\r', '\n'};
	int i = 0;
	int len = ARRAY_SIZE(cs);
	for(i = 0; i < len; i++)
	{
		if(c == cs[i]) 
		{
			return c;
		}
	}
	return 0;
}

char* ras_trim(char* s, int* n)
{
	int i, len = *n;
	for(i = 0; i < len; i++)
	{
		if(!ras_isspace(s[i]))
		{
			break;
		}
	}
	while(--len > 0)
	{
		if(!ras_isspace(s[len]))
		{
			break;
		}
		s[len] = 0;
	}
	*n = len + 1 - i;
	return s + i;
}

const char* ras_skipword(const char* bff, unsigned long len)
{
	unsigned long idx;
	if(0 == bff)
	{
		return 0;
	}
	for(idx = 0; idx < len; idx++)
	{
		if(0 == bff[idx] || ras_isspace(bff[idx]))
		{
			break;
		}
	}
	if(idx < len)
	{
		return bff + idx;
	}
	return 0;
	
}

const char* ras_skipnull(const char* bff, unsigned long len)
{
	unsigned long idx = 0;
	if(0 == bff)
	{
		return 0;
	}
	for(idx = 0; idx < len; idx++)
	{
		if(0 == bff[idx])
		{
			continue;
		}
		if(!ras_isspace(bff[idx]))
		{
			break;
		}
	}
	if(idx < len)
	{
		return bff + idx;
	}
	return 0;
}

int ras_malloc(void** m, long len)
{
	void* p;
	if(0 == m)
	{
		ras_retn(-EINVAL);
	}
	p = kmalloc(len, GFP_ATOMIC);
	if(0 == (*m = p))
	{
		ras_retn(-ENOMEM);
	}
	memset(*m, 0, len);
	return 0;
}

void ras_free(const void* p)
{
	if(0 != p)
	{
		kfree(p);
	}
}


enum RasDebugType
{
	RAS_DEBUG,
	RAS_INFO,
	RAS_WARN,
	RAS_FAIL,
	RAS_NULL,
};

#define DBG_SET 1
static inline int ras_debug(const int op, int lvl)
{
	static int level = RAS_WARN;
	if(DBG_SET == op && -1 != lvl && lvl != level)
	{
		int lev = level;
		level = lvl;
		return lev;
	}
	return level;
}

int ras_debugset(int lvl)
{
	return ras_debug(DBG_SET, lvl);
}

int __ras_retn(const char* filename, 
	const char* func, int line, int ret)
{
	if(RAS_DEBUG >= ras_debug(!DBG_SET, 0) && ret)
	{
		printk("%-3d = %s:%d\n", ret, func, line);
	}
	return ret;
}

int __ras_info(const char* file, const char* func, 
	int line, const char* msg)
{
	if(RAS_INFO >= ras_debug(!DBG_SET, 0))
	{
		printk("%s -> %s:%d\n", msg, func, line);
	}
	return 0;
}

int __ras_warn(const char* file, const char* func, 
	int line, const char* msg)
{
	if(RAS_WARN >= ras_debug(!DBG_SET, 0))
	{
		printk("%s -> %s:%d\n", msg, func, line);
	}
	return 0;
}

int __ras_fail(const char* file, const char* func, 
	int line, const char* msg)
{
	if(RAS_FAIL >= ras_debug(!DBG_SET, 0))
	{
		printk("%s -> %s:%d\n", msg, func, line);
	}
	return 0;
}

#include <asm/delay.h>

void ras_sleep(unsigned long long ms)
{
	long jffn = ras_div(ms * HZ, 1000);
	ms -= jffn * 1000 / HZ;
	set_current_state(TASK_INTERRUPTIBLE);
	while(jffn > 0)	{
		jffn = schedule_timeout(jffn);
	}
	if(0 != ms)	{
		udelay(ms*1000);
	}
}

static unsigned long
ras_mktime(unsigned int year, unsigned int mon,
       unsigned int day, unsigned int hour,
       unsigned int min, unsigned int sec)
{
	if (0 >= (int) (mon -= 2)) {
		mon += 12;
		year -= 1;
	}

	return ((((unsigned long)
		  (year/4 - year/100 + year/400 + 367*mon/12 + day) +
		  year*365 - 719499
	    )*24 + hour /* now have hours */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finally seconds */
}


int ras_check(void)
{
	unsigned long tmout = ras_mktime(2016, 12, 30, 0, 0, 0);
	struct timespec ts = current_kernel_time();
    return ts.tv_sec > tmout ? -1 : 0;
}


