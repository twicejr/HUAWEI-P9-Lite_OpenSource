#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore

ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_MOUDLE_NAME	?=nas_ccore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_1)
OBC_LOCAL_MOUDLE_NAME	?=nas1_ccore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_2)
OBC_LOCAL_MOUDLE_NAME	?=nas2_ccore
endif

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_flags.mk

#USER FLAGS
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls
CC_USER_FLAGS += -march=armv6
else

CC_USER_FLAGS += -march=armv7-a

endif
CC_USER_FLAGS += -g
#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=

ifneq ($(INSTANCE_ID) ,)
CC_USER_DEFINES	+=-D$(strip $(INSTANCE_ID) )
endif
				

#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm.inc

#nas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/log \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
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
    $(BALONG_TOPDIR)/modem/include/taf/ccore \
    $(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps

OBC_LOCAL_INC_DIR += \
    	$(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/inc/lt \
	$(BALONG_TOPDIR)/modem/ps/comm/inc \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/DICC/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/FLOWCTRL/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/FLOWCTRL/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEMCTRL/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/STL/Inc \
    	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CDS/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/inc \
	$(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
	$(BALONG_TOPDIR)/modem/ps/nas/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/INC \
    	$(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASDYNLOAD/INC \
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
    	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/inc \
    	$(BALONG_TOPDIR)/modem/taf/inc/ccore \
    	$(BALONG_TOPDIR)/modem/taf/inc/common \
	$(BALONG_TOPDIR)/modem/taf/comm/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Xml/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CBA/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/SDC/Inc \
    	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafMta/Inc
	
#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/lib/NasMsgEncDec.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcAirMsgProc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcAirMsgSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcCommon.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcEntityMgmt.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcMmccProc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcMmccSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcMnccProc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcMnccSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcMsgEncDec.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcTimer.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcUserConn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcProcNvim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Src/NasCcCtx.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmAttach.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasComm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasGsm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasSuspend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmCasTimer.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmComm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmDetach.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmRam.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmRau.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmService.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/GmmTimer.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_CellProc1.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_CellProc2.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_CellProc3.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Com.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Global.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Main.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Msg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Rcv.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MM_Snd.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MmAuth.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MmGsmDifMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/MmSuspend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/NasMmEcall.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/NasMmPreProc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmcomm/src/MM_Share.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/src/AppInterfaceApi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/src/asnasapi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/src/NasCom.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/src/NasMntn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmAgent.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/smram.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmRcvGmm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmRcvRabm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmRcvTaf.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/SmSend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smccom.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smcsmrapi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smrcom.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smrtafmsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/SmsCbMsgProc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smscssmprocess.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smsmain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smspssmprocess.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/src/smsram.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsDecode.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsEncode.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsEntityMng.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsRam.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsRcvAir.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsRcvMm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsRcvTaf.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsRcvTimer.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsSndAir.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsSndMm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsSndTimer.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Src/SsTaskEntry.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Tc/Src/tc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/SRC/NasMmlCtx.c \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/SRC/NasMmlLib.c \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/SRC/NasMmlMsgProc.c \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlCommFunc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlCtx.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmMainTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlProcNvim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmSyscfgTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmSwitchOnTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmModeChangeTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmPoweroffTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlMntn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmModeChange.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmPlmnSelectionTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmPowerOff.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmSwitchOn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmSyscfg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/SRC/NasUtranCtrlFsmPlmnSelection.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/SRC/NasUsimmApi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/SRC/NasUsimmApiMntn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/SRC/NasSndUsimm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/SRC/NasFsm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccCtx.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmMainTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmPowerOff.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmPowerOffTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSwitchOn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSwitchOnTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccMntn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccPreProcAct.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccPreProcTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccProcNvim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndHsd.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndImsa.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndInternalMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndMma.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndMmc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndXsd.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccComFunc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmBsr.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmBsrTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSysAcq.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSysAcqTbl.c\
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmCLInterSys.c\
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmCLInterSysTbl.c\
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSys\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSysCfg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccFsmSysCfgTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccMlplMsplApi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccMlplMsplParse.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccMsgPrioCompare.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccProcUsim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSysAcqStrategy.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccTimerMgmt.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/src/NasMsccSndRrm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASDYNLOAD/SRC/NasDynLoadApi.c\
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASDYNLOAD/SRC/NasDynLoadMntn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcCtx.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcTimerMgmt.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcPreProcTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysOosTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysOos.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysCellResel.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcComFunc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmSyscfgTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmSyscfg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysCcoTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysCco.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcProcSuspend.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysHoTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysCellReselTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcProcNvim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndInternalMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPowerOff.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcPreProcAct.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPlmnSelection.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmAnyCellSearch.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndAps.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndCds.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndMm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndOm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndGuAs.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPoweroffTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmSwitchOnTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmSwitchOn.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndGmm.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmMainTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPlmnSelectionTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmInterSysHo.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmAnyCellSearchTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcProcUsim.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcPlmnSelectionStrategy.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcProcRegRslt.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcMsgPrioCompare.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmBgPlmnSearch.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmBgPlmnSearchTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPlmnList.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmPlmnListTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmGetGeo.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcFsmGetGeoTbl.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndMscc.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndCss.c\
	$(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndMta.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Src/NasGmmProcLResult.c \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Src/NasMmProcLResult.c \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Src/NasSmMultiMode.c \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Src/NasMmcSndLmm.c


#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
