#ifndef __VIDEO_HARDEN_H__
#define __VIDEO_HARDEN_H__

typedef enum {
	VIDEO_HARDEN_DEV_ID_VCODEC   = 0,
	VIDEO_HARDEN_DEV_ID_JPEG     = 1,
	VIDEO_HARDEN_DEV_ID_ISP      = 2
}video_harden_dev_id_enum;


typedef struct
{
    unsigned int vcodec_bit : 1;
    unsigned int jpeg_bit   : 1;
    unsigned int isp_bit    : 1;
    unsigned int reserve    : 29;
}video_harden_vote;


int video_harden_regulator_enable(video_harden_dev_id_enum dev_id);
int video_harden_regulator_disable(video_harden_dev_id_enum dev_id);
int video_harden_rstdis_isodis_clken(video_harden_dev_id_enum dev_id);
int video_harden_clkdis_isoen_rsten(video_harden_dev_id_enum dev_id);
int video_harden_regen_rstdis_isodis_clken_check(video_harden_dev_id_enum dev_id);
int video_harden_regdis_clkdis_isoen_rsten_check(video_harden_dev_id_enum dev_id);
int video_harden_video_noc_enable(video_harden_dev_id_enum dev_id);
int video_harden_video_noc_disable(video_harden_dev_id_enum dev_id);


#endif

