#Copyright Huawei Technologies Co., Ltd. 1998-2011. All rights reserved.
#This file is Auto Generated 

dtb-y += hi6250/VENUS_TL00_VA_config.dtb
dtb-y += hi6250/VENUS_L31_VB_config.dtb
dtb-y += hi6250/VENUS_L21_VA_config.dtb
dtb-y += hi6250/VENUS_L21_VB_config.dtb
dtb-y += hi6250/VENUS_L22_VB_config.dtb
dtb-y += hi6250/VENUS_L31_VA_config.dtb
dtb-y += hi6250/VENUS_L23_VA_config.dtb
dtb-y += hi6250/VENUS_DL00_VA_config.dtb
dtb-y += hi6250/VENUS_L22_VA_config.dtb
dtb-y += hi6250/VENUS_L23_VC_config.dtb
dtb-y += hi6250/VENUS_L53_VB_config.dtb
dtb-y += hi6250/VENUS_L22_VC_config.dtb
dtb-y += hi6250/VENUS_L23_VB_config.dtb
dtb-y += hi6250/VENUS_L53_VA_config.dtb
dtb-y += hi6250/hi6250_udp_DSDS_config.dtb
dtb-y += hi6250/hi6250_udp_6555codec_config.dtb
dtb-y += hi6250/hi6250_udp_noRF_config.dtb
dtb-y += hi6250/hi6250_hi6250_fpga_config.dtb
dtb-y += hi6250/hi6250_udp_6555codec_noRF_config.dtb
dtb-y += hi6250/hi6250_emulator_config.dtb
dtb-y += hi6250/hi6250_udp_default_config.dtb
dtb-y += hi6250/NEMO_UL10_VA_config.dtb
dtb-y += hi6250/NEMO_TL00_VA_config.dtb
dtb-y += hi6250/NEMO_L21_VA_config.dtb
dtb-y += hi6250/NEMO_L21_VB_config.dtb
dtb-y += hi6250/NEMO_TL00H_VA_config.dtb
dtb-y += hi6250/NEMO_CL00_VB_config.dtb
dtb-y += hi6250/NEMO_L22_VB_config.dtb
dtb-y += hi6250/NEMO_AL10_VA_config.dtb
dtb-y += hi6250/NEMO_TL00H_VB_config.dtb
dtb-y += hi6250/NEMO_L23_VA_config.dtb
dtb-y += hi6250/NEMO_UL10_VB_config.dtb
dtb-y += hi6250/NEMO_TL00_VC_config.dtb
dtb-y += hi6250/NEMO_L22_VA_config.dtb
dtb-y += hi6250/NEMO_L22E_VA_config.dtb
dtb-y += hi6250/NEMO_UL10_VC_config.dtb
dtb-y += hi6250/NEMO_CL00_VA_config.dtb
dtb-y += hi6250/NEMO_L21E_VB_config.dtb
dtb-y += hi6250/NEMO_L22E_VB_config.dtb
dtb-y += hi6250/NEMO_L21E_VA_config.dtb
dtb-y += hi6250/NEMO_L23_VB_config.dtb
dtb-y += hi6250/NEMO_TL00_VB_config.dtb

targets += hi6250_dtb
targets += $(dtb-y)

# *.dtb used to be generated in the directory above. Clean out the
# old build results so people don't accidentally use them.
hi6250_dtb: $(addprefix $(obj)/, $(dtb-y))
	$(Q)rm -f $(obj)/../*.dtb

clean-files := *.dtb

#end of file
