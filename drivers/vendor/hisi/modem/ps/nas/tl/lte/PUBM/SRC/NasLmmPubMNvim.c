/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
    File name   : NasLmmPubMNvim.c
    Description :
    History     :
      1.  hanlufeng 41410 2008-10-25 Draft Enact
      2.  zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMNvim.c修改为
                                           NasLmmPubMNvim.c
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "UsimPsInterface.h"
#include    "SysNvId.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMNVIM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMNVIM_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

VOS_UINT32                              g_aucNvimBuff[NAS_NVIM_MAX_BUFFER];

static NAS_LMM_NV_ACT_STRU               g_astNvDataMap[] =
{
    /*NVIM数据*/
    {EN_NV_ID_UE_NET_CAPABILITY,      NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_IMSI,                   NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_EPS_LOC,                NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_SEC_CONTEXT,            NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_UE_CENTER,              NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {en_NV_Item_UMTS_CODEC_TYPE,      NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {en_NV_Item_MED_CODEC_TYPE,       NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_UE_VOICE_DOMAIN,        NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_NAS_RELEASE,            NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_CONFIG_NWCAUSE,         NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_DAM_CONFIG_PARA,        NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_LNAS_COMM_CONFIG_PARA,  NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},

    {EN_NV_ID_LNAS_SWITCH_PARA,       NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
};

VOS_UINT32 g_ulNvDataMapNum = sizeof(g_astNvDataMap)/sizeof(NAS_LMM_NV_ACT_STRU);

/* 将从USIM读取的文件ID */
VOS_UINT32 g_aulMmUsimEf[] = {  0x6F38, 0x6FAD, 0x6F7B, 0x6F31, 0x6F7E,
                                0x6F73, 0x6F07, 0x6F08, 0x6F09, 0x6FE4,
                                0x6F78};
VOS_UINT32 g_ulUsimSecuFileLen;

VOS_UINT8  g_aucUsimSecuContext[NAS_NVIM_SECU_CONTEXT_MAX_LEN] = {0}; /* 保存上次写卡的安全上下文码流 */

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : NAS_LMM_SndUsimReadFileReq()
 Description    : 给USIM发送读取文件请求
 Input          : ulAppType         应用类型
                  ucRecordNum
                  ulOpId
                  stGetFilePath     文件路径
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
          1.zhaochen 00308719  2015-02-10   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
)
{
    USIMM_READFILE_REQ_STRU     *pstUsimReadFileReq;

    /*分配空间并检验分配是否成功*/
    pstUsimReadFileReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(USIMM_READFILE_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstUsimReadFileReq)
    {
        /*打印异常信息*/
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_SndUsimReadFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndUsimReadFileReq_ENUM
,LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_LMM_MEM_SET_S(  pstUsimReadFileReq,
                        sizeof(USIMM_READFILE_REQ_STRU),
                        0,
                        sizeof(USIMM_READFILE_REQ_STRU));

    /*填写消息头*/
    /*消息结构体中的SendPara用来存储OpId*/
    NAS_EMM_USIM_MSG_HEAD(pstUsimReadFileReq, USIMM_READFILE_REQ, ulAppType, ulOpId);

    /*填写消息内容*/
    pstUsimReadFileReq->ucRecordNum = ucRecordNum;
    pstUsimReadFileReq->bNeedReadCache = VOS_TRUE;
    NAS_LMM_MEM_CPY_S(  &(pstUsimReadFileReq->stFilePath),
                        sizeof(USIMM_FILEPATH_INFO_STRU),
                        pstGetFilePath,
                        sizeof(USIMM_FILEPATH_INFO_STRU));

    /*调用消息发送函数 */
    NAS_LMM_SEND_MSG(pstUsimReadFileReq);

}

/*****************************************************************************
 Function Name  : NAS_LMM_SndUsimReadFileReq()
 Description    : 给USIM发送写入文件请求
 Input          : ulAppType         应用类型
                  ucRecordNum
                  ulOpId
                  stGetFilePath     文件路径
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
          1.zhaochen 00308719  2015-02-15   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndUsimWriteFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath,
    VOS_UINT16                      usDataLen,
    VOS_UINT8                      *aucContent
)
{
    USIMM_UPDATEFILE_REQ_STRU       *pstUsimUpdateFileReq;
    VOS_UINT16                       usUsimUpdateFileReqLen;

    /*分配空间并检验分配是否成功*/
    usUsimUpdateFileReqLen = sizeof(USIMM_UPDATEFILE_REQ_STRU) + usDataLen - 3;
    pstUsimUpdateFileReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(usUsimUpdateFileReqLen);

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstUsimUpdateFileReq)
    {
        /*打印异常信息*/
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_SndUsimWriteFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndUsimWriteFileReq_ENUM
,LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_LMM_MEM_SET_S(  pstUsimUpdateFileReq,
                        usUsimUpdateFileReqLen,
                        0,
                        usUsimUpdateFileReqLen);

    /*填写消息头*/
    /*消息结构体中的SendPara用来存储OpId*/
    NAS_EMM_USIM_MSG_HEAD(pstUsimUpdateFileReq, USIMM_UPDATEFILE_REQ, ulAppType, ulOpId);

    /*填写消息内容*/
    pstUsimUpdateFileReq->ucRecordNum = ucRecordNum;
    pstUsimUpdateFileReq->usDataLen = usDataLen;
    NAS_LMM_MEM_CPY_S(  &(pstUsimUpdateFileReq->stFilePath),
                        sizeof(USIMM_FILEPATH_INFO_STRU),
                        pstGetFilePath,
                        sizeof(USIMM_FILEPATH_INFO_STRU));
    NAS_LMM_MEM_CPY_S(  pstUsimUpdateFileReq->aucContent,
                        usDataLen,
                        aucContent,
                        usDataLen);

    /*调用消息发送函数 */
    NAS_LMM_SEND_MSG(pstUsimUpdateFileReq);

}
/* 2015-03-15: 注意本次是此文件大面积修改 */
/*****************************************************************************
 Function Name  : NAS_LMM_NvimWrite
 Discription    : 其他模块调用本函数写一个指定的NV_Item
 Input          : ulNVItemType: NV_Item类型
                  *pData：      NV的数据指针
                  usDataLen：   要写入数据长度
 Output         : None
 Return         : 0：数据成功写入，函数正常返回
                  2：要写的NV类型超过最大值出错
                  4：系统异常，数据无法写入
 History:
     1.sunbing   49683      2010-7-22  modify
     2.sunjitan 00193151    2015-03-15 Modify
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_NvimWrite
(
    NAS_LMM_ITEM_TYPE_ENUM_UINT32       ulNVItemType,
    VOS_VOID                           *pData,
    VOS_UINT16                          usDataLen
)
{
    VOS_UINT32                          ulRslt = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    VOS_UINT32                          i;
    NAS_LMM_NV_ACTION_FUN               pActFun = NAS_LMM_NULL_PTR;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)
        ||(usDataLen == VOS_NULL)
        ||(ulNVItemType > EN_NV_ID_PS_END))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:input para ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData       = pData;
    stNvCtrlTbl.pNvData     = g_aucNvimBuff;
    stNvCtrlTbl.usDataLen   = usDataLen;
    stNvCtrlTbl.usNvDataLen = 0;

    /* 在g_astNvDataMap中查找对应的NV TYPE*/
    for(i = 0; i < g_ulNvDataMapNum; i++)
    {
        /* 若NV类型相同,则找到了,返回当前的NV动作函数，退出循环 */
        if(ulNVItemType == g_astNvDataMap[i].ulEventType)
        {
            pActFun = g_astNvDataMap[i].pfEncodeActionFun;
            break;
        }
    }

    if (NAS_LMM_NULL_PTR == pActFun)
    {
        /* 如果找不到处理函数，表示当前没有该处理函数 */
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:Action functin is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NVIM_FAIL;
    }

    ulRslt = (*pActFun) (&stNvCtrlTbl);

    if ( NAS_LMM_NVIM_WRITTEN_UNNEEDED == ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_NvimWrite: Don't need to write usim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_NVIM_WRITTEN_UNNEEDED;
    }

    if(ulRslt != NAS_LMM_NVIM_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:Encode is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL3);

        return NAS_LMM_NVIM_FAIL;
    }

    /*其他情况向NV中写信息*/
    /*lint -e718*/
    /*lint -e516*/
    /*lint -e732*/
    ulRslt = LPs_NvimItem_Write(ulNVItemType, stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);
    /*lint +e732*/
    /*lint +e516*/
    /*lint +e718*/
    return ulRslt;

}

/*****************************************************************************
 Function Name  : NAS_LMM_NvimRead
 Discription    : 其他模块调用本函数读一个指定的NV_Item
 Input          : ulNVItemType: NV_Item类型
                  *pData ：     数据缓存指针
                  *pusDataLen： 返回数据长度
 Output         : pusDataLen ： 返回数据长度
 Return         : 0：数据成功读取，函数正常返回
                  1：未找到要读取的NV项
                  3：传入的缓存不够出错
                  4：系统异常，读取出错
 History:
      1.sunbing   49683      2010-7-22  modify
      2.zhaochen  00308719   2015-2-10  modify for USIM interface
      3.sunjitan  00193151   2015-03-15 Modify
*****************************************************************************/
NAS_LMM_USIM_NV_RESULT  NAS_LMM_NvimRead
(
    NAS_LMM_ITEM_TYPE_ENUM_UINT32       ulNVItemType,
    VOS_VOID                           *pData,
    const VOS_UINT16                   *pusDataLen )
{
    VOS_UINT32                          ulRslt  = NAS_LMM_NVIM_FAIL;
    NAS_LMM_NV_ACTION_FUN               pActFun = NAS_LMM_NULL_PTR;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    VOS_UINT32                          i;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)
        ||(NAS_NVIM_NULL_PTR == pusDataLen)
        ||(ulNVItemType > EN_NV_ID_PS_END))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead :Input Para is error");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    NAS_LMM_MEM_SET_S(g_aucNvimBuff, sizeof(g_aucNvimBuff), 0, sizeof(g_aucNvimBuff));

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData        = pData;
    stNvCtrlTbl.pNvData      = g_aucNvimBuff;
    stNvCtrlTbl.usDataLen    = *pusDataLen;
    stNvCtrlTbl.usNvDataLen  = *pusDataLen;

    /* 从NV中读取信息 */
    /*lint -e718*/
    /*lint -e516*/
    /*lint -e732*/
    ulRslt = LPs_NvimItem_Read(ulNVItemType, stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);
    /*lint +e732*/
    /*lint +e516*/
    /*lint +e718*/
    if(ulRslt != EN_NV_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead:PS_NVIM_Read is fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_FAIL);
        return NAS_LMM_NVIM_FAIL;
    }

    /* 在g_astNvDataMap中查找对应的NV TYPE, 译码NV*/
    for(i = 0; i < g_ulNvDataMapNum; i++)
    {
        /* 若NV类型相同,则找到了,返回当前的NV动作函数，退出循环 */
        if(ulNVItemType == g_astNvDataMap[i].ulEventType)
        {
           pActFun = g_astNvDataMap[i].pfDecodeActionFun;
           break;
        }
    }

    if (NAS_LMM_NULL_PTR != pActFun)
    {
        ulRslt = (*pActFun) (&stNvCtrlTbl);
        if(NAS_LMM_NVIM_OK == ulRslt)
        {
            return NAS_LMM_NVIM_OK;
        }
        else
        {
            return NAS_LMM_NVIM_FAIL;
        }
    }
    else /* 如果找不到处理函数，表示当前没有该处理函数 */
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead:Action functin is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_ERROR);
        return NAS_LMM_NVIM_FAIL;
    }

}


/*****************************************************************************
 Function Name  : NAS_LMM_UsimFileWrite
 Discription    : 其他模块调用本函数写一个指定的USIM文件
 Input          : USIMM_DEF_FILEID_ENUM_UINT32: USIM文件ID
 Output         : VOS_VOID
 Return         : VOS_VOID
 History:
      1.sunjitan 00193151     2015-03-15   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UsimFileWrite
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId,
    VOS_VOID                           *pData,
    VOS_UINT16                          usDataLen
)
{
    VOS_UINT32                          ulRslt      = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;

    /*ucRecordNum默认为1，NAS目前涉及的文件是线形文件，且只有一个记录*/
    VOS_UINT8                           ucRecordNum = 0x01;
    VOS_CHAR                           *cPathStr;
    VOS_UINT8                          *paucContent;
    USIMM_FILEPATH_INFO_STRU            stSetFilePath;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)||(usDataLen == VOS_NULL))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileWrite:input para ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  &stSetFilePath,
                        sizeof(USIMM_FILEPATH_INFO_STRU),
                        0,
                        sizeof(USIMM_FILEPATH_INFO_STRU));

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData       = pData;
    stNvCtrlTbl.pNvData     = g_aucNvimBuff;

    /* 内部数据长度不使用，写USIM使用的实际长度是Encode后得到的usNvDataLen */
    stNvCtrlTbl.usDataLen   = usDataLen;
    stNvCtrlTbl.usNvDataLen = 0;

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileWrite: UsimFileId = ", ulUsimFileId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL1,ulUsimFileId);

    switch(ulUsimFileId)
    {
        case USIMM_USIM_EFEPSLOCI_ID :

            ulRslt = NAS_LMM_EncodeSimPsLoc(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSNSC_ID  :

            ulRslt = NAS_LMM_EncodeSimSecContext(&stNvCtrlTbl);
            break;
        default:
            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_UsimFileWrite: UsimFileId err ID = ", ulUsimFileId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL2,ulUsimFileId);
            return;
    }

    if (NAS_LMM_NVIM_WRITTEN_UNNEEDED == ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_UsimFileWrite: code Don't need to write usim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }

    if(ulRslt != NAS_LMM_NVIM_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileWrite:Encode is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL4);
        return;
    }

    /*将FileID转换为文件路径*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(ulUsimFileId, &cPathStr))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL5);
        return;
    }
    stSetFilePath.ulPathLen = strlen(cPathStr);
    NAS_LMM_MEM_CPY_S(stSetFilePath.acPath, USIMM_PATHSTR_MAX_LEN, cPathStr, stSetFilePath.ulPathLen);

    paucContent = stNvCtrlTbl.pNvData;

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileWrite: usNvDataLen = ", stNvCtrlTbl.usNvDataLen);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileWrite_ENUM
                                ,LNAS_FUNCTION_LABEL6,stNvCtrlTbl.usNvDataLen);

    NAS_LMM_SndUsimWriteFileReq(USIMM_GUTL_APP, ucRecordNum, 0, &stSetFilePath, stNvCtrlTbl.usNvDataLen, paucContent);

    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(), (VOS_UINT8*)stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);

    return;

}


/*****************************************************************************
 Function Name  : NAS_LMM_UsimFileRead
 Discription    : 其他模块调用本函数读一个指定的USIM文件
 Input          : USIMM_DEF_FILEID_ENUM_UINT32: USIM文件ID
 Output         : VOS_VOID
 Return         : VOS_VOID
 History:
      1.sunjitan 00193151     2015-03-15   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UsimFileRead
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId
)
{
    USIMM_FILEPATH_INFO_STRU            stGetFilePath;
    VOS_CHAR                           *cPathStr;

    /*ucRecordNum默认为1，NAS目前涉及的文件是线形文件，且只有一个记录*/
    VOS_UINT8                           ucRecordNum = 0x01;

    NAS_LMM_MEM_SET_S(  &stGetFilePath,
                        sizeof(USIMM_FILEPATH_INFO_STRU),
                        0,
                        sizeof(USIMM_FILEPATH_INFO_STRU));

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileRead: UsimFileId = ", ulUsimFileId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL1,ulUsimFileId);

    switch(ulUsimFileId)
    {
        case USIMM_USIM_EFAD_ID      :
        case USIMM_USIM_EFACC_ID     :
        case USIMM_USIM_EFEPSLOCI_ID :
        case USIMM_USIM_EFEPSNSC_ID  :
            break;
        default:
            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_UsimFileRead: UsimFileId err ID = ", ulUsimFileId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL2,ulUsimFileId);
            return;
    }

    /*将FileID转换为文件路径*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(ulUsimFileId, &cPathStr))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileRead: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }

    stGetFilePath.ulPathLen = strlen(cPathStr);
    NAS_LMM_MEM_CPY_S(stGetFilePath.acPath, USIMM_PATHSTR_MAX_LEN, cPathStr, stGetFilePath.ulPathLen);

    /*发送读USIM文件的消息*/
    NAS_LMM_SndUsimReadFileReq(USIMM_GUTL_APP, ucRecordNum, 0, &stGetFilePath);

    NAS_EMM_GET_SEND_COUNTER()++;

    return;
}


VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf( MsgBlock  * pMsg)
{
    USIMM_READFILE_CNF_STRU          *pstUsimCnf = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRst;

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: g_ulSendMsgCounter = ,NAS_EMM_GET_USIM_FILE_TYPE=",
                                        NAS_EMM_GET_SEND_COUNTER(),
                                        NAS_EMM_GET_USIM_FILE_TYPE());
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL1,
                                        NAS_EMM_GET_SEND_COUNTER(),
                                        NAS_EMM_GET_USIM_FILE_TYPE());

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_READING_USIM))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: STATE ERR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /*收到后计数*//*对全局变量进行保护，以防出现负数*/
    if (NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER())
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: Receive USIM cnf when Counter is 0!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL3);
        return NAS_LMM_MSG_DISCARD;
    }
    else
    {
        NAS_EMM_GET_SEND_COUNTER() --;
    }

    pstUsimCnf = (USIMM_READFILE_CNF_STRU*)pMsg;


    NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf:===>",pstUsimCnf->stCmdResult.ulResult);
    TLPS_PRINT2LAYER_WARNING1(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL4,pstUsimCnf->stCmdResult.ulResult);

    /*读卡失败*/
    if (VOS_OK != pstUsimCnf->stCmdResult.ulResult)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: Read file err !");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL5);


        if( NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER() )
        {/*可选最后一个文件读取失败，进行读NV、转状态的动作*/

            NAS_LMM_DoAfterReadOptFileOver();
        }

        return NAS_LMM_MSG_HANDLED;
    }

    /* 对文件进行处理 */
    ulRst = NAS_LMM_ProcessHardUsimCnf(pstUsimCnf);
    if(NAS_LMM_NVIM_OK != ulRst)
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf : Decode USIM MSG err: ",
                                ulRst);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL6,ulRst);
    }

    if( NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER())
    {   /* 读完必读或可选文件 */

        NAS_LMM_DoAfterReadOptFileOver();
    }

    /* 没有读完，则继续等待读卡响应消息 */

    return NAS_LMM_MSG_HANDLED;
}




VOS_VOID  NAS_LMM_DoAfterReadOptFileOver( VOS_VOID )
{
    NAS_LMM_FSM_STATE_STRU               EmmState;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeMode;

    NAS_LMM_UEID_STRU                    *pstUeId;


    /* 停止TI_NAS_LMM_TIMER_WAIT_USIM_CNF */
    NAS_LMM_StopStateTimer(TI_NAS_LMM_TIMER_WAIT_USIM_CNF);
    /*如果读取到的GUTI无效但是安全上下文有效，则删除本地和NV中的上下文*/
    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    if((NAS_EMM_BIT_NO_SLCT == pstUeId->bitOpGuti)
        &&(EMM_CUR_SECU_NOT_EXIST!= NAS_LMM_GetSecuCurFsmCS()))
    {
        NAS_EMM_ClearCurSecuCntxt();
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);
    }

    /* Read NV Files*/
    NAS_LMM_ProcessNvData();

    /* 状态转成读必选文件状态 */
    /* V7不再区分必读可选 */
    /*NAS_EMM_GET_USIM_FILE_TYPE() = NAS_LMM_USIM_MANDATORY_FILE;*/
    ulLteUeMode = NAS_LMM_ComputeLteUeMode( NAS_EMM_GetMsMode(),
                                          NAS_LMM_GetEmmInfoUeCenter());
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeMode);
    /* 启动TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER);

    /* 转状态 */
    EmmState.enFsmId             = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState         = EMM_MS_NULL;
    EmmState.enSubState          = EMM_SS_NULL_WAIT_MMC_START_CNF;
    EmmState.enStaTId            = TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /* 向MMC发送MMC_EMM_START_REQ(正常启动)消息 */
    (VOS_VOID)NAS_EMM_PLMN_SendMmcStartReq(EMMC_EMM_START_REQ_CAUSE_NORMAL_START);

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ProcessNvData
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-1-14  Draft Enact
    2.    yangfan 00159566     2010-5-11  删除Rplmn

*****************************************************************************/
VOS_VOID  NAS_LMM_ProcessNvData( VOS_VOID )
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_ProcessNvData is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcessNvData_ENUM
,LNAS_ENTRY);

    /*初始化EMM全局变量ReadNV*/
    NAS_EMM_ReadEmmNvim();

    return;
}


VOS_UINT32  NAS_LMM_ProcessHardUsimCnf(USIMM_READFILE_CNF_STRU* pstUsimFileCnf)
{
    VOS_UINT32                          ulRslt      = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID = 0;

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pNvData     = pstUsimFileCnf->aucEf;
    stNvCtrlTbl.usNvDataLen = pstUsimFileCnf->usEfLen;

    /* 调用USIM提供的接口，将文件路径转换为FileID */
    if(VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstUsimFileCnf->stFilePath.ulPathLen,
                                        pstUsimFileCnf->stFilePath.acPath, &enDefFileID))
    {
        /* 如果转换失败，表示没有对应的FileID */
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ProcessHardUsimCnf: USIMM_ChangePathToDefFileID err");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL1);
        return VOS_ERR;
    }

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_ProcessHardUsimCnf:pstUsimCnf->usEfId=,pstUsimCnf->ucEfLen",
                                        enDefFileID,
                                        pstUsimFileCnf->usEfLen);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL2,
                                        enDefFileID,
                                        pstUsimFileCnf->usEfLen);
    switch(enDefFileID)
    {
        case USIMM_USIM_EFIMSI_ID    :

            ulRslt = NAS_LMM_DecodeSimImsi(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFAD_ID      :

            ulRslt = NAS_LMM_DecodeSimMncLen(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFACC_ID     :

            ulRslt = NAS_LMM_DecodeNvACC(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSLOCI_ID :

            ulRslt = NAS_LMM_DecodeSimPsLoc(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSNSC_ID  :

            ulRslt = NAS_LMM_DecodeSimSecContext(&stNvCtrlTbl);
            break;
        default:

            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_ProcessHardUsimCnf: UsimFileId err ID = ", enDefFileID);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL3,enDefFileID);
            return NAS_LMM_NVIM_FAIL;
    }

    if(NAS_LMM_NVIM_OK != ulRslt)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_ProcessHardUsimCnf: UsimFileId decode err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL4);
    }

    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadUsimFileImsi
 Description     : 读IMSI
 Input           : None
 Output          : None
 Return          : NAS_LMM_USIM_READ_RST_ENUM_UINT32
 History         :
    1. HanLufeng 41410      2011-02-23     Draft Enact
    2. sunjitan 00193151    2015-03-15    Modify
*****************************************************************************/
NAS_LMM_USIM_READ_RST_ENUM_UINT32  NAS_LMM_ReadUsimFileImsi(VOS_VOID)
{
    VOS_UINT32                          ulRst;
    USIMM_READFILE_CNF_STRU            *pstUsimCnfMsg;
    VOS_CHAR                           *pcPathStr;

    pstUsimCnfMsg = (USIMM_READFILE_CNF_STRU *)(g_aucNvimBuff);

    /* 6F07    MMC_READ_IMSI_FILE_ID 读USIM卡提供的接口函数 */
    ulRst = NAS_EMM_GetCardIMSI((VOS_UINT8 *)(pstUsimCnfMsg->aucEf));
    if(USIMM_API_SUCCESS != ulRst)
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_ReadMmcUsimFile : read IMSI err: ",
                                  ulRst);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL1,ulRst);
        return  NAS_LMM_USIM_READ_HARD_IMSI_ERR;
    }
    else
    {
        /* 打印从USIM读出的原始码流 */
        NAS_LMM_PUBM_LOG_NORM("\n");
        NAS_LMM_PUBM_LOG_NORM("====== USIMM_GetCardIMSI: IMSI:  ======");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                         pstUsimCnfMsg->aucEf,
                                         NAS_LMM_NVIM_IMSI_FILE_LEN);
        NAS_LMM_PUBM_LOG_NORM("\n");

        /*将FileID转换为文件路径*/
        if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_USIM_EFIMSI_ID, &pcPathStr))
        {
            NAS_LMM_NVIM_LOG_ERR("NAS_LMM_ReadMmcUsimFile: ChangeDefFileToPath err.");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL3);
            return NAS_LMM_USIM_READ_HARD_IMSI_ERR;
        }

        pstUsimCnfMsg->stFilePath.ulPathLen = strlen(pcPathStr);
        NAS_LMM_MEM_CPY_S(  pstUsimCnfMsg->stFilePath.acPath,
                            USIMM_PATHSTR_MAX_LEN,
                            pcPathStr,
                            pstUsimCnfMsg->stFilePath.ulPathLen);

        /* 准备一下 NAS_LMM_ProcessHardUsimCnf 的入口参数 */
        pstUsimCnfMsg->usEfLen     = NAS_LMM_NVIM_IMSI_FILE_LEN;
        pstUsimCnfMsg->ucRecordNum = 0;
        pstUsimCnfMsg->ucTotalNum  = 0;

        /* 解码 */
        ulRst = NAS_LMM_ProcessHardUsimCnf(pstUsimCnfMsg);
        if(NAS_LMM_NVIM_OK != ulRst)
        {
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_ReadMmcUsimFile : Decode IMSI err: ", ulRst);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL4,ulRst);
            return  NAS_LMM_USIM_READ_HARD_IMSI_ERR;
        }
    }

    return  NAS_LMM_USIM_READ_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ReadLteUsimFile
 Description     : 读取LTE自己的个文件:
                    6F78    USIMM_USIM_EFACC_ID
                    6FE3    USIMM_USIM_EFEPSLOCI_ID
                    6FE4    USIMM_USIM_EFEPSNSC_ID
                    安全上下文文件和GUTI应该是同时存在的，有GUTI就应该有安全，有
                    安全，就应该有GUTI;
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.HanLufeng 41410      2011-2-23  Draft Enact
    2.sunjitan 00193151    2015-03-15 Modify
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadLteUsimFile(VOS_VOID)
{
    /*6F78 */
    NAS_EMM_ReadAccClassMask();

    /*6FE3 安全上下文和 PS_LOC*/
    NAS_LMM_ReadUsimEmmInfoFile();
    /*6FAD MNC长度*/
    NAS_LMM_ReadSimMncLen();
    return;
}

/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif


