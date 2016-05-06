#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=cas_ccore

#***********************************************************#
#thumb compile switch:必须放在COMM FLAGS之前
#***********************************************************#

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm_flags.mk

#USER FLAGS AND DEFINES
CC_USER_FLAGS   ?=
AS_USER_FLAGS   ?=



ifeq ($(CFG_THUMB_COMPILE),YES)



CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls

endif


CC_USER_FLAGS += -march=armv6


#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=
CC_USER_DEFINES +=-DWAS_BBIT_SWITCH


#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm.inc

#cas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include \
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
    $(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
        $(BALONG_TOPDIR)/modem/include/taf/ccore \
        $(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/nv/gu/cas \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/comm/scm \
	$(BALONG_TOPDIR)/modem/include/oam/gu/si \
	$(BALONG_TOPDIR)/modem/include/oam/comm/socp \
	$(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
	$(BALONG_TOPDIR)/modem/include/oam/comm/errno \
	$(BALONG_TOPDIR)/modem/include/oam/comm/dms \
	$(BALONG_TOPDIR)/modem/include/oam/comm/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/gu/log \
	$(BALONG_TOPDIR)/modem/include/oam/gu/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/nvim \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/phy/cphy \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_cm \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_sm \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd_cm \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd_sm \
	$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM_HISI_BALONG)

OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK\Inc \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/gu/zlib\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/gu/zlib\Src \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087 \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma/1x \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/tx \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/rx \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/mac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/rlp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/mac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/rlp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sig \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sps \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/comm/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/fsm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/cch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/init \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/main \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/nasitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/ohm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/phyitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/srch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/ttfitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/meas \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/util \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/tch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/smc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/srd \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/usimitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/hrpditf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/fsm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/nasitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ohm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/smc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srd \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/util \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/usimitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/conn \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/idle \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/almp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/conn \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/idle \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/init \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/main \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/nasitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/ohm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/phyitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/rrm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/rup \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/scp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/ttfitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/lteitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/util \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/init \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/nasitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ohm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/phyitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rrm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ttfitf \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/util

#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/usimitf/Cas1xUsimitfCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/comm/Cas1xCommFunc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/comm/Cas1xMainCcb.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/comm/Cas1xCommSaveIe.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/fsm/Cas1xFsmComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/fsm/Cas1xPrintFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xCchCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xCchGlobal.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xCchComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xCchMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xIdleFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xIdleFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xIdleHandoff.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsOrigAttempt.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsHoFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsRegFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsPageResponse.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsMsgTransmit.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsOrdOrMsgRsp.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xAcsHandoff.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xCchLost.c\
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/cch/Cas1xSlottedMode.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init/Cas1xInitEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init/Cas1xInitFlow.c  \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init/Cas1xInitFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init/Cas1xInitRelAll.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/init/Cas1xInitUim.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xCasmEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xCmeasEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xCsrchEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xMain.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xMainFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/main/Cas1xCapability.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ohm/Cas1xOhmSaveIe.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ohm/Cas1xOhmUpdate.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf/Cas1xPhyitfChCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf/Cas1xPhyitfComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf/Cas1xPhyitfFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf/Cas1xPhyitfMeasCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/phyitf/Cas1xPhyitfSrchCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfLacCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfMacCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfRlpCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/ttfitf/Cas1xTtfitfRrmItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srch/Cas1xSrchComProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srch/Cas1xSrchFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srch/Cas1xSrchSysAcq.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srch/Cas1xSrchMsg.c\
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/nasitf/Cas1xNasItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/util/Cas1xMainOta.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/util/Cas1xMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/util/Cas1xMsgComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/util/Cas1xTimer.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasComProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasSaveIe.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/meas/Cas1xMeasMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchSaveIe.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchCtrlService.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchRelease.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchPwrCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchPwrUpFunc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchHardHandoff.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchSoftHandoff.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchTestDataSo.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchSndMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/tch/Cas1xTchPara.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/smc/Cas1xAuthentication.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/smc/Cas1xSsdUpdate.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srd/Cas1xSrvRed.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/srd/Cas1xSrdFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/hrpditf/Cas1xHrpdItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasCommFunc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasFsmComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasIntraMsgComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasPrintFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/CasTimer.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpFlowEutran.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpReselToEutran.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpSysSync.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpConnSetup.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpConnSetupSendMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpL2CBSR.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpEutranReselToHrpd.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/almp/CasHrpdHalmpL2CRedirect.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/comm/CasHrpdCommCcb.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/conn/CasHrpdConnFlow.c  \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/conn/CasHrpdConnFsm.c  \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/idle/CasHrpdIdleFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/idle/CasHrpdIdleFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/init/CasHrpdInitEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/init/CasHrpdInitFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/init/CasHrpdInitPilotSearch.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/init/CasHrpdInitBsrEutran.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdHalmpEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdHrupEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdHscpEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdHspEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdMain.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/main/CasHrpdMainFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/nasitf/CasHrpdNasItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ohm/CasHrpdOhmUpdate.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ohm/CasHrpdOhmUpdateEutran.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/phyitf/CasHrpdPhyItfChCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rrm/CasHrpdRrm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/lteitf/CasHrpdLteItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupMeas.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupMeasEutran.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupSlaveMeas.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/rup/CasHrpdRupRouteUpdate.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpCommonProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpFlow.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpAtNeg.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpAnNeg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpSecurityNeg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpMACNeg.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpAppLayerNeg.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpSessionLayerNeg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpStreamNeg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpKeyExchange.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp/CasHrpdHscpMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ttfitf/CasHrpdTtfItf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/ttfitf/CasHrpdTtfItfFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/util/CasHrpdFsm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/util/CasHrpdMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/util/CasHrpdMsgComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/util/CasHrpdTimer.c
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk

