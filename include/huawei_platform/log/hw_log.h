#ifndef _LINUX_HWLOG_H
#define _LINUX_HWLOG_H

#include <linux/printk.h>
#include <linux/types.h>


enum {
	HWLOG_ERR         = 1U << 0,
	HWLOG_WARNING     = 1U << 1,
	HWLOG_INFO        = 1U << 2,
	HWLOG_DEBUG       = 1U << 3,
	HWLOG_DEBUG1      = 1U << 4,
	HWLOG_DEBUG2      = 1U << 5,
	HWLOG_DEBUG3      = 1U << 6,
	HWLOG_DEBUG4      = 1U << 7,
};

#define HWLOG_TAG_DEFOUTL_LEVEL (HWLOG_ERR \
                                | HWLOG_WARNING \
                                | HWLOG_INFO)

struct huawei_log_tag {
	const char *name;
	u32 level;
};


#define HWLOG_REGIST()	\
        HWLOG_REGIST_TAG_LEVEL(HWLOG_TAG, HWLOG_TAG_DEFOUTL_LEVEL)

#define HWLOG_REGIST_LEVEL(level)	\
        HWLOG_REGIST_TAG_LEVEL(HWLOG_TAG, level)

#define HWLOG_REGIST_TAG_LEVEL(name,level)	\
        _HWLOG_REGIST_TAG_LEVEL(name, level)

#define _HWLOG_REGIST_TAG_LEVEL(name,level)	\
	static struct huawei_log_tag TAG_STRUCT_NAME(name)	\
	__used								\
    __attribute__ ((unused,__section__ ("__hwlog_tag"))) \
	= { #name, level}

#define hwlog_err(x...) \
        _hwlog_err(HWLOG_TAG,##x)

#define _hwlog_err(TAG,x...) \
        __hwlog_err(TAG,##x)

#define __hwlog_err(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_ERR) \
            pr_err(hw_fmt_tag(TAG,E) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_warn(x...) \
        _hwlog_warn(HWLOG_TAG,##x)

#define _hwlog_warn(TAG,x...) \
        __hwlog_warn(TAG,##x)

#define __hwlog_warn(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_WARNING) \
            pr_err(hw_fmt_tag(TAG,W) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_info(x...) \
        _hwlog_info(HWLOG_TAG,##x)

#define _hwlog_info(TAG,x...) \
        __hwlog_info(TAG,##x)

#define __hwlog_info(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_INFO) \
            pr_info(hw_fmt_tag(TAG,I) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_debug(x...) \
        _hwlog_debug(HWLOG_TAG,##x)

#define _hwlog_debug(TAG,x...) \
        __hwlog_debug(TAG,##x)

#define __hwlog_debug(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_DEBUG) \
            pr_err(hw_fmt_tag(TAG,D) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_debug1(x...) \
        _hwlog_debug1(HWLOG_TAG,##x)

#define _hwlog_debug1(TAG,x...) \
        __hwlog_debug1(TAG,##x)

#define __hwlog_debug1(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_DEBUG1) \
            pr_err(hw_fmt_tag(TAG,D1) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_debug2(x...) \
        _hwlog_debug2(HWLOG_TAG,##x)

#define _hwlog_debug2(TAG,x...) \
        __hwlog_debug2(TAG,##x)

#define __hwlog_debug2(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_DEBUG2) \
            pr_err(hw_fmt_tag(TAG,D2) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_debug3(x...) \
        _hwlog_debug3(HWLOG_TAG,##x)

#define _hwlog_debug3(TAG,x...) \
        __hwlog_debug3(TAG,##x)

#define __hwlog_debug3(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_DEBUG3) \
            pr_err(hw_fmt_tag(TAG,D3) fmt,##__VA_ARGS__);    \
    }while(0)

#define hwlog_debug4(x...) \
        _hwlog_debug4(HWLOG_TAG,##x)

#define _hwlog_debug4(TAG,x...) \
        __hwlog_debug4(TAG,##x)

#define __hwlog_debug4(TAG,fmt, ...) \
    do{ \
        if(TAG_STRUCT_NAME(TAG).level & HWLOG_DEBUG4) \
            pr_err(hw_fmt_tag(TAG,D4) fmt,##__VA_ARGS__);    \
    }while(0)

#define TAG_STRUCT_NAME(name) \
        _hwtag_##name

#define hw_fmt_tag(TAG,LEVEL) "[" #LEVEL "/" #TAG "] "


#endif
