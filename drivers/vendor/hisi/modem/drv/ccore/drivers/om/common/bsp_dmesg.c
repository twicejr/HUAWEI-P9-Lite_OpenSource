/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dump_print.c
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言的打印功能
*
*   修改记录 :  2013年1月10日  v1.00  z67193  创建
*************************************************************************/
/*lint -save -e537 -e830 -e525 -e64*/
#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <semLib.h>
#include <taskLib.h>
#include <stdio.h>
#endif
#ifdef __OS_RTOSCK__
#include <osl_sem.h>
#include <osl_thread.h>
#include <sre_libc.h>
#include <sre_shell.h>
#include <sre_io_intf.h>
#endif
#include "securec.h" 

#include <string.h>
#include "osl_common.h"
#include "osl_irq.h"
#include "mdrv.h"
#include "bsp_dump_drv.h"
#include "bsp_memmap.h"
#include "bsp_om.h"
#include "bsp_ipc.h"
#include <bsp_modem_log.h>
/*lint -restore*/

typedef void (* funcvoid)(void);


#ifdef __OS_VXWORKS__
void dmesg_cshell_hook(void);
#endif
int  dmesg_get_char(char *out_char);
int dmesg_charter_send_hook(char* charter);


#define __LOG_BUF_LEN	        (DUMP_DMESG_SIZE)
#define DUMP_PRINT_MAGIC        (0x32325445)
#define LOG_BUF_MASK            (__LOG_BUF_LEN -1)
#define LOG_BUF(idx)            (g_dmesg_buff->log_buf[(idx) & LOG_BUF_MASK])

typedef struct
{
	struct log_mem log_info; /* log info to communicate with modem log */
    u32     logged_chars;   /* number of chars in log buffer */
    u32     w_mark;         /* water mark, if logged chars exceed w_mark, send IPC to acore */
    u32     reserved;       /* reserved for 32-byte align */
    s8 *    log_buf;        /* data area */
}log_mem_stru;

typedef struct
{
    s8 *    buffer1;
    s8 *    buffer2;
    u32     size1;
    u32     size2;
    u32     poff1;
    u32     poff2;
}dmesg_print;

log_mem_stru *  g_dmesg_buff = NULL;
BSP_BOOL        dmesg_enable = BSP_FALSE;
dmesg_print     g_dmesg_print;
extern u32  g_dump_product_type;


char * dmesg_buf = NULL;

void dmesg_clear_pbuff(int ix)
{
    if(1 == ix)
    {
        g_dmesg_print.buffer1 = NULL;
        g_dmesg_print.size1 = 0;
        g_dmesg_print.poff1 = 0;
    }
    else if(2 == ix)
    {
        g_dmesg_print.buffer2 = NULL;
        g_dmesg_print.size2 = 0;
        g_dmesg_print.poff2 = 0;
    }
}
/*lint -save -e830 -e525*/
static void emit_log_char(char c)
{
	LOG_BUF(g_dmesg_buff->log_info.write) = c;
	g_dmesg_buff->log_info.write++;

	if (g_dmesg_buff->log_info.write >= g_dmesg_buff->log_info.size)
	{
    	//LOG_BUF(g_dmesg_buff->log_end -1) = 0;
		g_dmesg_buff->log_info.write = 0;
    }
	if (g_dmesg_buff->logged_chars < g_dmesg_buff->log_info.size)
		g_dmesg_buff->logged_chars++;
}
/*lint -restore*/
void dmesg_notify_acore(void)
{
	/* struct log_mem info is enough for bsp_modem_log_fwrite_trigger in ccore  */
	struct log_usr_info usr_info;

    if(g_dump_product_type == DUMP_MBB && g_dmesg_buff)
    {
		usr_info.wake_interval = 0;
		usr_info.mem = &g_dmesg_buff->log_info;
		bsp_modem_log_fwrite_trigger(&usr_info);
    }
}

static inline u32 dmesg_writen_size_get(u32 write, u32 read, u32 ring_buffer_size)
{
	return (write >= read)? (write - read): (ring_buffer_size - read + write);
}

static inline u32 dmesg_writable_size_get(u32 write, u32 read, u32 ring_buffer_size)
{
	return (read > write)? (read - write): (ring_buffer_size - write + read);
}

/*lint -save -e18*/
int dmesg_write(const char* buffer, const unsigned len)
{
	char* buff  = (char*)buffer;
    u32 read_p;
    u32 write_p;
	u32 writen_size;
	u32 writable_size;

    if(dmesg_enable != BSP_TRUE)
    {
        return 0;
    }

    read_p  = g_dmesg_buff->log_info.read;
    write_p = g_dmesg_buff->log_info.write;

	writable_size = dmesg_writable_size_get(write_p, read_p, g_dmesg_buff->log_info.size);
	writen_size   = dmesg_writen_size_get(write_p, read_p, g_dmesg_buff->log_info.size);
	if (len <=  writable_size && (writen_size + len > g_dmesg_buff->w_mark))
    {/* enough space left to write &&  writen size > threshhold */
        dmesg_notify_acore();
    }
    /*lint -save -e539*/

	while(buff < buffer + len)
	{
		(void)emit_log_char(*buff);
		buff++;
	}
    /*lint -restore +e539*/
	return buff - buffer;
}
/*lint -restore +e18*/

__inline__ void dmesg_start()
{
	dmesg_enable = BSP_TRUE;
    return;
}

__inline__ void dmesg_stop()
{
	dmesg_enable = BSP_FALSE;
    return;
}

/*lint -save -e64*/
void dmesg_init(void)
{
    dmesg_buf = (char *)(DUMP_DMESG_ADDR);

    (void)memset_s(dmesg_buf, DUMP_DMESG_SIZE,0, DUMP_DMESG_SIZE);

	g_dmesg_buff = (log_mem_stru *)dmesg_buf;
	g_dmesg_buff->log_info.magic = DUMP_PRINT_MAGIC;
	g_dmesg_buff->log_info.read  = 0;
	g_dmesg_buff->log_info.write = 0;
	g_dmesg_buff->logged_chars   = 0;
	g_dmesg_buff->log_info.size  = __LOG_BUF_LEN - sizeof(log_mem_stru);
	g_dmesg_buff->log_info.app_is_active= 0;
        
    /* coverity[suspicious_pointer_arithmetic] */
	g_dmesg_buff->log_buf = (s8 *)((s8*)g_dmesg_buff + sizeof(log_mem_stru));
    g_dmesg_buff->w_mark = g_dmesg_buff->log_info.size - (g_dmesg_buff->log_info.size)/4;

    dmesg_clear_pbuff(1);
    dmesg_clear_pbuff(2);
#ifdef __OS_VXWORKS__
    balongv7r2_uart_register_hook(dmesg_get_char);
#else
    /*注册输出字符钩子函数*/
    //SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)dmesg_hshell_hook);
    uart_register_hook(dmesg_charter_send_hook);


#endif
	dmesg_start();
}
/*lint -restore*/


int dmesg_save(const char* buffer, const unsigned length)
{
    u32 end = 0;
    u32 len = 0, chars = 0;
    s8 *s1, *s2;
    u32 l1, l2;

	end = g_dmesg_buff->log_info.write;
	chars = g_dmesg_buff->logged_chars;
    len = g_dmesg_buff->log_info.size;
    /*lint -save -e830 -e525 -e64*/
	if (chars >= len) {
		s1 = (s8*)(g_dmesg_buff->log_buf + end);
		l1 = len - end;

		s2 = (s8*)g_dmesg_buff->log_buf;
		l2 = end; /* [false alarm]:屏蔽Fority错误 */
	}
    else {
		s1 = NULL;
		l1 = 0;

		s2 = (s8*)g_dmesg_buff->log_buf;
		l2 = chars; /* [false alarm]:屏蔽Fority错误 */
	}
    /*lint -restore +e830 +e525 +e64*/

    if((s1 != NULL) && (l1 != 0))
    {
        (void)memcpy_s((void *)buffer, (u32)l1,(void *)s1, (u32)l1);
    }
    (void)memcpy_s((void *)(buffer+l1), (u32)l2,(void *)s2, (u32)l2);

    return 0;
}

void dmesg(void)
{
    u32 end, chars, len;
    unsigned long lock_key;

    local_irq_save(lock_key);

    if(g_dmesg_buff)
    {
    	end = g_dmesg_buff->log_info.write;
    	chars = g_dmesg_buff->logged_chars;
        len = g_dmesg_buff->log_info.size;
        /*lint -save -e64*/
    	if (chars >= len) {
            g_dmesg_print.poff1 = 0;
    		g_dmesg_print.buffer1 = (s8*)(g_dmesg_buff->log_buf + end);
    		g_dmesg_print.size1 = (u32)(len - end);
            g_dmesg_print.poff2 = 0;
    		g_dmesg_print.buffer2 = (g_dmesg_buff->log_buf);
    		g_dmesg_print.size2 = (u32)end;
    	}
        else if(chars > 0)
        {
            dmesg_clear_pbuff(1);
            g_dmesg_print.poff2 = 0;
    		g_dmesg_print.buffer2 = g_dmesg_buff->log_buf;
    		g_dmesg_print.size2 = (u32)chars;
    	}
        else
        {
            dmesg_clear_pbuff(1);
            dmesg_clear_pbuff(2);
        }
        /*lint -restore +e64*/
    }
    else
    {
        dmesg_clear_pbuff(1);
        dmesg_clear_pbuff(2);
    }

    local_irq_restore(lock_key);

    return;
}

int dmesg_get_char(char *out_char)
{
    if(g_dmesg_print.buffer1 && g_dmesg_print.size1)
    {
        if(g_dmesg_print.poff1 < g_dmesg_print.size1)
        {
            *out_char = (char)(g_dmesg_print.buffer1[g_dmesg_print.poff1++]);
            return BSP_OK;
        }
        else
        {
            dmesg_clear_pbuff(1);
        }
    }

    if(g_dmesg_print.buffer2 && g_dmesg_print.size2)
    {
        if(g_dmesg_print.poff2 < g_dmesg_print.size2)
        {
            *out_char = (char)(g_dmesg_print.buffer2[g_dmesg_print.poff2++]);
            return BSP_OK;
        }
        else
        {
            dmesg_clear_pbuff(2);
        }
    }

    return BSP_ERROR;
}
#ifdef __OS_VXWORKS__
void dmesg_cshell_hook(void)
{
    if(g_dmesg_print.buffer1 && g_dmesg_print.size1)
    {
        dmesg_clear_pbuff(1);
    }

    if(g_dmesg_print.buffer2 && g_dmesg_print.size2)
    {
        dmesg_clear_pbuff(2);
    }
}

#else
int dmesg_charter_send_hook(char* charter)
{

    emit_log_char((char)(*charter));
 
   return MDRV_OK;
}

#endif


