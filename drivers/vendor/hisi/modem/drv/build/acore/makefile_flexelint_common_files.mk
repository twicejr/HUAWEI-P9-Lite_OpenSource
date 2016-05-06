
include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR       := $(BALONG_TOPDIR)/modem/drv
#*******************************************************************
#*******************************************************************
PCLINT_OPTION +=

#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/ \
	-I$(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/include_gu/ \
	-I$(BALONG_TOPDIR)/config/nvim/include/gu/ \
	-I$(BALONG_TOPDIR)/include/nv/comm/ \
	-I$(BALONG_TOPDIR)/include/nv/tl/oam/ \
	-I$(BALONG_TOPDIR)/include/nv/tl/lps/ \
	-I$(BALONG_TOPDIR)/include/phy/lphy/ \
	-I$(BALONG_TOPDIR)/include/nv/tl/drv \
	-I$(BALONG_TOPDIR)/include/drv \
	-I$(BALONG_TOPDIR)/include/med \
	-I$(BALONG_TOPDIR)/platform/$(CFG_PLATFORM) \
	-I$(BALONG_TOPDIR)/platform/$(CFG_PLATFORM)/soc \
	-I$(BALONG_TOPDIR)/modem/drv/common/include/ \
	-I$(CFG_ANDROID_DIR)/kernel/arch/arm/include/ \
	-I$(CFG_ANDROID_DIR)/kernel/include/ \
	-I$(OUT_KERNEL)/arch/arm/include/ \
	-I$(OUT_KERNEL)/include/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/common/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/oms/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/log/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/dump/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/sys_view/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/usbtrace/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/ipc/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/balong_timer/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/icc/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/bbp/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/version/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/onoff/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/nvim/

#*******************************************************************
#*******************************************************************
#/*******************************************bsp1 begin********************************************************/
#// rfile 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/rfile/rfile_balong.c
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/adp/adp_rfile.c
#/*MEM*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/mem/mem_balong.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/adp/adp_mem_balong.c*/
#OBC_LOCAL_PCLINT_SRC_FILE += \
#	$(BSP_DIR)/acore/kernel/drivers/modem/mem/mem_balong_test.c
#/*log*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/log/bsp_om_log.c
#/*om common*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/common/bsp_om_comm.c
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/om/common/bsp_om_save.c
#/*oms*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/oms/bsp_om_server.c
	
#/*nvim*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_base.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_comm.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_ctrl.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_xml_dec.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nvchar.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_test.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_nvim.c
	
#/*******************************************bsp1 end*******************************************/


#/*******************************************bsp3 begin*******************************************/
#// bsp3-lixiaojie begin
#//ipc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_ipc.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/ipc/ipc_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/ipc/ipc_balong_test.c
#//timer
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/softtimer_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/softtimer_balong_test.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_timer.c
#//sync
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/sync/sync_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/hwadp/hwadp_balong.c
#//int
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_int.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_gic_balong.c
#// bsp3-lixiaojie end
#// bsp3-yaoguocai begin
#// icc

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_icc.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/icc/icc_balong.c
#// hwadp_memory
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/hwadp/hwadp_memory.c
#// bsp3-yaoguocai end
#// bsp3-wangxiandong start
#//cshell
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/cshell/cshell.c
#// bsp3-wangxiandong end
#/*******************************************bsp3   end*******************************************/

#/*******************************************bsp2 begin*******************************************/
#//bsp2-liuwenhui begin
#// adp_mem_save 
#OBC_LOCAL_PCLINT_SRC_FILE += \
         #$(BSP_DIR)/acore/kernel/drivers/modem/om/mem_save/mem_save.c
#// antenna
#OBC_LOCAL_PCLINT_SRC_FILE += \
         #$(BSP_DIR)/acore/kernel/drivers/modem/antenna/anten_balong.c
#// efuse 
#OBC_LOCAL_PCLINT_SRC_FILE += \
         #$(BSP_DIR)/acore/kernel/drivers/modem/efuse/efuse_comm.c
#//bsp2-liuwenhui end

#//bsp2-lusuo begin
#//bsp2-lusuo end
#//bsp2-zuofenghua begin
#//bbp
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_bbp_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/bbp/bbp_balong.c
#//version
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_version.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/version/version_balong.c
#//bsp2-zuofenghua end
#//bsp2-zhangjingyuan begin
#//onoff
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/onoff/bsp_modem_boot.c
#//bsp2-zhangjingyuan end
#//bsp2-xuwenfang begin
#//bsp2-xuwenfang end

#//bsp2-haoran begin
#//bsp2-haoran end
#/*******************************************bsp2 end*******************************************/
