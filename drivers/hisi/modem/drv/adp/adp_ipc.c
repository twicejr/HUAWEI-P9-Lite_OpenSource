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

/*lint -save -e537*/
#include <mdrv_ipc.h>
#include <bsp_ipc.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <bsp_memmap.h>
/*lint -restore +e537*/

int mdrv_ipc_sem_create (unsigned int u32SignalNum)
{
	return bsp_ipc_sem_create(u32SignalNum);
}

int mdrv_ipc_sem_delete(unsigned int u32SignalNum)
{
	return bsp_ipc_sem_delete(u32SignalNum);
}

int mdrv_ipc_int_enable (IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_enable(ulLvl);
}

int mdrv_ipc_int_disable (IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_disable(ulLvl);
}

int mdrv_ipc_int_connect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter)
{
	return bsp_ipc_int_connect(ulLvl,(voidfuncptr)routine,parameter);
}

int mdrv_ipc_int_disconnect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter)
{
	return bsp_ipc_int_disconnect(ulLvl,(voidfuncptr)routine,parameter);
}

int mdrv_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_send(enDstCore, ulLvl);
}

int mdrv_ipc_sem_take (unsigned int u32SignalNum,int s32timeout)
{
	return bsp_ipc_sem_take(u32SignalNum,s32timeout);
}

int mdrv_ipc_sem_give(unsigned int u32SignalNum)
{
	(void)bsp_ipc_sem_give(u32SignalNum);
	return MDRV_OK;
}

void mdrv_ipc_spin_lock(unsigned int u32SignalNum)
{
	(void)bsp_ipc_spin_lock (u32SignalNum);
 	return;
}

int mdrv_ipc_spin_trylock(unsigned int u32SignalNum)
{
	return bsp_ipc_spin_trylock (u32SignalNum);
}

void mdrv_ipc_spin_unlock(unsigned int u32SignalNum)
{
	(void)bsp_ipc_spin_unlock (u32SignalNum);
	return;
}

