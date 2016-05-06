/*
 * hisi_watchpoint.h - HW watchpoint file to watch kernel address
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#ifndef __HISI_WATCHPOINT_H
#define __HISI_WATCHPOINT_H


#ifdef CONFIG_DEBUG_FS
#define WP_DBG_SIZE_PAGE            (2048)
#endif

/*
*/
struct wp_strct {
	void *wp_addr;
	unsigned int wp_len;
	unsigned int wp_type;
	struct perf_event *__percpu *wp_hbp;
};

extern void die(const char *str, struct pt_regs *regs, int err);

#endif
