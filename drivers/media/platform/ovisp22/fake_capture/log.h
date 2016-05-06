
/*
 *  Hisilicon K3 soc camera ISP log debug switch header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *	Author : 
 *  Version:  1.2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED


#ifndef DEBUG_DEBUG
#define DEBUG_DEBUG 0
#endif

#ifndef DEBUG_INFO
#define DEBUG_INFO  1
#endif

#ifndef DEBUG_WARN
#define DEBUG_WARN  1
#endif

#ifndef DEBUG_ERROR
#define DEBUG_ERROR 1
#endif

#ifndef LOG_TAG
#define LOG_TAG ""
#endif

#if DEBUG_DEBUG
#define print_debug(fmt, ...) printk("[" LOG_TAG "]" "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
#define print_debug(fmt, ...)
#endif
#if DEBUG_INFO
#define print_info(fmt, ...) printk("[" LOG_TAG "]" "INFO: " fmt "\n", ##__VA_ARGS__)
#else
#define print_info(fmt, ...) 
#endif
#if DEBUG_WARN
#define print_warn(fmt, ...) printk("[" LOG_TAG "]" "WARN: " fmt "\n", ##__VA_ARGS__)
#else
#define print_warn(fmt, ...)
#endif
#if DEBUG_ERROR
#define print_error(fmt, ...) printk("[" LOG_TAG "]" "ERROR: " fmt "\n", ##__VA_ARGS__)
#else
#define print_error(fmt, ...)
#endif

#define assert(x)     						\
    do{               						\
        if(!(x))                         	\
        printk("!!!!!ASSERT ERROR!!!!");	\
    } while(0)

#endif /*LOG_H_INCLUDED*/
/********************************* END ***********************************************/
