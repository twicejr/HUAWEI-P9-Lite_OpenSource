

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : v00R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---Base模块实现
  Function List:
  History      :
************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_USIMM_APP_BASE_C
/*lint +e767*/

extern VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
extern VOS_VOID   SI_PB_PidMsgProc(struct MsgCB *pstPBMsg);
extern VOS_VOID   PCSC_AcpuMsgProc(MsgBlock *pMsg);
extern VOS_VOID   SI_PIH_AcpuInit(VOS_VOID);

/*****************************************************************************
 Prototype       : OM_AcpuFidInit
 Description     : ACPU OM FID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 USIMM_APP_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PB,
                                        (Init_Fun_Type)WuepsPBPidInit,
                                        (Msg_Fun_Type)SI_PB_PidMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PCSC,
                                        VOS_NULL_PTR,
                                        (Msg_Fun_Type)PCSC_AcpuMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_USIMM, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            SI_PIH_AcpuInit();

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

