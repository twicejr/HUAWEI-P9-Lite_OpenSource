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

#include <bsp_pm_om.h>

#define PM_OM_TEST_DUMP_SIZE (u32)(0x4000)
#define PM_OM_TEST_LOG_SIZE  (u32)(64)


/* ¶ÔÓ¦mcoreµÄpm_om_platform_init */
void pmom_test_init(void)
{
}

void pmom_dump_test_func(u32 magic, u32 size)
{
	char *dump_addr;
	char name[5];

	(*(unsigned *)(name)) = magic;
	name[4]=0;

	dump_addr = bsp_pm_dump_get((u32)magic, size);
	if (NULL == dump_addr)
	{
		pmom_pr_err("no pm om mem\n");
	}
	else
	{
		pmom_pr_err("[%s]0x%p\n", name, dump_addr);
	}
}
void pmom_dump_test(void)
{
	pmom_dump_test_func(PM_OM_ABB, PM_OM_TEST_DUMP_SIZE);
	pmom_dump_test_func(PM_OM_BBP, PM_OM_TEST_DUMP_SIZE);
	pmom_dump_test_func(PM_OM_DSP, PM_OM_TEST_DUMP_SIZE);
	pmom_dump_test_func(PM_OM_PMU, PM_OM_TEST_DUMP_SIZE);
	//pmom_dump_test_func(PM_OM_ABB, PM_OM_TEST_DUMP_SIZE);
}

void pmom_dump_test2(void)
{
	pmom_dump_test_func(PM_OM_ABB, PM_OM_TEST_DUMP_SIZE);
}

void pmom_log_test_func(u32 magic)
{
	static u8 write = 0;
	static u8 log[PM_OM_TEST_LOG_SIZE];
	u32 i = 0;

	for (i = 0; i < PM_OM_TEST_LOG_SIZE; i++)
	{
		log[write&(PM_OM_TEST_LOG_SIZE-1)] = write;
		write++;
	}

	if (PM_OM_OK != bsp_pm_log_type(magic, 0, PM_OM_TEST_LOG_SIZE, (void *)&log))
	{
		pmom_pr_err("pm_log_type err\n");
	}
}

void pmom_log_test(void)
{
	static u32 i = 0;

	if (i == 0)
	{
		pmom_log_test_func(PM_OM_ABB);
		pmom_log_test_func(PM_OM_ACLK);
	}
	else if (i == 1)
	{
		pmom_log_test_func(PM_OM_AIPC);
		pmom_log_test_func(PM_OM_AIPF);
	}
	else if (i == 2)
	{
		pmom_log_test_func(PM_OM_BBP);
		pmom_log_test_func(PM_OM_CCLK);
	}
	else if (i == 3)
	{
		pmom_log_test_func(PM_OM_CIPC);
		pmom_log_test_func(PM_OM_CIPF);
	}
	else if (i == 4)
	{
		pmom_log_test_func(PM_OM_CPUF);
		pmom_log_test_func(PM_OM_DSP);
	}
	else if (i == 5)
	{
		pmom_log_test_func(PM_OM_DPM);
		pmom_log_test_func(PM_OM_PMA);
	}
	else if (i == 6)
	{
		pmom_log_test_func(PM_OM_PMC);
		pmom_log_test_func(PM_OM_PMM);
		i = 0;
	}
	i++;
}

