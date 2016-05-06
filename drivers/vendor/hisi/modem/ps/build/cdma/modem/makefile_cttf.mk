#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=cttf_ccore

#***********************************************************#
#thumb compile switch: 必须放在COMM FLAGS之前
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

#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=
CC_USER_DEFINES +=-DTTF_BBIT_SWITCH


CC_USER_FLAGS += -march=armv7-a


#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm.inc

#cttf include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include \
	$(BALONG_TOPDIR)/modem/config/log \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/drv/common \
    $(BALONG_TOPDIR)/modem/include/drv/ccore \
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
	$(BALONG_TOPDIR)/modem/include/oam/gu/hpa \
	$(BALONG_TOPDIR)/modem/include/oam/lt/msp \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/phy/gphy \
	$(BALONG_TOPDIR)/modem/include/phy/wphy \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
    	$(BALONG_TOPDIR)/modem/include/taf/ccore \
    	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/csdr \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/csdr/hrpd \
	$(BALONG_TOPDIR)/modem/include/phy/cphy \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc\cproc_hrpd \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_cm \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd_cm \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_sm \
    $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM_HISI_BALONG)

OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/inc/lt \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma/1x \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
	$(BALONG_TOPDIR)/modem/ps/comm/inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/DICC/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/FLOWCTRL/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEMCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/STL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CDS/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/Pstool/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004 \
	$(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/IP/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/inc \
	$(BALONG_TOPDIR)/modem/ps/as/comm/TPE/Inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/comm \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/ctrlext/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/voiceagent/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/testsoctrl/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/tx \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/rx \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/mac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/rlp \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/phy/cphy/csdr \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/comm/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc \
	$(BALONG_TOPDIR)/modem/ps/as/comm/tools/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/mac \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/rlp \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sig \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sps \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/utility/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/inc

#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/src/Crc.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Src/PsQnode.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/comm/src/Sha1.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfComm.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfLog.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfTimer.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfDataMoveService.c \
        $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/src/CttfHrpdMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/comm/TPE/Src/TtfTpe.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacCsch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacDsch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacAddrMatch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/src/Cttf1xFLacSendMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/mntn/src/Cttf1xLacMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacCsch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacDsch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacCfg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacSendMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/src/Cttf1xRLacAddrMatch.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/src/Cttf1xFMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/src/Cttf1xFMacDemuxDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/src/Cttf1xFMacDemuxEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/src/Cttf1xFMacCommChDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/src/Cttf1xFMacCommChEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/voiceagent/src/Cttf1xVoiceAgent.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/rx/src/Cttf1xFLoopback.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/tx/src/Cttf1xRLoopback.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/mntn/src/Cttf1xMacMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/tx/src/Cttf1xRMarkov.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/rx/src/Cttf1xFMarkov.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/utility/src/Cttf1xMarkovUtility.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/tx/src/Cttf1xRTdso.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/rx/src/Cttf1xFTdso.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/utility/src/Cttf1xTdsoUtility.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/testsoctrl/src/Cttf1xTestSoCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/src/Cttf1xRMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/src/Cttf1xRMacMuxDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/src/Cttf1xRMacMuxEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/src/Cttf1xRMacSrbpDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/src/Cttf1xRMacSrbpEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/utility/src/Cttf1xMacUtility.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/ctrlext/src/Cttf1xMacCtrlExt.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpSendRRlpMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpType1Rx.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpType3Rx.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/src/Cttf1xFRlpDataBuf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/mntn/src/Cttf1xRlpMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/utility/src/Cttf1xRlpSecurity.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/utility/src/Cttf1xRlpBlob.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/utility/src/Cttf1xRlpShareBuffer.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpBoIf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpCdsTxIf.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpSendFRlpMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpSendRRlpMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpSendCasMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpTx.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpType1Tx.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/src/Cttf1xRRlpType3Tx.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/Cttf1xFwdEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/Cttf1xRevEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfIsr.c\
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfHrpdFwdEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfHrpdRevEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfHrpdSigEntry.c \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/src/CttfDataMoveDriver.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/src/CttfHrpdCcMacDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/src/CttfHrpdCcMacEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/src/CttfHrpdFMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/src/CttfHrpdFtcMacDataProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/src/CttfHrpdFtcMacEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdAcMacAccProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdAcMacCfgProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdAcMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRtcMacCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRMacSendMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRtcMacDataProc.c \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRtc3MacDataProc.c \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/src/CttfHrpdRtcMacEntProc.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/mntn/src/CttfHrpdMacMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/utility/src/CttfHrpdMacUtility.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/mntn/src/CttfHrpdSigMntn.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/rx/src/CttfHrpdFSigPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/rx/src/CttfHrpdFSlpPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/tx/src/CttfHrpdRSigPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/tx/src/CttfHrpdRSlpPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/utility/src/CttfHrpdSigPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/src/CttfHrpdFSpsCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/src/CttfHrpdFSpsPC.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/src/CttfHrpdFSpsPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/src/CttfHrpdFSpsSecurity.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/src/CttfHrpdFSpsStream.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/src/CttfHrpdRSpsCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/src/CttfHrpdRSpsPC.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/src/CttfHrpdRSpsPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/src/CttfHrpdRSpsSecurity.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/src/CttfHrpdRSpsStream.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFPaPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFPaCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFRlp.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFTap.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFPaSendRPaMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRTap.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaPidEntry.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRpaQosBlob.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaSendNasMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaSendSnpMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaSendCasMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRRlp.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaSendPppMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRPaSendFPaMsg.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/src/CttfHrpdRDos.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/src/CttfHrpdFDos.c \
	$(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/mntn/src/CttfHrpdPaMntn.c 

endif             
        
#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
