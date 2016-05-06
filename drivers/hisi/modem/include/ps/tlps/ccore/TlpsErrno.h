/*************************************************************************
* FILE NAME   TlpsErrno.h                  VERSION   1.0.0
*
* COMPONENT                                       PUB
*
* DESCRIPTION
* TLPS复位类型定义
*
* DATA STRUCTURES
*
*
*
* FUNCTIONS
*
* NONE
*
* HISTORY
*
* NAME            DATE             VERSION      REMARKS
*zhangshiaho      2015.08.22       v1.0.0       creation
*
*************************************************************************/
#ifndef TLPSERRNO_H
#define TLPSERRNO_H
/*DRV begin*/
#define TLPS_REBOOT_TYPE_WRITE_MAILBOX_FAIL        0xab000000
/*DRV end*/

/*GUAS begin*/
#define TLPS_REBOOT_TYPE_GUAS_RELALL_LRRC_FAIL     0xa4000001
#define TLPS_REBOOT_TYPE_WAS_LRRC_MEASURE_EXPIRED  0xa4000002
/*GUAS end*/

/*GUNAS begin*/
#define TLPS_REBOOT_TYPE_TRRC_RESUME_FAIL          0xa6000001
#define TLPS_REBOOT_TYPE_LRRC_RESUME_FAIL          0xa6000002
/*GUNAS end*/



#endif

