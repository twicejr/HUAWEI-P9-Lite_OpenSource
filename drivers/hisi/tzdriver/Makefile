ifneq ($(TARGET_BUILD_VARIANT),user)
EXTRA_CFLAGS += -DDEBUG_TUI
endif
obj-$(CONFIG_TZDRIVER) += tc_client_driver.o teek_client_api.o
obj-$(CONFIG_TZDRIVER) += smc.o agent.o gp_ops.o mem.o tee_rdr_register.o
obj-$(CONFIG_TEELOG) += tlogger.o
obj-$(CONFIG_HISI_MMC_SECURE_RPMB) += agent_rpmb.o
obj-$(CONFIG_TEE_TUI) += tui.o

EXTRA_CFLAGS += -Idrivers/video/hisi/dss \
				-Idrivers/atfdriver
