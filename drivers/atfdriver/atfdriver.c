
/*lint -e715 -esym(715,*) */
/*lint -e818 -esym(818,*) */
#include <asm/compiler.h>
#include "atfdriver.h"

noinline int atfd_hisi_service_efusec_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
}

/* the interface is used as access some secure registers from unsecure-Kernel layer.
 * main_fun_id--input parameter, fixed as ACCESS_REGISTER_FN_MAIN_ID,equal to 0xc500aa01
 * buff_addr_phy--input parameter for write, output para for read, the allocated buffer address in Kernel, must be physical address
 * data_len--the buffer size, unit is Bytes
 * sub_fun_id--the sub function id, started by 0x55bbcce0, the index increase one by one
*/
noinline int atfd_hisi_service_access_register_smc(u64 main_fun_id, u64 buff_addr_phy, u64 data_len, u64 sub_fun_id)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (main_fun_id)
        : "r" (buff_addr_phy), "r" (data_len), "r" (sub_fun_id));

    return (int)main_fun_id;
}

noinline int atfd_hisi_rpmb_smc(u64 function_id, u64 arg0, u64 arg1,  u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
}

noinline int atfd_hisee_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
}
/*lint +e715 +esym(715,*) */
/*lint +e818 +esym(818,*) */
