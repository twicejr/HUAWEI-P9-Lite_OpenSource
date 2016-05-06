#ifndef __RAS_BASE__
#define __RAS_BASE__

#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/version.h>
struct RasVector;
int rasvector_create(struct RasVector**);
int rasvector_append(struct RasVector*, const char* str);
int rasvector_substr(struct RasVector*, int idx, int len, char* savedbuf);
int rasvector_reset(struct RasVector*);
int rasvector_length(struct RasVector*);
int rasvector_destroy(struct RasVector*);
void rasvector_display(struct RasVector* vec);

struct RasProc;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
int rasproc_create(struct RasProc**, const char* name, 
	read_proc_t* pread, write_proc_t* pwrite, void* data);
#endif
int rasproc_read(struct RasProc*, void (*update)(struct RasProc*), 
	char* buf, char** bl, off_t offset, int len, int* eof);
int rasproc_append(struct RasProc*, const char* str);
int rasproc_destroy(struct RasProc*);
void* rasproc_data(struct RasProc*);

struct RasMap;
typedef int (rasmap_less_t)(void* data, void* k1, void* k2);
typedef int (rasmap_each_t)(void* data, void* key, void* val);
typedef void(rasmap_free_t)(void* data, void* key, void* val);
int rasmap_size(struct RasMap* rm);
int rasmap_each(struct RasMap* rm, rasmap_each_t* each, void* data);
int rasmap_add(struct RasMap* rm, void* key, void* val);
void* rasmap_get(struct RasMap* rm, void* key);
void  rasmap_del(struct RasMap* rm, void* key);
void  rasmap_clear(struct RasMap* rm);
void  rasmap_destroy(struct RasMap* rm);
int   rasmap_create(struct RasMap** rm, rasmap_less_t *less,
		rasmap_free_t *freeKV, void* data);

int ras_read(const char* filename, int (*line)(void*, const char*), void*);

// oct: 012345670 ; dec: 1234567890 ; hex: 0x1234567890abcdef
int ras_atoll(long long *ll, const char* a, long len, long* ppos);
int ras_equal(const char* exp, const char* act);
const char* ras_skipword(const char* bff, unsigned long len);
const char* ras_skipnull(const char* bff, unsigned long len);
int ras_args(const char* args, unsigned long len, 
	int (*process)(void* dt, int argc, char* args[]), void* dt);
long long ras_div(long long n, long long base);

char* ras_trim(char* s, int* n);
int ras_check(void);
int ras_isspace(char);
int ras_malloc(void**, long);
void ras_free(const void*);
#define RASTICK 3*1000/HZ
void ras_sleep(unsigned long long ms);

unsigned long long ras_ns(void);
unsigned long long ras_ms(void);

int ras_debugset(int level); // set level, return old level
#define ras_info(msg) __ras_info(__FILE__, __func__, __LINE__, msg);
#define ras_warn(msg) __ras_warn(__FILE__, __func__, __LINE__, msg);
#define ras_fail(msg) __ras_fail(__FILE__, __func__, __LINE__, msg);
#define ras_retn(ret) return __ras_retn(__FILE__, __func__, __LINE__, ret)
int __ras_info(const char* file, const char* func, int line, const char*);
int __ras_warn(const char* file, const char* func, int line, const char*);
int __ras_fail(const char* file, const char* func, int line, const char*);
int __ras_retn(const char* file, const char* func, int line, int ret);

#define ras_retn_if(con, ret) if(con) ras_retn(ret)

#define ras_retn_iferr(ret) do { \
	int ____ret = (ret); \
	if(____ret) { ras_retn(____ret); } \
} while(0)

#define ras_retn_iferr_then(ret, op) do { \
	int ____ret = (ret); \
	if(____ret) { (op); ras_retn(____ret); } \
} while(0)

#define ras_setllu_retn(rase, valu, flag, fld, arg) do {\
	int len = strlen(#fld"="); \
	if(0 == strncmp(#fld"=", arg, len)) { \
		long long val = 0; \
		char* cval = arg + len;   \
		ras_retn_if(0 == *cval, -EINVAL); \
		ras_retn_iferr(ras_atoll(&val, cval, strlen(cval), 0)); \
		rase->flag.fld = 1; \
		rase->valu.fld = val; \
		return 0; \
	} \
} while(0)

#define ras_setstr_retn(rase, valu, flag, fld, arg) do {\
	int len = strlen(#fld"="); \
	if(0 == strncmp(#fld"=", arg, len)) { \
		char* cval = arg + len;   \
		ras_retn_if(0 == *cval, -EINVAL); \
		rase->flag.fld[0] = 1; \
		strncpy(rase->valu.fld,cval,sizeof(rase->valu.fld)); \
		return 0; \
	} \
} while(0)


int rasfile_pathname(struct vfsmount* mnt, struct dentry* den, 
	int (*op)(void*, const char*), void* data);
#define rasbase_set(ins, fld, arg) do {\
        unsigned long long val = 0; \
        int len = strlen(#fld"="); \
        if(0 == strncmp(#fld"=", arg, len)) { \
            char* cval = arg + len;   \
            ras_retn_if(0 == *cval, -EINVAL);\
            ras_retn_iferr(ras_atoll(&val, cval, strlen(cval), 0)); \
            ins->fld = val; \
            return 0; \
        } \
    } while(0);
#define rasbase_set_func(ins, fld, arg,func) do {\
        int len = strlen(#fld"="); \
        if(0 == strncmp(#fld"=", arg, len)) { \
            char* cval = arg + len;   \
            ras_retn_if(0 == *cval, -EINVAL); \
            ins->fld=func(cval);\
            return 0; \
        } \
    } while(0);
#define rasbase_cset(ins, fld, arg) do {\
        int len = strlen(#fld"="); \
        if(0 == strncmp(#fld"=", arg, len)) { \
            char* cval = arg + len;   \
            ras_retn_if(0 == *cval, -EINVAL); \
            snprintf(ins->fld,BDEVNAME_SIZE-1,cval);\
            return 0; \
        } \
    } while(0);
#endif

