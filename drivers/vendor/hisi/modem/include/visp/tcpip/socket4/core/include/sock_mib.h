/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_mib.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: the macro,struct,function used by mib agent
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef         _SOCK_MIB_H
#define         _SOCK_MIB_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define IOCPARM_MASK    0x1fff          
#define IOCPARM_LEN(x)  (((x) >> 16) & IOCPARM_MASK)
#define IOCBASECMD(x)   ((x) & ~(IOCPARM_MASK << 16))
#define IOCGROUP(x)     (((x) >> 8) & 0xff)

#define NBPG            0x1000
#define IOCPARM_MAX     NBPG    
                        
#define IOC_VOID        (ULONG)0x20000000
#define IOC_OUT         (ULONG)0x40000000
#define IOC_IN          (ULONG)0x80000000
#define IOC_INOUT       (IOC_IN|IOC_OUT)
#define IOC_DIRMASK     (ULONG)0xe0000000

#define _IOC(inout,group,num,len) \
    (inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define _IO(g,n)        _IOC(IOC_VOID,  (g), (n), 0)
#define _IOR(g,n,t)     _IOC(IOC_OUT,   (g), (n), sizeof(t))
#define _IOW(g,n,t)     _IOC(IOC_IN,    (g), (n), sizeof(t))
#define _IOWR(g,n,t)    _IOC(IOC_INOUT,(g), (n), sizeof(t))
#define _IOMR(g,n,t)    _IOC(IOC_OUT,   (g), (n), (t))
#define _IOMW(g,n,t)    _IOC(IOC_IN,    (g), (n), (t))
#define _IOMWR(g,n,t)   _IOC(IOC_INOUT,(g), (n), (t))


#define NIMIB           0x01
#define ETHMIB          0x02
#define SERMIB          0x03
#define PPPMIB          0x04
#define IPMIB           0x05
#define IPATMIB         0x06
#define IPRTMIB         0x07
#define IPNMMIB         0x08
#define ICMPMIB         0x09
#define UDPMIB          0x0a
#define TCPMIB          0x0b
#define FRMIB           0x0c
#define ISNMIB          0x0d
#define IPXMIB          0x0e
#define RIPMIB          0x0f
#define X25MIB          0x10
#define LAPBMIB         0x11
#define OSPFMIB         0x12
#ifdef _Q4500_
#define MODULEMIB       0x13
#endif
#define MIXINFOMIB      0X14

#define SIOCPSOSINIT                    _IOMW('s',10,4)
/*----------------------------------------------------------------------*/
/* Definitions for MBUF statistics                                      */
/*----------------------------------------------------------------------*/
#define SIOCGMBSTAT                     _IOMR('s',1,255)
#define SIOCGDBSTAT                     _IOMR('s',2,255)


/*----------------------------------------------------------------------*/
/* Definitions for Routing entries                                      */
/*----------------------------------------------------------------------*/
#define SIOCADDRT                       _IOW('r', 10, struct tagORTENTRY)
#define SIOCDELRT                       _IOW('r', 11, struct tagORTENTRY)
#define SIOCMODRT                       _IOW('r', 13,struct tagORTENTRY) 

/* added by groupcast */
#define SIOCGETVIFCNT                     _IOW('r',14,ULONG)
#define SIOCGETSGCNT                      _IOW('r',15,ULONG)

/*----------------------------------------------------------------------*/
/* Definitions for NI parameters                                        */
/*----------------------------------------------------------------------*/
#define SIOCAIFADDR                     _IOW('i',10,struct tagIFREQ)
#define SIOCDIFADDR                     _IOW('i',11,struct tagIFREQ)
#define SIOCSIFADDR                     _IOW('i',12,struct tagIFREQ)
#define SIOCGIFADDR                     _IOWR('i',13,struct tagIFREQ)
#define SIOCSIFDSTADDR                  _IOW('i',14,struct tagIFREQ)
#define SIOCGIFDSTADDR                  _IOWR('i',15,struct tagIFREQ)
#define SIOCSIFLOCADDR                  _IOWR('i',16,struct tagIFREQ)
#define SIOCSIFFLAGS                    _IOW('i',17,struct tagIFREQ)
#define SIOCGIFFLAGS                    _IOWR('i',18,struct tagIFREQ)
#define SIOCGIFBRDADDR                  _IOWR('i',19,struct tagIFREQ)
#define SIOCSIFBRDADDR                  _IOW('i',20,struct tagIFREQ)
#define SIOCGIFCONF                     _IOWR('i',21,struct tagIFREQ)
#define SIOCGIFNETMASK                  _IOWR('i',22,struct tagIFREQ)
#define SIOCSIFNETMASK                  _IOW('i',23,struct tagIFREQ)
#define SIOCGIFMTU                      _IOWR('i',24,struct tagIFREQ)
#define SIOCSIFMTU                      _IOW('i',25,struct tagIFREQ)
#define SIOCGIFMRU                      _IOWR('i',26,struct tagIFREQ)
#define SIOCSIFMRU                      _IOW('i',27,struct tagIFREQ)
#define SIOCGIFMETRIC               _IOW('i',28,struct tagIFREQ)
#define SIOCSIFMETRIC               _IOW('i',29,struct tagIFREQ)
#define SIOCADDMULTI                _IOW('i',30,struct tagIFREQ)
#define SIOCDELMULTI                _IOW('i',31,struct tagIFREQ)
#define SIOCGHWADDR                 _IOWR('i',32,struct tagIFREQ)
#define SIOCSHWADDR                 _IOW('i',33,struct tagIFREQ)
#define SIOCGIFMADDRLEN             _IOWR('i',34,struct tagIFREQ)
#define SIOCGIFMHDRLEN              _IOWR('i',35,struct tagIFREQ)
#define SIOCGIFBAUDRATE             _IOWR('i',36,struct tagIFREQ)
#define SIOCGIFETHCHIPSET           _IOWR('i',37,struct tagIFREQ)
/*----------------------------------------------------------------------*/
/* Definitions for ARP entries                                          */
/*----------------------------------------------------------------------*/
#define SIOCSARP                        _IOW('i',38,struct tagIFREQ)
#define SIOCGARP                        _IOWR('i',39,struct tagIFREQ)
#define SIOCDARP                        _IOW('i',40,struct tagIFREQ)

#define SIOCDIFDSTADDR                  _IOW('i',41,struct tagIFREQ)
/* The under commands are used start/halt/get net protocol */
/*
#define SIOCSNETPROTO                   _IOW('i',42,LONG)
#define SIOCHNETPROTO                   _IOW('i',43,LONG)
#define SIOCGNETPROTO                   _IOR('i',44,LONG)
#define SIOCSIPXFRAMETYPE               _IOW('i',45,LONG)
#define SIOCGIPXFRAMETYPE               _IOW('i',46,LONG)
#define SIOCSIPXFRAMEIF                 _IOW('i',47,LONG)
#define SIOCGIPXFRAMEIF                 _IOW('i',48,LONG)
#define SIOCHIPXFRAMEIF                 _IOW('i',49,LONG)
#define SIOCSIFUP                       _IOW('i',50,LONG)
#define SIOCSIFDOWN                     _IOW('i',51,LONG)
*/




/*----------------------------------------------------------------------*/
/* Definitions for Interface Group MIB variables                        */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIFNUMBER           _IOMR('m',1,NIMIB)
#define SIOCGIFTABLE            _IOMR('m',2,NIMIB)
#define SIOCGIFINDEX            _IOMR('m',3,NIMIB)
#define SIOCGIFDESCR            _IOMR('m',4,NIMIB)
#define SIOCGIFTYPE             _IOMR('m',5,NIMIB)
#define SIOCGIFMTUNIT           _IOMR('m',6,NIMIB)
#define SIOCGIFSPEED            _IOMR('m',7,NIMIB)
#define SIOCGIFPHYSADDRESS      _IOMR('m',8,NIMIB)
#define SIOCGIFADMINSTATUS      _IOMR('m',9,NIMIB)
#define SIOCGIFOPERSTATUS       _IOMR('m',10,NIMIB)
#define SIOCGIFLASTCHANGE       _IOMR('m',11,NIMIB)
#define SIOCGIFINOCTETS         _IOMR('m',12,NIMIB)
#define SIOCGIFINUCASTPKTS      _IOMR('m',13,NIMIB)
#define SIOCGIFINNUCASTPKTS     _IOMR('m',14,NIMIB)
#define SIOCGIFINDISCARDS       _IOMR('m',15,NIMIB)
#define SIOCGIFINERRORS         _IOMR('m',16,NIMIB)
#define SIOCGIFINUNKNOWNPROTOS  _IOMR('m',17,NIMIB)
#define SIOCGIFOUTOCTETS        _IOMR('m',18,NIMIB) 
#define SIOCGIFOUTUCASTPKTS     _IOMR('m',19,NIMIB)
#define SIOCGIFOUTNUCASTPKTS    _IOMR('m',20,NIMIB)
#define SIOCGIFOUTDISCARDS      _IOMR('m',21,NIMIB)
#define SIOCGIFOUTERRORS        _IOMR('m',22,NIMIB)
#define SIOCGIFOUTQLEN          _IOMR('m',23,NIMIB)
#define SIOCGIFSPECIFIC         _IOMR('m',24,NIMIB)

/*----------------------------------------------------------------------*/
/* set command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIFADMINSTATUS      _IOMW('m',1,NIMIB)

/* This is ethernet mib access command */

#define SIOCGMTETHSTATTABLE             _IOMR('m',1,ETHMIB)
#define SIOCGMTALIGERRORS               _IOMR('m',2,ETHMIB)
#define SIOCGMTFCSERRORS                _IOMR('m',3,ETHMIB)
#define SIOCGMTSINGCOLLFRAMES           _IOMR('m',4,ETHMIB)
#define SIOCGMTMULTCOLLFRAMES           _IOMR('m',5,ETHMIB)
#define SIOCGMTSQETESTERRORS            _IOMR('m',6,ETHMIB)
#define SIOCGMTDEFERTRANSMISSIONS       _IOMR('m',7,ETHMIB)
#define SIOCGMTLATECOLLISIONS           _IOMR('m',8,ETHMIB)
#define SIOCGMTEXCECOLLISIONS           _IOMR('m',9,ETHMIB)
#define SIOCGMTINTMACTRANSERRORS        _IOMR('m',10,ETHMIB)
#define SIOCGMTCARRSENSERRORS           _IOMR('m',11,ETHMIB)
#define SIOCGMTFRAMTOOLONGS             _IOMR('m',12,ETHMIB)
#define SIOCGMTINTMACRECVERRORS         _IOMR('m',13,ETHMIB)
#define SIOCGMTETHCHIPSET               _IOMR('m',14,ETHMIB)

#define  SIOCGMTETHCOLLTABLE            _IOMR('m',15,ETHMIB)
#define  SIOCGMTCOLLFREQ                _IOMR('m',16,ETHMIB)

/*    This is used by linwei    */
/*  232-port-table    ( get )    */
#define     SIOCG232PORTTABLE           _IOMR('m',1,SERMIB)    
#define     SIOCG232NUMBER              _IOMR('m',2,SERMIB)
#define     SIOCG232PORTINDEX           _IOMR('m',3,SERMIB)
#define     SIOCG232PORTTYPE            _IOMR('m',4,SERMIB)
#define     SIOCG232PORTINSIGNUM        _IOMR('m',5,SERMIB)
#define     SIOCG232PORTOUTSIGNUM       _IOMR('m',6,SERMIB)
#define     SIOCG232PORTINSPEED         _IOMR('m',7,SERMIB)
#define     SIOCG232PORTOUTSPEED        _IOMR('m',8,SERMIB)
#define     SIOCG232PORTINFLOWTYPE      _IOMR('m',9,SERMIB)
#define     SIOCG232PORTOUTFLOWTYPE     _IOMR('m',10,SERMIB)
/*  232-port-table    ( set )    */
#define     SIOCS232PORTINSPEED         _IOMW('m',7,SERMIB)
#define     SIOCS232PORTOUTSPEED        _IOMW('m',8,SERMIB)
#define     SIOCS232PORTINFLOWTYPE      _IOMW('m',9,SERMIB)
#define     SIOCS232PORTOUTFLOWTYPE     _IOMW('m',10,SERMIB)

/*  232-AsyncPortTable (get)    */
#define     SIOCG232ASYNPORTTABLE       _IOMR('m',11,SERMIB)
#define     SIOCG232ASYNINDEX           _IOMR('m',12,SERMIB)
#define     SIOCG232ASYNBITS            _IOMR('m',13,SERMIB)
#define     SIOCG232ASYNSTOPBITS        _IOMR('m',14,SERMIB)
#define     SIOCG232ASYNPARITY          _IOMR('m',15,SERMIB)
#define     SIOCG232ASYNAUTOBAUD        _IOMR('m',16,SERMIB)
#define     SIOCG232ASYNPARITYERRS      _IOMR('m',17,SERMIB)
#define     SIOCG232ASYNFRAMERRS        _IOMR('m',18,SERMIB)
#define     SIOCG232ASYNOVERRUNERRS     _IOMR('m',19,SERMIB)
/*  232-AsyncPortTable (set)    */
#define     SIOCS232ASYNBITS            _IOMW('m',13,SERMIB)
#define     SIOCS232ASYNSTOPBITS        _IOMW('m',14,SERMIB)
#define     SIOCS232ASYNPARITY          _IOMW('m',15,SERMIB)
#define     SIOCS232ASYNAUTOBAUD        _IOMW('m',16,SERMIB)

/*  232-SyncPortTable  (get)    */
#define     SIOCG232SYNPORTTABLE        _IOMR('m',20,SERMIB)
#define     SIOCG232SYNINDEX            _IOMR('m',21,SERMIB)
#define     SIOCG232SYNCLOCKSOURCE      _IOMR('m',22,SERMIB)
#define     SIOCG232SYNFRAMECHKERRS     _IOMR('m',23,SERMIB)
#define     SIOCG232SYNTRSUNDERRUN      _IOMR('m',24,SERMIB)
#define     SIOCG232SYNRCVOVERRUN       _IOMR('m',25,SERMIB)
#define     SIOCG232SYNINTFRAMES        _IOMR('m',26,SERMIB)
#define     SIOCG232SYNABORTEDFRAME     _IOMR('m',27,SERMIB)
#define     SIOCG232SYNROLE             _IOMR('m',28,SERMIB)
#define     SIOCG232SYNENCODING         _IOMR('m',29,SERMIB)
#define     SIOCG232SYNRTSCONTROL       _IOMR('m',30,SERMIB)
#define     SIOCG232SYNRCDELAY          _IOMR('m',31,SERMIB)
#define     SIOCG232SYNMODE             _IOMR('m',32,SERMIB)
#define     SIOCG232SYNIDLEPAT          _IOMR('m',33,SERMIB)
#define     SIOCG232SYNMINFLAG          _IOMR('m',34,SERMIB)
/*    232-SyncPortTable  (set)    */
#define     SIOCS232SYNCLOCKSOURCE      _IOMW('m',22,SERMIB)
#define     SIOCS232SYNROLE             _IOMW('m',28,SERMIB)
#define     SIOCS232SYNENCODING         _IOMW('m',29,SERMIB)
#define     SIOCS232SYNRTSCONTROL       _IOMW('m',30,SERMIB)
#define     SIOCS232SYNRCDELAY          _IOMW('m',31,SERMIB)
#define     SIOCS232SYNMODE             _IOMW('m',32,SERMIB)
#define     SIOCS232SYNIDLEPAT          _IOMW('m',33,SERMIB)
#define     SIOCS232SYNMINFLAG          _IOMW('m',34,SERMIB)

/* 232-InSigPortTable      (get)        */
#define        SIOCGINSIGPORTTABLE            0X40096D90
#define     SIOCGINSIGINDEX             0X40096D91
#define     SIOCGINSIGNAME              0X40096D92
#define     SIOCGINSIGSTATE             0X40096D93
#define     SIOCGINSIGCHANGE            0X40096D94

/* 232-OutSigPortTable      (get)        */
#define        SIOCGOUTSIGPORTTABLE        0X40096DA0
#define     SIOCGOUTSIGINDEX            0X40096DA1
#define     SIOCGOUTSIGNAME             0X40096DA2
#define     SIOCGOUTSIGSTATE            0X40096DA3
#define     SIOCGOUTSIGCHANGE           0X40096DA4 

/* This is PPP mib                                  */
#define SIOCGPPPLINKSTATUSTABLE _IOMR('m',1,PPPMIB)
#define SIOCGPPPPHYINDEX        _IOMR('m',2,PPPMIB)
#define SIOCGPPPBADADDR         _IOMR('m',3,PPPMIB)
#define SIOCGPPPBADCTL          _IOMR('m',4,PPPMIB)
#define SIOCGPPPPACTOOLONG      _IOMR('m',5,PPPMIB)
#define SIOCGPPPBADFCS          _IOMR('m',6,PPPMIB)
#define SIOCGPPPLOCMRU          _IOMR('m',7,PPPMIB)
#define SIOCGPPPRMTMRU          _IOMR('m',8,PPPMIB)
#define SIOCGSENDACCMAP         _IOMR('m',9,PPPMIB)
#define SIOCGPPPRECVACCMAP      _IOMR('m',10,PPPMIB)
#define SIOCGPPPLOCPCMP         _IOMR('m',11,PPPMIB)
#define SIOCGPPPRMTPCMP         _IOMR('m',12,PPPMIB)
#define SIOCGPPPLOCACCMP        _IOMR('m',13,PPPMIB)
#define SIOCGPPPRMTACCMP        _IOMR('m',14,PPPMIB)
#define SIOCGPPPSENDFCSSIZE     _IOMR('m',15,PPPMIB)
#define SIOCGPPPRECVFCSSIZE     _IOMR('m',16,PPPMIB)
#define    SIOCGPPPSENDACCMAP    _IOMR('m',17,PPPMIB)    
    

/*----------------------------------------------------------------------*/
/* Definitions for IP Group MIB variables                               */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPFORWARDING       _IOMR('m',1,IPMIB)
#define SIOCGIPDEFAULTTTL       _IOMR('m',2,IPMIB)
#define SIOCGIPINRECEIVES       _IOMR('m',3,IPMIB)
#define SIOCGIPINHDRERRORS      _IOMR('m',4,IPMIB)
#define SIOCGIPINADDRERRORS     _IOMR('m',5,IPMIB)
#define SIOCGIPFORWDATAGRAMS    _IOMR('m',6,IPMIB)
#define SIOCGIPINUNKNOWNPROTOS  _IOMR('m',7,IPMIB)
#define SIOCGIPINDISCARDS       _IOMR('m',8,IPMIB)
#define SIOCGIPINDELIVERS       _IOMR('m',9,IPMIB)
#define SIOCGIPOUTREQUESTS      _IOMR('m',10,IPMIB)
#define SIOCGIPOUTDISCARDS      _IOMR('m',11,IPMIB)
#define SIOCGIPOUTNOROUTES      _IOMR('m',12,IPMIB)
#define SIOCGIPREASMTIMEOUT     _IOMR('m',13,IPMIB)
#define SIOCGIPREASMREQDS       _IOMR('m',14,IPMIB)
#define SIOCGIPREASMOKS         _IOMR('m',15,IPMIB)
#define SIOCGIPREASMFAILS       _IOMR('m',16,IPMIB)
#define SIOCGIPFRAGOKS          _IOMR('m',17,IPMIB)
#define SIOCGIPFRAGFAILS        _IOMR('m',18,IPMIB)
#define SIOCGIPFRAGCREATES      _IOMR('m',19,IPMIB)
#define SIOCGIPROUTINGDISCARDS  _IOMR('m',20,IPMIB)
/*    This is defined by wang    sheng    */
#define    SIOCGIPTOOSHORT        _IOMR('m',21,IPMIB)
#define    SIOCGIPTOOSMALL        _IOMR('m',22,IPMIB)
#define    SIOCGIPBADVERSIONS    _IOMR('m',23,IPMIB)
#define    SIOCGIPBADCHECKSUM    _IOMR('m',24,IPMIB)
#define    SIOCGIPBADLEN        _IOMR('m',25,IPMIB)
#define SIOCGIPBADHLEN      _IOMR('m',26,IPMIB)
#define SIOCGIPBADOPTIONS   _IOMR('m',27,IPMIB)
#define SIOCGIPFRAGTIMEOUT  _IOMR('m',28,IPMIB)
#define SIOCGIPRAWOUT       _IOMR('m',29,IPMIB)

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPFORWARDING       _IOMW('m',1,IPMIB)
#define SIOCSIPDEFAULTTTL       _IOMW('m',2,IPMIB)

/*----------------------------------------------------------------------*/
/* Definitions for IP NI Address Table                                  */
/* GET commands definitions                                             */
/*----------------------------------------------------------------------*/
#define SIOCGIPADDRTABLE            _IOMR('m',1,IPATMIB)
#define SIOCGIPADDRENTADDR          _IOMR('m',2,IPATMIB)
#define SIOCGIPADDRENTIFINDEX       _IOMR('m',3,IPATMIB)
#define SIOCGIPADDRENTNETMASK       _IOMR('m',4,IPATMIB)
#define SIOCGIPADDRENTBCASTADDR        _IOMR('m',5,IPATMIB)
#define SIOCGIPADDRENTREASMMAXSIZE     _IOMR('m',6,IPATMIB)

/*----------------------------------------------------------------------*/
/* Definitions for IP route table                                       */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPROUTETABLE       _IOMR('m',1,IPRTMIB)
#define SIOCGIPROUTEDEST        _IOMR('m',2,IPRTMIB)
#define SIOCGIPROUTEIFINDEX     _IOMR('m',3,IPRTMIB)
#define SIOCGIPROUTENEXTHOP     _IOMR('m',4,IPRTMIB)
#define SIOCGIPROUTETYPE        _IOMR('m',5,IPRTMIB)
#define SIOCGIPROUTEPROTO       _IOMR('m',6,IPRTMIB)
#define SIOCGIPROUTEAGE         _IOMR('m',7,IPRTMIB)
#define SIOCGIPROUTEMASK        _IOMR('m',8,IPRTMIB)

/*    This is defined by lin wei    */
#define    SIOCGIPROUTEBADREDIRECT    _IOMR('m',9,IPRTMIB)
#define    SIOCGIPROUTEDYNAMIC    _IOMR('m',10,IPRTMIB)
#define    SIOCGIPNEWGATEWAY    _IOMR('m',11,IPRTMIB)
#define    SIOCGIPROUTEUNREACH    _IOMR('m',12,IPRTMIB)
#define    SIOCGIPROUTEWILDCARD    _IOMR('m',13,IPRTMIB)
#define SIOCGIPROUTEMETRIC1     _IOMR('m',14,IPRTMIB)
#define SIOCGIPROUTEMETRIC2     _IOMR('m',15,IPRTMIB)
#define SIOCGIPROUTEMETRIC3     _IOMR('m',16,IPRTMIB)
#define SIOCGIPROUTEMETRIC4     _IOMR('m',17,IPRTMIB)
#define SIOCGIPROUTEMETRIC5     _IOMR('m',18,IPRTMIB)


/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPROUTEDEST        _IOMW('m',1,IPRTMIB)
#define SIOCSIPROUTEIFINDEX     _IOMW('m',2,IPRTMIB)
#define SIOCSIPROUTENEXTHOP     _IOMW('m',3,IPRTMIB)
#define SIOCSIPROUTETYPE        _IOMW('m',4,IPRTMIB)
#define SIOCSIPROUTEAGE         _IOMW('m',5,IPRTMIB)
#define SIOCSIPROUTEMASK        _IOMW('m',6,IPRTMIB)
#define SIOCSIPROUTEMETRIC1     _IOMW('m',7,IPRTMIB)
#define SIOCSIPROUTEMETRIC2     _IOMW('m',8,IPRTMIB)
#define SIOCSIPROUTEMETRIC3     _IOMW('m',9,IPRTMIB)
#define SIOCSIPROUTEMETRIC4     _IOMW('m',10,IPRTMIB)
#define SIOCSIPROUTEMETRIC5     _IOMW('m',11,IPRTMIB)
/*----------------------------------------------------------------------*/
/* Definitions for IP NET-TO-MEDIA table                                */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGIPNETTOMEDIATABLE          _IOMR('m',1,IPNMMIB)
#define SIOCGIPNETTOMEDIAIFINDEX        _IOMR('m',2,IPNMMIB)
#define SIOCGIPNETTOMEDIAPHYSADDRESS    _IOMR('m',3,IPNMMIB)
#define SIOCGIPNETTOMEDIANETADDRESS     _IOMR('m',4,IPNMMIB)
#define SIOCGIPNETTOMEDIATYPE           _IOMR('m',5,IPNMMIB)


/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSIPNETTOMEDIAPHYSADDRESS    _IOMW('m',1,IPNMMIB)
#define SIOCSIPNETTOMEDIANETADDRESS     _IOMW('m',2,IPNMMIB)
#define SIOCSIPNETTOMEDIATYPE           _IOMW('m',3,IPNMMIB)
#define SIOCSIPNETTOMEDIAIFINDEX        _IOMW('m',4,IPNMMIB)
#define SIOCSATIFINDEX                  _IOMW('m',5,IPNMMIB)
#define SIOCSATNETADDRESS               _IOMW('m',6,IPNMMIB)

/*----------------------------------------------------------------------*/
/* Definitions for ICMP Group MIB variables                             */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGICMPINMSGS             _IOMR('m',1,ICMPMIB)
#define SIOCGICMPINERRORS           _IOMR('m',2,ICMPMIB)
#define SIOCGICMPINDESTUNREACHS     _IOMR('m',3,ICMPMIB)
#define SIOCGICMPINTIMEEXCDS        _IOMR('m',4,ICMPMIB)
#define SIOCGICMPINPARAMPROBS       _IOMR('m',5,ICMPMIB)
#define SIOCGICMPINSRCQUENCHS       _IOMR('m',6,ICMPMIB)
#define SIOCGICMPINREDIRECTS        _IOMR('m',7,ICMPMIB)
#define SIOCGICMPINECHOS            _IOMR('m',8,ICMPMIB)
#define SIOCGICMPINECHOREPS         _IOMR('m',9,ICMPMIB)
#define SIOCGICMPINTIMESTAMPS       _IOMR('m',10,ICMPMIB)
#define SIOCGICMPINTIMESTAMPREPS        _IOMR('m',11,ICMPMIB)
#define SIOCGICMPINADDRMASKS        _IOMR('m',12,ICMPMIB)
#define SIOCGICMPINADDRMASKREPS     _IOMR('m',13,ICMPMIB)
#define SIOCGICMPOUTMSGS            _IOMR('m',14,ICMPMIB)
#define SIOCGICMPOUTERRORS          _IOMR('m',15,ICMPMIB)
#define SIOCGICMPOUTDESTUNREACHS        _IOMR('m',16,ICMPMIB)
#define SIOCGICMPOUTTIMEEXCDS       _IOMR('m',17,ICMPMIB)
#define SIOCGICMPOUTPARAMPROBS      _IOMR('m',18,ICMPMIB)
#define SIOCGICMPOUTSRCQUENCHS      _IOMR('m',19,ICMPMIB)
#define SIOCGICMPOUTREDIRECTS       _IOMR('m',20,ICMPMIB)
#define SIOCGICMPOUTECHOS           _IOMR('m',21,ICMPMIB)
#define SIOCGICMPOUTECHOREPS        _IOMR('m',22,ICMPMIB)
#define SIOCGICMPOUTTIMESTAMPS      _IOMR('m',23,ICMPMIB)
#define SIOCGICMPOUTTIMESTAMPREPS       _IOMR('m',24,ICMPMIB)
#define SIOCGICMPOUTADDRMASKS       _IOMR('m',25,ICMPMIB)
#define SIOCGICMPOUTADDRMASKREPS        _IOMR('m',26,ICMPMIB)
/*    This is defined by wang sheng    */
#define    SIOCGICMPINBADCODE        _IOMR('m',27,ICMPMIB)
#define    SIOCGICMPINBADLEN        _IOMR('m',28,ICMPMIB)
#define    SIOCGICMPINCHECKSUM        _IOMR('m',29,ICMPMIB)
#define    SIOCGICMPINTOOSHORT        _IOMR('m',30,ICMPMIB)
#define    SIOCGICMPOUTOLDICMP        _IOMR('m',31,ICMPMIB)
#define    SIOCGICMPOUTOLDSHORT        _IOMR('m',32,ICMPMIB)


/*----------------------------------------------------------------------*/
/* Definitions for UDP MIB variables                                    */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGUDPINDATAGRAMS     _IOMR('m',1,UDPMIB)
#define SIOCGUDPNOPORTS         _IOMR('m',2,UDPMIB)
#define SIOCGUDPINERRORS        _IOMR('m',3,UDPMIB)
#define SIOCGUDPOUTDATAGRAMS    _IOMR('m',4,UDPMIB)
#define SIOCGUDPTABLE           _IOMR('m',5,UDPMIB)

/*----------------------------------------------------------------------*/
/* Definitions for TCP Group MIB variables                              */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCGTCPRTOALGORITHM    _IOMR('m',1,TCPMIB)
#define SIOCGTCPRTOMIN          _IOMR('m',2,TCPMIB)
#define SIOCGTCPRTOMAX          _IOMR('m',3,TCPMIB)
#define SIOCGTCPMAXCONN         _IOMR('m',4,TCPMIB)
#define SIOCGTCPACTIVEOPENS     _IOMR('m',5,TCPMIB)
#define SIOCGTCPPASSIVEOPENS    _IOMR('m',6,TCPMIB)
#define SIOCGTCPATTEMPTFAILS    _IOMR('m',7,TCPMIB)
#define SIOCGTCPESTABRESETS     _IOMR('m',8,TCPMIB)
#define SIOCGTCPCURRESTAB       _IOMR('m',9,TCPMIB)
#define SIOCGTCPINSEGS          _IOMR('m',10,TCPMIB)
#define SIOCGTCPOUTSEGS         _IOMR('m',11,TCPMIB)
#define SIOCGTCPRETRANSSEGS     _IOMR('m',12,TCPMIB)
#define SIOCGTCPCONNTABLE       _IOMR('m',13,TCPMIB)
#define SIOCGTCPCONNSTATE       _IOMR('m',14,TCPMIB)
#define SIOCGTCPINERRS          _IOMR('m',15,TCPMIB)
#define SIOCGTCPOUTRSTS         _IOMR('m',16,TCPMIB)

/*----------------------------------------------------------------------*/
/* SET command definitions                                              */
/*----------------------------------------------------------------------*/
#define SIOCSTCPCONNSTATE       _IOMW('m',14,TCPMIB)

/*----------------------------------------------------------------------*/
/* Definitions for Frame Relay Group MIB variables                      */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/

/* The under command are to GET MIB variables from frDlcmiTable.*/
#define SIOCGDLCMITABLE         _IOMR('m',1,FRMIB)

#define SIOCGDLCMISTATE         _IOMR('m',2,FRMIB)
#define SIOCGDLCMIADDR          _IOMR('m',3,FRMIB)
#define SIOCGDLCMIADDRLEN       _IOMR('m',4,FRMIB)
#define SIOCGDLCMIPOLLINGINT    _IOMR('m',5,FRMIB)
#define SIOCGDLCMIFULLENQINT    _IOMR('m',6,FRMIB)

#define SIOCGDLCMIERRTHRESHOLD  _IOMR('m',7,FRMIB)
#define SIOCGDLCMIMONEVENTS     _IOMR('m',8,FRMIB)
#define SIOCGDLCMIMAXSUPVCS     _IOMR('m',9,FRMIB)
#define SIOCGDLCMIMULTICAST     _IOMR('m',10,FRMIB)

/* The under command are to SET MIB variables from frDlcmiTable.*/
#define SIOCSDLCMISTATE         _IOMW('m',2,FRMIB)
#define SIOCSDLCMIADDR          _IOMW('m',3,FRMIB)
#define SIOCSDLCMIADDRLEN       _IOMW('m',4,FRMIB)
#define SIOCSDLCMIPOLLINGINT    _IOMW('m',5,FRMIB)
#define SIOCSDLCMIFULLENQINT    _IOMW('m',6,FRMIB)

#define SIOCSDLCMIERRTHRESHOLD  _IOMW('m',7,FRMIB)
#define SIOCSDLCMIMONEVENTS     _IOMW('m',8,FRMIB)
#define SIOCSDLCMIMAXSUPVCS     _IOMW('m',9,FRMIB)
#define SIOCSDLCMIMULTICAST     _IOMW('m',10,FRMIB)
/********************************************************************/

/* The under command are to GET MIB variables from frCircuitTable.*/
#define SIOCGCIRCUITTABLE       _IOMR('m',11,FRMIB)

#define SIOCGCIRCUDLCI          _IOMR('m',12,FRMIB)
#define SIOCGCIRCUSTATE         _IOMR('m',13,FRMIB)
#define SIOCGCIRCURECVFECNS     _IOMR('m',14,FRMIB)
#define SIOCGCIRCURECVBECNS     _IOMR('m',15,FRMIB)
#define SIOCGCIRCUSENTFRAMES    _IOMR('m',16,FRMIB)

#define SIOCGCIRCUSENTOCTETS    _IOMR('m',17,FRMIB)
#define SIOCGCIRCURECVFRAMES    _IOMR('m',18,FRMIB)
#define SIOCGCIRCURECVOCTETS    _IOMR('m',19,FRMIB)
#define SIOCGCIRCUCREATTIME     _IOMR('m',20,FRMIB)
#define SIOCGCIRCULASTCHANGE    _IOMR('m',21,FRMIB)
    
#define SIOCGCIRCUCOMMITBURST   _IOMR('m',22,FRMIB)
#define SIOCGCIRCUEXCESSBURST   _IOMR('m',23,FRMIB)
#define SIOCGCIRCUTHROUGHPUT    _IOMR('m',24,FRMIB)

/* The under command are to SET variables.*/
#define SIOCSCIRCUSTATE         _IOMW('m',13,FRMIB)
#define SIOCSCIRCUCOMMITBURST   _IOMW('m',22,FRMIB)
#define SIOCSCIRCUEXCESSBURST   _IOMW('m',23,FRMIB)
#define SIOCSCIRCUTHROUGHPUT    _IOMW('m',24,FRMIB)

/***********************************************************************/

/* The under command are to get MIB variables from frErrTable.*/
#define SIOCGFRERRTABLE         _IOMR('m',25,FRMIB)

#define SIOCGFRERRTYPE          _IOMR('m',26,FRMIB)
#define SIOCGFRERRDATA          _IOMR('m',27,FRMIB)
#define SIOCGFRERRTIME          _IOMR('m',28,FRMIB)

/************************************************************************/

/* The under command are used to get/set MIB variables in FRDte-MIB. */
#define SIOCGFRTRAPSTATE        _IOMR('m',30,FRMIB)
#define SIOCSFRTRAPSTATE        _IOMW('m',30,FRMIB)

#define SIOCGDLCMITABLENUM      _IOMR('m',31,FRMIB)
#define SIOCGCIRCUITTABLENUM    _IOMR('m',32,FRMIB)
#define SIOCGFRERRTABLENUM      _IOMR('m',33,FRMIB)

/*************************************************************
 * define the command to access viables in ISDN MIB
 * added by guxuguang  98.3.16
 ************************************************************/
#define  SIOCGDEMANDNBRTABLE               _IOMR('m',1,ISNMIB)
#define  SIOCGDEMANDNBRLOGIF               _IOMR('m',2,ISNMIB) 
#define  SIOCGDEMANDNBRNAME                _IOMR('m',3,ISNMIB) 
#define  SIOCGDEMANDNBRADDRESS             _IOMR('m',4,ISNMIB)
#define  SIOCGDEMANDNBRPERMISSION          _IOMR('m',5,ISNMIB)
#define  SIOCGDEMANDNBRMAXDURATION         _IOMR('m',6,ISNMIB)
#define  SIOCGDEMANDNBRLASTDURATION        _IOMR('m',7,ISNMIB)
#define  SIOCGDEMANDNBRCLEARREASON         _IOMR('m',8,ISNMIB)
#define  SIOCGDEMANDNBRCLEACODE            _IOMR('m',9,ISNMIB)
#define  SIOCGDEMANDNBRSUCCESSCALLS        _IOMR('m',10,ISNMIB) 
#define  SIOCGDEMANDNBRFAILCALLS           _IOMR('m',11,ISNMIB) 
#define  SIOCGDEMANDNBRACCEPTCALLS         _IOMR('m',12,ISNMIB)
#define  SIOCGDEMANDNBRREFUSECALLS         _IOMR('m',13,ISNMIB)
#define  SIOCGDEMANDNBRLASTATTEMPTTIME     _IOMR('m',14,ISNMIB)
#define  SIOCGDEMANDNBRCALLORIGIN          _IOMR('m',15,ISNMIB) 

/* define the set command */
#define  SIOCSDEMANDNBRLOGIF               _IOMW('m',1,ISNMIB)
#define  SIOCSDEMANDNBRNAME                _IOMW('m',2,ISNMIB)
#define  SIOCSDEMANDNBRADDRESS             _IOMW('m',3,ISNMIB)
#define  SIOCSDEMANDNBRPERMISSION          _IOMW('m',4,ISNMIB)
#define  SIOCSDEMANDNBRMAXDURATION         _IOMW('m',5,ISNMIB)


/******************************************************
 * define the command to access IPX MIB               *
 * added by guxuguang 98.3.16                         *
 ******************************************************/

/* read table command      */
#define SIOCGBASICSYSTABLE                         _IOMR('m',1,IPXMIB)
#define SIOCGADVSYSTABLE                           _IOMR('m',2,IPXMIB)
#define SIOCGCIRCTABLE                             _IOMR('m',3,IPXMIB)
#define SIOCGDESTTABLE                               _IOMR('m',4,IPXMIB)    
#define SIOCGSTATICROUTETABLE                      _IOMR('m',5,IPXMIB)
#define SIOCGSERVTABLE                             _IOMR('m',6,IPXMIB)
#define SIOCGDESTSERVTABLE                         _IOMR('m',7,IPXMIB)
#define SIOCGSTATICSERVTABLE                       _IOMR('m',8,IPXMIB)

/* read basicsys table command */            
#define SIOCGIPXBASICSYSEXISTSTATE                 _IOMR('m',9,IPXMIB)
#define SIOCGIPXBASICSYSNETNUMBER                  _IOMR('m',10,IPXMIB)
#define SIOCGIPXBASICSYSNODE                       _IOMR('m',11,IPXMIB)
#define SIOCGIPXBASICSYSNAME                       _IOMR('m',12,IPXMIB)
#define SIOCGIPXBASICSYSINHDRERRORS                _IOMR('m',13,IPXMIB)
#define SIOCGIPXBASICSYSINUNKNOWNSOCKETS           _IOMR('m',14,IPXMIB)  
#define SIOCGIPXBASICSYSINDISCARDS                 _IOMR('m',15,IPXMIB) 
#define SIOCGIPXBASICSYSINBADCHECKSUMS             _IOMR('m',16,IPXMIB)
#define SIOCGIPXBASICSYSINDELIVERS                 _IOMR('m',17,IPXMIB)
#define SIOCGIPXBASICSYSNOROUTES                   _IOMR('m',18,IPXMIB)
#define SIOCGIPXBASICSYSOUTREQUESTS                _IOMR('m',19,IPXMIB)
#define SIOCGIPXBASICSYSOUTMALFORMEDREQUESTS       _IOMR('m',20,IPXMIB)
#define SIOCGIPXBASICSYSOUTDISCARDS                _IOMR('m',21,IPXMIB)
#define SIOCGIPXBASICSYSOUTPACKETS                 _IOMR('m',22,IPXMIB)
#define SIOCGIPXBASICSYSCONFIGSOCKETS              _IOMR('m',23,IPXMIB)
#define SIOCGIPXBASICSYSOPENSOCKETFAILS            _IOMR('m',24,IPXMIB)

/* read advsys table command */
#define SIOCGIPXADVSYSMAXPATHSPLITS                _IOMR('m',25,IPXMIB)
#define SIOCGIPXADVSYSMAXHOPS                      _IOMR('m',26,IPXMIB)
#define SIOCGIPXADVSYSINTOOMANYHOPS                _IOMR('m',27,IPXMIB)
#define SIOCGIPXADVSYSINFILTERED                   _IOMR('m',28,IPXMIB)
#define SIOCGIPXADVSYSINCOMPRESSDISCARDS           _IOMR('m',29,IPXMIB)
#define SIOCGIPXADVSYSNETBIOSPACKETS               _IOMR('m',30,IPXMIB)
#define SIOCGIPXADVSYSFORWPACKETS                  _IOMR('m',31,IPXMIB)
#define SIOCGIPXADVSYSOUTFILTERED                  _IOMR('m',32,IPXMIB)
#define SIOCGIPXADVSYSOUTCOMPRESSDISCARDS          _IOMR('m',33,IPXMIB)
#define SIOCGIPXADVSYSCIRCCOUNT                    _IOMR('m',34,IPXMIB)
#define SIOCGIPXADVSYSDESTCOUNT                    _IOMR('m',35,IPXMIB)
#define SIOCGIPXADVSYSSERVCOUNT                    _IOMR('m',36,IPXMIB)
#define SIOCGIPXBASICSYSINRECEIVES                 _IOMR('m',37,IPXMIB) 

/* read circ talbe command */
#define SIOCGIPXCIRCEXISTSTATE                     _IOMR('m',40,IPXMIB)
#define SIOCGIPXCIRCOPERSTATE                      _IOMR('m',41,IPXMIB)
#define SIOCGIPXCIRCIFINDEX                        _IOMR('m',42,IPXMIB)
#define SIOCGIPXCIRCNAME                           _IOMR('m',43,IPXMIB)
#define SIOCGIPXCIRCDIALNAME                       _IOMR('m',44,IPXMIB)
#define SIOCGIPXCIRCLOCALMAXPACKETSIZE             _IOMR('m',45,IPXMIB)         
#define SIOCGIPXCIRCCOMPRESSSTATE                  _IOMR('m',46,IPXMIB)            
#define SIOCGIPXCIRCCOMPRESSSLOTS                  _IOMR('m',47,IPXMIB)         
#define SIOCGIPXCIRCSTATICSTATUS                   _IOMR('m',48,IPXMIB)           
#define SIOCGIPXCIRCCOMPRESSEDSENT                 _IOMR('m',49,IPXMIB)          
#define SIOCGIPXCIRCCOMPRESSEDINITSENT             _IOMR('m',50,IPXMIB)         
#define SIOCGIPXCIRCCOMPRESSEDREJECTSSENT          _IOMR('m',51,IPXMIB)                 
#define SIOCGIPXCIRCUNCOMPRESSEDSENT               _IOMR('m',52,IPXMIB)            
#define SIOCGIPXCIRCCOMPRESSEDRECEIVED             _IOMR('m',53,IPXMIB)         
#define SIOCGIPXCIRCCOMPRESSEDINITRECEIVED         _IOMR('m',54,IPXMIB)         
#define SIOCGIPXCIRCCOMPRESSEDREJECTSRECEIVED      _IOMR('m',55,IPXMIB)                  
#define SIOCGIPXCIRCUNCOMPRESSEDRECEIVED           _IOMR('m',56,IPXMIB)         
#define SIOCGIPXCIRCMEDIATYPE                      _IOMR('m',57,IPXMIB)         
#define SIOCGIPXCIRCNETNUMBER                      _IOMR('m',58,IPXMIB)         
#define SIOCGIPXCIRCSTATECHANGES                   _IOMR('m',59,IPXMIB) 
#define SIOCGIPXCIRCINITFAILS                      _IOMR('m',60,IPXMIB)
#define SIOCGIPXCIRCDELAY                          _IOMR('m',61,IPXMIB)
#define SIOCGIPXCIRCTHROUGHPUT                     _IOMR('m',62,IPXMIB)
#define SIOCGIPXCIRCNEIGHROUTERNAME                _IOMR('m',63,IPXMIB)  
#define SIOCGIPXCIRCNEIGHINTERNALNETNUM            _IOMR('m',64,IPXMIB) 
#define SIOCGIPXCIRCTYPE                           _IOMR('m',65,IPXMIB)

/* read dest table command */
#define SIOCGIPXDESTPROTOCOL                       _IOMR('m',70,IPXMIB)
#define SIOCGIPXDESTTICKS                          _IOMR('m',71,IPXMIB) 
#define SIOCGIPXDESTHOPCOUNT                       _IOMR('m',72,IPXMIB) 
#define SIOCGIPXDESTHOPCIRCINDEX                   _IOMR('m',73,IPXMIB)
#define SIOCGIPXDESTNEXTHOPNICADDRESS              _IOMR('m',74,IPXMIB)
#define SIOCGIPXDESTNEXTHOPNETNUM                  _IOMR('m',75,IPXMIB)

/* read staticroute table command */
#define SIOCGIPXSTATICROUTEEXISTSTATE              _IOMR('m',76,IPXMIB)
#define SIOCGIPXSTATICROUTETICKS                   _IOMR('m',77,IPXMIB)
#define SIOCGIPXSTATICROUTEHOPCOUNT                _IOMR('m',78,IPXMIB) 

/* read ser table command   */
#define SIOCGIPXSERVPROTOCOL                       _IOMR('m',80,IPXMIB)
#define SIOCGIPXSERVNETNUM                         _IOMR('m',81,IPXMIB) 
#define SIOCGIPXSERVNODE                           _IOMR('m',82,IPXMIB)
#define SIOCGIPXSERVSOCKET                         _IOMR('m',83,IPXMIB)
#define SIOCGIPXSERVHOPCOUNT                       _IOMR('m',84,IPXMIB)

/* read destser table command  */                
#define SIOCGIPXDESTSERVPROTOCOL                   _IOMR('m',85,IPXMIB)
#define SIOCGIPXDESTSERVHOPCOUNT                   _IOMR('m',86,IPXMIB) 
 
/* read staticser table command  */
#define SIOCGIPXSTATICSERVEXISTSTATE               _IOMR('m',87,IPXMIB)  
#define SIOCGIPXSTATICSERVNETNUM                   _IOMR('m',88,IPXMIB)
#define SIOCGIPXSTATICSERVNODE                     _IOMR('m',89,IPXMIB)
#define SIOCGIPXSTATICSERVSOCKET                   _IOMR('m',90,IPXMIB) 
#define SIOCGIPXSTATICSERVHOPCOUNT                 _IOMR('m',91,IPXMIB)

/* define the set command   */
#define SIOCSIPXBASICSYSEXISTSTATE                 _IOMW('m',1,IPXMIB)
#define SIOCSIPXBASICSYSNODE                       _IOMW('m',2,IPXMIB) 
#define SIOCSIPXBASICSYSNAME                       _IOMW('m',3,IPXMIB)

#define SIOCSIPXADVSYSMAXPATHSPLITS                _IOMW('m',4,IPXMIB)
#define SIOCSIPXADVSYSMAXHOPS                      _IOMW('m',5,IPXMIB)

#define SIOCSIPXCIRCEXISTSTATE                     _IOMW('m',6,IPXMIB)
#define SIOCSIPXCIRCOPERSTATE                      _IOMW('m',7,IPXMIB)
#define SIOCSIPXCIRCNAME                           _IOMW('m',8,IPXMIB)
#define SIOCSIPXCIRCDIALNAME                       _IOMW('m',9,IPXMIB)         

#define SIOCSIPXSTATICROUTEEXISTSTATE              _IOMW('m',10,IPXMIB)
#define SIOCSIPXSTATICROUTETICKS                   _IOMW('m',11,IPXMIB)
#define SIOCSIPXSTATICROUTEHOPCOUNT                _IOMW('m',12,IPXMIB)  

#define SIOCSIPXSTATICSERVEXISTSTATE               _IOMW('m',13,IPXMIB)
#define SIOCSIPXSTATICSERVNETNUM                   _IOMW('m',14,IPXMIB)
#define SIOCSIPXSTATICSERVNODE                     _IOMW('m',15,IPXMIB)
#define SIOCSIPXSTATICSERVSOCKET                   _IOMW('m',16,IPXMIB)
#define SIOCSIPXSTATICSERVHOPCOUNT                 _IOMW('m',17,IPXMIB)

#define SIOCGSERVTABLENUM                          _IOMR('m',100,IPXMIB)
#define SIOCGDESTSERVTABLENUM                      _IOMR('m',101,IPXMIB)
#define SIOCGSTATICSERVTABLENUM                    _IOMR('m',102,IPXMIB)

/*************************************************************
 * define the command to access viables in RIP MIB
 * added by YeYihe 98.9.3
 ************************************************************/
/************* define the command to read table *****************/
#define SIOCGRIP2IFSTATTABLE   _IOMW('m',0,RIPMIB)
#define SIOCGRIP2IFCONFTABLE   _IOMW('m',1,RIPMIB)
#define SIOCGRIP2PEERTABLE     _IOMW('m',2,RIPMIB)

/**************define the get command to scabular ifstattable*************/
#define SIOCGRIP2GLOBALROUTECHANGES         _IOMW('m',3,RIPMIB)
#define SIOCGRIP2GLOBALQUERIES              _IOMW('m',4,RIPMIB)

/**************define the get command to access ifstattable*************/
#define SIOCGRIP2IFSTATRCVBADPACKETS        _IOMW('m',5,RIPMIB)
#define SIOCGRIP2IFSTATRCVBADROUTES         _IOMW('m',6,RIPMIB)
#define SIOCGRIP2IFSTATSENTUPDATES          _IOMW('m',7,RIPMIB)
#define SIOCGRIP2IFSTATSTATUS               _IOMW('m',8,RIPMIB)

/***************define the get command to access ifconftable****************/
#define SIOCGRIP2IFCONFDOMAIN               _IOMW('m',9,RIPMIB)

#define SIOCGRIP2IFCONFAUTHTYPE             _IOMW('m',10,RIPMIB)
#define SIOCGRIP2IFCONFAUTHKEY              _IOMW('m',11,RIPMIB)
#define SIOCGRIP2IFCONFSEND                 _IOMW('m',12,RIPMIB)  
#define SIOCGRIP2IFCONFRECEIVE              _IOMW('m',13,RIPMIB)  
#define SIOCGRIP2IFCONFDEFAULTMETRIC        _IOMW('m',14,RIPMIB) 
#define SIOCGRIP2IFCONFSTATUS               _IOMW('m',15,RIPMIB)

/**************define the get command to access peertable*********************/
#define SIOCGRIP2PEERLASTUPDATE             _IOMW('m',16,RIPMIB) 
#define SIOCGRIP2PEERVERSION                _IOMW('m',17,RIPMIB) 
#define SIOCGRIP2PEERRCVBADPACKETS          _IOMW('m',18,RIPMIB)
#define SIOCGRIP2PEERRCVBADROUTES           _IOMW('m',19,RIPMIB)

/************define the set command **************************/
/* in the conftable */
#define SIOCSRIP2IFCONFAUTHTYPE          _IOMW('m',20,RIPMIB)
#define SIOCSRIP2IFCONFAUTHKEY           _IOMW('m',21,RIPMIB)    
#define SIOCSRIP2IFCONFSEND              _IOMW('m',22,RIPMIB) 
#define SIOCSRIP2IFCONFRECEIVE           _IOMW('m',23,RIPMIB)
#define SIOCSRIP2IFCONFDEFAULTMETRIC     _IOMW('m',24,RIPMIB) 
#define SIOCSRIP2IFCONFSTATUS            _IOMW('m',25,RIPMIB)
#define SIOCSRIP2IFCONFDOMAIN            _IOMW('m',26,RIPMIB)
/* in the rip2ifstattable*/
#define SIOCSRIP2IFSTATSTATUS            _IOMW('m',27,RIPMIB)

/************* define the command to read table number *****************/
#define SIOCGRIP2IFSTATTABLENUM   _IOMW('m',28,RIPMIB)
#define SIOCGRIP2IFCONFTABLENUM   _IOMW('m',29,RIPMIB)
#define SIOCGRIP2PEERTABLENUM     _IOMW('m',30,RIPMIB)

/******************************************************
 * define the command to access x25 MIB               *
 * added by liuwei 98.6.24                         *
 ******************************************************/

/*----------------------------------------------------------------------*/
/* Definitions for x25 MIB variables                                    */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/


/*READ TABLE COMMAND*/
 
/*NUM IS NOT SORTED 98.6.25*/
 
 #define SIOCGX25ADMNTABLE                _IOMR('m',1,X25MIB)
 #define SIOCGX25OPERTABLE                _IOMR('m',2,X25MIB)
 #define SIOCGX25STATTABLE                _IOMR('m',3,X25MIB)
 #define SIOCGX25CHANNELTABLE            _IOMR('m',4,X25MIB)
 #define SIOCGX25CIRCUITTABLE            _IOMR('m',5,X25MIB)
 #define SIOCGX25CLEAREDCIRCUITTABLE        _IOMR('m',6,X25MIB)
 #define SIOCGX25CALLPARMTABLE            _IOMR('m',7,X25MIB)

/*GET X.25 Administration Table COMMAND */    
 
 #define SIOCGX25ADMNINTERFACEMODE                       _IOMR('m',8,X25MIB) 
 #define SIOCGX25ADMNMAXACTIVECIRCUITS                   _IOMR('m',9,X25MIB) 
 #define SIOCGX25ADMNPACKETSEQUENCING                    _IOMR('m',10,X25MIB)
 #define SIOCGX25ADMNRESTARTTIMER                        _IOMR('m',11,X25MIB) 
 #define SIOCGX25ADMNCALLTIMER                           _IOMR('m',12,X25MIB) 
 #define SIOCGX25ADMNRESETTIMER                          _IOMR('m',13,X25MIB) 
 #define SIOCGX25ADMNCLEARTIMER                          _IOMR('m',14,X25MIB) 
 #define SIOCGX25ADMNWINDOWTIMER                         _IOMR('m',15,X25MIB)          
 #define SIOCGX25ADMNDATARXMTTIMER                       _IOMR('m',16,X25MIB)   
 #define SIOCGX25ADMNINTERRUPTTIMER                      _IOMR('m',17,X25MIB)  
 #define SIOCGX25ADMNREJECTTIMER                         _IOMR('m',18,X25MIB)         
 #define SIOCGX25ADMNREGISTRATIONREQUESTTIMER            _IOMR('m',19,X25MIB) 
 #define SIOCGX25ADMNMINIMUMRECALLTIMER                  _IOMR('m',20,X25MIB) 
 #define SIOCGX25ADMNRESTARTCOUNT                        _IOMR('m',21,X25MIB) 
 #define SIOCGX25ADMNRESETCOUNT                          _IOMR('m',22,X25MIB)
 #define SIOCGX25ADMNCLEARCOUNT                          _IOMR('m',23,X25MIB)
 #define SIOCGX25ADMNDATARXMTCOUNT                       _IOMR('m',24,X25MIB)
 #define SIOCGX25ADMNREJECTCOUNT                         _IOMR('m',25,X25MIB) 
 #define SIOCGX25ADMNREGISTRATIONREQUESTCOUNT            _IOMR('m',26,X25MIB)
 #define SIOCGX25ADMNNUMBERPVCS                          _IOMR('m',27,X25MIB) 
 #define SIOCGX25ADMNDEFCALLPARAMID                      _IOMR('m',28,X25MIB)         
 #define SIOCGX25ADMNLOCALADDRESS                        _IOMR('m',29,X25MIB) 
 #define SIOCGX25ADMNPROTOCOLVERSIONSUPPORTED            _IOMR('m',30,X25MIB)     


/*READ X.25 Operational Table COMMAND*/
 
 #define SIOCGX25OPERINTERFACEMODE                       _IOMR('m',31,X25MIB) 
 #define SIOCGX25OPERMAXACTIVECIRCUITS                   _IOMR('m',32,X25MIB) 
 #define SIOCGX25OPERPACKETSEQUENCING                    _IOMR('m',33,X25MIB) 
 #define SIOCGX25OPERRESTARTTIMER                        _IOMR('m',34,X25MIB) 
 #define SIOCGX25OPERCALLTIMER                           _IOMR('m',35,X25MIB) 
 #define SIOCGX25OPERRESETTIMER                          _IOMR('m',36,X25MIB) 
 #define SIOCGX25OPERCLEARTIMER                          _IOMR('m',37,X25MIB) 
 #define SIOCGX25OPERWINDOWTIMER                         _IOMR('m',38,X25MIB) 
 #define SIOCGX25OPERDATARXMTTIMER                       _IOMR('m',39,X25MIB) 
 #define SIOCGX25OPERINTERRUPTTIMER                      _IOMR('m',40,X25MIB) 
 #define SIOCGX25OPERREJECTTIMER                         _IOMR('m',41,X25MIB) 
 #define SIOCGX25OPERREGISTRATIONREQUESTTIMER            _IOMR('m',42,X25MIB) 
 #define SIOCGX25OPERMINIMUMRECALLTIMER                  _IOMR('m',43,X25MIB) 
 #define SIOCGX25OPERRESTARTCOUNT                        _IOMR('m',44,X25MIB) 
 #define SIOCGX25OPERRESETCOUNT                     _IOMR('m',45,X25MIB) 
 #define SIOCGX25OPERCLEARCOUNT                          _IOMR('m',46,X25MIB) 
 #define SIOCGX25OPERDATARXMTCOUNT                       _IOMR('m',47,X25MIB) 
 #define SIOCGX25OPERREJECTCOUNT                         _IOMR('m',48,X25MIB) 
 #define SIOCGX25OPERREGISTRATIONREQUESTCOUNT            _IOMR('m',49,X25MIB) 
 #define SIOCGX25OPERNUMBERPVCS                          _IOMR('m',50,X25MIB) 
 #define SIOCGX25OPERDEFCALLPARAMID                      _IOMR('m',51,X25MIB) 
 #define SIOCGX25OPERLOCALADDRESS                        _IOMR('m',52,X25MIB) 
 #define SIOCGX25OPERDATALINKID                          _IOMR('m',53,X25MIB) 
 #define SIOCGX25OPERPROTOCOLVERSIONSUPPORTED            _IOMR('m',54,X25MIB)      
      
/*  READ X.25 Statistics Table COMMAND*/

 #define SIOCGX25STATINCALLS                             _IOMR('m',55,X25MIB) 
 #define SIOCGX25STATINCALLREFUSALS                      _IOMR('m',56,X25MIB) 
 #define SIOCGX25STATINPROVIDERINITIATEDCLEARS           _IOMR('m',57,X25MIB) 
 #define SIOCGX25STATINREMOTELYINITIATEDRESETS           _IOMR('m',58,X25MIB) 
 #define SIOCGX25STATINPROVIDERINITIATEDRESETS           _IOMR('m',59,X25MIB) 
 #define SIOCGX25STATINRESTARTS                          _IOMR('m',60,X25MIB) 
 #define SIOCGX25STATINDATAPACKETS                       _IOMR('m',61,X25MIB) 
 #define SIOCGX25STATINACCUSEDOFPROTOCOLERRORS           _IOMR('m',62,X25MIB) 
 #define SIOCGX25STATININTERRUPTS                        _IOMR('m',63,X25MIB) 
 #define SIOCGX25STATOUTCALLATTEMPTS                     _IOMR('m',64,X25MIB) 
 #define SIOCGX25STATOUTCALLFAILURES                     _IOMR('m',65,X25MIB) 
 #define SIOCGX25STATOUTINTERRUPTS                       _IOMR('m',66,X25MIB) 
 #define SIOCGX25STATOUTDATAPACKETS                      _IOMR('m',67,X25MIB) 
 #define SIOCGX25STATOUTGOINGCIRCUITS                    _IOMR('m',68,X25MIB) 
 #define SIOCGX25STATINCOMINGCIRCUITS                    _IOMR('m',69,X25MIB) 
 #define SIOCGX25STATTWOWAYCIRCUITS                      _IOMR('m',70,X25MIB) 
 #define SIOCGX25STATRESTARTTIMEOUTS                     _IOMR('m',71,X25MIB) 
 #define SIOCGX25STATCALLTIMEOUTS                        _IOMR('m',72,X25MIB)
 #define SIOCGX25STATRESETTIMEOUTS                       _IOMR('m',73,X25MIB) 
 #define SIOCGX25STATCLEARTIMEOUTS                       _IOMR('m',74,X25MIB) 
 #define SIOCGX25STATDATARXMTTIMEOUTS                    _IOMR('m',75,X25MIB) 
 #define SIOCGX25STATINTERRUPTTIMEOUTS                   _IOMR('m',76,X25MIB) 
 #define SIOCGX25STATRETRYCOUNTEXCEEDEDS                 _IOMR('m',77,X25MIB) 
 #define SIOCGX25STATCLEARCOUNTEXCEEDEDS                 _IOMR('m',78,X25MIB) 

/*READ X.25 Channel Table COMMAND*/
 
 #define SIOCGX25CHANNELLIC                                _IOMR('m',79,X25MIB) 
 #define SIOCGX25CHANNELHIC                                _IOMR('m',80,X25MIB) 
 #define SIOCGX25CHANNELLTC                                _IOMR('m',81,X25MIB) 
 #define SIOCGX25CHANNELHTC                                _IOMR('m',82,X25MIB) 
 #define SIOCGX25CHANNELLOC                                _IOMR('m',83,X25MIB) 
 #define SIOCGX25CHANNELHOC                                _IOMR('m',84,X25MIB) 

/*READ  X25 Per Circuits Information Table COMMAND*/

 
 #define SIOCGX25CIRCUITSTATUS                           _IOMR('m',85,X25MIB) 
 #define SIOCGX25CIRCUITESTABLISHTIME                    _IOMR('m',86,X25MIB) 
 #define SIOCGX25CIRCUITDIRECTION                        _IOMR('m',87,X25MIB) 
 #define SIOCGX25CIRCUITINOCTETS                         _IOMR('m',88,X25MIB) 
 #define SIOCGX25CIRCUITINPDUS                           _IOMR('m',89,X25MIB) 
 #define SIOCGX25CIRCUITINREMOTELYINITIATEDRESETS        _IOMR('m',90,X25MIB) 
 #define SIOCGX25CIRCUITINPROVIDERINITIATEDRESETS        _IOMR('m',91,X25MIB) 
 #define SIOCGX25CIRCUITININTERRUPTS                     _IOMR('m',92,X25MIB) 
 #define SIOCGX25CIRCUITOUTOCTETS                        _IOMR('m',93,X25MIB) 
 #define SIOCGX25CIRCUITOUTPDUS                          _IOMR('m',94,X25MIB) 
 #define SIOCGX25CIRCUITOUTINTERRUPTS                    _IOMR('m',95,X25MIB) 
 #define SIOCGX25CIRCUITDATARETRANSMISSIONTIMEOUTS       _IOMR('m',96,X25MIB) 
 #define SIOCGX25CIRCUITRESETTIMEOUTS                    _IOMR('m',97,X25MIB) 
 #define SIOCGX25CIRCUITINTERRUPTTIMEOUTS                _IOMR('m',98,X25MIB) 
 #define SIOCGX25CIRCUITCALLPARAMID                      _IOMR('m',99,X25MIB)      
 #define SIOCGX25CIRCUITCALLEDDTEADDRESS                 _IOMR('m',100,X25MIB) 
 #define SIOCGX25CIRCUITCALLINGDTEADDRESS                _IOMR('m',101,X25MIB) 
 #define SIOCGX25CIRCUITORIGINALLYCALLEDADDRESS          _IOMR('m',102,X25MIB) 
 #define SIOCGX25CIRCUITDESCR                            _IOMR('m',103,X25MIB) 

/*READ X.25     The Cleared Circuit Table COMMAND*/


 #define SIOCGX25CLEAREDCIRCUITPLEINDEX                  _IOMR('m',104,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITTIMEESTABLISHED           _IOMR('m',105,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITTIMECLEARED               _IOMR('m',106,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITCHANNEL                   _IOMR('m',107,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITCLEARINGCAUSE             _IOMR('m',108,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITDIAGNOSTICCODE            _IOMR('m',109,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITINPDUS                    _IOMR('m',110,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITOUTPDUS                   _IOMR('m',111,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITCALLEDADDRESS             _IOMR('m',112,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITCALLINGADDRESS            _IOMR('m',113,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITCLEARFACILITIES           _IOMR('m',114,X25MIB) 

/*READ X.25The Call Parameter Table COMMAND*/

 #define SIOCGX25CALLPARMSTATUS                          _IOMR('m',115,X25MIB) 
 #define SIOCGX25CALLPARMREFCOUNT                        _IOMR('m',116,X25MIB) 
 #define SIOCGX25CALLPARMINPACKETSIZE                    _IOMR('m',117,X25MIB) 
 #define SIOCGX25CALLPARMOUTPACKETSIZE                   _IOMR('m',118,X25MIB) 
 #define SIOCGX25CALLPARMINWINDOWSIZE                    _IOMR('m',119,X25MIB) 
 #define SIOCGX25CALLPARMOUTWINDOWSIZE                   _IOMR('m',120,X25MIB) 
 #define SIOCGX25CALLPARMACCEPTREVERSECHARGING           _IOMR('m',121,X25MIB) 
 #define SIOCGX25CALLPARMPROPOSEREVERSECHARGING          _IOMR('m',122,X25MIB) 
 #define SIOCGX25CALLPARMFASTSELECT                      _IOMR('m',123,X25MIB) 
 #define SIOCGX25CALLPARMINTHRUPUTCLASSIZE               _IOMR('m',124,X25MIB) 
 #define SIOCGX25CALLPARMOUTTHRUPUTCLASSIZE              _IOMR('m',125,X25MIB) 
 #define SIOCGX25CALLPARMCUG                             _IOMR('m',126,X25MIB) 
 #define SIOCGX25CALLPARMCUGOA                           _IOMR('m',127,X25MIB) 
 #define SIOCGX25CALLPARMBCUG                            _IOMR('m',128,X25MIB) 
 #define SIOCGX25CALLPARMNUI                             _IOMR('m',129,X25MIB) 
 #define SIOCGX25CALLPARMCHARGINGINFO                    _IOMR('m',130,X25MIB) 
 #define SIOCGX25CALLPARMRPOA                            _IOMR('m',131,X25MIB) 
 #define SIOCGX25CALLPARMTRNSTDLY                        _IOMR('m',132,X25MIB) 
 #define SIOCGX25CALLPARMCALLINGEXT                      _IOMR('m',133,X25MIB) 
 #define SIOCGX25CALLPARMCALLEDEXT                       _IOMR('m',134,X25MIB) 
 #define SIOCGX25CALLPARMINMINTHUPUTCLS                  _IOMR('m',135,X25MIB) 
 #define SIOCGX25CALLPARMOUTMINTHUPUTCLS                 _IOMR('m',136,X25MIB) 
 #define SIOCGX25CALLPARMENDTRNSDLY                      _IOMR('m',137,X25MIB) 
 #define SIOCGX25CALLPARMPRIORITY                        _IOMR('m',138,X25MIB) 
 #define SIOCGX25CALLPARMPROTECTION                      _IOMR('m',139,X25MIB) 
 #define SIOCGX25CALLPARMEXPTDATA                        _IOMR('m',140,X25MIB) 
 #define SIOCGX25CALLPARMUSERDATA                        _IOMR('m',141,X25MIB) 
 #define SIOCGX25CALLPARMCALLINGNETWORKFACILITIES        _IOMR('m',142,X25MIB) 
 #define SIOCGX25CALLPARMCALLEDNETWORKFACILITIES         _IOMR('m',143,X25MIB) 

 #define SIOCGX25CLEAREDCIRCUITENTRIESREQUESTED             _IOMR('m',144,X25MIB) 
 #define SIOCGX25CLEAREDCIRCUITENTRIESGRANTED             _IOMR('m',145,X25MIB) 
/********************************************************* 
         define the set command 
**********************************************************/


/*SET X.25 Administration Table COMMAND */    
 
 #define SIOCSX25ADMNINTERFACEMODE                       _IOMW('m',145+1,X25MIB) 
 #define SIOCSX25ADMNMAXACTIVECIRCUITS                   _IOMW('m',145+2,X25MIB) 
 #define SIOCSX25ADMNPACKETSEQUENCING                    _IOMW('m',145+3,X25MIB) 
 #define SIOCSX25ADMNRESTARTTIMER                        _IOMW('m',145+4,X25MIB) 
 #define SIOCSX25ADMNCALLTIMER                           _IOMW('m',145+5,X25MIB) 
 #define SIOCSX25ADMNRESETTIMER                          _IOMW('m',145+6,X25MIB) 
 #define SIOCSX25ADMNCLEARTIMER                          _IOMW('m',145+7,X25MIB) 
 #define SIOCSX25ADMNWINDOWTIMER                         _IOMW('m',145+8,X25MIB)          
 #define SIOCSX25ADMNDATARXMTTIMER                       _IOMW('m',145+9,X25MIB)   
 #define SIOCSX25ADMNINTERRUPTTIMER                      _IOMW('m',145+10,X25MIB)  
 #define SIOCSX25ADMNREJECTTIMER                         _IOMW('m',145+11,X25MIB)         
 #define SIOCSX25ADMNREGISTRATIONREQUESTTIMER            _IOMW('m',145+12,X25MIB) 
 #define SIOCSX25ADMNMINIMUMRECALLTIMER                  _IOMW('m',145+13,X25MIB) 
 #define SIOCSX25ADMNRESTARTCOUNT                        _IOMW('m',145+14,X25MIB) 
 #define SIOCSX25ADMNRESETCOUNT                          _IOMW('m',145+15,X25MIB) 
 #define SIOCSX25ADMNCLEARCOUNT                          _IOMW('m',145+16,X25MIB) 
 #define SIOCSX25ADMNDATARXMTCOUNT                       _IOMW('m',145+17,X25MIB) 
 #define SIOCSX25ADMNREJECTCOUNT                         _IOMW('m',145+18,X25MIB) 
 #define SIOCSX25ADMNREGISTRATIONREQUESTCOUNT            _IOMW('m',145+19,X25MIB) 
 #define SIOCSX25ADMNNUMBERPVCS                          _IOMW('m',145+20,X25MIB) 
 #define SIOCSX25ADMNDEFCALLPARAMID                      _IOMW('m',145+21,X25MIB)         
 #define SIOCSX25ADMNLOCALADDRESS                        _IOMW('m',145+22,X25MIB) 
 #define SIOCSX25ADMNPROTOCOLVERSIONSUPPORTED            _IOMW('m',145+23,X25MIB)     

 /*SET X.25 Channel Table COMMAND*/
 #define SIOCSX25CHANNELLIC                                _IOMW('m',145+24,X25MIB) 
 #define SIOCSX25CHANNELHIC                                _IOMW('m',145+25,X25MIB) 
 #define SIOCSX25CHANNELLTC                                _IOMW('m',145+26,X25MIB) 
 #define SIOCSX25CHANNELHTC                                _IOMW('m',145+27,X25MIB) 
 #define SIOCSX25CHANNELLOC                                _IOMW('m',145+28,X25MIB) 
 #define SIOCSX25CHANNELHOC                                _IOMW('m',145+29,X25MIB) 

/*set  X25 Per Circuits Information Table COMMAND*/

 #define SIOCSX25CIRCUITSTATUS                           _IOMW('m',145+30,X25MIB) 
 #define SIOCSX25CIRCUITDIRECTION                        _IOMW('m',145+31,X25MIB)  
 #define SIOCSX25CIRCUITCALLEDDTEADDRESS                 _IOMW('m',145+32,X25MIB) 
 #define SIOCSX25CIRCUITCALLINGDTEADDRESS                _IOMW('m',145+33,X25MIB) 
 #define SIOCSX25CIRCUITORIGINALLYCALLEDADDRESS          _IOMW('m',145+34,X25MIB) 
 #define SIOCSX25CIRCUITDESCR                            _IOMW('m',145+35,X25MIB) 


/*SET X.25The Call Parameter Table COMMAND*/

 #define SIOCSX25CALLPARMSTATUS                          _IOMW('m',145+36,X25MIB)  
 #define SIOCSX25CALLPARMINPACKETSIZE                    _IOMW('m',145+37,X25MIB) 
 #define SIOCSX25CALLPARMOUTPACKETSIZE                   _IOMW('m',145+38,X25MIB) 
 #define SIOCSX25CALLPARMINWINDOWSIZE                    _IOMW('m',145+39,X25MIB) 
 #define SIOCSX25CALLPARMOUTWINDOWSIZE                   _IOMW('m',145+40,X25MIB) 
 #define SIOCSX25CALLPARMACCEPTREVERSECHARGING           _IOMW('m',145+41,X25MIB) 
 #define SIOCSX25CALLPARMPROPOSEREVERSECHARGING          _IOMW('m',145+42,X25MIB) 
 #define SIOCSX25CALLPARMFASTSELECT                      _IOMW('m',145+43,X25MIB) 
 #define SIOCSX25CALLPARMINTHRUPUTCLASSIZE               _IOMW('m',145+44,X25MIB) 
 #define SIOCSX25CALLPARMOUTTHRUPUTCLASSIZE              _IOMW('m',145+45,X25MIB) 
 #define SIOCSX25CALLPARMCUG                             _IOMW('m',145+46,X25MIB) 
 #define SIOCSX25CALLPARMCUGOA                           _IOMW('m',145+47,X25MIB) 
 #define SIOCSX25CALLPARMBCUG                            _IOMW('m',145+48,X25MIB) 
 #define SIOCSX25CALLPARMNUI                             _IOMW('m',145+49,X25MIB) 
 #define SIOCSX25CALLPARMCHARGINGINFO                    _IOMW('m',145+50,X25MIB) 
 #define SIOCSX25CALLPARMRPOA                            _IOMW('m',145+51,X25MIB) 
 #define SIOCSX25CALLPARMTRNSTDLY                        _IOMW('m',145+52,X25MIB) 
 #define SIOCSX25CALLPARMCALLINGEXT                      _IOMW('m',145+53,X25MIB) 
 #define SIOCSX25CALLPARMCALLEDEXT                       _IOMW('m',145+54,X25MIB) 
 #define SIOCSX25CALLPARMINMINTHUPUTCLS                  _IOMW('m',145+55,X25MIB) 
 #define SIOCSX25CALLPARMOUTMINTHUPUTCLS                 _IOMW('m',145+56,X25MIB) 
 #define SIOCSX25CALLPARMENDTRNSDLY                      _IOMW('m',145+57,X25MIB) 
 #define SIOCSX25CALLPARMPRIORITY                        _IOMW('m',145+58,X25MIB) 
 #define SIOCSX25CALLPARMPROTECTION                      _IOMW('m',145+59,X25MIB) 
 #define SIOCSX25CALLPARMEXPTDATA                        _IOMW('m',145+60,X25MIB) 
 #define SIOCSX25CALLPARMUSERDATA                        _IOMW('m',145+61,X25MIB) 
 #define SIOCSX25CALLPARMCALLINGNETWORKFACILITIES        _IOMW('m',145+62,X25MIB) 
 #define SIOCSX25CALLPARMCALLEDNETWORKFACILITIES         _IOMW('m',145+63,X25MIB) 
 #define SIOCSX25CLEAREDCIRCUITENTRIESREQUESTED             _IOMW('m',145+64,X25MIB)

/* Get Max Number of every table:---------------------------------------*/
#define  SIOCGX25ADMNTABLENUM                            _IOMR('m',145+65,X25MIB)
#define  SIOCGX25OPERTABLENUM                            _IOMR('m',145+66,X25MIB)
#define  SIOCGX25STATTABLENUM                            _IOMR('m',145+67,X25MIB)
#define  SIOCGX25CHANNELTABLENUM                         _IOMR('m',145+68,X25MIB)
#define  SIOCGX25CLEAREDCIRCUITTABLENUM                  _IOMR('m',145+69,X25MIB)
#define  SIOCGX25CALLPARMTABLENUM                        _IOMR('m',145+70,X25MIB)
#define  SIOCGX25CIRCUITTABLENUM                         _IOMR('m',145+71,X25MIB)

/******************************************************
 * define the command to access lapb MIB               *
 * added by liuwei 98.7.16                         *
 ******************************************************/

/*----------------------------------------------------------------------*/
/* Definitions for lapb MIB variables                                    */
/* GET command definitions                                              */
/*----------------------------------------------------------------------*/


/*READ TABLE COMMAND*/

#define      SIOCGLAPBADMNTABLE                    _IOMR('m',1,LAPBMIB)  
#define      SIOCGLAPBOPERTABLE                    _IOMR('m',2,LAPBMIB)  
#define      SIOCGLAPBFLOWTABLE                    _IOMR('m',3,LAPBMIB)  
#define      SIOCGLAPBXIDTABLE                    _IOMR('m',4,LAPBMIB)  

/*Get LAPB Administration Table COMMAND */

#define     SIOCGLAPBADMNSTATIONTYPE                    _IOMR('m',5,LAPBMIB)     
#define     SIOCGLAPBADMNCONTROLFIELD                   _IOMR('m',6,LAPBMIB)         
#define     SIOCGLAPBADMNTRANSMITN1FRAMESIZE                  _IOMR('m',7,LAPBMIB) 
#define      SIOCGLAPBADMNRECEIVEN1FRAMESIZE             _IOMR('m',8,LAPBMIB) 
#define     SIOCGLAPBADMNTRANSMITKWINDOWSIZE            _IOMR('m',9,LAPBMIB) 
#define     SIOCGLAPBADMNRECEIVEKWINDOWSIZE             _IOMR('m',10,LAPBMIB) 
#define     SIOCGLAPBADMNN2RXMITCOUNT               _IOMR('m',11,LAPBMIB) 
#define     SIOCGLAPBADMNT1ACKTIMER                 _IOMR('m',12,LAPBMIB) 
#define        SIOCGLAPBADMNT2ACKDELAYTIMER              _IOMR('m',13,LAPBMIB) 
#define        SIOCGLAPBADMNT3DISCONNECTTIMER              _IOMR('m',14,LAPBMIB) 
#define        SIOCGLAPBADMNT4IDLETIMER                  _IOMR('m',15,LAPBMIB) 
#define     SIOCGLAPBADMNACTIONINITIATE           _IOMR('m',16,LAPBMIB) 
#define     SIOCGLAPBADMNACTIONRECVDM                 _IOMR('m',17,LAPBMIB) 

/*Get LAPB OPER Table COMMAND */

#define       SIOCGLAPBOPERSTATIONTYPE                _IOMR('m',18,LAPBMIB) 
#define       SIOCGLAPBOPERCONTROLFIELD               _IOMR('m',19,LAPBMIB) 
#define       SIOCGLAPBOPERTRANSMITN1FRAMESIZE            _IOMR('m',20,LAPBMIB)  
#define       SIOCGLAPBOPERRECEIVEN1FRAMESIZE             _IOMR('m',21,LAPBMIB) 
#define       SIOCGLAPBOPERTRANSMITKWINDOWSIZE            _IOMR('m',22,LAPBMIB) 
#define       SIOCGLAPBOPERRECEIVEKWINDOWSIZE             _IOMR('m',23,LAPBMIB) 
#define       SIOCGLAPBOPERN2RXMITCOUNT               _IOMR('m',24,LAPBMIB)  
#define       SIOCGLAPBOPERT1ACKTIMER                 _IOMR('m',25,LAPBMIB) 
#define       SIOCGLAPBOPERT2ACKDELAYTIMER            _IOMR('m',26,LAPBMIB) 
#define       SIOCGLAPBOPERT3DISCONNECTTIMER          _IOMR('m',27,LAPBMIB) 
#define       SIOCGLAPBOPERT4IDLETIMER                _IOMR('m',28,LAPBMIB) 
#define       SIOCGLAPBOPERPORTID                     _IOMR('m',29,LAPBMIB) 
#define       SIOCGLAPBOPERPROTOCOLVERSIONID              _IOMR('m',30,LAPBMIB) 

/*Get LAPB FLOW Table COMMAND */


#define       SIOCGLAPBFLOWSTATECHANGES               _IOMR('m',31,LAPBMIB) 
#define       SIOCGLAPBFLOWCHANGEREASON                 _IOMR('m',32,LAPBMIB) 
#define       SIOCGLAPBFLOWCURRENTMODE                 _IOMR('m',33,LAPBMIB) 
#define       SIOCGLAPBFLOWBUSYDEFERS                 _IOMR('m',34,LAPBMIB) 
#define       SIOCGLAPBFLOWREJOUTPKTS                 _IOMR('m',35,LAPBMIB) 
#define       SIOCGLAPBFLOWREJINPKTS                 _IOMR('m',36,LAPBMIB) 
#define       SIOCGLAPBFLOWT1TIMEOUTS                _IOMR('m',37,LAPBMIB) 
#define       SIOCGLAPBFLOWFRMRSENT                 _IOMR('m',38,LAPBMIB) 
#define       SIOCGLAPBFLOWFRMRRECEIVED                 _IOMR('m',39,LAPBMIB) 
#define       SIOCGLAPBFLOWXIDRECEIVED                 _IOMR('m',40,LAPBMIB) 

/*Get LAPB XID Table COMMAND */


#define        SIOCGLAPBXIDADRIDENTIFIER                _IOMR('m',41,LAPBMIB) 
#define       SIOCGLAPBXIDADRADDRESS                _IOMR('m',42,LAPBMIB) 
#define       SIOCGLAPBXIDPARAMETERUNIQUEIDENTIFIER        _IOMR('m',43,LAPBMIB) 
#define       SIOCGLAPBXIDGROUPADDRESS                _IOMR('m',44,LAPBMIB) 
#define       SIOCGLAPBXIDPORTNUMBER                _IOMR('m',45,LAPBMIB) 
#define       SIOCGLAPBXIDUSERDATASUBFIELD            _IOMR('m',46,LAPBMIB) 
   

/*Set LAPB Administration Table COMMAND */

#define     SIOCSLAPBADMNSTATIONTYPE                    _IOMW('m',47,LAPBMIB)    
#define     SIOCSLAPBADMNCONTROLFIELD                   _IOMW('m',48,LAPBMIB)        
#define     SIOCSLAPBADMNTRANSMITN1FRAMESIZE                _IOMW('m',49,LAPBMIB) 
#define     SIOCSLAPBADMNRECEIVEN1FRAMESIZE             _IOMW('m',50,LAPBMIB) 
#define     SIOCSLAPBADMNTRANSMITKWINDOWSIZE            _IOMW('m',51,LAPBMIB) 
#define     SIOCSLAPBADMNRECEIVEKWINDOWSIZE             _IOMW('m',52,LAPBMIB) 
#define     SIOCSLAPBADMNN2RXMITCOUNT               _IOMW('m',53,LAPBMIB) 
#define     SIOCSLAPBADMNT1ACKTIMER                 _IOMW('m',54,LAPBMIB) 
#define     SIOCSLAPBADMNT2ACKDELAYTIMER            _IOMW('m',55,LAPBMIB) 
#define     SIOCSLAPBADMNT3DISCONNECTTIMER          _IOMW('m',56,LAPBMIB) 
#define     SIOCSLAPBADMNT4IDLETIMER                _IOMW('m',57,LAPBMIB) 
#define     SIOCSLAPBADMNACTIONINITIATE           _IOMW('m',58,LAPBMIB) 
#define     SIOCSLAPBADMNACTIONRECVDM                 _IOMW('m',59,LAPBMIB) 

/*Set LAPB OPER Table COMMAND */

#define     SIOCSLAPBOPERT4IDLETIMER                _IOMW('m',60,LAPBMIB) 

/*Set LAPB XID Table COMMAND */


#define       SIOCSLAPBXIDADRIDENTIFIER               _IOMW('m',61,LAPBMIB) 
#define       SIOCSLAPBXIDADRADDRESS                _IOMW('m',62,LAPBMIB) 
#define       SIOCSLAPBXIDPARAMETERUNIQUEIDENTIFIER     _IOMW('m',63,LAPBMIB) 
#define       SIOCSLAPBXIDGROUPADDRESS              _IOMW('m',64,LAPBMIB) 
#define       SIOCSLAPBXIDPORTNUMBER                _IOMW('m',65,LAPBMIB) 
#define       SIOCSLAPBXIDUSERDATASUBFIELD          _IOMW('m',66,LAPBMIB) 

/*******************************************************************************
            Get  number of every mib table
*********************************************************************************/
#define      SIOCGLAPBADMNTABLENUM                      _IOMR('m',67,LAPBMIB)                           
#define      SIOCGLAPBOPERTABLENUM                      _IOMR('m',68,LAPBMIB)    
#define      SIOCGLAPBFLOWTABLENUM                      _IOMR('m',69,LAPBMIB)    
#define      SIOCGLAPBXIDTABLENUM                       _IOMR('m',70,LAPBMIB)


/* define ospf command */
#define SIOCGOSPFAREATABLENUM        _IOMR('m',9,OSPFMIB)
#define SIOCGOSPFAREATABLE        _IOMR('m',1,OSPFMIB) /* read AREA talbe */
#define SIOCGOSPFAUTHTYPE        _IOMR('m',2,OSPFMIB) /* read auth type */
#define SIOCGOSPFIMPORTASEEXTERN        _IOMR('m',3,OSPFMIB)  /* read ase extern */
#define SIOCGOSPFSPFRUNS        _IOMR('m',4,OSPFMIB)
#define SIOCGOSPFAREABDRCOUNT        _IOMR('m',5,OSPFMIB)
#define SIOCGOSPFASBDRRTRCOUNT        _IOMR('m',6,OSPFMIB)
#define SIOCGOSPFAREALSACOUNT        _IOMR('m',7,OSPFMIB)
#define SIOCGOSPFAREALSACKSUMSUM    _IOMR('m',8,OSPFMIB)


#define SIOCGOSPFSTUBAREATABLENUM    _IOMR('m',10,OSPFMIB)
#define SIOCGOSPFSTUBAREATABLE        _IOMR('m',11,OSPFMIB)
#define SIOCGOSPFSTUBMETRIC        _IOMR('m',12,OSPFMIB)
#define SIOCGOSPFSTUBSTATUS        _IOMR('m',13,OSPFMIB)


#define SIOCGOSPFLSDBTABLENUM        _IOMR('m',21,OSPFMIB)
#define SIOCGOSPFLSDBTABLE        _IOMR('m',22,OSPFMIB)
#define SIOCGOSPFLSDBSEQUENCE        _IOMR('m',23,OSPFMIB)
#define SIOCGOSPFLSDBAGE        _IOMR('m',24,OSPFMIB)
#define SIOCGOSPFLSDBCHECKSUM        _IOMR('m',25,OSPFMIB)
#define SIOCGOSPFLSDBADVERTISEMENT    _IOMR('m',26,OSPFMIB)


#define SIOCGOSPFAREARANGETABLENUM    _IOMR('m',31,OSPFMIB)
#define SIOCGOSPFAREARANGETABLE        _IOMR('m',32,OSPFMIB)
#define SIOCGOSPFAREARANGEMASK        _IOMR('m',33,OSPFMIB)
#define SIOCGOSPFAREARANGESTATUS    _IOMR('m',34,OSPFMIB)


#define SIOCGOSPFHOSTTABLENUM        _IOMR('m',41,OSPFMIB)
#define SIOCGOSPFHOSTTABLE        _IOMR('m',42,OSPFMIB)
#define SIOCGOSPFHOSTMETRIC        _IOMR('m',43,OSPFMIB)
#define SIOCGOSPFHOSTSTATUS        _IOMR('m',44,OSPFMIB)


#define SIOCGOSPFIFTABLENUM        _IOMR('m',51,OSPFMIB)
#define SIOCGOSPFIFTABLE        _IOMR('m',52,OSPFMIB)
#define SIOCGOSPFIFAREAID        _IOMR('m',53,OSPFMIB)
#define SIOCGOSPFIFTYPE            _IOMR('m',54,OSPFMIB)
#define SIOCGOSPFIFADMINSTAT        _IOMR('m',55,OSPFMIB)
#define SIOCGOSPFIFRTRPRIORITY        _IOMR('m',56,OSPFMIB)
#define SIOCGOSPFIFTRANSITDELAY        _IOMR('m',57,OSPFMIB)
#define SIOCGOSPFIFRETRANSINTERVAL    _IOMR('m',58,OSPFMIB)
#define SIOCGOSPFIFHELLOINTERVAL    _IOMR('m',59,OSPFMIB)
#define SIOCGOSPFIFRTRDEADINTERVAL    _IOMR('m',60,OSPFMIB)
#define SIOCGOSPFIFPOLLINTERVAL        _IOMR('m',61,OSPFMIB)
#define SIOCGOSPFIFSTATE        _IOMR('m',62,OSPFMIB)
#define SIOCGOSPFIFDESIGNATEDROUTER    _IOMR('m',63,OSPFMIB)
#define SIOCGOSPFIFBACKUPDESIGNATEDROUTER    _IOMR('m',64,OSPFMIB)
#define SIOCGOSPFIFEVENTS        _IOMR('m',65,OSPFMIB)
#define SIOCGOSPFIFAUTHKEY        _IOMR('m',66,OSPFMIB)


#define SIOCGOSPFIFMETRICTABLENUM    _IOMR('m',71,OSPFMIB)
#define SIOCGOSPFIFMETRICTABLE        _IOMR('m',72,OSPFMIB)
#define SIOCGOSPFIFMETRICMETRIC        _IOMR('m',73,OSPFMIB)
#define SIOCGOSPFIFMETRICSTATUS        _IOMR('m',74,OSPFMIB)


#define SIOCGOSPFVIRTIFTABLENUM        _IOMR('m',81,OSPFMIB)
#define SIOCGOSPFVIRTIFTABLE        _IOMR('m',82,OSPFMIB)
#define SIOCGOSPFVIRTIFTRANSITDELAY    _IOMR('m',83,OSPFMIB)
#define SIOCGOSPFVIRTIFRETRANSINTERVAL    _IOMR('m',84,OSPFMIB)
#define SIOCGOSPFVIRTIFHELOINTERVAL    _IOMR('m',85,OSPFMIB)
#define SIOCGOSPFVIRTIFRTRDEADINTERVAL    _IOMR('m',86,OSPFMIB)
#define SIOCGOSPFVIRTIFSTATE        _IOMR('m',87,OSPFMIB)
#define SIOCGOSPFVIRTIFEVENTS        _IOMR('m',88,OSPFMIB)
#define SIOCGOSPFVIRTIFAUTHKEY        _IOMR('m',89,OSPFMIB)
#define SIOCGOSPFVIRTIFSTATUS        _IOMR('m',90,OSPFMIB)


#define SIOCGOSPFNBRTABLENUM        _IOMR('m',91,OSPFMIB)
#define SIOCGOSPFNBRTABLE        _IOMR('m',92,OSPFMIB)
#define SIOCGOSPFNBRRTRID        _IOMR('m',93,OSPFMIB)
#define SIOCGOSPFNBROPTIONS        _IOMR('m',94,OSPFMIB)
#define SIOCGOSPFNBRPRIORITY        _IOMR('m',95,OSPFMIB)
#define SIOCGOSPFNBRSTATE        _IOMR('m',96,OSPFMIB)
#define SIOCGOSPFMNREVENTS        _IOMR('m',97,OSPFMIB)
#define SIOCGOSPFNBRLSRETRANSQLEN    _IOMR('m',98,OSPFMIB)
#define SIOCGOSPFNBMANBRSTATUS        _IOMR('m',99,OSPFMIB)


#define SIOCGOSPFVIRTNBRTABLENUM    _IOMR('m',101,OSPFMIB)
#define SIOCGOSPFVIRTNBRTABLE        _IOMR('m',102,OSPFMIB)
#define SIOCGOSPFVIRTNBRIPADDR        _IOMR('m',103,OSPFMIB)
#define SIOCGOSPFVIRTNBROPTIONS        _IOMR('m',104,OSPFMIB)
#define SIOCGOSPFVIRTNBRSTATE        _IOMR('m',105,OSPFMIB)
#define SIOCGOSPFVIRTNBREVENTS        _IOMR('m',106,OSPFMIB)
#define SIOCGOSPFVIRTNBRLSRETRANSQLEN    _IOMR('m',107,OSPFMIB)



/* Define 8040 privatiate MIB */
#ifdef _Q4500_
#define SIOCGMODULETABLE            _IOMR('m',1,MODULEMIB)
#define SIOCGMODULEINDEX            _IOMR('m',2,MODULEMIB)
#define SIOCGMODULESLOTNUM          _IOMR('m',3,MODULEMIB)
#define SIOCGMODULETYPE             _IOMR('m',4,MODULEMIB)
#define SIOCGMODULEFIRSTPORT        _IOMR('m',5,MODULEMIB)
#define SIOCGMODULEPORTNUM          _IOMR('m',6,MODULEMIB)
#define SIOCGMODULEVERSION          _IOMR('m',7,MODULEMIB)
#define SIOCGMODULEROUTERMEMORY     _IOMR('m',8,MODULEMIB)

#endif

/* define MIXINFO_MIB command */
#define SIOCGMODULEID                        _IOMR('m',1,MIXINFOMIB)
#define SIOCGROMID                           _IOMR('m',2,MIXINFOMIB)
#define SIOCGROMVERSION                      _IOMR('m',3,MIXINFOMIB)
#define SIOCGROMSYSVERSION                  _IOMR('m',4,MIXINFOMIB)
#define SIOCGPROCESSORRAM                   _IOMR('m',5,MIXINFOMIB)
#define SIOCGNVRAMSIZE                         _IOMR('m',6,MIXINFOMIB)
#define SIOCGNVRAMUSED                      _IOMR('m',7,MIXINFOMIB)
#define SIOCGCONFIGREGISTER                 _IOMR('m',8,MIXINFOMIB)
#define SIOCGCONFIGREGNEXT                  _IOMR('m',9,MIXINFOMIB)
#define SIOCGTFTPSTATUS                     _IOMR('m',10,MIXINFOMIB)
#define SIOCGFREEMEM                        _IOMR('m',11,MIXINFOMIB)
#define SIOCGBUSYPER                        _IOMR('m',12,MIXINFOMIB)
#define SIOCGAVGBUSY5                       _IOMR('m',13,MIXINFOMIB)

#define SIOCGFLASHSIZE                         _IOMR('m',14,MIXINFOMIB)
#define SIOCGFLASHFREE                      _IOMR('m',15,MIXINFOMIB)
#define SIOCGFLASHERASE                     _IOMR('m',16,MIXINFOMIB)
#define SIOCGFLASHERASETIME                 _IOMR('m',17,MIXINFOMIB)
#define SIOCGFLASHERASESTATUS               _IOMR('m',18,MIXINFOMIB)
#define SIOCGFLASHSTATUS                    _IOMR('m',19,MIXINFOMIB)
#define SIOCGFLASHENTRIES                   _IOMR('m',20,MIXINFOMIB)

#define SIOCGMEMORYPOOLUSED                 _IOMR('m',21,MIXINFOMIB)
#define SIOCGMEMORYPOOLFREE                    _IOMR('m',22,MIXINFOMIB)
#define SIOCGMEMORYPOOLLARGESTFREE             _IOMR('m',23,MIXINFOMIB)
#define SIOCGBUFFER32SIZE                      _IOMR('m',24,MIXINFOMIB)
#define SIOCGBUFFER32TOTAL                     _IOMR('m',25,MIXINFOMIB)
#define SIOCGBUFFER32FREE                      _IOMR('m',26,MIXINFOMIB)
#define SIOCGBUFFER32USED                      _IOMR('m',27,MIXINFOMIB)
#define SIOCGBUFFER32DROPCOUNTS                _IOMR('m',28,MIXINFOMIB)
#define SIOCGBUFFER32FREEERROR2             _IOMR('m',29,MIXINFOMIB)
#define SIOCGBUFFER32FREEERROR3                _IOMR('m',30,MIXINFOMIB)
#define SIOCGBUFFER32COLLECTCOUNTS             _IOMR('m',31,MIXINFOMIB)
#define SIOCGBUFFER64SIZE                      _IOMR('m',32,MIXINFOMIB)
#define SIOCGBUFFER64TOTAL                     _IOMR('m',33,MIXINFOMIB)
#define SIOCGBUFFER64FREE                      _IOMR('m',34,MIXINFOMIB)
#define SIOCGBUFFER64USED                      _IOMR('m',35,MIXINFOMIB)
#define SIOCGBUFFER64DROPCOUNTS                _IOMR('m',36,MIXINFOMIB)
#define SIOCGBUFFER64FREEERROR2                 _IOMR('m',37,MIXINFOMIB)
#define SIOCGBUFFER64FREEERROR3                _IOMR('m',38,MIXINFOMIB)
#define SIOCGBUFFER64COLLECTCOUNTS             _IOMR('m',39,MIXINFOMIB)
#define SIOCGBUFFER128SIZE                      _IOMR('m',40,MIXINFOMIB)
#define SIOCGBUFFER128TOTAL                     _IOMR('m',41,MIXINFOMIB)
#define SIOCGBUFFER128FREE                      _IOMR('m',42,MIXINFOMIB)
#define SIOCGBUFFER128USED                      _IOMR('m',43,MIXINFOMIB)
#define SIOCGBUFFER128DROPCOUNTS                _IOMR('m',44,MIXINFOMIB)
#define SIOCGBUFFER128FREEERROR2                _IOMR('m',45,MIXINFOMIB)   
#define SIOCGBUFFER128FREEERROR3                _IOMR('m',46,MIXINFOMIB)
#define SIOCGBUFFER128COLLECTCOUNTS             _IOMR('m',47,MIXINFOMIB)
#define SIOCGBUFFER256SIZE                      _IOMR('m',48,MIXINFOMIB)
#define SIOCGBUFFER256TOTAL                     _IOMR('m',49,MIXINFOMIB)
#define SIOCGBUFFER256FREE                      _IOMR('m',50,MIXINFOMIB)
#define SIOCGBUFFER256USED                      _IOMR('m',51,MIXINFOMIB)
#define SIOCGBUFFER256DROPCOUNTS                _IOMR('m',52,MIXINFOMIB)
#define SIOCGBUFFER256FREEERROR2               _IOMR('m',53,MIXINFOMIB)   
#define SIOCGBUFFER256FREEERROR3                _IOMR('m',54,MIXINFOMIB)
#define SIOCGBUFFER256COLLECTCOUNTS                _IOMR('m',55,MIXINFOMIB)  
#define SIOCGBUFFER512SIZE                        _IOMR('m',56,MIXINFOMIB)  
#define SIOCGBUFFER512TOTAL                      _IOMR('m',57,MIXINFOMIB)  
#define SIOCGBUFFER512FREE                       _IOMR('m',58,MIXINFOMIB)  
#define SIOCGBUFFER512USED                       _IOMR('m',59,MIXINFOMIB)  
#define SIOCGBUFFER512DROPCOUNTS                 _IOMR('m',60,MIXINFOMIB)  
#define SIOCGBUFFER512FREEERROR2                 _IOMR('m',61,MIXINFOMIB)   
#define SIOCGBUFFER512FREEERROR3                 _IOMR('m',62,MIXINFOMIB)  
#define SIOCGBUFFER512COLLECTCOUNTS              _IOMR('m',63,MIXINFOMIB)  
#define SIOCGBUFFER1024SIZE                     _IOMR('m',64,MIXINFOMIB)  
#define SIOCGBUFFER1024TOTAL                    _IOMR('m',65,MIXINFOMIB)  
#define SIOCGBUFFER1024FREE                     _IOMR('m',66,MIXINFOMIB)  
#define SIOCGBUFFER1024USED                     _IOMR('m',67,MIXINFOMIB)  
#define SIOCGBUFFER1024DROPCOUNTS               _IOMR('m',68,MIXINFOMIB)  
#define SIOCGBUFFER1024FREEERROR2              _IOMR('m',69,MIXINFOMIB)   
#define SIOCGBUFFER1024FREEERROR3               _IOMR('m',70,MIXINFOMIB)  
#define SIOCGBUFFER1024COLLECTCOUNTS            _IOMR('m',71,MIXINFOMIB)  
#define SIOCGBUFFER2048SIZE                      _IOMR('m',72,MIXINFOMIB)  
#define SIOCGBUFFER2048TOTAL                     _IOMR('m',73,MIXINFOMIB)
#define SIOCGBUFFER2048FREE                      _IOMR('m',74,MIXINFOMIB)
#define SIOCGBUFFER2048USED                      _IOMR('m',75,MIXINFOMIB)
#define SIOCGBUFFER2048DROPCOUNTS                _IOMR('m',76,MIXINFOMIB)
#define SIOCGBUFFER2048FREEERROR2               _IOMR('m',77,MIXINFOMIB)   
#define SIOCGBUFFER2048FREEERROR3                _IOMR('m',78,MIXINFOMIB)
#define SIOCGBUFFER2048COLLECTCOUNTS             _IOMR('m',79,MIXINFOMIB)
#define SIOCGBUFFER4096SIZE                      _IOMR('m',80,MIXINFOMIB)
#define SIOCGBUFFER4096TOTAL                     _IOMR('m',81,MIXINFOMIB)
#define SIOCGBUFFER4096FREE                      _IOMR('m',82,MIXINFOMIB)
#define SIOCGBUFFER4096USED                      _IOMR('m',83,MIXINFOMIB)
#define SIOCGBUFFER4096DROPCOUNTS                _IOMR('m',84,MIXINFOMIB)
#define SIOCGBUFFER4096FREEERROR2               _IOMR('m',85,MIXINFOMIB)   
#define SIOCGBUFFER4096FREEERROR3                _IOMR('m',86,MIXINFOMIB)
#define SIOCGBUFFER4096COLLECTCOUNTS             _IOMR('m',87,MIXINFOMIB)
#define SIOCGBUFFER8192SIZE                      _IOMR('m',88,MIXINFOMIB)
#define SIOCGBUFFER8192TOTAL                     _IOMR('m',89,MIXINFOMIB)
#define SIOCGBUFFER8192FREE                      _IOMR('m',90,MIXINFOMIB)
#define SIOCGBUFFER8192USED                      _IOMR('m',91,MIXINFOMIB)
#define SIOCGBUFFER8192DROPCOUNTS                _IOMR('m',92,MIXINFOMIB)
#define SIOCGBUFFER8192FREEERROR2               _IOMR('m',93,MIXINFOMIB)   
#define SIOCGBUFFER8192FREEERROR3                _IOMR('m',94,MIXINFOMIB)
#define SIOCGBUFFER8192COLLECTCOUNTS             _IOMR('m',95,MIXINFOMIB)
#define SIOCGBUFFER45KSIZE                      _IOMR('m',96,MIXINFOMIB)
#define SIOCGBUFFER45KTOTAL                     _IOMR('m',97,MIXINFOMIB)
#define SIOCGBUFFER45KFREE                      _IOMR('m',98,MIXINFOMIB)
#define SIOCGBUFFER45KUSED                      _IOMR('m',99,MIXINFOMIB)
#define SIOCGBUFFER45KDROPCOUNTS                _IOMR('m',100,MIXINFOMIB)
#define SIOCGBUFFER45KFREEERROR2               _IOMR('m',101,MIXINFOMIB)   
#define SIOCGBUFFER45KFREEERROR3                _IOMR('m',102,MIXINFOMIB)
#define SIOCGBUFFER45KCOLLECTCOUNTS             _IOMR('m',103,MIXINFOMIB)
#define SIOCGBUFFER256KSIZE                      _IOMR('m',104,MIXINFOMIB)
#define SIOCGBUFFER256KTOTAL                     _IOMR('m',105,MIXINFOMIB)
#define SIOCGBUFFER256KFREE                      _IOMR('m',106,MIXINFOMIB)
#define SIOCGBUFFER256KUSED                      _IOMR('m',107,MIXINFOMIB)
#define SIOCGBUFFER256KDROPCOUNTS                _IOMR('m',108,MIXINFOMIB)
#define SIOCGBUFFER256KFREEERROR2               _IOMR('m',109,MIXINFOMIB)   
#define SIOCGBUFFER256KFREEERROR3                _IOMR('m',110,MIXINFOMIB)
#define SIOCGBUFFER256KCOLLECTCOUNTS             _IOMR('m',111,MIXINFOMIB)

#define SIOCGBUFFERFAIL                        _IOMR('m',112,MIXINFOMIB)
#define SIOCGBUFFERNOMEM                       _IOMR('m',113,MIXINFOMIB)

#define SIOCGCONFIGFILERUNNINGLASTCHANGED       _IOMR('m',114,MIXINFOMIB)
#define SIOCGCONFIGFILERUNNINGLASTSAVED         _IOMR('m',115,MIXINFOMIB)
#define SIOCGCONFIGFILESTARTUPLASTCHANGED       _IOMR('m',116,MIXINFOMIB)
#define SIOCGNETCONFIGNAME                     _IOMR('m',117,MIXINFOMIB)
#define SIOCGHOSTCONFIGNAME                     _IOMR('m',118,MIXINFOMIB)


#define SIOCGCURRENTTIME                     _IOMR('m',119,MIXINFOMIB)
#define SIOCGSYSTEMTEMPERATURE               _IOMR('m',120,MIXINFOMIB)
#define SIOCGBUZZERSTATUS                    _IOMR('m',121,MIXINFOMIB)
#define SIOCGFANSTATUS                       _IOMR('m',122,MIXINFOMIB)


/*Set CURRENTTIME COMMAND */

#define     SIOCSCURRENTTIME                    _IOMW('m',123,MIXINFOMIB)    


#ifdef    __cplusplus
}

#endif    /* end of __cplusplus */

#endif
