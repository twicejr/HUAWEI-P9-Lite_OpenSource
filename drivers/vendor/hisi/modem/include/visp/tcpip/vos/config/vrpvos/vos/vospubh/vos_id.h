/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/25                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *  History：                                                           *
 *      VRP3R001M07，刘凯(L03198)，2002/10                              *
 *          --  增加了MID_IPHC和MID_VJCOMP的模块定义。这两个模块有单独的    *
 *              模块号，而没有和PPP模块使用相同的模块号                 *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/
#ifndef _VOS_ID_H_
#define _VOS_ID_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

/*Please include "BaseType.h" before this head-file. */

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

/*All type ID inside our VRP.*/


/*::All base types inSIDe BaseType.h.*/
#define SID_CHAR    0x1 /* CHAR      */
#define SID_UCHAR   0x2 /* UCHAR     */
#define SID_SHORT   0x3 /* SHORT     */
#define SID_USHORT  0x4 /* USHORT    */
#define SID_LONG    0x5 /* LONG      */
#define SID_ULONG   0x6 /* ULONG     */
#define SID_BOOL_T  0x7 /* BOOL_T    */
#define SID_SOCKADDR_S  0x8 /* SOCKADDR_S */


/*::VOS Module*/
#define SID_MBUF_S     0x100
#define SID_MBUF_DATABLOCKDESCRIPTOR_S      0x101
#define SID_VOS_MEMSIMPLEALLOC              0x102
#define SID_VOS_QUE         0x105
#define SID_VOS_TMR         0x106
#define SID_VOS_HASH        0x107
 
#define SID_VOS_NAME  0x110
#define SID_VOS_SELF_TASK_STACK 0x115
#define SID_VOS_SELF_TASK_NODE 0x116

#define SID_MEMSHOWMIB  0x129
#define SID_BUFSHOWMIB  0x117
#define SID_TASKSHOWMIB 0x124
#define SID_CPUSHOWMIB  0x127

#define SID_SEMA   0x119
#define SID_MEMSHOW 0x120
#define SID_TASKSHOW 0x121

/*add by xuying for BYDD00134*/
#define SID_MEMSHOW_USER 0x118
/*add over by xuying for BYDD00134*/

#define SID_SYSCMD 0x122

/*add by anhongjie for D21775*/
#define SID_MON_ASSERT 0x123
/*add by anhongjie for D21775*/

#define SID_VOS_MON_BUF  0x125
#define SID_VOS_MON_LOGFILE_BUF  0x126
#define SID_VOS_VFS_BUF  0x130

#define SID_IPC_DEBUG     0x131
#define SID_IPC_STAT       0x132


#define SID_MBUF_DEBUG    0x133
#define SID_MBUF_STAT      0x134

#define SID_RPC_MODULE    0x135

#if (VRP_VERSION_5 == VRP_YES)
#define SID_LCS_GET          0x136
#define SID_LCS_UPDATE       0x137
#define SID_LCS_HA           0x138
#define SID_LCS_SYN          0x139
#define SID_LCS_BUFFER       0x13A
#define SID_LCS_UPDATECB     0x13B

#define SID_PAF_GET          0x140
#define SID_PAF_UPDATE       0x141
#define SID_PAF_HA           0x142
#define SID_PAF_SYN          0x143
#define SID_PAF_BUFF         0x144

#define SID_SYSTRACE_CMD     0x14A
#define SID_SYSTRACE_BUFFER  0x14B
#endif

/*IFNET module*/
#define SID_IFNET_S     0x150
#define SID_IFNAME_S    0x151
#define SID_IFINDEX_S   0x152
#define SID_IF_VECTOR_S 0x153
#define SID_IF_VECTOR_INDEX_S 0x154
#define SID_IFMSGHDR_S  0x155
#define SID_IF_CREATE_S 0x156
#define SID_IFNET_CFA_S 0x157
#define SID_IF_HOTINSERT_S 0x158   /*added by bailin for d15109*/
#if (VRP_IFNET_E1_T1_E3_T3_CPOS == VRP_YES)
#define SID_IFNET_BUILDRUN_S 0x159
#endif
/*added for 8070V100R008.PRO.E001*/   
#if((VRP_IFNET_LOGIC_ENHENCE==VRP_YES) && (VRP_MODULE_LINK_MFR == VRP_YES)) 
#define SID_IFNET_MFR       0x15b
#endif

#if(VRP_IFNET_MP_GROUP==VRP_YES) 
#define SID_IFNET_MLT      0x15C
#endif

#if(VRP_SUBINTERFACE_FLOW_COUNT == VRP_YES )
#define SID_IFNET_SIC       0x15d
#endif
#if(VRP_IFNET_FASTFEELING == VRP_YES)
#define SID_IFNET_FASTFEELING 0x15D
#endif
#define SID_ISDN_L2PORT         0x160
#define SID_ISDN_L3CR           0x161
#define SID_ISDN_L3CMT          0x162
#define SID_ISDN_L3DLCI         0x163
#define SID_ISDN_CCUSER         0x164
#define SID_ISDN_CCQ931         0x165
#define SID_ISDN_CCPLCY_HEAD    0x166
#define SID_ISDN_CCPLCY_NODE    0x167
#define SID_ISDN_CCPLCYDT       0x168
#define SID_ISDN_CCDCH          0x169
#define SID_ISDN_CCB            0x16a
#define SID_ISDN_Q921           0x16b
#define SID_ISDN_Q931           0x16c
#define SID_ISDN_Q931TIME       0x16d
#define SID_ISDN_Q931STAT       0x16e
#define SID_ISDN_BUILDRUN       0x170

/*::ETHER-ARP module*/
#define SID_ETHARP_MTSOFTC_S    0x180
#define SID_ETHARP_ARPRTENTRY_S 0x181
#define SID_ETHARP_ARPCMD_S     0x182
/*  added by fxy    */
#define SID_ETHCMDA              0x183
#define SID_ARPCMDA              0x184
#define SID_ENABLEARP            0x185
#define SID_ARPBUILDRUN          0x186
#define SID_IP_MIB                 0x187

#define SID_ARPCMD_CLEAR             0x188 
#define SID_ARPCMD_CLEARINTERFACE   0x189

/*::VLINK module */
#define SID_ADTACENTTABLE_S     0x190
#define SID_VLINKTABLE_S        0x191
#define SID_ETHARP_MTSOFTCSUB_S     0x192

#if (VRP_MODULE_MPLS_L2VPN_INTERWORKING == VRP_YES)
#define SID_MPLS_L2VPN_ETHARP_ARPRTENTRY_S   0x193
#define SID_MPLS_L2VPN_DISPLAYLOCALCE_RPCREQ_S   0x194
#endif

/*::DRV(VIRT) module*/
#define SID_ETH_MESSAGE_S       0x200
#define SID_DEVLINK_S           0x201
#define SID_CONAUX_CTRL_S       0x202
#define SID_AUX_S           0x203       

/*::RTPRO module*/
#define SID_RTPRO_GENERAL_S     0x210

/*::IP module*/
#define SID_IPIFADDR_S          0x220  /* IP  -- IPIFADDR_S   */
#define SID_IPIFNET_S           0x221  /* IP  -- IPIFNET_S    */
#define SID_RTCMD_S     0x222
#define SID_RTMSG_S     0x223 
#define SID_RT          0x224
#define SID_IPREASSQUEUE_S      0x225 /* IPREASSQUEUE_S */
#define SID_IPCMDA      0x226
#define SID_IPMSG_S             0x227 
#define SID_RPCMSG_S            0x228 
#define SID_IPADDCHECK_S      0x229      
#define  SID_IPSTAT_S           0x219

#if (VRP_VERSION_5 == VRP_YES) /* Robin Added for MPLS_FW */
#define SID_RT_VRF              0x21A
#define SID_RT_RTENTRY_S        0x21B
#define SID_RT_VRFHEAD_S        0x21C
#define SID_RT_SLL              0x21D
#endif

/* "debug show ip interface" 2001/10/16*/
#define SID_DBGSHOWIP_REQUEST_S         0x22A
#define SID_DBGSHOWIP_REPLY_S            0x22B

/* VRRP */
#define SID_VRRP_STANDBY_S      0x0001
#define SID_VRRP_PACKET_S       0x0002
#define SID_VRRP_TRACKEDIF_S    0x0003
#define SID_VRRP_IPC_INFO_S     0x0004
#define SID_VRRP_ARP_ITEM_S     0x0005

/*ip policy routing module id*/
#define SID_SETUP_RTNODE        0x0001

/*multicast policy routing module*/
#define SID_MCAST_POLICY_DEBUG        0x0001

/*::LINE  moudle*/
#define SID_LINETRANSBUF_S 0x229
#define SID_LINE_S         0x230
#define SID_LINETYPE_S     0x231

/*::EXEC moudle*/
#define SID_EXEC_DATA_S     0x232
#define SID_EXEC_SHOWBUF_S  0x233
#define SID_EXEC_AAAPRIM_S  0x234

/*::PPP moudle*/
#define SID_PPP_PACKET_S        0x235
#define SID_PPP_CB_S            0x236
#define SID_PPP_BUILDRUN        0x237
#define SID_PPP_L2TPOPTION_S    0x238
#define SID_PPP_L2TPPARA_S      0x239
#define SID_PPP_AAAPRIM_S       0x240
#define SID_PPP_ASY_S           0x241
#define SID_PPP_SYN_S           0x242

/*::MP moudle*/
#define SID_PPP_MP              0x400
#define SID_MP_SHOW_BLOCK_S     0x401
#define SID_MP_WAITLIST_PARAM_S 0x402
#define SID_MP_ENQUERY_MSG_S    0x403
#define SID_MP_IPC              0x404
#define SID_MP_MIB              0x405

/*::SLIP moudle*/
#define SID_SLIP_ASY_PACKET     0x350
#define SID_SLIP_SYN_PACKET     0x351
#define SID_SLIP_CB_S           0x352
#define SID_SLIP_BUILDRUN       0x353

/* CLI moudle*/    
#define SID_CLI_VECTOR_S                0x240    
#define SID_CLI_EXTEND_CMDELEMENT_S     0x241
#define SID_CLI_TRACENODE_S             0x242 
#define SID_CLI_NODEBRANCH_S            0x243
#define SID_CLI_ELEMENTTYPE_S           0x244
#define SID_CLI_SINGLEELEMENT_S         0x245
#define SID_CLI_CMDELEMENT_S            0x246    
#define SID_CLI_CMDTEMPLET_S            0x247
#define SID_CLI_CMDMODE_S               0x248
#define SID_CLI_INSERTCMDREC_S          0x249
#define SID_CLI_INSERTBRANCHREC_S       0x250
#define SID_CLI_CMD_S                   0x251
#define SID_CLI_MARKSTRING_S            0x252
#define SID_CLI_CMDINF_S                0x253
#define SID_CLI_MARKCMDREC_S            0x254
#define SID_CLI_MARKBRANCHREC_S         0x255
#define SID_CLI_HELPINFOR_S             0x256
#define SID_CLI_MATCHNODEREC_S          0x257
#define SID_CLI_MATCHBRANCHREC_S        0x258
#define SID_CLI_MATCHELEMENT_S          0x259
#define SID_CLI_WS_S                    0x260
#define SID_CLI_LINECMDREC_S            0x261
#define SID_CLI_CMDLEVEL_S              0x262               /*buildRun用*/
#define SID_CLI_CMDMODE_MSG_S           0x263
#define SID_CLI_REGERRINF_S             0x264
#define SID_USER_ACCESS_CMDMODE_REC_S   0x265
#define SID_CLI_SETHOSTNAME_MSG_S        0x266


/*Config file management module*/
#define SID_CFM_SECTION_TYPE    0x270
#define SID_CFM_SECTION         0x271
#define SID_CFM_BUILD_RUN       0x272
#define SID_VOS_SLL             0x273


/*Module PPPOE*/
#define SID_PPPOE_HEADERLIST    0x280
#define SID_PPPOE_HISMACLIST    0x281
#define SID_PPPOE_HEADLIST      0x282
#define SID_PPPOE_CB            0x283
#define SID_PPPOE_OURMAC        0x284
#define SID_PPPOE_SESSIONID     0x285
#define SID_PPPOE_HISMAC        0x286
#define SID_PPPOE_SB            0x287
#define SID_PPPOE_ENQUERY_MSG_S 0x288
#define SID_PPPOE_SHOW_BLOCK_S  0x289
#define SID_PPPOE_WAITLIST_PARAM_S 0x290
 
#define SID_CFG_REGMOD_S    0x290
#define SID_CFG_CFGVECTOR_S 0x291

/*INFO-CENTER */
#define SID_IC_OUTPUTATTR_S 0x299
#define SID_IC_MSGPDU_S     0x300
#define SID_IC_EXECREGATTR_S    0x301
#define SID_IC_EXECUSERATTR_S   0x302
#define SID_IC_SGLLISTNODE_S    0x303
#define SID_IC_DBGINFO_S    0x304
#define SID_IC_DBGREG_S     0x305
#define SID_IC_MODUMASK_S   0x306
#define SID_IC_REGMODU_S    0x307
#define SID_IC_LOGBUFINFOITEM_S     0x308
#define SID_IC_TRAPBUFINFOITEM_S    0x309

/*VTY */
#define SID_VTY_DRIVER_S       0x310
#define SID_VTY_LISTEN_PORT_S  0x311

/*Telnet Clients */
#define SID_TEL_CLIENT_DATA_S    0x312


/* FTP Client  */
#define SID_FTP_CLIENT_DATA_S    0x314

/* FTP Server */
#define SID_FTPS_USER_S          0x315
#define SID_FTPS_AAA_S           0x316

/*SSH SERVER*/
#define SID_SSH_AAA_S          0x317
#define SID_SSH_NODE_S         0x318
#define SID_RSA_LOCAL          0x319
#define SID_RSA_PEER            0x320
#define SID_RSA_ENCODE          0x321
#define SID_RSA_ALG             0x322
#define SID_SSH_GLOBLE          0x323

#define SID_MDM_S               0x362
#define SID_MDM_DIALMSG_S       0x363
#if( VRP_MODULE_CFG_MODEM == VRP_YES )
#if( VRP_MODULE_CFG_CHATSCRIPT == VRP_YES )
#define SID_MDM_CHATSCRIPT_S 0x364
#endif
#endif

#if( VRP_MODULE_CFG_MODEM == VRP_YES )
#if( VRP_MODULE_CFG_SYNCMDM == VRP_YES )
#define SID_MDM_SYNC_S 0x365
#endif
#endif


/*STACK*/
#define SID_STAC_BUFFER_S       0x320
#define SID_STAC_PACKET_S       0x321
#define SID_STAC_HASHTABLE_S    0x322
#define SID_STAC_MINLIST_S      0x323
#define SID_STAC_HASHNODE_S 0x324

/* FR */
#define SID_FR_PVC_S            0x330
#define SID_FR_MAP_S            0x331
#define SID_FR_PVC_HASH         0x332
#define SID_FR_CB_S         0x333
#define SID_FR_SUBIF_S          0x334
#define SID_FR_ARP_PAC          0x335
#define SID_FR_LMIAE_PAC        0x336
#define SID_FR_LMIBR_PAC        0x337
#define SID_FR_MBUF_S           0x338
#define SID_FR_SWITCH_S         0x339
#define SID_FR_VJCOMP_S         0x340
#define SID_FR_IPC_MSG_S        0x341
#define SID_FR_RPC_ENQUERY_MSG_S        0x342
#define SID_FR_RPC_REPLY_MSG_S          0x343
#define SID_FR_WAITLIST_PARAM_S     0x344
#define SID_FR_SHOW_BLOCK_S     0x345
#define SID_FR_BUILDRUN         0x346
/*added for 8070V100R008.PRO.E001*/   
#if (VRP_MODULE_LINK_MFR == VRP_YES)    
#define SID_FR_BUNDLECB_S       0x347
#define SID_FR_BLINKCB_S        0x348
#define SID_FR_MFRSTATIS_S      0x349
#endif
#if( VRP_MODULE_LINK_FRF9 == VRP_YES )
#define SID_FR_FRF9_S           0x350
#endif

/* CHDLC */
#define SID_CHDLC_CB_S          0x0350
#define SID_CHDLC_BDRN_SPACE    0x0351

/*::LAPB moudle*/
#define SID_LAPB_CB_S           0x360
#define SID_LAPB_BUILDRUN       0x361

/*DDR*/
#define SID_DDR_CALLER_S        0x370
#define SID_DDR_LIST_S          0x371
#define SID_DDR_CALL_S          0x372
#define SID_DDR_LINK_S          0x373
#define SID_DDR_MAP_S           0x374
#define SID_DDR_POOLMEMBER_S        0x375
#define SID_DDR_S           0x376
#define SID_DDR_DIALMSG_S       0x377
#define SID_DDR_ENABLE_S        0x378
#define SID_DDR_CALLBACK_S      0x379
#define SID_DDR_NODE_S          0x380
#define SID_DDR_BUILDRUN        0x381
#define SID_DDR_BUILDRUN_DIALERLIST 0x382

#if (VRP_VERSION_5 == VRP_YES)
#if( VRP_MODULE_MPLS_RSVP== VRP_YES )
/* VRPv5 Scott */
#define MID_MPLS_RSVPTE (ULONG)0x08880000

#define SID_RSVP_NBR_INFO_S                0x2
#define SID_RSVP_TIMER_S                   0x3

#define SID_RSVP_SESSIONENTRY_S            0x5
#define SID_RSVP_IFENTRY_S                 0x6
#define SID_RSVP_CRLSP_INFO_S              0x7
#define SID_RSVP_DYN_ITEM                  0x8
#define SID_RSVP_RRO_INFO_S                0x9
#define SID_RSVP_RRO_INFO_NODE_S           0xA
#define SID_RSVP_ERO_INFO_S                0xB
#define SID_RSVP_RSB_FILTERSPEC_INFO_S     0xC
#define SID_RSVP_FLOWDESC_NODE_S           0xD
#define SID_RSVP_FILTERSPEC_NODE_S         0xE
#define SID_DIFFSERV_S                     0xF
#define SID_RSVP_NBRLOST_S                 0x10
#define SID_TRAFF_INFO_S                   0x11
#define SID_RSVP_HOP_NODE_S                0x12
#define SID_RSVP_TCSB_FILTERSPEC_INFO_S    0x13
#define SID_RSVP_MPLSIF_INFO_S             0x14
#define SID_RSVP_HOPNODE_S                 0x15
#define SID_RSVP_UNKNOWNOBJNODE_S          0x16
#define SID_RSVP_RRO_S                     0x17
#define SID_RSVP_ERO_S                     0x18
#define SID_RSVP_MPLS_MPLSTE_SET_INFO_S    0x19
#define SID_RSVP_ALLOCITEM                 0x1A
#define SID_RSVP_DELETEALL_S               0x1B
#define SID_RSVP_PSB_S                     0x1C
#define SID_RSVP_RSB_S                     0x1D
#define SID_RSVP_RFSB_S                    0x1E
#define SID_RSVP_TCSB_S                    0x1F
#define SID_RSVP_BSB_S                     0x20
/* VRPv5 Scott */
#define SID_RSVP_MSGID_ACK_NODE_S          0x21
#define SID_RSVP_MSGID_NACK_NODE_S         0x22
#define SID_RSVP_MSGID_LIST_NODE_S         0x23
#define SID_RSVP_RETRANS_BUFFER_S          0x24

/* add by Robin */
#define SID_RSVP_CFGPSB_S                  0x25

#endif

/* Start: Scott, Defect BYAD07859 */
#define VOS_MID_TWL          (ULONG)0x08890000
#define VOS_SID_TWL          0x25

#if (VRP_MODULE_MPLS_RSVP == VRP_YES)
#define RSVP_WAITLIST_HASHNODE_TYPE 2201
#define RSVP_WAITLIST_PSBID_TYPE    2202
#define RSVP_WAITLIST_RSBID_TYPE    2203
#define RSVP_WAITLIST_HASHNODE_TYPE2 2204
#endif


/* Robin Check it */
/*#define SID_LSPM_MANUALCRLSPENTRY_S         (SID_MPLS_LSPM_BASE + 0x200)
  #define SID_LSPM_TEMIB_TUNNELENTRY_S        (SID_MPLS_LSPM_BASE + 0x201)
  #define SID_LSPM_TEMIB_ERHOPENTRY_S         (SID_MPLS_LSPM_BASE + 0x202) */
#define SID_CRLSP_INFO_S                    (SID_MPLS_LSPM_BASE + 0x203)
#define SID_ERHOP_S                         (SID_MPLS_LSPM_BASE + 0x204)
/*#define SID_LSPM_TEMIB_ERHOPNODE_S          (SID_MPLS_LSPM_BASE + 0x205)
  #define SID_LSPM_TEMIB_ARHOPNODE_S          (SID_MPLS_LSPM_BASE + 0x206)
  #define SID_CRLSP_FAILEDINFO_S              (SID_MPLS_LSPM_BASE + 0x207) */
/* Added by Scott */
#define SID_BIND_INFO_S                     (SID_MPLS_LSPM_BASE + 0x208)
#define SID_MPLSIF_RESM_PREEMPTLIST_S       (SID_MPLS_LSPM_BASE + 0x209)
#define SID_LSPM_PATHCACULATION_INFO_S       (SID_MPLS_LSPM_BASE + 0x20a)
/* LSPM_PATHCACULATION_INFO_S */
#endif


/*atm*/
#define SID_ATM_BUILDRUN            0x383
#define SID_ATM_RPC_ENQ             0x384
#define SID_ATM_RPC_RPL             0x385
#define SID_ATM_WAITLIST_PARAM      0x387
#define SID_ATM_MBUF                0x388
#define SID_ATM_CB                  0x389
#define SID_ATM_INTF                0x390
#define SID_ATM_PVC                 0x391
#define SID_ATM_IPMAP               0x392
#define SID_ATM_PPPMAP              0x393
#define SID_ATM_PPPOEMAP            0x394

#if (VRP_MODULE_LINK_ATM == VRP_YES)
/***********************************************************************************
以下为R8070_MODULE_ATMEXTEND特性新增代码
创建时间: 2000/03/10
创 建 者: Lvhong
***********************************************************************************/


#define SID_ATM_VCCLASS                0x38F

/**********************************************************************************
R8070_MODULE_ATMEXTEND-END
***********************************************************************************/
#endif /* VRP_MODULE_LINK_ATM end */

/* X25 */
#define SID_X25_LCD             0x390
#define SID_X25_LCI_NODE        0x391
#define SID_X25_CB              0x392
#define SID_X25_SUBINTF         0x393
#define SID_X25_WAITLIST_PARAM_S    0x394
#define SID_X25_ALIAS               0x395
#define SID_X25_MAP                 0x396
#define SID_X25_RPC_REPLY_MSG_S     0x397
#define SID_X25_RPC_ENQUERY_MSG_S   0x398
#define SID_X25_SHOW_BLOCK_S        0x399
#define SID_X25_BUILDRUN            0x39A

#define SID_X25_ROA_S               0x39B
#define SID_X25_VJCOMP_S            (SID_X25_ROA_S + 1)
#define SID_X25_CUG_S               (SID_X25_ROA_S + 2)
#define SID_X25_CUG_MAP_S           (SID_X25_ROA_S + 3)

#define SID_X25_BAK_SMOOTH                      0x3A0
#define SID_X25_RPC_INTF_DEL_MSG_S              0x3A1 
#define SID_X25_SW_VCRTENTRY_S                  0x3A2 
#define SID_X25_SW_SHOW_BLOCK_S                 0x3A3
#define SID_X25_IPC_SW_GET_OUTIFNAME_RPL_MSG_S  0x3A4
#define SID_X25_RPC_SW_ENQUERY_MSG_S            0x3A5
#define SID_X25_RPC_SW_PVCSTATE_MSG_S           0x3A6
#define SID_X25_IPC_SW_GET_OUTIFNAME_REQ_MSG_S  0x3a7
#define SID_X25_RPC_XOT_CREATE_PVC_MSG_S        0x3a8

/*addition end for X25ENH*/
/*为交换而加 2002/12/16 sangyuesong*/
#define SID_X25_SWRT            0x3B1
#define SID_X25_SWVCRT          0x3B2
#define SID_X25_IPC_MSG_S       0x3B3 

#define SID_X25_HG_IPC_REQ      0x3BA

#define SID_X25_XOT                 0x3c1

/*X25ENH_PAD*/
#define SID_X25_PAD_CB         0x3D1
#define SID_X25_PAD_IPC_REQ    0x3D2
#define SID_X25_PAD_RPC_REQ    0x3D3
#define SID_X25_PAD_RPC_RPL    0x3D4

/*::MPLS module*/
#define SID_MPLS_LDP    0x400
#define SID_LSPMSG      0x401
#define SID_VRFMSG     0x402
#define SID_VRF_LIST    0x403
#define SID_DESTNHLFE   0x404
#define SID_FTNVRFNODE  0x405
#define SID_VPNNHLFE    0x406
#define SID_ILMTBL      0x407
#define SID_ILMNHLFE    0x408
#define SID_ILMIDX      0x409

#define SID_MASK        0x40A
#define SID_RADIXHEAD   0x40B
#define SID_ZERO        0x40C
#define SID_ENTRY       0x40D
#define SID_KEY         0x40E
#define SID_RADIX_MASK  0x40F

#define SID_LBLSTK      0x410

/*MPLS Interface Management */
#define  SID_MPLSIF_IFNODE             1
#define  SID_MPLSIF_LABELSPACE         2
#define  SID_MPLSIF_KEY1               3
#define  SID_MPLSIF_KEY2               4
#define  SID_MPLSIF_LABELRANGE         5
#define  SID_MPLSIF_IFFUNC_NODE        6
#define  SID_MPLSIF_LBLFUNC_NODE       7
#define  SID_MPLSIF_LABELRANGE_FLAG    8
#define  SID_MPLSIF_SLL_S              9      

/*DDRS*/
#define SID_DDRS_BUILDRUN   0x423
#define SID_DDRS_CREATEDDRS 0x424
#define SID_DDRS_DIALMSG    0x425

#if ( VRP_MODULE_LINK_DLSW == VRP_YES)
/*DLSW*/
#define SID_DLSW_LLC2_SND_S     0x0001
#define SID_DLSW_CIR            0x0002
#define SID_DLSW_LLC2_RPC_ENQUERY_MSG_S     0x0003
#define SID_DLSW_LLC2_RPC_REPLY_MSG_S        0x0004
#define SID_DLSW_LLC2_WAITLIST_PARAM_S      0x0005
#define SID_DLSW_LLC2_BUILDRUN                0x0006
#define SID_8070_DLSW_LLC2_BRIDGE_ENTRY    0x0010
#define SID_8070_DLSW_LLC2_BRIDGE_IPC       0x0011

#define SID_SSP                                 0x0020
#define SID_DLSW_DLC_CREATE_CIRCUIT          0x0021
#define SID_DLSW_DLC_SEND_FRAME              0x0022
#define SID_SDLC                                0x0023
#define SID_IC_PORT                            0x0024
#define SID_DLSW_CFG_SHOW                     0x0025
#define SID_DLSW_RPC_REQUEST                 0x0026
#define SID_DLSW_LOCPEER                      0x0027
#define SID_DLSW_PEERCAP                      0x0028
#define SID_DLSW_RMTPEER                      0x0029
#define SID_DLSW_BUILDRUN                     0x0030
#define SID_DLSW_LLC2                         0x0031
/* add by libingshan for backup peer */
#define SID_8070_DLSW_SSP_BRIDGE_ENTRY    0x0040
#define SID_8070_DLSW_IPC                 0x0050
#endif

/*NTP*/
#define SID_NTP_AUTHKEY 0x430
#define SID_NTP_SRCIPADDR   0x431
#define SID_NTP_IFDISABLE   0x432
#define SID_NTP_EXTSYSVAR   0x433
#define SID_NTP_PEERVAR 0x434
#define SID_NTP_CLKVAR  0x435
#define SID_NTP_SERVER  0x436
#define SID_NTP_MULTIADDR   0x437
#define SID_NTP_INTERFACE   0x438
#define SID_NTP_SYSHUFF 0x439
#define SID_NTP_MON 0x43A
#define SID_NTP_RECVBUFFER  0x43B
#define SID_NTP_ENDPOINT    0x43C
#define SID_NTP_INDEX   0x43D
#define SID_NTP_PEER    0x43E
#define SID_NTP_KEYLIST 0x43F
/*NTP*/
#define SID_NTP_AUTHKEY 0x430
#define SID_NTP_SRCIPADDR   0x431
#define SID_NTP_IFDISABLE   0x432
#define SID_NTP_EXTSYSVAR   0x433
#define SID_NTP_PEERVAR 0x434
#define SID_NTP_CLKVAR  0x435
#define SID_NTP_SERVER  0x436
#define SID_NTP_MULTIADDR   0x437
#define SID_NTP_INTERFACE   0x438
#define SID_NTP_SYSHUFF 0x439
#define SID_NTP_MON 0x43A
#define SID_NTP_RECVBUFFER  0x43B
#define SID_NTP_ENDPOINT    0x43C
#define SID_NTP_INDEX   0x43D
#define SID_NTP_PEER    0x43E
#define SID_NTP_KEYLIST 0x43F
/*IP MRT MODULE*/
#define SID_MRT_BLKMFC     0x500
#define SID_MRT_MFC        0x501
#define SID_MRT_VIF        0x502
#define SID_MRT_MFC_CNT    0x503
#if ( VRP_MODULE_IPTN_BASE == VRP_YES )
#define SID_IPTN_TIMERDOWNLOAD          0x430
#endif
/*SID of MPLS L2VPN module */
#if ( VRP_MODULE_VPN_L2VPN == VRP_YES ) 
#define SID_L2VPN_CHAR              0x600
#define SID_L2VPN_TNL                0x601
#define SID_L2VPN_CCCENCAPINTF    0x602
#define SID_L2VPN_DESTCONN         0x603

#if ( VRP_MODULE_VPN_L2VPN_CCC == VRP_YES ) 
#define SID_L2VPN_CCCCONN           0x604
#define SID_L2VPN_TNL_LSP            0x605
#endif

#if ( VRP_MODULE_VPN_L2VPN_LDP == VRP_YES ) 
#define SID_L2VPN_LOCALLDPVC        0x606
#define SID_L2VPN_REMOTELDPVC       0x607
#define SID_L2VPN_LDP_VCFECHEAD     0x608
#define SID_L2VPN_LDP_INTFPARATLV   0x609
#define SID_L2VPN_LDP                   0x60a
#endif /*_MPLS_L2VPN_LDP*/

#define SID_L2VPN_L2FORWARDENTRY    0x60b

#if ( VRP_MODULE_VPN_L2VPN_BGP == VRP_YES ) 
#define SID_L2VPN_BGP_MSG              0x60c
#define SID_L2VPN_BGP_MLB              0x60d
#define SID_L2VPN_BGP_MRLB              0x60e
#define SID_L2VPN_BGP_NLRI              0x60f
#define SID_L2VPN_BGP_REFH          0x610
#define SID_L2VPN_BGP_L2INFO           0x611
#define SID_L2VPN_BGP_LLB           0x612
#define SID_L2VPN_BGP_VPN               0x613
#define SID_L2VPN_BGP_CE                0x614
#define SID_L2VPN_BGP_RLB               0x615
#define SID_L2VPN_BGP_PRT           0x616
#define SID_L2VPN_BGP_RT            0x617
#define SID_L2VPN_BGP_VC                0x618
#define SID_L2VPN_BGP_RMTRD             0x619
#define SID_L2VPN_BGP_RMTPE             0x61a
#define SID_L2VPN_BGP_DLLNODE           0x61b
#endif  /*_MPLS_L2VPN_BGP*/

#if ( VRP_MODULE_VPN_L2VPN_SVC == VRP_YES ) 
#define SID_L2VPN_SVCCONN          0x61c
#endif

#if (VRP_VERSION_5 == VRP_YES)
#else
#if ( VRP_MODULE_VPN_L2VPN_VPLS == VRP_YES ) 
#define SID_L2VPN_DLL          0x61d
#endif
#endif

#if (VRP_VERSION_5 == VRP_YES)
#define SID_VPN_L2VPN_INTF       0x61e
#define SID_L2VPN_ENCAP_DLLNODE  0x61f 
#define SID_VPN_L2VPN_TNL        0x620  


#define SID_L2VPN_BGP_HASHNODE   0x621 

/*newlely defined : the old SID_L2VPN_TNL can be removed   */
#define SID_L2VPN_TUNNELVC       0x622 
#define SID_L2VPN_TNL_DLLNODE    0x623
#define SID_L2VPN_TNL_HASHNODE   0x624

/*newlely defined  */
#define SID_L2VPN_CCC_DLLNODE    0x625 

#define SID_L2VPN_SVC_HASHNODE   0x626
#define SID_L2VPN_SVC_DLLNODE    0x627


#define SID_L2VPN_LDP_HASHNODE   0x628
#define SID_L2VPN_LDP_DLLNODE    0x629
#endif
#endif  /*_MPLS_L2VPN*/

/*SID of TNLM module - Added for D00047 on 30/08/2004*/
#if(VRP_YES == VRP_MODULE_VPN_TNLM)
#define SID_TNLM_HASHNODE   0x651
#define SID_TNLM_GADSHANDLE 0x652
#define SID_TNLM_HASHTABLE  0x653
#endif

/*VRPV3R001M07 backup 2002/11/06*/
#define SID_IB_BUILDRUN     0x701
#define SID_IB_ISM           0x702

#if  (VRP_MODULE_LINK_PPPOE_CLIENT == VRP_YES)
#define SID_PPPOE_CLIENT_CB  0x800
#define SID_PPPOE_C_SESSION  0x801
#define SID_PPPOE_CLIENT_BUILDRUN            0x802
#define SID_PPPOE_CLIENT_RPC_ENQ             0x803
#define SID_PPPOE_CLIENT_RPC_RPL             0x804
#define SID_PPPOE_CLIENT_WAITLIST_PARAM      0x805
#endif

#if( VRP_MODULE_LINK_IPX == VRP_YES )
#define SID_IPX_CB 0x810
#define SID_IPX_IFADDR 0x811
#define SID_IPX_PKT 0x812
#define SID_IPX_PING 0x813
#define SID_IPX_DISPLAY 0x814
#define SID_IPX_BUILDRUN 0x815
#endif

#if (VRP_MODULE_IP_USERLOG == VRP_YES)
/* USERLOG SID */
#define SID_USERLOG_NAT        0x0001
#define SID_USERLOG_ACCESS     0x0002
#define SID_USERLOG_FLOW       0x0003
#define SID_USERLOG_EXPORT     0x0004
#define SID_USERLOG_CFG        0x0005
#endif

/* ip trunk */
#define SID_IP_TRUNK 0x426 /* add by housen 11-15-2001 */
#define SID_TRUNK_VLAN_INTERFACE_S 0X427
#define SID_SYS_MSG_S 0x428
/*All modules inside our VRP.*/

/*::VOS module*/
#define MID_VOS_HASH    0x010000
#define MID_VOS_QUE     0x020000
#define MID_VOS_TMR 0x030000
#define MID_MBUF    0x050000
#define MID_MBUF_TR 0x060000

#define MID_VOS_NAME 0x070000
#define MID_VOS_SELF_TASK_STACK 0x080000
#define MID_VOS_SELF_TASK_NODE 0x090000
#define MID_FASTMBUF         0x0a0000
#define MID_VOS         0x100000
#define MID_WAITLIST            0x110000
#define MID_VOS_VFS         0x120000
/* ha slave2main */
#define MID_HA_SLAVE2MAIN       0x130000
#define MID_HSC_BOARD2BOARD     0x140000
/* flash */
#define MID_FLASH               0x150000
#define MID_VOS_MON             0x160000
/* add by renmin, IPC */
#define MID_VOS_IPC             0x170000
#define MID_VOS_PATCH        0x180000
#define MID_OSSA                0x190000
/*系统管理MIB*/
#define MID_SYSMIB                       0x1b0000

#if (VRP_VERSION_5 == VRP_YES)
/*by terry*/
#define MID_PAF         0x200000
#define MID_LICENSE     0x210000
#define MID_SYSTRACE    0x220000
#define MID_COMPONENT   0x230000
#endif

/*::IFNET module*/
#define MID_IFNET   0x500000
#define MID_IFNET_CFA   0x510000
#define MID_IPTRUNK 0x520000 /* add by housen 11-15-2001 */

/*::VIRT module*/
#define MID_VIRT    0x600000
#define MID_VIRT2   0x610000

/*::ETHER-ARP module*/
#define MID_ETHER       0x800000
#define MID_ARP         0x810000
#define MID_ARP_CMD     0x820000
#define MID_ARP_CLEAR       0x830000
#define MID_ARP_CLEARIFNET      0x840000

/*::RTPRO module*/
#define MID_RTPRO_ISIS  0x890000   
#define MID_RTPRO_RM    0x900000
#define MID_RTPRO_RM2   0x910000
#define MID_RTPRO_RIP   0x920000
#define MID_RTPRO_RIPNG 0x930000
#define MID_RTPRO_HIGP 0x940000
#define MID_RTPRO_OSPF  0x950000
#define MID_RTPRO_BGP   0x960000
#define MID_RTPRO_IGMP  0x970000
#define MID_RTPRO_DVMRP 0x980000
#define MID_RTPRO_PIM   0x990000
#define MID_RTPRO_POLICY 0x9a0000
#define MID_RTPRO_OSPF6 0x9F0000
/*added by liuye 37514 for multicast*/

/* Commented by Krishnaraj */
/* IO does not get compiled with this check `*/
/* #if (VRP_MODULE_RTPRO_MRM==VRP_YES) */
#define MID_RTPRO_MRM   0x9e0000 
/* #endif */

/* Commented by Krishnaraj */
/* IO does not get compiled with this check `*/
/* #if (VRP_MODULE_RTPRO_MSDP==VRP_YES)*/
#define MID_RTPRO_MSDP  0xA00000 
/* #endif */

/* DHCPPRJ:Modefied begin ShuaiKe at 2002/02/14 */
/* DHCP moudle */
#if ( VRP_MODULE_IP_DHCP == VRP_YES )

#define MID_DHCP            0xdd4e0000
#if ( VRP_MODULE_IP_DHCP_RELAY == VRP_YES )
#if ( VRP_MODULE_IP_DHCP_HELPER_ADDRESS == YES )
#define MID_DHCPRELAY   0x9b0000
#define MID_HELPERADDRESS 0x9c0000
#endif                  /* end of VRP_MODULE_IP_DHCP_HELPER_ADDRESS */
#endif                  /* end of VRP_MODULE_IP_DHCP_RELAY */
#if ( VRP_MODULE_IP_DHCP_SERVER == VRP_YES )
#define MID_DHCPSERVER  0xdd4d0000
#endif

#endif
/* DHCPPRJ:Modefied end  */
#if ( VRP_MODULE_IPTN_BASE == VRP_YES )
#define MID_IPTN            0x870000
#define MID_COPS_CLNT       0x880000
#endif

#define MID_ETA         0x850000
/*::IP moudle */
#define MID_IP                  0x1000000
#define MID_IP_RT_CALLOC        0x1100000
#define MID_IP_GETVIPPKT        0x1110000 /* IP -- IP_GetValidIpPkt */
#define MID_IP_FORWARD          0x1120000 /* IP -- IP_Forward */
#define MID_IP_IF_OUTPUT        0x1130000 /* IP -- IP_IF_Output */
#define MID_IP_INPUT            0x1140000       /* IP -- IP_Input */
#define MID_IP_REASS            0x1150000 /* IP -- IP_Reass */
#define MID_IP_FRAG             0x1160000 /* IP -- IP_Frag */
#define MID_IP_IF_INIT          0x1170000 /* IP -- IP_IF_Init */
#define MID_IP_IF_NewIPIFNET    0x1180000 /* IP -- IP_IF_NewIpIfNet */
#define MID_IP_IF_NewIPIFADDR   0x1190000 /* IP -- IP_NewIpIfAddr */
#define MID_IP_FF               0x11A0000 /* IP -- IP_FAST_FORWARDING */
#define MID_IP_MIB              0x11B0000 /* IP -- IP_MIB */
#define MID_IP_STATISTIC        0x11C0000 /* IP--IP_Statistic*/
#define MID_IP_FIB              0x11D0000 /* IP--IP_FIB*/
/*added by liuye 37514 for multicast*/
#if (VRP_MODULE_IP_MCAST_FORWARD==VRP_YES)
#define MID_IP_MFIB             0x11E0000 /*IP--IP_MFIB*/
#endif

#define MID_IP_ARPCMD           0x1200000

#define MID_ARP_PLUGIN          0x1210000

#define MID_ICMP_ERROR          0x1220000 /* ICMP -- ICMP_Error */
#define MID_ICMP_INPUT          0x1230000 /* ICMP -- ICMP_Input */
#define MID_ICMP_REFLECT        0x1240000 /* ICMP -- ICMP_Reflect */
#define MID_ICMP_SEND           0x1250000 /* ICMP -- ICMP_Send */

#define MID_IP_RIP_INPUT        0x1300000 /* IP -- RIP_Input */
#define MID_IP_RIP_OUTPUT       0x1310000 /* IP -- RIP_Output */
#define MID_IP_RIP_CTLOUTPUT    0x1320000 /* IP -- RIP_CtlOutput */

#define MID_IP_SETMOPTIONS      0x1330000 /* IP -- IP_SetMOptions */
#define MID_IP_GETMOPTIONS      0x1340000 /* IP -- IP_GetMOptions */
#define MID_IPIF_ADDMULTI       0x1350000 /* IP -- IPIF_AddMulti */
#define MID_IP_SRCROUTE     0x1360000
#define MID_IP_INSERTOPTION     0x1370000

#define MID_IP_IP_SRCROUTE      0x1380000
#define MID_RTSYN_TIMERDOWNLOAD 0x1390000 /* RTSYN_TimerDownload */

#define MID_IP_CMD              0x13A0000

/*ip policy routing module id*/
#define MID_IP_POLICY           0x13B0000

/* VRRP */
#define MID_VRRP                0x13C0000

/*socket tcp udp module */
#define MID_SOCK_SOCKET         0x13D0000
#define MID_SOCK_TCP            0x13E0001
#define MID_SOCK_UDP            0x13F0002
/*::LINE-EXEC moudle*/
#define MID_LINE    0x1400000
#define MID_EXEC    0x1410000

#define MID_IPMRT               0x1420000
#define MID_IP_HANGOVERBLANKMFC 0x1430000
#define MID_IP_SENDBYMFC        0x1440000
#define MID_IP_IPIP_INPUT       0x1450000
#define MID_IP_MRTMLOOPBACK     0x1460000
#define MID_IP_MRTGET           0x1470000
#define MID_IP_ENCAPSEND        0x1480000
#define MID_IP_MRT_ASSCTLTOMFC  0x1490000
#define MID_IP_MRTADDVIF        0x14A0000
#define MID_IP_MRTADDMFC        0x14B0000
#define MID_IP_MRTINIT          0x14C0000  
#define MID_IP_TMEMINIT         0x14d0000
#define MID_IP_TRIEINIT         0x14e0000
#define MID_IP_MRTDOWNLOAD      0x14f0000
/* CLI moudle*/   
#define MID_CLI     0x1500000

/* SS moudle*/ 
#define MID_SS      0x1510000
#if (VRP_MODULE_IP_URPF == VRP_YES )
#define MID_IP_URPF    0x1580000
#endif

/* #if ( VRP_MODULE_DNS_CLIENT == VRP_YES ) */
#define MID_DNS_CLIENT    0x1590000
/* #endif */


/* PPPOE module*/
#define MID_PPPOE   0x1600000

#if( VRP_MODULE_LINK_PPPOE_CLIENT == VRP_YES )
/* The above is PPPOE server module, and the following is PPPOE Client module*/
#define MID_PPPOE_CLIENT    0x1610000
#endif

/*start: zhaoyujin 00919 2003-11-10 VRP_PRODUCT_ROUTER*/
/*chang note:add hwping function */
#if (VRP_HWPING_SNMP == VRP_YES)
#define MID_HWPING    0x1630000
#define SID_HWPING_HISTORY   0x001
#define SID_HWPING_SERVER   0x002
#define SID_HWPING_CLASS   0x003
#define SID_HWPING_UDPDATA 0x004
#endif
/*end  :zhaoyujin 00919 2003-11-10 VRP_PRODUCT_ROUTER*/
#if (VRP_MODULE_IP_USERLOG == VRP_YES)
/* USERLOG module */
#define MID_IP_USERLOG  0x1620000
#endif

/*::PPP moudle*/
#define MID_PPP     0X1650000    /* PPP */

/*add by gwei for netstream project*/
/*::NetStream module*/
#if(VRP_MODULE_NETSTREAM == VRP_YES)
#define MID_NETSTREAM   0xdd20000   /*模块ID*/

#define SID_NS_HASH     1
#define SID_NS_ENTRY    2
#define SID_NS_IF       3
#define SID_NS_ASCACHE              4  
#define SID_NS_PROTPORTCACHE        5
#define SID_NS_SRCPREFIXCACHE       6
#define SID_NS_DSTPREFIXCACHE       7
#define SID_NS_PREFIXCACHE          8
#define SID_NS_PREFIXHASH           9
#define SID_NS_DSTPREFIXHASH        10
#define SID_NS_SRCPREFIXHASH        11
#define SID_NS_ASHASH               12
#define SID_NS_PROTPORTHASH         13
#define SID_NS_MBUF                 14
#define SID_NS_IPC_EXPORT           15
#define SID_NS_IPC_CACHE            16
#define SID_NS_BUILDRUN             17
#define SID_NS_RPC_CACHE            18           /*RPC回应的Cache消息的结构ID*/  
#define SID_NS_RPC_CACHEENTRY       19           /*RPC回应的entry消息的结构ID*/
#define SID_NS_RPC_SHOWEXPORT       20           /*RPC回应的entry消息的结构ID*/    
#define SID_NS_RPC_ENQ              21           /*RPC请求数据的结构ID*/  
#define SID_NS_CHAR                 22           /*信息显示字符串*/  
/*add by gao新增聚合类的SID*/
#define SID_NS_ASTOSCACHE      23
#define SID_NS_PROTPORTTOSCACHE        24
#define SID_NS_SRCPREFIXTOSCACHE       25
#define SID_NS_DSTPREFIXTOSCACHE       26
#define SID_NS_PREFIXTOSCACHE          27
#define SID_NS_PREFIXTOSHASH           28
#define SID_NS_DSTPREFIXTOSHASH        29
#define SID_NS_SRCPREFIXTOSHASH        30
#define SID_NS_ASTOSHASH               31
#define SID_NS_PROTPORTTOSHASH         32

#define SID_NS_INTERFACOPTION         33
/*end by gao*/
#endif
/*add by gaowei for netstream project*/

/* VRP3R001M07，刘凯(L03198)，2002/10，增加IPHC和VJCOMP两个模块号 */
#define MID_IPHC    0x1680000
#define MID_VJCOMP  0x1690000
/* VRP3R001M07，刘凯(L03198)，2002/10，结束 */
/*::MP moudle*/
#define MID_PPP_MP  0X1640000    /* MP */    


/*::SLIP moudle*/
#define MID_SLIP     0X1660000    /* SLIP */

/*::LAPB moudle*/
#define MID_LAPB     0X1670000    /* LAPB */

/*::Cofig plane moudle*/
#define MID_CFG 0x1700000

/*::Config file management moudle*/
#define MID_CFM 0x1710000

/*::Agent management moudle*/
#define MID_CFA 0x1720000

/*::Huawei config management mib moudle*/
#define MID_HWCM 0x1730000

/* Info Center */
#define MID_INFO_CENTER 0x1750000

/* MDM */
#define MID_MODEM             0x17a0000

#if( VRP_MODULE_CFG_MODEM == VRP_YES )
#if( VRP_MODULE_CFG_CHATSCRIPT == VRP_YES )
/* CHAT */
#define MID_CHAT              0x17b0000
#endif
#endif

/* NTP */
#define MID_NTP             0x17d0000

/* VTY */
#define MID_VTY           0x1800000

/*SSH*/
#define MID_SSH           0x1810000
#define MID_RSA           0x1820000
#define MID_BIGNUM       0x1830000

#if( VRP_MODULE_CFG_HOTKEY == VRP_YES )
#define MID_HOTKEY       0x1840000

#endif

/* Telnet Client*/   
#define MID_TEL_CLIENT    0x1850000

/* FTP Client */
#define MID_FTP_CLIENT    0x1870000

/* FTP */
#define MID_FTP_SERVER    0x1880000

/* TFTP */
#define MID_TFTP_CLIENT   0x18A0000

/*STACK*/
#define MID_STAC        0x1900000
#define MID_STAC_HASH   0x1910000


/* Ping */
#define MID_PIN_PING            0x1950000
#define MID_TRACERT_TRACEROUTE  0x1960000

#define MID_LSPV                0x1970000

/*IPSEC*/
#define MID_IKE     0x2000000
#define MID_IPSEC   0x2010000
#define MID_L2TP    0x2020000
#define MID_TIMERNG 0x2050000
#define MID_ACL     0x2060000
#define MID_FILTER  0x2070000
#define MID_NAT     0x2080000
#define MID_PAM     0x2090000
#define MID_ASPF    0x20a0000
#define MID_TASK         0x20b0000
#define MID_MEMORY    0x20c0000
#define MID_CPU    0x20d0000

/*add over*/

#define MID_ZONE    0x20e0000
#define MID_BLS     0x20f0000
#define MID_SECBAK  0x2100000
#define MID_SECLOG  0x2110000
#define MID_SECSTAT 0x2120000
#define MID_BIND    0x2130000
#define MID_SECATK  0x2140000
#define MID_CODEC   0x2150000
#define MID_SEC     0x2160000
/*hrp*/
#define MID_HRP     0x2170000
#define MID_TP           0x2180000
#define MID_TP_IDS  0x2190000

/* VGMP */
#define MID_VGMP    0x21a0000


/* snmp agent */
#define MID_AGENT       0x2200000

/*SaN*/
#if ( VRP_PRODUCT_SAN == VRP_YES )
#define MID_SAN_AM         0x2500000
#define MID_SAN_SIP        0x2510000
#define MID_SAN_MGCP       0x2520000
#define MID_SAN_RTPRELAY   0x2530000
#define MID_SAN_IADMS   0x2540000
#define MID_E2K_MIB 0x2550000
#define MID_SAN_H323PRX  0x2560000
#define MID_SAN_H323STK  0x2570000
#define MID_TRVS_SERV    0x2580000
#endif

/* Chenwejun for E2100 MIB */
#if( VRP_PRODUCT_SAN == VRP_YES )
#define MID_Eudemon_MIB_HWENT_E2100  0x4460000
#define MID_Eudemon_MIB_ENTITY_E2100  0x4450000
#endif
/* END */

/*SaN*/
#if ( VRP_PRODUCT_SAN == VRP_YES )
#define SID_IADMS_REG   0x700
#define SID_IADMS_RESP   0x701
#define SID_IADMS_ACT   0x702
#define SID_IADMS_TRANSFER   0x703
#define SID_IADMS_PDU   0x704
#define SID_IADMS_TIMER   0x705
#define SID_IADMS_OTHER   0x706
#define SID_IADMS_LOCK   0x707
#endif
/*SaN*/


#define MID_SEMA        0x3330000

/* FR */
#define MID_FR          0x3400000

/*added for 8070V100R008.PRO.E001*/   
#if( VRP_MODULE_LINK_FRTS == VRP_YES )
#define   MID_FRTS           0xdd480000
#define   SID_FRTS_MAPCLASS  0x001
#define   SID_FRTS_BUILDRUN  0x002
#define   SID_MAPCLASSEX     0x003
#define   SID_FRTS_RPC_ENQUERY_MSG_S 0x004
#define   SID_FRTS_RPC_REPLY_MSG_S   0x005
#define   SID_FRTS_CONNECT           0x006
#define   SID_FRTS_DE                0x007
#define   SID_FRTS_PVCQUEUE          0x011
#define   SID_FRTS_BECN_RESPONSE     0x012
/*added the sid for fr mib by chengsongming*/
#define   SID_FRTS_RPC_CLASS_INFO_MSG_S 0x013
#endif
#if (VRP_MODULE_LINK_MFR == VRP_YES)       
#define   SID_MFR_RPC_ENQUERY_MSG_S  0x008
#define   SID_MFR_BUILDRUN           0x009
#define   SID_MFR_RPC_REPLY_MSG_S    0x010
#endif
/*end*/


/* QOS */
#define MID_QOS         0x3500000
#define MID_CQC         0x3580000
#define SID_CQC_8021PBA       0x01
#define SID_CQC_DSCPBA         0x02
#define SID_CQC_ELSPBA          0x03
#define SID_CQC_PHB               0x04
#define SID_CQC_DSBAK           0x05


/* MQC */
#define MID_MQC         0x3510000
#define SID_MQC_CLASSMAP          0x01
#define SID_MQC_MATCH             0x02 
#define SID_MQC_POLICYMAP         0x03
#define SID_MQC_POLICYCLASS       0x04
#define SID_MQC_CHARACTERISTIC    0x05
#define SID_MQC_SHOW              0x06
#define SID_MQC_BEHAVIOR          0x07
#define SID_MQC_CFA_RPC           0x08   /* added by chenxia for VRP_MODULE_MQCMIB */

/*atmqos*/
#if (VRP_MODULE_QOS == VRP_YES && VRP_MODULE_LINK_ATM == VRP_YES) 
#if (VRP_MODULE_ATMQOS == VRP_YES ) 
#define  MID_8070_ATMQOS      0x3520000
#endif  /*VRP_MODULE_ATMQOS END*/
#endif  /*VRP_MODULE_QOS&&VRP_MODULE_LINK_ATM END*/

#define MID_QOS_LFI     0x3530000

#if( VRP_MODULE_QOS_TE == VRP_YES )
#define MID_QOS_TE      0xddaa0000
#endif
/* CHDLC */
#define MID_CHDLC                       0x03600000
#define MID_CHDLC_ENCAP                 0x03610000
#define MID_CHDLC_SEND_KEEP_ALIVE       0x03620000
#define MID_CHDLC_RCV_ISL               0x03630000
#define MID_CHDLC_OUTPUT                0x03640000
#define MID_CHDLC_BDRN                  0x03650000
#define MID_CHDLC_PROCESS_KEEP_ALIVE    0x03660000
#define MID_CHDLC_OUTPUT_KEEP_ALIVE     0x03670000
#define MID_CHDLC_SEND_IPCRPCMESSAGE    0x03680000


#define MID_ISDN_CC      0x03700000
#define MID_ISDN_Q931    0x03710000
#define MID_ISDN_Q921    0x03720000
#define MID_ISDN_DDR     0x03730000/*for isdn*/

/* DDR */
#define MID_DDR         0x03800000

/* DDRS */
#define MID_DDRS        0x03810000

/*SOCKET*/
#define MID_UDP         0x03900000
#define MID_TCP         0x03910000
#define MID_SOCKET      0x03920000

/*GRE*/
#define MID_GRE                 0x03930000
#define MID_TUNNEL              0x03940000
#define MID_MPLS_FW         0x04000000
/* modified by chenxia for MFW整改, D99999 */
#define SID_MPLS_ILM_SHOW                   0x100
#define SID_MPLS_NHLFE_SHOW                 0x101
/* added for D25178 */
#define SID_MPLS_STATISTICS_SHOW            0x102
#define SID_MPLS_STATISTICS_CLEAR           0x103
#define SID_MPLS_L2VPNFWD_SHOW              0x104  
#define SID_MPLSFW_MAIN                        0x105  
#define SID_MPLSFW_CELLPACKING                 0x106  /* addedby chenxia for VRP_MODULE_ATM_CELL_TRANSPORT */  

#define MID_RADIX       0x04010000
#define MID_MPLS_LDP           0x04020000
#define MID_MPLS_LSR           0x04030000
#define MID_MPLS_LSRMIB       0x04040000
#define MID_MPLS_LSPAGT       0x04050000
#define MID_MPLS_LDP_DISPLAY  0x04060000
#define MID_MPLSIF            0x04070000
/* added by zhangtj*/
#define MID_MPLSVPNMIB           0x04080000
/* end*/

#if (VRP_PRODUCT_8060 == VRP_YES)
#define MID_DIAG         0x04090000
#define MID_SRM          0x040a0000
#define MID_LOAD         0x040b0000
#define MID_PTS          0x040c0000
#define MID_NPS          0x040d0000 /*0x07000000*/
#endif   

#if( ( VRP_PRODUCT_8060_ROUTER_E200 == VRP_YES ) || ( VRP_PRODUCT_8060_SAN_E2200 == VRP_YES )  )
/* E200 baseline MIB */
#define MID_Eudemon_MIB_ENTITY        0x040e0000
#define MID_Eudemon_MIB_HWENT         0x040f0000
#endif

#if( VRP_PRODUCT_8060_ROUTER_NE20 == VRP_YES )
/* NE20 baseline MIB */
#define MID_NE20_MIB_ENTITY           0x05010000
#define MID_NE20_MIB_HWENT            0x05020000
#endif


/*#if( VRP_MODULE_MPLS_LSPM == VRP_YES )*/
#define MID_MPLS_LSPM                     0x08800000
#define MID_MPLS_LSPM_SHOW                0x08900000
#define MID_MPLS_STAT_SHOW              0x09000000
/*end*/

#define MID_MPLS_CSPF                       0x09100000
#define SID_MPLSTE_CSPF_COMPUTE             0x101
#define SID_MPLSTE_CSPF_TEDB                0x201

#define SID_MPLS_LSPM_BASE                0x500
#define SID_LSPM_QUEMSG_S                   (SID_MPLS_LSPM_BASE + 0x1)
#define SID_LSPM_FAILEDMSG2PROTOCOL_S       (SID_MPLS_LSPM_BASE + 0x2)
#define SID_ReqToLM                         (SID_MPLS_LSPM_BASE + 0x10)
#define SID_LM_DELETE_S                     (SID_MPLS_LSPM_BASE + 0x11)
#define SID_MPLS_AGENT_INFO_S               (SID_MPLS_LSPM_BASE + 0x13)
#define SID_MPLS_LSP_INFO_S                 (SID_MPLS_LSPM_BASE + 0x14)
#define SID_LM_INTERFACETABLEITEM           (SID_MPLS_LSPM_BASE + 0x15)
#define SID_HASH_NODE_S                     (SID_MPLS_LSPM_BASE + 0x16)
#define SID_LM_INSEGMENTTABLEITEM           (SID_MPLS_LSPM_BASE + 0x17)
#define SID_LM_SEGMENTNODE_S                (SID_MPLS_LSPM_BASE + 0x18)
#define SID_LM_LABELHASHNODE_S              (SID_MPLS_LSPM_BASE + 0x19)
#define SID_LM_SEGMENTHASHNODE_S            (SID_MPLS_LSPM_BASE + 0x20)
#define SID_LM_OUTSEGMENTTABLEITEM          (SID_MPLS_LSPM_BASE + 0x21)
#define SID_LM_XCTABLEITEM                  (SID_MPLS_LSPM_BASE + 0x22)
#define SID_LM_CRLSPIDHASHNODE_S            (SID_MPLS_LSPM_BASE + 0x23)
#define SID_LM_LSPNODE_S                    (SID_MPLS_LSPM_BASE + 0x24)
#define SID_LM_LABELSTACKTABLEITEM          (SID_MPLS_LSPM_BASE + 0x25)
#define SID_LM_TRAFFICPARAMTABLEITEM        (SID_MPLS_LSPM_BASE + 0x26)
#define SID_LM_TRAFFICNAMEHASHNODE_S        (SID_MPLS_LSPM_BASE + 0x27)
#define SID_LM_VPNLSPLIST_S                 (SID_MPLS_LSPM_BASE + 0x28)
#define SID_LM_VPNINLABEL_S                 (SID_MPLS_LSPM_BASE + 0x29)

#define SID_LSPM_SLL                        (SID_MPLS_LSPM_BASE + 0x31)
#define SID_LSPM_LSPNODE                    (SID_MPLS_LSPM_BASE + 0x32)
#define SID_LM_GRE_INFO_HASH_TABLE          (SID_MPLS_LSPM_BASE + 0x33)
#define SID_LSPM_FIB_S                      (SID_MPLS_LSPM_BASE + 0x100)


#define SID_LSPM_ROUTE2PROTOCOL_S           (SID_MPLS_LSPM_BASE + 0x102)
#define SID_LSPM_MANUALLSPNODE_S            (SID_MPLS_LSPM_BASE + 0x103)
#define SID_LM_STATICLSPINFO_S              (SID_MPLS_LSPM_BASE + 0x104)
#define SID_LSPM_DELETEALL_S                (SID_MPLS_LSPM_BASE + 0x105)
#define SID_SIGNALPROTOCOL2LSPM_S           (SID_MPLS_LSPM_BASE + 0x106)
#define SID_SHOWFTN_S                       (SID_MPLS_LSPM_BASE + 0x107)
#define SID_LSPM_RPC                        (SID_MPLS_LSPM_BASE + 0x108)
#define SID_LSPM_STATICLSP_S                (SID_MPLS_LSPM_BASE + 0x109)

#define SID_LM_IPC_VRF                      (SID_MPLS_LSPM_BASE + 0x10b)


#if( VRP_MODULE_MPLS_LSPM_VPN== VRP_YES )
#define MID_MPLS_LSPM_VPN                   0x09200000
/* Modified By santosh E w.r.t to defect id BYAD08577 
 Logic :: earlier RM and RPA's definations were falling under MPLS Macro */
#endif
/* Modification End */


/*atm*/
#define MID_ATM         0x04100000

#if (VRP_IFNET_ATMEXTEND == VRP_YES)
#define MID_ADSL        0x04120000
#endif 

/* X25 */
#define MID_X25         0x041a0000

#if( R8070_MODULE_PFM == VRP_YES )
#define MID_MIB_PFM 0xdd020000
#define SID_EVENT 0x01
#define SID_LOG 0x02
#define SID_PFM 0x03
#endif

#if( (VRP_PRODUCT_8070 == VRP_YES && R8070_MODULE_DEV == VRP_YES) || (VRP_MEMORY_MIB == VOS_YES))
#define MID_MIB_DEV 0xdd030000
#endif

#if( R8070_MODULE_PNL == VRP_YES )
#define MID_MIB_PNL     0xdd040000
#endif

#if(R8070_MEDIUMMIB == VRP_YES)
#define MID_MediumMIB           0xdd500000
#define MID_MediumMIB_DS1       0xdd510000
#define MID_MediumMIB_DS3       0xdd520000
#define MID_MediumMIB_SDH       0xdd530000
#define MID_MediumMIB_ATM       0xdd540000
#endif
/*endof by wangyue*/


#if( R8070_MODULE_PLB == VRP_YES )
#define MID_MIB_PLB     0xdd470000
#endif

#if ( R8070_MODULE_DEV_MGT_PUB_MIB == VRP_YES )
/*  zhangwei  */
#define MID_DEV_MGT_PUB_MIB   0xdd070000
#endif

#if (( R8070_ENTITYMIB == VRP_YES ) || (R8011_ENTITYMIB == VRP_YES))
#define MID_ENTITYMIB   0xdd080000

#if ((R8070_ENTITYEXTMIB == VRP_YES) || (R8011_ENTITYMIB == VRP_YES))
#define MID_ENTITYEXTMIB 0xdd090000
#endif
#endif


#define MID_PAD    0x041b0000 /* add by xuyongqing for regist (no) debug all*/

#if (VRP_MODULE_IPV6 == VRP_YES)
#define SID_IP6_BASE_S           0x600

/*#if (VRP_MODULE_FIB6CONTR == VRP_YES || VRP_MODULE_FIB6AGENT == VRP_YES)*/
/* MIDs */
#define MID_IP6_FIB              0x045c0000
#define MID_IP6_FIBAGENT         0x045d0000
#define MID_IP6_FIBCONTR         0x045e0000

/* SIDs */
#define SID_RTMSG6_S             (SID_IP6_BASE_S+1)
#define SID_RT_ENTRY_S           (SID_IP6_BASE_S+2)
#define SID_IP6_FIB_MSGHDR_S     (SID_IP6_BASE_S+3)
#define SID_ROUTE6_S             (SID_IP6_BASE_S+4)
#define SID_RT6_CMD_S            (SID_IP6_BASE_S+5)
#define SID_RT6_ENTRY_S          (SID_IP6_BASE_S+6)
#define SID_SLL_NODE_S           (SID_IP6_BASE_S+7) 
#define SID_RT6_NODE_S           (SID_IP6_BASE_S+8)
#define SID_VOS_RDX6_EXT_NODE_S  (SID_IP6_BASE_S+9)    
/*#endif*/

#define MID_IP6_MANAGER           0x045f0000
#define MID_IPV6_CMD_FORWARD      0x04600000   
#define MID_IPV6_DISPLAYSTATS     0x04610000  
#define MID_IPV6_DEBUG            0x04620000  
#define MID_IPV6_MIB              0x04630000 

/*Added by guojianjun178934, 宏定义同Tcpip_id.h中重复, 2013/12/19   问题单号:20131219_1_Compile */
/*注意如果在VRP模式下，需要此宏定义,如果非VRP模式直接使用Tcpip_id.h中的定义*/
#if (VRP_YES == TCPIP_IN_VRP)
#define MID_IP6_ADDR              0x04640000
#define MID_ICMP6                 0x04650000
#define MID_ND                    0x04660000
#define MID_RIP6                  0x04670000
#define MID_UDP6                  0x04680000
#define MID_PMTU                  0x04690000
#define MID_PING6                 0x046a0000
#endif
/* End of Added by guojianjun178934, 2013/12/19   问题单号:20131219_1_Compile */

#define MID_IP6_ADDR_CmdProc      0x046b0000
/* Begin : Defect ID: BYAD12114,     Modifier:Rajesh,   Date:2004/10/21 
Reason   : IPC RPC synch call must not be called from sock run context*/
#define MID_ICMP6_PLUGIN          0x046d0000    /* Added by IPV6-Basic */

/*#if (VRP_MODULE_SEC_ACL6  == VRP_YES) */
#define MID_ACL_IPV6              0x046e0000
/*#endif*/

#define MID_TRACERT6_TRACEROUTE   0x046f0000

#if (VRP_MODULE_NATPT == VRP_YES)||(MODULE_NATPT_8011 == VRP_YES)
#define MID_NATPT                 0x04710000 /* IPv6 Natpt Module */
#endif

/*Added by guojianjun178934, 宏定义同Tcpip_id.h中重复, 2013/12/19   问题单号:20131219_1_Compile */
/*注意如果在VRP模式下，需要此宏定义,如果非VRP模式直接使用Tcpip_id.h中的定义*/
#if (VRP_YES == TCPIP_IN_VRP)
#define MID_TCP6                  0x04720000 
#endif
/* End of Added by guojianjun178934, 2013/12/19   问题单号:20131219_1_Compile */


#if (VRP_MODULE_IPV6_TUNNEL == VRP_YES)  
#define MID_TUNNEL6               0x04730000
/* IPv6 Tunnel 模块的SID */
#define SID_TUNN6_MAKECONT       (SID_IP6_BASE_S+10)
#define SID_TUNN6_PREPENDSPACE   (SID_IP6_BASE_S+11)
#endif

/*#if (VRP_MODULE_FIB6CACHE == VRP_YES )*/
#define MID_IP6_FIBCACHE         0x04740000

/* SIDs for FIB Cache*/
#define SID_IP6FIBCACHE_BUILDRUN       (SID_IP6_BASE_S+12)
#define SID_RT6_CACHE_S                (SID_IP6_BASE_S+13)
#define SID_PRT6_CACHE_S               (SID_IP6_BASE_S+14)
/*#endif*/

#endif /* VRP_MODULE_IPV6*/




/*@@@@atmqos*/
#if (VRP_MODULE_QOS == VRP_YES && VRP_MODULE_LINK_ATM == VRP_YES) 
#if (VRP_MODULE_ATMQOS == VRP_YES ) 
/*#define  MID_8070_ATMQOS      0xdd300000*/
#endif  /*VRP_MODULE_ATMQOS END*/
#endif  /*VRP_MODULE_QOS&&VRP_MODULE_LINK_ATM END*/
#if (VRP_MODULE_LINK_IPOEOA == VRP_YES ) /*guohongtao29200 at 2002年07月15日, for IPoEoA*/


#define  MID_8070_IPOEOA      0xdd430000
#endif  /*VRP_MODULE_LINK_IPOEOA END*/
#define MID_8070DRIVE_ATM            0xde000000
#define MID_8070DRIVE_AUXDRV         0xde010000
#define MID_8070DRIVE_CE1            0xde020000
#define MID_8070DRIVE_CONAUX        0xde030000
#define MID_8070DRIVE_CPCI           0xde040000
#define MID_8070DRIVE_DEVICE         0xde050000
#define MID_8070DRIVE_E3             0xde060000
#define MID_8070DRIVE_ETH            0xde070000
#define MID_8070DRIVE_FETH           0xde080000
#define MID_8070DRIVE_FLASHDRV      0xde090000
#define MID_8070DRIVE_GETH           0xde0a0000
#define MID_8070DRIVE_HSC            0xde0b0000
#define MID_8070DRIVE_PHY_CMD       0xde0c0000
#define MID_8070DRIVE_PHY_IC         0xde0d0000
#define MID_8070DRIVE_POS            0xde0e0000
#define MID_8070DRIVE_SA             0xde0f0000
#define MID_8070DRIVE_SAR            0xde100000
#define MID_8070DRIVE_SYS_CMD       0xde110000
#define MID_8070DRIVE_BTRM          0xde120000
#define MID_8070DRIVE_CPOS           0xde130000
#define MID_8070DRIVE_T3             0xde140000
#define MID_8070DRVIE_ATME1          0xde150000
#define MID_8070DRIVE_ATME3           0xde160000
#define MID_8070DRIVE_ATM622           0xde170000 /*added by lhm29307 for atm622*/
#define MID_8070DRIVE_GTETH            0xde180000
#define MID_8070DRIVE_SETDEVLINK       0xde190000
#define MID_8070DRIVE_SD701           0xde1a0000
/*8040产品驱动ID*/
#define MID_8040DRIVE_SYS_CMD        0xc0000000
#define MID_8040DRIVE_ATM_CMD        0xc0000100
#define MID_8040DRIVE_CE1_CMD        0xc0000200
#define MID_8040DRIVE_2S1B_CMD       0xc0000300
#define MID_8040DRIVE_16AS_CMD       0xc0000400
#define MID_8040DRIVE_BRI_CMD        0xc0000500
#define MID_8040DRIVE_ETH1_CMD       0xc0000600
#define MID_8040DRIVE_ETH2_CMD       0xc0000700
#define MID_8040DRIVE_SA_CMD         0xc0000800
#define MID_8040DRIVE_8040_701_CMD   0xc0000900
#define MID_8040DRIVE_8040_701BRI_CMD   0xc0000910
#define MID_8040DRIVE_8040_701E1_CMD    0xc0000920
#define MID_8040DRIVE_8040_701T1_CMD    0xc0000930
#define MID_8040DRIVE_8040_701SER_CMD   0xc0000940

#define MID_8040DRIVE_701_CMD          0xc0000a00
#define MID_8040DRIVE_701BRI_CMD       0xc0000a10
#define MID_8040DRIVE_701E1_CMD        0xc0000a20
#define MID_8040DRIVE_701T1_CMD        0xc0000a30
#define MID_8040DRIVE_701SER_CMD       0xc0000a40

#define MID_8040DRIVE_CN8500_CMD          0xc0010000
#define MID_8040DRIVE_CN8500CE3_CMD       0xc0020000
#define MID_8040DRIVE_CN8500CT3_CMD        0xc0030000
/*8040产品驱动ID*/
#define MID_8040DRIVE_SYS_CMD        0xc0000000
#define MID_8040DRIVE_ATM_CMD        0xc0000100
#define MID_8040DRIVE_CE1_CMD        0xc0000200
#define MID_8040DRIVE_2S1B_CMD       0xc0000300
#define MID_8040DRIVE_16AS_CMD       0xc0000400
#define MID_8040DRIVE_BRI_CMD        0xc0000500
#define MID_8040DRIVE_ETH1_CMD       0xc0000600
#define MID_8040DRIVE_ETH2_CMD       0xc0000700
#define MID_8040DRIVE_SA_CMD         0xc0000800
#define MID_8040DRIVE_8040_701_CMD   0xc0000900
#define MID_8040DRIVE_8040_701BRI_CMD   0xc0000910
#define MID_8040DRIVE_8040_701E1_CMD    0xc0000920
#define MID_8040DRIVE_8040_701T1_CMD    0xc0000930
#define MID_8040DRIVE_8040_701SER_CMD   0xc0000940

#define MID_8040DRIVE_701_CMD          0xc0000a00
#define MID_8040DRIVE_701BRI_CMD       0xc0000a10
#define MID_8040DRIVE_701E1_CMD        0xc0000a20
#define MID_8040DRIVE_701T1_CMD        0xc0000a30
#define MID_8040DRIVE_701SER_CMD       0xc0000a40


#define MID_GSR_XXX     0xfc000000 /*Reserve for GSR*/
#define MID_HGMP   0x00A20000

/* changed by sword */
#ifndef MID_SRM
#define MID_SRM     0xfcf00000  /* System Running Management */
#endif 

#ifndef MID_DLD
#define MID_DLD     0xfcf10000  /* Download */
#endif

#ifndef MID_MSS
#define MID_MSS     0xfcf20000  /* Master Slave Swap */
#endif

#ifndef MID_DIAG
/*                                诊断模块的ID 说明:                                              */
/*   使用四个诊断模块ID 纯粹是为了解决诊断命令CMO    */
/*   资源不够的问题。对于系统内其他模块来说，与    */
/*   诊断模块交互仅仅只可见MID_DIAG，其他几个不可见*/
/*       MID_DIAG            :  用于RPS与其他模块传递诊断信息时  */
/*                                     的源和目的模块ID，并用于RPS的诊断*/
/*                                     CMO定义                                                                    */
/*       MID_DIAG_RAIN   :  用于RAINIER诊断命令CMO的定义                 */
/*       MID_DIAG_2800   :  用于10G 诊断命令CMO的定义                       */
/*       MID_DIAG_IP6      :  用于IPv6 诊断命令CMO的定义                     */
#define MID_DIAG    0xfcf30000  /* Test & Diagnoise */
#define MID_DIAG_RAIN    0xfcfb0000 /* Test & Diagnoise for Rainier*/
#define MID_DIAG_2800    0xfcfc0000 /* Test & Diagnoise for 2800(10G)*/
#define MID_DIAG_IP6    0xfcfd0000  /* Test & Diagnoise for IPv6*/
#endif

#ifndef MID_IOAGT
#define MID_IOAGT   0xfcf40000  /* IO Board agent */
#endif

#ifndef MID_AGT
#define MID_AGT     0xfcf70000  /* AGT */
#endif

/* L2IF */ 
#define MID_L2IF        0xfce80000
#define MID_RSTP        0xfcea0000
#define MID_RMON     0x01a20000

#if(VRP_MODULE_RMON2 == VRP_YES)
#define MID_RMON2     0x01a30000
#define SID_RMON2_PRODIR    0x01
#define SID_RMON2_HLHTCTL   0x02
#define SID_RMON2_NLHT      0x03
#define SID_RMON2_BUILDRUN      0x04
#define SID_RMON2_IPCRPC             0x05
#define SID_RMON2_INF_KEY_NLHOSTTBL_S    0x06   
#endif

#define MID_GSR_YYY     0xfeff0000

#define MID_VLAN        0x009D0000
#define MID_RTPRO_VRF   0x009E0000

/*xmodem added by xuqingwei 2001-8*/
#define MID_XM          0x04200000

/*私有数据文件模块*/
#define MID_PDF         0x04300000

#define MID_SYSTEST     0x05000000 /*Added by m24267*/

/*multicast policy routing module*/
#define MID_IP_MCAST_POLICY               0x05100000

/* Commented by Krishnaraj */
/* #define MID_RTPRO_MSDP    0x06000000 */
#define MID_MSDP_TRACERT 0x06100000 

/*-------------------------------------------------*
 * 定义mtrace模块ID
 *-------------------------------------------------*/
#define MID_RTPRO_MTRACE 0x07000000

#define MID_TEST_PIM     0x08000000

/*VRPV3R001M07 backup 2002/11/06*/
#define MID_IB          0x09000000
#define MID_ETH_ACL       0x0a000000
/* VRPV3R001M06B03D003_BRIDGE_TZB 支持过滤以太帧头的ACL*/

#define MID_EF            0x0b000000
/* VRPV3R001M06B03D003_BRIDGE_TZB 支持在接口过滤以太帧头*/

#define MID_TB            0x0c000000
/* VRPV3R001M06B03D003_BRIDGE_TZB 支持透明网桥*/

#if (VRP_VERSION_5 == VRP_YES)
/*add by huke at aug 30 2003*/
/* MID of MPLS L2VPN module*/
#if ( VRP_MODULE_VPN_L2VPN == VRP_YES)
#define MID_VPN_L2VPN       0x99990000
#define MID_VPN_L2VPN_CFG   0x999A0000
#endif

#if ( VRP_MODULE_VPN_TNLM == VRP_YES)
#define MID_TNLM       0x99890000
#define MID_TNLM_CFG   0x998A0000
#endif

#if ( VRP_MODULE_VPN_L3VPN == VRP_YES)
#define MID_VPN_L3VPN  0x99690000 
#endif

#define MID_VPN_L3FIB  0x996A0000

#else

/* MID of MPLS L2VPN module*/
#if ( VRP_MODULE_VPN_L2VPN == VRP_YES)
#define MID_MPLS_L2VPN       0x99990000
#define MID_L2VPN_CFG   0x999A0000
#endif
#endif

#if( VRP_MODULE_LINK_IPX == VRP_YES )
#define MID_IPX     0x0a000000
#define MID_IPX_RIP     0x0a100000
#define MID_IPX_SAP     0x0a200000
#define MID_IPX_RM     0x0a300000
#define MID_IPX_RM1    0x0a400000
#endif

/* Begin by tianli29125 2001-12-10 for merging WCCP module */
#if (VRP_MODULE_WCCP2 == VRP_YES) 
#define MID_WCCP2       0xdd100000
#define SID_WCCP2_ENQ  0x0001
#define SID_WCCP2_RPL   0x0002
#define SID_WCCP2_BUILDRUN   0x0003
#define SID_WCCP2_SHOWINFO  0x0004
#endif
/* Finish by tianli29125 2001-12-10 for merging WCCP module */

#if(R8070_MODULE_SECP == VRP_YES)
#define MID_IPSEC_SECP              0xdd4b0000
#define MID_IKE_SECP                0xdd4c0000
#define MID_SECP                    0xdd4a0000
#endif

/* DLSW */
#if(VRP_MODULE_LINK_DLSW == VRP_YES)
#define MID_8070_DLSW               0xdd450000
#define MID_DLSW_LLC2                0xdd460000
#endif

/*SDLC*/                             
#if(VRP_MODULE_LINK_SDLC == VRP_YES)
#define MID_SDLC                      0xdd320000
#endif

/*show tech*/
#if(VRP_IO_BOARD == VRP_NO)/*jipeng27905 for "show tech"*/
#define MID_8070_SHOWTECH         0xdd350000 
#define SID_CLI_ST_ULONG              0x0001
#define SID_CLI_ST_CMD_KEY_S          0x0002
#define SID_CLI_ST_SHOW_TECH_S        0x0003
#endif
#if(VRP_MODULE_BAS_CM == VRP_YES)
#define MID_CM         0x0a500000
#endif
#if(VRP_MODULE_BAS_ACM == VRP_YES)
#define  MID_ACM       0x0a600000
#endif
#if(VRP_MODULE_BAS_WEB == VRP_YES)
#define MID_WEB        0x0a700000
#endif
#if(VRP_MODULE_BAS_RADIUS == VRP_YES)
#define MID_RADIUS     0x0a800000
#endif
#if(VRP_MODULE_BAS_AAA == VRP_YES)
#define MID_AAA        0x0a900000
#endif
#if(VRP_MODULE_BAS_HWTACACS == VRP_YES)
#define MID_TAC        0x0aa0000
#endif
#if(VRP_MODULE_BAS_LAM == VRP_YES)
#define MID_LAM        0x0ab00000
#endif

#if( VRP_MODULE_LICENSE == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )    
#if( VRP_MODULE_VOS_VFS == VRP_YES && VRP_MODULE_VOS_VFS_FLS == VRP_YES )  
/* LICENSE的模块ID */
#define MID_LCNS 0x0ac00000
#endif
#endif
#endif
#if (VRP_MODULE_IP_ARP_PROXY == VRP_YES)
#define MID_IP_ARP_PROXY 0xdd270000
#endif
#if(VRP_MODULE_DAMP_SUPPRESS==VRP_YES)
#define MID_DAMP_SUPPRESS 0xdd280000
#endif
#if (VRP_VERSION_5 == VRP_YES)
#define VOS_MID_GADS                  0xde000000
#define VOS_MID_SYSTRACE              0xdf000000
#endif
#if (VRP_MODULE_QUEFWD == VRP_YES )
#define  SID_QUEFWD_RPC      0x671
#define  MID_QUEFWD              0xdd310000
#endif 

#if (VRP_MODULE_FINGER == VRP_YES)
#define MID_IP_FINGER 0x0ad00000
#define SID_FINGER_BUILDRUN 0x0001
#define SID_FINGER_CLIENT 0x0002
#define SID_FINGER_DRV 0x0003
#define SID_FINGER_USERINFO  0x0004

#endif

/*Added by pengjimei for 8070 IP特性移植项目. 2004/04/21*/
#define MID_IP_RPC      0xdd330000
/*END*/
#define  MID_IP_PBR                      0xe0000000
/*********************IPC/VP channel id************************************/
/*IPC Tunnel IDs*/
#define TID_IPC_IKE_KEY     10
#define TID_IPC_L2TP        11
#define TID_IPC_IPSEC_KEY   12
#define TID_IPC_IPSEC_CMD   13

/*IP*/
#define TID_IPC_MAINIP      14
#define TID_IPC_IPCMD       15 
#define TID_IPC_IPDBG       16

/*IC*/
#define TID_IPC_IC      17
/* ARPCMD*/
#define TID_IPC_ARPCMD      18

/*RPC*/
#define TID_IPC_RPC_CHANNEL 19

/* FR */
#define TID_IPC_FR      20

/*  added by fxy   */
#define TID_IPC_ARPDBG      24
#define TID_IPC_ETHDBG      25

#define VRP_IPC_IFNET       26

#define RTSYN_IPC_ID        27

#define CFA_IPC_CHANNEL     28

/* MP */
#define MP_IPC_CHID         29
#define MP_IPC_MAIN_IO_CHID 30

/* ip policy routing zhaobiao*/
#define TID_IPC_IP_POLICY   31    /*max tunnel id is 49*/

/* VRRP */
#define TID_IPC_VRRP        32

/*guofanglu*/
#define TID_IPC_QOS     33

#define TID_IPC_VOS     34

#define TID_IPC_MRT     35

/* IPC channel for multicast policy routing*/
#define TID_IPC_MCAST_POLICY     36


/* dengyiou 2004-09-16 for IAS */
/*#if( VRP_MODULE_MPLS_LSPAGT == VRP_YES )*/
#define TID_IPC_LSPAGT      37
/*#endif*/
/* DDR */
#define TID_IPC_DDR        38

#if( VRP_MODULE_LINK_X25_SWITCH == VRP_YES )
#define TID_IPC_X25     39
#endif

#if ( VRP_MODULE_LINK_DLSW == VRP_YES )
#define TID_IPC_DLSW_BRIDGE      40
/* add by libingshan for backup peer */
#define TID_IPC_DLSW      41 
#define TID_IPC_DLSW_REACH 42
#endif
#if( VRP_MODULE_TB_BASE == VRP_YES )
/* VRPV3R001M06B03D003_BRIDGE_TZB 支持透明网桥*/
#define TID_IPC_TB       43
#endif
#define NE80_IPC_START_ID  50  /* vrp CFA */

/* RPS IO_Agent */
#define TID_IPC_RPSIOAGT    51

/* SRM IPC CHannel ID */
#define TID_IPC_SRM         52

/* rps srm ipc channel */
#define TID_IPC_DIAG_ID     53

/* VRRP 32 IN VRP */

#define TID_IPC_ETA     56
#if( NE80_MODULE_DPT == VRP_YES )
#define TID_IPC_DPT     57
#endif
/*Modified by wzx24732IPV6*//*jipeng27905 for ipv6 tunnel*/
#if((MODULE_GRE_8011 == VRP_YES)||(MODULE_TUNNEL_8011 == VRP_YES))
#define TID_IPC_GRE     58
#endif
#define TID_IPC_LSPAGT_ID    59 /*  36 - SMITH */ /*NE80_IPC_START_ID + 4*/

/*add by anhongjie for D21775*/
#define TID_IPC_VOS_ASSERT   60
/*add by anhongjie for D21775*/

/* L2IF */
#define TID_IPC_L2IF_ID   61

#define TID_IPC_PROXYMSG  62

#define TID_IPC_CQC_ID     63
#if (VRP_MODULE_IPTN_BASE == VRP_YES)
#define IPTNSYN_IPC_ID      44
#endif
#define TID_IPC_CM          64
#define TID_IPC_AAA         65
#define TID_IPC_ADMIN       66
#define TID_IPC_IP          67
#define TID_IPC_ARP         68
#define TID_IPC_FC          69
#define TID_IPC_PPP         70
#define TID_IPC_DHCPR       71
#define TID_IPC_WEB         72
#define TID_IPC_RADIUS      73
#define TID_IPC_TAC         74

/* dengyiou 2004-09-15 for IAS pruning */
#define TID_IPC_HA          78
#define TID_IPC_BLS_REPORT  79

#if (VRP_MODULE_IPV6 == VRP_YES)

/*#if (VRP_MODULE_FIB6CONTR == VRP_YES || VRP_MODULE_FIB6AGENT == VRP_YES)*/
#define IP6_FIBAGENT_IPC_ID 75
#define IP6_FIBCONTR_IPC_ID 76
/*#endif*/


#if (VRP_MODULE_IPV6 == VRP_YES)
#define IPV6_PMTU_CHNL_ID     80
#endif

#if (VRP_MODULE_NATPT == VRP_YES)||(MODULE_NATPT_8011 == VRP_YES)
#define NATPT_IPC_CHNL_ID   81
#endif

/* Begin : Defect ID: BYAD12114,     Modifier:Rajesh,   Date:2004/10/21 
Reason   : IPC RPC synch call must not be called from sock run context*/

#define IPV6_ADDR_CHNL_ID         82


#endif /* VRP_MODULE_IPV6*/


#define TID_IPC_ND_ID          82


/* FOR LSP */
#if (VRP_YES == VRP_MODULE_HA_SLAVE2MAIN  && VRP_NO == VRP_MODULE_HA_DATA)
#define TID_IPC_GR_LSPAGT_ID          83
#endif

/* FOR FIBv4*/
#if (VRP_YES == VRP_MODULE_HA_SLAVE2MAIN && VRP_NO == VRP_MODULE_HA_DATA)
#define TID_IPC_GR_FIBV4AGT_ID          84
#endif
/* end of addition */

 #if (VRP_MODULE_IP_MCAST_FORWARD==VRP_YES)
 #define TID_IPC_MFIB                 35
 #endif

/******************VP***********************/
/*VP Tunnel IDs*/
#define TID_VP_L2TP     10

/*IC*/
#define TID_VP_IC       11

/* FR */
#define TID_VP_FR       12

/* add by xiaoshouhe for MRT*/
#define TID_VP_MRT      13

#define TID_VP_ASSERT   14

#define TID_VP_MEMMON   15

#if( VRP_MODULE_LINK_X25_SWITCH == VRP_YES )
#define TID_VP_X25      16
#endif

#if (VRP_MODULE_IP_MCAST_FORWARD==VRP_YES)
 #define TID_VP_MFIB                 17
 #endif


/*******************MBUF TR ID**************************/
#define MBUF_TR_IP_IFOUTPUT         0x00000000
#define MBUF_TR_IP_DELIVERTOUP      0x00000001
#define MBUF_TR_IP_OPTION           0x00000002
/* MP */
#define MP_MBUF_TR_RCV              0x00000003

#define MBUF_TR_IFNET               0x00000004

#define MBUF_TR_ISIS_OUTPUT         0x00000005
#define MBUF_TR_ISIS_INPUT         0x00000006
#define MBUF_TR_L2TP_LAC           0x00000007

#define MBUF_TR_IP_MFORWARD_ID      0x00000008      /* forward send mbuf to main board */
#define   MPLS_OUTPUT_ID               0x00000009 
#if( VRP_MODULE_IP_MPLS_SOFTFW == VRP_YES )
#define MBUF_TR_MPLSFW_OUTPUT       0x00000009
#endif
#if (VRP_PRODUCT_GSR != VRP_YES)
#define MBUF_TR_GRE_INPUT           0x0000000a      /*用于tunnel/src分离，板间透传*/
#endif
#if( VRP_MODULE_LINK_X25_SWITCH == VRP_YES )
#define MBUF_TR_X25_SWITCH      0x0000000b
#endif
/*addition end for X25ENH*/

/* addef for ipsec nat-traversal */
#define MBUF_TR_IP_INPUT            0x0000000c
/* end */

#if( VRP_MODULE_TB_BASE == VRP_YES )
/* VRPV3R001M06B03D003_BRIDGE_TZB 支持透明网桥*/
#define MBUF_TR_ETHFRAME_BRIDGE       0x00000020
#endif

#if (VRP_PRODUCT_GSR == VRP_YES)
#if (NE80_MODULE_ADP == VRP_YES)    /*add by tshi*/
#define MBUF_TR_QOS_SAMPLE_ID       0x0000000a      /* QOS SAMPLE*/
#endif


#if (L3_MODULE_RSTP == VRP_YES)
#define MBUF_TR_RSTPR               0x0000000d
#endif

#if (L3_MODULE_HGMP == VRP_YES)
#define MBUF_TR_HGMP                0x0000000e
#endif

#define MBUF_TR_GRE_INPUT           0x0000000f      /*用于tunnel/src分离，板间透传, Guo yuedong modefied from 0x0000000a to 0x0000000f*/
#endif
#if (VRP_PRODUCT_GSR == VRP_YES)

#define MBUF_TR_FSU_LOG             0x00000010       /* ADDED FOR FSU_LOG  */
#endif /*(VRP_PRODUCT_GSR == VRP_YES)*/
#if (VRP_MODULE_LINK_DLSW == VRP_YES)
#define MBUF_TR_DLSW_BRIDGE             0x00000021
#define MBUF_TR_DLSW_SSP                0x00000022
#endif

#if( R8070_MODULE_SECP == VRP_YES )
#define MBUF_TR_SECP_IO             0x00000011
#define IPSEC_OUTPUT_ID             0x00000012
#endif

/* added by chenxia for TTL处理 */
#define MBUF_TR_IP_TRCHANNEL       0x00000013
#define MBUF_TR_FR              0x00000014

#if (VRP_MODULE_IPV6 == VRP_YES)
#define MBUF_TR_IP6_IFOUTPUT                0x0000001A
#define MBUF_TR_IP6_ProcessInMainBoard      0x0000001B
#define MBUF_TR_NATPT                       0x0000001C
#define MBUF_TR_ICMP6_DELIVEREDTOUP         0x0000001D
#endif


#if ( (VRP_PRODUCT_GSR == VRP_YES ) ||( VRP_MODULE_IPV6_SIMULATE == VRP_YES ) )
#define MBUF_TR_IP6_PLATFORM_IN             0x0000001E
#define MBUF_TR_IP6_PLATFORM_OUT            0x0000001F
#endif

#define MBUF_TR_LSPV                        0x00000020

/***************WaitList******************************/
/* SHOW FIB*/
#define FIB_MAINTYPE            1001
/* SHOW ARP */
#define ARP_ENTRY_MAINTYPE      1002
#define ARP_MTSOFT_MAINTYPE     1003
/* SHOW IP ADDR */
#define IP_ADDR_LIST            1004
/* FRAME-RELAY */
#define FR_WAIT_LIST_MAIN_TYPE  1005
/* DEBUG  */
/* INFO CENTER  */
#define IC_EXEC_CHAIN           1006
#define IC_OUT_CHAIN            1007
/*ISDN*/
#define ISDN_ACTIVE_CCB_MAINTYPE            1008
#define ISDN_ACTIVE_DCH_MAINTYPE            1009

#define Q921_INTF_LIST          1010

#define DDR_SHOWDIALER_DDR      1011
#define DDR_SHOWDIALER_MAP      1012

#if (VRP_VERSION_5 == VRP_YES)
/* move to file end */
#else
/* bgp */
#define ASPATHLIST_TYPE         1013
#define NETWORK_RECORD_TYPE     1014
#define BGPGROUP_TYPE           1015
#define BGPPEERGROUP_TYPE       1016
#define BGPPEER_TYPE            1017
#define BGPINSTANCE_TYPE        1200

/* ospf */
#define WAITLIST_OSPF_LSDB          1018
#define WAITLIST_OSPF_NBR           1019
#define WAITLIST_OSPF_NEXTHOP       1020
#define WAITLIST_OSPF_AREA          1021
#define WAITLIST_OSPF_ROUTE         1022
#define WAITLIST_OSPF_INTF          1023
#endif

#define RM_RADIX_TREE_TYPE    1029

/*PPPOE*/
#define PPPOE_WAIT_LIST_MAIN_TYPE   1030

/* MP */
#define MP_WAIT_LIST_MAIN_TYPE      1031

/*ATM*/
#define ATM_WAIT_LIST_MAIN_TYPE     1032

/* X25 */
#define X25_WAIT_LIST_MAIN_TYPE     1033

/* ARP & TCP */
#define ARP_IP_MAINTYPE            1034      
#define TCP_PCB_MAINTYPE            1035

#if (VRP_VERSION_5 == VRP_YES)
/* move to file end */
#else
/* ISIS */
#define WAITLIST_ISIS_NBR           1036
#define WAITLIST_ISIS_ROUTE         1037
#define WAITLIST_ISIS_DATABASE      1038
#define WAITLIST_ISIS_SPFLOG        1039
#define WAITLIST_ISIS_INTERFACE     1201
#endif

/* CFM */
#define CFM_SECTION_NODE_CHAIN      1040

/* IPSEC */
#define IPSEC_WAITLIST_MAP_IFINDEX      1041
#define IPSEC_WAITLIST_TDBENTRY         1042
#define IPSEC_WAITLIST_DYNA_TDBENTRY    1043
#define IPSEC_WAITLIST_TRANSFORM        1044
#define IPSEC_WAITLIST_MAP_LIST         1045
#define IPSEC_WAITLIST_MAPHEAD_LIST     1046

/* IKE */
#define IKE_WAITLIST_POLICY          1047
#define IKE_WAITLIST_IKE_SA          1048
#define IKE_WAITLIST_PRESHARED_KEY  1049



/* RTP */
#define WAITLIST_ROUTEMAP     1050
#define WAITLIST_ROUTEMAP_NODE    1051
#define WAITLIST_IP_COMMUNITY_LIST 1052
#define WAITLIST_IP_PREFIX_LIST      1053
#define WAITLIST_IP_PREFIX_NODE     1054

#define WAITLIST_IFPR_NODE           1055
#define WAITLIST_VRRPSTANDBY_NODE   1056

/*#if(VRP_MODULE_MPLS_LSPM == VRP_YES)*/
#define L3FIB_WAITLIST_XC_TYPE            1900
#define L3FIB_WAITLIST_INSEG_TYPE        1901
#define L3FIB_WAITLIST_OUTSEG_TYPE        1902
#define L3FIB_WAITLIST_SHWFWT_TYPE        1903  
#define L3FIB_WAITLIST_SHWFWT_VPN_TYPE        1904  
#define L3FIB_WAITLIST_SHWMPLSSTAT_TYPE     1905 
/*#endif*/


/* MVLAN MQT */
#if (VRP_MODULE_MVLAN == VRP_YES)
#define LSPM_WAITLIST_GATEWAY_SHWNHLFE_TYPE     1909
#define LSPM_WAITLIST_GATEWAY_SHWASBR_TYPE     1910 
#endif


#if(VRP_MODULE_MPLS_LDP == VRP_YES)
#define LDP_WAITLIST_VRF_TYPE            2004
#define LDP_WAITLIST_LOCAL_ENTITY_TYPE   2005
#define LDP_WAITLIST_PEER_TYPE           2006
#define LDP_WAITLIST_REMOTE_ENTITY_TYPE  2007
#define LDP_WAITLIST_FEC_TYPE            2009
#define LDP_WAITLIST_ADV_FEC_TYPE        2010
#define LDP_WAITLIST_CRLSP_TYPE          2011
#define LDP_WAITLIST_HSB_PEER_TYPE       2012
#define LDP_WAITLIST_HSB_FEC_TYPE        2013
#define LDP_WAITLIST_HSB_CRLSP_TYPE      2014
#endif

#if ( VRP_MODULE_VPN_L2VPN == VRP_YES)
/* Wait List主类型 */
#define L2VPN_WAITLISTTYPE_CCCCONN      2100
#define L2VPN_WAITLISTTYPE_LDPCONN      2101
#define L2VPN_WAITLISTTYPE_SVCCONN      2102
#define L2VPN_WAITLISTTYPE_BGPVPN       2103
#define L2VPN_WAITLISTTYPE_BGPCONN      2104
#define L2VPN_WAITLISTTYPE_BGPCE        2105
#define L2VPN_WAITLISTTYPE_BGPLLB       2106
#define L2VPN_WAITLISTTYPE_BGPRMTCE     2107
#define L2VPN_WAITLISTTYPE_BGPRMTLB     2108
#define L2VPN_WAITLISTTYPE_BGPRT        2109
#if (VRP_VERSION_5 == VRP_YES)
#define L2VPN_WAITLISTTYPE_CCCENCAP     2110
#endif
#endif

/* SHOW */
/* INFO CENTER  */
#define IC_LOGBUF_CHAIN         1057
#define IC_MASKTAB_CHAIN            1058
#define IC_TRAPBUF_CHAIN            1059

/* IFNET */
#define IF_SEARCH_CONFIG_CHAIN  1000
#define IF_WAITLIST_TREE_NODE   1060

/* MSDP */
#define MSDP_PEER_WAITLIST_TYPE  1061
#define MSDP_SGT_WAITLIST_TYPE   1062


/* add for D16109 */
#define WAITLIST_VRIB_LIST            1066


/*VRF*/
#define WAITLIST_VRF_DETAIL           1067
#define WAITLIST_INTERFACE            1068
#define WAITLIST_ROUTETARGET          1069

/* RM */
#define WAITLIST_RM_VRIBLIST_TYPE     1070

/* 组播路由表MRT和组播转发表MFC的WaitList定义, sunshengtao 2002/8/14 added */
#define MRT_SRC_WAITLIST_TYPE         1071
#define MFC_SRC_WAITLIST_TYPE         1072

#if ( VRP_MODULE_RTPRO_BGP_L2VPN == VRP_YES )
/* bgp l2vpn */
#define BGP_L2VPN_WAITLIST_TYPE       1111
#endif


/*SSH*/
#define SSH_USER_WAITLIST_CHAIN       1075
#define RSA_WAITLIST_PEER_PUBKEYS      1076

#if(R8070_MODULE_SECP == VRP_YES)
#define SECP_WAITLIST_LINKCB          3001
#define SECP_WAITLIST_RELATION        3002
#endif

#if( VRP_MODULE_LINK_PPPOE_CLIENT == VRP_YES )
#define PPPOE_CLIENT_WAIT_LIST_MAIN_TYPE    1077
#endif

#define IKE_WAITLIST_PEER          1078
#define IKE_WAITLIST_IKEPEER       1079

/*#if ( VRP_MODULE_DNS_CLIENT == VRP_YES )*/
#define WAITLIST_DNS_CACHE         1073
/*#endif*/
#if( VRP_HWPING_SNMP == VRP_YES)
#define HWPING_WAIT_LIST_MAIN_TYPE  1080
#define HWPINGHIS_WAIT_LIST_MAIN_TYPE 1081

#endif
#if( VRP_MODULE_LINK_IPX == VRP_YES )
#define IPX_ADDR_MAIN_TYPE 1100

#define IPXRM_WAITLIST_RTHEAD      1101
#define IPXRM_WAITLIST_RT          1102
/*end of addition by liuxueqin for IPXRM on 2003/05/19*/
#define IPXSAP_WAITLIST_THT 1105
#define IPXSAP_WAITLIST_NHT 1106
#define IPXSAP_WAITLIST_SIT_FROM_THT  1107
#define IPXSAP_WAITLIST_SIT_FROM_NHT  1108
#define IPXSAP_WAITLIST_INACTIVE_SIT  1109
#endif
#if ( VRP_MODULE_LINK_DLSW == VRP_YES )
/* for DLSW  */
#define DLSW_LLC2_WAIT_LIST_MAIN_TYPE   5003
#define WAITLIST_DLSW_BRIDGEENTRY_NODE  5004
#define WAITLIST_DLSW_CIRCUIT_NODE  5005
#define WAITLIST_DLSW_REACH_NODE   5006
#endif

#if(VRP_MODULE_VPN_TNLM == VRP_YES)
#define TNLM_WAITLISTTYPE_TNLPLCY      2210 
#define TNLM_WAITLISTTYPE_TNLINFO      2211 
#endif

/* For VRPv5 Adapt, scope 2300 ~ 2500 reserved */
#if (VRP_VERSION_5 == VRP_YES)
/* BGP WAITLIST TYPE */
#define ASPATHLIST_TYPE                 2300
#define NETWORK_RECORD_TYPE             2301
#define BGPGROUP_TYPE                   2302
#define BGPPEERGROUP_TYPE               2303 
#define BGPPEER_TYPE                    2304
#define BGPINSTANCE_TYPE                2305
#define BGPRIBIn_TYPE                   2306
#define BGPInstance_TYPE                2307
#define BGPRIBOut_TYPE                  2308
#define BGPPath_TYPE                    2309
#define BGPRD_TYPE                      2310    /*Janvin,2004-oct-14,D01965*/

/* OSPF WAITLIST TYPE */
#define WAITLIST_OSPF_SHAM_LINK         2315
#define WAITLIST_OSPF_LSDB              2320
#define WAITLIST_OSPF_NBR               2321
#define WAITLIST_OSPF_NEXTHOP           2322
#define WAITLIST_OSPF_AREA              2323
#define WAITLIST_OSPF_ROUTE             2324
#define WAITLIST_OSPF_INTF              2325
#define WAITLIST_OSPF_PROCESS           2326 
#define WAITLIST_OSPF_VLNK              2327
#define WAITLIST_OSPF_ROUTER_LSA_PIECE  2328
#define WAITLIST_OSPF_NETWORK_LSA_PIECE 2329
#define WAITLIST_OSPF_CRYPT             2330
#define WAITLIST_OSPF_DOMAINID          2331
#define WAITLIST_OSPF_ADDR              2332
#define WAITLIST_OSPF_HOST              2333
#define WAITLIST_OSPF_VLINK             2334
#define WAITLIST_OSPF_NETWORKCMD        2335
#define WAITLIST_OSPF_MATCHGRP          2336
#define WAITLIST_OSPF_MATCHGRP_ELEMENT  2337
#define WAITLIST_OSPF_INST              2338
#define WAITLIST_OSPF_MATCHGRP_ELEMENT_EXT  2339

/* RM WAITLIST TYPE */
#define WAITLIST_RM_TASK                2340
#define WAITLIST_RM_RDX                 2341
#define WAITLIST_RM_SLL                 2342
#define WAITLIST_RM_RDX6                2343

/* ISIS WAITLIST TYPE */
#define WAITLIST_ISIS_NBR               2360
#define WAITLIST_ISIS_ROUTE             2361
#define WAITLIST_ISIS_DATABASE          2362
#define WAITLIST_ISIS_SPFLOG            2363
#define WAITLIST_ISIS_INTERFACE         2364
#define WAITLIST_ISIS_REDIST            2365
#define WAITLIST_ISIS_DYNNAME           2366
#define WAITLIST_ISIS_TELINKLIST        2367
#define WAITLIST_ISIS_TELINKNODE        2368
#define WAITLIST_ISIS_TENW              2369
#define WAITLIST_ISIS_PROCESS           2370
#define WAITLIST_ISIS_SUMMRT            2371
#define WAITLIST_ISIS_SUMMRT_V6         2372

/* RIP WAITLIST TYPE */
#define RIP_WAITLIST_TRIPNBR            2380
#define RIP_WAITLIST_INSTANCE           2381
#define RIP_WAITLIST_PROC               2382
#define RIP_WAITLIST_RADIX              2383
#define RIP_WAITLIST_NBRRT              2384
#define RIP_WAITLIST_NBR                2385
#define RIP_WAITLIST_PHYIF              2386

#define WAITLIST_TYPE_VOS_RADIX         2400

#define CSPF_WAITLIST_LINKLIST_TYPE      2420
#define CSPF_WAITLIST_NODELIST_TYPE      2421
#define CSPF_WAITLIST_USEDNODELIST_TYPE  2422
#define CSPF_WAITLIST_NWLSA_TYPE         2423

#if (VRP_MODULE_IPV6 == VRP_YES)
#define IP6_WAITLIST_UNICASTADDR        2500
#define IP6_WAITLIST_MULTICASTADDR      2501
#define WAITLIST_NEIGHBORENTRY_NODE     2502
#define WAITLIST_ACL6_LIST              2504
#define TCP6_PCB_MAINTYPE               2503
#endif


/* #define WAITLIST_DNS_CACHE              2505 */

#if (VRP_MODULE_NATPT == VRP_YES)||(MODULE_NATPT_8011 == VRP_YES)
#define WAITLIST_NATPT_DPATMAP          2506
#define WAITLIST_NATPT_ADDRMAP          2507
#define WAITLIST_NATPT_SESSIONMAP       2508
#define WAITLIST_NATPT_FRAGMAP          2509
#endif

#if (VRP_MODULE_IPV6 == VRP_YES)
#define WAITLIST_PMTUENTRY_NODE         2510 
#endif

#endif

#if(VRP_MODULE_BAS_ACM == VRP_YES)
#define  WAITLIST_BAS_ACM_IPACB       5100
#define  WAITLIST_BAS_ACM_ARPACB      5101
#define  WAITLIST_BAS_ACM_DHCPACB     5102
#define  WAITLIST_BAS_ACM_DNATACB     5103
#endif


#if(VRP_MODULE_IP_MCAST_FORWARD==VRP_YES)
#define WAITLIST_MFIB_MAINTYPE  5200
#endif

#if ( VRP_MODULE_RTPRO_MRM==VRP_YES)
#define WAITLIST_MRM_TYPE_DIS_MEM 5201 
#define WAITLIST_MRM_TYPE_DLL     5202
#define WAITLIST_MRM_TYPE_GCQ     5203
#endif

#if ( VRP_MODULE_RTPRO_PIM==VRP_YES)
#define WAITLIST_PIM_STATIC_RP    5204
#define WAITLIST_PIM_TSI_ID       5205
#define WAITLIST_PIM_TSI_SRC_LIST  2599
#endif



#if(CQC_8011 == VRP_YES)  
#define WAITLIST_CQC_SAMP_TYPE          2001
#define WAITLIST_CQC_MAC_GROUP_TYPE     2002
#define WAITLIST_NE80_QOS_ACLNODE_TYPE  2003    /**added by tshi for QOS_WaitList_TBL**/
#define WAITLIST_NE80_QOS_CARBAK_TYPE   2004
#endif

/* NE80R003_NAT_JIANGXIAOBO */
#define WAITLIST_NAT_POOL           1090
#define WAITLIST_NAT_SERVER         1091
#define WAITLIST_NAT_MATCHHOST      1092    

#define WAITLIST_TUNNEL               1093
#if (VRP_MODULE_MVLAN == VRP_YES)
#define WAITLIST_MVLAN_GATEWAYTYPE            1094
#endif

#define  RPS_TID_NAT            0xfcfa0000
/*In case of the C++.*/
/* ARP PROXY */
#define PROXYARP_ENTRY_MAINTYPE 1155

#if( VRP_MODULE_RMON2 == VRP_YES )
#define RMN2_WAITLIST_PROTOCOLDIRTBL  1200
#define RMN2_WAITLIST_HOSTCTRLTBL  1201
#define RMN2_WAITLIST_HOSTTBL  1202
#define RMN2_WAITLIST_INF_PROTOCOLDIRTBL  1203
#endif

#define WAITLIST_PBROUTEMAP_NODE   2511

/* Added by Guru for BYAD11532 */
#define FIB6_MAINTYPE  1025
/* End of addition by Guru for BYAD11532 */

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif


#endif/*End of the file. */
