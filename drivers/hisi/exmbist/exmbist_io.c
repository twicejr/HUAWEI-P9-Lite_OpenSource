

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "exmbist_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -e818*/
exmbist_uint32 exm_io_wr_cmd (ExmCtx * ctx, exmbist_uint32 cmd) {
    exmbist_uint32 uiret = EXMBIST_OK;

    if(ctx->exm_io_wr_cmd_p)
    {
     (void)(*(ctx->exm_io_wr_cmd_p))(cmd);
    }

    //EXMBIST_info("exm_io_wr_cmd, din : 0x%x \n",cmd);
    return uiret;
}

exmbist_uint32 exm_io_wr_din (ExmCtx * ctx, exmbist_uint32 din) {
    exmbist_uint32 uiret = EXMBIST_OK;

    if(ctx->exm_io_wr_din_p)
    {
    (void)(*(ctx->exm_io_wr_din_p))(din);
    }

    //EXMBIST_info("exm_io_wr_din, din : 0x%x. \n",din);
    return uiret;
}

exmbist_uint32 exm_io_rd_dout (ExmCtx * ctx) {
    exmbist_uint32  dout = 0x0;

    if(ctx->exm_io_rd_dout_p)
    {
    dout = (*(ctx->exm_io_rd_dout_p))();
    }

    //EXMBIST_info("exm_io_rd_dout, dout : 0x%x.\n",dout);
    return dout;
}

exmbist_uint32 exm_io_rd_status (ExmCtx * ctx) {
    exmbist_uint32 status = 0x0;

    if(ctx->exm_io_rd_status_p)
    {
    status = (*(ctx->exm_io_rd_status_p))();
    }

    return status;
}
/*lint +e818*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
