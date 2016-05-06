# Makefile for Discretix CC63P Linux device driver

MODULE_NAME = dx_cc63p

obj-$(CONFIG_CRYPTO_DEV_DX_CC63P) := $(MODULE_NAME).o
$(MODULE_NAME)-objs := dx_driver.o dx_sysfs.o dx_buffer_mgr.o dx_request_mgr.o dx_cipher.o dx_hash.o dx_aead.o dx_ivgen.o dx_sram_mgr.o dx_pm.o dx_pm_ext.o

EXTRA_CFLAGS += -DDX_CC_REE #-DCOMP_IN_WQ
EXTRA_CFLAGS += -DDX_ROM_VERSION=$(CONFIG_DX_ROM_VERSION)
ifneq ($(DX_CC_SRAM_SIZE),)
EXTRA_CFLAGS += -DDX_CC_SRAM_SIZE=$(CONFIG_DX_CC_SRAM_SIZE)
endif
ifeq ($(CONFIG_DX_DISABLE_COHERENT_DMA_OPS),y)
EXTRA_CFLAGS += -DDISABLE_COHERENT_DMA_OPS
endif
ifeq ($(CONFIG_DX_FPGA_ENV),y)
EXTRA_CFLAGS += -DDX_FPGA_ENV
endif

ifeq ($(CONFIG_DX_TEST_48BIT_DMA_ADDR),y)
EXTRA_CFLAGS += -DDX_DMA_48BIT_SIM
endif

ifeq ($(CONFIG_DX_DEBUG),y) # Remove optimization flags
EXTRA_CFLAGS += -DDX_DEBUG
define remove_o2
	CFLAGS_REMOVE_$(1) = -O2
endef
$(foreach obj,$(MODULE_NAME)-objs,$(eval $(call remove_o2,$(obj))))
EXTRA_CFLAGS += -DDEBUG -O1
endif

$(info $(if $(DEBUG),DEBUG=$(DEBUG)))

