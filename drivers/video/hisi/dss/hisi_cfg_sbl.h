#ifndef __HISI_CFG_SBL_H__
#define __HISI_CFG_SBL_H__

#define NEW_SBL_CTRL
//#define CONFIG_SBL_BY_FILE

#ifdef CONFIG_SBL_BY_FILE

#define FORMAT_1 "<%d>"
#define FORMAT_2 "<%d %d>"
#define FORMAT_4 "<%d %d %d %d>"
#define FORMAT_33 "<%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d>"
#define ARG_33(d) &d[0],&d[1],&d[2],&d[3],&d[4],&d[5],&d[6],&d[7],&d[8],&d[9],&d[10],&d[11],&d[12],&d[13],&d[14],&d[15],&d[16],&d[17],&d[18],&d[19], \
	              &d[20],&d[21],&d[22],&d[23],&d[24],&d[25],&d[26],&d[27],&d[28],&d[29],&d[30],&d[31],&d[32]

enum SBL_REG_INDEX {
	ASYMMETRY_LUT,
	ENABLE,
	COLOR_CORRECTION_LUT,
	BLACK_LEVEL,
	WHITE_LEVEL,
	VARIANCE_INTENSITY_SPACE,
	BRIGHT_DARK_AMP_LIMIT,
	SLOPE_MAX,
	SLOPE_MIN,
	DITHER_MODE,
	APICAL_DITHER,
	FRAME_WIDTH,
	FRAME_HEIGHT,
	LOGO_TOP,
	LOGO_LEFT,
	BL_linearity_LUT,
	BL_linearity_inverse_LUT,
	BL_att_LUT,
	AL_CALIB_LUT,
	BACKLIGHT_MIN,
	BACKLIGHT_MAX,
	BACKLIGHT_SCALE,
	AMBIENT_LIGHT_MIN,
	FILTER,
	CALIBRATION_ABCD,
	STRENGTH_LIMIT,
	T_FILTER_CONTROL,
	STABILIZATION_ITERATION,
	POWER_SAVING_COEFF,
	AL_CHANGE_DETECT_COEFF,
};

typedef struct _sbl_reg {
	char* name;
	int index;
} ST_SBL_REG;

#endif


#endif
