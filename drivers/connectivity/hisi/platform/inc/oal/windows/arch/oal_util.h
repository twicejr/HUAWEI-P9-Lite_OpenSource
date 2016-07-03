

#ifndef __OAL_WINDOWS_UTIL_H__
#define __OAL_WINDOWS_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "hsimu_reg.h"
#include <sys/stat.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 32字节序大小端转换 */
#define OAL_SWAP_BYTEORDER_32(_val)        \
        ((((_val) & 0x000000FF) << 24) +     \
        (((_val) & 0x0000FF00) << 8) +       \
        (((_val) & 0x00FF0000) >> 8) +       \
        (((_val) & 0xFF000000) >> 24))

#define OAL_CONST                                   const
/* 获取CORE ID */
#define OAL_GET_CORE_ID()     (g_cpuid_register[0])

typedef LONG                    oal_bitops;

typedef FILE                    oal_file_stru;

typedef struct _stat            oal_file_stat_stru;

#define OAL_FILE_FAIL           OAL_PTR_NULL

#define OAL_LIKELY(_expr)       (_expr)
#define OAL_UNLIKELY(_expr)     (_expr)

#if defined(_PRE_PC_LINT)
#define OAL_FUNC_NAME           "pc_lint"
#else
#define OAL_FUNC_NAME           __FUNCTION__
#endif
#define OAL_RET_ADDR             OAL_PTR_NULL


/* 将几个字符串按照指定格式合成一个字符串 */
#define OAL_SPRINTF             sprintf_s

/* 内存读屏障 */
#define OAL_RMB()

/* 内存写屏障 */
#define OAL_WMB()

/* 内存屏障 */
#define OAL_MB()

#define OAL_OFFSET_OF(TYPE,MEMBER)  ((unsigned long) &((TYPE *)0)->MEMBER)

#define __OAL_DECLARE_PACKED

#define OAL_IO_PRINT            printf

#define OAL_BUG_ON(_con)

#define OAL_WARN_ON(condition)  (condition)

#define OAL_VSPRINTF            vsprintf_s

/* 虚拟地址转物理地址 */
#define OAL_VIRT_TO_PHY_ADDR(_virt_addr)            ((oal_uint32)(_virt_addr))

/* 物理地址转虚拟地址 */
#define OAL_PHY_TO_VIRT_ADDR(_phy_addr)             ((oal_uint32 *)(_phy_addr))


#define OAL_CFG_FILE_PATH       ("C:\\1151_cfg.ini")

#ifndef current
#define current (0)
#endif

#define OAL_STRLEN                                  strlen
#define OAL_MEMCMP                                  memcmp
#define OAL_STRSTR                                  strstr
#define OAL_STRCMP                                  strcmp

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct object{
    char* name;
}oal_kobject;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#define OAL_ROUND_UP(x,y)   OAL_ROUNDUP(x,y)
#define OAL_ROUND_DOWN(value,boundary)  ((value) & (~((boundary)-1)))


/*****************************************************************************
  10 函数声明
*****************************************************************************/


OAL_INLINE oal_bitops  oal_bit_atomic_test_and_set(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    return InterlockedBitTestAndSet(p_addr, nr);
}


OAL_INLINE oal_void  oal_bit_atomic_clear(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    InterlockedBitTestAndReset(p_addr, nr);
}


OAL_INLINE oal_uint16  oal_byteorder_host_to_net_uint16(oal_uint16 us_byte)
{
    us_byte = ((us_byte & 0x00FF) << 8) + ((us_byte & 0xFF00) >> 8);

    return us_byte;
}


OAL_INLINE oal_uint16  oal_byteorder_net_to_host_uint16(oal_uint16 us_byte)
{
    us_byte = ((us_byte & 0x00FF) << 8) + ((us_byte & 0xFF00) >> 8);

    return us_byte;
}


OAL_STATIC OAL_INLINE oal_uint32  oal_byteorder_host_to_net_uint32(oal_uint32 ul_byte)
{
    ul_byte = OAL_SWAP_BYTEORDER_32(ul_byte);

    return ul_byte;
}


OAL_STATIC OAL_INLINE oal_uint32  oal_byteorder_net_to_host_uint32(oal_uint32 ul_byte)
{
    ul_byte = OAL_SWAP_BYTEORDER_32(ul_byte);

    return ul_byte;
}


OAL_INLINE oal_file_stru* oal_file_open_rw(const oal_int8 *pc_path)
{
    oal_file_stru *rlt;

    fopen_s(&rlt, pc_path, "w+");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}


OAL_INLINE oal_file_stru* oal_file_open_append(const oal_int8 *pc_path)
{
    oal_file_stru *rlt;

    fopen_s(&rlt, pc_path, "a");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}


OAL_INLINE oal_file_stru* oal_file_open_readonly(const oal_int8 *pc_path)
{
    oal_file_stru* rlt;

    fopen_s(&rlt, pc_path, "r");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}


OAL_INLINE oal_file_stru* oal_file_write(oal_file_stru* file, oal_int8 *pc_string, oal_uint32 ul_length)
{
    oal_int32 l_rlt;

    l_rlt = fprintf(file, "%s", pc_string);

    if (l_rlt < 0)
    {
        return OAL_FILE_FAIL;
    }

    return file;
}


OAL_INLINE oal_int32 oal_file_close(oal_file_stru* file)
{
    oal_int32 l_rlt;

    l_rlt = fclose(file);

    if (EOF == l_rlt)
    {
        return -1;
    }

    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_file_read(oal_file_stru *file,
		                                         oal_int8 *puc_buf,
		                                         oal_uint32 ul_count)
{
    return (oal_int32)fread(puc_buf, 1, ul_count, file);
}



OAL_INLINE oal_int32  oal_file_size(oal_uint32 *pul_file_size)
{
    oal_file_stat_stru       st_file_stat;
    oal_int32                l_ret;

    l_ret = _stat(OAL_CFG_FILE_PATH, &st_file_stat);
    if (OAL_SUCC != l_ret)
    {
        return l_ret;
    }

    *pul_file_size = (oal_uint32)st_file_stat.st_size;

    return OAL_SUCC;
}


OAL_INLINE oal_int32  oal_atoi(const oal_int8 *c_string)
{
    return atoi(c_string);
}


OAL_INLINE oal_void  oal_itoa(oal_int32 l_val, oal_int8 *c_string, oal_uint8 uc_strlen)
{
    _itoa_s(l_val, c_string, uc_strlen, 10);   /* 将字符串转成10进制整形 */
}


OAL_STATIC OAL_INLINE oal_int8 *oal_strtok(oal_int8 *pc_token, OAL_CONST oal_int8 *pc_delemit, oal_int8 **ppc_context)
{
    return strtok_s(pc_token, pc_delemit, ppc_context);
}


OAL_STATIC OAL_INLINE oal_int  oal_strtol(OAL_CONST oal_int8 *pc_nptr, oal_int8 **ppc_endptr, oal_int32 l_base)
{
    return strtol(pc_nptr, ppc_endptr, l_base);
}


OAL_STATIC OAL_INLINE oal_void  oal_udelay(oal_uint u_loops)
{
}


OAL_STATIC OAL_INLINE oal_void  oal_mdelay(oal_uint u_loops)
{
}


OAL_STATIC OAL_INLINE oal_uint32  oal_kallsyms_lookup_name(OAL_CONST oal_uint8 *uc_var_name)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_void oal_dump_stack(oal_void)
{
    /* win32下, do nothing */
}


OAL_STATIC OAL_INLINE oal_void  oal_msleep(oal_uint32 ul_usecs)
{

}


OAL_STATIC OAL_INLINE errno_t oal_strcpy(oal_int8 *pc_dest, OAL_CONST oal_int8 *pc_src)
{
    return strcpy_s((oal_int8 *)pc_dest, strlen(pc_src), pc_src);
}

OAL_STATIC OAL_INLINE oal_void oal_random_ether_addr(oal_uint8 *addr)
{
   addr[0] = 0x22;
   addr[1] = 0x22;
   addr[2] = 0x21;
   addr[3] = 0x22;
   addr[4] = 0x23;
   addr[5] = 0x22;
}

OAL_STATIC OAL_INLINE oal_void oal_print_hex_dump(oal_uint8*addr, oal_int32 len, oal_int32 groupsize,oal_int8* pre_str)
{
    OAL_REFERENCE(groupsize);
    OAL_REFERENCE(addr);
    OAL_REFERENCE(len);
    OAL_REFERENCE(pre_str);
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_util.h */
