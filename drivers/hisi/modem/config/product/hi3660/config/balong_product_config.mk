 mkfilepath := $(abspath $(lastword $(MAKEFILE_LIST)))
 current_dir :=$(dir $(mkfilepath))

 include $(current_dir)/balong_product_config_legacy.mk
 include $(current_dir)/balong_product_config_drv.mk
 include $(current_dir)/balong_product_config_pam.mk
 include $(current_dir)/balong_product_config_gucas.mk
 include $(current_dir)/balong_product_config_gucnas.mk
 include $(current_dir)/balong_product_config_gucphy.mk
 include $(current_dir)/balong_product_config_tlps.mk
 include $(current_dir)/balong_product_config_tlphy.mk
 include $(current_dir)/balong_product_config_audio.mk
 include $(current_dir)/balong_product_config_tool.mk




