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

#ifndef __MEM_FUN_H
#define __MEM_FUN_H

#include  <basicfunc.h>
#include  <printk.h>

int sys_mem_init( UINT32  src_addr,    /*Memory Address*/
               int     num_byte,   /* Number of Data in Byte*/
               UINT32  init_data);

int sys_mem_init_v9r1( UINT32  src_addr,    /*Memory Address*/
               int     num_byte,   /* Number of Data in Byte*/
               UINT32  init_data,
               UINT32  inc_type);

int sys_mem_clr( UINT32  addr,         //Memory Address
              int     num_byte );    //Number of Data to clear in Byte

void sys_mem_copy( UINT32 src_addr,    // Memory Source Address
               UINT32 des_addr,    // Memory Destination Address
               int    num_byte);   // Number of Data in Byte

int sys_mem_comp( UINT32 addr1,     //Address 1
              UINT32 addr2,     //Address 2
              UINT32 num_byte );    //Number of data to Check in Byte

int sys_mem_test(  UINT32 src_addr,    // Memory Address
               long int     num_byte,   // Number of Data in Byte
               int test_num );



void MemClrNoLog ( UINT32 addr,       //Memory Address
				   int total_byte,    //Number of Data to clear in Byte
				   UINT32 logaddr, 
				   int logbit );                                       
                 

void MemCompNoLog ( UINT32 addr1,      //Address 1
					UINT32 addr2,      //Address 2
					UINT32 length,     //Number of data to Check in Byte 
					UINT32 logaddr,   
					int logbit );

int sys_mem_byte_cmp  (UINT32 src_addr,   //Address1
                   UINT32 dest_addr,  //Address2
                   UINT32 length);    //Number of data to Check in Byte

int sys_mem_cmp       (UINT32 src_addr,   //Address1
                   UINT32 dest_addr,  //Address2
				   UINT32 length);    //Number of data to Check in Word

int edmac_mem_comp( UINT32 src_addr,     
			  UINT32 des_addr,     
			  UINT32 num_byte,
			  UINT32 trans_type);

#endif /*__MEM_FUN_H*/
