#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=was_ccore_private

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_flags.mk

#USER FLAGS AND DEFINES
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls
CC_USER_FLAGS += -march=armv6
else

CC_USER_FLAGS += -march=armv7-a

endif

#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=
CC_USER_DEFINES +=-DWAS_BBIT_SWITCH
				

#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm.inc

#was include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
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
	$(BALONG_TOPDIR)/modem/include/oam/lt/ccore \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/phy/gphy \
	$(BALONG_TOPDIR)/modem/include/phy/wphy \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
	$(BALONG_TOPDIR)/modem/include/taf/ccore \
	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
	$(BALONG_TOPDIR)/modem/include/nv/gu/phy
     
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/inc/gu \
    $(BALONG_TOPDIR)/modem/ps/inc/lt \
    $(BALONG_TOPDIR)/modem/ps/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/STL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Pscfg \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Comm \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Gtf \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Wtf \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Gas \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Was \
	$(BALONG_TOPDIR)/modem/ps/as/gu/comm/ASN1/Codec \
	$(BALONG_TOPDIR)/modem/ps/as/gu/comm/Cipher/Inc \
	$(BALONG_TOPDIR)/modem/ps/as/gu/comm/Frmwk/Inc \
	$(BALONG_TOPDIR)/modem/ps/as/gu/comm/Pscfg/Inc \
	$(BALONG_TOPDIR)/modem/ps/as/gu/gas/COMMON/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/DATA/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GASM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMSI/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GRR/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/RR/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCBS/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PUBLIC \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/CF/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/TOOLS \
	$(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/MUX/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/CST/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/DL/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GMAC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GRLC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GRM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/LL/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/SN/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/PDCP/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/MAC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/RLC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/BMC/Inc \
	$(BALONG_TOPDIR)/modem/ps/nas/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmcomm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Tc/Inc \
	$(BALONG_TOPDIR)/modem/taf/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc


#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/ps/as/gu/comm/ASN1/Codec/per_main.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/Dec/message_list_rom_dec.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/Dec/rrc_dec_per_rom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/Enc/message_list_rom_enc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/Enc/rrc_enc_per_rom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/Itf/WasAsn1Api.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/DynEnc/message_list_rom_dyn_enc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/ASN1/DynEnc/rrc_dyn_enc_per_rom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CBS/WasCbs.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CBS/WasCbsFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselIntraFreq.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselComProc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMsgItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSndMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellResel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselInterFreq.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMsgProc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselInterRat.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSpecPlmnSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselFftPlmnSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselPlmnListSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselAnyCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSpecCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselStartNeighMeas.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCandCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselBestCandCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSpecFreqSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselStart.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselStop.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSysInfoChanged.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselGetServCellSysInfo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSsc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSlaveMeasCfg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgGlobal.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgSndMsgItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgDeactiveSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselHistoryCandCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcRrmmCellSelCtrl.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcUraPchResel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcEntry.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCellCfg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcRelAll.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcOutService.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcIdleResel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCellFachResel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcPlmnSearch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcNasSysChgInfo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCommProc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCellPchResel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcDeactive.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuCellupdate.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuCellUpdate2D.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuCellUpdate2F.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuCellUpdate2P.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuCellUpdateCnfMsgHandle.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuMsgHandleComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuParaSet.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUpdateCtx.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUraUpdate.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUraUpdate2F.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUraUpdate2P.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUraUpdateCnfMsgHandle.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUtranMobiInfo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuUtranMobilInfoMsgHandle.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuWaitCellUpdateCnf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfRcvMac.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfRcvRlc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfSndPdcp.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfRcvPdcp.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfEntry.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfCom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfSndRlc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfSndMac.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfSndBmc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/L2ITF/WasL2itfFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainTimer.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainPrintFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasFsmComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMain.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainFlow.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainCcb.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasWcomFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasEntry.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasWrrFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasPfcFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MNTN/WasMntnUuMsgTrace.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MNTN/WasMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MNTN/WasMntnSoftPara.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/NASITF/WasNasItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyItfFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyItfWCom.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyItfWrr.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyitfMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbParaSet.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbUpdateCtx.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlD2P.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlF2F.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlD2F.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlF2D.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlF2P.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbCtrlD2D.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbSndUuMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbSndCfgMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMain.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleTfcCtrl.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleRbRel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleTrchRecfg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandlePhyRecfg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleRbRecfg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMsgHandleRbSetup.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB/WasRbMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmIntraFreqMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmInterFreqMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSndMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmMeasureRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR3.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR4.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmActionList.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmProcMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmGlobal.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR5.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR6.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR7.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR8.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeR9.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmInterRatMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmQualMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmTrafVolMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmUeInternalMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIe.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmPositionMeasRslt.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnSetupDch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcUeCapab.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnReq.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcPaging.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcAdrx.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcSibChange.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcDirectData.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcSignalRel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnReject.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnRel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnSetupComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnSetupFach.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnWaitSetup.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcInterRatHoInfo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcFastDormancy.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SHO/WasShoAsuMsgHandle.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SHO/WasShoComm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SHO/WasShoFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SHO/WasShoProc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SHO/WasShoMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibCommItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibModify.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibCommPros.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibGetDchSysInfo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibStart.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSib6hUpdate.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibPeriod.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibRcvSib7.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibMsgSnd.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibReqMsgHandle.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SIB/WasSibMsgItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SMC/WasSmcFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SMC/WasSmcEntry.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SMC/WasSmc.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoEntry.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoFsm.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoG2WCchg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoG2WHo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoGlobal.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIe.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR3.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR4.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR5.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR6.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR7.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeR9.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSndMsg.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoW2GCchgInDch.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoW2GCchgInFach.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoW2GHo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoMntn.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoG2WCellSel.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoW2LHo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoL2WHo.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoL2WRedirect.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/TAFITF/WasTafItf.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR3.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR4.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR6.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR5.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR7.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR8.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR9.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommCcbApi.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasRsltCode.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MNTN/WasMntnNetMon.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PWR/WasPwrMain.c\
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRMITF/WasRrmItf.c
    
OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselComProcEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMntnEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMsgItfEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselMsgProcEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselSndMsgEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselCellReselEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgDeactiveSearchEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgSearchEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasBgSndMsgItfEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL/WasCselPlmnListSearchEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCellPchReselEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcComEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCommProcEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcEntryEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcIdleReselEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcOutServiceEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcUraPchReselEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC/WasCselpcCellSearchEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU/WasCuOutOfServEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasMainFlowEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasWcomFsmEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MAIN/WasWrrFsmEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/MNTN/WasMntnEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyItfWComEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PHYITF/WasPhyItfWrrEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmActionListEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmGlobalEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmMntnEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmProcMsgEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSaveIeEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmSndMsgEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM/WasRmEutraMeasRslt.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnRejectEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnRelEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnReqEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcConnSetupCommEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcInterRatHoInfoEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC/WasRrcUeCapabEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoEntryEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoGlobalEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSaveIeEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO/WasSysHoSndMsgEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommCcbApiEutra.c \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/COMM/WasCommSaveIeR8Eutra.c 
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
