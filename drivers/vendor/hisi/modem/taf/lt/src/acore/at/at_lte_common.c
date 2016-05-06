

/******************************************************************************
 */
/* PROJECT   : MSP_CPV700R001C01
 */
/* SUBSYSTEM : AT
 */
/* MODULE    : LTE
 */
/* OWNER     :
 */
/******************************************************************************
 */
/*lint -save -e537 -e958 -e713 -e718 -e746 -e740 -e516 -e830 -e533*/
#include "osm.h"
#include "gen_msg.h"
#include "msp_at.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"

#include <linux/syscalls.h>
#include "mdrv_om.h"

/*lint -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_COMMON_C
/*lint +e767 */

/* 发送缓冲区
 */
AT_SEND_DATA_BUFFER_STRU gstLAtSendData = {{0},};
VOS_UINT8 *pgucLAtSndCodeAddr = &gstLAtSendData.aucBuffer[2];


AT_ERROR_CODE_TABLE_STRU g_stErrCodeTable[] = {
    {APP_SUCCESS,                               AT_OK},
    {APP_FAILURE,                               AT_ERROR},
    {APP_ERR_CAPABILITY_ERROR,                  AT_CME_OPERATION_NOT_SUPPORTED},
    {APP_ERR_USIM_SIM_CARD_NOTEXIST,            AT_CME_SIM_NOT_INSERTED},
    {APP_ERR_NEED_PIN1,                         AT_CME_SIM_PIN_REQUIRED},
    {APP_ERR_NEED_PUK1,                         AT_CME_SIM_PUK_REQUIRED},
    {APP_ERR_USIM_SIM_INVALIDATION,             AT_CME_SIM_FAILURE},
    {APP_ERR_ID_INVALID,                        AT_CME_INVALID_INDEX},
    {APP_ERR_TIME_OUT,                          AT_CME_NETWORK_TIMEOUT},
    {APP_ERR_PARA_ERROR,                        AT_CME_INCORRECT_PARAMETERS},
    {APP_ERR_NULL_PTR,                          AT_CME_INCORRECT_PARAMETERS},
    {APP_ERR_NUM_VALUE_INVALID,                 AT_CME_INCORRECT_PARAMETERS},
    {APP_ERR_NUM_LEN_INVALID,                   AT_CME_INCORRECT_PARAMETERS},

    /* 拨号错误
 */
    {APP_ERR_SM_APN_LEN_ILLEGAL,                AT_CME_APN_LEN_ILLEGAL},
    {APP_ERR_SM_APN_SYNTACTICAL_ERROR,          AT_CME_APN_SYNTACTICAL_ERROR},
    {APP_ERR_SM_SET_APN_BEFORE_SET_AUTH,        AT_CME_SET_APN_BEFORE_SET_AUTH},
    {APP_ERR_SM_AUTH_TYPE_ILLEGAL,              AT_CME_AUTH_TYPE_ILLEGAL},
    {APP_ERR_SM_USER_NAME_TOO_LONG,             AT_CME_USER_NAME_TOO_LONG},
    {APP_ERR_SM_USER_PASSWORD_TOO_LONG,         AT_CME_USER_PASSWORD_TOO_LONG},
    {APP_ERR_SM_ACCESS_NUM_TOO_LONG,            AT_CME_ACCESS_NUM_TOO_LONG},
    {APP_ERR_SM_CALL_CID_IN_OPERATION,          AT_CME_CALL_CID_IN_OPERATION},
    {APP_ERR_SM_BEARER_TYPE_NOT_DEFAULT,        AT_CME_BEARER_TYPE_NOT_DEFAULT},
    {APP_ERR_SM_CALL_CID_INVALID,               AT_CME_CALL_CID_INVALID},
    {APP_ERR_SM_CALL_CID_ACTIVE,                AT_CME_CALL_CID_ACTIVE},
    {APP_ERR_SM_BEARER_TYPE_ILLEGAL,            AT_CME_BEARER_TYPE_ILLEGAL},
    {APP_ERR_SM_MUST_EXIST_DEFAULT_TYPE_CID,    AT_CME_MUST_EXIST_DEFAULT_TYPE_CID},
    {APP_ERR_SM_PDN_TYPE_ILLEGAL,               AT_CME_PDN_TYPE_ILLEGAL},
    {APP_ERR_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL,   AT_CME_IPV4_ADDR_ALLOC_TYPE_ILLEGAL},
    {APP_ERR_SM_LINK_CID_INVALID,               AT_CME_LINK_CID_INVALID},

    /* NV ERROR CODE
 */
    {ERR_MSP_NV_NOT_SUPPORT_ID,         AT_DEVICE_NV_NOT_SUPPORT_ID},
    {ERR_MSP_NV_ERROR_READ,             AT_DEVICE_NV_READ_FAILURE},
    {ERR_MSP_NV_NOT_SUPPORT_LENTH,      AT_DEVICE_NV_WRITE_FAIL_OVERLEN},
    {ERR_MSP_NV_BAD_BLOCK,              AT_DEVICE_NV_WRITE_FAIL_BADFLASH},
    {ERR_MSP_NV_ERROR_WRITE,            AT_DEVICE_NV_WRITE_FAIL_UNKNOWN},
    /* 装备 ERROR CODE
 */
    {ERR_MSP_SUCCESS,                   AT_OK},
    {ERR_MSP_FAILURE,                   AT_ERROR},
    {ERR_MSP_NOT_EXIST,                 AT_DEVICE_NOT_SUPPORT},
    {ERR_MSP_UNKNOWN,                   AT_DEVICE_ERR_UNKNOWN},
    {ERR_MSP_INVALID_PARAMETER,         AT_DEVICE_INVALID_PARAMETERS},
    {ERR_MSP_VCTCXO_OVER_HIGH,          AT_DEVICE_VCTCXO_OVER_HIGH},
    {ERR_MSP_UE_MODE_ERR,               AT_DEVICE_UE_MODE_ERR},
    {ERR_MSP_NOT_SET_CHAN,              AT_DEVICE_NOT_SET_CHAN},
    {ERR_MSP_OPEN_RFTX_ERROR,           AT_DEVICE_OPEN_UL_CHAN_ERROR},
    {ERR_MSP_OPEN_RFRX_ERROR,           AT_DEVICE_OPEN_DL_CHAN_ERROR},
    {ERR_MSP_OPEN_CHAN_ERROR,           AT_DEVICE_OPEN_CHAN_ERROR},
    {ERR_MSP_CLOSE_CHAN_ERROR,          AT_DEVICE_CLOSE_CHAN_ERROR},
    {ERR_MSP_NOT_SUPPORT,               AT_DEVICE_OPERATION_NOT_SUPPORT},
    {ERR_MSP_INVALID_OP,                AT_DEVICE_INVALID_OP},
    {ERR_MSP_ENTER_BAND_ERROR,          AT_DEVICE_CHAN_BAND_INVALID},
    {ERR_MSP_SET_CHAN_INFOR_ERROR,      AT_DEVICE_SET_CHAN_INFO_FAILURE},
    {ERR_MSP_FRE_CHANI_NOTMATCH,        AT_DEVICE_CHAN_BAND_CHAN_NOT_MAP},
    {ERR_MSP_SET_TX_POWER_FAILUE,       AT_DEVICE_SET_TX_POWER_FAILURE},
    {ERR_MSP_SET_PA_LEVEL_FAILUE,       AT_DEVICE_SET_PA_LEVEL_FAILURE},
    {ERR_MSP_NOT_SET_CURRENT_CHAN,      AT_DEVICE_NOT_SET_CURRENT_CHAN},
    {ERR_MSP_NOT_ABLETO_RD_APC,         AT_DEVICE_CUR_APC_UNAVAILABLE},
    {ERR_MSP_SET_APC_ERROR,             AT_DEVICE_SET_APC_ERR},
    {ERR_MSP_RD_APC_ERROR,              AT_DEVICE_RD_APC_ERR},
    {ERR_MSP_SET_LINA_ERROR,            AT_DEVICE_SET_LNA_ERR},
    {ERR_MSP_NOT_OPEN_RXRX,             AT_DEVICE_NOT_OPEN_DL_CHAN},
    {ERR_MSP_NOT_OPEN_RXTX,             AT_DEVICE_NOT_OPEN_UL_CHAN},
    {ERR_MSP_NO_SIGNAL,                 AT_DEVICE_NO_SIGNAL},
    {ERR_MSP_PHYNUM_LENGTH_ERROR,       AT_DEVICE_PHYNUM_LEN_ERR},
    {ERR_MSP_PHYNUM_INVALID,            AT_DEVICE_PHYNUM_INVALID},
    {ERR_MSP_PHYNUM_TYPE_ERROR,         AT_DEVICE_PHYNUM_TYPE_ERR},
    {ERR_MSP_PLATINFOR_NOTABLE_TORD,    AT_DEVICE_PLATFORM_INFO_UNAVAILABLE},
    {ERR_MSP_WRT_NOT_UNLOCK,            AT_DEVICE_DATA_LOCK},
    {ERR_MSP_CALLNUM_OVER20,            AT_DEVICE_PLMN_OVER_20},
    {ERR_MSP_MNC_ENTER_OVERFLOW,        AT_DEVICE_MNC_NUM_INVALID},
    {ERR_MSP_RD_VER_FAILUE,             AT_DEVICE_GET_VER_ERR},
    {ERR_MSP_OPERTION_ERROR,            AT_DEVICE_PORTLOCK_ERR},
    {ERR_MSP_PWD_ERR,                   AT_DEVICE_PWD_ERR},
    {ERR_MSP_TIME_OUT,                  AT_DEVICE_TIMEOUT_ERR},
    {ERR_MSP_NO_MORE_MEMORY,            AT_DEVICE_NOT_ENOUGH_MEMORY},
    {ERR_MSP_SIMM_LOCK,                 AT_DEVICE_SIMM_LOCK},
    {ERR_MSP_CLOSE_RFTX_ERROR,          AT_DEVICE_CLOSE_UL_CHAN_FAILURE},
    {ERR_MSP_CLOSE_RFRX_ERROR,          AT_DEVICE_CLOSE_DL_CHAN_FAILURE},
    {ERR_MSP_NV_DATA_INVALID,           AT_DEVICE_NV_DATA_INVALID},

};

#define FTM_DUMP_FILE_NAME_LENGTH 50
#define FTM_DUMP_FILE_MAX_NUM     4
#define FTM_DUMP_SIZE_12K                 0x3000

#define FTM_DUMP_LOG_PATH "/modem_log/DrvLog/Ftm/"
#define FTM_DUMP_HEAD            "ftm_"

struct linux_dirent {
	unsigned long	d_ino;
	unsigned long	d_off;
	unsigned short	d_reclen;
	char		    d_name[1];
};


int ftm_create_dir(char *path)
{
    int fd;

    /* 如果文件夹不存在，创建新文件夹*/
    fd = sys_access(path, 0); //F_OK, 检查文件是否存在
    if(0 != fd)
    {
        fd  = sys_mkdir(path, 0660);
        if(fd < 0)
        {
            (VOS_VOID)vos_printf("[%s line %d]create ftm dump log dir failed! ret = %d\n",__FUNCTION__,__LINE__, fd);
            return fd;
        }
    }
    return 0;
}

int ftm_open_dir(char *path)
{
    int fd;

    fd = ftm_create_dir(path);
    if(0 == fd)
    {
        fd = sys_open(path, O_RDONLY| O_DIRECTORY, 0);
    }
    return fd;
}

int ftm_close_dir(int fd)
{
    sys_close(fd);
    return 0;
}

VOS_INT32 atClearOldfile(VOS_INT32 fd, VOS_CHAR * header)
{
    VOS_INT32 ret = 0;
    VOS_INT i;
    VOS_UINT32 index;
    VOS_UINT32 head_len;
    VOS_UINT32 read_bytes;
    VOS_CHAR *buf = NULL;
    struct linux_dirent *dir;
    VOS_CHAR filename[FTM_DUMP_FILE_MAX_NUM][FTM_DUMP_FILE_NAME_LENGTH] = {{0},{0}};
    VOS_CHAR temp[FTM_DUMP_FILE_NAME_LENGTH];

    buf = kmalloc(1024, GFP_KERNEL);
    if(NULL == buf)
    {
        (VOS_VOID)vos_printf("[%s]failed to malloc!\n",__FUNCTION__);
        return -1;
    }

    read_bytes = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
    if(-1 == read_bytes)
    {
        /* 读取文件夹错误 */
        (VOS_VOID)vos_printf("[%s]failed to get dirent!\n",__FUNCTION__);
        ret = -1;
        goto out;
    }

    if(0 == read_bytes)
    {
        /* 文件夹是空的，直接返回OK */
        ret = 0;
        goto out;
    }

    /*轮询文件夹*/
    head_len = strlen(header);
    for(i=0; i<read_bytes; )
    {
        dir = (struct linux_dirent *)(buf + i);
        i += (VOS_UINT32)dir->d_reclen;

        /* 删除旧的和错误的文件 */
        if(0 == strncmp ((char *)dir->d_name, header, head_len))
        {
            strncpy(temp, FTM_DUMP_LOG_PATH, FTM_DUMP_FILE_NAME_LENGTH-1);
            strncat(temp, dir->d_name, FTM_DUMP_FILE_NAME_LENGTH-strlen(FTM_DUMP_LOG_PATH)-1);

            index = simple_strtol(dir->d_name + head_len, NULL, 0);
            // 如果索引号超过最大值，或者有重复，直接删除文件
            if((index >= FTM_DUMP_FILE_MAX_NUM - 1) || (0 != filename[index][0]))
            {
                sys_unlink(temp);
            }
            else
            {
                strncpy(filename[index], temp, FTM_DUMP_FILE_NAME_LENGTH -1);
            }
        }
    }

    /* 文件重命名 */
    for(i=FTM_DUMP_FILE_MAX_NUM-2; i>=0; i--)
    {
        if(filename[i][0])
        {
            snprintf(temp, sizeof(temp), "%s%s%02d.bin", FTM_DUMP_LOG_PATH, FTM_DUMP_HEAD, i+1);
            /* coverity[check_return] */
            (VOS_VOID)sys_rename(filename[i], temp);
        }
    }
out:
    if(buf)
        kfree(buf);

    return ret;
}

/******************************************************************************
 */
/* 函数名称: atChgErrorCode
 */
/* 功能描述: 把其他模块返回的错误码转换成AT的错误码
 */
/*
 */
/* 参数说明:
 */
/*   usTafErrorCode [in] 错误码
 */
/*
 */
/* 返 回 值:
 */
/*    返回AT的错误码
 */
/*
 */
/* 调用要求: TODO: ...
 */
/* 调用举例: TODO: ...
 */
/* 作    者: 崔军强/00064416 [2009-08-11]
 */
/******************************************************************************
 */
static VOS_UINT32 ChgErrorCode(VOS_UINT32 usTafErrorCode)
{
    VOS_UINT32 ulRtn = AT_CME_UNKNOWN;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulErrNum = sizeof(g_stErrCodeTable)/sizeof(AT_ERROR_CODE_TABLE_STRU);

    for(i = 0; i < ulErrNum; i++)
    {
        if(usTafErrorCode == g_stErrCodeTable[i].ulSrcError)
        {
            ulRtn = g_stErrCodeTable[i].ulATError;

            return ulRtn;
        }
    }

    return AT_ERROR;
}



/******************************************************************************
 */
/* 函数名称: CmdErrProc
 */
/* 功能描述: 错误码转换及AT回复上报
 */
/*
 */
/* 参数说明:
 */
/*   ucClientId [in] 客户端ID
 */
/*   ulErrCode [in]  错误码
 */
/*   usBufLen [in]   回复信息
 */
/*   pucBuf [in]     回复信息长度
 */
/*
 */
/* 返 回 值:
 */
/*    无
 */
/*
 */
/* 调用要求: TODO: ...
 */
/* 调用举例: TODO: ...
 */
/* 作    者: 崔军强/00064416 [2009-08-11]
 */
/******************************************************************************
 */
VOS_VOID CmdErrProc(VOS_UINT8 ucClientId, VOS_UINT32 ulErrCode, VOS_UINT16 usBufLen, VOS_UINT8* pucBuf)
{
    VOS_UINT32 ulResult = 0;
    gstAtSendData.usBufLen = usBufLen;
    if(NULL != pucBuf)
    {
        /*MSP_MEMCPY(gstAtSendData.aucBuffer, pucBuf, usBufLen); */
        /*改成下面的以匹配函数 At_FormatResultData */
        MSP_MEMCPY(pgucAtSndCodeAddr, pucBuf, usBufLen);
    }

    if(ERR_MSP_SUCCESS != ulErrCode)
    {
        ulResult = ChgErrorCode(ulErrCode);

        At_FormatResultData(ucClientId, ulResult);
    }
    else
    {
        At_FormatResultData(ucClientId, AT_OK);
    }

    return ;
}


/******************************************************************************
 */
/* 函数名称: atSendFtmDataMsg
 */
/* 功能描述: AT模块给FTM 模块发送消息
 */
/*
 */
/* 参数说明:
 */
/*   TaskId [in] 接收PID
 */
/*   MsgId  [in] 消息ID
 */
/*   ulClientId [in] 端口号
 */
/*   pData  [in] 数据起始
 */
/*   uLen   [in] 数据长度
 */
/* 返 回 值:
 */
/*    ERR_MSP_SUCCESS成功
 */
/*    非ERR_MSP_SUCCESS失败
 */

/******************************************************************************
 */
VOS_UINT32 atSendFtmDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_UINT32 ulClientId, VOS_VOID* pData, VOS_UINT32 uLen)
{
    VOS_UINT32 u32Ret = ERR_MSP_UNKNOWN;
    AT_FW_DATA_MSG_STRU* pMsgBlock = NULL;

    pMsgBlock = (AT_FW_DATA_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_AT,(sizeof(AT_FW_DATA_MSG_STRU)+ uLen - 20));

    if (pMsgBlock)
    {
        pMsgBlock->ulReceiverPid = TaskId;
        pMsgBlock->ulSenderPid   = WUEPS_PID_AT;
        pMsgBlock->ulLength      = sizeof(AT_FW_DATA_MSG_STRU)+ uLen - 20;
        pMsgBlock->ulMsgId      = MsgId;
        pMsgBlock->ulClientId   = ulClientId;
        pMsgBlock->ulLen        = uLen;

        MSP_MEMCPY(pMsgBlock->pContext, pData, uLen);

        u32Ret = VOS_SendMsg(pMsgBlock->ulSenderPid, pMsgBlock);

        if (u32Ret == VOS_OK)
        {
            u32Ret = ERR_MSP_SUCCESS;
        }
    }

    return u32Ret;
}


/*****************************************************************************
 函 数 名  : atSendFtmDataMsg
 功能描述  : AT给其他模块发送消息
 输入参数  : VOS_UINT32 TaskId
             VOS_UINT32 MsgId
             VOS_UINT32 ulClientId
             IN VOS_VOID* pData
             VOS_UINT32 uLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : c64416
    修改内容   : 新生成函数
  1.日    期   : 2013年6月6日
    作    者   : c64416
    修改内容   : 适配L4A优化方案


*****************************************************************************/
VOS_UINT32 atSendDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_VOID* pData, VOS_UINT32 uLen)
{
    VOS_UINT32 u32Ret = 0;
    L4A_COMM_REQ_STRU* pMsgBlock;

    pMsgBlock = (L4A_COMM_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, (uLen - VOS_MSG_HEAD_LENGTH));

    if (pMsgBlock)
    {
        MSP_MEMCPY(pMsgBlock, pData, uLen);

        pMsgBlock->ulReceiverPid    = TaskId;
        pMsgBlock->ulSenderPid      = WUEPS_PID_AT;
        /* coverity[overflow_const] */
        pMsgBlock->ulLength         = (uLen - VOS_MSG_HEAD_LENGTH);
        pMsgBlock->enMsgId          = MsgId;

        u32Ret = VOS_SendMsg(pMsgBlock->ulSenderPid, pMsgBlock);
    }

    return u32Ret;
}

/* 定义了LTE与TDS私有AT命令 */


AT_PAR_CMD_ELEMENT_STRU g_astAtTLCmdTbl[] = {
    {AT_CMD_LWCLASH,
    VOS_NULL_PTR,           AT_SET_PARA_TIME,   AT_QryLwclashPara,      AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,           AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"^LWCLASH",    VOS_NULL_PTR},

    {AT_CMD_RADVER,
    AT_SetRadverPara,       AT_SET_PARA_TIME,   VOS_NULL_PTR,           AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,           AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"^RADVER",    (VOS_UINT8*)"(0-3),(4-16)"},

#if 0
    {AT_CMD_ISMCOEX,
    AT_SetIsmcoexPara,      3000,               AT_QryIsmcoexPara,      AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,           AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"^ISMCOEX",    (VOS_UINT8*)"(@bw),(@bw),(@bw),(@bw),(@bw),(@bw)"},
#endif

    {AT_CMD_LCACELL,
    VOS_NULL_PTR,           AT_NOT_SET_TIME,    AT_QryLcacellPara,      AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,           AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"^LCACELL",    VOS_NULL_PTR}
};



/*lint -restore*/


/*****************************************************************************

 函 数 名  : At_RegisterTLCmdTable

 功能描述  : 向AT解析器注册TDS/LTE专有命令表

 输入参数  : 无

 输出参数  : 无

 返 回 值  : VOS_UINT32

 调用函数  :

 被调函数  :

 修改历史  :

  1.日    期   : 2013年9月22日


     作    者   : c64416

     修改内容   : 新生成函数


*****************************************************************************/
VOS_UINT32 At_RegisterTLCmdTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtTLCmdTbl, sizeof(g_astAtTLCmdTbl)/sizeof(g_astAtTLCmdTbl[0]));
}

