#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=cnas_ccore

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

CC_USER_DEFINES	+=-DNAS_BBIT_SWITCH

				

#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm.inc

#cnas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include \
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
	$(BALONG_TOPDIR)/modem/include/oam/lt/msp \
	$(BALONG_TOPDIR)/modem/include/oam/lt/diag \
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
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
    $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/ccb/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/task/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/timer/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/inc \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma \
    $(BALONG_TOPDIR)/modem/ps/inc/1x \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
    $(BALONG_TOPDIR)/modem/taf/inc/acore \
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
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/ccb/src/CnasCcb.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/src/CnasPrlApi.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/src/CnasPrlMem.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/src/CnasPrlMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/src/CnasPrlParse.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/task/src/CnasMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/timer/src/CnasTimerMgmt.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/mntn/src/CnasMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmMainTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmSwitchOn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmSwitchOnTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmPowerOff.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmPowerOffTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdPreProcAct.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdPreProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdProcNvim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdProcCard.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSndCas.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSndXcc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSndXreg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdComFunc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmSysAcq.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmSysAcqTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSysAcqStrategy.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmRedirTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdFsmRedir.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/src/CnasXsdSndMscc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregSndCas.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregSndXsd.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregFsmMainTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregPreProc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregPreProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregProcess.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregRegingProc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregRegingProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregListProc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregSndAps.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregFsmSwitchOn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregFsmSwitchOnTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/src/CnasXregMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMainTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMoCalling.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMoCallingTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMtCalling.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccFsmMtCallingTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndXsd.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccInstanceMgmt.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccMainCtrl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndAps.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccComFunc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndXcall.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndCas.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndCsms.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccProcNvim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndMma.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/src/CnasXccSndXpds.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluComm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluSndFsig.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluSndHsd.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluSndHsm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluProcNvim.c \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/src/CnasHluSndAs.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdComFunc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmMainTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmPowerOff.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmPowerOffTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmSwitchOn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmSwitchOnTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmSysAcq.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmSysAcqTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdPreProcAct.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdPreProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdProcCard.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdProcNvim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndCas.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndHlu.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndHsm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSysAcqStrategy.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdAvoidStrategy.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndRrm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndMscc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmPowerSave.c\
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmPowerSaveTbl.c\
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmInterSys.c\
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdFsmInterSysTbl.c\
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/src/CnasHsdSndEhsm.c\
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmComFunc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmDecode.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmEncode.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmSessionAct.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmSessionDeact.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmUatiRequest.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmPreProcAct.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmPreProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmProcNvim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndAps.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndAs.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndHlu.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndHsd.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndTtf.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmCachedMsgPriMnmt.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmConnMnmt.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmFsmSwitchOn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmKeepAlive.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmProcUsim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndEhsm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndRrm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/src/CnasHsmSndMma.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmCtx.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmMainTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmDeactivatingTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmDeactivating.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmActivatingTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmFsmActivating.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmDecode.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmEncode.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmMain.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmMntn.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmPreProcAct.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmPreProcTbl.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndAps.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndEsm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndHsd.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndHsm.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndInternalMsg.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmSndPpp.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmTimerMgmt.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmProcNvim.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmComFunc.c \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/src/CnasEhsmMsgPrioCompare.c 
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
