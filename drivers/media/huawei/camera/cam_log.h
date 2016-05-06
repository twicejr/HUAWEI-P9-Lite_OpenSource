
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

enum{
		CAM_DEBUG_EMERG     = 1<<7,
		CAM_DEBUG_ALERT     = 1<<6,
		CAM_DEBUG_CRIT      = 1<<5,
		CAM_DEBUG_ERR       = 1<<4,
		CAM_DEBUG_WARING    = 1<<3,
		CAM_DEBUG_NOTICE    = 1<<2,
		CAM_DEBUG_INFO      = 1<<1,
		CAM_DEBUG_DEBUG     = 1<<0,

		//...
};

extern uint32_t hwcam_debug_mask;

#define CAMERA_LOG_DEBUG
#ifdef CAMERA_LOG_DEBUG
#define cam_debug(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_DEBUG) \
				printk("[CAMERA]" "DEBUG: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_info(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_INFO) \
				printk("[CAMERA]" "INFO: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_notice(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_NOTICE) \
				printk("[CAMERA]" "NOTICE: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_warn(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_WARING) \
				printk("[CAMERA]" "WARN: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_err(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_ERR) \
				printk("[CAMERA]" "ERROR: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_crit(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_CRIT) \
				printk("[CAMERA]" "CRIT: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_alert(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_ALERT) \
				printk("[CAMERA]" "ALERT:" fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_emerg(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_EMERG) \
				printk("[CAMERA]" "EMERG: " fmt "\n", ##__VA_ARGS__); \
	}while (0)
#else
#define cam_debug(fmt, ...)

#define cam_info(fmt, ...) 

#define cam_notice(fmt, ...) 

#define cam_warn(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_WARING) \
				printk("[CAMERA]" "WARN: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_err(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_ERR) \
				printk("[CAMERA]" "ERROR: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_crit(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_CRIT) \
				printk("[CAMERA]" "CRIT: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_alert(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_ALERT) \
				printk("[CAMERA]" "ALERT: " fmt "\n", ##__VA_ARGS__); \
	}while (0)

#define cam_emerg(fmt, ...) \
	do { \
			if(hwcam_debug_mask & CAM_DEBUG_EMERG) \
				printk("[CAMERA]" "EMERG: " fmt "\n", ##__VA_ARGS__); \
	}while (0)
#endif

#endif /*LOG_H_INCLUDED */
/********************************* END ****************************************/
