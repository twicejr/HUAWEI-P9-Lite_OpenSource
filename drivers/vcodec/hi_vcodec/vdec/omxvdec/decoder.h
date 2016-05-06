

#ifndef __DECODER_H__
#define __DECODER_H__


#include "channel.h"


#define LAST_FRAME_BUF_ID           (0xFFFFFFEE)
#define LAST_FRAME_BUF_SIZE         (20)

typedef enum
{
    DEC_CMD_CLEAR_STREAM,
    DEC_CMD_ALLOC_MEM,
    DEC_CMD_BIND_MEM,
    DEC_CMD_ACTIVATE_INST,
    DEC_CMD_SYNC_EXT_BUF,
}DECODER_CMD_E;

HI_S32 decoder_init(HI_VOID);

HI_S32 decoder_exit(HI_VOID);

HI_S32 decoder_suspend(HI_VOID);

HI_S32 decoder_resume(HI_VOID);

HI_S32 decoder_create_inst(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_CHAN_CFG *pchan_cfg);

HI_S32 decoder_release_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_start_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_stop_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_reset_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_ctrl_inst(OMXVDEC_CHAN_CTX *pchan, DECODER_CMD_E eCmd, HI_VOID *pParam);

HI_VOID decoder_proc_entry(OMXVDEC_CHAN_CTX *pchan, struct seq_file *p);


#endif

