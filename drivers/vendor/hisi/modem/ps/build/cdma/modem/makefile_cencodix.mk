#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=cencodix_ccore

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
				
CC_USER_FLAGS := -g
#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm.inc

#cas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK\Inc \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063 \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087 \
	
#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/csn1clib.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/ed_dynamic.c

OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005/C.S0005.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005/ed_c_cs0005.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005/ed_c_known_ie_cs0005.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005/ed_c_recog_cs0005.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005/UserDefinedDataTypes_cs0005.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004/C.S0004.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004/ed_c_cs0004.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004/ed_c_known_ie_cs0004.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004/ed_c_recog_cs0004.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004/UserDefinedDataTypes_cs0004.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DALMP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DALMP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DCSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DCSP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DIDSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DIDSP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DINSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DINSP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DPCP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DRUP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_DRUP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_EISP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_EISP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_MRUP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_MRUP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_OMP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_OMP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_QISP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CONN_QISP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/CSN1DataTypes_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/ed_c_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/ed_c_known_ie_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/ed_c_recog_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/GEN_GAUP_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/GEN_GCP_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DACMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DACMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DCCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DFTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DFTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DRTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_DRTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_EACMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_EACMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_ECCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_EFTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_EFTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_MFTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_MFTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_MRTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_MRTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_S1RTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_S1RTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_S3RTCMACP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MAC_S3RTCMACP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MFPAPP_DOSP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MFPAPP_FCP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MFPAPP_LUP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MFPAPP_MFPA_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/MFPAPP_RLP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PHYS01_DS0S1PLPI_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PHYS2_S2PLPI_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PHYS3_S3PLPI_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PHYS3_S3PLPI_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PKTAPP_DPA_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PKTAPP_FCP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PKTAPP_LUP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/PKTAPP_RLP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_DAP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_DEP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_DHKEP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_DKEP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_DSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_GSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SECURITY_SHA1AP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_DAMP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_DAMP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_DSCP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_DSMP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_DSMP_INUSE_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SESSION_GMCDP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SIGAPP_SLP_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/SIGAPP_SLP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/STREAM_DSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/STREAM_GVSP_INCFG_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0024/UserDefinedDataTypes_cs0024.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/CSN1DataTypes_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/ed_c_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/ed_c_known_ie_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/ed_c_recog_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_DOSP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_EMFPA_INCFG_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_FCP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_LUP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_RLP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/EMFPKA_RSP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_DOSP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_FCP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_LUP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_MMFPA_INCFG_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_RSP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/MLMFPA_SRP_INUSE_cs0063.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0063/UserDefinedDataTypes_cs0063.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/CSN1DataTypes_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/ed_c_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/ed_c_known_ie_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/ed_c_recog_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_DSAP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATINSP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATINSP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATISP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATISP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATOMP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATOMP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATOMPCS0024B_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATOMPCS0024B_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATQISP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATQISP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATRUP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATRUP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATSAP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_IRATSAP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_S1IRATRUP_INCFG_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDCON_S1IRATRUP_INUSE_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDRAT_ATS3RTCMACPR_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDRAT_ATS4RTCMACPR_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/RPDSES_SL_cs0087.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0087/UserDefinedDataTypes_cs0087.c
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk

