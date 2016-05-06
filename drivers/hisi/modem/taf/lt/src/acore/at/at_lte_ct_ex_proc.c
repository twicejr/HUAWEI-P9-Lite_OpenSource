

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */
/******************************************************************************
 */


/******************************************************************************
 */
/*新增AT命令CheckList(chenpeng/00173035 2010-12-17):
 */
/*
 */
/*
 */
/* 参数检查checklist:
 */
/*   1、AT命令类型是否正确
 */
/*      typedef VOS_UINT8 AT_CMD_OPT_TYPE;
 */
/*      #define AT_CMD_OPT_SET_CMD_NO_PARA     0
 */
/*      #define AT_CMD_OPT_SET_PARA_CMD        1
 */
/*      #define AT_CMD_OPT_READ_CMD            2
 */
/*      #define AT_CMD_OPT_TEST_CMD            3
 */
/*      #define AT_CMD_OPT_BUTT                4
 */
/*
 */
/*   2、参数个数是否符合要求
 */
/*      gucAtParaIndex
 */
/*
 */
/*   3、每个参数的长度是否正确，是否为0
 */
/*      gastAtParaList[0].usParaLen
 */
/*      gastAtParaList[1].usParaLen
 */
/*
 */
/*   4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足
 */
/*      注:参数取值约束应该放在具体的命令处理模块保证，此处仅透明发送
 */
/*      gastAtParaList[0].ulParaValue
 */
/*      gastAtParaList[1].ulParaValue
 */
/******************************************************************************
 */
/*lint -save -e537 -e734 -e813 -e958 -e718 -e746*/
/*#include <stdlib.h>
 */
/*#include "at_common.h"
 */
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"
#include "ATCmdProc.h"

/*快速校准 c00173035  start in 2010-12-14*/

/******************************************************************************
 */
/* 功能描述:  根据用户输入，解析参数列表并初始化相应的结构
 */
/*
 */
/* 参数说明:
 */
/*   pPara     [in] ...
 */
/*   ulListLen [in] ...
 */
/*   pausList  [out] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/*
 */
/* 使用约束:
 */
/*    1、只接受十进制数字字符串作为输入
 */
/*    2、0作为数字开头，以及空格个数在满足所有checklist的条件下不做限制
 */
/*
 */
/* 字符串解析Checklist:
 */
/*    1、检查字符串总长度是否合法
 */
/*    2、检查是否有非期待字符(空格和数字以外)
 */
/*    3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
/*       避免用于 000000123 ，这种非法输入
 */
/*    4、检查字符串解析出的参数个数是否和用户输入的一致
 */
/******************************************************************************
 */
VOS_UINT32 initParaListS16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_INT16* pausList)
{
    VOS_UINT16 ulTmp;
    VOS_UINT8 *pParaData    = pPara->aucPara;
    VOS_UINT8  ucDigitNum   = 0;     /* 记录数字字符个数，不能超过5
 */
    VOS_INT16 usDigitValue = 0;     /* 记录数字数值大小，不能超过65535
 */
    VOS_UINT16 usTmpListNum = 0;     /* 记录解析出来的数字个数，不能超过16
 */
    VOS_BOOL bDigit      = FALSE; /* 是否是数字
 */
	VOS_BOOL bNegative   = FALSE; /* 是否负数
 */
    VOS_UINT32 ulRst        = ERR_MSP_SUCCESS;

    if ((NULL == pPara) ||(pPara->usParaLen > 2048))
    {
        /* 1、检查字符串总长度是否合法
 */
        return ERR_MSP_INVALID_PARAMETER;
    }

    for(ulTmp = 0 ; ulTmp < pPara->usParaLen ; ulTmp++)
    {
        VOS_UINT8 ucChr = *pParaData;

        if(isdigit(ucChr))
        {
            /* 第一个字节为数字或者前面有空格
 */
            if(!bDigit)
            {
                bDigit = TRUE;
                ucDigitNum = 0;
                usDigitValue = 0;

                /* 4、检查字符串解析出的参数个数是否和用户输入的一致
 */
                if(++usTmpListNum > ulListLen)
                {
                    ulRst = ERR_MSP_INVALID_PARAMETER;
                    break;
                }
            }

            /* 3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
            if((++ucDigitNum > 5) ||((32767-usDigitValue*10) < (ucChr - 0x30)))
            {
                ulRst = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            usDigitValue = (VOS_INT16)(usDigitValue*10+(ucChr-0x30));

			pausList[usTmpListNum-1] = (VOS_INT16)((bNegative == FALSE)?(usDigitValue):(usDigitValue*(-1)));
        }
        else if(isspace(ucChr))
        {
			/* 单个'-'符号的异常处理
 */
			if(!bDigit && bNegative)
			{
				break;
			}

            bDigit = FALSE;
			bNegative = FALSE;

			pParaData++;
			continue;
        }
        else if(('-' == ucChr) && !bDigit && !bNegative)
        {
			bNegative = TRUE;

			pParaData++;
			continue;
		}
        else
        {
            /* 2、检查是否有非期待字符(空格和数字以外)
 */
            ulRst = ERR_MSP_INVALID_PARAMETER;
            break;
        }
        pParaData++;
    }

    /* 4、强制检测:检查字符串解析出的参数个数是否和用户输入的一致
 */
    if(usTmpListNum != ulListLen)
    {
        ulRst = ERR_MSP_INVALID_PARAMETER;
    }

    return ulRst;
}




/******************************************************************************
 */
/* 功能描述:  根据用户输入，解析参数列表并初始化相应的结构
 */
/*
 */
/* 参数说明:
 */
/*   pPara     [in] ...
 */
/*   ulListLen [in] ...
 */
/*   pausList  [out] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/*
 */
/* 使用约束:
 */
/*    1、只接受十进制数字字符串作为输入
 */
/*    2、0作为数字开头，以及空格个数在满足所有checklist的条件下不做限制
 */
/*
 */
/* 字符串解析Checklist:
 */
/*    1、检查字符串总长度是否合法
 */
/*    2、检查是否有非期待字符(空格和数字以外)
 */
/*    3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
/*       避免用于 000000123 ，这种非法输入
 */
/*    4、检查字符串解析出的参数个数是否和用户输入的一致
 */
/******************************************************************************
 */
VOS_UINT32 initParaListU16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_UINT16* pausList)
{
    VOS_UINT16 ulTmp;
    VOS_UINT8 *pParaData    = pPara->aucPara;
    VOS_UINT8  ucDigitNum   = 0;  /* 记录数字字符个数，不能超过5
 */
    VOS_UINT16 usDigitValue = 0;  /* 记录数字数值大小，不能超过65535
 */
    VOS_UINT16 usTmpListNum = 0;  /* 记录解析出来的数字个数，不能超过16
 */
    VOS_BOOL bDigit      = FALSE;
    VOS_UINT32 ulRst        = ERR_MSP_SUCCESS;

    if ((NULL == pPara) ||(pPara->usParaLen > 2048))
    {
        /* 1、检查字符串总长度是否合法
 */
        return ERR_MSP_INVALID_PARAMETER;
    }

    for(ulTmp = 0 ; ulTmp < pPara->usParaLen ; ulTmp++)
    {
        VOS_UINT8 ucChr = *pParaData;

        if(isdigit(ucChr))
        {
            /* 第一个字节为数字或者前面有空格
 */
            if(!bDigit)
            {
                bDigit = TRUE;
                ucDigitNum = 0;
                usDigitValue = 0;

                /* 4、检查字符串解析出的参数个数是否和用户输入的一致
 */
                if(++usTmpListNum > ulListLen)
                {
                    ulRst = ERR_MSP_INVALID_PARAMETER;
                    break;
                }
            }

            /* 3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
            if((++ucDigitNum > 5) ||((65535-usDigitValue*10) < (ucChr - 0x30)))
            {
                ulRst = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            usDigitValue = (VOS_UINT16)(usDigitValue*10+(ucChr-0x30));
            pausList[usTmpListNum-1] = usDigitValue;
        }
        else if(isspace(ucChr))
        {
            bDigit = FALSE;

			pParaData++;
			continue;
        }
        else
        {
            /* 2、检查是否有非期待字符(空格和数字以外)
 */
            ulRst = ERR_MSP_INVALID_PARAMETER;
            break;
        }
        pParaData++;
    }

    /* 4、强制检测:检查字符串解析出的参数个数是否和用户输入的一致
 */
    if(usTmpListNum != ulListLen)
    {
        ulRst = ERR_MSP_INVALID_PARAMETER;
    }

    return ulRst;
}


/******************************************************************************
 */
/* 功能描述:  根据用户输入，解析参数列表并初始化相应的结构
 */
/*
 */
/* 参数说明:
 */
/*   pPara     [in] ...
 */
/*   ulListLen [in] ...
 */
/*   pausList  [out] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/*
 */
/* 使用约束:
 */
/*    1、只接受十进制数字字符串作为输入
 */
/*    2、0作为数字开头，以及空格个数在满足所有checklist的条件下不做限制
 */
/*
 */
/* 字符串解析Checklist:
 */
/*    1、检查字符串总长度是否合法
 */
/*    2、检查是否有非期待字符(空格和数字以外)
 */
/*    3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
/*       避免用于 000000123 ，这种非法输入
 */
/*    4、检查字符串解析出的参数个数是否和用户输入的一致
 */
/******************************************************************************
 */

static VOS_UINT32 initParaListU8( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_UINT8* paucList)
{
    VOS_UINT16 ulTmp;
    VOS_UINT8 *pParaData    = pPara->aucPara;
    VOS_UINT8  ucDigitNum   = 0;  /* 记录数字字符个数，不能超过5
 */
    VOS_UINT8  ucDigitValue = 0;  /* 记录数字数值大小，不能超过255
 */
    VOS_UINT16 usTmpListNum = 0;  /* 记录解析出来的数字个数，不能超过16
 */
    VOS_BOOL bDigit = FALSE;
    VOS_UINT32 ulRst        = ERR_MSP_SUCCESS;

    if ((NULL == pPara) ||(pPara->usParaLen > 2048))
    {
        /* 1、检查字符串总长度是否合法
 */
        return ERR_MSP_INVALID_PARAMETER;
    }

    for(ulTmp = 0 ; ulTmp < pPara->usParaLen ; ulTmp++)
    {
        VOS_UINT8 ucChr = *pParaData;

        if(isdigit(ucChr))
        {
            if(!bDigit)
            {
                bDigit       = TRUE;
                ucDigitValue = 0;
                ucDigitNum   = 0;

                /* 4、检查字符串解析出的参数个数是否和用户输入的一致
 */
                if(++usTmpListNum > ulListLen)
                {
                    ulRst = ERR_MSP_INVALID_PARAMETER;
                    break;
                }
            }

            /* 3、检查字符串解析出的参数取值是否符合要求，包括数字字符串长度不能超过5个
 */
            if((++ucDigitNum>3) || ((255-ucDigitValue*10) < (ucChr-0x30)))
            {
                ulRst = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            ucDigitValue = (VOS_UINT8)(ucDigitValue*10+(ucChr-0x30));
            paucList[usTmpListNum-1] = ucDigitValue;
        }
        else if(isspace(ucChr))
        {
            bDigit = FALSE;

			pParaData++;
			continue;
        }
        else
        {
            /* 2、检查是否有非期待字符(空格和数字以外)
 */
            ulRst = ERR_MSP_INVALID_PARAMETER;
            break;
        }
        pParaData++;
    }

    /* 4、强制检测:检查字符串解析出的参数个数是否和用户输入的一致
 */
    if(usTmpListNum != ulListLen)
    {
        ulRst = ERR_MSP_INVALID_PARAMETER;
    }

    return ulRst;
}

/******************************************************************************
 */
/* 功能描述:  ^BANDSW 单板Band切换
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetBandSWPara(VOS_UINT8 ucClientId)
{
    FTM_SET_BANDSW_REQ_STRU stBandSwSetReq;
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
 	if(5 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen)||
       (0 == gastAtParaList[2].usParaLen)||
       (0 == gastAtParaList[3].usParaLen)||
       (0 == gastAtParaList[4].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    if(4 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen)||
       (0 == gastAtParaList[2].usParaLen)||
       (0 == gastAtParaList[3].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#endif
    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */

    stBandSwSetReq.enMode = (FCHAN_MODE_ENUM)(gastAtParaList[0].ulParaValue);
    stBandSwSetReq.ucBand = (VOS_UINT8)(gastAtParaList[1].ulParaValue);
    stBandSwSetReq.usUlCh = (VOS_UINT16)(gastAtParaList[2].ulParaValue);
    stBandSwSetReq.usDlCh = (VOS_UINT16)(gastAtParaList[3].ulParaValue);
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stBandSwSetReq.usDlAbbChanIndex= (VOS_UINT16)(gastAtParaList[4].ulParaValue);
#endif	

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    /*ulRst = atLteSendMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_BANDSW_REQ, (VOS_VOID*)(&stBandSwSetReq), sizeof(stBandSwSetReq));
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_BANDSW_REQ,ucClientId, (VOS_VOID*)(&stBandSwSetReq), sizeof(stBandSwSetReq));


    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_BANDSW_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetBandSWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_BANDSW_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_BANDSW_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^BANDSW 单板Band切换
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryBandSWPara(VOS_UINT8 ucClientId)
{
    FTM_RD_BANDSW_REQ_STRU stBandSWQryReq = {0};
    VOS_UINT32 ulRst;

	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    /*ulRst = atLteSendMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_BANDSW_REQ, (VOS_VOID*)(&stBandSWQryReq), sizeof(stBandSWQryReq));
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_BANDSW_REQ, ucClientId,(VOS_VOID*)(&stBandSWQryReq), sizeof(stBandSWQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_BANDSW_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryBandSWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	FTM_RD_BANDSW_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_BANDSW_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

    /* lkf58113 @ 20111103 add  先判断错误码再决定是否显示结构体内容
 */
    if(ERR_MSP_SUCCESS != pstCnf->ulErrCode)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    }
    else
    {
    	usLength = 0;
    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
    		"^BANDSW:%u,%u",pstCnf->enMode,pstCnf->ucBand);

    	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    }
    return AT_FW_CLIENT_STATUS_READY;
}

/******************************************************************************
 */
/* 功能描述:   ^FCHANS 快速校准命令支持，设置非信令的信道
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFCHANSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FCHANS_REQ_STRU stFFCHANSSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(4 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen) ||
       (0 == gastAtParaList[2].usParaLen) ||
       (0 == gastAtParaList[3].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFFCHANSSetReq.usULFreqNum =(VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stFFCHANSSetReq.usULFreqNum >0) && (stFFCHANSSetReq.usULFreqNum <= CT_F_FREQ_LIST_MAX_NUM))
    {
        ulRst = initParaListU16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),stFFCHANSSetReq.usULFreqNum,stFFCHANSSetReq.usULFreqList);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    stFFCHANSSetReq.usDLFreqNum= (VOS_UINT16)(gastAtParaList[2].ulParaValue);

    if((stFFCHANSSetReq.usDLFreqNum >0) && (stFFCHANSSetReq.usDLFreqNum <= CT_F_FREQ_LIST_MAX_NUM))
    {
        ulRst = initParaListU16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[3])),stFFCHANSSetReq.usDLFreqNum,stFFCHANSSetReq.usDLFreqList);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    /*ulRst = atLteSendMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FCHANS_REQ, (VOS_VOID*)(&stFFCHANSSetReq), sizeof(stFFCHANSSetReq));
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FCHANS_REQ,ucClientId, (VOS_VOID*)(&stFFCHANSSetReq), sizeof(stFFCHANSSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FCHANS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}

VOS_UINT32 atSetFFCHANSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FCHANS_CNF_STRU *pFchansCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFchansCnf = (FTM_SET_F_FCHANS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFchansCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}

/******************************************************************************
 */
/* 功能描述:    ^FCHANS 快速校准命令支持，设置非信令的信道
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFCHANSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FCHANS_REQ_STRU stFFCHANQryReq = {0};
    VOS_UINT32 ulRst;

	/*lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FCHANS_REQ, ucClientId,(VOS_VOID*)(&stFFCHANQryReq), sizeof(stFFCHANQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FCHANS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}
VOS_UINT32 atQryFFCHANSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_RD_F_FCHANS_CNF_STRU *pstCnf = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FCHANS_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
        return ERR_MSP_FAILURE;
	}

    /* lkf58113 @ 20111103 add  先判断错误码再决定是否显示结构体内容
 */
    if(ERR_MSP_SUCCESS != pstCnf->ulErrCode)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    }
    else
    {

    	usLength=0;

        /* ^FCHANS:
 */
    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
            "\r\n^FCHANS:\r\n");

        /* < channel_ul_num >[,< channel_ul_list >]
 */

    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         	"\r\n%u",pstCnf->usULFreqNum);

    	if ((pstCnf->usULFreqNum > 0) && (pstCnf->usULFreqNum <= CT_F_FREQ_LIST_MAX_NUM))
    	{
    		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			",%u",pstCnf->usULFreqList[0]);

    		for( ucTmp = 1 ; ucTmp < pstCnf->usULFreqNum ; ucTmp++)
    		{
    			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			" %u",pstCnf->usULFreqList[ucTmp]);
    		}
    	}
    	else
    	{
    		/*pstCnf->usULFreqNum 为无符，此分支只为0，没有负数情况
 */
    		/*TODO:如果pstCnf->usULFreqNum大于CT_F_FREQ_UL_LIST_MAX_NUM，此处增加SDM信息
 */
    	}

    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
           			(VOS_CHAR *)pgucLAtSndCodeAddr,
           			(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			"%s",
        	 		"\r\n");

    	/* < channel_dl_num >[, < channel_dl_list >]
 */

    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         	"\r\n%u",pstCnf->usDLFreqNum);

    	if ((pstCnf->usDLFreqNum > 0) && (pstCnf->usDLFreqNum <= CT_F_FREQ_LIST_MAX_NUM))
    	{
    		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			",%u",pstCnf->usDLFreqList[0]);

    		for( ucTmp = 1 ; ucTmp < pstCnf->usDLFreqNum ; ucTmp++)
    		{
    			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			" %u", pstCnf->usDLFreqList[ucTmp]);
    		}
    	}
    	else
    	{
    		/*pstCnf->usDLFreqNum 为无符，此分支只为0，没有负数情况
 */
    		/*TODO:如果pstCnf->usDLFreqNum大于CT_F_FREQ_DL_LIST_MAX_NUM，此处增加SDM信息
 */
    	}

    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
         			"%s","\r\n");

    	 CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    }
    return AT_FW_CLIENT_STATUS_READY;
}
/******************************************************************************
 */
/* 功能描述:   ^FSEGMENT 快速校准命令支持，设置SEGMENT长度
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFSEGMENTPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FSEGMENT_REQ_STRU stFFSegmentSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(3 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen)||
        (0 == gastAtParaList[1].usParaLen)||
        (0 == gastAtParaList[2].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFFSegmentSetReq.usSegmentLen   = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
    stFFSegmentSetReq.usMeasOffset   = (VOS_UINT16)(gastAtParaList[1].ulParaValue);
    stFFSegmentSetReq.usMeasLen      = (VOS_UINT16)(gastAtParaList[2].ulParaValue);

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atLteSendMsg 改为 atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FSEGMENT_REQ, ucClientId,(VOS_VOID*)(&stFFSegmentSetReq), sizeof(stFFSegmentSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FSEGMENT_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}
VOS_UINT32 atSetFFSEGMENTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

   	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FSEGMENT_CNF_STRU *pFsegmentCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFsegmentCnf = (FTM_SET_F_FSEGMENT_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFsegmentCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}
/******************************************************************************
 */
/* 功能描述:    ^FSEGMENT 快速校准命令支持，设置SEGMENT长度
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFSEGMENTPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FSEGMENT_REQ_STRU stFFSegmentQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FSEGMENT_REQ,ucClientId, (VOS_VOID*)(&stFFSegmentQryReq), sizeof(stFFSegmentQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FSEGMENT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFFSEGMENTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	FTM_RD_F_FSEGMENT_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FSEGMENT_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

	usLength = 0;
	 usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FSEGMENT:%u,%u,%u",pstCnf->usSegmentLen,pstCnf->usMeasOffset,pstCnf->usMeasLen);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}
/******************************************************************************
 */
/* 功能描述:   ^FPOWS 快速校准命令支持，设置发射机的发射功率
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFPOWSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FPOWS_REQ_STRU stFFPOWSSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFFPOWSSetReq.usTxPowerNum =(VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stFFPOWSSetReq.usTxPowerNum > 0) && (stFFPOWSSetReq.usTxPowerNum <= CT_F_TXPOW_SET_MAX_NUM))
    {
        ulRst = initParaListS16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),stFFPOWSSetReq.usTxPowerNum,stFFPOWSSetReq.asTxPower);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FPOWS_REQ, ucClientId,(VOS_VOID*)(&stFFPOWSSetReq), sizeof(stFFPOWSSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPOWS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FPOWS_CNF_STRU *pFpowsCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFpowsCnf = (FTM_SET_F_FPOWS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFpowsCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:    ^FPOWS 快速校准命令支持，设置发射机的发射功率
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFPOWSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FPOWS_REQ_STRU stFFPowsQryReq = {0};
    VOS_UINT32 ulRst;

	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FPOWS_REQ,ucClientId, (VOS_VOID*)(&stFFPowsQryReq), sizeof(stFFPowsQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPOWS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFFPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	FTM_RD_F_FPOWS_CNF_STRU *pstCnf =  NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FPOWS_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	/* ^FPOWS:< power_num >[,< power_list >]
 */
    usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FPOWS:%u",pstCnf->usTxPowerNum);

	if ((pstCnf->usTxPowerNum > 0) && (pstCnf->usTxPowerNum <= CT_F_TXPOW_SET_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				",%d",pstCnf->asTxPower[0]);

		for( ucTmp = 1 ; ucTmp < pstCnf->usTxPowerNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %d",pstCnf->asTxPower[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usTxPowerNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usTxPowerNum大于CT_F_TXPOW_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^FPAS 快速校准命令支持，设置发射机PA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFPASPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FPAS_REQ_STRU stFFPASSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFFPASSetReq.usPaLevelNum =(VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stFFPASSetReq.usPaLevelNum > 0) && (stFFPASSetReq.usPaLevelNum <= CT_F_PA_SET_MAX_NUM))
    {
        ulRst = initParaListU8((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),stFFPASSetReq.usPaLevelNum,stFFPASSetReq.aucPaLevelList);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FPAS_REQ, ucClientId,(VOS_VOID*)(&stFFPASSetReq), sizeof(stFFPASSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPAS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFPASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FPAS_CNF_STRU *pFpasCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFpasCnf = (FTM_SET_F_FPAS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFpasCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:    ^FPAS 快速校准命令支持，设置发射机PA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFPASPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FPAS_REQ_STRU stFFPasQryReq = {0};
    VOS_UINT32 ulRst;

	/* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FPAS_REQ,ucClientId, (VOS_VOID*)(&stFFPasQryReq), sizeof(stFFPasQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPAS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}
VOS_UINT32 atQryFFPASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	FTM_RD_F_FPAS_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FPAS_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}
	/* ^FPAS:< level_num >,< level_list >
 */

	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FPAS:%u",pstCnf->usPaLevelNum);

	if ((pstCnf->usPaLevelNum > 0) && (pstCnf->usPaLevelNum <= CT_F_PA_SET_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				",%u",pstCnf->aucPaLevelList[0]);

		for( ucTmp = 1 ; ucTmp < pstCnf->usPaLevelNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %u",pstCnf->aucPaLevelList[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usPaLevelNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usPaLevelNum大于CT_F_PA_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^FLNAS 快速校准命令支持，设置接收机LNA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFLNASPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_AAGC_REQ_STRU stFAAGCSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFAAGCSetReq.usAagcNum =(VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stFAAGCSetReq.usAagcNum > 0 ) && (stFAAGCSetReq.usAagcNum <= CT_F_AAGC_SET_MAX_NUM))
    {
        ulRst = initParaListU8((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),stFAAGCSetReq.usAagcNum,stFAAGCSetReq.aucAAGCValue);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FLNAS_REQ,ucClientId ,(VOS_VOID*)(&stFAAGCSetReq), sizeof(stFAAGCSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FLNAS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFLNASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_F_AAGC_CNF_STRU *pFlnasCnf = NULL;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pFlnasCnf = (FTM_SET_F_AAGC_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pFlnasCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:    ^FLNAS 快速校准命令支持，设置接收机LNA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFLNASPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_AAGC_REQ_STRU stFAagcsQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FLNAS_REQ, ucClientId,(VOS_VOID*)(&stFAagcsQryReq), sizeof(stFAagcsQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FLNAS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFFLNASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_AAGC_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_AAGC_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}
	/* ^FLNAS:< level_num >[,< level_list >]
 */
    usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FLNAS:%u",pstCnf->usAagcNum);

	if ((pstCnf->usAagcNum > 0) && (pstCnf->usAagcNum <= CT_F_AAGC_SET_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				",%u",pstCnf->aucAAGCValue[0]);

		for( ucTmp = 1 ; ucTmp < pstCnf->usAagcNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %u",pstCnf->aucAAGCValue[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usAagcNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usAagcNum大于CT_F_AAGC_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^FTXWAVE 快速校准命令支持，设置发射的波形
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFTXWAVEPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FTXWAVE_REQ_STRU stFTxWaveSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFTxWaveSetReq.usWaveType =(VOS_UINT16)(gastAtParaList[0].ulParaValue);

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FTXWAVE_REQ,ucClientId, (VOS_VOID*)(&stFTxWaveSetReq), sizeof(stFTxWaveSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FTXWAVE_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFTXWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_F_FTXWAVE_CNF_STRU *pFtxwaveCnf = NULL;


	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pFtxwaveCnf = (FTM_SET_F_FTXWAVE_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pFtxwaveCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^FTXWAVE 快速校准命令支持，设置发射的波形
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFTXWAVEPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FTXWAVE_REQ_STRU stFFTxwaveQryReq = {0};
    VOS_UINT32 ulRst;
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FTXWAVE_REQ, ucClientId,(VOS_VOID*)(&stFFTxwaveQryReq), sizeof(stFFTxwaveQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FTXWAVE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFFTXWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_FTXWAVE_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;
	/*VOS_UINT8 ucTmp = 0;
 */

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FTXWAVE_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
    	"^FTXWAVE:%u",pstCnf->usWaveType);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}
/******************************************************************************
 */
/* 功能描述:   ^FSTART 快速校准命令支持，启动TRIGGER及校准流程
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFSTARTPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_TRIGGER_REQ_STRU stFTriggerSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */

    stFTriggerSetReq.ucType = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FSTART_REQ,ucClientId ,(VOS_VOID*)(&stFTriggerSetReq), sizeof(stFTriggerSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FSTART_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_F_TRIGGER_CNF_STRU *pFstartCnf = NULL;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pFstartCnf = (FTM_SET_F_TRIGGER_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pFstartCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}
/******************************************************************************
 */
/* 功能描述:   ^FSTART 快速校准命令支持，启动TRIGGER及校准流程
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFFSTARTPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_TRIGGER_REQ_STRU stFTriggerQryReq = {0};
    VOS_UINT32 ulRst;
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FSTART_REQ, ucClientId,(VOS_VOID*)(&stFTriggerQryReq), sizeof(stFTriggerQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FSTART_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFFSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_TRIGGER_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;
	/*VOS_UINT8 ucTmp = 0;
 */

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_TRIGGER_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FSTART:%u,%u",pstCnf->ucStatus,pstCnf->ucType);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}
/******************************************************************************
 */
/* 功能描述:   ^FRSSIS 快速校准支持，查询RSSI功能命令
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFRSSISPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FRSSIS_REQ_STRU stFFRSSISSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stFFRSSISSetReq.usDLFreq = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FRSSIS_REQ, ucClientId,(VOS_VOID*)(&stFFRSSISSetReq), sizeof(stFFRSSISSetReq));
    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FRSSIS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFRSSISParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_F_FRSSIS_CNF_STRU *pstCnf = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_F_FRSSIS_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	/* ^FRSSIS:< rvalue_num >[,< rvalue_list_1 >,< rvalue_list_2 >]
 */
	usLength = 0;
	usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
			"^FRSSIS:%d",pstCnf->usRSSIPowNum);

	/* 天线1的功率列表
 */
	if ((pstCnf->usRSSIPowNum > 0) && (pstCnf->usRSSIPowNum <= RSSI_POW_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
			",%d",pstCnf->ausRxANT1RSSI[0]);
		for( ucTmp = 1 ; ucTmp < pstCnf->usRSSIPowNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %d",pstCnf->ausRxANT1RSSI[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usAagcNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usAagcNum大于CT_F_AAGC_SET_MAX_NUM，此处增加SDM信息
 */
	}

	/* 天线2的功率列表
 */
	if ((pstCnf->usRSSIPowNum > 0) && (pstCnf->usRSSIPowNum <= RSSI_POW_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
			",%d",pstCnf->ausRxANT2RSSI[0]);
		for( ucTmp = 1 ; ucTmp < pstCnf->usRSSIPowNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %d",pstCnf->ausRxANT2RSSI[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usAagcNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usAagcNum大于CT_F_AAGC_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}
/*快速校准 c00173035  end in 2010-12-14*/


/******************************************************************************
 */
/* 功能描述:   ^FCMTMS 快速校准支持，查询芯片温度功能命令
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFFCMTMSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FCMTMS_REQ_STRU stFFCmtmsQryReq = {0};
    VOS_UINT32 ulRst;
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FCMTMS_REQ,ucClientId, (VOS_VOID*)(&stFFCmtmsQryReq), sizeof(stFFCmtmsQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FCMTMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atSetFFCMTMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
	FTM_RD_F_FCMTMS_CNF_STRU *pstCnf = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_F_FCMTMS_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	/* ^FCMTMS:< channel_num >[,< temperature_list >
 */
	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCMTMS:%u",pstCnf->usCmtmsNum);

	if ((pstCnf->usCmtmsNum > 0) && (pstCnf->usCmtmsNum <= CT_F_FREQ_LIST_MAX_NUM))
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				",%u",pstCnf->ausCmtms[0]);

		for( ucTmp = 1 ; ucTmp < pstCnf->usCmtmsNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %u",pstCnf->ausCmtms[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usAagcNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usAagcNum大于CT_F_AAGC_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);

    return ERR_MSP_SUCCESS;

}

/******************************************************************************
 */
/* 功能描述:   ^FBLK 快速校准支持，
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */

VOS_UINT32 atSetFBLKPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FBLK_REQ_STRU stFBLK = {0};
    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多
 */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 如果没有默认设置的模式，返回失败
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        stFBLK.ulBlocking= gastAtParaList[0].ulParaValue;
    }

    /* 执行命令操作
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    if(AT_SUCCESS == atSendFtmDataMsg(MSP_SYS_FTM_PID,ID_MSG_FTM_F_SET_FBLK_REQ,ucClientId,
        (VOS_VOID*)(&stFBLK), sizeof(FTM_SET_F_FBLK_REQ_STRU)))
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FBLK_SET;

        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}

VOS_UINT32 atSetFBLKParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FBLK_CNF_STRU *pFBLKCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFBLKCnf = (FTM_SET_F_FBLK_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFBLKCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}
VOS_UINT32 atQryFBLKPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FBLK_REQ_STRU stQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FBLK_REQ,ucClientId, (VOS_VOID*)(&stQryReq), sizeof(stQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FBLK_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}
VOS_UINT32 atQryFBLKParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_FBLK_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FBLK_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FBLK:%u",pstCnf->ulBlocking);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述:   ^FIPSTART 快速校准支持，
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */

VOS_UINT32 atSetFIPSTARTPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FIPSTART_REQ_STRU stFIPSTART = {0};
    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多
 */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 如果没有默认设置的模式，返回失败
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        stFIPSTART.ulChannel= gastAtParaList[0].ulParaValue;
    }

    /* 执行命令操作
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    if(AT_SUCCESS == atSendFtmDataMsg(MSP_SYS_FTM_PID,ID_MSG_FTM_F_SET_FIPSTART_REQ,ucClientId,
        (VOS_VOID*)(&stFIPSTART), sizeof(FTM_SET_F_FIPSTART_REQ_STRU)))
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FIPSTART_SET;

        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}

VOS_UINT32 atSetFIPSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FIPSTART_CNF_STRU *pFIPSTART = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFIPSTART = (FTM_SET_F_FIPSTART_CNF_STRU *)pEvent->ulParam1;

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FIPSTART:%d,%d",pFIPSTART->ulIp2Value1,pFIPSTART->ulIp2Value2);

    CmdErrProc(ucClientId, pFIPSTART->ulErrCode, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;

}

VOS_UINT32 atSetFPDMSPara(VOS_UINT8 ucClientId)
{

    FTM_SET_F_FPDMS_REQ_STRU stFPDMS = {0};
    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多
 */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 如果没有默认设置的模式，返回失败
 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        stFPDMS.ulSwitch= gastAtParaList[0].ulParaValue;
    }

    /* 执行命令操作
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    if(AT_SUCCESS == atSendFtmDataMsg(MSP_SYS_FTM_PID,ID_MSG_FTM_SET_FPDMS_REQ,ucClientId,
        (VOS_VOID*)(&stFPDMS), sizeof(FTM_SET_F_FPDMS_REQ_STRU)))
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPDMS_SET;

        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}

VOS_UINT32 atSetFPDMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FPDMS_CNF_STRU *pFPDMS = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFPDMS = (FTM_SET_F_FPDMS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFPDMS->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}
VOS_UINT32 atQryFPDMSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_F_FPDMS_REQ_STRU stFPDMSQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FPDMS_REQ, ucClientId, (VOS_VOID*)(&stFPDMSQryReq), sizeof(stFPDMSQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPDMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFPDMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_FPDMS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FPDMS_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FPDMS:%d",
        pstCnf->ulSwitch);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/***************************************************************************************
 */
/*
 */
/*
 */
VOS_UINT32 atSetFPAPOWERPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FPAPOWER_REQ_STRU stSetReq = {0};
    VOS_UINT32 ulRst;

    /* 1、AT命令类型是否正确
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2、参数个数是否符合要求
 */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 3、每个参数的长度是否正确，是否为0
 */
    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
 */
    stSetReq.usPaLeverNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stSetReq.usPaLeverNum > 0) && (stSetReq.usPaLeverNum <= CT_F_TXPOW_SET_MAX_NUM))
    {
        ulRst = initParaListS16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),stSetReq.usPaLeverNum,(VOS_INT16*)(stSetReq.usMaxPowerList));
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
 */
    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FPAPOWER_REQ,ucClientId, (VOS_VOID*)(&stSetReq), sizeof(stSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPAPOWER_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}
VOS_UINT32 atSetFPAPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FPAPOWER_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_F_FPAPOWER_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}
VOS_UINT32 atQryFPAPOWERPara(VOS_UINT8 ucClientId)
{
    
    FTM_RD_F_FPAPOWER_REQ_STRU stFPAPOWERQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FPAPOWER_REQ, ucClientId, (VOS_VOID*)(&stFPAPOWERQryReq), sizeof(stFPAPOWERQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPAPOWER_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFPAPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    
    FTM_RD_F_FPAPOWER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;
    VOS_UINT8 ucTmp = 0;
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FPAPOWER_CNF_STRU *)pEvent->ulParam1;
    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }
    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FPAPOWER:%u,",
        pstCnf->usPaLeverNum);

	if ((pstCnf->usPaLeverNum > 0) && (pstCnf->usPaLeverNum <= CT_F_TXPOW_SET_MAX_NUM))
	{
		for( ucTmp = 0 ; ucTmp < pstCnf->usPaLeverNum ; ucTmp++)
		{
			usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
				" %d",pstCnf->usMaxPowerList[ucTmp]);
		}
	}
	else
	{
		/*pstCnf->usPaLeverNum 为无符，此分支只为0，没有负数情况
 */
		/*TODO:如果pstCnf->usTxPowerNum大于CT_F_TXPOW_SET_MAX_NUM，此处增加SDM信息
 */
	}
	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

/***************************************************************************************
 */
/*
 */
/*
 */
VOS_UINT32 atSetFMAXPOWERPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FMAXPOWER_REQ_STRU stSetReq = {0};
    VOS_UINT32 ulRst;

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].usParaLen)||
    (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    stSetReq.usPaLevelNum= (VOS_UINT16)(gastAtParaList[0].ulParaValue);
	stSetReq.usPaReduceGain = (VOS_UINT16)(gastAtParaList[1].ulParaValue);

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FMAXPOWER_REQ, ucClientId, (VOS_VOID*)(&stSetReq), sizeof(stSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FMAXPOWER_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;

}
VOS_UINT32 atSetFMAXPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FMAXPOWER_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_F_FMAXPOWER_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

VOS_UINT32 atQryFMAXPOWERPara(VOS_UINT8 ucClientId)
{
    
    FTM_RD_F_FMAXPOWER_REQ_STRU stFMAXPOWERQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FMAXPOWER_REQ,ucClientId, (VOS_VOID*)(&stFMAXPOWERQryReq), sizeof(stFMAXPOWERQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FMAXPOWER_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFMAXPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    

    FTM_RD_F_FMAXPOWER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FMAXPOWER_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FMAXPOWER:%u,%d",
        pstCnf->usPaLevelNum,pstCnf->usPaReduceGain);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

// *****************************************************************************
// 功能描述:   ^FCALPDDCS 快速校准支持，启动上行PD直流校椎
//
// 参数说明:
//   ulIndex [in] ...信道号
//                ...
//
// 返 回 值:
//    TODO: ...
// *****************************************************************************
VOS_UINT32 atSetFCALPDDCSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FCALPDDCS_REQ_STRU stFCALPDDCSSetReq = {0};
    VOS_UINT32 ulRst;

    // 1、AT命令类型是否正确
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 2、参数个数是否符合要求
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 3、每个参数的长度是否正确，是否为0
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
    stFCALPDDCSSetReq.ulPdAutoFlg = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    // 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
    // lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FCALPDDCS_REQ, ucClientId,(VOS_VOID*)(&stFCALPDDCSSetReq), sizeof(stFCALPDDCSSetReq));
    if(AT_SUCCESS == ulRst)
    {
        // 设置当前操作类型
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FCALPDDCS_SET;
        return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFCALPDDCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FCALPDDCS_CNF_STRU *pFCalPDDCSCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFCalPDDCSCnf = (FTM_SET_F_FCALPDDCS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFCalPDDCSCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}


VOS_UINT32 atQryFCALPDDCSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stCALPDDCSQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_RD_FCALPDDCS_REQ, ucClientId,(VOS_VOID*)(&stCALPDDCSQryReq), sizeof(stCALPDDCSQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FCALPDDCS_RD;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFCALPDDCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_F_FCALPDDCS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_F_FCALPDDCS_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
    	return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pstCnf->ulErrCode)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    }
    else
    {
    	usLength = 0;
    	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
    		"^FCALPDDCS: %u \r\n ^FCALPDDCS:DAC:%u \r\n ^FCALPDDCS:VGA:%u", pstCnf->usStatus, pstCnf->usDacCfg, pstCnf->usVgaCfg);

    	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    }
    return AT_FW_CLIENT_STATUS_READY;
}


// *****************************************************************************
// 功能描述:   ^FPDPOWS 快速校准命令支持，设置PD功率电压曲线校准开关 功能命令
//
// 参数说明:
//   ulIndex [in] ...ON / OFF
//                ...
//
// 返 回 值:
//    TODO: ...
// *****************************************************************************
VOS_UINT32 atSetFPDPOWSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_F_FPDPOWS_REQ_STRU stFPDPOWS = {0};
    // 参数检查
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 参数过多
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 如果没有默认设置的模式，返回失败
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        stFPDPOWS.ulPdEnbFlg = gastAtParaList[0].ulParaValue;
		stFPDPOWS.usDacCfg = gastAtParaList[1].ulParaValue;
		stFPDPOWS.usVgaCfg = gastAtParaList[2].ulParaValue;
    }

    if(AT_SUCCESS == atSendFtmDataMsg(MSP_SYS_FTM_PID,ID_MSG_FTM_SET_FPDPOWS_REQ,ucClientId,
        (VOS_VOID*)(&stFPDPOWS), sizeof(FTM_SET_F_FPDPOWS_REQ_STRU)))
    {
        // 设置当前操作类型
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FPDPOWS_SET;

        return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
    }

    return AT_ERROR;

}

VOS_UINT32 atSetFPDPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_F_FPDPOWS_CNF_STRU *pFPDPOWS = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pFPDPOWS = (FTM_SET_F_FPDPOWS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pFPDPOWS->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}

// *****************************************************************************
// 功能描述:   ^FQPDDCRES 快速校准支持，查询PD电压与功率曲线校准的电压值
//
// 参数说明:
//   ulIndex [in] ...信道号
//                ...
//
// 返 回 值:
//    TODO: ...
// *****************************************************************************
VOS_UINT32 atSetFQPDDCRESPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FQPDDCRES_REQ_STRU stFQPDDCRESSetReq = {0};
    VOS_UINT32 ulRst;

    // 1、AT命令类型是否正确
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 2、参数个数是否符合要求
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 3、每个参数的长度是否正确，是否为0
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 4、每个参数取值的约束(取值范围，与其他参数的依赖等)是否满足(注:业务处理模块保证，此处仅透明发送)
    stFQPDDCRESSetReq.ulChannel = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    // 5、发送消息给命令处理模块:透明传送用户符合格式的输入，不判断输入值的正确性
    // lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_F_SET_FQPDDCRES_REQ, ucClientId,(VOS_VOID*)(&stFQPDDCRESSetReq), sizeof(stFQPDDCRESSetReq));
    if(AT_SUCCESS == ulRst)
    {
        // 设置当前操作类型
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_F_FQPDDCRES_SET;
        return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFQPDDCRESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_FQPDDCRES_CNF_STRU *pstCnf = NULL;
	VOS_UINT16 usLength = 0;
	VOS_UINT8 ucTmp = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_FQPDDCRES_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	// ^FQPDDCRES:< rvalue_num >[,< rvalue_list_1 >]
	usLength = 0;

	for( ucTmp = 0 ; ucTmp < RSSI_POW_MAX_NUM ; ucTmp++)
	{
		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
			" %u",pstCnf->ausPDDCValue[ucTmp]);
	}

	CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}


/*lint -restore*/


