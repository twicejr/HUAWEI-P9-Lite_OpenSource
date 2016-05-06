####################################################################################################
#
####################################################################################################
USER_CCFLAGS :=

####################################################################################################
#Directories for library files 
####################################################################################################
vob_lib_dirs :=

####################################################################################################
#library files
####################################################################################################
vob_lib_files :=

####################################################################################################
#Directories for include files
####################################################################################################
include $(BALONG_SRC_PATH)/modem/oam/build/gu/MODEM_CORE/msp_code_gu_modem_core.inc

####################################################################################################
#Directories for source files
####################################################################################################
vob_src_dirs :=

MSP_MCORE_DIR			:=$(BALONG_SRC_PATH)/modem/oam/gu/comm
MSP_CCORE_DIR  			:=$(BALONG_SRC_PATH)/modem/oam/gu/ccore
PRJ_CONFIG_DIR          :=$(BALONG_SRC_PATH)/modem/config
PRJ_INCLUDE_DIR         :=$(BALONG_SRC_PATH)/modem/include
PRJ_PLATFORM_DIR        :=$(BALONG_SRC_PATH)/modem/platform
####################################################################################################
#Source files
####################################################################################################
vob_src_files  :=   $(MSP_CCORE_DIR)/sleep/sleepflow.c\
                    $(MSP_CCORE_DIR)/sleep/mlowpower.c\
                    $(MSP_CCORE_DIR)/usimm/usimmapdu.c\
                    $(MSP_CCORE_DIR)/usimm/UsimmApi.c\
                    $(MSP_CCORE_DIR)/usimm/usimmapicnf.c\
                    $(MSP_CCORE_DIR)/usimm/usimmbase.c\
                    $(MSP_CCORE_DIR)/usimm/usimmcommon.c\
                    $(MSP_CCORE_DIR)/usimm/usimmdl.c\
                    $(MSP_CCORE_DIR)/usimm/usimmt1dl.c\
                    $(MSP_CCORE_DIR)/usimm/usimmgobal.c\
                    $(MSP_CCORE_DIR)/usimm/usimmpool.c\
                    $(MSP_CCORE_DIR)/usimm/usimmvsim.c\
                    $(MSP_CCORE_DIR)/usimm/usimminit.c\
                    $(MSP_CCORE_DIR)/usimm/usimmcuim.c\
                    $(MSP_CCORE_DIR)/usimm/usimmvsimauth.c\
                    $(MSP_MCORE_DIR)/si/pbapi.c\
                    $(MSP_MCORE_DIR)/si/pbdata.c\
                    $(MSP_MCORE_DIR)/si/pbmsg.c\
                    $(MSP_MCORE_DIR)/si/pihapi.c\
                    $(MSP_MCORE_DIR)/si/stkapi.c\
                    $(MSP_CCORE_DIR)/si/pbbase.c\
                    $(MSP_CCORE_DIR)/si/pihproc.c\
                    $(MSP_CCORE_DIR)/si/stkcomm.c\
                    $(MSP_CCORE_DIR)/si/stkgobal.c\
                    $(MSP_CCORE_DIR)/si/stkproc.c\
                    $(MSP_CCORE_DIR)/si/stkispecialproc.c\
                    $(MSP_CCORE_DIR)/si/StkAtprintf.c\
                    $(MSP_CCORE_DIR)/dh/aes_core.c\
                    $(MSP_CCORE_DIR)/dh/aes_util.c\
                    $(MSP_CCORE_DIR)/dh/md5c.c\
                    $(MSP_CCORE_DIR)/dh/nn.c\
                    $(MSP_CCORE_DIR)/dh/r_dh.c\
                    $(MSP_CCORE_DIR)/dh/rand.c\
                    $(MSP_CCORE_DIR)/si/csimagent.c
ifeq ($(INSTANCE_ID), INSTANCE_0)
vob_src_files  +=	$(MSP_CCORE_DIR)/led/lightled.c\
					$(MSP_CCORE_DIR)/cbtfun/cbtfunction.c\
					$(MSP_CCORE_DIR)/cbtfun/cbtrl.c\
					$(MSP_CCORE_DIR)/hpa/apmprocess.c\
					$(MSP_CCORE_DIR)/hpa/hpaentity.c\
					$(MSP_CCORE_DIR)/hpa/hpaglobalvar.c\
					$(MSP_CCORE_DIR)/hpa/hpainit.c\
					$(MSP_CCORE_DIR)/hpa/hpaisr.c\
					$(MSP_CCORE_DIR)/hpa/hpaoperatertt.c\
					$(MSP_CCORE_DIR)/hpa/hparingbuffer.c\
					$(MSP_CCORE_DIR)/pstool/psregrpt.c\
					$(MSP_CCORE_DIR)/sleep/sleepinit.c\
					$(MSP_MCORE_DIR)/om/OmHdlc.c\
					$(MSP_MCORE_DIR)/om/omringbuffer.c\
					$(MSP_MCORE_DIR)/om/ombufmngr.c\
					$(MSP_MCORE_DIR)/om/omlist.c\
					$(MSP_CCORE_DIR)/om/rfa.c\
					$(MSP_CCORE_DIR)/om/agingtest.c\
					$(MSP_CCORE_DIR)/om/omnosig.c\
					$(MSP_CCORE_DIR)/om/ombbpmaster.c\
					$(MSP_CCORE_DIR)/om/spysystem.c\
					$(MSP_CCORE_DIR)/om/pamom.c\
					$(MSP_CCORE_DIR)/sc/ScCtx.c\
					$(MSP_CCORE_DIR)/sc/ScApSec.c\
					$(MSP_CCORE_DIR)/sc/ScComm.c\
					$(MSP_CCORE_DIR)/sc/ScFactory.c\
					$(MSP_CCORE_DIR)/sc/ScPersonalization.c\
					$(MSP_CCORE_DIR)/bbplog/ombbplog.c\
					$(MSP_CCORE_DIR)/usimm/UsimmInstanceApi.c\
					$(MSP_CCORE_DIR)/cbpa/cbpacommagent.c\
					$(MSP_MCORE_DIR)/sc/ScCommCtx.c\
					$(MSP_MCORE_DIR)/osa/rtc_timer.c\
					$(MSP_MCORE_DIR)/osa/v_blkmem.c\
					$(MSP_MCORE_DIR)/osa/v_private.c\
					$(MSP_MCORE_DIR)/osa/v_int.c\
					$(MSP_MCORE_DIR)/osa/v_lib.c\
					$(MSP_MCORE_DIR)/osa/v_msg.c\
					$(MSP_MCORE_DIR)/osa/v_nsprintf.c\
					$(MSP_MCORE_DIR)/osa/v_queue.c\
					$(MSP_MCORE_DIR)/osa/v_sprintf.c\
					$(MSP_MCORE_DIR)/osa/v_timer.c\
					$(MSP_MCORE_DIR)/osa/vos_Id.c\
					$(MSP_MCORE_DIR)/osa/vos_main.c\
					$(MSP_MCORE_DIR)/osa/vos_outside.c\
					$(MSP_MCORE_DIR)/osa/watchdog.c\
					$(MSP_CCORE_DIR)/osa/monitordsp.c\
					$(MSP_CCORE_DIR)/osa/nucleus_sem.c\
					$(MSP_CCORE_DIR)/osa/nucleus_sock.c\
					$(MSP_CCORE_DIR)/osa/nucleus_task.c\
					$(MSP_CCORE_DIR)/osa/v_sem.c\
					$(MSP_CCORE_DIR)/osa/v_sock.c\
					$(MSP_CCORE_DIR)/osa/v_task.c\
					$(MSP_CCORE_DIR)/osa/rtosck_sem.c\
					$(MSP_CCORE_DIR)/osa/rtosck_task.c\
					$(MSP_CCORE_DIR)/xml/OamXmlComm.c
endif					
					

####################################################################################################
#general make rules
####################################################################################################

####################################################################################################
#
####################################################################################################


####################################################################################################
#
####################################################################################################