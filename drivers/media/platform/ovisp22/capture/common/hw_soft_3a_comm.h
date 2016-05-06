#ifndef __HW_SOFT_3A_COMM_H__
#define __HW_SOFT_3A_COMM_H__

#include <linux/io.h>
#include <linux/string.h>
#define _IS_DEBUG_3A	1

#define REG_ROI_MEM_WIDTH_3A						(0X63b48)
#define HW_3A_ENABLE								(0x6502f)
#define HW_3A_ROI_ENABLE_REG	     					(0x63010)
#define HW_3A_FRAME_CTRL_REG						(0x63b78)
#define HW_3A_BLC_ENABLE_REG						(0x67002) 

#define HW_3A_HIST_SHIFT_REG						(0x67003)

#define HW_3A_MEAN_SHIFT_REG						(0x67004)


//aec agc awb:hist&mean
#define HW_3A_WIN_TOP_REG_H						(0x67007)

#define HW_3A_WIN_TOP_REG_L						(0x67008)

#define HW_3A_WIN_LEFT_REG_H						(0x67009)

#define HW_3A_WIN_LEFT_REG_L						(0x6700a)

#define HW_3A_WIN_HEIGHT_REG					       (0x6700b)

#define HW_3A_WIN_WIDTH_REG						(0x6700c)

#define HW_3A_AECAGC_ENABLE						(0x67000)

#define HW_3A_AECAGC_MODEL						(0x67006)//aec agc &awb mode 0:16x16;1:8x8

#define HW_3A_RAM_ACCESS_ENABLE					(0x6302d)

#define HW_3A_STATS_POINTS_REG_H1				(0x67038)
#define HW_3A_STATS_POINTS_REG_H2				(0x67039)
#define HW_3A_STATS_POINTS_REG_L					(0x6703a)

#define HW_3A_AF_shift								(0x67005)

#define HW_3A_AF_ENABLE_REG						(0x67001)

#define HW_3A_AF_WIN_TOP_REG_H					(0x6700d)
#define HW_3A_AF_WIN_TOP_REG_L					(0x6700e)
#define HW_3A_AF_WIN_LEFT_REG_H					(0x6700f)
#define HW_3A_AF_WIN_LEFT_REG_L					(0x67010)
#define HW_3A_AF_WIN_HEIGHT_REG					(0x67011)
#define HW_3A_AF_WIN_WIDTH_REG					(0x67012)
#define HW_3A_AF_WIN_vPitch_REG_H				(0x67013)
#define HW_3A_AF_WIN_vPitch_REG_L					(0x67014)
#define HW_3A_AF_WIN_hPitch_REG_H				(0x67015)
#define HW_3A_AF_WIN_hPitch_REG_L					(0x67016)

#define HW_3A_AF_WIN_NUM_REG_H					(0x67019)

#define HW_3A_AF_FILTER0_REG					(0x6701a)
#define HW_3A_AF_FILTER1_REG					(0x6701b)
#define HW_3A_AF_FILTER2_REG					(0x6701c)
#define HW_3A_AF_FILTER3_REG					(0x6701d)
#define HW_3A_AF_FILTER4_REG					(0x6701e)
#define HW_3A_AF_FILTER10_REG					(0x6701f)
#define HW_3A_AF_FILTER11_REG					(0x67020)
#define HW_3A_AF_FILTER12_REG					(0x67021)
#define HW_3A_AF_FILTER13_REG					(0x67023)
#define HW_3A_AF_FILTER14_REG					(0x67023)
#define HW_3A_AF_FILTER20_REG					(0x67024)
#define HW_3A_AF_FILTER21_REG					(0x67025)
#define HW_3A_AF_FILTER22_REG					(0x67026)
#define HW_3A_AF_FILTER23_REG					(0x67027)
#define HW_3A_AF_FILTER24_REG					(0x67028)
#define HW_3A_AF_FILTER30_REG					(0x67029)
#define HW_3A_AF_FILTER31_REG					(0x6702a)
#define HW_3A_AF_FILTER32_REG					(0x6702b)
#define HW_3A_AF_FILTER33_REG					(0x6702c)
#define HW_3A_AF_FILTER34_REG					(0x6702d)
#define HW_3A_AF_FILTER40_REG					(0x6702e)
#define HW_3A_AF_FILTER41_REG					(0x6702f)
#define HW_3A_AF_FILTER42_REG					(0x67030)
#define HW_3A_AF_FILTER43_REG					(0x67031)
#define HW_3A_AF_FILTER44_REG					(0x67032)

#define HW_3A_AF_FILTER_SHIFT_REG			(0x67033)
#define HW_3A_AF_LOWPASS_FILTER_REG			(0x67034)
#define HW_3A_AF_CONTRAST_LIMIT_REG_H		(0x67035)
#define HW_3A_AF_CONTRAST_LIMIT_REG_L		(0x67036)
#define HW_3A_AF_PIXEL_OPTION_REG			(0x67037)
#define HW_3A_AF_STATS_POINTS_REG_H1		(0x6703b)
#define HW_3A_AF_STATS_POINTS_REG_H2		(0x6703c)
#define HW_3A_AF_STATS_POINTS_REG_L			(0x6703d)
#define HW_3A_EVEN_ODD_FRAME_REG			(0x6703e)

#define _IS_DEBUG_3A	1
#define SHIFT_BIT_7   (1<<7)
#define SHIFT_BIT_6   (1<<6)
#define SHIFT_BIT_5   (1<<5)
#define SHIFT_BIT_4   (1<<4)
#define SHIFT_BIT_3   (1<<3)
#define SHIFT_BIT_2   (1<<2)
#define SHIFT_BIT_1   (1<<1)
#define SHIFT_BIT_0   (1<<0)

typedef enum {
	HW_3A_OFF  = 0,
	HW_3A_ON,
} hw_3a_switch;

typedef enum{
	HW_3A_NOT_SUPPORT = 0,
	HW_3A_SUPPORT = 1,
}hw_3a_func;

typedef enum{
	AWB_OTP_NOT_SUPPORT = 0,
	AWB_OTP_SUPPORT = 1,
}awb_opt_func;

#endif /*__HW_SOFT_3A_H__ */
