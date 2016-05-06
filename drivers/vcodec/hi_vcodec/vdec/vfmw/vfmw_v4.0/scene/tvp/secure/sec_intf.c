
#include "sec_intf.h"
#include "sec_share.h"
#include "public.h"
#include "tvp_adapter.h"


/************************************************************************
    Secure VFMW Init
*************************************************************************/
SINT32 SEC_VDEC_Init(UINT32 Args, UINT32 Share)
{
    SINT32 ret = VDEC_ERR;
    VDEC_OPERATION_S *pParam = NULL;

    ret = SEC_ShareZone_Init(Share);
    if (ret != VDEC_OK)
    {
        dprint(PRN_FATAL, "%s %d, SEC_ShareZone_Init failed!\n", __func__,__LINE__);
        return VDEC_ERR;
    }
    
    pParam = (VDEC_OPERATION_S *)SOS_MapShare(Args, sizeof(VDEC_OPERATION_S), 1, 1);
    if (pParam != NULL)
    {
        pParam->ext_intf.event_handler  = SEC_EventReport;
        pParam->ext_intf.buffer_handler = SEC_Buffer_Handler;
        ret = VDEC_Init(pParam);  
        SOS_UnMapShare((VOID *)pParam, sizeof(VDEC_OPERATION_S));
    }
    else
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed!\n", __func__,__LINE__);
        ret = VDEC_ERR;
    }
      
    return ret;
}

/************************************************************************
    Secure VFMW Exit
*************************************************************************/
SINT32 SEC_VDEC_Exit(UINT32 IsSecure)
{
    SINT32 ret = VDEC_ERR;
    
    ret = VDEC_Exit(IsSecure);

    SEC_ShareZone_Exit();

    return ret;
}

/************************************************************************
    Secure VFMW Suspend
*************************************************************************/
SINT32 SEC_VDEC_Suspend(VOID)
{
    return VDEC_Suspend();
}

/************************************************************************
    Secure VFMW Resume
*************************************************************************/
SINT32 SEC_VDEC_Resume(VOID)
{
    return VDEC_Resume();
}

/************************************************************************
    Secure VFMW Control
*************************************************************************/
SINT32 SEC_VDEC_Control(SINT32 ChanID, UINT32 eCmdID, UINT32 Args, UINT32 ArgLen)
{
    SINT32 ret = VDEC_ERR;
    UINT8  MapFlag = 0;
    VOID  *pParam  = NULL;
    
    if (Args != 0 && ArgLen != 0)
    {
        pParam = (VOID *)SOS_MapShare(Args, ArgLen, 1, 1);
        if (NULL == pParam)
        {
            dprint(PRN_FATAL, "%s SOS_MapShare failed!\n", __func__);
            return VDEC_ERR;
        }
        MapFlag = 1;
    }

    ret = SEC_ControlAdjust(ChanID, eCmdID, pParam);
    if (ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "%s SEC_ControlFilter failed!\n", __func__);
        goto EXIT;
    }
    
    ret = VDEC_Control(ChanID, eCmdID, pParam, ArgLen);

    SEC_ControlConverse(ChanID, eCmdID, pParam);

EXIT:
    if (1 == MapFlag)
    {
        SOS_UnMapShare((VOID *)pParam, ArgLen);
    }
    
    return ret;
}

/************************************************************************
    Secure VFMW Run Process
*************************************************************************/
SINT32 SEC_VDEC_RunProcess(UINT32 Args, UINT32 ArgLen)
{    
    return VCTRL_RunProcess();
}

/************************************************************************
    Secure VFMW Get Chan Image
*************************************************************************/
SINT32 SEC_VDEC_GetChanImage(SINT32 ChanID, UINT32 Image)
{
    SINT32 ret = VDEC_ERR;
    IMAGE *pImage = NULL;
    
    pImage = (IMAGE *)SOS_MapShare(Image, sizeof(IMAGE), 1, 1);
    if (pImage != NULL)
    {
        ret = VCTRL_GetChanImage(ChanID, pImage);
        SOS_UnMapShare((VOID *)pImage, sizeof(IMAGE));
    }
    else
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
        ret = VDEC_ERR;
    }

    return ret;
}

/************************************************************************
    Secure VFMW Release Chan Image
*************************************************************************/
SINT32 SEC_VDEC_ReleaseChanImage(SINT32 ChanID, UINT32 Image)
{
    SINT32 ret = VDEC_ERR;
    IMAGE *pImage = NULL;
    
    pImage = (IMAGE *)SOS_MapShare(Image, sizeof(IMAGE), 1, 1);
    if (pImage != NULL)
    {
        ret = VCTRL_ReleaseChanImage(ChanID, pImage);
        SOS_UnMapShare((VOID *)pImage, sizeof(IMAGE));
    }
    else
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
        ret = VDEC_ERR;
    }
    
    return ret;
}

/************************************************************************
    Secure VFMW Read Proc
*************************************************************************/
SINT32 SEC_VDEC_ReadProc(UINT32 Page, SINT32 Count)
{
    SINT32 ret = VDEC_ERR;
    SINT8 *pParam = NULL;
    
    pParam = SOS_MapShare(Page, MAX_PROC_SIZE, 1, 1);
    if (pParam != NULL)
    {
        ret = SEC_ReadProc(pParam, Count);
        SOS_UnMapShare((VOID *)pParam, MAX_PROC_SIZE);
    }
    else
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
        ret = VDEC_ERR;
    }
    
    return ret;
}

/************************************************************************
    Secure VFMW Wrtie Proc
*************************************************************************/
SINT32 SEC_VDEC_WriteProc(UINT32 Option, SINT32 Value)
{
    return SEC_WriteProc(Option, Value);
}

