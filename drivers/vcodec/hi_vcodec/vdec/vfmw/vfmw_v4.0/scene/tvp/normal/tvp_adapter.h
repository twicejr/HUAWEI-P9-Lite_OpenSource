
#ifndef __TVP_ADAPTER_H__
#define __TVP_ADAPTER_H__


#define MAX_RAW_NUM           (1024)
#define MAX_EVENT_NUM         (512)
#define MAX_PARA_SIZE         (64)

#define MAX_PROC_SIZE         (100*1024)

typedef struct 
{   
    HI_U32               sec_print_word;
    UADDR                event_report_list;
    UADDR                stream_data_list;
    UADDR                ext_buffer_array;
    VFMW_DTS_CONFIG_S    dts_data;
} SHARE_DATA_S;

typedef struct
{
    HI_S32               Head_NS;
    HI_S32               Head_S;
    HI_S32               Tail_S;
    HI_S32               Tail_NS;
    STREAM_DATA_S        RawPacket[MAX_RAW_NUM];
} SHARE_RAW_ARRAY_S;

typedef struct
{
    HI_S32               IsValid;
    HI_S32               ChanID;
    HI_S32               Type;
    HI_U8                para[MAX_PARA_SIZE];
} SHARE_MSG_NODE_S;

typedef struct
{
    HI_S32               Head;
    HI_S32               Tail;
    SHARE_MSG_NODE_S     Message[MAX_EVENT_NUM];
} SHARE_EVENT_ARRAY_S;

typedef struct
{
    UINT32           TotalNum;
    EXTBUF_STATE_E   State[MAX_FRAME_NUM];
    UADDR            PhyAddr[MAX_FRAME_NUM];
} SHARE_EXTBUF_ARRAY_S;


#ifdef ENV_ARMLINUX_KERNEL

// Interface for Normal VFMW
HI_VOID TVP_VDEC_OpenModule(HI_VOID);
HI_VOID TVP_VDEC_ExitModule(HI_VOID);
HI_S32  TVP_VDEC_Init(VDEC_OPERATION_S *pArgs);
HI_S32  TVP_VDEC_Exit(HI_U8 IsSecure);
HI_S32  TVP_VDEC_Control(HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs, HI_U32 ArgLen);
HI_S32  TVP_VDEC_Suspend(HI_VOID);
HI_S32  TVP_VDEC_Resume(HI_VOID);

#endif

#endif //end of __TVP_ADAPTER_H__

