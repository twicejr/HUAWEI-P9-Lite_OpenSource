#include "hisi_fb.h"
#include "hisi_cfg_sbl.h"

#ifdef CONFIG_SBL_BY_FILE

#define SBL_CFG_FILE "/data/local/apical_sbl.cfg"

static uint32_t bl_linearity_lut_cfg[33];
static uint32_t bl_att_lut_cfg[33];
static uint32_t bl_linearity_inverse_lut_cfg[33];
static uint32_t al_calib_lut_cfg[32];
static uint32_t asymmetry_lut_cfg[32];
static uint32_t color_correctton_lut_cfg[32];


static ST_SBL_REG sbl_reg[30] = {
	{"ASYMMETRY_LUT", ASYMMETRY_LUT},
	{"SBL_ENABLE",ENABLE},
	{"COLOR_CORRECTION_LUT",COLOR_CORRECTION_LUT},
	{"BLACK_LEVEL", BLACK_LEVEL},
	{"WHITE_LEVEL", WHITE_LEVEL},
	{"VARIANCE_INTENSITY_SPACE", VARIANCE_INTENSITY_SPACE},
	{"BRIGHT_DARK_AMP_LIMIT", BRIGHT_DARK_AMP_LIMIT},
	{"SLOPE_MAX", SLOPE_MAX},
	{"SLOPE_MIN", SLOPE_MIN},
	{"DITHER_MODE", DITHER_MODE},
	{"APICAL_DITHER", APICAL_DITHER},
	{"FRAME_WIDTH", FRAME_WIDTH},
	{"FRAME_HEIGHT", FRAME_HEIGHT},
	{"LOGO_TOP", LOGO_TOP},
	{"LOGO_LEFT", LOGO_LEFT},
	{"BL_linearity_LUT", BL_linearity_LUT},
	{"BL_linearity_inverse_LUT", BL_linearity_inverse_LUT},
	{"BL_att_LUT", BL_att_LUT},
	{"AL_CALIB_LUT", AL_CALIB_LUT},
	{"BACKLIGHT_MIN", BACKLIGHT_MIN},
	{"BACKLIGHT_MAX", BACKLIGHT_MAX},
	{"BACKLIGHT_SCALE", BACKLIGHT_SCALE},
	{"AMBIENT_LIGHT_MIN", AMBIENT_LIGHT_MIN},
	{"FILTER", FILTER},
	{"CALIBRATION_ABCD", CALIBRATION_ABCD},
	{"STRENGTH_LIMIT", STRENGTH_LIMIT},
	{"T_FILTER_CONTROL", T_FILTER_CONTROL},
	{"stabilization_iterations", STABILIZATION_ITERATION},
	{"power_saving_coeff", POWER_SAVING_COEFF},
	{"al_change_detect_coeff", AL_CHANGE_DETECT_COEFF},
};


static int isVaildReg(char* reg_from_cfg)
{
	int i = 0;
	int ret = 0;
	for( i = 0; i < 30; i++) {
		ret = strncmp(reg_from_cfg, sbl_reg[i].name, strlen(sbl_reg[i].name));
		if(!ret) {
			return sbl_reg[i].index;
		}
	}
	return -1;
}

static int find_start_code(char* buffer, int data_size, char code)
{
	int i = 0;
	char cur_code;
	for(i = 0; i < data_size; i++) {
		sscanf(buffer+i, "%c", &cur_code);
		if( cur_code == code )
			break;
	}
	if( i == data_size)
		return -1;

	return i;
}

static int get_reg_param(char* buffer, int file_size, char* reg_from_cfg, struct sbl_panel_info_cfg *sbl_para)
{
	int i = 0, fileSize = 0;
	int pos = 0;
	int ret = 0;
	char prefix[2];
	char line_buffer[512];

	ret = isVaildReg(reg_from_cfg);
	if( ret < 0)
		return -1;
	pos =  find_start_code(buffer, file_size, '<');
	if( pos < 0)
		return -1;
	buffer += pos;
	switch( ret )
	{
	case ASYMMETRY_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->asymmetry_lut));
		break;
	case ENABLE:
		sscanf(buffer, FORMAT_1, &sbl_para->sbl_enable);
		break;
	case COLOR_CORRECTION_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->color_correctton_lut));
		break;
	case BLACK_LEVEL:
		sscanf(buffer, FORMAT_1, &sbl_para->balck_level);
		break;
	case WHITE_LEVEL:
		sscanf(buffer, FORMAT_1, &sbl_para->white_level);
		break;
	case VARIANCE_INTENSITY_SPACE:
		sscanf(buffer, FORMAT_1, &sbl_para->variance_intensity_space);
		break;
	case BRIGHT_DARK_AMP_LIMIT:
		sscanf(buffer, FORMAT_1, &sbl_para->bright_dark_amp_limit);
		break;
	case SLOPE_MAX:
		sscanf(buffer, FORMAT_1, &sbl_para->slope_max);
		break;
	case SLOPE_MIN:
		sscanf(buffer, FORMAT_1, &sbl_para->slope_min);
		break;
	case DITHER_MODE:
		sscanf(buffer, FORMAT_1, &sbl_para->dither_mode);
		break;
	case APICAL_DITHER:
		sscanf(buffer, FORMAT_1, &sbl_para->apical_dither);
		break;
	case FRAME_WIDTH:
		sscanf(buffer, FORMAT_1, &sbl_para->frame_width);
		break;
	case FRAME_HEIGHT:
		sscanf(buffer, FORMAT_1, &sbl_para->frame_height);
		break;
	case LOGO_TOP:
		sscanf(buffer, FORMAT_1, &sbl_para->logo_top);
		break;
	case LOGO_LEFT:
		sscanf(buffer, FORMAT_1, &sbl_para->logo_left);
		break;
	case BL_linearity_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->BL_linearity_LUT));
		break;
	case BL_linearity_inverse_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->BL_linearity_inverse_LUT));
		break;
	case BL_att_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->BL_att_LUT));
		break;
	case AL_CALIB_LUT:
		sscanf(buffer, FORMAT_33, ARG_33(sbl_para->AL_CALIB_LUT));
		break;
	case BACKLIGHT_MIN:
		sscanf(buffer, FORMAT_1, &sbl_para->backlight_min);
		break;
	case BACKLIGHT_MAX:
		sscanf(buffer, FORMAT_1, &sbl_para->backlight_max);
		break;
	case BACKLIGHT_SCALE:
		sscanf(buffer, FORMAT_1, &sbl_para->backlight_scale);
		break;
	case AMBIENT_LIGHT_MIN:
		sscanf(buffer, FORMAT_1, &sbl_para->ambient_light_min);
		break;
	case FILTER:
		sscanf(buffer, FORMAT_2, &sbl_para->filter_a, &sbl_para->filter_b);
		break;
	case CALIBRATION_ABCD:
		sscanf(buffer, FORMAT_4, &sbl_para->calibration_a, &sbl_para->calibration_b, &sbl_para->calibration_c, &sbl_para->calibration_d);
		break;
	case STRENGTH_LIMIT:
		sscanf(buffer, FORMAT_1, &sbl_para->strength_limit);
		break;
	case T_FILTER_CONTROL:
		sscanf(buffer, FORMAT_1, &sbl_para->t_filter_control);
		break;
	case STABILIZATION_ITERATION:
		sscanf(buffer, FORMAT_1, &sbl_para->stabilization_iterations);
		break;
	case POWER_SAVING_COEFF:
		sscanf(buffer, FORMAT_1, &sbl_para->power_saving_coeff);
		break;
	case AL_CHANGE_DETECT_COEFF:
		sscanf(buffer, FORMAT_2, &sbl_para->al_change_detect_coeff_tolerance, &sbl_para->al_change_detect_coeff_offset);
		break;
	default:
		break;
	}
	return pos;
}

int sbl_parse_cfg(char* filename, struct sbl_panel_info_cfg *sbl_para)
{
	char* buffer = NULL;
	char* pbuff = NULL;
	struct file *fd = NULL;
	int file_size = 0;
	int len = 0;
	loff_t pos = 0;
	mm_segment_t old_fs;

	fd = filp_open(filename, O_CREAT|O_RDWR, 0644);
	if (IS_ERR(fd)) {
		HISI_FB_ERR("filp_open returned:filename %s, error %ld\n", filename, PTR_ERR(fd));
		return -1;
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);

	file_size = (int)(vfs_llseek(fd, 0L, SEEK_END));
	vfs_llseek(fd, 0L, SEEK_SET);

	buffer = kmalloc(file_size*2, GFP_KERNEL);
	pbuff = buffer;

	len = vfs_read(fd, pbuff, file_size, &pos);

	while(file_size > 0) {
		char line_tag[512] = {0};
		len = find_start_code(pbuff, file_size, '#');
		if( len < 0 )
			break;
		pbuff += len;
		file_size -= len;
		sscanf(pbuff, "%s", line_tag);
		len = strlen(line_tag);
		pbuff += len;
		file_size -= len;
		get_reg_param(pbuff, file_size, line_tag+1, sbl_para);
	}

	//show_reg_para(sbl_para);

	pos = 0;
	set_fs(old_fs);
	filp_close(fd, NULL);
	kfree(buffer);
	return 0;
}

static void show_reg_para(struct sbl_panel_info_cfg *pSbl_para)
{
	int i = 0;
	HISI_FB_INFO("asymmetry_lut: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ",pSbl_para->asymmetry_lut[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("sbl_enable : %d \n",pSbl_para->sbl_enable);

	HISI_FB_INFO("color_correctton_lut: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ",pSbl_para->color_correctton_lut[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("balck_level: %d \n", pSbl_para->balck_level);
	HISI_FB_INFO("white_level: %d \n", pSbl_para->white_level);
	HISI_FB_INFO("variance_intensity_space: %d \n", pSbl_para->variance_intensity_space);
	HISI_FB_INFO("bright_dark_amp_limit: %d \n", pSbl_para->bright_dark_amp_limit);
	HISI_FB_INFO("slope_max: %d \n", pSbl_para->slope_max);
	HISI_FB_INFO("slope_min: %d \n", pSbl_para->slope_min);
	HISI_FB_INFO("dither_mode: %d \n", pSbl_para->dither_mode);
	HISI_FB_INFO("apical_dither: %d \n", pSbl_para->apical_dither);
	HISI_FB_INFO("frame_width: %d \n", pSbl_para->frame_width);
	HISI_FB_INFO("frame_height: %d \n", pSbl_para->frame_height);
	HISI_FB_INFO("logo_left: %d \n", pSbl_para->logo_left);
	HISI_FB_INFO("logo_top: %d \n", pSbl_para->logo_top);

	HISI_FB_INFO("BL_linearity_LUT: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ", pSbl_para->BL_linearity_LUT[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("BL_linearity_inverse_LUT: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ", pSbl_para->BL_linearity_inverse_LUT[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("BL_att_LUT: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ", pSbl_para->BL_att_LUT[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("AL_CALIB_LUT: ");
	for(i = 0; i< 33; i++)
		HISI_FB_INFO("%d ", pSbl_para->AL_CALIB_LUT[i]);
	HISI_FB_INFO("\n");

	HISI_FB_INFO("backlight_min: %d \n", pSbl_para->backlight_min);
	HISI_FB_INFO("backlight_max: %d \n", pSbl_para->backlight_max);
	HISI_FB_INFO("backlight_scale: %d \n", pSbl_para->backlight_scale);
	HISI_FB_INFO("ambient_light_min: %d \n", pSbl_para->ambient_light_min);
	HISI_FB_INFO("filter_a: %d \n", pSbl_para->filter_a);
	HISI_FB_INFO("filter_b: %d \n", pSbl_para->filter_b);
	HISI_FB_INFO("calibration_a: %d \n", pSbl_para->calibration_a);
	HISI_FB_INFO("calibration_b: %d \n", pSbl_para->calibration_b);
	HISI_FB_INFO("calibration_c: %d \n", pSbl_para->calibration_c);
	HISI_FB_INFO("calibration_d: %d \n", pSbl_para->calibration_d);
	HISI_FB_INFO("strength_limit: %d \n", pSbl_para->strength_limit);
	HISI_FB_INFO("t_filter_control: %d \n", pSbl_para->t_filter_control);
	HISI_FB_INFO("stabilization_iterations: %d \n", pSbl_para->stabilization_iterations);
	HISI_FB_INFO("power_saving_coeff: %d \n", pSbl_para->power_saving_coeff);
	HISI_FB_INFO("al_change_detect_coeff_tolerance: %d \n", pSbl_para->al_change_detect_coeff_tolerance);
	HISI_FB_INFO("al_change_detect_coeff_offset: %d \n", pSbl_para->al_change_detect_coeff_offset);
}

void sbl_reg_write(char __iomem *sbl_base, uint32_t offset_l, uint32_t offset_h, uint32_t value)
{
	int tmp = value;
	if (offset_l) {
		outp32(sbl_base + offset_l, (tmp & 0xff));
	}

	if (offset_h) {
		outp32(sbl_base + offset_h, ((tmp >> 8) & 0xff));
	}
}

void init_sbl_by_cfg(struct hisi_panel_info *pinfo, char __iomem *sbl_base)
{
	int i = 0;
	pinfo->smart_bl_cfg.BL_linearity_LUT = bl_linearity_lut_cfg;
	pinfo->smart_bl_cfg.BL_linearity_inverse_LUT = bl_linearity_inverse_lut_cfg;
	pinfo->smart_bl_cfg.BL_att_LUT = bl_att_lut_cfg;
    	pinfo->smart_bl_cfg.AL_CALIB_LUT = al_calib_lut_cfg;
	pinfo->smart_bl_cfg.asymmetry_lut = asymmetry_lut_cfg;
	pinfo->smart_bl_cfg.color_correctton_lut = color_correctton_lut_cfg;
    
	if (!sbl_parse_cfg(SBL_CFG_FILE, &pinfo->smart_bl_cfg)) {
		HISI_FB_INFO("[sbl] sbl config file read succeed!\n");
		outp32(sbl_base + SBL_ENABLE, pinfo->smart_bl_cfg.sbl_enable);
		sbl_reg_write(sbl_base, SBL_BLACK_LEVEL_L, SBL_BLACK_LEVEL_H, pinfo->smart_bl_cfg.balck_level);
		sbl_reg_write(sbl_base, SBL_WHITE_LEVEL_L, SBL_WHITE_LEVEL_H, pinfo->smart_bl_cfg.white_level);
		outp32(sbl_base + SBL_VARIANCE_INTENSITY_SPACE, pinfo->smart_bl_cfg.variance_intensity_space);
		outp32(sbl_base + SBL_BRIGHT_DARK_AMP_LIMIT, pinfo->smart_bl_cfg.bright_dark_amp_limit);
		outp32(sbl_base + SBL_SLOPE_MAX, pinfo->smart_bl_cfg.slope_max);
		outp32(sbl_base + SBL_SLOPE_MIN, pinfo->smart_bl_cfg.slope_min);
		outp32(sbl_base + SBL_DITHER_MODE, pinfo->smart_bl_cfg.dither_mode);
		outp32(sbl_base + SBL_APICAL_DITHER, pinfo->smart_bl_cfg.apical_dither);
		sbl_reg_write(sbl_base, SBL_FRAME_WIDTH_L, SBL_FRAME_WIDTH_H, pinfo->smart_bl_cfg.frame_width);
		sbl_reg_write(sbl_base, SBL_FRAME_HEIGHT_L, SBL_FRAME_HEIGHT_H, pinfo->smart_bl_cfg.frame_height);
		outp32(sbl_base + SBL_LOGO_LEFT, pinfo->smart_bl_cfg.logo_left);
		outp32(sbl_base + SBL_LOGO_TOP, pinfo->smart_bl_cfg.logo_top);
		sbl_reg_write(sbl_base, SBL_BACKLIGHT_MIN_L, SBL_BACKLIGHT_MIN_H, pinfo->smart_bl_cfg.backlight_min);
		sbl_reg_write(sbl_base, SBL_BACKLIGHT_MAX_L, SBL_BACKLIGHT_MAX_H, pinfo->smart_bl_cfg.backlight_max);
		sbl_reg_write(sbl_base, SBL_BACKLIGHT_SCALE_L, SBL_BACKLIGHT_SCALE_H, pinfo->smart_bl_cfg.backlight_scale);
		sbl_reg_write(sbl_base, SBL_AMBIENT_LIGHT_MIN_L, SBL_AMBIENT_LIGHT_MIN_H, pinfo->smart_bl_cfg.ambient_light_min);
		sbl_reg_write(sbl_base, SBL_FILTER_A_L, SBL_FILTER_A_H, pinfo->smart_bl_cfg.filter_a);
		outp32(sbl_base + SBL_FILTER_B, pinfo->smart_bl_cfg.filter_b);
		sbl_reg_write(sbl_base, SBL_CALIBRATION_A_L, SBL_CALIBRATION_A_H, pinfo->smart_bl_cfg.calibration_a);
		sbl_reg_write(sbl_base, SBL_CALIBRATION_B_L, SBL_CALIBRATION_B_H, pinfo->smart_bl_cfg.calibration_b);
		sbl_reg_write(sbl_base, SBL_CALIBRATION_C_L, SBL_CALIBRATION_C_H, pinfo->smart_bl_cfg.calibration_c);
		sbl_reg_write(sbl_base, SBL_CALIBRATION_D_L, SBL_CALIBRATION_D_H, pinfo->smart_bl_cfg.calibration_d);
		outp32(sbl_base + SBL_STRENGTH_LIMIT, pinfo->smart_bl_cfg.strength_limit);
		outp32(sbl_base + SBL_T_FILTER_CONTROL, pinfo->smart_bl_cfg.t_filter_control);

		for(i = 0; i < 33; i++) {
			outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_ADDR, i);
			outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L, (pinfo->smart_bl_cfg.AL_CALIB_LUT[i] & 0xff));
			outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H, ((pinfo->smart_bl_cfg.AL_CALIB_LUT[i] >> 8) & 0xff));
		}

		pinfo->smart_bl.BL_linearity_LUT = pinfo->smart_bl_cfg.BL_linearity_LUT;
		pinfo->smart_bl.BL_linearity_inverse_LUT =  pinfo->smart_bl_cfg.BL_linearity_inverse_LUT;
		pinfo->smart_bl.BL_att_LUT = pinfo->smart_bl_cfg.BL_att_LUT;

		HISI_FB_INFO("[sbl] config sbl finished !\n");
	}

}
#endif


#ifdef NEW_SBL_CTRL
int apical_lut(int dat_w, int x, int *lut_nodes) {
	int lut_a = 5;
	int result1 = x >> (dat_w - lut_a);
	int node0 = lut_nodes[result1];
	int node1 = lut_nodes[result1+1];
	int sign, diff, y;
	int node_mul;
	int diff_mul;
	diff = node1 - node0;
	if (diff < 0)
		sign = 1;
	else
		sign = 0;
	node_mul =  x & 2047;// x & ((int)pow(2, (dat_w-lut_a)) -1);
	diff_mul = node_mul * diff;
	if(sign == 0)
		y= node0 + (diff_mul >> (dat_w - lut_a));
	else
		y = node0 - (diff_mul >> (dat_w - lut_a));

	return y;
}


int calculateAttenuatedBlendedBL(struct hisi_fb_data_type *hisifd,  int inpt_BL, int alpha, int num_bl_bits)
{
	int* BLlin33 = hisifd->panel_info.smart_bl.BL_linearity_LUT;
	int* BLatt33 = hisifd->panel_info.smart_bl.BL_att_LUT;
	int backlight_scaled = inpt_BL;

	int backlight_lin = apical_lut(16, backlight_scaled, BLlin33);
	int backlight_atten = apical_lut(16, backlight_lin, BLatt33);

	int bl_atten_minus_bl_lin = backlight_atten - backlight_lin;
	int mult_o = 0;
	int my_sign = 0;

	if (bl_atten_minus_bl_lin < 0) {
		mult_o = ((-bl_atten_minus_bl_lin) * alpha) >> 8;
		my_sign = -1;
	}
	else {
		mult_o = ((bl_atten_minus_bl_lin) * alpha) >> 8;
		my_sign = 1;
	}

	return (backlight_lin + my_sign * (mult_o));
}

#endif


