/*
 *  Hisilicon K3 soc camera v4l2 driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
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

#ifndef __K3_V4L2_CAPTURE_COMM_H__
#define __K3_V4L2_CAPTURE_COMM_H__

#include <linux/videodev2.h>
#include <linux/semaphore.h>

#define VIDIOC_CHECK_CAP  _IOWR('V', 200, struct v4l2_ext_controls)

struct v4l2_ext_control32 {
	__u32 id;
	__u32 size;
	__u32 reserved2[1];
	union {
		__s32 value;
		__s64 value64;
		compat_caddr_t string; /* actually char * */
	};
} __attribute__ ((packed));

struct v4l2_ext_controls32 {
       __u32 ctrl_class;
       __u32 count;
       __u32 error_idx;
       __u32 reserved[2];
       compat_caddr_t controls; /* actually struct v4l2_ext_control32 * */
};

#define VIDIOC_CHECK_CAP_32  _IOWR('V', 200, struct v4l2_ext_controls32)
/*
 * key and value pair struct
 * used for setting parameters
 */
enum {
	PKEY_IN_WIDTH = 1,	/* camera sensor input width */
	PKEY_IN_HEIGHT,		/* camera sensor input height */
	PKEY_IN_RESOLUTION,
	PKEY_START_X,		/* capture start x position */
	PKEY_START_Y,
	PKEY_START_POS,
	PKEY_OUT_WIDTH,
	PKEY_OUT_HEIGHT,
	PKEY_OUT_RESOLUTION,
	PKEY_OUT_FMT,
	PKEY_MIRROR,
	PKEY_BRIGHT,
	PKEY_CONTRAST,
	PKEY_FRAMERATE,
	PKEY_OUT_STRIDE,
};

#endif /*__K3_V4L2_CAPTURE_H__ */

/********************************* END ***********************************************/
