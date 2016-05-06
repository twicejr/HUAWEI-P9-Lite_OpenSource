#!/bin/bash 
set -e

BALONG_TOPDIR=$1
CFG_ANDROID_DIR=$2
CFG_OS_ANDROID_PRODUCT_NAME=$3
CFG_PRODUCT_CFG_KERNEL_ENTRY=$4
ANDROID_MAKE_GOALS=$5
NumJobs=`expr $(cat /proc/cpuinfo | grep "processor" | wc -l) \* 2`
function sed_balong_start()
{
	MAKE_BOOT_FILE=${CFG_ANDROID_DIR}/kernel/arch/arm/mach-$1/Makefile.boot
	TEMP_MAKE_BOOT_FILE=${CFG_ANDROID_DIR}/kernel/arch/arm/mach-$1/Makefile_temp.boot
	sed -e "s/CFG_PRODUCT_CFG_KERNEL_ENTRY/$CFG_PRODUCT_CFG_KERNEL_ENTRY/g" ${MAKE_BOOT_FILE} > ${TEMP_MAKE_BOOT_FILE}
}

function sed_balong_end()
{
	rm -rf ${TEMP_MAKE_BOOT_FILE}
}

case "$CFG_OS_ANDROID_PRODUCT_NAME" in
	"balong" )
	sed_balong_start balong;
	cd ${CFG_ANDROID_DIR}
	. build/envsetup.sh
	choosecombo release ${CFG_OS_ANDROID_PRODUCT_NAME} eng
	if [ -z "${ANDROID_MAKE_GOALS}" ]; then
		make BUILD_TINY_ANDROID=true -j${NumJobs}
		echo "make USE_MINGW=y fastboot"
		make USE_MINGW=y fastboot
	else
		android_pkgs=${ANDROID_MAKE_GOALS}
		make  -j ${NumJobs} ${android_pkgs}
	fi	
	sed_balong_end;
	;;
	"hi3650" )
	cd ${CFG_ANDROID_DIR}
	MODEM_SWITCH=fullAP
	if [ "${singleap}" = "true" ]; then
		MODEM_SWITCH=singleAP
	fi
	. build/envsetup.sh
	choosecombo release ${CFG_OS_ANDROID_PRODUCT_NAME} eng normal ${MODEM_SWITCH} arm64
	if [ "${tiny}" = "true" ]; then
		android_pkgs="bootimage fastboot.img make_ext4fs"
	elif [ -z "${ANDROID_MAKE_GOALS}" ]; then
		android_pkgs=""
	else
		android_pkgs=${ANDROID_MAKE_GOALS}
	fi

	if [ "${separate}" = "true" ]; then
		echo "separate=true"
	else
		if [ -d vendor/huawei/modem/commril/ ] ;then
			cp -rf vendor/huawei/modem/commril/* hardware/ril/libril/
			rm hardware/ril/libril/Android.mk
			mv hardware/ril/libril/Android.mk.ril hardware/ril/libril/Android.mk
			cp -rf vendor/huawei/modem/commril/rild/* hardware/ril/rild/
			rm -rf hardware/ril/libril/rild
		fi
	fi
    
	if [ "${singleap}" = "true" ]; then
		echo "make -j ${android_pkgs}"
		make -j ${android_pkgs}
	else
		echo "make -j ${android_pkgs} CFG_BALONG_MODEM=true"
		make -j ${android_pkgs} CFG_BALONG_MODEM=true
	fi

	;;
esac

exit $?
