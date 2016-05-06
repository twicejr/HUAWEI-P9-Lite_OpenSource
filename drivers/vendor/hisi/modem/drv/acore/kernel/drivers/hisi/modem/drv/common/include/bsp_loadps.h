#ifndef __BSP_OVERLAY_H__
#define __BSP_OVERLAY_H__


typedef struct _loadps_msg
{
    u32 addr;
    u32 size;
    u32 rat_mode;
} loadps_msg;

typedef struct _loadps_status
{
    s32 result;
} loadps_status;

/*镜像的头格式*/
struct loadps_header
{
   unsigned long magic;
   unsigned long image_size;
   unsigned long text_start;
   unsigned long text_size;
   unsigned long data_start;
   unsigned long data_size;
   unsigned long bss_start;
   unsigned long bss_size;
   unsigned long unwind_start;
   unsigned long unwind_size;
   unsigned long symbol_start;
   unsigned long symbol_size;
};

#if 1
#define BSP_LOADPS_LOG_LEVEL  BSP_LOG_LEVEL_INFO

#else
#define BSP_LOADPS_LOG_LEVEL  BSP_LOG_LEVEL_ERROR
#endif
#define LOADPS_ICC_IFC_ID    (ICC_CHN_IFC << 16 | IFC_RECV_FUNC_LOADPS)
#endif
