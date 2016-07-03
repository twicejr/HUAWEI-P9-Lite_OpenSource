dtb-y += hi6250_udp_DSDS_config.dtb
dtb-y += hi6250_udp_6555codec_config.dtb
dtb-y += hi6250_udp_noRF_config.dtb
dtb-y += hi6250_hi6250_fpga_config.dtb
dtb-y += hi6250_udp_6555codec_noRF_config.dtb
dtb-y += hi6250_emulator_config.dtb
dtb-y += hi6250_udp_default_config.dtb

targets += dtbs

dtbs: $(addprefix $(obj)/, $(dtb-y))
	$(Q)rm -f $(obj)/../*.dtb

clean-files := *.dtb
