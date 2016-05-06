/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_EX1.C
 *      Purpose: Your First RTX example program
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2013 ARM Germany GmbH
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
#include "product_config.h"
#include <ARMCM3.h>
#include <bsp_ipc.h>
#include "console.h"
#include "printk.h"
#include <bsp_icc.h>
#include "m3_pm.h"
#include "m3_cpufreq.h"
#include "om_balong.h"
#include <bsp_dsp.h>
#include <bsp_hkadc.h>
#include <bsp_nvim.h>
#include <bsp_softtimer.h>
#include <bsp_sysctrl.h>
#include <bsp_tsensor.h>
#include "temperature.h"
#include <wdt_balong.h>
#include "ccpu_start.h"
#include <om_balong.h>
#include <socp_balong.h>
#include <m3_dump.h>
#include <libfdt.h>
#include "bsp_ipf.h"
#include "bsp_psam.h"
#include <edma_balong.h>
#include <bsp_dump_mem.h>
#include <bsp_pmu.h>
#include <bsp_slice.h>
#include <bsp_uart.h>
#include <bsp_rsracc.h>
#include <amon_balong.h>
#include <ddr_sec_balong.h>

u32 sys_initial = 0;
void ios_init(void);
void bsp_clk_init(void);

/*----------------------------------------------------------------------------
 *   Main Thread
 *---------------------------------------------------------------------------*/
int main (void) {
	ddr_sec_int_init();
	dt_sysctrl_init();

	(void)bsp_slice_init();
	bsp_rsracc_init();
    bsp_dump_mem_init();

    m3_log_init();

	bsp_serial_init();
	console_init();

	bsp_ipc_init();
	
	bsp_ipf_init();
#ifdef CONFIG_PSAM
	bsp_psam_init();
#endif

	bsp_icc_init();
	(void)bsp_softtimer_init();
	/* must after ipc icc init */
	pm_init();
    edma_init();
	cpufreq_init();
    /* pm_dsp_pll_open: v711 hifi和dsp共pll，hifi上下电在m3实现，dsp上下电在ccore实现，
        必须保证在ccore启动以前该pll是可用的，
        所以要放在ccore启动之前，请不要修改位置 */
    pm_dsp_pll_open((u32)PM_PWR_VOTE_CCORE);
    ccpu_start_init();

    bsp_nvm_init();

    bsp_hifi_init();

    bsp_pmu_init(); /* 需要放在HKADC前面 */

    bsp_hkadc_init();

    bsp_tsensor_init();

#ifdef CONFIG_TEMPERATURE_PROTECT
    tem_protect_init();
#endif

	socp_m3_init();

	om_log_init();

    /*bsp_rfile_init();*/

	bsp_wdt_init();
	
	m3_dump_init();

    (void)axi_init();

	ios_init();
	bsp_clk_init();

	bsp_rsracc_init_late();
	sys_initial = 1;
	printk("\nsys: init ok\n");
	return 0;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
