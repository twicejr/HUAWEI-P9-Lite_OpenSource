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

#ifndef ___BSP_RSRACC_H__
#define ___BSP_RSRACC_H__
#include <product_config.h>
#include <osl_common.h>
#include <osl_list.h>
#include <bsp_om.h>

typedef enum{
	only_valid_save_flow=1,
	only_valid_resume_flow,
	both_save_and_resume_flow
}rsr_acc_valid_flow;

struct rsracc_cb_s;

typedef enum{
	rsracc_bd_level_0,
	rsracc_bd_level_1,
	rsracc_bd_level_2,
	rsracc_bd_level_3,
	rsracc_bd_level_4,
	rsracc_bd_level_5,
	rsracc_bd_level_6,
	rsracc_bd_level_7,
	rsracc_bd_level_8,
	rsracc_bd_level_9,
}rsracc_bd_level;

typedef struct bd_desc_s
{
	rsracc_bd_level level;
	const char *name;
	struct rsracc_cb_s 			  *ops;
	bool 				only_ops_in_bd;/*if this bd descriptor only have ops,this flag must be set 			*/
	u32* 					  reg_addr;/*the reg addr of need saved										*/
	u32						   reg_num;/*the number of saved reg										*/
	u32*					  bak_addr;/*the ddr where saved reg										*/
	bool	need_rsracc_assign_bakaddr;/*assign bakaddr by rsracc,in m3 must set false 					*/
	rsr_acc_valid_flow	 bd_valid_flow;/*the bd is valid in which flow (save\resume\SR)					*/
	bool			is_negation_resume;/*is this bd negate resume £»1:~[ddr]->reg;0:ddr->reg			*/
 	u32		   negation_resume_bitmask;/*which bit negate resume(0x3 indicate [1:0] 2bit negate resume)		*/
	bool					is_wait_bd;/*is this bd a wait bd											*/
	u32						wait_cycle;/*if is_wait_bd is set£tthis variable is the cycle of axi_glb bus			*/
	struct list_head entry;
}rsr_acc_description;
typedef struct rsracc_cb_debug_s
{
	u32 suspend_begin_slice[2];		/*0:slice of before suspend_begin ops,1:slice of after suspend_begin ops	*/
	u32 suspend_end_slice[2];		/*0:slice of before suspend_end ops,1:slice of after suspend_end ops 		*/
	u32 resume_begin_slice[2];		/*0:slice of before resume_begin ops,1:slice of after resume_begin ops	*/
	u32 resume_end_slice[2];		/*0:slice of before resume_end ops,1:slice of after resume ops			*/
	u32 suspend_begin_fail_times;	/*ops suspend_begin failed times									*/
	u32 suspend_begin_fail_slice;	/*ops suspend_begin failed latest slice								*/
}rsracc_cb_debug;

struct rsracc_cb_s
{
	s32 (*suspend_begin)(rsr_acc_description *bd_descri);
	void (*suspend_end)(rsr_acc_description *bd_descri);
	void (*resume_begin)(rsr_acc_description *bd_descri);
	void (*resume_end)(rsr_acc_description *bd_descri);
	rsracc_cb_debug debug;
};
#ifdef CONFIG_RSR_ACC
void bsp_rsracc_init(void);
void bsp_rsracc_init_late(void);
s32  bsp_rsracc_register(rsr_acc_description *bd_descri,u32 cnt);
s32  bsp_rsracc_unregister(rsr_acc_description *bd_descri,u32 cnt);
s32  bsp_rsracc_suspend_begin(void);
void  bsp_rsracc_suspend_halt(void);
void bsp_rsracc_suspend_end(void);
void bsp_rsracc_resume_begin(void);
void bsp_rsracc_resume_end(void);
bool bsp_rsracc_support(void);
void bsp_rsracc_set_checkflag(bool flag);

#else
static inline void bsp_rsracc_init(void){}
static inline void bsp_rsracc_init_late(void){}
static inline s32  bsp_rsracc_register(rsr_acc_description *bd_descri,u32 cnt){return BSP_OK;}
static inline s32  bsp_rsracc_unregister(rsr_acc_description *bd_descri,u32 cnt){return BSP_OK;}
static inline s32  bsp_rsracc_suspend_begin(void){return BSP_OK;}
static inline void bsp_rsracc_suspend_halt(void){}
static inline void bsp_rsracc_suspend_end(void){}
static inline void bsp_rsracc_resume_begin(void){}
static inline void bsp_rsracc_resume_end(void){}
static inline bool bsp_rsracc_support(void){return false;}
static inline void bsp_rsracc_set_checkflag(bool flag){}
#endif/*CONFIG_RSR_ACC*/
#endif/*___BSP_RSRACC_H__*/




