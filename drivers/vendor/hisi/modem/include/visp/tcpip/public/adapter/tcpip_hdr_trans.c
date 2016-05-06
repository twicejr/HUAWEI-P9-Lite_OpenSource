/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              hdr_trans.c
*
*  Project Code: VISPV100R007C03
*   Module Name: PUBLIC  
*  Date Created: 2009-02-27
*        Author: VISPV100R007C03项目组
*   Description: VISP 健康体检报告与临终遗言解析翻译模块
*                可以支持脱离协议栈独立编译。
*   使用说明：
*   1、首先需要在VISP协议栈启动之前进调用注册函数，把写二进制文件的函数注册到协议栈
*       TCPIP_RegFuncHealthOutputHook(HDR_Translate);
*       TCPIP_RegFuncLastWordOutputHook(HDR_LastWord_Translate);
*   2、从VISP资料手册中获取解析二进制文件的描述文件
*   3、运行本文件编译后的exe程序按照提示输入
*       1)、输入二进制文件名,如e:/tcpiphealth1.file,e:/tcpiplastword.file
*       2)、输入解析二进制文件的描述文件名,如e:/tcpiphealth.ini,e:/tcpiplastword.ini
*       3)、输入描述ID,如是解析临终遗言则此扫描ID无效
*       4)、输入写二进制文件时是大头序还是小头序。0:表示大头序,1:表示小头序
*   4、运行后会在exe同一目录中生成记录解析结果文件。如tcpiphealthresualt1.txt
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-27   VISPV100R007C03项目组   Create
*******************************************************************************/
#ifdef  __cplusplus
    extern  "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tcpip_hdr_trans.h"

/* 接口索引 与 接口名对应关系表头 */
HDR_IFNAMEANDINDEX_S *g_pstNameAndIndex = NULL;

/* 大小头序标识 */
ULONG g_HDRByteOrder = 1; /* 默认小字头 */

/* 体检模块ID */
CHAR *HDR_Trans_ModuleName[] = 
{
    "null",
    "ifnet",
    "ip",
    "etharp",
    "trunk",
    "ppp",
    "poes",
    "pppoe",
    "dhcp4c",
    "dhcp4r",
    "sfib",
    "socket",
    "bfd",
    "public",
    "tcp",
    "oam3ah",
    "oam1ag",
    "igmp",
    "mstp",
    "mp",
    "null",
    "null",
};

/* 最大模块数 */
ULONG g_ulHdrMaxModule = 22;

/*******************************************************************************
*    Func Name: HDR_toHL
* Date Created: 2009-02-26
*       Author: zhukun
*  Description: 将二进制报告中的数值转化为本PC的主机序
*        Input: ULONG ulX
*       Output: 
*       Return: 本PC的主机序数值
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zhukun                  Create
*
*******************************************************************************/
ULONG HDR_toHL(ULONG ulX)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    if(g_HDRByteOrder == HDR_LITTLE_ENDIAN)
    {
        /* 体检报告是在小字头设备上记录的，与本解析工具一致，无需转换 */
        return ulX;
    }
    else
    {
        /* 体检报告是在大字头设备上记录的，与本解析工具不一致，无需转换 */
        return ((((ulX) & 0x000000ff) << 24) | \
                (((ulX) & 0x0000ff00) <<  8) | \
                (((ulX) & 0x00ff0000) >>  8) | \
                (((ulX) & 0xff000000) >> 24))      ;
    }
#endif
}

/*******************************************************************************
*    Func Name: HDR_toHS
* Date Created: 2009-02-26
*       Author: zhukun
*  Description: 将二进制报告中的数值转化为本PC的主机序
*        Input: USHORT usX
*       Output: 
*       Return: 本PC的主机序数值
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zhukun                  Create
*
*******************************************************************************/
USHORT HDR_toHS(USHORT usX)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    if(g_HDRByteOrder == HDR_LITTLE_ENDIAN)
    {
        /* 体检报告是在小字头设备上记录的，与本解析工具一致，无需转换 */
        return usX;
    }
    else
    {
        /* 体检报告是在大字头设备上记录的，与本解析工具不一致，无需转换 */
        return ((((usX) & 0x00ff) << 8) | \
                (((usX) & 0xff00) >> 8))      ;
    }
#endif
}

/*******************************************************************************
*    Func Name: Hdr_IpAddrToStr
* Date Created: 2009-03-26
*       Author: ZhengSenHuo 104483
*  Description: 把ULONG的地址转换成点分十进制
*        Input: ULONG ulAddr:地址(必须为主机序)
*       Output: CHAR *szStr:点分十进制地址
*       Return: 点分十进制地址
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
CHAR  *Hdr_IpAddrToStr(ULONG ulAddr, CHAR *szStr)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    if (NULL ==szStr)
    {
        return NULL;
    }

    (VOID)TCPIP_SNPRINTF0(szStr, LEN_128, P4("%d.%d.%d.%d", 
        ulAddr >> 24, (ulAddr >> 16) & 0xff,
        (ulAddr >> 8) & 0xff, ulAddr & 0xff));
    return szStr;
#endif
}

/*******************************************************************************
*    Func Name: HDR_Translate
* Date Created: 2009-03-28
*       Author: ZhengSenHuo(104483)
*  Description: 写VISP体检报告二进制文件
*        Input: UCHAR* pHDRMsg:体检报告消息指针
*               ULONG ulMsgLen:体检报告消息长度
*               ULONG ulScanId:扫描ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-28   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
VOID HDR_Translate(UCHAR* pHDRMsg, ULONG ulMsgLen, ULONG ulScanId)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    /* 写体检报告二进制文件 */
    HDR_WriteBinaryFile(pHDRMsg, ulMsgLen, TYPE_HEALTH_CHECKUP,ulScanId);
#endif
}

/*******************************************************************************
*    Func Name: HDR_LastWord_Translate
* Date Created: 2009-03-28
*       Author: ZhengSenHuo(104483)
*  Description: 写VISP临终遗言二进制文件
*        Input: UCHAR* pHDRMsg:临终遗言消息指针
*               ULONG ulMsgLen:临终遗言消息长度
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-28   ZhengSenHuo(104483)       Create
*
*******************************************************************************/
VOID HDR_LastWord_Translate(UCHAR* pHDRMsg, ULONG ulMsgLen)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    /* 写临终遗言二进制文件 */
    HDR_WriteBinaryFile(pHDRMsg, ulMsgLen, TYPE_LASTWORD_CHECKUP,0);
#endif
}

/*******************************************************************************
*    Func Name: HDR_WriteBinaryFile
* Date Created: 2009-03-28
*       Author: ZhengSenHuo(104483)
*  Description: 
*        Input: UCHAR* pHDRMsg: 消息体指针
*               ULONG ulMsgLen: 消息长度
*               ULONG ulMsgType:消息类型
*               ULONG ulScanId: 扫描ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-28   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
VOID HDR_WriteBinaryFile(UCHAR* pHDRMsg, ULONG ulMsgLen, ULONG ulMsgType, ULONG ulScanId)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    CHAR  szFileName[LEN_128];
    FILE *fpWrite = NULL;

    if (TYPE_HEALTH_CHECKUP == ulMsgType)
    {
        (VOID)TCPIP_SNPRINTF0(szFileName, LEN_128, P1("e:/tcpiphealth%d.file",ulScanId));
    }
    else
    {
        (VOID)TCPIP_SNPRINTF0(szFileName, LEN_128, P0("e:/tcpiplastword.file"));
    }
    
    fpWrite = fopen(szFileName,"ab");
    if (NULL == fpWrite)
    {
        printf("\r\nError occurs while openning file.");
        return;
    }

    if (fwrite(pHDRMsg,ulMsgLen,1,fpWrite) != 1)
    {
        printf("\r\nError occurs while writing file.");
    }

    fclose(fpWrite);
#endif
    return;
    
}

/*******************************************************************************
*    Func Name: HDR_GetLineByFile
* Date Created: 2009-03-26
*       Author: ZhengSenHuo(104483)
*  Description: 从文本文件中读取一行
*        Input: FILE *fp:文件句柄
*       Output: UCHAR *pucLine:当前行
*               ULONG *pulLineLen:当前行的长度
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   ZhengSenHuo(104483)  Create
*
*******************************************************************************/
VOID HDR_GetLineByFile(FILE *fp, UCHAR *pucLine, ULONG *pulLineLen)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    /*CHAR ch;*/
    LONG ch;/*by shuxieliu00176784, at 2011-05-16. 修改原因: fgetc返回值类型是整型 */    
    CHAR cNextCh;
    UCHAR *pucBuf = pucLine;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (('\r' == (CHAR)ch) || ('\n' == (CHAR)ch))
        {
            if ('\r' == (CHAR)ch)
            {
                cNextCh = (CHAR)fgetc(fp);/*by shuxieliu00176784, at 2011-05-16. 修改原因: fgetc返回值类型是整型 */
                if ('\n' != cNextCh)
                {
                    fseek(fp,-1,SEEK_CUR);
                }
            }
            break;
        }
        /* Modified by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
        /* 将ch前添加(UCHAR),保证两端类型一致 */
        *pucBuf = (UCHAR)ch;
        
        pucBuf++;
        (*pulLineLen)++;
    }

    pucBuf[0] = 0;
#endif
    return ;
}

/*******************************************************************************
*    Func Name: HDR_GetBeginLineByType
* Date Created: 2009-04-07
*       Author: ZhengSenHuo(104483)
*  Description: 查找配置文件中的子消息类型是否与输入的一致
*        Input: FILE *fp:
*               ULONG ulSubType:
*               
*       Output: ULONG *pulSubLen:结构体长度
*               UCHAR *uszInfo:  结构体说明信息
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-07   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
ULONG HDR_GetBeginLineByType(FILE *fp,ULONG ulSubType,ULONG *pulSubLen,UCHAR *uszInfo)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    CHAR  szLine[LEN_256] = {0};
    ULONG ulLineLen = 0;
    CHAR *pcCurStr = NULL;
    CHAR *pcNextStr;
    ULONG ulCfgSubType;
    UCHAR ucSubTemp[LEN_128];
        
    while (1)
    {
        while (!feof(fp))
        {
            ulLineLen = 0;
            HDR_GetLineByFile(fp,(UCHAR*)szLine,&ulLineLen);
            if ((0 == strlen(szLine)) || (0 == ulLineLen))
            {
                break;
            }

            pcCurStr = NULL;
            if (NULL != (pcCurStr = strstr(szLine,"BEGIN")))
            {
                break;
            }
        }

        if (NULL == pcCurStr)
        {
            break;
        }

        if (NULL == (pcNextStr = strstr(pcCurStr,",")))
        {
            break;
        }
        
        (VOID)TCPIP_Mem_Copy(ucSubTemp, LEN_128, (pcCurStr + strlen("BEGIN:")), pcNextStr - (pcCurStr + strlen("BEGIN:")));
        ucSubTemp[pcNextStr - (pcCurStr + strlen("BEGIN:"))] = 0;
        ulCfgSubType = atoi((CHAR *)ucSubTemp);

        if (ulCfgSubType == ulSubType)
        {
            /* 移到第一个","后面 */
            pcCurStr = pcNextStr + 1;
            /* 获取结构体长度 */
            if (NULL != (pcNextStr = strstr(pcCurStr,",")))
            {
                (VOID)TCPIP_Mem_Copy(ucSubTemp, LEN_128, pcCurStr, pcNextStr - pcCurStr);
                ucSubTemp[pcNextStr - pcCurStr] = 0;
                (*pulSubLen) = atoi((CHAR *)ucSubTemp);
            }

            /* 获取结构体说明信息 */
            if (NULL != (pcCurStr = strstr(pcCurStr,"\"")))
            {
                if (NULL != (pcNextStr = strstr(pcCurStr + 1,"\"")))
                {
                    (VOID)TCPIP_Mem_Copy(uszInfo, LEN_256, (pcCurStr + 1), pcNextStr - (pcCurStr + 1));
                    uszInfo[pcNextStr - (pcCurStr + 1)]= 0;
                }
            }
            
            return VOS_OK;
        }
    }
#endif
    return VOS_ERR;
}

/*******************************************************************************
*    Func Name: HDR_TranslateByCfg
* Date Created: 2009-03-26
*       Author: ZhengSenHuo(104483)
*  Description: 根据描述文件解析二进制文件并保存到文件中
*        Input: HDR_MSG_HEAD_S *pstHdrComHead:输入的消息头
*               FILE *fpHdrFile:体检消息文件句柄
*               FILE *fpCfgFile:描述文件句柄
*               ULONG ulScanId: 扫描ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
VOID HDR_TranslateByCfg(HDR_MSG_HEAD_S *pstHdrComHead, FILE *fpHdrFile, FILE *fpCfgFile, ULONG ulScanId)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    CHAR   szResualt[LEN_128];
    CHAR   szOutinfo[LEN_2048];
    CHAR  *pcOutInfo = szOutinfo;
    
    FILE  *fpWrite = NULL;
    HDR_TLVHEAD_S  *pstSubhead;

    LONG  ulOffLen;
    ULONG ulSubType;
    ULONG ulLoop;
    ULONG ulTypeLen = 1;
    ULONG ulOutOffSet = 0;
    ULONG ulMsgLen;
    ULONG ulTlvHeadLen = sizeof(HDR_TLVHEAD_S);

    /*
     * 统一对公共首部进行翻译
     */
    if (TYPE_HEALTH_CHECKUP == pstHdrComHead->ulMsgType)
    {
        (VOID)TCPIP_SNPRINTF0(szResualt, LEN_128, P1("tcpiphealthresualt%d.txt",ulScanId));
        ulOutOffSet += TCPIP_SNPRINTF0(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("\r\n%30s","Print health info:"));
        ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%lu","Scan ID:", ulScanId));
    }
    else
    {
        sprintf(szResualt,"tcpiplastwordresualt.txt");
        ulOutOffSet += TCPIP_SNPRINTF0(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("\r\n%30s","Print lastword info:"));
    }

    fpWrite = fopen(szResualt,"a");
    if (NULL == fpWrite)
    {
        printf("\r\nError occurs while openning write file.");
        return ;
    }

    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%lu", "ulMsgType:", pstHdrComHead->ulMsgType));
    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%lu", "ulSeq:", pstHdrComHead->ulSeq));
    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P7("\r\n%30s%02d/%02d/%02d %02d:%02d:%02d","TIME:",
                                     pstHdrComHead->stTime.usYear,
                                     pstHdrComHead->stTime.ucMonth,
                                     pstHdrComHead->stTime.ucDate,
                                     pstHdrComHead->stTime.ucHour,
                                     pstHdrComHead->stTime.ucMinute,
                                     pstHdrComHead->stTime.ucSecond));
    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%s", "ModuleName:", 
        (pstHdrComHead->usModID < g_ulHdrMaxModule) ? HDR_Trans_ModuleName[pstHdrComHead->usModID]:"null"));
    
    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%lu", "usMsgLen:", pstHdrComHead->usMsgLen));
    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("\r\n%30s%lu\r\n", "ulMsgNum:", pstHdrComHead->ulMsgNum));

    (VOID)printf("%s", pcOutInfo);

    if (fwrite(pcOutInfo,ulOutOffSet,1,fpWrite) != 1)
    {
        printf("\r\nError occurs while writing(head) file.\r\n");
    }
    pcOutInfo[0] = 0;

    ulMsgLen = pstHdrComHead->usMsgLen;

    ulOffLen = ulMsgLen - sizeof(HDR_MSG_HEAD_S);
    while (ulOffLen > 0)
    {
        CHAR  szLine[LEN_256] = {0};
        UCHAR ucDesc[LEN_256];
        /* Modify by shuxieliu00176784, at 2011-05-20. 修改原因: 消除Coverity告警 字符数组初始化0*/        
        CHAR  szSubTemp[LEN_256] = {0};
        UCHAR ucTlvMsg[LEN_1024] = {0}; 
        
        CHAR  *pcCurStr = NULL;
        CHAR  *pcNextStr;
        UCHAR *pucSubValue;
        
        ULONG ulLineLen = 0;
        ULONG ulFlag;
        ULONG ulSubOff;
        ULONG ulSubLen = 0;
        ULONG ulCfgLen = 0;

        /* 读取TLV头部 */
        if (1 != fread(ucTlvMsg, ulTlvHeadLen, 1, fpHdrFile))
        {
            printf("%s", "\r\n====Error occurs while reading tlv head.\r\n");
            break;
        }

        pstSubhead = (HDR_TLVHEAD_S *)ucTlvMsg;
        ulSubType = HDR_toHS(pstSubhead->usType);
        ulSubLen  = HDR_toHS(pstSubhead->usLen);

        /* 读取TLV内容 */
        if (1 != fread((ucTlvMsg + ulTlvHeadLen), (ulSubLen - ulTlvHeadLen), 1, fpHdrFile))
        {
            printf("%s", "\r\n====Error occurs while reading tlv content.\r\n");
            break;
        }
        
        pucSubValue = ucTlvMsg + ulTlvHeadLen;        

        ulOutOffSet = 0;

        /* 判断描述文件中是否存在此消息类型 */
        if( VOS_OK != HDR_GetBeginLineByType(fpCfgFile,ulSubType,&ulCfgLen,ucDesc))
        {
            printf("\r\n====Get sub type error./sub type:%u====\r\n",ulSubType);
            fseek(fpCfgFile, SEEK_SET, 0);
            ulOffLen = ulOffLen - ulSubLen;
            continue;
        }

        if ((ulSubLen - ulTlvHeadLen) != ulCfgLen)
        {
            printf("\r\n====Sub struct len error./sub type:%u,msg sub len:%u,cfg sub len:%u====\r\n",
                   ulSubType,(ulSubLen - ulTlvHeadLen),ulCfgLen);
            fseek(fpCfgFile, SEEK_SET, 0);
            ulOffLen = ulOffLen - ulSubLen;
            continue;
        }

        ulOutOffSet += TCPIP_SNPRINTF0(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("%30s%s\r\n","SubStructInfo:",ucDesc));
        ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P2("%30s%u\r\n","SubMsgType:",ulSubType));

        while (NULL != pucSubValue)
        {
            HDR_GetLineByFile(fpCfgFile,(UCHAR *)szLine,&ulLineLen);
            if ((0 == strlen(szLine)) || (0 == ulLineLen))
            {
                break;
            }
            
            /* Added by y00176567, at 2011-05-23. 修改原因: 消除Coverity告警 */
            /* if (NULL != (pcCurStr = strstr(szLine,"END;"))) */                
            pcCurStr = strstr(szLine,"END;");
            if (NULL != pcCurStr)
            {
                break;
            }

            if (strstr(szLine,"ULONG"))
            {
                ulFlag = HDR_TYPE_ULONG;
                ulSubOff = sizeof(ULONG);
            }
            else if (strstr(szLine,"USHORT"))
            {
                ulFlag = HDR_TYPE_USHORT;
                ulSubOff = sizeof(USHORT);
            }
            else if (strstr(szLine,"BOOL_T"))
            {
                ulFlag = HDR_TYPE_BOOL;
                ulSubOff = sizeof(USHORT);
            }
            else
            {
                ulFlag = HDR_TYPE_UCHAR;
                ulSubOff = sizeof(UCHAR);
            }

            pcCurStr = NULL;
            if (NULL != (pcCurStr = strstr(szLine,",")))
            {
                if (NULL != (pcNextStr = strstr(pcCurStr + 1,",")))
                {
                   (VOID)memcpy(szSubTemp,pcCurStr + 1,(pcNextStr - (pcCurStr + 1)));
                    szSubTemp[(pcNextStr - (pcCurStr + 1))] = 0;
                    ulTypeLen = atoi(szSubTemp);
                    
                    pcCurStr = pcNextStr+1;
                    if (NULL != (pcNextStr = strstr(pcCurStr,",")))
                    {
                        (VOID)TCPIP_Mem_Copy(szSubTemp, LEN_256, pcCurStr + 1,(pcNextStr - 1 - (pcCurStr + 1)));
                        szSubTemp[(pcNextStr - 1 - (pcCurStr + 1))] = 0;

                        /* 把大写字母转换成小写字母 */
                        (VOID)strlwr(szSubTemp);

                        pcCurStr = pcNextStr + 2;
                        if (NULL != (pcNextStr = strstr(pcCurStr,"\"")))
                        {
                            (VOID)TCPIP_Mem_Copy(ucDesc, LEN_256, pcCurStr,pcNextStr - pcCurStr);
                            ucDesc[pcNextStr - pcCurStr] = 0;
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%30s:",ucDesc));
                        }

                        /* 根据各种输出格式进行输出 */
                        if (NULL != (strstr(szSubTemp,"%d")))
                        {
                            for (ulLoop = 0;ulLoop < ulTypeLen;ulLoop++)
                            {
                                if (HDR_TYPE_ULONG == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%d ",HDR_toHL(*((ULONG*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_USHORT == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%d ",HDR_toHS(*((USHORT*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_BOOL == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%d ",*((USHORT*)(pucSubValue) + ulLoop)));
                                }
                                else
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%d ",*(pucSubValue + ulLoop)));
                                }
                            }
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%u")))
                        {
                            for (ulLoop = 0;ulLoop < ulTypeLen;ulLoop++)
                            {
                                if (HDR_TYPE_ULONG == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%u ",HDR_toHL(*((ULONG*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_USHORT == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%u ",HDR_toHS(*((USHORT*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_BOOL == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%u ",*((USHORT*)(pucSubValue) + ulLoop)));
                                }
                                else
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%u ",*(pucSubValue + ulLoop)));
                                }
                            }
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%lu")))
                        {
                            for (ulLoop = 0;ulLoop < ulTypeLen;ulLoop++)
                            {
                                if (HDR_TYPE_ULONG == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%lu ",HDR_toHL(*((ULONG*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_USHORT == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%lu ",HDR_toHS(*((USHORT*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_BOOL == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%lu ",*((USHORT*)(pucSubValue) + ulLoop)));
                                }
                                else
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%u ",*(pucSubValue + ulLoop)));
                                }
                            }
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%x")))
                        {
                            for (ulLoop = 0;ulLoop < ulTypeLen;ulLoop++)
                            {
                                if (HDR_TYPE_ULONG == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%#x ",HDR_toHL(*((ULONG*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_USHORT == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%#x ",HDR_toHS(*((USHORT*)(pucSubValue) + 
                                    ulLoop))));
                                }
                                else if (HDR_TYPE_BOOL == ulFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%#x ",*((USHORT*)(pucSubValue) + ulLoop)));
                                }
                                else
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%#x ",*(pucSubValue + ulLoop)));
                                }
                            }
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%c")))
                        {
                            UCHAR szTemp[LEN_128] = {0};
                            
                            for (ulLoop = 0;ulLoop < ulTypeLen;ulLoop++)
                            {
                                szTemp[ulLoop] = *(pucSubValue + ulLoop);
                            }
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%s",szTemp));
                            
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%s")))
                        {
                            UCHAR szTemp[LEN_128] = {0};

                            TCPIP_Mem_Copy(szTemp,LEN_128,pucSubValue,ulTypeLen);
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%s",szTemp));
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%mac")))
                        {
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P6("%02x-%02x-%02x-%02x-%02x-%02x",
                                                           *(pucSubValue),*(pucSubValue + 1),
                                                           *(pucSubValue + 2),*(pucSubValue + 3),
                                                           *(pucSubValue + 4),*(pucSubValue + 5)));
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%ip")))
                        {
                            CHAR szIp[LEN_128] = {0};
                            ULONG ulIp;
                            
                            ulIp = HDR_toHL(*((ULONG*)pucSubValue));
                            (VOID)Hdr_IpAddrToStr(ulIp,szIp);
                            
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%s",szIp));
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                        else if (NULL != (strstr(szSubTemp,"%ifname")))
                        {
                            UCHAR uszName[IF_MAX_INTERFACE_NAME_LEN + 1] = {0};
                            HDR_IFNAMEANDINDEX_S *pstNode = NULL;

                            TCPIP_Mem_Copy(uszName,IF_MAX_INTERFACE_NAME_LEN + 1,pucSubValue,IF_MAX_INTERFACE_NAME_LEN + 1);
                                
                            pstNode = (HDR_IFNAMEANDINDEX_S*)malloc(sizeof(HDR_IFNAMEANDINDEX_S));
                            if (pstNode != NULL)
                            {
                                TCPIP_Mem_Set(pstNode,0,sizeof(HDR_IFNAMEANDINDEX_S));
                                TCPIP_Mem_Copy(pstNode->szIfName,IF_MAX_INTERFACE_NAME_LEN+1,uszName,IF_MAX_INTERFACE_NAME_LEN + 1);
                                pstNode->ulIfIndex = *((ULONG*)(pucSubValue + IF_MAX_INTERFACE_NAME_LEN + 1));
                                if (NULL == g_pstNameAndIndex)
                                {
                                    g_pstNameAndIndex = pstNode;
                                }
                                else
                                {
                                    pstNode->pstNext = g_pstNameAndIndex->pstNext;
                                    g_pstNameAndIndex->pstNext = pstNode;
                                }
                            }
                            
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%s",uszName));
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                            
                        }
                        else if (NULL != (strstr(szSubTemp,"%index")))
                        {
                            ULONG ulIndex;
                            ULONG ulFindFlag = 0;
                            
                            HDR_IFNAMEANDINDEX_S *pstNode = NULL;

                            for (ulLoop = 0; ulLoop < ulTypeLen; ulLoop++)
                            {
                                ulIndex = *(((ULONG*)pucSubValue) + ulLoop);
                                pstNode = g_pstNameAndIndex;
                                ulFindFlag = 0;

                                /* 查找对应的接口名 */
                                while(pstNode != NULL)
                                {
                                    if (pstNode->ulIfIndex == ulIndex)
                                    {
                                        ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%s ",pstNode->szIfName));
                                        ulFindFlag = 1;
                                        break;
                                    }
                                    pstNode = pstNode->pstNext;
                                }

                                if (0 == ulFindFlag)
                                {
                                    ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P1("%#x ",HDR_toHL(ulIndex)));
                                }
                            }
                            
                            ulOutOffSet += TCPIP_SNPRINTF(pcOutInfo + ulOutOffSet, LEN_2048 - ulOutOffSet, P0("\r\n"));
                        }
                    }
                }
            }
            pucSubValue = pucSubValue + (ulSubOff * ulTypeLen);
            /* 默认为一个 */
            ulTypeLen= 1;
        }
        
        (VOID)printf("%s\r\n", pcOutInfo);

        if (fwrite(pcOutInfo,ulOutOffSet,1,fpWrite) != 1)
        {
            printf("\r\nError occurs while writing(head) file.\r\n");
        }

        pcOutInfo[0] = 0;

        fseek(fpCfgFile, SEEK_SET, 0);
        ulOffLen = ulOffLen - ulSubLen;
    }

    if (fpWrite)
    {
        fclose(fpWrite);
    }
#endif
    return;
}

/*******************************************************************************
*    Func Name: TCPIP_TranslatHdrByConfig
* Date Created: 2009-03-26
*       Author: ZhengSenHuo(104483)
*  Description: 解析二进制文件
*        Input: CHAR szHdrFile[LEN_128]: 二进制文件
*               CHAR szCfgFile[LEN_128]: 解析描述文件
*               ULONG ulScanId: 扫描ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   ZhengSenHuo(104483)  Create
*
*******************************************************************************/
ULONG TCPIP_TranslatHdrByConfig(CHAR szHdrFile[LEN_128],CHAR szCfgFile[LEN_128],ULONG ulScanId)
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    FILE *fpHdrFile = NULL;
    FILE *fpCfgFile = NULL;

    HDR_MSG_HEAD_S stHDRComHeader;

    fpHdrFile = fopen(szHdrFile,"rb");
    if (NULL == fpHdrFile)
    {
        printf("\r\nError occurs while openning hdr file.");
        return VOS_ERR;
    }

    fpCfgFile = fopen(szCfgFile,"r");
    if (NULL == fpCfgFile)
    {
        /**/
        printf("\r\nError occurs while openning cfg file.");
        fclose(fpHdrFile);
        return VOS_ERR;
    }

    while (!feof(fpHdrFile))
    {
        /* 读一个公共首部 */
        if (fread(&stHDRComHeader, sizeof(HDR_MSG_HEAD_S), 1, fpHdrFile) != 1)
        {
            continue;   /* 继续读下一条租期记录 */
        }

        stHDRComHeader.ulMsgType = HDR_toHL(stHDRComHeader.ulMsgType);
        stHDRComHeader.ulSeq     = HDR_toHL(stHDRComHeader.ulSeq);
        stHDRComHeader.usMsgLen  = HDR_toHS(stHDRComHeader.usMsgLen);
        stHDRComHeader.ulMsgNum  = HDR_toHL(stHDRComHeader.ulMsgNum);
        stHDRComHeader.stTime.usYear = HDR_toHS(stHDRComHeader.stTime.usYear);
        stHDRComHeader.usModID   = HDR_toHS(stHDRComHeader.usModID);

        /* 解析翻译 */
        HDR_TranslateByCfg(&stHDRComHeader, fpHdrFile, fpCfgFile, ulScanId);
        /* 移到描述文件头 */
        fseek(fpCfgFile, SEEK_SET, 0);
    }

    if (fpHdrFile)
    {
        fclose(fpHdrFile);
    }

    if (fpCfgFile)
    {
        fclose(fpCfgFile);
    }
#endif
    return VOS_OK;
}

/*******************************************************************************
*    Func Name: main
* Date Created: 2009-03-26
*       Author: ZhengSenHuo(104483)
*  Description: 程序入口
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   ZhengSenHuo(104483)  Create
*
*******************************************************************************/
/*VOID main(VOID)*/
int main(VOID) /* Modify by shuxieliu00176784, at 2011-05-20. 修改原因: 消除Coverity告警 */
{
#if((TCPIP_FOR_HERT == VRP_NO) && (TCPIP_FOR_BALONG == VRP_NO)&&(TCPIP_FOR_USP == VRP_NO))
    CHAR szHdrFile[LEN_128];
    CHAR szCfgFile[LEN_128];
    ULONG ulRet;
    ULONG ulScanId = 0;
    ULONG ulByteOrder = 0;
    FILE *fp = NULL;
    HDR_IFNAMEANDINDEX_S *pstCurNode = g_pstNameAndIndex;
    HDR_IFNAMEANDINDEX_S *pstNextNode = NULL;

    /* 输入二进制文件 */
    printf("please input hdr file name:\r\n");
    TCPIP_Scanf("%s",szHdrFile);
    while (1)
    {
        fp = fopen(szHdrFile,"rb");
        if (NULL != fp)
        {
            fclose(fp);
            break;
        }
        
        printf("file is not exist,please repeat input hdr file name:\r\n");
        TCPIP_Scanf("%s",szHdrFile);
    }

    /* 输入描述文件 */
    printf("please input cfg file name:\r\n");
    TCPIP_Scanf("%s",szCfgFile);

    while (1)
    {
        fp = fopen(szCfgFile,"r");
        if (NULL != fp)
        {
            fclose(fp);
            break;
        }
        
        printf("file is not exist,please repeat input cfg file name:\r\n");
        TCPIP_Scanf("%s",szCfgFile);
    }
    
    /* 输入扫描ID */
    printf("please input scan id:\r\n");
    TCPIP_Scanf("%d",&ulScanId);

    /* 输入大小头序 */
    printf("please input byte order(0:big,1:little):\r\n");
    TCPIP_Scanf("%d",&ulByteOrder);

    while (1)
    {
        if ((HDR_LITTLE_ENDIAN == ulByteOrder) || (HDR_BIG_ENDIAN == ulByteOrder))
        {
            break;
        }
        
        printf("byte order error,please repeat input byte order(0:big,1:little):\r\n");
        TCPIP_Scanf("%d",&ulByteOrder);
    }

    g_HDRByteOrder = ulByteOrder;

    ulRet = TCPIP_TranslatHdrByConfig(szHdrFile,szCfgFile,ulScanId);
    if (ulRet!= 0)
    {
        printf("Translat hdr by config failed.ret = %d\r\n",ulRet);
    }
    
    while(pstCurNode != NULL)
    {
        pstNextNode = pstCurNode->pstNext;
        free(pstCurNode);
        pstCurNode = pstNextNode;
    }
    
    (VOID)getchar();
    (VOID)getchar();
#endif
    /* Add by shuxieliu00176784, at 2011-05-20. 修改原因: 消除Coverity告警 */
    return VOS_OK;
}


#ifdef __cplusplus
}
#endif

