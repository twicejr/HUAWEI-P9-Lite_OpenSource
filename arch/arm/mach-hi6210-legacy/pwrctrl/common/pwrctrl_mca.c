#include <mach/pwrctrl/pwrctrl_mca_prot.h>
//#include <mailbox/drv_mailbox_interface.h>
#include <multicore/ipcm/bsp_drv_ipc.h>
#include <pwrctrl_multi_memcfg.h>
#include <linux/slab.h>
#include "bsp_mailbox.h"
#include "drv_ifc.h"

#ifdef GENERIC_PROJECT
#define MCA_INST_IPC_ID                 1   //fIXME:定义在typedef enum tagIPC_INT_LEV_E中
#endif

#define MCA_DEBUG printk
#if 0
/*stub *************************************/

#define MAILBOX_OK   (0)
#define BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MCA_CH 3
#define BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH 1

/*****************************************************************************
 函 数 名  : mailbox_send_msg
 功能描述  : 邮箱用户发送邮件数据
 输入参数  : MailCode   -- 邮编, 指定邮件发送目标
             pData      -- 指向邮件数据的指针
             Length     -- 待发送数据长度, 单位byte
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long mailbox_send_msg(
                unsigned long           MailCode,
                void                   *pData,
                unsigned long           Lengt)
{ return MAILBOX_OK; }

/*****************************************************************************
 函 数 名  : mailbox_reg_msg_cb
 功能描述  : 注册邮件数据接收函数
 输入参数  : MailCode   -- 数据接收函数处理的对象邮编
             pFun       -- 邮件数据接收处理函数指针
             UserHandle -- 用户定义句柄, 数据接收函数被调用时会作为入参, 无则填空
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月29日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long mailbox_reg_msg_cb(
                unsigned long           MailCode,
                void *  pFun,
                void                   *UserHandle)
{ return MAILBOX_OK; }

/*****************************************************************************
 函 数 名  : mailbox_read_msg_data
 功能描述  : 邮箱用户在数据接收回调函数中调用, 从邮箱中读取一封最先到达的邮件
 输入参数  : MailHandle -- 邮箱句柄, 数据接收回调函数入参
             pData      -- 保存待读出数据的缓存地址
             *pSize     -- 缓存长度, 单位byte, 需要大于待读取邮件长度
 输出参数  : *pSize     -- 实际读取长度, 单位byte
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long mailbox_read_msg_data(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned long          *pSize)
{ return MAILBOX_OK; }

/*stub end*/


struct mca_sblock* slist[MCA_MAX_SESSION_NUM];

MCA_LOCAL int mca_create_session()
{
    int idx;

    for(idx=0; idx<MCA_MAX_SESSION_NUM; idx++)
    {
        if(!slist[idx])
        {
            slist[idx] = (struct mca_sblock*)mca_malloc(sizeof(struct mca_sblock));

            mca_sem_init(&slist[idx]->sem, 0);

            return idx;
        }
    }

    return -1;
}

MCA_LOCAL int mca_remove_session(int sid)
{
    if(!mca_valid_sid(sid))
        return -1;

    if(!slist[sid])
        return -1;

    mca_sem_up(&slist[sid]->sem);

    mca_sem_del(&slist[sid]->sem);

    mca_free(slist[sid]);

    slist[sid] = NULL;

    return 0;
}

MCA_LOCAL int mca_save_session(int sid, struct mca_sdata sdata)
{
    if(!mca_valid_sid(sid))
        return -1;

    if(!slist[sid])
        return -1;

    slist[sid]->sdata = sdata;

    return 0;
}

MCA_LOCAL int mca_read_session(int sid, struct mca_sdata* sbuf)
{
    if(!mca_valid_sid(sid))
        return -1;

    if(!slist[sid])
        return -1;

    if(!sbuf)
        return -1;

    *sbuf = slist[sid]->sdata;

    return 0;
}

MCA_LOCAL int mca_lock_session(int sid, int time_out)
{
    if(!mca_valid_sid(sid))
        return -1;

    if(!slist[sid])
        return -1;

    if(!time_out)
        mca_sem_down(&slist[sid]->sem);
    else
        if(mca_sem_down_timeout(&slist[sid]->sem, time_out))
            return -1;

    return 0;
}

MCA_LOCAL int mca_unlock_session(int sid)
{
    if(!mca_valid_sid(sid))
        return -1;

    if(!slist[sid])
        return -1;

    mca_sem_up(&slist[sid]->sem);

    return 0;
}

MCA_LOCAL int mca_is_session_locked(int sid)
{
    return mca_sem_count(&slist[sid]->sem) == 0;
}

int mca_send_no_use(int cmd_id, union mca_udata_req req_data, union mca_udata_rsp* p_rsp_data, int time_out)
{
    int sid;
    struct mca_sdata sdata = {0};
    struct mca_frame frame = {0};

    // If user need response data, p_rsp_data != NULL
    if(p_rsp_data)
    {
        sid = mca_create_session();
        if(sid < 0)
            return -1;

        sdata.p_rsp = p_rsp_data;

        if(mca_save_session(sid, sdata))
            goto ERR_DESTROY_EXIT;

        memset(&frame, 0, sizeof(struct mca_frame));
        frame.sid    = sid;
        frame.stype  = MCA_SESSION_SYNC;
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;
        if(MAILBOX_OK != mailbox_send_msg(
                BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
                &frame,
                sizeof(struct mca_frame)))
            goto ERR_DESTROY_EXIT;

        // wait for response.
        if(mca_lock_session(sid, time_out) != 0)
        {
            // may response hare after time_out.
            mca_lock_irq();

            // check if responsed after time_out.
            if(mca_is_session_locked(sid))
                mca_unlock_session(sid); /* session shoud be kept untill rsp. */
            else
                mca_remove_session(sid); /* destroy if responsed. */

            mca_unlock_irq();

            return -1;
        }

        // if all ok.
        mca_remove_session(sid);
    }
    else /* If p_rsp_data == NULL, we'll think user needn't response.  */
    {
        memset(&frame, 0, sizeof(struct mca_frame));
        frame.stype  = MCA_SESSION_NRSP;
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;
        if(MAILBOX_OK != mailbox_send_msg(
                BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
                &frame,
                sizeof(struct mca_frame)))
            return -1;
    }

    return 0;

ERR_DESTROY_EXIT:

    mca_remove_session(sid);

    return -1;
}

int mca_post(int cmd_id, union mca_udata_req req_data, mca_post_cb post_cb, void* private_data, int time_out)
{
    int sid;
    struct mca_sdata sdata = {0};
    struct mca_frame frame = {0};

    if(post_cb)
    {
        sid = mca_create_session();
        if(sid < 0)
            return -1;

        sdata.post_cb      = post_cb;
        sdata.private_data = private_data;

        if(mca_save_session(sid, sdata))
            goto ERR_DESTROY_EXIT;

        memset(&frame, 0, sizeof(struct mca_frame));
        frame.sid    = sid;
        frame.stype  = MCA_SESSION_ASYN;
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;
        if(MAILBOX_OK != mailbox_send_msg(
                BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
                &frame,
                sizeof(struct mca_frame)))
            goto ERR_DESTROY_EXIT;
    }
    else
    {
        memset(&frame, 0, sizeof(struct mca_frame));
        frame.stype  = MCA_SESSION_NRSP;
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;
        if(MAILBOX_OK != mailbox_send_msg(
                BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
                &frame,
                sizeof(struct mca_frame)))
            return -1;
    }

    //FIXME: time_out not use. session may never destroy.
    return 0;

ERR_DESTROY_EXIT:

    mca_remove_session(sid);

    return -1;
}

int mca_inst(int cmd_id, union mca_udata_req req_data)
{
#if 0
    struct mca_frame frame = {0};

    if(*(int*)MCA_INST_DATA_MUTEX_ADDR)
        return -1;

    // FIXME: DANGEROUS! USE RES LOCK!
    *(int*)MCA_INST_DATA_MUTEX_ADDR = 1;

    memset(&frame, 0, sizeof(struct mca_frame));
    frame.stype  = MCA_SESSION_NRSP;
    frame.cmd_id = cmd_id;
    frame.udata  = req_data;

    memcpy(MCA_INST_DATA_ADDR, &frame, sizeof(struct mca_frame));

    BSP_IPC_IntSend(IPC_TARGET_CPU_MCU, MCA_INST_IPC_ID);
#endif
    return 0;
}

MCA_LOCAL void mca_rsp_isr(void *UserHandle, void *MailHandle, unsigned long MailLen)
{
#if 0
    struct mca_frame frame = {0};
    struct mca_sdata sdata = {0};
    unsigned long frame_size;

    if(mailbox_read_msg_data(MailHandle, (unsigned char*)&frame, &frame_size) != MAILBOX_OK)
        return;

    if(frame.cmd_id != MCA_CMD_RSP)
        return;

    if(mca_read_session(frame.sid, &sdata))
        return;

    if(frame.stype == MCA_SESSION_SYNC)
    {
        // check if session expired.
        if(mca_is_session_locked(frame.sid))
        {
            *sdata.p_rsp = frame.udata;
            mca_unlock_session(frame.sid);
        }
        else
            mca_remove_session(frame.sid);
    }
    else if(frame.stype == MCA_SESSION_ASYN)
    {
        if(sdata.post_cb)
            sdata.post_cb(frame.udata, sdata.private_data);

        mca_remove_session(frame.sid);
    }
#endif
}

void mca_init()
{
    mailbox_reg_msg_cb(BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MCA_CH, mca_rsp_isr, 0);
}
#endif

IFC_GEN_CALL4(MAILBOX_IFC_ACPU_TO_MCU_MCA, mcu_mca_cmd_handler,
                IFC_INVAR, void *, buf, 0,
                IFC_INCNT, int, buf_len, 0,
                IFC_OUTVAR, void *, rsp, 0,
                IFC_INCNT, int , rsp_len , 0)

int mca_send(int cmd_id, union mca_udata_req req_data, union mca_udata_rsp* p_rsp_data, int time_out)
{
    struct mca_frame frame = {0};
    union mca_udata_rsp rsp;
    unsigned long outputlen;
    unsigned char outbuf[512] = {0};
    int ret;
    
    // If user need response data, p_rsp_data != NULL
    if(p_rsp_data)
    {
        memset(&frame, 0, sizeof(struct mca_frame));
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;

        outputlen = sizeof(union mca_udata_rsp);
        MCA_DEBUG("mca send cmd:%d\n", cmd_id);
#if 0 //monan for new ifc
        if(BSP_OK != MB_IFC_ExtendCall( IFCP_FUNC_MCU_MCA, BSP_MAILBOX_IFC_CALL_SYNC, (void *)0,(unsigned char*)(&frame),
                sizeof(struct mca_frame), (unsigned char*)(&outbuf[0]), &outputlen))
        {
            MCA_DEBUG("mca send cmd:%d failed!!!\n",cmd_id);
            goto ERR_DESTROY_EXIT;
        }
#endif
        if(BSP_OK != (ret = mcu_mca_cmd_handler((unsigned char*)(&frame), sizeof(struct mca_frame), (unsigned char*)(&outbuf[0]), outputlen, time_out)))
        {
            MCA_DEBUG("mca send cmd:%d ret:0x%x failed!!!\n",cmd_id, ret);
            goto ERR_DESTROY_EXIT;
        }

        if(sizeof(union mca_udata_rsp) != outputlen)
        {
            MCA_DEBUG("output len(%d) is error, mca send cmd:%d failed!!!\n",outputlen, cmd_id);
            goto ERR_DESTROY_EXIT;
        }
        else
        {
            memcpy(p_rsp_data, outbuf, outputlen);
        }
    }
    else /* If p_rsp_data == NULL, we'll think user needn't response.  */
    {
        memset(&frame, 0, sizeof(struct mca_frame));
        frame.cmd_id = cmd_id;
        frame.udata  = req_data;

        goto ERR_DESTROY_EXIT;
 #if 0   //monan for new ifc
        if(BSP_OK != MB_IFC_ExtendCall( IFCP_FUNC_MCU_MCA, BSP_MAILBOX_IFC_CALL_SYNC, (void *)0,(unsigned char*)(&frame),
                sizeof(struct mca_frame), (unsigned char*)(&outbuf[0]), &outputlen))
        {
            MCA_DEBUG("mca send cmd:%d failed!!!\n",cmd_id);
            goto ERR_DESTROY_EXIT;
        }
#endif
        if(sizeof(union mca_udata_rsp) != outputlen)
        {
            MCA_DEBUG("output len(%d) is error, mca send cmd:%d failed!!!\n",outputlen, cmd_id);
            goto ERR_DESTROY_EXIT;
        }
    }

    rsp = *(union mca_udata_rsp *)outbuf;
    if(-1 == rsp.dfs_default_rsp.ret)
    {
        goto ERR_DESTROY_EXIT;
    }

    return 0;

ERR_DESTROY_EXIT:

    return -1;
}

void test_mca_cmd(s32_t qos_id, u32_t req_value)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};
    s32_t buf[32] = {0};
    s32_t* req_id = &buf[0];

    if(!req_id)
        return RET_ERR_PARAM_NULL;

    req.dfs_rqqos_req.qos_id    = qos_id;
    req.dfs_rqqos_req.req_value = req_value;

    if(-1 == mca_send(MCA_CMD_DFS_RQQOS, req, &rsp, 100000))
    {
        printk("mca_send failed!!!\n");
        return;
    }
    *req_id = rsp.dfs_rqqos_rsp.req_id;

    printk("req_id:%d\n",*req_id);
}