/************************************************************************
  Copyright    : 2013-2015, Huawei Tech. Co., Ltd.
  File name    : usimmt1dl.c
  Author       : jinni 00168360
  Version      : V900R001
  Date         : 2013-10-14
  Description  : 该C文件给出了T=1 DL层实现
  Function List:
  History      :
 ************************************************************************/
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmbase.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_T1_DL_C
/*lint +e767*/

/* T=1 控制上下文  */
USIMM_T1_CTRL_CTX_STRU          g_stUsimmT1CtrlCtx;

/* T=1 数据发送信息结构  */
USIMM_T1_SEND_DATA_STRU         g_stT1SendDataInfo;

/* T=1 数据接收信息结构  */
USIMM_T1_RCV_DATA_STRU          g_stT1RcvDataInfo;

/* T=1 统计信息结构  */
USIMM_T1_STATISTIC_STRU         g_stT1StatisticInfo;

/* T=1 向底软发送数据时所使用的缓存，预留一个字节做保护 */
VOS_UINT8                       g_aucT1SndBuffer[USIMM_T1_BLOCK_MAX_SIZE + 1];

/* CRC-16-CCITT标准CRC表  */
static const VOS_UINT16 g_stT1Crc16CcittTbl[] =
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

/*****************************************************************************
函 数 名  : USIMM_T1CalCCITTCrc16
功能描述  : 计算CRC-16-CCITT标准CRC值
输入参数  : pucData:CRC校验数据
            ulLen  :CRC校验数据长度
输出参数  : 无
返 回 值  : usCrc16
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月22日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_UINT16 USIMM_T1CalCCITTCrc16(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT16      usCrc16;
    VOS_UINT16      usLoop;

    /* 初始化SEED */
    usCrc16 = VOS_NULL_WORD;

    /* 查表计算CRC16 */
    for (usLoop = 0; usLoop < ulLen; usLoop++)
    {
        usCrc16 = (usCrc16 >> 8) ^ g_stT1Crc16CcittTbl[(usCrc16 ^ pucData[usLoop]) & VOS_NULL_BYTE];
    }

    usCrc16 ^= VOS_NULL_WORD;

    return usCrc16;
}

/*****************************************************************************
函 数 名  : USIMM_T1CalLrc
功能描述  : 计算LRC
输入参数  : pucData:LRC校验数据
            ulLen  :LRC校验数据长度
输出参数  : 无
返 回 值  : ucLrc
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月22日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_UINT8 USIMM_T1CalLrc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT8       ucLrc;
    VOS_UINT16      usLoop;

    ucLrc = 0x00;

    /* 逐字节异或 */
    for (usLoop = 0; usLoop < ulLen; usLoop++)
    {
        ucLrc ^= pucData[usLoop];
    }

    return ucLrc;
}

/*****************************************************************************
函 数 名  :USIMM_T1StatisticSendSBlockSucc
功能描述  :发送成功的S block信息统计
输入参数  :enSBlkType ---发送的S block类型
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
  1.日    期   : 2013年10月18日
    作    者   : L00256032
    修改内容   : V9R1 T=1项目修改
*****************************************************************************/
VOS_VOID USIMM_T1StatisticSendSBlockSucc(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType
)
{
    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_RESYNCH_REQ:
            g_stT1StatisticInfo.ulSndSBlkResynchReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_REQ:
            g_stT1StatisticInfo.ulSndSBlkIFSReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_RES:
            g_stT1StatisticInfo.ulSndSBlkIFSRspSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_REQ:
            g_stT1StatisticInfo.ulSndSBlkAbortReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_RES:
            g_stT1StatisticInfo.ulSndSBlkAbortRspSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_WTX_RES:
            g_stT1StatisticInfo.ulSndSBlkWTXRspSuccCnt++;
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_T1StatisticSendSBlockFail
功能描述  :发送失败的S block信息统计
输入参数  :enSBlkType ---发送的S block类型
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
  1.日    期   : 2013年10月18日
    作    者   : L00256032
    修改内容   : V9R1 T=1项目修改
*****************************************************************************/
VOS_VOID USIMM_T1StatisticSendSBlockFail(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType
)
{
    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_RESYNCH_REQ:
            g_stT1StatisticInfo.ulSndSBlkResynchReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_REQ:
            g_stT1StatisticInfo.ulSndSBlkIFSReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_RES:
            g_stT1StatisticInfo.ulSndSBlkIFSRspFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_REQ:
            g_stT1StatisticInfo.ulSndSBlkAbortReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_RES:
            g_stT1StatisticInfo.ulSndSBlkAbortRspFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_WTX_RES:
            g_stT1StatisticInfo.ulSndSBlkWTXRspFailCnt++;
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_T1ShowCtrlAndStatisticInfo
功能描述  :打印T1控制上下文及可维可测信息
输入参数  :VOS_VOID
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
  1.日    期   : 2013年10月18日
    作    者   : L00256032
    修改内容   : V9R1 T=1项目修改
*****************************************************************************/
VOS_VOID USIMM_T1ShowCtrlAndStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\n********************T1 控制上下文信息************************\n");
    vos_printf("g_stUsimmT1CtrlCtx.ulIFSC                   %d\n", g_stUsimmT1CtrlCtx.ulIFSC);
    vos_printf("g_stUsimmT1CtrlCtx.ulIFSD                   %d\n", g_stUsimmT1CtrlCtx.ulIFSD);
    vos_printf("g_stUsimmT1CtrlCtx.enErrDetectMode          %d\n", g_stUsimmT1CtrlCtx.enErrDetectMode);
    vos_printf("g_stUsimmT1CtrlCtx.ulBWTTimes               %d\n", g_stUsimmT1CtrlCtx.ulBWTTimes);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType    %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.ucLen         %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.ucLen);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.ucData        %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.ucData);
    vos_printf("g_stUsimmT1CtrlCtx.enT1HandleState          %d\n", g_stUsimmT1CtrlCtx.enT1HandleState);
    vos_printf("g_stUsimmT1CtrlCtx.enT1ProcState            %d\n", g_stUsimmT1CtrlCtx.enT1ProcState);
    vos_printf("g_stUsimmT1CtrlCtx.ulUESeqNum               %d\n", g_stUsimmT1CtrlCtx.ulUESeqNum);
    vos_printf("g_stUsimmT1CtrlCtx.ulUICCSeqNum             %d\n", g_stUsimmT1CtrlCtx.ulUICCSeqNum);
    vos_printf("g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg         %d\n", g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg);
    vos_printf("g_stUsimmT1CtrlCtx.ulSendBlkChainFlg        %d\n", g_stUsimmT1CtrlCtx.ulSendBlkChainFlg);
    vos_printf("g_stUsimmT1CtrlCtx.ulUnexpectCount          %d\n", g_stUsimmT1CtrlCtx.ulUnexpectCount);

    vos_printf("\n********************T1 可维可测信息************************\n");
    vos_printf("发送I-Block成功次数统计                     %d\n", g_stT1StatisticInfo.ulSndIBlkSuccCnt);
    vos_printf("发送I-Block失败次数统计                     %d\n", g_stT1StatisticInfo.ulSndIBlkFailCnt);
    vos_printf("发送R-Block成功次数统计                     %d\n", g_stT1StatisticInfo.ulSndRBlkSuccCnt);
    vos_printf("发送R-Block失败次数统计                     %d\n", g_stT1StatisticInfo.ulSndRBlkFailCnt);
    vos_printf("发送S-Block(RESYNCH Request)成功次数统计    %d\n", g_stT1StatisticInfo.ulSndSBlkResynchReqSuccCnt);
    vos_printf("发送S-Block(RESYNCH Request)失败次数统计    %d\n", g_stT1StatisticInfo.ulSndSBlkResynchReqFailCnt);
    vos_printf("发送S-Block(IFS Request)成功次数统计        %d\n", g_stT1StatisticInfo.ulSndSBlkIFSReqSuccCnt);
    vos_printf("发送S-Block(IFS Request)失败次数统计        %d\n", g_stT1StatisticInfo.ulSndSBlkIFSReqFailCnt);
    vos_printf("发送S-Block(IFS Response)成功次数统计       %d\n", g_stT1StatisticInfo.ulSndSBlkIFSRspSuccCnt);
    vos_printf("发送S-Block(IFS Response)失败次数统计       %d\n", g_stT1StatisticInfo.ulSndSBlkIFSRspFailCnt);
    vos_printf("发送S-Block(ABORT Request)成功次数统计      %d\n", g_stT1StatisticInfo.ulSndSBlkAbortReqSuccCnt);
    vos_printf("发送S-Block(ABORT Request)失败次数统计      %d\n", g_stT1StatisticInfo.ulSndSBlkAbortReqFailCnt);
    vos_printf("发送S-Block(ABORT Response)成功次数统计     %d\n", g_stT1StatisticInfo.ulSndSBlkAbortRspSuccCnt);
    vos_printf("发送S-Block(ABORT Response)失败次数统计     %d\n", g_stT1StatisticInfo.ulSndSBlkAbortRspFailCnt);
    vos_printf("发送S-Block(WTX Response)成功次数统计       %d\n", g_stT1StatisticInfo.ulSndSBlkWTXRspSuccCnt);
    vos_printf("发送S-Block(WTX Response)失败次数统计       %d\n", g_stT1StatisticInfo.ulSndSBlkWTXRspFailCnt);
    vos_printf("接收到NAD域错误的Block次数统计              %d\n", g_stT1StatisticInfo.ulRcvNADErrBlkCnt);
    vos_printf("接收到长度异常(小于理论最小块长度或大于理论最大块长度)的Block次数统计 %d\n", g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt);
    vos_printf("接收到长度错误(头+LEN+EDC长度不等于接收到的总长度)的Block次数统计     %d\n", g_stT1StatisticInfo.ulRcvBlkSizeErrBlkCnt);
    vos_printf("接收到EDC域错误的Block次数统计              %d\n", g_stT1StatisticInfo.ulRcvEDCErrBlkCnt);
    vos_printf("接收到信息域超过IFSD的Block次数统计         %d\n", g_stT1StatisticInfo.ulRcvMoreThanIFSDErrBlkCnt);
    vos_printf("接收到LEN长度不为0的R-Block次数统计         %d\n", g_stT1StatisticInfo.ulRcvInvalidLenRBlkCnt);
    vos_printf("接收到PCB域bit 6不为0的R-Block次数统计      %d\n", g_stT1StatisticInfo.ulRcvInvalidBit6OfPCBRBlkCnt);
    vos_printf("接收到触发UE重发的R-Block次数统计           %d\n", g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt);
    vos_printf("接收到不符合协议流程逻辑的R-Block次数统计   %d\n", g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt);
    vos_printf("接收到不符合协议流程逻辑的I-Block次数统计   %d\n", g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt);
    vos_printf("接收到LEN长度不符合协议逻辑(如WTX REQ中LEN!=1)的S-Block次数统计       %d\n", g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt);
    vos_printf("接收到Type不符合协议逻辑的S-Block次数统计   %d\n", g_stT1StatisticInfo.ulRcvInvalidTypeSBlkCnt);
    vos_printf("接收到不符合协议流程逻辑的S-Block次数统计   %d\n", g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt);
    vos_printf("去激活卡次数统计                            %d\n", g_stT1StatisticInfo.ulDeactCardCnt);
    vos_printf("调用底软接口设置BWT失败次数统计             %d\n", g_stT1StatisticInfo.ulSetBWTFailCnt);
    vos_printf("调用底软接口进行T=0和T=1协议类型切换失败次数统计                      %d\n", g_stT1StatisticInfo.ulProtocolSwitchFailCnt);
    /*lint +e534*/

    return;

}

/*****************************************************************************
函 数 名  :USIMM_T1ResetStatisticInfo
功能描述  :清除T1可维可测信息
输入参数  :VOS_VOID
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
  1.日    期   : 2013年10月18日
    作    者   : L00256032
    修改内容   : V9R1 T=1项目修改
*****************************************************************************/
VOS_VOID USIMM_T1ResetStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stT1StatisticInfo, 0, sizeof(g_stT1StatisticInfo));
    /*lint +e534*/
    return;
}

/*****************************************************************************
函 数 名  : USIMM_T1DLSendRBlock
功能描述  : T=1链路层发送R-Block
输入参数  : pstAPDUData:输入命令内容
            ulSeqNum   :发送序号
输出参数  : 无
返 回 值  : VOS_OK  --- 函数执行成功
            VOS_ERR --- 函数执行失败
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_UINT32  USIMM_T1DLSendRBlock(
    USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32    enErrcode,
    VOS_UINT32                              ulSeqNum
)
{
    VOS_UINT32      ulRBlkLen;
    VOS_UINT8      *pucRBlk;
    VOS_UINT16      usCrc16;
    VOS_INT32       lSCIResult;

    /* 计算R-Block的长度 */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulRBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulRBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucRBlk = &g_aucT1SndBuffer[0];

    /* 填充Prologue field */
    /* 1.填充NAD为0 */
    pucRBlk[T1_NAD] = 0;

    /* 2.填充PCB:
         Bit 8~Bit 6: 100
         Bit 5:填写为预期的N(R);
         Bit 4~Bit 1:0000-Error free;
                     0001-EDC error;
                     0002-Other error;
                     其他-RFU*/
    pucRBlk[T1_PCB] = 0x80;

    pucRBlk[T1_PCB] |= (VOS_UINT8)(ulSeqNum << (USIMM_R_BLOCK_PCB_NR_BIT - 1));

    pucRBlk[T1_PCB] |= (VOS_UINT8)enErrcode;

    /* 3.填充LEN，R-block的INF长度为0 */
    pucRBlk[T1_LEN] = 0;

    /* 填充Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucRBlk[T1_INFO_START_BYTE] = USIMM_T1CalLrc(pucRBlk, USIMM_T1_PROLOGUE_FIELD_SIZE);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucRBlk, USIMM_T1_PROLOGUE_FIELD_SIZE);

        pucRBlk[T1_INFO_START_BYTE] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucRBlk[T1_INFO_START_BYTE + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* 调用底软SCI发送接口 */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulRBlkLen, pucRBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* 勾取发送的R-Block */
    USIMM_SciDataHook(ulRBlkLen, pucRBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulSndRBlkSuccCnt++;

        return VOS_OK;
    }
    else
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulSndRBlkFailCnt++;

        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  : USIMM_T1DLSendIBlock
功能描述  : T=1链路层发送I-Block
输入参数  : pucData :待发送数据指针
            ulLen   :待发送数据长度
            ulSeqNum:发送序号
输出参数  : 无
返 回 值  : VOS_OK  --- 函数执行成功
            VOS_ERR --- 函数执行失败
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_UINT32  USIMM_T1DLSendIBlock(VOS_UINT8 *pucData, VOS_UINT32 ulLen, VOS_UINT32 ulSeqNum)
{
    VOS_UINT32                                              ulIBlkLen;
    /* 区分分片/不分片的场景，需要记录当前这次实际发送的INF域长度 */
    VOS_UINT32                                              ulCurrSndInflen;
    VOS_UINT8                                              *pucIBlk;
    VOS_UINT16                                              usCrc16;
    VOS_INT32                                               lSCIResult;
    USIMM_T1_PROC_STATE_ENUM_UINT32                         enDstState;
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32              enMoreBit;

    if (0 == ulLen)
    {
        USIMM_WARNING_LOG("USIMM_T1DLSendIBlock: ulLen is 0!");

        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulSndIBlkFailCnt++;

        return VOS_ERR;
    }
    else if (ulLen <= g_stUsimmT1CtrlCtx.ulIFSC)
    {
        ulCurrSndInflen = ulLen;
        enMoreBit = USIMM_T1_I_BLOCK_WITHOUT_MORE_DATA;
        enDstState = USIMM_T1_PROC_STATE_SENT_APDU;
    }
    else
    {
        ulCurrSndInflen = g_stUsimmT1CtrlCtx.ulIFSC;
        enMoreBit = USIMM_T1_I_BLOCK_WITH_MORE_DATA;
        enDstState = USIMM_T1_PROC_STATE_SENT_CHAIN_APDU;

        /* 标记正在链块发送过程中 */
        g_stUsimmT1CtrlCtx.ulSendBlkChainFlg = VOS_TRUE;
    }

    /* 计算I-Block的长度 */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulIBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulIBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucIBlk = &g_aucT1SndBuffer[0];

    /* 填充Prologue field */
    /* 1.填充NAD为0 */
    pucIBlk[T1_NAD] = 0;

    /* 2.填充PCB:
         Bit 8: 0
         Bit 7: 填充N(S)
         Bit 6: 赋值为M bit的值
         Bit 5~Bit 1:RFU*/
    pucIBlk[T1_PCB] = (VOS_UINT8)(ulSeqNum << (USIMM_I_BLOCK_PCB_NS_BIT - 1));

    pucIBlk[T1_PCB] |= (VOS_UINT8)(enMoreBit << (USIMM_I_BLOCK_PCB_MORE_DATA_BIT - 1));

    /* 3.填充LEN，I-block的INF长度填写为当此发送的长度 */
    pucIBlk[T1_LEN] = (VOS_UINT8)ulCurrSndInflen;

    /* 填充Information field */
    /*lint -e534*/
    VOS_MemCpy(pucIBlk + T1_INFO_START_BYTE, pucData, ulCurrSndInflen);
    /*lint +e534*/

    /* 填充Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen] = USIMM_T1CalLrc(pucIBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucIBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen);

        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* 调用底软SCI发送接口 */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulIBlkLen, pucIBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* 勾取发送的R-Block */
    USIMM_SciDataHook(ulIBlkLen, pucIBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* 将状态迁移至目标状态 */
        g_stUsimmT1CtrlCtx.enT1ProcState = enDstState;

        /* 将此次发送的INF域长度记录到全局变量中 */
        g_stT1SendDataInfo.ulLastLen = ulCurrSndInflen;

        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulSndIBlkSuccCnt++;

        return VOS_OK;
    }
    else
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulSndIBlkFailCnt++;

        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  : USIMM_T1DLSendSBlock
功能描述  : T=1链路层发送S-Block
输入参数  : pstSBlk   --- 待发送的S-Block信息，包括S-Block类型，长度、指针
输出参数  : 无
返 回 值  : VOS_OK  --- 函数执行成功
            VOS_ERR --- 函数执行失败
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_UINT32  USIMM_T1DLSendSBlock(USIMM_T1_S_BLOCK_STRU *pstSBlk)
{
    VOS_UINT32      ulSBlkLen;
    VOS_UINT8      *pucSBlk;
    VOS_UINT16      usCrc16;
    VOS_INT32       lSCIResult;

    /* 检查S-Block信息域的长度是否合法 */
    if (pstSBlk->ucLen > 1)
    {
        USIMM_WARNING_LOG("USIMM_T1DLSendSBlock: pstSBlk->ucLen is abnormal!");
        return VOS_ERR;
    }

    /* 计算S-Block的长度 */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulSBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulSBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucSBlk = &g_aucT1SndBuffer[0];

    /* 填充Prologue field */
    /* 1.填充NAD为0 */
    pucSBlk[T1_NAD] = 0;

    /* 2.填充PCB:
         Bit 8~Bit 7: 11
         Bit 6: 0- request;
                1- response;
         Bit 5~Bit 1:00000-RESYNCH;
                     00001-IFS;
                     00002-ABORT;
                     00003-WTX;
                     00004-VPP error(不使用)
                     其他-RFU*/
    pucSBlk[T1_PCB] = (VOS_UINT8)pstSBlk->enSBlkType;

    /* 3.填充LEN */
    pucSBlk[T1_LEN] = pstSBlk->ucLen;

    /* 填充Information field,S-Block的LEN长度为0或1 */
    if (0 != pstSBlk->ucLen)
    {
        pucSBlk[T1_INFO_START_BYTE] = pstSBlk->ucData;
    }

    /* 填充Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen] = USIMM_T1CalLrc(pucSBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucSBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen);

        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* 调用底软SCI发送接口 */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulSBlkLen, pucSBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* 勾取发送的R-Block */
    USIMM_SciDataHook(ulSBlkLen, pucSBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* 如果发送的是S-Block的request帧，则需要将状态切入USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ */
        if (0 == (pstSBlk->enSBlkType & USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK))
        {
            g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ;
        }

        /* 可维可测信息统计 */
        USIMM_T1StatisticSendSBlockSucc(pstSBlk->enSBlkType);
        return VOS_OK;
    }
    else
    {
        /* 可维可测信息统计 */
        USIMM_T1StatisticSendSBlockFail(pstSBlk->enSBlkType);
        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  :USIMM_T1DLGetBlkType
功能描述  :T=1协议,获取块类型及相应参数
输入参数  :ucPCB:块起始域中PCB字节
输出参数  :pstBlkPara:块类型及参数
返 回 值  :VOS_VOID
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_T1DLGetBlkType(VOS_UINT8 ucPCB, USIMM_T1_BLOCK_PARA_STRU *pstBlkPara)
{
    if (USIMM_T1_BLOCK_TYPE_R == (ucPCB & USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK))
    {
        /* 收到R block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_R;

        /* 得到R block的序号 */
        pstBlkPara->uBlockPara.stRBlockPara.ulSeqNum = (ucPCB & USIMM_R_BLOCK_PCB_NR_BIT_MASK) >> (USIMM_R_BLOCK_PCB_NR_BIT - 1);

        /* 得到R block的错误码 */
        pstBlkPara->uBlockPara.stRBlockPara.enErrcode = ucPCB & USIMM_R_BLOCK_PCB_ERRCODE_BIT_MASK;
    }
    else if (USIMM_T1_BLOCK_TYPE_S == (ucPCB & USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK))
    {
        /* 收到S block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_S;

        /* 获取S block的子类型 */
        pstBlkPara->uBlockPara.stSBlockPara.enSBlkType = ucPCB;
    }
    else
    {
        /* 收到I block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_I;

        /* 获取I block的序号 */
        pstBlkPara->uBlockPara.stIBlockPara.ulSeqNum  = (ucPCB & USIMM_I_BLOCK_PCB_NS_BIT_MASK) >> (USIMM_I_BLOCK_PCB_NS_BIT - 1);

        /* 获取I block的more data bit 指示位 */
        pstBlkPara->uBlockPara.stIBlockPara.enMoreBit = (ucPCB & USIMM_I_BLOCK_PCB_MORE_DATA_BIT_MASK) >> (USIMM_I_BLOCK_PCB_MORE_DATA_BIT - 1);
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLCheckBlockByPCB
功能描述  :T=1协议中通过PCB字节判定块是否合法
输入参数  :pstPrologueField--块起始域
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_T1DLCheckBlockByPCB(USIMM_T1_PROLOGUE_FIELD_STRU  *pstPrologueField)
{
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;

    /* 获取块类型及参数 */
    USIMM_T1DLGetBlkType(pstPrologueField->ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* R block 信息域应该为0 */
        if (0 != pstPrologueField->ucLen)
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvInvalidLenRBlkCnt++;
            return VOS_ERR;
        }

        /* R block 的PCB字节中，bit 6必须为0 */
        if (0 != (pstPrologueField->ucPCB & USIMM_R_BLOCK_PCB_SIXTH_BIT_MASK))
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvInvalidBit6OfPCBRBlkCnt++;
            return VOS_ERR;
        }
    }

    if (USIMM_T1_BLOCK_TYPE_S == stBlkPara.enBlockType)
    {
        switch (stBlkPara.uBlockPara.stSBlockPara.enSBlkType)
        {
            /* 下面S BLOCK应该有信息域 */
            case USIMM_T1_S_BLOCK_IFS_REQ:
            case USIMM_T1_S_BLOCK_IFS_RES:
            case USIMM_T1_S_BLOCK_WTX_REQ:
                if (1 != pstPrologueField->ucLen)
                {
                    /* 可维可测信息统计 */
                    g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt++;
                    return VOS_ERR;
                }
                break;

            /* 下面S BLOCK应该没有信息域 */
            case USIMM_T1_S_BLOCK_RESYNCH_RES:
            case USIMM_T1_S_BLOCK_ABORT_REQ:
            case USIMM_T1_S_BLOCK_ABORT_RES:
                if (0 != pstPrologueField->ucLen)
                {
                    /* 可维可测信息统计 */
                    g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt++;
                    return VOS_ERR;
                }
                break;

            default:
                /* 非法S BLOCK */
                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulRcvInvalidTypeSBlkCnt++;
                return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLIsBlockValid
功能描述  :T=1协议中判定块是否合法　
输入参数  :ulLength:块长度
           pucData:块数据
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_T1DLIsBlockValid(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    VOS_UINT8                           ucLrc;
    VOS_UINT16                          usCrc;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT32                          ulBlkSize;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMaxBlkSize;
    VOS_UINT32                          ulMinBlkSize;

    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulMinBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulMinBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_CRC_SIZE;
    }

    if (ulLength < ulMinBlkSize)
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
        return VOS_FALSE;
    }

    /* 块起始域赋值 */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];

    /* 如果采用的是LRC校验 */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        /* 如果块大于最大块大小,则认为块非法 */
        ulMaxBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_LRC_SIZE;

        if (ulLength > ulMaxBlkSize)
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
            return VOS_FALSE;
        }

        /* 如果块校验和错误,则认为块非法 */
        ucLrc = USIMM_T1CalLrc(pucData, ulLength - USIMM_T1_LRC_SIZE);

        /* LRC校验和错误,块数据最后一个字节为LRC校验和 */
        if (ucLrc != pucData[ulLength - 1])
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvEDCErrBlkCnt++;
            return VOS_FALSE;
        }

        /* 计算块大小 */
        ulBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + stPrologueField.ucLen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        /* 如果块大于最大块大小,则认为块非法 */
        ulMaxBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_CRC_SIZE;

        if (ulLength > ulMaxBlkSize)
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
            return VOS_FALSE;
        }

        /* 如果块校验和错误,则认为块非法 */
        usCrc = USIMM_T1CalCCITTCrc16(pucData, ulLength - USIMM_T1_CRC_SIZE);

        /* CRC校验和错误,块数据最后两个字节为CRC校验和 */
        if (usCrc != ((pucData[ulLength - 1] << 8) | pucData[ulLength - 2]))
        {
            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvEDCErrBlkCnt++;
            return VOS_FALSE;
        }

        /* 计算块大小 */
        ulBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + stPrologueField.ucLen + USIMM_T1_CRC_SIZE;
    }

    /* 如果SAD和DAD错误，则认为块非法 */
    if (0 != stPrologueField.ucNAD)
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvNADErrBlkCnt++;

        return VOS_FALSE;
    }

    /* 通过PCB判断是否非法 */
    ulResult = USIMM_T1DLCheckBlockByPCB(&stPrologueField);
    if (VOS_OK != ulResult)
    {
        return VOS_FALSE;
    }

    /* 长度字段与块实际长度不符则非法 */
    if (ulBlkSize != ulLength)
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvBlkSizeErrBlkCnt++;
        return VOS_FALSE;
    }

    /* 信息域长度大于IFSD则非法 */
    if (stPrologueField.ucLen > g_stUsimmT1CtrlCtx.ulIFSD)
    {
        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvMoreThanIFSDErrBlkCnt++;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcInvalidBlock
功能描述  :T=1协议,处理收到的非法块
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcInvalidBlock(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if (g_stUsimmT1CtrlCtx.ulUnexpectCount < USIMM_T1_MAX_ATTEMPTS_TIMES)
    {
        /* 发送R-BLOCK请求重传 */
        ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

        /* 计数器增加 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount++;
    }
    else
    {
        /* 发送重同步请求,无信息域 */
        g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* 计数器清零,发送重同步请求后如果收到非法块会重新发送Sblock，在收到Sblock响应那里计数器增加 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcCardCmdRes
功能描述  :T=1协议,收到完整I BLOCK后处理卡的命令响应数据
输入参数  :
输出参数  :
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcCardCmdRes(USIMM_APDU_ST *pstAPDUData)
{
    /* 卡的响应至少为两字节 */
    if (g_stT1RcvDataInfo.ulDataLen < T1_CARD_SW_LEN)
    {
        return VOS_ERR;
    }

    /* 适配上层数据，给各字段赋值 */
    pstAPDUData->ucSW1 = g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen - 2];
    pstAPDUData->ucSW2 = g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen - 1];

    if ((g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN) <= USIMM_APDU_MAXLEN)
    {
        /*lint -e534*/
        VOS_MemCpy(pstAPDUData->aucRecvBuf, g_stT1RcvDataInfo.aucInfoData, g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(pstAPDUData->aucRecvBuf, g_stT1RcvDataInfo.aucInfoData, USIMM_APDU_MAXLEN);
        /*lint +e534*/
    }

    pstAPDUData->ulRecDataLen = g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN;

    pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;
    pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;

    /*lint -e534*/
    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLReSendSBlock
功能描述  :T=1协议,重新发送S BLOCK　
输入参数  :
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_T1DLReSendSBlock(VOS_VOID)
{
    VOS_UINT32      ulResult;

    /* 重发次数已超过最大次数 */
    if (g_stUsimmT1CtrlCtx.ulUnexpectCount >= USIMM_T1_MAX_ATTEMPTS_TIMES)
    {
        /* 重同步请求已发送三次或者IFS发送三次则直接复位 */
        if ((USIMM_T1_S_BLOCK_RESYNCH_REQ == g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType)
            ||(USIMM_T1_S_BLOCK_IFS_REQ == g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType))
        {
            /* 调用底软API去激活卡 */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RST);
            ulResult = mdrv_sci_deact();

            if (USIMM_SCI_SUCCESS != ulResult)
            {
                USIMM_ERROR_LOG("USIMM_T1DLReSendSBlock: Deactive Card Error");
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulDeactCardCnt++;

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
            /* 此场景下要上报无卡给协议栈 */
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);
#else
            /* 此场景下要上报无卡给协议栈 */
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange  = USIMM_CARD_STATE_CHANGED;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType     = USIMM_CARD_NOCARD;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService  = USIMM_CARD_SERVIC_ABSENT;
#endif

            g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;

            return VOS_ERR;
        }
        else
        {
            /* 发送重同步请求 */
            g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

            /* 重发次数计数器清零 */
            g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
        }
    }
    else
    {
        /* 重发S BLOCK */
        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* 重发次数计数器更新 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount++;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcRcvSBlockReq
功能描述  :T=1协议,收到S BLOCK REQUEST后的处理
输入参数  :enSBlkType:S BLOCK子类型
           ucData:S BLOCK信息域，根据子类型区别，可能无信息域
输出参数  :
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcRcvSBlockReq(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                           ucData
)
{
    VOS_UINT32      ulResult;

    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_IFS_REQ:

            /* IFSC不在范围内，则不更新全局变量,发重同步请求 */
            if ((ucData > USIMM_T1_MAX_IFS) || (ucData < USIMM_T1_MIN_IFS))
            {
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* 重发次数计数器清零 */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
            }
            else
            {
                /* 更新IFSC */
                g_stUsimmT1CtrlCtx.ulIFSC = ucData;

                /* 回复响应 */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_IFS_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(ucData);
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = ucData;
            }

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            break;

        case USIMM_T1_S_BLOCK_ABORT_REQ:

            /* 判断是否在链块发送中 */
            if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulSendBlkChainFlg)
            {
                /* 清空已发送链块 */
                g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
                g_stT1SendDataInfo.ulLastLen       = 0;
                g_stT1SendDataInfo.ulLastTotalLen  = 0;

                /* 回复响应 */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_ABORT_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            else if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg) /* 判断是否在链块接收中 */
            {
                /* 清空接收数据 */
                g_stT1RcvDataInfo.ulDataLen = 0;

                /* 回复响应 */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_ABORT_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            else /* 出错分支 */
            {
                /* 错误响应, 发送重同步请求 */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* 重发次数计数器清零 */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            break;

        case USIMM_T1_S_BLOCK_WTX_REQ:
            /* 判断BWT倍数是否合法 */
            if (0 == ucData)
            {
                /* BWT倍数非法, 发送重同步请求 */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* 重发次数计数器清零 */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
                return ulResult;
            }

            /* 更新WTX */
            g_stUsimmT1CtrlCtx.ulBWTTimes = ucData;

            /* 回复响应 */
            g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_WTX_RES;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(ucData);
            g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = ucData;

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

            /* 发送数据出错 */
            if (VOS_OK != ulResult)
            {
                break;
            }

            /* 调用底软API设置BWT超时 */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1);
            if (USIMM_SCI_SUCCESS == mdrv_sci_set_bwt(ucData))
            {
                ulResult = VOS_OK;
            }
            else
            {
                ulResult = VOS_ERR;

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulSetBWTFailCnt++;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            break;

        default:
            /* 错误响应, 根据RULE 7.1，需要发送R-BLOCK请求重传 */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* 计数器增加 */
            g_stUsimmT1CtrlCtx.ulUnexpectCount++;

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcRcvSBlockRes
功能描述  :T=1协议,收到S BLOCK RESPONSE后处理
输入参数  :enSBlkType:S BLOCK子类型
           ucData:S BLOCK信息域，根据子类型区别，可能无信息域
输出参数  :
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcRcvSBlockRes(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                           ucData
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    NV_USIMM_T1_CTRL_PARA_STRU          stT1CtrlPara;

    /* 判断收到的响应和发送的REQ是否匹配，不匹配则重新发送REQ */
    if (enSBlkType != (USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK | g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType))
    {
        ulResult = USIMM_T1DLReSendSBlock();

        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

        return ulResult;
    }

    switch(enSBlkType)
    {
        case USIMM_T1_S_BLOCK_IFS_RES:

            /*lint -e534*/
            VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
            /*lint +e534*/

            if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA, &stT1CtrlPara, sizeof(stT1CtrlPara)))
            {
                /* 打印错误 */
                USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");
            }

            if (ucData != stT1CtrlPara.ulDefaultIFSD)
            {
                /* 与IFS REQ中的不相同，重新发送IFS REQ */
                ulResult = USIMM_T1DLReSendSBlock();
            }
            else
            {
                /* 更新IFSD的值 */
                g_stUsimmT1CtrlCtx.ulIFSD = ucData;

                /* IFS REQ只在初始化第一次发送，因此收到响应后，状态机置为IDLE */
                g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;
            }

            break;

        case USIMM_T1_S_BLOCK_RESYNCH_RES:

            /* 设置UE和卡的块初始序号 */
            g_stUsimmT1CtrlCtx.ulUESeqNum = USIMM_T1_I_BLOCK_INIT_SEQ;
            g_stUsimmT1CtrlCtx.ulUICCSeqNum = USIMM_T1_I_BLOCK_INIT_SEQ;

            /* 清空已发送数据 */
            g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
            g_stT1SendDataInfo.ulLastLen       = 0;
            g_stT1SendDataInfo.ulLastTotalLen  = 0;

            /* 重新发送I-BLOCK */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            break;

        case USIMM_T1_S_BLOCK_ABORT_RES:

            /* 当前在发送链块，则重新发送链块 */
            if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulSendBlkChainFlg)
            {
                /* 将已发送数据清零 */
                g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
                g_stT1SendDataInfo.ulLastLen       = 0;
                g_stT1SendDataInfo.ulLastTotalLen  = 0;

                /* 重新发送数据 */
                ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
            }
            else if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg)/* 当前在接收链块，重新发送I-BLOCK，触发链块的接收 */
            {
                /* 清空已接收数据长度 */
                g_stT1RcvDataInfo.ulDataLen = 0;

                /* 重新发送数据 */
                ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
            }
            else
            {
                /* 错误响应,重新发送S-BLOCK */
                ulResult = USIMM_T1DLReSendSBlock();
            }

            break;

        default:
            /* 错误响应,重新发送S-BLOCK */
            ulResult = USIMM_T1DLReSendSBlock();

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcSBlock
功能描述  :T=1协议,收到S BLOCK后处理
输入参数  :enSBlkType:S BLOCK子类型
           pucInfData:S BLOCK信息域指针
输出参数  :
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcSBlock(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                          *pucInfData
)
{
    VOS_UINT32      ulResult;

    /* 当前发送过S BLOCK REQ,等待接收response */
    if (USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ == g_stUsimmT1CtrlCtx.enT1ProcState)
    {
        ulResult = USIMM_T1DLProcRcvSBlockRes(enSBlkType, *pucInfData);
    }
    else /* 收到S BLOCK REQ */
    {
        ulResult = USIMM_T1DLProcRcvSBlockReq(enSBlkType, *pucInfData);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcIBlockRes
功能描述  :T=1协议,当前发送了单个APDU后处理收到I BLOCK的响应数据处理
输入参数  :enMoreBit:链块指示
           pstPrologueField:指向块起始域信息
           pucInformationData:指向块信息域
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcIBlockRes(
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32  enMoreBit,
    USIMM_T1_PROLOGUE_FIELD_STRU               *pstPrologueField,
    VOS_UINT8                                  *pucInformationData
)
{
    VOS_UINT32      ulResult = VOS_OK;

    /* 判断是否为链块数据 */
    if (USIMM_T1_I_BLOCK_WITH_MORE_DATA == enMoreBit)
    {
        /* 标记在链块的接收中 */
        g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg = VOS_TRUE;

        /* 重发次数计数器清零 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* 链块接收中，期望卡的序号翻转 */
        g_stUsimmT1CtrlCtx.ulUICCSeqNum = (g_stUsimmT1CtrlCtx.ulUICCSeqNum + 1) % 2;

        /* 接收buf满的话丢弃数据 */
        if ((g_stT1RcvDataInfo.ulDataLen + pstPrologueField->ucLen) <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* 存储数据 */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]), pucInformationData, pstPrologueField->ucLen);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += pstPrologueField->ucLen;
        }

        /* 发送R BLOCK确认块，请求下一个数据块 */
        ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_ERROR_FREE, g_stUsimmT1CtrlCtx.ulUICCSeqNum);
    }
    else
    {
        /* 如果更新过WTX，则收到正常响应后，恢复WTX值 */
        if (USIMM_T1_DEFAULT_WTX != g_stUsimmT1CtrlCtx.ulBWTTimes)
        {
            /* 调用底软API设置BWT超时 */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2);
            if (USIMM_SCI_SUCCESS != mdrv_sci_set_bwt(USIMM_T1_DEFAULT_WTX))
            {
                /* 如果调用底软API出错，打印错误 */
                USIMM_ERROR_LOG("USIMM_T1DLProcIBlockRes:Set BWT to default value fail");

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulSetBWTFailCnt++;
            }
            else
            {
                g_stUsimmT1CtrlCtx.ulBWTTimes = USIMM_T1_DEFAULT_WTX;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }

        /* 收到单个apdu的响应或者链块的最后一个响应，发送序号和期望卡的序号都要翻转 */
        g_stUsimmT1CtrlCtx.ulUESeqNum = (g_stUsimmT1CtrlCtx.ulUESeqNum + 1) % 2;

        g_stUsimmT1CtrlCtx.ulUICCSeqNum = (g_stUsimmT1CtrlCtx.ulUICCSeqNum + 1) % 2;

        if ((g_stT1RcvDataInfo.ulDataLen + pstPrologueField->ucLen) <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* 存储数据 */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]), pucInformationData, pstPrologueField->ucLen);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += pstPrologueField->ucLen;
        }
        else if (g_stT1RcvDataInfo.ulDataLen + T1_CARD_SW_LEN <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* buf不够存储本次所有数据，因此只存储状态字 */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]),
                       (pucInformationData + pstPrologueField->ucLen - T1_CARD_SW_LEN), T1_CARD_SW_LEN);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += T1_CARD_SW_LEN;
        }
        else
        {
            /* buf不够存储状态字，因此状态字覆盖原有后两个数据 */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[USIMM_T1_RCV_BUF_SIZE-T1_CARD_SW_LEN]),
                       (pucInformationData + pstPrologueField->ucLen - T1_CARD_SW_LEN), T1_CARD_SW_LEN);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen = USIMM_T1_RCV_BUF_SIZE;
        }

        /* 重发次数计数器清零 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* 将接收链块标记置为VOS_FALSE */
        g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg = VOS_FALSE;

        /* 将发送链块标记置为VOS_FALSE */
        g_stUsimmT1CtrlCtx.ulSendBlkChainFlg = VOS_FALSE;

        /* 收到完整的响应数据 */
        g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcIdleState
功能描述  :T=1协议,当前为IDLE态的处理流程，由于状态机运转设计不会进入该状态，所以
           进入该状态后都作为异常处理
输入参数  :bValidFlag :标记收到的块是否合法
           ulLength   :块长度
           pucData    :块数据
           pstAPDUData:APDU结构
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月22日
   作    者   : L00256032
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcIdleState(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    USIMM_ERROR_LOG("USIMM_T1DLProcIdleState: Usimm T1 DL receive block Run into Error State");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcSendApduState
功能描述  :T=1协议,当前发送了单个APDU后处理收到响应块　
输入参数  :bValidFlag:标记收到的块是否合法
           ulLength:块长度
           pucData:块数据
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcSendApduState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* 处理非法块 */
    if (VOS_FALSE == bValidFlag)
    {
        ulResult = USIMM_T1DLProcInvalidBlock();

        return ulResult;
    }

    /* 处理正常响应 */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* 获取块类型及参数 */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_I == stBlkPara.enBlockType)
    {
        /* 判断是否为我们发出的I BLOCK的响应数据 */
        if (stBlkPara.uBlockPara.stIBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUICCSeqNum)
        {
            ulResult = USIMM_T1DLProcIBlockRes(stBlkPara.uBlockPara.stIBlockPara.enMoreBit, &stPrologueField, pucInformationData);
        }
        else
        {
            /* 不是我们期望的数据，发送R Block，请求重发 */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
        }
    }
    else if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* 如何控制此处 避免在此处死循环 */
        if (stBlkPara.uBlockPara.stRBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUESeqNum)
        {
            /* 重新发送I BLOCK */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt++;
        }
        else
        {
            /* 收到一个不期望的块，请求发出的I BLOCK的响应数据块 */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt++;
        }
    }
    else
    {
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcSendChainApduState
功能描述  :T=1协议,当前发送了链块APDU后处理收到响应块　
输入参数  :bValidFlag:标记收到的块是否合法
           ulLength:块长度
           pucData:块数据
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcSendChainApduState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* 处理非法块 */
    if (VOS_FALSE == bValidFlag)
    {
        ulResult = USIMM_T1DLProcInvalidBlock();

        return ulResult;
    }

    /* 处理正常响应 */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* 获取块类型及参数 */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_I == stBlkPara.enBlockType)
    {
        /* 不期望的响应，直接发送重同步请求，此处协议没有明确规定如何处理 */
        g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

        /* 重发次数计数器清零 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* 可维可测信息统计 */
        g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
    }
    else if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* 判断收到的序号是否和发送序号相同 */
        /* 如何控制此处 避免在此处死循环 */
        if (stBlkPara.uBlockPara.stRBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUESeqNum)
        {
            /* 重发I BLOCK分片 */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt++;
        }
        else  /* 收到期望响应 */
        {
            /* 重发次数计数器清零 */
            g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

            /* 链块发送过程中，收到期望响应后，发送序号增加 */
            g_stUsimmT1CtrlCtx.ulUESeqNum = (g_stUsimmT1CtrlCtx.ulUESeqNum + 1) % 2;

            /* 更新已发送数据指针 */
            g_stT1SendDataInfo.pucLastInfoData += g_stT1SendDataInfo.ulLastLen;
            g_stT1SendDataInfo.ulLastTotalLen  += g_stT1SendDataInfo.ulLastLen;

            /* 发送下一个分片 */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
        }
    }
    else
    {
        /* 收到S BLOCK */
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcSendSBlkReqState
功能描述  :T=1协议,当前发送了S BLOCK req后处理收到响应块　
输入参数  :bValidFlag:标记收到的块是否合法
           ulLength:块长度
           pucData:块数据
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLProcSendSBlkReqState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* 处理非法块 */
    if (VOS_FALSE == bValidFlag)
    {
        /* 重新发送S BLOCK */
        ulResult = USIMM_T1DLReSendSBlock();

        return ulResult;
    }

    /* 处理正常响应 */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* 获取块类型及参数 */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_S == stBlkPara.enBlockType)
    {
        /* 处理收到的S BLOCK */
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }
    else
    {
        /* I BLOCK或者R BLOCK都重发S BLOCK */
        ulResult = USIMM_T1DLReSendSBlock();

        /* 可维可测信息统计 */
        if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
        {
            g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt++;
        }
        else
        {
            g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
        }

    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLProcessBlock
功能描述  :T=1协议,处理卡返回的块数据　
输入参数  :bValidFlag:标记收到的块是否合法
           ulLength:块长度
           pucData:块数据
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
static USIMMT1DL_RECV_FUNC_STATUS gastUSIMMT1DLRecvBlkProc[] =
{
    {USIMM_T1_PROC_STATE_IDLE,              USIMM_T1DLProcIdleState},
    {USIMM_T1_PROC_STATE_SENT_APDU,         USIMM_T1DLProcSendApduState},
    {USIMM_T1_PROC_STATE_SENT_CHAIN_APDU,   USIMM_T1DLProcSendChainApduState},
    {USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ,  USIMM_T1DLProcSendSBlkReqState},
};

VOS_UINT32 USIMM_T1DLProcessBlock(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    VOS_UINT32      ulResult = VOS_ERR;
    VOS_UINT32      i;

    for (i = 0; i < ARRAYSIZE(gastUSIMMT1DLRecvBlkProc); i++)
    {
        if (g_stUsimmT1CtrlCtx.enT1ProcState == gastUSIMMT1DLRecvBlkProc[i].enStateId)
        {
            ulResult = gastUSIMMT1DLRecvBlkProc[i].pProcFun(bValidFlag, ulLength, pucData);

            break;
        }
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLReceiveData
功能描述  :实现T=1协议时卡返回数据的接收　
输入参数  :无
输出参数  :pstAPDUData:APDU命令接收内容
返 回 值  :调用底软API结果
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLReceiveData(VOS_VOID)
{
    VOS_INT32       lSCIResult;
    VOS_UINT8       aucRecData[USIMM_T1_BLOCK_MAX_SIZE + 1] = {0};    /* 增加一字节保护 */
    VOS_UINT32      ulRecBlockLen = 0;
    VOS_BOOL        bBlockValidFlag;
    VOS_UINT32      ulResult;

    /* 调用底软接口接收数据 */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RCV);
    lSCIResult = mdrv_sci_rcv_blk(aucRecData, (VOS_UINT *)&ulRecBlockLen);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* 勾取原始数据 */
        USIMM_SciDataHook(ulRecBlockLen, aucRecData);

        /* 判定块是否合法 */
        bBlockValidFlag = USIMM_T1DLIsBlockValid(ulRecBlockLen, aucRecData);
    }
    else
    {
        /* 打印错误，底软api返回错误 or 超时 */
        bBlockValidFlag = VOS_FALSE;
    }

    ulResult = USIMM_T1DLProcessBlock(bBlockValidFlag, ulRecBlockLen, aucRecData);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLCombineSendData
功能描述  :实现T=1协议时将APDU层传下来的发送数据组合成待发送数据块的信息域
输入参数  :无
输出参数  :pstAPDUData:APDU命令接收内容
返 回 值  :VOS_OK/VOS_ERR;
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLCombineSendData(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_OK;

    switch (gstUSIMMDLControl.enCMDCase)
    {
        case USIMM_CMD_CASE1: /* case1 只有四字节apdu头，既没有发送数据也没有响应数据 */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, T1_CASE1_APDU_LEN);
            /*lint +e534*/
            g_stT1SendDataInfo.ulTotalLen = T1_CASE1_APDU_LEN;

            break;

        case USIMM_CMD_CASE2: /* case2 没有发送数据有响应数据回来 */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);
            /*lint +e534*/
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN;
            break;

        case USIMM_CMD_CASE3: /* case3 有发送数据没有响应数据回来 */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);

            /* copy 发送数据 */
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData + USIMM_APDU_HEADLEN, pstAPDUData->aucSendBuf, pstAPDUData->ulLcValue);
            /*lint +e534*/

            /* 赋值发送长度 */
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue;
            break;

        case USIMM_CMD_CASE4: /* case4 既有发送数据也有响应数据回来 */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);

            /* copy 发送数据 */
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData + USIMM_APDU_HEADLEN, pstAPDUData->aucSendBuf, pstAPDUData->ulLcValue);
            /*lint +e534*/

            /* 赋值LE字段 */
            g_stT1SendDataInfo.aucInfoData[USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue] = (VOS_UINT8)pstAPDUData->ulLeValue;

            /* 赋值发送长度 */
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue + 1;
            break;

        default:
            /* 错误情况 */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandleIdleState
功能描述  :实现T=1协议时一层状态机IDLE状态处理
输入参数  :pstAPDUData:APDU命令发送内容
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLHandleIdleState(USIMM_APDU_ST* pstAPDUData)
{
    USIMM_ERROR_LOG("USIMM_T1DLHandleIdleState: Usimm T1 DL handle Run into Error State");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandleSendIFSState
功能描述  :实现T=1协议时一层状态机发送IFSD REQ状态处理
输入参数  :pstAPDUData:APDU命令发送内容
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLHandleSendIFSState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult;

    g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_IFS_REQ;
    g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(VOS_UINT8);
    g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = pstAPDUData->aucSendBuf[0];

    ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

    /* 发送ok的话转到接收块状态 */
    if (VOS_OK == ulResult)
    {
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_RCV_BLOCK;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandleSendInfoState
功能描述  :实现T=1协议时一层状态机发送APDU层数据状态处理
输入参数  :pstAPDUData:APDU命令发送内容
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLHandleSendInfoState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_T1DLCombineSendData(pstAPDUData);

    if (VOS_OK != ulResult)
    {
        return ulResult;
    }

    /* 全局变量初始化 */
    g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
    g_stT1SendDataInfo.ulLastLen       = 0;
    g_stT1SendDataInfo.ulLastTotalLen  = 0;

    /* 勾取发送的APDU */
    USIMM_SciDataHook(g_stT1SendDataInfo.ulTotalLen, g_stT1SendDataInfo.aucInfoData);

    /* 根据case组装信息域发送数据 */
    ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen, g_stUsimmT1CtrlCtx.ulUESeqNum);

    /* 发送ok的话转到接收块状态 */
    if (VOS_OK == ulResult)
    {
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_RCV_BLOCK;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandleRcvBlockState
功能描述  :实现T=1协议时一层状态机接收块数据状态处理
输入参数  :pstAPDUData:APDU命令发送内容
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLHandleRcvBlockState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_ERR;

    while (USIMM_T1_PROC_STATE_IDLE != g_stUsimmT1CtrlCtx.enT1ProcState)
    {
        ulResult = USIMM_T1DLReceiveData();

        /* 过程出现错误,跳出循环 */
        if (VOS_OK != ulResult)
        {
            break;
        }
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandleStateStar
功能描述  :实现T=1协议时一层状态机开始前预处理
输入参数  :无
输出参数  :pstAPDUData:APDU命令接收内容
返 回 值  :无
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_T1DLHandleStateStar(USIMM_APDU_ST* pstAPDUData)
{
    /* IFS REQ */
    if (VOS_TRUE == g_bSendIFSReqFlag)
    {
        /* 状态迁到发送IFS */
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_SEND_IFS;
    }
    else
    {
        /* 发送数据全局变量清空 */
        /*lint -e534*/
        VOS_MemSet(&g_stT1SendDataInfo, 0, sizeof(g_stT1SendDataInfo));

        VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);

        VOS_MemSet(&g_stT1RcvDataInfo, 0, sizeof(g_stT1RcvDataInfo));
        /*lint +e534*/

        /* 重新发送一个过程时，计数器清零 */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* 判断case */
        USIMM_DLJudgeCmdCase(pstAPDUData);

        /* 状态迁到发送业务数据 */
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_SEND_INFO;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLHandle
功能描述  :实现T=1协议时与卡交互数据入口
输入参数  :无
输出参数  :pstAPDUData:APDU命令接收内容
返 回 值  :调用底软API结果
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
static USIMMT1DL_HANDLE_FUNC_STATUS gastUSIMMT1DLHandleProc[] =
{
    {USIMM_T1DL_HANDLE_STATE_IDLE,              USIMM_T1DLHandleIdleState},
    {USIMM_T1DL_HANDLE_STATE_SEND_IFS,          USIMM_T1DLHandleSendIFSState},
    {USIMM_T1DL_HANDLE_STATE_SEND_INFO,         USIMM_T1DLHandleSendInfoState},
    {USIMM_T1DL_HANDLE_STATE_RCV_BLOCK,         USIMM_T1DLHandleRcvBlockState},
};

VOS_UINT32 USIMM_T1DLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_ERR;
    VOS_UINT32      i;

    if (USIMMDL_STATE_IDLE != g_stUsimmT1CtrlCtx.enT1HandleState)
    {
        USIMM_WARNING_LOG("USIMM_T0DLHandle: DL State is Wrong");/* 打印警告 */
    }

    USIMM_T1DLHandleStateStar(pstAPDUData);

    for (i = 0; i < ARRAYSIZE(gastUSIMMT1DLHandleProc); i++)
    {
        if (g_stUsimmT1CtrlCtx.enT1HandleState == gastUSIMMT1DLHandleProc[i].enStateId)
        {
            ulResult = gastUSIMMT1DLHandleProc[i].pProcFun(pstAPDUData);

            if (VOS_OK != ulResult)
            {
                break;
            }
        }
    }

    /* 一层状态迁到idle态，以便下一次过程正常进行 */
    g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_IDLE;

    if (VOS_TRUE == g_bSendIFSReqFlag)
    {
        return ulResult;
    }

    /* 给输出参数赋值 */
    if (VOS_OK == ulResult)
    {
        ulResult = USIMM_T1DLProcCardCmdRes(pstAPDUData);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_T1DLUpdateParaByATR
功能描述  :更新由ATR得到的T=1参数
输入参数  :enEDCType:块结束域校验类型
           ulIFSC:卡的接收能力
           ulIFSD:UE接收能力
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR;
修订记录  :
1. 日    期   : 2013年10月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_T1DLUpdateParaByATR(
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32   enEDCType,
    VOS_UINT32                                  ulIFSC,
    VOS_UINT32                                  ulIFSD
)
{
    if ((ulIFSC > USIMM_T1_MAX_IFS) || (ulIFSC < USIMM_T1_MIN_IFS))
    {
        return VOS_ERR;
    }

    if ((ulIFSD > USIMM_T1_MAX_IFS) || (ulIFSD < USIMM_T1_MIN_IFS))
    {
        return VOS_ERR;
    }

    if (enEDCType >= USIMM_T1_BLOCK_EPILOGUE_FIELD_BUTT)
    {
        return VOS_ERR;
    }

    g_stUsimmT1CtrlCtx.enErrDetectMode = enEDCType;
    g_stUsimmT1CtrlCtx.ulIFSC = ulIFSC;
    g_stUsimmT1CtrlCtx.ulIFSD = ulIFSD;

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

