/*
 * hisi softtime driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author:lijiangxiong <lijingxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
typedef void (*softtimer_func)(unsigned long);

struct softtimer_list
{
   softtimer_func func;
   unsigned long para;
   unsigned int timeout;
   unsigned int timer_type;

   struct list_head entry;
   unsigned int count_num;
   unsigned int is_running;
   unsigned int init_flags;
};

extern void hisi_softtimer_add(struct softtimer_list * timer);
extern int hisi_softtimer_delete(struct softtimer_list * timer);
extern int hisi_softtimer_create(struct softtimer_list *timer,softtimer_func func,
       unsigned long para, unsigned int timeout);
extern int hisi_softtimer_modify(struct softtimer_list *timer,unsigned int new_expire_time);



