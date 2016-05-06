/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              beioctl.h
*
*  Project Code: VISP1.5
*   Module Name:socket4   
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: IO control functions
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _BEIOCTL_H
#define        _BEIOCTL_H

#ifdef    __cplusplus
extern    "C"{
#endif

LONG    NI_IfIoCtl(ULONG,CHAR *);
#ifndef _WINDOWS_
LONG    Rs232_IoCtl(ULONG,CHAR *);
LONG    MT_1398IoCtl(ULONG,CHAR *);
#endif
LONG    PPP_IoCtl(ULONG, CHAR *);
LONG    IP_IoCtl(ULONG, CHAR *);
LONG    IP_RtIoCtl(ULONG, CHAR *);
LONG    IP_AtIoCtl(ULONG, CHAR *);
LONG    IP_NmIoCtl(ULONG, CHAR *);
LONG    ICMP_IoCtl(ULONG, CHAR *);
LONG    FR_IoCtl(ULONG, CHAR *);
LONG    PPP_MIBIoCtl(ULONG ulCmd, CHAR * pData);
LONG    ipx_ioctl(ULONG ulCmd, CHAR *pData);
LONG    rip_ioctl(ULONG ulCmd, CHAR *pData);
LONG    X25_MibIoCtl(ULONG l, CHAR* s);
LONG    Lapb_MibIoCtl(ULONG l, CHAR* s);
LONG    ospf_ioctl(ULONG cmd, CHAR * arg);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
