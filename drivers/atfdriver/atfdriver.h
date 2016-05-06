

#ifndef ATFDRIVER_H_
#define ATFDRIVER_H_

#include <linux/init.h>
#define ACCESS_REGISTER_FN_MAIN_ID              (0xc500aa01)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_INTLV     (0x55bbcce0)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_FLUX_W    (0x55bbcce1)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_FLUX_R    (0x55bbcce2)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_DRAM_R    (0x55bbcce3)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_STDID_W   (0x55bbcce4)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_DSS       (0x55bbcce5)
#define ACCESS_REGISTER_FN_SUB_ID_DDR_PASR      (0x55bbcce6)

noinline int atfd_hisi_service_efusec_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2);
noinline int atfd_hisi_service_access_register_smc(u64 main_fun_id, u64 buff_addr_phy, u64 data_len, u64 sub_fun_id);
#endif /* ATFDRIVER_H_ */
