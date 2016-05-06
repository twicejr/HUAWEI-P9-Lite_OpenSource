/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : rfile_balong.c
  版 本 号   : 初稿
  作    者   : c64416
  生成日期   : 2013年8月7日
  最近修改   :
  功能描述   : mcore远程文件系统处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月7日
    作    者   : c64416
    修改内容   : 创建文件

******************************************************************************/

#include "rfile_balong.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


osSemaphoreDef(rfile_req_sem);
osSemaphoreDef(rfile_all_sem);

#define bsp_trace(log_level, mod_id, fmt,...) printk(fmt, ##__VA_ARGS__)

extern void rfile_CommonCnf(struct bsp_rfile_common_cnf *pstCnf);


struct bsp_rfile_main_stru g_stRfileMain = {BSP_FALSE, };


/*************************************************************************
 函 数 名   : bsp_open
 功能描述   : bsp_open
 输入参数   : const s8 *path 
              s32 flags
              s32 mode

 返 回 值   : 失败返回-1，成功返回文件句柄

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_open(const s8 *path, s32 flags,  s32 mode)
{
    s32 ret;
    u32 ulNameLen, ulSize;
    struct bsp_rfile_open_req *pstReq;

    osSemaphoreWait(g_stRfileMain.semAll, osWaitForever);

    if(!path)
    {
        return BSP_ERROR;
    }

    ulNameLen = strlen(path) + 1;

    ulSize = sizeof(struct bsp_rfile_open_req) + ulNameLen;
    
    if(ulSize > RFILE_LEN_MAX)
    {
        return BSP_ERROR;
    }

    pstReq = Rfile_Malloc(ulSize);
    if(!pstReq)
    {
        return BSP_ERROR;
    }

    pstReq->opType = EN_RFILE_OP_OPEN;
    pstReq->pstlist = NULL;
    pstReq->nameLen = ulNameLen;
    pstReq->mode = mode;
    pstReq->flags = flags;

    memcpy(pstReq->aucData, path, ulNameLen);

    ret = bsp_icc_send(ICC_CPU_APP, RFILE_MCORE_ICC_WR_CHAN, pstReq, ulSize);
    if (ulSize != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);
        g_stRfileMain.ret = -1;
    }
    else
    {
        osSemaphoreWait(g_stRfileMain.semReq, osWaitForever);
    }

    Rfile_Free(pstReq);

    osSemaphoreRelease(g_stRfileMain.semAll);

    return g_stRfileMain.ret;
}

/*************************************************************************
 函 数 名   : bsp_close
 功能描述   : bsp_close
 输入参数   : fd
 输出参数   :
 返 回 值   : 成功返回0，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_close(u32 fd)
{
    s32 ret;
    struct bsp_rfile_close_req stReq;

    osSemaphoreWait(g_stRfileMain.semAll, osWaitForever);

    stReq.opType = EN_RFILE_OP_CLOSE;
    stReq.pstlist = NULL;
    stReq.fd = fd;

    ret = bsp_icc_send(ICC_CPU_APP, RFILE_MCORE_ICC_WR_CHAN, &stReq, sizeof(struct bsp_rfile_close_req));
    if (sizeof(struct bsp_rfile_close_req) != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);
        
        g_stRfileMain.ret = -1;
    }
    else
    {
        osSemaphoreWait(g_stRfileMain.semReq, osWaitForever);
    }

    osSemaphoreRelease(g_stRfileMain.semAll);

    return g_stRfileMain.ret;
}

/*************************************************************************
 函 数 名   : rfile_write
 功能描述   : 文件写处理(每次写入的数据不能超过ICC通道的长度限制)
 输入参数   : u32 fd
              void *ptr
              u32 size

 返 回 值   : 成功返回0，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
static s32 rfile_write(u32 fd ,void *ptr, u32 size)
{
    s32 ret;
    struct bsp_rfile_write_req *pstReq;
    u32 ulLen;

    ulLen = sizeof(struct bsp_rfile_write_req) + size;

    pstReq = Rfile_Malloc(ulLen);
    if(!pstReq)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);
        return BSP_ERROR;
    }

    pstReq->opType = EN_RFILE_OP_WRITE;
    pstReq->pstlist = NULL;
    pstReq->fd = fd;
    pstReq->ulSize = size;
    memcpy(pstReq->aucData, ptr, size);

    ret = bsp_icc_send(ICC_CPU_APP, RFILE_MCORE_ICC_WR_CHAN, pstReq, ulLen);
    if (ulLen != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);
        
        g_stRfileMain.ret = -1;
    }
    else
    {
        osSemaphoreWait(g_stRfileMain.semReq, osWaitForever);
    }

    Rfile_Free(pstReq);

    return g_stRfileMain.ret;
}


/*************************************************************************
 函 数 名   : bsp_write
 功能描述   : bsp_write
 输入参数   : u32 fd
              const s8 *ptr
              u32 size
 输出参数   :
 返 回 值   : 返回写入的数据长度

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_write(u32 fd, const s8 *ptr, u32 size)
{
    s32 ret = -1;
    u32 ulCur, ulLen;

    osSemaphoreWait(g_stRfileMain.semAll, osWaitForever);

    if(!ptr)
    {
        return BSP_ERROR;
    }

    /* 如果长度超过ICC最大长度限制，需要拆分传送 */
    ulCur = 0;
    while(ulCur < size)
    {
        ulLen = ((size - ulCur) > RFILE_WR_LEN_MAX) ? RFILE_WR_LEN_MAX : (size - ulCur);

        ret = rfile_write(fd, ((u8*)ptr+ulCur), ulLen);

        ulCur += ret;

        if(ret != ulLen)
        {
            break;
        }
    }

    osSemaphoreRelease(g_stRfileMain.semAll);

    return ulCur;
}


/*****************************************************************************
 函 数 名  : bsp_RfileCallback
 功能描述  : icc回调处理函数
 输入参数  : u32 channel_id
             u32 len
             void *context
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_RfileCallback(u32 channel_id, u32 len, void *context)
{
    void *pData;
    s32 ret;

    pData = Rfile_Malloc(len);
    if(!pData)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);
        return BSP_ERROR;
    }

    ret = bsp_icc_read(RFILE_MCORE_ICC_RD_CHAN, pData, len);

    if(len != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "icc_read failed %d.\n", ret);

        Rfile_Free(pData);

        return BSP_ERROR;
    }

    rfile_CommonCnf(pData);

    Rfile_Free(pData);

    osSemaphoreRelease(g_stRfileMain.semReq);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : bsp_rfile_init
 功能描述  : rfile模块初始化
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_rfile_init(void)
{
    s32 ret;

	g_stRfileMain.semAll = osSemaphoreCreate(osSemaphore(rfile_all_sem), 1);

	g_stRfileMain.semReq = osSemaphoreCreate(osSemaphore(rfile_req_sem), 0);

    ret = bsp_icc_event_register(RFILE_MCORE_ICC_RD_CHAN, bsp_RfileCallback, NULL, NULL, NULL);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_icc_event_register failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }

    g_stRfileMain.bInitFlag = BSP_TRUE;

//    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] success.\n", __FUNCTION__);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_CommonCnf
 功能描述  : 应答处理
 输入参数  : struct bsp_rfile_common_cnf *pstCnf
*****************************************************************************/
void rfile_CommonCnf(struct bsp_rfile_common_cnf *pstCnf)
{
    g_stRfileMain.ret = pstCnf->ret;

    return ;
}


s32 pfile;

void rfile_test_001(void)
{
    s32 ret;
    s8 *filepath = "/rfiletest001/rfile001.txt";
    
    pfile = bsp_open(filepath, (RFILE_CREAT|RFILE_RDWR), 0755);
    if(pfile < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);

        return ;
    }
}

void rfile_test_002(void)
{
    s32 ret;
    s8 *wrbuf = "cjqcjqcjq";

    ret = bsp_write(pfile, wrbuf, strlen(wrbuf));
    if(ret != strlen(wrbuf))
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);

        return ;
    }
}

void rfile_test_003(void)
{
    s32 ret;

    ret = bsp_close(pfile);
    if(BSP_OK != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "%d.\n", __LINE__);

        return ;
    }
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


