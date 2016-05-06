/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <product_config.h>


#ifndef CONFIG_CPU_BALONG_FREQ

#include <bsp_cpufreq.h>
#include <drv_comm.h>


#ifdef __cplusplus
extern "C"
{
#endif

int g_cpufreq_max_profile = 5;
struct cpufreq_msg debug_msg = {0,0,0,0};
/*提供pm流程调用，设置最大频率CPU/DDR*/
void cpufreq_set_max_freq(void)
{

}
/*
 * 获取当前profile
 */
int cpufreq_dfs_get_profile(void)
{
	return 0;
}
/*
 * 设置profile
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_profile(int profile)
{
	return BSP_OK;
}

/*
 * 设置profile下限
 * success: return BSP_OK	
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_baseprofile(int baseprofile)
{
	return BSP_OK;
}

/*
 * 锁定调频 lock=0锁定;lock=1解锁
 */
void cpufreq_dfs_lock(u32 lock)
{
	
}

/*
 * 调试接口，设置频率 BSP_ERROR 设置失败;BSP_OK 设置成功
 *
 */
int cpufreq_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return BSP_OK;
}

int cpufreq_dfs_current(int *a9freq, int *ddrfreq, int *slowfreq)
{
	return BSP_OK;
}

void cpufreq_update_frequency(void)
{
	
}
unsigned int cpufreq_calccpu_load_netif(void)
{
	return BSP_OK;
}
/********************************new interface start ***********************************/

int mdrv_pm_get_dfs_profile(void)
{
	return cpufreq_dfs_get_profile();
}

int mdrv_pm_set_dfs_profile(int profile)
{
	return cpufreq_dfs_set_profile(profile);
}

int mdrv_pm_set_dfs_baseprofile(int profile)
{
	return cpufreq_dfs_set_baseprofile(profile);
}

void mdrv_pm_lock_dfs(unsigned int lock)
{
	cpufreq_dfs_lock(lock);
}

int mdrv_pm_set_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return	cpufreq_dfs_target(a9freq, ddrfreq, slowfreq);
}
/********************************new interface end ***********************************/
#ifdef __cplusplus
}
#endif
#endif
