# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : subdirs_all pre_build main_all post_build

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

BUILD_SPEC = ARMARCH5gnu
DEBUG_MODE = 1
SRC_DIR := .
BUILD_ROOT_DIR := 
PRJ_ROOT_DIR := D:/view/BugFix/MAPS2000_CODE/Maps2000
WS_ROOT_DIR := D:/view/BugFix/MAPS2000_CODE/WKB

ALL_BUILD_SPECS := ARMARCH5diab ARMARCH5diabbe ARMARCH5gnu ARMARCH5gnube \
	 ARMARCH6diab ARMARCH6diabbe ARMARCH6gnu ARMARCH6gnube \
	 I80486diab I80486gnu MIPS32sfdiab MIPS32sfdiable \
	 MIPS32sfgnu MIPS32sfgnule MIPS64diab MIPS64diable \
	 MIPS64gnu MIPS64gnule PENTIUM2diab PENTIUM2gnu \
	 PENTIUM3diab PENTIUM3gnu PENTIUM4diab PENTIUM4gnu \
	 PENTIUMdiab PENTIUMgnu PPC32diab PPC32gnu \
	 PPC32sfdiab PPC32sfgnu PPC403diab PPC403gnu \
	 PPC405diab PPC405gnu PPC405sfdiab PPC405sfgnu \
	 PPC440diab PPC440gnu PPC440sfdiab PPC440sfgnu \
	 PPC603diab PPC603gnu PPC604diab PPC604gnu \
	 PPC85XXdiab PPC85XXgnu PPC85XXsfdiab PPC85XXsfgnu \
	 PPC860sfdiab PPC860sfgnu SH7750diab SH7750diable \
	 SH7750gnu SH7750gnule SIMLINUXdiab SIMLINUXgnu \
	 SIMNTdiab SIMNTgnu SIMSPARCSOLARISdiab SIMSPARCSOLARISgnu \
	 XSCALEdiab XSCALEdiabbe XSCALEgnu XSCALEgnube
ENABLED_BUILD_SPECS := ARMARCH5gnu

ifeq ($(BUILD_SPEC),ARMARCH5diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5diab_DEBUG
else
OBJ_DIR := ARMARCH5diab
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5diabbe_DEBUG
else
OBJ_DIR := ARMARCH5diabbe
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5gnu_DEBUG
else
OBJ_DIR := ARMARCH5gnu
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5gnube_DEBUG
else
OBJ_DIR := ARMARCH5gnube
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6diab_DEBUG
else
OBJ_DIR := ARMARCH6diab
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6diabbe_DEBUG
else
OBJ_DIR := ARMARCH6diabbe
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6gnu_DEBUG
else
OBJ_DIR := ARMARCH6gnu
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6gnube_DEBUG
else
OBJ_DIR := ARMARCH6gnube
endif
endif
ifeq ($(BUILD_SPEC),I80486diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := I80486diab_DEBUG
else
OBJ_DIR := I80486diab
endif
endif
ifeq ($(BUILD_SPEC),I80486gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := I80486gnu_DEBUG
else
OBJ_DIR := I80486gnu
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfdiab_DEBUG
else
OBJ_DIR := MIPS32sfdiab
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfdiable_DEBUG
else
OBJ_DIR := MIPS32sfdiable
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfgnu_DEBUG
else
OBJ_DIR := MIPS32sfgnu
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfgnule_DEBUG
else
OBJ_DIR := MIPS32sfgnule
endif
endif
ifeq ($(BUILD_SPEC),MIPS64diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64diab_DEBUG
else
OBJ_DIR := MIPS64diab
endif
endif
ifeq ($(BUILD_SPEC),MIPS64diable)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64diable_DEBUG
else
OBJ_DIR := MIPS64diable
endif
endif
ifeq ($(BUILD_SPEC),MIPS64gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64gnu_DEBUG
else
OBJ_DIR := MIPS64gnu
endif
endif
ifeq ($(BUILD_SPEC),MIPS64gnule)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64gnule_DEBUG
else
OBJ_DIR := MIPS64gnule
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM2diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM2diab_DEBUG
else
OBJ_DIR := PENTIUM2diab
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM2gnu_DEBUG
else
OBJ_DIR := PENTIUM2gnu
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM3diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM3diab_DEBUG
else
OBJ_DIR := PENTIUM3diab
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM3gnu_DEBUG
else
OBJ_DIR := PENTIUM3gnu
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM4diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM4diab_DEBUG
else
OBJ_DIR := PENTIUM4diab
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM4gnu_DEBUG
else
OBJ_DIR := PENTIUM4gnu
endif
endif
ifeq ($(BUILD_SPEC),PENTIUMdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUMdiab_DEBUG
else
OBJ_DIR := PENTIUMdiab
endif
endif
ifeq ($(BUILD_SPEC),PENTIUMgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUMgnu_DEBUG
else
OBJ_DIR := PENTIUMgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32diab_DEBUG
else
OBJ_DIR := PPC32diab
endif
endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32gnu_DEBUG
else
OBJ_DIR := PPC32gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC32sfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32sfdiab_DEBUG
else
OBJ_DIR := PPC32sfdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC32sfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32sfgnu_DEBUG
else
OBJ_DIR := PPC32sfgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC403diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC403diab_DEBUG
else
OBJ_DIR := PPC403diab
endif
endif
ifeq ($(BUILD_SPEC),PPC403gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC403gnu_DEBUG
else
OBJ_DIR := PPC403gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC405diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC405diab_DEBUG
else
OBJ_DIR := PPC405diab
endif
endif
ifeq ($(BUILD_SPEC),PPC405gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC405gnu_DEBUG
else
OBJ_DIR := PPC405gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC405sfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC405sfdiab_DEBUG
else
OBJ_DIR := PPC405sfdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC405sfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC405sfgnu_DEBUG
else
OBJ_DIR := PPC405sfgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC440diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC440diab_DEBUG
else
OBJ_DIR := PPC440diab
endif
endif
ifeq ($(BUILD_SPEC),PPC440gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC440gnu_DEBUG
else
OBJ_DIR := PPC440gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC440sfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC440sfdiab_DEBUG
else
OBJ_DIR := PPC440sfdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC440sfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC440sfgnu_DEBUG
else
OBJ_DIR := PPC440sfgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC603diab_DEBUG
else
OBJ_DIR := PPC603diab
endif
endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC603gnu_DEBUG
else
OBJ_DIR := PPC603gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC604diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC604diab_DEBUG
else
OBJ_DIR := PPC604diab
endif
endif
ifeq ($(BUILD_SPEC),PPC604gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC604gnu_DEBUG
else
OBJ_DIR := PPC604gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC85XXdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC85XXdiab_DEBUG
else
OBJ_DIR := PPC85XXdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC85XXgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC85XXgnu_DEBUG
else
OBJ_DIR := PPC85XXgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC85XXsfdiab_DEBUG
else
OBJ_DIR := PPC85XXsfdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC85XXsfgnu_DEBUG
else
OBJ_DIR := PPC85XXsfgnu
endif
endif
ifeq ($(BUILD_SPEC),PPC860sfdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC860sfdiab_DEBUG
else
OBJ_DIR := PPC860sfdiab
endif
endif
ifeq ($(BUILD_SPEC),PPC860sfgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC860sfgnu_DEBUG
else
OBJ_DIR := PPC860sfgnu
endif
endif
ifeq ($(BUILD_SPEC),SH7750diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH7750diab_DEBUG
else
OBJ_DIR := SH7750diab
endif
endif
ifeq ($(BUILD_SPEC),SH7750diable)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH7750diable_DEBUG
else
OBJ_DIR := SH7750diable
endif
endif
ifeq ($(BUILD_SPEC),SH7750gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH7750gnu_DEBUG
else
OBJ_DIR := SH7750gnu
endif
endif
ifeq ($(BUILD_SPEC),SH7750gnule)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH7750gnule_DEBUG
else
OBJ_DIR := SH7750gnule
endif
endif
ifeq ($(BUILD_SPEC),SIMLINUXdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMLINUXdiab_DEBUG
else
OBJ_DIR := SIMLINUXdiab
endif
endif
ifeq ($(BUILD_SPEC),SIMLINUXgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMLINUXgnu_DEBUG
else
OBJ_DIR := SIMLINUXgnu
endif
endif
ifeq ($(BUILD_SPEC),SIMNTdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMNTdiab_DEBUG
else
OBJ_DIR := SIMNTdiab
endif
endif
ifeq ($(BUILD_SPEC),SIMNTgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMNTgnu_DEBUG
else
OBJ_DIR := SIMNTgnu
endif
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMSPARCSOLARISdiab_DEBUG
else
OBJ_DIR := SIMSPARCSOLARISdiab
endif
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMSPARCSOLARISgnu_DEBUG
else
OBJ_DIR := SIMSPARCSOLARISgnu
endif
endif
ifeq ($(BUILD_SPEC),XSCALEdiab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEdiab_DEBUG
else
OBJ_DIR := XSCALEdiab
endif
endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEdiabbe_DEBUG
else
OBJ_DIR := XSCALEdiabbe
endif
endif
ifeq ($(BUILD_SPEC),XSCALEgnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEgnu_DEBUG
else
OBJ_DIR := XSCALEgnu
endif
endif
ifeq ($(BUILD_SPEC),XSCALEgnube)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEgnube_DEBUG
else
OBJ_DIR := XSCALEgnube
endif
endif

ifeq ($(BUILD_SPEC),ARMARCH5diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),I80486diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),I80486gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64diable)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64gnule)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM2diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM3diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM4diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUMdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUMgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32sfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32sfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC403diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC403gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC405diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC405gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC405sfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC405sfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC440diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC440gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC440sfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC440sfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC603diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC603gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC604diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC604gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC85XXdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC85XXgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC860sfdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC860sfgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH7750diab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH7750diable)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH7750gnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH7750gnule)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMLINUXdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMLINUXgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMNTdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMNTgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEdiab)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEgnu)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEgnube)
SUBDIRS :=
OBJECTS :=

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif

PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0

ifeq ($(BUILD_SPEC),ARMARCH5diab)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV5LS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV5ES:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH5gnu)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -t5
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Ppp/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/RR/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GRR/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GCOM/GCOMSI/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Comm -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Gmm/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/Encodix/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/HiOm -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Taf -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Usimm/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Gtf -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/COMMON/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Nas -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GCOM/DATA/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GCOM/GCOMM/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Rrcf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/GRLC/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Gas -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GCOM/GCOMC/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/At/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Hpa/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GCOM/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/LL/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Tafm/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Pscomm/Asn1/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Wrrc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wtf/Src/PDCP/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GHPA/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/SHPA/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wtf/Src/RLC/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Smt/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Pscomm/Pscfg/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Mm/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Aps/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GSLEEP/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wtf/Src/MAC/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/sleep/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Ssa/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Cc/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Mmc/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Rabm/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/SN/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Cca/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Ss/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Wtf -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/CF/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Rmf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gas/GASM/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Sms/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/PPPoE/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/GMAC/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Rcsf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Sm/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Gtf/DL/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Gna/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Rsrf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Pscomm/Psstub/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Om/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Tc/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Nasapi/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Inc/Pscfg -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Pscomm/Frmwk/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Nas/Src/Mmcomm/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wtf/Src/MUX/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Src/Wasapi/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Mma/status/inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wrrc/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Pscomm/Zc/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Wtf/Inc -ID:/view/BugFix/MAPS2000_CODE/Maps2000/Src/Taf/Src/Taf/Src/Mma/inc 
endif

ifeq ($(BUILD_SPEC),ARMARCH5gnube)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -t5be  -Wa,-EB
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH6diab)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV6LS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV6ES:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH6gnu)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -t5
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),ARMARCH6gnube)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -t5be  -Wa,-EB
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),I80486diab)
VX_CPU_FAMILY = pentium
CPU = I80486
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),I80486gnu)
VX_CPU_FAMILY = pentium
CPU = I80486
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=i486 -march=i486
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS32sfdiab)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS2FS:vxworks62 -Xno-mips16-calls
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS32sfdiable)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = diab
TOOL = sfdiable
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS2MS:vxworks62 -Xno-mips16-calls
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS32sfgnu)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips2 -EB
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS32sfgnule)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = gnu
TOOL = sfgnule
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips2 -EL
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS64diab)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS3XH:vxworks62 -Xno-mips16-calls
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS64diable)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = diab
TOOL = diable
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS3ZH:vxworks62 -Xno-mips16-calls
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS64gnu)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips3 -mabi=o64 -mgp64 -EB
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),MIPS64gnule)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = gnu
TOOL = gnule
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips3 -mabi=o64 -mgp64 -EL
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM2diab)
VX_CPU_FAMILY = pentium
CPU = PENTIUM2
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM2LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM2gnu)
VX_CPU_FAMILY = pentium
CPU = PENTIUM2
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=pentiumpro -march=pentiumpro
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM3diab)
VX_CPU_FAMILY = pentium
CPU = PENTIUM3
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM3LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM3gnu)
VX_CPU_FAMILY = pentium
CPU = PENTIUM3
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=pentium3 -march=pentium3
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM4diab)
VX_CPU_FAMILY = pentium
CPU = PENTIUM4
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM4LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUM4gnu)
VX_CPU_FAMILY = pentium
CPU = PENTIUM4
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=pentium4 -march=pentium4
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUMdiab)
VX_CPU_FAMILY = pentium
CPU = PENTIUM
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUMLH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PENTIUMgnu)
VX_CPU_FAMILY = pentium
CPU = PENTIUM
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=pentium -march=pentium
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC32diab)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCFH:vxworks62 -Xstmw-slow -DPPC32_fp60x
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC32gnu)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mhard-float -mstrict-align -mno-implicit-fp -DPPC32_fp60x
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC32sfdiab)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCFS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC32sfgnu)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -msoft-float -mstrict-align
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC403diab)
VX_CPU_FAMILY = ppc
CPU = PPC403
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC403FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC403gnu)
VX_CPU_FAMILY = ppc
CPU = PPC403
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=403 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC405diab)
VX_CPU_FAMILY = ppc
CPU = PPC405
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC405FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC405gnu)
VX_CPU_FAMILY = ppc
CPU = PPC405
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=405 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC405sfdiab)
VX_CPU_FAMILY = ppc
CPU = PPC405
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC405FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC405sfgnu)
VX_CPU_FAMILY = ppc
CPU = PPC405
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=405 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC440diab)
VX_CPU_FAMILY = ppc
CPU = PPC440
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC440FH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC440gnu)
VX_CPU_FAMILY = ppc
CPU = PPC440
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=440 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC440sfdiab)
VX_CPU_FAMILY = ppc
CPU = PPC440
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC440FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC440sfgnu)
VX_CPU_FAMILY = ppc
CPU = PPC440
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=440 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC603diab)
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC603FH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC603gnu)
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC604diab)
VX_CPU_FAMILY = ppc
CPU = PPC604
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC604FH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC604gnu)
VX_CPU_FAMILY = ppc
CPU = PPC604
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=604 -mstrict-align -mno-implicit-fp
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC85XXdiab)
VX_CPU_FAMILY = ppc
CPU = PPC85XX
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCE500FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC85XXgnu)
VX_CPU_FAMILY = ppc
CPU = PPC85XX
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=8540 -mstrict-align -msoft-float -mabi=no-spe
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
VX_CPU_FAMILY = ppc
CPU = PPC85XX
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCE500FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
VX_CPU_FAMILY = ppc
CPU = PPC85XX
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=8540 -mstrict-align -msoft-float -mabi=no-spe
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC860sfdiab)
VX_CPU_FAMILY = ppc
CPU = PPC860
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC860FS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),PPC860sfgnu)
VX_CPU_FAMILY = ppc
CPU = PPC860
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=860 -mstrict-align -msoft-float
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SH7750diab)
VX_CPU_FAMILY = sh
CPU = SH7750
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tSH4EH:vxworks62 -Xunderscore-leading
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SH7750diable)
VX_CPU_FAMILY = sh
CPU = SH7750
TOOL_FAMILY = diab
TOOL = diable
TOOL_PATH = 
CC_ARCH_SPEC = -tSH4LH:vxworks62 -Xunderscore-leading
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SH7750gnu)
VX_CPU_FAMILY = sh
CPU = SH7750
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -m4
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SH7750gnule)
VX_CPU_FAMILY = sh
CPU = SH7750
TOOL_FAMILY = gnu
TOOL = gnule
TOOL_PATH = 
CC_ARCH_SPEC = -m4 -ml
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMLINUXdiab)
VX_CPU_FAMILY = simlinux
CPU = SIMLINUX
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMLINUXgnu)
VX_CPU_FAMILY = simlinux
CPU = SIMLINUX
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=i486 -march=i486
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMNTdiab)
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMNTgnu)
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=i486 -march=i486
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
VX_CPU_FAMILY = simso
CPU = SIMSPARCSOLARIS
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tSPARCFH:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
VX_CPU_FAMILY = simso
CPU = SIMSPARCSOLARIS
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = 
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),XSCALEdiab)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMXLS:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),XSCALEdiabbe)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMXES:vxworks62
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),XSCALEgnu)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -txscale
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif

ifeq ($(BUILD_SPEC),XSCALEgnube)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -txscalebe  -Wa,-EB
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
endif


ifeq ($(BUILD_SPEC),ARMARCH5diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = 
else
DEBUGFLAGS_C-Compiler = -O3 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -mapcs-32 -fsigned-char -mlittle-endian -march=armv5 -DVOS_OS_VER=VOS_VXWORKS -DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0 -mlong-calls $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = 
else
DEBUGFLAGS_C++-Compiler = -O3 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -mapcs-32 -fsigned-char -mlittle-endian -march=armv5 -DVOS_OS_VER=VOS_VXWORKS -DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0 -mlong-calls $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -mapcs-32 -fsigned-char -mlittle-endian -march=armv5 -DVOS_OS_VER=VOS_VXWORKS -DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0 -mlong-calls $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -mapcs-32 -fsigned-char -mlittle-endian -march=armv5 -DVOS_OS_VER=VOS_VXWORKS -DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0 -mlong-calls $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -mapcs-32 -fsigned-char -mlittle-endian -march=armv5 -DVOS_OS_VER=VOS_VXWORKS -DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0 -mlong-calls $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall -msoft-float -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -fno-builtin -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),I80486gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -fno-builtin  -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -fno-builtin  -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -fno-builtin  -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -fno-builtin  -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop -mno-sse -mno-sse2
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xstsw-slow -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC403gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC405sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC440sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC604gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC85XXsfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC860sfgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xalign-power2 -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750diable)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xalign-power2 -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH7750gnule)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xmnem-mit -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMLINUXgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xmnem-mit -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMNTgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -nostdlib -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xlit-auto-off -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif





-include *.makefile

main_all : check_objectdir external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

check_objectdir :
	@if [ ! -d "$(OBJ_DIR)" ]; then\
		mkdir -p $(OBJ_DIR);\
	fi

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

# recursive make in SUBDIRS
subdirs_all :
	@_PWD=`pwd`;\
	for dir in _dummy_ $(SUBDIRS); do\
		if [ "$$dir" = "_dummy_" ]; then\
			continue ;\
		fi;\
		if [ ! -d "$$dir" ]; then\
			continue ;\
		fi;\
		echo "Recursive make: Changing to Directory '$$dir'";\
		cd "$$dir";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) all || exit;\
		echo "Recursive make: Changing back to Directory '$$_PWD'";\
		cd "$$_PWD";\
	done

clean ::
	@_PWD=`pwd`;\
	for dir in _dummy_ $(SUBDIRS); do\
		if [ "$$dir" = "_dummy_" ]; then\
			continue ;\
		fi;\
		if [ ! -d "$$dir" ]; then\
			continue ;\
		fi;\
		echo "Recursive make: Changing to Directory '$$dir'";\
		cd "$$dir";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) $@ || exit;\
		echo "Recursive make: Changing back to Directory '$$_PWD'";\
		cd "$$_PWD";\
	done

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""

_clean :
	@echo "make: removing targets and objects of `pwd`";\
	rm -f $(OBJECTS) $(PROJECT_TARGETS) $(DEP_FILES) $(wildcard $(OBJ_DIR)/*.unstripped) $(wildcard $(OBJ_DIR)/ctdt.*)

build_all_specs :
	@echo "building target default for ALL build-specs";\
	for spec in _dummy_ $(ALL_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building all for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) || exit;\
	done

clean_all_specs :
	@echo "building target clean for ALL build-specs";\
	for spec in _dummy_ $(ALL_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building clean for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) clean || exit;\
	done

build_enabled_specs :
	@echo "building target default for ENABLED build-specs";\
	for spec in _dummy_ $(ENABLED_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building all for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) || exit;\
	done

clean_enabled_specs :
	@echo "building target clean for ENABLED build-specs";\
	for spec in _dummy_ $(ENABLED_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building clean for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) clean || exit;\
	done
