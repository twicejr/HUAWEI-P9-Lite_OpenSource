

#ifndef __NASFILEID_H__
#define __NASFILEID_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 结构名称    :NAS_FILE_ID_DEFINE_ENUM
 使用说明    :NAS 可维可测 FILE ID
*****************************************************************************/
typedef enum
{
                  NAS_FILE_ID_NASCOMMBUFFER_C = 0,
/*  1    */       NAS_FILE_ID_NASCOMMDEBUG_C,
                  NAS_FILE_ID_NASCOMMPRINT_C,
                  NAS_FILE_ID_NASEMMATTACH_C,
                  NAS_FILE_ID_NASEMMATTACHAPPMSGPROC_C,
                  NAS_FILE_ID_NASEMMATTACHCNMSGPROC_C,
                  NAS_FILE_ID_NASEMMATTACHESMMSGPROC_C,
                  NAS_FILE_ID_NASEMMATTDETMRRCMSGPROC_C,
                  NAS_FILE_ID_NASEMMDETACH_C,
                  NAS_FILE_ID_NASEMMDETACHAPPMSGPROC_C,
                  NAS_FILE_ID_NASEMMDETACHCNMSGPROC_C,
/*  11   */       NAS_FILE_ID_NASEMMGUTI_C,
                  NAS_FILE_ID_NASEMMIDEN_C,
                  NAS_FILE_ID_NASEMMMRRCCONNEST_C,
                  NAS_FILE_ID_NASEMMMRRCREL_C,
                  NAS_FILE_ID_NASEMMPLMN_C,
                  NAS_FILE_ID_NASEMMPLMNPUBLIC_C,
                  NAS_FILE_ID_NASEMMPUBUCNMSGDECODE_C,
                  NAS_FILE_ID_NASEMMPUBUMAIN_C,
                  NAS_FILE_ID_NASEMMPUBUENTRY_C,
                  NAS_FILE_ID_NASEMMPUBUGLOBAL_C,
/*  21   */       NAS_FILE_ID_NASEMMPUBSUSPEND_C,
                  NAS_FILE_ID_NASEMMPUBURESUME_C,
                  NAS_FILE_ID_NASEMMSECUAUTH_C,
                  NAS_FILE_ID_NASEMMSECUPROTECT_C,
                  NAS_FILE_ID_NASEMMSECUOM_C,
                  NAS_FILE_ID_NASEMMSECUSMC_C,
                  NAS_FILE_ID_NASEMMSECUSOFTUSIM_C,
                  NAS_FILE_ID_NASEMMSERVICEPROC_C,
                  NAS_FILE_ID_NASEMMSERVICEABNORMAL_C,
                  NAS_FILE_ID_NASEMMSERVICESERREQ_C,
/*  31   */       NAS_FILE_ID_NASEMMSERVICESERSTOP_C,
                  NAS_FILE_ID_NASEMMTAUABNORMAL_C,
                  NAS_FILE_ID_NASEMMTAUACP_C,
                  NAS_FILE_ID_NASEMMTAUPROC_C,
                  NAS_FILE_ID_NASEMMTAUREJ_C,
                  NAS_FILE_ID_NASEMMTAUREQ_C,
                  NAS_FILE_ID_NASEMMCMAIN_C,
                  NAS_FILE_ID_NASEMMCPUBLIC_C,
                  NAS_FILE_ID_NASEMMCRCVMSG_C,
                  NAS_FILE_ID_NASEMMCSENDMSG_C,
/*  41   */       NAS_FILE_ID_NASMMPUBLIC_C,
                  NAS_FILE_ID_NASMMPUBMENTRY_C,
                  NAS_FILE_ID_NASMMPUBMFSM_C,
                  NAS_FILE_ID_NASMMPUBMNVIM_C,
                  NAS_FILE_ID_NASMMPUBMNVIMOSA_C,
                  NAS_FILE_ID_NASMMPUBMOM_C,
                  NAS_FILE_ID_NASMMPUBMPRINT_C,
                  NAS_FILE_ID_NASMMPUBMSTACK_C,
                  NAS_FILE_ID_NASMMPUBMTMER_C,
                  NAS_FILE_ID_NASMMPUBMINTRAMSG_C,
/*  51   */       NAS_FILE_ID_NASMMPUBMMSGBUF_C,
                  NAS_FILE_ID_NASMMTEST_C,
                  NAS_FILE_ID_NASESMAPPMSGPARAPROC_C,
                  NAS_FILE_ID_NASESMAPPMSGPROC_C,
                  NAS_FILE_ID_NASESMMAIN_C,
                  NAS_FILE_ID_NASESMEMMMSGPROC_C,
                  NAS_FILE_ID_NASESMIPMSGPROC_C,
                  NAS_FILE_ID_NASESMNWMSGDECODE_C,
                  NAS_FILE_ID_NASESMNWMSGENCODE_C,
                  NAS_FILE_ID_NASESMNWMSGPROC_C,
/*  61   */       NAS_FILE_ID_NASESMOMMSGPROC_C,
                  NAS_FILE_ID_NASESMRABMMSGPROC_C,
                  NAS_FILE_ID_NASESMPUBULIC_C,
                  NAS_FILE_ID_NASESMTEST_C,
                  NAS_FILE_ID_NASESMNWMSGBEARERRESALLOCPROC_C,
                  NAS_FILE_ID_NASESMNWMSGBEARERRESMODPROC_C,
                  NAS_FILE_ID_NASESMNWMSGPDNCONPROC_C,
                  NAS_FILE_ID_NASESMNWMSGPDNDISCOCPROC_C,
                  NAS_FILE_ID_NASESMTIMERMSGPROC_C,
                  NAS_FILE_ID_NASRABMAPPMSGPROC_C,
/*  71   */       NAS_FILE_ID_NASRABMEMMMSGPROC_C,
                  NAS_FILE_ID_NASRABMESMMSGPROC_C,
                  NAS_FILE_ID_NASRABMIPFILTER_C,
                  NAS_FILE_ID_NASRABMIPFOM_C,
                  NAS_FILE_ID_NASRABMIPMSGPROC_C,
                  NAS_FILE_ID_NASRABMMAIN_C,
                  NAS_FILE_ID_NASRABMPDCPMSGPROC_C,
                  NAS_FILE_ID_NASRABMRRCMSGPROC_C,
                  NAS_FILE_ID_NASRABMTCMSGPROC_C,
                  NAS_FILE_ID_NASRABMTEST_C,
/*  81   */       NAS_FILE_ID_NASRABMTIMERMSGPROC_C,
                  NAS_FILE_ID_IPDHCPV4SERVER_C,
                  NAS_FILE_ID_IPIPMGLOBAL_C,
                  NAS_FILE_ID_IPIPMIFACE_C,
                  NAS_FILE_ID_IPIPMMSGPROC_C,
                  NAS_FILE_ID_IPIPMOM_C,
                  NAS_FILE_ID_IPIPMREG_C,
                  NAS_FILE_ID_NASTCEMMMSGPROC_C,
                  NAS_FILE_ID_NASTCMAIN_C,
                  NAS_FILE_ID_LNASREPLAYPROC_C,
/*  91   */       NAS_FILE_ID_NASTCNWMSGDECODE_C,
                  NAS_FILE_ID_NASTCNWMSGENCODE_C,
                  NAS_FILE_ID_NASTCOMMSGPROC_C,
                  NAS_FILE_ID_NASTCPDCPMSGPROC_C,
                  NAS_FILE_ID_NASTCRABMMSGPROC_C,
                  NAS_FILE_ID_NASESMSMMSGPROC_C,
                  NAS_FILE_ID_NASERABMCDSMSGPROC_C,
                  NAS_FILE_ID_NASEMMSMSMSGPROC_C,
                  NAS_FILE_ID_NASEMMLPPMSGPROC_C,
                  NAS_FILE_ID_IMSAMAIN_C,
/*  101   */      NAS_FILE_ID_IMSACALLMANAGEMENT_C,
                  NAS_FILE_ID_IMSACONNMANAGEMENT_C,
                  NAS_FILE_ID_IMSAIMSADAPTION_C,
                  NAS_FILE_ID_IMSAPROCAPSMSG_C,
                  NAS_FILE_ID_IMSAPROCCCAMSG_C,
                  NAS_FILE_ID_IMSAPROCCDSMSG_C,
                  NAS_FILE_ID_IMSAPROCIMSCALLMSG_C,
                  NAS_FILE_ID_IMSAPROCIMSREGMSG_C,
                  NAS_FILE_ID_IMSAPROCIMSSMSMSG_C,
                  NAS_FILE_ID_IMSAPROCMMAMSG_C,
/*  111   */      NAS_FILE_ID_IMSAPROCSMSMSG_C,
                  NAS_FILE_ID_IMSAPROCSPMMSG_C,
                  NAS_FILE_ID_IMSAPROCTIMERMSG_C,
                  NAS_FILE_ID_IMSAPUBLIC_C,
                  NAS_FILE_ID_IMSAREGMANAGEMENT_C,
                  NAS_FILE_ID_IMSASERVICEMANAGEMENT_C,
                  NAS_FILE_ID_IMSAPROCATMSG_C,
                  NAS_FILE_ID_IMSAPROCIMSUSSDMSG_C,
                  NAS_FILE_ID_IMSAPROCUSSDMSG_C,
                  NAS_FILE_ID_IMSAPROCRNICMSG_C,

                  NAS_FILE_ID_NASESMBACKOFFALGMAIN_C,

                  NAS_FILE_ID_NASESMEHSMMSGPROC_C,
                  NAS_FILE_ID_NASEMMSSMSGPROC_C,
                  NAS_FILE_ID_NASLPPDECODE_C,
                  NAS_FILE_ID_NASLPPEMMMSGPROC_C,
                  NAS_FILE_ID_NASLPPENCODE_C,
                  NAS_FILE_ID_NASLPPENCODEDECODEPUBLIC_C,
                  NAS_FILE_ID_NASLPPINTRAMSGPROC_C,
                  NAS_FILE_ID_NASLPPLRRCMSGPROC_C,
                  NAS_FILE_ID_NASLPPMAIN_C,
                  NAS_FILE_ID_NASLPPMTAMSGPROC_C,
                  NAS_FILE_ID_NASLPPPUBLIC_C,
                  NAS_FILE_ID_NASLPPSENDMSG_C,
                  NAS_FILE_ID_NASLPPFSM_C,
                  NAS_FILE_ID_NASLPPOM_C,
                  NAS_FILE_ID_NASLPPETCMSGPROC_C,

                  NAS_FILE_ID_NASTCMTCMSGPROC_C,
                  NAS_FILE_ID_NASLPPLCSMSGPROC_C,
                  NAS_FILE_ID_NASLPPTIMERMSGPROC_C,
                  NAS_FILE_ID_NASLPPUPPUBLIC_C,
                  NAS_FILE_ID_NASLPPUPMSGPROC_C
}NAS_FILE_ID_DEFINE_ENUM;
typedef unsigned long  NAS_FILE_ID_DEFINE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LMM_SndDebugInfoInd(VOS_UINT32 ulFileName, VOS_UINT32 ulLineNo, VOS_UINT16 ucPara1, VOS_UINT16 ucPara2, VOS_UINT16 ucPara3, VOS_UINT16 ucPara4);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of NasFileId.h */




