
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

