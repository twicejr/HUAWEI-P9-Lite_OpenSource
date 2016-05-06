/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  rfile.c
*
*   作    者 :  yuyangyang 00228784
*
*   描    述 :  rfile 解析主流程
*
*   修改记录 : 2014年12月27日  v1.00  y00228784  创建
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "pmom_cat.h"

int rfile_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{

    if(typeid != 0)
    {
        printf("rfile_msg_parse Error Type ,%d\n",typeid);
        return 1;
    }
    if((len > 256)||((*out_ptr+len)>PMOM_PARSE_STR_BUFSIZ))
    {
        printf("rfile_msg_parse Error Len ,%d,%d\n",len,*out_ptr);
        return 2;
    }
    memcpy(&out_buf[*out_ptr],in_buf,len);
    *out_ptr += len;
    return PMOM_OK;
}

