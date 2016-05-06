/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  efuse_balong.c
*
*   作    者 :  liuwenhui
*
*   描    述 :  Efuse读取
*
*   修改记录 :  2011年6月9日  v1.00  wuzechun创建，后来移植到V7R2
*
*************************************************************************/
/*lint --e{522,534} */
#include <string.h>

#include "product_config.h"
#include "securec.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_wait.h"

#include "bsp_memmap.h"
#include "efuse_balong.h"
#include "hi_efuse.h"
#include "bsp_om.h"
#include "bsp_icc.h"


#ifdef CONFIG_EFUSE
static int is_efuse_init = 0;
static osl_sem_id efuse_sem_id;
static osl_sem_id efuse_queue_sem_id;
static u32 efuse_buf[EFUSE_MAX_ALLOW_SIZE] = {0};
static int efuse_ret = 0;

static int bsp_efuse_data_receive(unsigned int channel_id , unsigned int len, void* context)
{
    int length = 0;
    u32 *buf = efuse_buf;
    EFUSE_DATA_STRU msg ;

	length = bsp_icc_read(channel_id, (u8*)&msg, sizeof(EFUSE_DATA_STRU));
	if(length != (int)sizeof(EFUSE_DATA_STRU))
	{
		efuse_print_error("read len(%x) != expected len(%x).\n", length, sizeof(EFUSE_DATA_STRU));
        efuse_ret = -1;
        osl_sem_up(&efuse_sem_id);
		return EFUSE_ERROR;
	}

    (void)memcpy_s(buf, EFUSE_MAX_ALLOW_SIZE*EFUSE_GROUP_SIZE, msg.buf, EFUSE_MAX_ALLOW_SIZE*EFUSE_GROUP_SIZE);
    efuse_ret = msg.ret;
    osl_sem_up(&efuse_sem_id);

    return EFUSE_OK;
}

int efuse_init(void)
{
    int ret;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;

    if(1 == is_efuse_init)
    {
        return EFUSE_OK;
    }

    osl_sem_init(0, &efuse_sem_id);
    osl_sem_init(1, &efuse_queue_sem_id);

    ret = bsp_icc_event_register(chan_id, (read_cb_func)bsp_efuse_data_receive, NULL, NULL, NULL);/* [false alarm]:屏蔽Fortify错误 */
    if(ICC_OK != ret)
    {
        efuse_print_error("register is error.\n");
        return EFUSE_ERROR;
    }

    is_efuse_init = 1;/* [false alarm]:屏蔽Fortify错误 */

    efuse_print_info("efuse init ok.\n");

    return EFUSE_OK;
}


/*****************************************************************************
* 函 数 名  : bsp_efuse_read
*
* 功能描述  : 按组读取EFUSE中的数据
*
* 输入参数  : group  起始group
*             num    读取长度(word数,不超过512/4=128)
* 输出参数  : pBuf   EFUSE中的数据
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    int length = 0;
    u32 *buf = efuse_buf;

    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;
    EFUSE_DATA_STRU msg;

    if((0 == num) || (group + num > EFUSE_MAX_SIZE) || (NULL == pBuf) || (num > EFUSE_MAX_ALLOW_SIZE))
    {
        efuse_print_error(" parameter error, group=%d, num=%d, pBuf=0x%x.\n", group, num, pBuf);
        return EFUSE_ERROR;
    }

    msg.start = group;
    msg.len = num;
    msg.opt = (u32)EFUSE_READ;

    osl_sem_down(&efuse_queue_sem_id);

    length = bsp_icc_send(ICC_CPU_APP, chan_id, (unsigned char*)&msg, sizeof(EFUSE_DATA_STRU));
    if(length != (int)sizeof(EFUSE_DATA_STRU))
    {
        osl_sem_up(&efuse_queue_sem_id);
        efuse_print_error("send len(%x) != expected len(%x).\n", length, sizeof(EFUSE_DATA_STRU));
        return EFUSE_ERROR;
    }
    /* coverity[lock] */
    osl_sem_down(&efuse_sem_id);

    if(0 != efuse_ret)
    {
        osl_sem_up(&efuse_queue_sem_id);
        efuse_print_error("efuse icc write is fail, err= %d.\n", efuse_ret);
        /* coverity[missing_unlock] */
        return EFUSE_ERROR;
    }
    else
    {
        (void)memcpy_s(pBuf, EFUSE_GROUP_SIZE * num, buf, EFUSE_GROUP_SIZE * num);
    }

    osl_sem_up(&efuse_queue_sem_id);

    /* coverity[missing_unlock] */
    return EFUSE_OK;

}

/*****************************************************************************
* 函 数 名  : bsp_efuse_Write
*
* 功能描述  : 烧写Efsue
*
* 输入参数  : pBuf:待烧写的EFUSE值
*                 group,Efuse地址偏移
*                 len,烧写长度
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len)
{
    int length = 0;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;
    EFUSE_DATA_STRU msg ;

    if((0 == len) || (group + len > EFUSE_MAX_SIZE) || (NULL == pBuf))
    {
        efuse_print_error(" parameter error, group=%d, len=%d, pBuf=0x%x.\n", group, len, pBuf);
        return EFUSE_ERROR;
    }

    (void)memcpy_s(msg.buf, EFUSE_GROUP_SIZE * len, pBuf, EFUSE_GROUP_SIZE * len);
    msg.start = group;
    msg.len = len;
    msg.opt = (u32)EFUSE_WRITE;

    osl_sem_down(&efuse_queue_sem_id);
    length = bsp_icc_send(ICC_CPU_APP, chan_id, (unsigned char*)&msg, sizeof(EFUSE_DATA_STRU));
    if(length != (int)sizeof(EFUSE_DATA_STRU))
    {
        osl_sem_up(&efuse_queue_sem_id);
        efuse_print_error("send len(%x) != expected len(%x).\n", length, sizeof(EFUSE_DATA_STRU));
        return EFUSE_ERROR;
    }

    /* coverity[lock] */
    osl_sem_down(&efuse_sem_id);

    if(0 != efuse_ret)
    {
        osl_sem_up(&efuse_queue_sem_id);
        efuse_print_error("efuse icc write is fail, err= %d.\n", efuse_ret);
        /* coverity[missing_unlock] */
        return EFUSE_ERROR;
    }

    osl_sem_up(&efuse_queue_sem_id);
    /* coverity[missing_unlock] */
    return EFUSE_OK;
}


void bsp_efuse_show(void)
{
    u32 i = 0;
    u32 value = 0;

    for(i = 0;i < EFUSE_MAX_SIZE;i++)
    {
        if(OK == bsp_efuse_read(&value, i, 1))
        {
            efuse_print_error("efuse group%d value = 0x%x.\n ", i, value);
        }
        else
        {
            efuse_print_error("efuse group%d read fail.\n", i);
            return;
        }

    }

}


#endif

