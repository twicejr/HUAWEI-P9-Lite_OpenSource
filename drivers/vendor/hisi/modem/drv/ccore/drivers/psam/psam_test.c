#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include "osal.h"
#include "osl_malloc.h"
#include "osl_bio.h"
#include <bsp_hardtimer.h>

#include <bsp_ipf.h>
#include <bsp_psam.h>

#include "psam_balong.h"
#include "mdrv_psam.h"

extern struct tagpsam_global_var psam_dl;

int BSP_PSAM_ST_001(void)
{
    int ret;
    int i;
    unsigned int reg_val;

    for (i = 0; i < IPF_MODEM_MAX; i++) {
        ret = mdrv_psam_set_crdq_ctrl(i);
        
        if (ret) {
            IPF_PRINT("mdrv_psam_set_crdq_ctrl return error!\n");
            return ERROR;
        } else if(!ret) {
            reg_val = readl(psam_dl.regbase + HI_PSAM_CRDQ_CTRL_OFFSET);

            if (reg_val != i) {
                IPF_PRINT("check register error!\n");
                return ERROR;
            } 
        }
    }
    
    return OK;       
}

#ifdef __cplusplus
}
#endif

