dtb-y += EVA_CL00_ET_V4_config.dtb
dtb-y += EVA_L09_V0_config.dtb
dtb-y += EVA_L09_V3_config.dtb
dtb-y += EVA_CL00_V4_config.dtb
dtb-y += EVA_L09_V1_config.dtb
dtb-y += EVA_TUGL_V0_config.dtb
dtb-y += EVA_TUCL_64G_ET_VN1_config.dtb
dtb-y += EVA_L09_VN2_config.dtb
dtb-y += EVA_TUCL_V0_config.dtb
dtb-y += EVA_TL00_VN1_config.dtb
dtb-y += EVA_L29_ET_NEW_V4_config.dtb
dtb-y += EVA_TUCL_32G_ET_VN2_config.dtb
dtb-y += EVA_TL00_NEW_V4_config.dtb
dtb-y += EVA_TUCL_32G_ET_V4_config.dtb
dtb-y += EVA_L09_VN1_config.dtb
dtb-y += EVA_TUCL_64G_ET_NEW_ISP_V4_config.dtb
dtb-y += EVA_TUCL_32G_ET_VN1_config.dtb
dtb-y += EVA_TUCL_64G_V4_config.dtb
dtb-y += EVA_L29_V4_config.dtb
dtb-y += EVA_L29_V3_config.dtb
dtb-y += EVA_TL00_NEW_ISP_V4_config.dtb
dtb-y += EVA_TL00_V4_config.dtb
dtb-y += EVA_L09_V4_config.dtb
dtb-y += EVA_TUCL_V3_config.dtb
dtb-y += EVA_TUGL_V1_config.dtb
dtb-y += EVA_TUCL_64G_ET_HIGHCPU_V4_config.dtb
dtb-y += EVA_TL00_VN2_config.dtb
dtb-y += EVA_TUCL_V1_config.dtb
dtb-y += EVA_L29_ET_V4_config.dtb
dtb-y += EVA_TUCL_32G_V4_config.dtb
dtb-y += EVA_TUCL_ET_V3_config.dtb
dtb-y += EVA_TUCL_32G_VN1_config.dtb
dtb-y += EVA_TUCL_64G_ET_VN2_config.dtb
dtb-y += EVA_CL00_V3_config.dtb
dtb-y += EVA_TUCL_64G_ET_NEW_V4_config.dtb
dtb-y += EVA_L09_VN2_NEW_config.dtb
dtb-y += EVA_TUCL_64G_VN1_config.dtb
dtb-y += EVA_TUCL_64G_ET_V4_config.dtb

targets += dtbs

dtbs: $(addprefix $(obj)/, $(dtb-y))
	$(Q)rm -f $(obj)/../*.dtb

clean-files := *.dtb
