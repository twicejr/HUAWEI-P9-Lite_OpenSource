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

#include <linux/video/lcd_balong_busstress.h>
#include <linux/video/lcdfb_balong.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <bsp_busstress.h>
#include <osl_thread.h>
#include <bsp_softtimer.h>
#include <sys_bus_core.h>
#include <sys_bus_single.h>
#include <sys_bus_pressure.h>

#ifndef LCD_ERROR
#define LCD_ERROR (-1)
#endif

#ifndef LCD_OK
#define LCD_OK (0)
#endif

#ifndef TEST_STOP
#define TEST_STOP (0)
#endif

#ifndef TEST_RUN
#define TEST_RUN (1)
#endif


#define LCD_SEM_FULL (1)
#define LCD_SEM_EMPTY (0)

#ifdef CONFIG_FB_2_4_INCH_BALONG
#define LEN 153600
const char *gImage = hehua;
#elif defined CONFIG_FB_1_4_5_INCH_BALONG
#define LEN 32768
const char *gImage = sprint;
#endif
#ifndef CFG_CONFIG_MODULE_BUSSTRESS
s32 lcd_stress_test_stat = 0;
#endif
u32 lcd_test_interval = 0;
struct fb_info info;

u32 counter;    /* 计数器，压力测试程序正常运行的时候，counter会自加，表示程序正在run */

extern int get_test_switch_stat(int module_id);
extern struct fb_info g_fbinfo_get(void);
extern s32 lcd_refresh(struct fb_info * info);

void set_lcd_test_stat(int run_or_stop)
{
    #ifdef CFG_CONFIG_MODULE_BUSSTRESS
    set_test_switch_stat(LCD,run_or_stop);
    #else
	lcd_stress_test_stat = run_or_stop;
    #endif

}
int get_lcd_test_stat(void)
{
    #ifdef CFG_CONFIG_MODULE_BUSSTRESS
    printk("%d\n", counter);
    return get_test_switch_stat(LCD);
    #else
    return lcd_stress_test_stat;
    #endif
}
void drawRect (char * des, const char *src, u32 len)
{
    memcpy(des,src,len);
}

int lcd_stress_test_routine(void* data)
{
    info = g_fbinfo_get();

    while(get_lcd_test_stat()){

        msleep(lcd_test_interval);

        drawRect (info.screen_base , gImage,LEN);
        lcd_refresh(&(info));
        msleep(lcd_test_interval);
        drawRect (info.screen_base , gImage_red,LEN);
        lcd_refresh(&(info));
        msleep(lcd_test_interval);
        drawRect (info.screen_base , gImage_green,LEN);
        lcd_refresh(&(info));
        counter++;
    }
    return 0;
}


void sys_lcd_start(struct master* master)//(s32 task_priority,s32 dtime)
{
    set_lcd_test_stat(TEST_RUN);
    //lcd_test_interval = interval;
    counter = 0;
    kthread_run(lcd_stress_test_routine,0,"LcdStressTask");

    return;
}

void sys_lcd_stop(struct master* master)
{
    set_lcd_test_stat(TEST_STOP);

    msleep(2000);
	return;
}

 void lcd_refresh_test(void)
{
    info = g_fbinfo_get();
    memcpy(info.screen_base,gImage,LEN);
    lcd_refresh(&info);
}
 
 void sys_lcd_init(struct master* master)
 {
     master->start = sys_lcd_start;
     master->stop = sys_lcd_stop;
 
     master->init_flag = 1;
     sys_bus_trace("lcd bus stress init ok\n");
 }

 




