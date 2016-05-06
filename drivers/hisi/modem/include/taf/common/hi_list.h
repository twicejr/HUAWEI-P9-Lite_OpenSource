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

#ifndef _HI_LIST_H
#define _HI_LIST_H

struct msp_list_header {
    struct msp_list_header *next;
    struct msp_list_header *prev;
};


typedef struct msp_list_header HI_LIST_S;

#define HI_LIST_HEAD_INIT(name) { &(name), &(name) }


/* init a list head */
#define HI_INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)


/**
 * msp_list_entry - get the struct for this entry
 * @ptr:    the &struct msp_list_header pointer.
 * @type:    the type of the struct this is embedded in.
 * @member:    the name of the list_struct within the struct.
 */
#define msp_list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)16)->member)+16))

/**
 * msp_list_for_each    -    iterate over a list
 * @pos:    the &struct msp_list_header to use as a loop counter.
 * @head:    the head for your list.
 */
#define msp_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * msp_list_for_each_safe    -    iterate over a list safe against removal of list entry
 * @pos:    the &struct msp_list_header to use as a loop counter.
 * @n:        another &struct msp_list_header to use as temporary storage
 * @head:    the head for your list.
 */
#define msp_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
            pos = n, n = pos->next)

/**
 * msp_list_for_each_ex    -    iterate over a list
 * @pos:    the &struct msp_list_header to use as a loop counter.
 * @head:   the head for your list.
 * @begin:  the previous item of the begining item
 */
#define msp_list_for_each_ex(pos, head, begin) \
    for (pos = (begin)->next; pos != (head); pos = (pos)->next)

/**
 * msp_list_for_index    -    iterate over a list for index
 * @pos:    the &struct msp_list_header to use as a loop counter.
 * @head:    the head for your list.
 */
#define msp_list_for_index(pos, i, head, index) \
    for (pos = (head)->next, i=0; (pos != (head) && i < index); pos = pos->next,i++)

/*lint -esym(752,__list_add_msp)*/
extern void __list_add_msp(struct msp_list_header * newnew,
        struct msp_list_header * prev,
        struct msp_list_header * next);

/*lint -esym(752,msp_list_add_tail)*/
extern void msp_list_add_tail(struct msp_list_header *newnew, struct msp_list_header *head);

/*lint -esym(752,__list_del_msp)*/
extern void __list_del_msp(struct msp_list_header * prev,
        struct msp_list_header * next);

/*lint -esym(752,msp_list_del)*/
extern void msp_list_del(struct msp_list_header *entry);


#endif /* _MG_LIST_H */


