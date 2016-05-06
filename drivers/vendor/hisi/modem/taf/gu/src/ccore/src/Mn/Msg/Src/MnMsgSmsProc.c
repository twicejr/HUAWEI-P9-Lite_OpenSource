/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSmsProc.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月19日
  最近修改   :
  功能描述   : 实现Msg模块接收到nas层sms模块发送过来消息的函数接口
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 创建文件

  2.日    期   : 2008年6月5日
    作    者   : fuyingjun id:62575
    修改内容   : 注册状态在MN层的更新不正确，SMS的TAF层不能进入正常驻留状态,问题单号:AT2D03632
  3.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04609,CMMS命令的增加；
  4.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
  5.日    期   : 2008-11-17
    作    者   : f62575
    修改内容   : 问题单号:AT2D06843, 短信状态报告的读，删除和上报接口与终端工具需求不符问题
  6.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D08974, 短信打印级别过高
  7.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D10321, SMMA重复发送问题；
  8.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
  9.日    期   : 2009年3月25日
    作    者   : 周君 40661
    修改内容   : 问题单号 AT2D08875,PS优先域发送短信，失败（
  10.日    期   : 2009年4月1日
     作    者   : 周君 40661
     修改内容   : 问题单号:AT2D09786, 用AT+CMGD=,4删除短信时，长时间不回应，导致自动化脚本检测不到单板
  11.日    期   : 2009年4月7日
     作    者   : f62575
     修改内容   : 问题单号 AT2D06392, 不支持短信和状态报告的NV存储相关代码通过宏开关关闭
  12.日    期   : 2009年4月22日
     作    者   : f62575
     修改内容   : 问题单号 AT2D11196, [SMS]短信状态报告接收存储后，查询短信存储状态，已使用的短信记录条数没有增加
  13.日    期   : 2009年05月11日
     作    者   : f62575
     修改内容   : 问题单号：AT2D11136，PICS表设置为仅支持SM存储，执行GCF测试用例34.2.5.3，测试用例失败
  14.日    期   : 2009年7月18日
     作    者   : z40661
     修改内容   : 终端可配置需求合入
  15.日    期   : 2009年08月7日
     作    者   : f62575
     修改内容   : STK特性合入
  16.日    期   : 2009年9月02日
     作    者   : f62575
     修改内容   : 问题单号:AT2D14189, 执行GCF协议34123的用例16.1.2和16.2.2失败
  17.日    期   : 2009年10月16日
     作    者   : f62575
     修改内容   : 问题单号:AT2D15127, 服务域为PS ONLY，发送域为CS PREFER，参照标杆
                  短信首先尝试从CS域发送；
  18.日    期   : 2009年12月9日
       作    者   : f62575
       修改内容   : 问题单号:AT2D15782, 短信存储区满时接收到短信状态报告给网络回复RP-ACK消息，
                                  与标竿相同情况下回复RP-ERROR(错误原因值22内存满不一致)；
  19.日    期   : 2009年12月16日
     作    者   : f62575
     修改内容   : AT2D16304, STK PP DOWN功能完善和SMS相关的(U)SIM文件REFRESH
  20.日    期   : 2010年01月26日
     作    者   : f62575
     修改内容   : 问题单号AT2D16565
                  短信自动回复桩失效，修改自动回复桩，使其能完成自动回复功能；
  21.日    期   : 2010年4月16日
     作    者   : f62575
     修改内容   : AT2D18550 TP-PID 为011111（Return Call Message）的短信,
                  UE未按协议要求的REPLACE方式处理
  22.日    期   : 2010年04月30日
     作    者   : F62575
     修改内容   : 问题单号AT2D15403
                  短信以CMT方式上报且CSMS配置为1时若应用不下发CNMA命令确认新短信接收,
                  则后续短信既不上报也不存储到本地;
  23.日    期   : 2010年03月25日
     作    者   : s46746
     修改内容   : 问题单号AT2D17931
                  合入新增Control口和激活SMS特性
  24.日    期   : 2010年5月7日
     作    者   : zhoujun /z40661
     修改内容   : AT2D19153，重发时间不够时，未能停止定时器

  25.日    期   : 2010年6月30日
     作    者   : 傅映君
     修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include "siapppb.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
#include "NasGmmInterface.h"
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

#include "NasUsimmApi.h"

#include "MmCmInterface.h"

#include "TafSdcCtx.h"
#include "MnMsgSendSpm.h"
#include "TafStdlib.h"

#include "MnMsgSmCommProc.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SMSPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
#define MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM                    (3)
#define MN_MSG_ACTIVE_MESSAGE_ENDSTR_MAX_LEN                (3)
/*****************************************************************************
  3 变量定义
*****************************************************************************/
LOCAL MN_MSG_TS_DATA_INFO_STRU         f_stMsgTsData;
VOS_UINT8                              g_ucMnMsgAutoReply = 0;
LOCAL VOS_UINT32                       f_ulMsgMoNum = 0;
LOCAL VOS_UINT32                       f_ulMsgMtNum = 0;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                               g_ucSetEfSmssClear = 0;
#endif

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_MSG_GetCurrentLineLen
 功能描述  : 获取激活短信内容中行结束符首地址
 输入参数  : VOS_UINT8                           *pucOrgAddr      行首首指针
             VOS_UINT32                          ulMsgLen         短信内容长度
             MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding      字符串的编码方式;
 输出参数  : VOS_UINT32                          *pulCurrentLineLen 行长度;
             VOS_UINT32                          *pulLineLenWithOutEndFlag 不带结束符的行长度;
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月18日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  MN_MSG_GetCurrentLineLen(
    VOS_UINT8                           *pucOrgAddr,
    VOS_UINT32                          ulOrgLen,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    VOS_UINT32                          *pulCurrentLineLen,
    VOS_UINT32                          *pulLineLenWithOutEndFlag
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucLineEndStr[MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM][MN_MSG_ACTIVE_MESSAGE_ENDSTR_MAX_LEN]
                                            = {"\r\n", "\r", "\n"};
    VOS_UINT32                          ulLineLen;
    VOS_UINT8                           *pucEndFlagStr;
    VOS_BOOL                            bEqualFlag;
    VOS_INT8                            cRet;
    VOS_UINT32                          ulLineEndStrLen;

    /*输出参数初始化: 包含结束符或不包含结束符长度均赋值为输入字符串的总长度*/
    *pulCurrentLineLen          = ulOrgLen;
    *pulLineLenWithOutEndFlag   = ulOrgLen;

    /*循环变量初始化: 结束符首地址指向输入字符串首地址；行长度赋值为输入字符串的总长度*/
    pucEndFlagStr = pucOrgAddr;
    ulLineLen     = ulOrgLen;

    if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
    {
        while (0 != ulLineLen)
        {
            /*UCS2编码: 检查是否存在行结束符<CR><LF>, <CR>, <LF>*/
            for (ulLoop = 0; ulLoop < MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM; ulLoop++)
            {
                MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucEndFlagStr,
                                                        ulLineLen,
                                                        aucLineEndStr[ulLoop],
                                                        &bEqualFlag);
                if (VOS_TRUE == bEqualFlag)
                {
                    *pulLineLenWithOutEndFlag = (VOS_UINT32)(pucEndFlagStr - pucOrgAddr);
                    *pulCurrentLineLen        = (VOS_UINT32)(*pulLineLenWithOutEndFlag
                                       + (VOS_UINT32)(VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]) * 2));
                    return;
                }
            }

            pucEndFlagStr += MN_WORD_UCS2_ENCODE_LEN;
            ulLineLen     -= MN_WORD_UCS2_ENCODE_LEN;
        }

    }
    else
    {
        while (0 != ulLineLen)
        {
            /*ASCII编码: 检查是否存在行结束符<CR><LF>, <CR>, <LF>*/
            for (ulLoop = 0; ulLoop < MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM; ulLoop++)
            {
                ulLineEndStrLen = VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]);
                if (ulLineLen < ulLineEndStrLen)
                {
                    continue;
                }

                cRet = VOS_StrNiCmp((VOS_CHAR *)pucEndFlagStr,
                                    (VOS_CHAR *)aucLineEndStr[ulLoop],
                                    ulLineEndStrLen);
                if (0 == cRet)
                {
                    *pulLineLenWithOutEndFlag = (VOS_UINT32)(pucEndFlagStr - pucOrgAddr);
                    *pulCurrentLineLen        = (VOS_UINT32)(*pulLineLenWithOutEndFlag
                                           + VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]));
                    return;
                }
            }

            pucEndFlagStr++;
            ulLineLen--;
        }


    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_IdentfyActiveMessage
 功能描述  : 判定短信是否激活短信
 输入参数  : MN_MSG_DELIVER_STRU                 *pstDeliver 解码后的短信
 输出参数  : VOS_BOOL                            *pbActiveMessage 是否激活短信
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID MN_MSG_IdentfyActiveMessage(
    const MN_MSG_DELIVER_STRU           *pstDeliver,
    VOS_BOOL                            *pbActiveMessage
)
{
    /*短信的CLASS类型不是CLASS1则输出短信不是激活短信*/
    /*短信的TP-PID类型不是TYPE0则输出短信不是激活短信*/
    if ((MN_MSG_TP_PID_SM_TYPE_0 == pstDeliver->enPid)
     && (MN_MSG_MSG_CLASS_1 == pstDeliver->stDcs.enMsgClass))
    {
        *pbActiveMessage = VOS_TRUE;
    }
    else
    {
        *pbActiveMessage = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_IdentifyActiveStatus
 功能描述  : 识别激活短信的激活状态字符串
 输入参数  : VOS_UINT8 *pucOrgData  激活短信内容首地址
             VOS_UINT32 ulLineLen   激活短信内容长度
             MN_MSG_MSG_CODING_ENUM_U8 enMsgCoding 激活短信内容编码
 输出参数  : MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8 *penActiveStatus
                MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE   去激活
                MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE       激活
 返 回 值  : VOS_OK 存在激活状态字符串,否则,不存在;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月19日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_IdentifyActiveStatus(
    VOS_UINT8                                                   *pucOrgData,
    VOS_UINT32                                                  ulLineLen,
    MN_MSG_MSG_CODING_ENUM_U8                                   enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8                     *penActiveStatus
)
{
    VOS_BOOL                            pbEqualFlag;
    VOS_INT8                            cRet;

    /*UCS2编码情况下获取激活状态*/
    if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
    {
        MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucOrgData,
                                                ulLineLen,
                                                (VOS_UINT8 *)"rs:on",
                                                &pbEqualFlag);
        if (VOS_TRUE == pbEqualFlag)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE;
            return VOS_OK;
        }

        MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucOrgData,
                                                ulLineLen,
                                                (VOS_UINT8 *)"rs:off",
                                                &pbEqualFlag);
        if (VOS_TRUE == pbEqualFlag)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
            return VOS_OK;
        }

    }
    /*GSM7BIT 8BIT编码情况下获取激活状态*/
    else
    {
        cRet = VOS_StrNiCmp((VOS_CHAR *)pucOrgData, "rs:on", VOS_StrLen("rs:on"));
        if (0 == cRet)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE;
            return VOS_OK;
        }

        cRet = VOS_StrNiCmp((VOS_CHAR *)pucOrgData, "rs:off", VOS_StrLen("rs:off"));
        if (0 == cRet)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
            return VOS_OK;
        }

    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetActiveStatus
 功能描述  : 获取激活短信的激活状态
 输入参数  : VOS_UINT8 *pucOrgData  激活短信内容首地址
             VOS_UINT32 ulLineLen   激活短信内容长度
             MN_MSG_MSG_CODING_ENUM_U8 enMsgCoding 激活短信内容编码
 输出参数  : MN_MSG_ACTIVE_MESSAGE_STATUS_UINT8  *penActiveStatus 激活短信的激活状态
 返 回 值  : VOS_ERR    激活短信的激活状态获取失败；
             VOS_OK     激活短信的激活状态获取成功；
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_GetActiveStatus(
    const VOS_UINT8                                             *pucMsgData,
    VOS_UINT32                                                  ulMsgLen,
    MN_MSG_MSG_CODING_ENUM_U8                                   enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8                     *penActiveStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucOrgData;                            /*sms content,not 7bit,all 8bit */
    VOS_UINT32                          ulLineLen;
    VOS_UINT32                          ulCurrentLineLen;
    VOS_UINT32                          ulLineLenWithOutEndFlag;
    VOS_UINT8                           *pucStatusStr;


    ulLineLen = 0;


    pucOrgData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pucOrgData)
    {
        MN_WARN_LOG("MN_MSG_GetActiveStatus:fail to alloc memory. ");
        return MN_ERR_NOMEM;
    }

    /*对短信内容进行7BIT到ASCII码的转换*/
    if (MN_MSG_MSG_CODING_7_BIT == enMsgCoding)
    {
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        TAF_STD_ConvertDefAlphaToAscii(pucMsgData, ulMsgLen, pucOrgData, &ulLineLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    }
    else
    {
        PS_MEM_CPY(pucOrgData, pucMsgData, ulMsgLen);
        ulLineLen = ulMsgLen;
    }

    /*获取激活短信状态字段: 判断当前字符串是否"rs:on"或"rs:off"，不区分大小写
      若包含"rs:on"或"rs:off", 则获取操作成;
      否则,获取操作失败;
    */
    pucStatusStr = pucOrgData;
    while (0 != ulLineLen)
    {
        /*确认当前字段是否激活短信状态字段*/
        ulRet = MN_MSG_IdentifyActiveStatus(pucStatusStr,
                                            ulLineLen,
                                            enMsgCoding,
                                            penActiveStatus);
        if (VOS_OK == ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
            return MN_ERR_NO_ERROR;
        }

        /*获取下一个信息行的行首并返回剩余字段长度;*/
        MN_MSG_GetCurrentLineLen(pucStatusStr,
                               ulLineLen,
                               enMsgCoding,
                               &ulCurrentLineLen,
                               &ulLineLenWithOutEndFlag);

        pucStatusStr    += ulCurrentLineLen;
        ulLineLen       -= ulCurrentLineLen;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
    return MN_ERR_UNSPECIFIED;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetActiveUrl
 功能描述  : 获取激活短信的URL
 输入参数  : VOS_UINT8 *pucOrgData  激活短信内容首地址
             VOS_UINT32 ulLineLen   激活短信内容长度
             MN_MSG_MSG_CODING_ENUM_U8 enMsgCoding 激活短信内容编码
 输出参数  : MN_MSG_ ACTIVE_MESSAGE_URL_STRU     *pstUrl        激活短信的URL
 返 回 值  : VOS_ERR                激活短信的URL获取失败；
             VOS_OK                 激活短信的URL获取成功；

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_GetActiveUrl(
    const VOS_UINT8                     *pucMsgData,
    VOS_UINT32                          ulMsgLen,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_URL_STRU      *pstUrl
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulStrLen;
    VOS_UINT8                           *pucUrlStr;
    VOS_UINT8                           *pucOrgData;                            /*sms content,not 7bit,all 8bit */
    VOS_UINT32                          ulLineLen;
    VOS_UINT32                          ulCurrentLineLen;
    VOS_UINT32                          ulLineLenWithOutEndFlag;
    VOS_BOOL                            bEqualFlag;
    VOS_INT8                            cRet;


    ulLineLen = 0;


    pucOrgData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pucOrgData)
    {
        return MN_ERR_NOMEM;
    }

    /*对短信内容进行7BIT到ASCII码的转换*/
    if (MN_MSG_MSG_CODING_7_BIT == enMsgCoding)
    {
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        TAF_STD_ConvertDefAlphaToAscii(pucMsgData, ulMsgLen, pucOrgData, &ulLineLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    }
    else
    {
        PS_MEM_CPY(pucOrgData, pucMsgData, ulMsgLen);
        ulLineLen = ulMsgLen;
    }

    /*获取激活短信状态字段: 判断当前字符串是否"url:"，不区分大小写
      若包含"url:", 则获取操作成;      否则,获取操作失败;    */
    bEqualFlag  = VOS_FALSE;
    ulStrLen    = VOS_StrLen("url:");
    pucUrlStr   = pucOrgData;
    while (0 != ulLineLen)
    {
        /*确认当前字段是否激活短信状态字段*/
        if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
        {
            MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucUrlStr,
                                                    ulLineLen,
                                                    (VOS_UINT8 *)"url:",
                                                    &bEqualFlag);
            if (VOS_TRUE == bEqualFlag)
            {
                pucUrlStr += (2 * ulStrLen);
                ulLineLen -= (2 * ulStrLen);
                break;
            }

        }
        else
        {
            cRet = VOS_StrNiCmp((VOS_CHAR *)pucUrlStr, "url:", ulStrLen);
            if (0 == cRet)
            {
                bEqualFlag = VOS_TRUE;
                pucUrlStr += ulStrLen;
                ulLineLen -= ulStrLen;
                break;
            }

        }

        /*获取下一个信息行的行首并返回剩余字段长度;*/
        MN_MSG_GetCurrentLineLen(pucUrlStr,
                                 ulLineLen,
                                 enMsgCoding,
                                 &ulCurrentLineLen,
                                 &ulLineLenWithOutEndFlag);

        ulLineLen -= ulCurrentLineLen;
        pucUrlStr += ulCurrentLineLen;
    }

    if (VOS_TRUE == bEqualFlag)
    {
        /*获取URL可能的最大长度*/
        MN_MSG_GetCurrentLineLen(pucUrlStr,
                                 ulLineLen,
                                 enMsgCoding,
                                 &ulCurrentLineLen,
                                 &pstUrl->ulLen);

        /*填写URL到输出参数*/
        PS_MEM_CPY(pstUrl->aucUrl, pucUrlStr, pstUrl->ulLen);
        ulRet = MN_ERR_NO_ERROR;
    }
    else
    {
        ulRet = MN_ERR_UNSPECIFIED;
    }


    PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_WriteActiveMessage
 功能描述  : 写激活短信的信息到NVIM
 输入参数  : MN_MSG_ACTIVE_MESSAGE_STRU     *pstOrgActiveMessageInfo NVIM中的激活短信参数
             MN_MSG_ACTIVE_MESSAGE_STRU     *pstActiveMessageInfo   激活短信参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR 写操作成功；其他，写操作失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_WriteActiveMessage(
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstActiveMessageInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                           *pucActiveMessageInfo;
    VOS_UINT8                           *pucEvaluate;

    /*1.判断待写入的激活短信参数与NVIM中的参数是否一致；一致则不用写NVIM直接退出*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                   pstActiveMessageInfo->stUrl.aucUrl,
                                   pstActiveMessageInfo->stUrl.ulLen);
                if (0 == lRet)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.写激活短信参数到NVIM中*/
    /*2.1 为NVIM存储的数据流申请内存*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 将激活短信参数数据结构转换成NVIM存储的数据流*/
    pucEvaluate = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    PS_MEM_CPY(pucEvaluate,
               pstActiveMessageInfo->stUrl.aucUrl,
               pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 写激活短信信息到NVIM*/
    ulRet = NV_Write(en_NV_Item_SMS_ActiveMessage_Para,
                     pucActiveMessageInfo,
                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReadActiveMessage
 功能描述  : 从NVIM中获取激活短信参数
 输入参数  : MN_MSG_ACTIVE_MESSAGE_STRU          *pstActiveMessage
                激活短信参数；
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR 写操作成功；其他，写操作失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月19日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_ReadActiveMessage(
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstActiveMessage
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucActiveMessageInfo;
    VOS_UINT8                           *pucEvaluate;

    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to alloc memory . ");
        return MN_ERR_NOMEM;
    }

    ulRet = NV_Read(en_NV_Item_SMS_ActiveMessage_Para,
                    pucActiveMessageInfo,
                    MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to read NVIM . ");
        PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
        return MN_ERR_CLASS_SMS_NVIM;
    }

    pucEvaluate = pucActiveMessageInfo;

    pstActiveMessage->enActiveStatus = *pucEvaluate;
    pucEvaluate++;

    pstActiveMessage->enMsgCoding   = *pucEvaluate;
    pucEvaluate++;

    /*lint -e701*/
    pstActiveMessage->stUrl.ulLen   = *pucEvaluate;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 8;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 16;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 24;
    pucEvaluate++;
    /*lint +e701*/

    if (pstActiveMessage->stUrl.ulLen > MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to read NVIM . ");
        pstActiveMessage->stUrl.ulLen = MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN;
    }

    PS_MEM_CPY(pstActiveMessage->stUrl.aucUrl,
               pucEvaluate,
               pstActiveMessage->stUrl.ulLen);

    PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetAndSaveActiveMessageInfo
 功能描述  : 获取并存储激活短信信息到NVIM
 输入参数  : MN_MSG_DELIVER_STRU                 *pstDeliver 解码后的短信
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID MN_MSG_GetAndSaveActiveMessageInfo(
    const MN_MSG_DELIVER_STRU           *pstDeliver
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRemainder;
    VOS_BOOL                            bActiveMessage;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    MN_MSG_ACTIVE_MESSAGE_STRU          stOrgActiveMessageInfo;

    /*If (MN_MSG_IdentfyActiveMessage为假)        Return; */
    MN_MSG_IdentfyActiveMessage(pstDeliver, &bActiveMessage);
    if (VOS_TRUE != bActiveMessage)
    {
        MN_INFO_LOG("MN_MSG_GetAndSaveActiveMessageInfo :not a active message. ");
        return;
    }

    /*记录短信的内容的编码格式: 此处已完成了GSM7bit到8BIT的转换*/
    if (MN_MSG_MSG_CODING_UCS2 == pstDeliver->stDcs.enMsgCoding)
    {
        ulRemainder = pstDeliver->stUserData.ulLen % MN_WORD_UCS2_ENCODE_LEN;
        if (0 != ulRemainder)
        {
            return;
        }

        stActiveMessageInfo.enMsgCoding = MN_MSG_MSG_CODING_UCS2;
    }
    else
    {
        stActiveMessageInfo.enMsgCoding = MN_MSG_MSG_CODING_8_BIT;
    }

    /*MN_MSG_GetActiveStatus获取激活状态信息失败        Return; */
    ulRet = MN_MSG_GetActiveStatus(pstDeliver->stUserData.aucOrgData,
                                   pstDeliver->stUserData.ulLen,
                                   pstDeliver->stDcs.enMsgCoding,
                                   &stActiveMessageInfo.enActiveStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_INFO_LOG("MN_MSG_GetAndSaveActiveMessageInfo :no active status. ");
        return;
    }

    ulRet = MN_MSG_ReadActiveMessage(&stOrgActiveMessageInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return;
    }

    /*MN_MSG_GetActiveUrl获取激活短信URL信息*/
    ulRet = MN_MSG_GetActiveUrl(pstDeliver->stUserData.aucOrgData,
                                pstDeliver->stUserData.ulLen,
                                pstDeliver->stDcs.enMsgCoding,
                                &stActiveMessageInfo.stUrl);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*获取NVIM中记录的激活短信参数*/
        PS_MEM_CPY(&stActiveMessageInfo.stUrl,
                   &stOrgActiveMessageInfo.stUrl,
                   sizeof(stActiveMessageInfo.stUrl));
        stActiveMessageInfo.enMsgCoding = stOrgActiveMessageInfo.enMsgCoding;
    }

    /*记录短信的内容的编码格式: 此处已完成了GSM7bit到8BIT的转换*/
    /*MN_MSG_WriteActiveMessage写激活短信的激活状态和URL信息到NVIM；*/
    ulRet = MN_MSG_WriteActiveMessage(&stOrgActiveMessageInfo, &stActiveMessageInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_GetAndSaveActiveMessageInfo:Fail to Write NVIM.");
    }

    return;

}

/*****************************************************************************
 函 数 名  : MSG_DecodeRpData
 功能描述  : 将一串字节流解码为24011 RP DATA (Network to Mobile Station)定义的结构
 输入参数  : pucRpduContent  :网络发送过来的RP-Data的内容
 输出参数  : pstRpData       :24011 RP DATA定义的结构
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
LOCAL VOS_VOID MSG_DecodeRpData(
    const VOS_UINT8                     *pucRpduContent,
    MN_MSG_RP_DATA_STRU                 *pstRpData
)
{
    VOS_UINT32                          ucIdx = 0;

    /*lint -e961*/
    pstRpData->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpData->ucRpMr = pucRpduContent[ucIdx++];
    if (pucRpduContent[ucIdx] > 0)
    {
        pstRpData->stOrgAddr.ucBcdLen = pucRpduContent[ucIdx++] - 1;
        pstRpData->stOrgAddr.addrType = pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpData->stOrgAddr.aucBcdNum,pucRpduContent+ucIdx,pstRpData->stOrgAddr.ucBcdLen);
        ucIdx += pstRpData->stOrgAddr.ucBcdLen;
    }
    else
    {
        pstRpData->stOrgAddr.ucBcdLen = 0;
        ucIdx++;
    }
    /*lint +e961*/

    if (pucRpduContent[ucIdx] > 0)
    {
        /*lint -e961*/
        pstRpData->stDestAddr.ucBcdLen = pucRpduContent[ucIdx++] - 1;
        pstRpData->stDestAddr.addrType = pucRpduContent[ucIdx++];
        /*lint +e961*/
        PS_MEM_CPY(pstRpData->stDestAddr.aucBcdNum,pucRpduContent+ucIdx,pstRpData->stDestAddr.ucBcdLen);
        ucIdx += pstRpData->stDestAddr.ucBcdLen;
    }
    else
    {
        pstRpData->stDestAddr.ucBcdLen = 0;
        ucIdx++;
    }
    /*lint -e961*/
    pstRpData->ucRpUserDataLen = pucRpduContent[ucIdx++];
    /*lint +e961*/
    PS_MEM_CPY(pstRpData->aucRpUserData,pucRpduContent + ucIdx,pstRpData->ucRpUserDataLen);
}


/*****************************************************************************
 函 数 名  : MSG_DecodeRpAck
 功能描述  : 将一串字节流解码为24011 RP ACK定义的结构
 输入参数  : pucRpduContent:网络发送过来的RP-ACK的内容
             ucRpduvLen:Rp-Ack的长度
             pstRpAck:24011 RP ACK定义的结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID MSG_DecodeRpAck(
    const VOS_UINT8                     *pucRpduContent,
    VOS_UINT8                           ucRpduvLen,
    MN_MSG_RP_ACK_STRU                  *pstRpAck
)
{
    VOS_UINT32                          ucIdx = 0;
    /*lint -e961*/
    pstRpAck->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpAck->ucRpMr = pucRpduContent[ucIdx++];
    if ((ucRpduvLen > 3)
     && (MN_MSG_RP_USER_DATA_IEI == pucRpduContent[ucIdx]))
    {
        pstRpAck->bRpUserDataExist = VOS_TRUE;
        pstRpAck->ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        ucIdx++;
        pstRpAck->ucRpUserDataLen = pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpAck->aucRpUserData,pucRpduContent + ucIdx,pstRpAck->ucRpUserDataLen);
    }
    else
    {
        pstRpAck->bRpUserDataExist = VOS_FALSE;
    }
    /*lint +e961*/
}
/*****************************************************************************
 函 数 名  : MSG_DecodeRpErr
 功能描述  : 将一串字节流解码为24011 RP ERROR定义的结构
 输入参数  : pucRpduContent:网络发送过来的RP-ERROR的内容
             ucRpduvLen:Rp-Error的长度
             pstRpErr:24011 RP ERROR定义的结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/

LOCAL VOS_VOID MSG_DecodeRpErr(
    const VOS_UINT8                     *pucRpduContent,
    VOS_UINT8                           ucRpduvLen,
    MN_MSG_RP_ERR_STRU                  *pstRpErr
)
{
    VOS_UINT32                          ucIdx = 0;
    /*lint -e961*/
    pstRpErr->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpErr->ucRpMr = pucRpduContent[ucIdx++];
    pstRpErr->ucRpCauseLen = pucRpduContent[ucIdx++];
    pstRpErr->stRpCause.enRpCause = pucRpduContent[ucIdx++];
    if (1 == pstRpErr->ucRpCauseLen)
    {
        pstRpErr->stRpCause.bDiagnosticsExist = VOS_FALSE;
    }
    else
    {
        pstRpErr->stRpCause.bDiagnosticsExist = VOS_TRUE;
        pstRpErr->stRpCause.ucDiagnostics = pucRpduContent[ucIdx++];
    }
    if ((ucRpduvLen > (ucIdx + 1))
     && (MN_MSG_RP_USER_DATA_IEI == pucRpduContent[ucIdx]))
    {
        pstRpErr->bRpUserDataExist = VOS_TRUE;
        pstRpErr->ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        ucIdx++;
        pstRpErr->ucRpUserDataLen= pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpErr->aucRpUserData,pucRpduContent + ucIdx,pstRpErr->ucRpUserDataLen);
    }
    else
    {
        pstRpErr->bRpUserDataExist = VOS_FALSE;
    }
    /*lint +e961*/
}

/*****************************************************************************
 函 数 名  : MSG_JudgeRetryFlg
 功能描述  : 判断当前是否需要进行重发
 输入参数  :无
 输出参数  : 无
 返 回 值  :  MN_MSG_RETRY_OFF:重发功能未开启
              MN_MSG_RETRY_END:重发已经结束
              MN_MSG_RETRY_BEGIN:重发准备开始
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月6日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年03月01日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                 服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
  3.日    期   : 2011年3月29日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011030500602，增加CS域可用的判断标准，UE服务域为非PS
                 ONLY, IMSI在CS域有效且CS域未被BAR情况下可以尝试重发，支持在PS域重发短信
  4.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
LOCAL MN_MSG_RETRY_FLAG_U8 MSG_JudgeRetryFlg(VOS_VOID)
{
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;
    VOS_UINT32                          ulRemainTimeTick;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);

    /* 当前没有设置重发 */
    if ((0 == stRetryInfo.ulRetryPeriod) || (0 == stRetryInfo.ulRetryInterval))
    {
        return MN_MSG_RETRY_OFF;
    }

    ulRemainTimeTick = MN_MSG_GetTimerRemainTime(MN_MSG_ID_WAIT_RETRY_PERIOD);
    if (ulRemainTimeTick == 0)
    {
        return MN_MSG_RETRY_END;
    }

    if (((VOS_INT32)(ulRemainTimeTick - stRetryInfo.ulRetryInterval)) <= 0)
    {
        return MN_MSG_RETRY_END;
    }

    return MN_MSG_RETRY_BEGIN;
}

/*****************************************************************************
 函 数 名  : MSG_CheckSmsTpErrorRetry
 功能描述  : 判断MO短信TP拒绝原因值是否需要重发
 输入参数  : VOS_UINT32
 输出参数  : 无
 返回值    : PS_TRUE: 需要重试；
             PS_FALSE: 不需要重试；
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : j00174725
    修改内容   : DTS2015052201409
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MSG_CheckSmsTpErrorRetry(
    VOS_UINT32                          ulFailCause
)
{
    VOS_UINT32                          ulCause;
    PS_BOOL_ENUM_UINT8                  enRet;

    enRet = PS_TRUE;

    /* 判断是否是TP ERROR */
    if (TAF_MSG_ERROR_TP_ERROR_BEGIN  != (ulFailCause & TAF_MSG_ERROR_TP_ERROR_BEGIN))
    {
        return PS_TRUE;
    }

    ulCause = ulFailCause & (~TAF_MSG_ERROR_TP_ERROR_BEGIN);

    switch(ulCause)
    {
        /* 拒绝原因为 SM Rejected-Duplicate SM 则不需要重发 */
        case MN_MSG_TP_CAUSE_REJECTED_DUPLICATE_SM:
            enRet = PS_FALSE;
            break;

        default:
            enRet = PS_TRUE;
            break;
    }

    return enRet;
}

/*****************************************************************************
 函 数 名  : MSG_IsProcessRetry
 功能描述  : 判断当前是否已经进行重发
 输入参数  :无
 输出参数  : 无
 返 回 值  :  VOS_TRUE:进行重发
              VOS_FALSE:未进行重发
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月6日
    作    者   : 周君 40661
    修改内容   : 新生成函数

  2.日    期   : 2010年5月7日
    作    者   : zhoujun /z40661
    修改内容   : AT2D19153，重发时间不够时，未能停止定时器
  3.日    期   : 2012年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012110604069，TAF层重发的SUBMIT短信TP-RD应该修改为1，
                 指示短信中心拒绝接收重复短信
  4.日    期   : 2013年7月15日
     作    者   : y00245242
     修改内容   : 从消息实体中获取路由标识，决定重试路由标识
  5.日    期   : 2013年10月22日
    作    者   : w00167002
    修改内容   : NETSCAN: 增加enErrCause，在CS短信失败时候，需要根据失败原因值来
                 判定是否需要短信重发。
  6.日    期   : 2015年05月23日
    作    者   : j00174725
    修改内容   : DTS2015052201409
*****************************************************************************/

LOCAL VOS_BOOL MSG_IsProcessRetry(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause,
    VOS_UINT32                          ulMoFailCause
)
{
    MN_MSG_RETRY_FLAG_U8                enRetryFlg = MN_MSG_RETRY_OFF;
    VOS_UINT32                          ulRet;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enOldSendDomain;

    /* 判断TP 错误原因值是否需要重试 */
    if ( PS_FALSE == MSG_CheckSmsTpErrorRetry(ulMoFailCause))
    {
        return VOS_FALSE;
    }

    enRetryFlg = MSG_JudgeRetryFlg();


    /* 当前NV未开启重发，判断是否需要通过另一个域进行发送 */
    if (MN_MSG_RETRY_OFF == enRetryFlg)
    {
        /* 重发存在两种情况,一个域发送失败通过另外一个域发送,
        但当CS域发送失败后,PS域发送成功,此时会先通过PS域发送
        PS域发送失败了,仍然需要通过CS域发送*/
        /* 重发功能关闭,判断是否需要重另外一个域发送 */
        if ( ((MN_MSG_SEND_DOMAIN_PS_PREFERRED == pstMoEntity->enHopeSendDomain)
            && (MN_MSG_SEND_DOMAIN_PS == pstMoEntity->enSendDomain))
          ||((MN_MSG_SEND_DOMAIN_CS_PREFERRED == pstMoEntity->enHopeSendDomain)
            && (MN_MSG_SEND_DOMAIN_CS == pstMoEntity->enSendDomain)))
        {
            enOldSendDomain = pstMoEntity->enSendDomain;
            MN_MSG_GetCurSendDomain(pstMoEntity->enHopeSendDomain,&(pstMoEntity->enSendDomain));
            /* 获取新的发送域和老的不一致才需要进行重发 */
            if (MN_MSG_SEND_DOMAIN_NO != pstMoEntity->enSendDomain)
            {
                if (pstMoEntity->enSendDomain != enOldSendDomain)
                {
                    /* TAF层重发的SUBMIT短信TP-RD应该修改为1，指示短信中心拒绝接收重复短信 */
                    MN_MSG_SetTpRd(pstMoEntity);

                    /*将一条完整的RP-Data发送给NAS层的SMS模块*/
                    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
                    ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                                    pstMoEntity->aucRpDataInfo,
                                                    pstMoEntity->ucRpDataLen,
                                                    pstMoEntity->enMsgSignallingType);
                    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

                    if (VOS_OK == ulRet)
                    {
                        /* 更新MO变量 */
                        MN_MSG_CreateMoInfo(pstMoEntity);
                        return VOS_TRUE;
                    }
                }
            }
        }

        return VOS_FALSE;
    }

    if ( (VOS_TRUE          == MN_MSG_IsGuNeedSmsRetry(enErrCause))
      && (MN_MSG_RETRY_BEGIN == enRetryFlg) )
    {
        /* 需要进行重发,启动重发间隔定时器,定时器超时后再进行重发 */
        MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL, 0);

        return VOS_TRUE;
    }

    /* 重发过程结束,不需要进行任何操作,停止定时器 */
    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);

    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL);

    return VOS_FALSE;


}


/*****************************************************************************
 函 数 名  : MSG_CreateEFSmsrContent
 功能描述  : 根据TPDU创建一条短信状态报告,短信状态报告格式为USIM卡中EFSMSR的格式
 输入参数  : pstRawData:TPDU的内容
             ucIndex:存入的位置
 输出参数  : pucContent:短信状态报告内容,USIM卡中EFSMSR的格式
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_CreateEFSmsrContent(
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucContent
)
{
    *pucContent = ucIndex;
    if (pstRawData->ulLen > (MN_MSG_EFSMSR_LEN - 1))
    {
        PS_MEM_CPY(pucContent + 1,pstRawData->aucData,MN_MSG_EFSMSR_LEN - 1);
    }
    else
    {
        PS_MEM_CPY(pucContent + 1,pstRawData->aucData,pstRawData->ulLen);
    }
}

/*****************************************************************************
 函 数 名  : MSG_FindReplaceSms
 功能描述  :
 输入参数  : pstOrigAddr: 新短信的TP-OA
             enPid      : 新短信的TP-PID
 输出参数  : pulIndex:    待替换的短信存储位置
 返 回 值  : VOS_UINT32
                VOS_OK    找到了待替换的短信；
                其他，    没有找到待替换的短信；
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年11月28日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2012112706267，短信替换功能修改为先在MODEM所有存储介质中尝试替换，
                 找不到可替换短信则按普通短信处理；
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
LOCAL VOS_UINT32 MSG_FindReplaceSms(
    const MN_MSG_ASCII_ADDR_STRU       *pstOrigAddr,
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRecCount;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucScaLen;                               /* Sca的长度 */
    VOS_UINT8                           *pucTpdu;                               /* 指向Tpdu的指针 */
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    ucStatus = EF_SMS_STATUS_FREE_SPACE;
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                             sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        return VOS_ERR;
    }

    ulRecCount = MN_MSG_GetSmCapacity(enMemStore);
    for (i = 0; i < ulRecCount; i++)
    {
        PS_MEM_SET(&stRawData,0X00,sizeof(stRawData));
        PS_MEM_SET(pstTsDataInfo,0X00,sizeof(MN_MSG_TS_DATA_INFO_STRU));
        ulRet = MN_MSG_GetStatus(enMemStore,i,&ucStatus);
        if ((MN_ERR_NO_ERROR == ulRet)
         && (((ucStatus & 0x03) == EF_SMS_STATUS_MT_READ)
          || ((ucStatus & 0x03) == EF_SMS_STATUS_MT_TO_BE_READ)))
        {

            PS_MEM_SET(aucSmContent, 0x00, sizeof(aucSmContent));

            ulRet = MN_MSG_ReadSmsInfo(enMemStore,i,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                continue;
            }

            ucScaLen = aucSmContent[1];
            pucTpdu = aucSmContent + 1 + 1 + ucScaLen;
            if ( MN_MSG_TP_MTI_DELIVER != ( *pucTpdu & 0x03 ))
            {
                continue;
            }
            stRawData.enTpduType = MN_MSG_TP_MTI_DELIVER;
            stRawData.ulLen = (MN_MSG_EFSMS_LEN - ucScaLen) - 1;


            if ( stRawData.ulLen > sizeof(stRawData.aucData) )
            {
                stRawData.ulLen = sizeof(stRawData.aucData);
            }

            PS_MEM_CPY(stRawData.aucData,pucTpdu,stRawData.ulLen);
            ulRet = MN_MSG_Decode(&stRawData,pstTsDataInfo);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                continue;
            }
            ulRet = (VOS_UINT32)VOS_MemCmp(pstOrigAddr, &(pstTsDataInfo->u.stDeliver.stOrigAddr),sizeof(MN_MSG_ASCII_ADDR_STRU));
            if ((enPid == pstTsDataInfo->u.stDeliver.enPid)
             && (0 == ulRet))
            {
                *pulIndex = i;
                PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
                return VOS_OK;
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);

    return VOS_ERR;
}

/***********************************************************************
函 数 名  : MSG_SearchReplacedSms
功能描述  : 当pid是"Short Message Type 1-7",寻找存储器中是否有可替代的短信
输入参数  : stOrigAddr:TP-OA
            enPid:TP-PID
输出参数  : penMemStore:短信的存储位置,NVIM或USIM
            pulIndex:需要替代短信的索引
返 回 值  : VOS_OK:找到短信需要替代
            VOS_ERR:未能找到短信需要替代
调用函数  :
被调函数  :
修改历史      :
  1.日    期   : 2007年12月06日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年6月10日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011061006066, EM三期短信定制需求
  3.日    期   : 2011年9月20日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011092002791，ME短信替换功能错误，导致重复接收的替换短信接收失败
  4.日    期   : 2012年11月28日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012112706267，短信替换功能修改为先在MODEM所有存储介质中尝试替换，
                 找不到可替换短信则按普通短信处理；
************************************************************************/
LOCAL VOS_UINT32 MSG_SearchReplacedSms(
    const MN_MSG_ASCII_ADDR_STRU       *pstOrigAddr,
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_MEM_STORE_ENUM_U8           *penMemStore,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucActFlg;

    MN_MSG_GetReplaceFeature(&ucActFlg);
    if (MN_MSG_NVIM_ITEM_ACTIVE != ucActFlg)
    {
        return VOS_ERR;
    }

    ulRet = MSG_FindReplaceSms(pstOrigAddr, enPid, MN_MSG_MEM_STORE_SIM, pulIndex);
    if (VOS_OK == ulRet)
    {
        *penMemStore = MN_MSG_MEM_STORE_SIM;
        return VOS_OK;
    }

    ulRet = MSG_FindReplaceSms(pstOrigAddr, enPid, MN_MSG_MEM_STORE_NV, pulIndex);
    if (VOS_OK == ulRet)
    {
        *penMemStore = MN_MSG_MEM_STORE_NV;
        return VOS_OK;
    }

    return VOS_ERR;
}

/***********************************************************************
函 数 名  : MSG_ProcReplaceSm
功能描述  : 处理REPLACE属性的短信接收
输入参数  : pstCfgParm:当前短信参数的配置
            pstScAddr:短信中心的地址
            pstRawData:TPDU的内容
            pstTsData:TPDU解析后的内容
输出参数  : 无
返 回 值  : VOS_TRUE    短信替换成功
            VOS_FALSE   不是替换属性短信，或没有可替换的短信
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2012年11月26日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MSG_ProcReplaceSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcopId;
#endif
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    /* 短信不是Replace类型的，返回VOS_FALSE   不是替换属性短信，或没有可替换的短信 */
    if (((MN_MSG_TP_PID_REPLACE_SM_1 <= (VOS_UINT8)pstTsData->u.stDeliver.enPid )
       && (MN_MSG_TP_PID_REPLACE_SM_7 >= (VOS_UINT8)pstTsData->u.stDeliver.enPid))
      || (MN_MSG_TP_PID_RETURN_CALL == (VOS_UINT8)pstTsData->u.stDeliver.enPid))
    {
        ;
    }
    else
    {
        return VOS_FALSE;
    }

    /* 没有可替换的短信，返回VOS_FALSE   不是替换属性短信，或没有可替换的短信 */
    /* 此处需要对比标杆确认是否遍历所有MODEM的存储介质 */
    ulRet = MSG_SearchReplacedSms(&(pstTsData->u.stDeliver.stOrigAddr),
                                  pstTsData->u.stDeliver.enPid,
                                  &enMemStore,
                                  &ulSaveIndex);
    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    MN_MSG_CreateEFSmContent(pstScAddr,
                             pstRawData,
                             EF_SMS_STATUS_MT_TO_BE_READ,
                             aucSmContent);

    /* 用新收到的短信替换已经存储短信 */
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
|| (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = MN_CLIENT_ALL;
    stSmaUsimInfo.opId = 0;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
    ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
        stWriteUsimInfo.stUsimInfo.opId = 0;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(enMemStore, VOS_NULL_PTR, &stWriteUsimInfo, aucSmContent);

    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(enMemStore, &ulSaveIndex, VOS_NULL_PTR, aucSmContent);
    }
#endif

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        MN_WARN_LOG("MSG_ProcStoreSm:MN_MSG_WriteSmsFile Return Error");
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == pstCfgParm->enSmMemStore)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        /*广播上报来一条短信*/
        bcopId = MN_MSG_GetBCopId();
        stDeliverEvt.ulInex = ulSaveIndex;
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*广播上报NVIM中短信已发生了改变*/
        MN_MSG_ReportSmChanged(MN_CLIENT_ALL,bcopId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
    }
#endif
    else
    {
    }

    return VOS_TRUE;
}

/***********************************************************************
函 数 名  : MSG_ProcClass2Msg
功能描述  : 处理CLASS 2类型的短信
输入参数  : pstCfgParm:当前短信参数的配置
            pstScAddr:短信中心的地址
            pstRawData:TPDU的内容
            pstTsData:TPDU解析后的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2008年01月18日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年3月21日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011031105471，短信溢出存储介质总是SM，没有对ME存储溢出显示问题
 3.日    期   : 2011年11月08日
   作    者   : 傅映君/f62575
   修改内容   : DTS2012111201995，DCM短信接收定制需求

************************************************************************/
LOCAL VOS_VOID MSG_ProcClass2Msg(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData
)
{
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    MN_INFO_LOG("MSG_ProcClass2Msg: step into function. ");
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);

    ulSaveIndex = MN_MSG_GetAvailSmRecIndex(MN_MSG_MEM_STORE_SIM);

    /*当前USIM卡已满 (此处参考协议23038)*/
    MN_NORM_LOG1("MSG_ProcClass2Msg: ucSaveIndex is ", (VOS_INT32)ulSaveIndex);
    if (MN_MSG_NO_AVAILABLE_SMS_REC != ulSaveIndex)
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = MN_CLIENT_ALL;
        stSmaUsimInfo.opId = 0;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        ulRet = MN_MSG_WriteSmsFile(MN_MSG_MEM_STORE_SIM,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
        stWriteUsimInfo.stUsimInfo.opId = 0;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(MN_MSG_MEM_STORE_SIM,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_ProcClass2Msg:Save Class 2 in Usim Error");
        }
        return;
    }

    MN_MSG_FailToWriteEfsms(MN_MSG_MEM_STORE_SIM, MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
}

/***********************************************************************
函 数 名  : MSG_ProcStoreSm
功能描述  : 处理需要存储在USIM或NVIM中的短信
输入参数  : pstCfgParm:当前短信参数的配置
            pstScAddr:短信中心的地址
            pstRawData:TPDU的内容
            pstTsData:TPDU解析后的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2008年01月18日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2009年12月9日
   作    者   : f62575
   修改内容   : 问题单号:AT2D15782, 短信接收流程写EFSMS文件失败分支代码冗余
 3.日    期   : 2011年3月21日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011031105471，短信溢出存储介质总是SM，没有对ME存储溢出显示问题
 4.日    期   : 2011年9月20日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011092002791，ME短信替换功能错误，导致重复接收的替换短信接收失败
 5.日    期   : 2011年11月08日
   作    者   : 傅映君/f62575
   修改内容   : DTS2012111201995，DCM短信接收定制需求
************************************************************************/
LOCAL VOS_VOID MSG_ProcStoreSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcopId;
#endif
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);

    ulSaveIndex = MN_MSG_GetAvailSmRecIndex(pstCfgParm->enSmMemStore);

    /*当前存储器已满,没有合法的ucSaveIndex*/
    if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
    {
        MN_MSG_FailToWriteEfsms(pstCfgParm->enSmMemStore,
                                MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
    }
    else
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = MN_CLIENT_ALL;
        stSmaUsimInfo.opId = 0;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstCfgParm->enSmMemStore)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
            stWriteUsimInfo.stUsimInfo.opId = 0;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
            stWriteUsimInfo.bCreateNode = VOS_TRUE;
            ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,&ulSaveIndex,VOS_NULL_PTR,aucSmContent);
        }
#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_ProcStoreSm:MN_MSG_WriteSmsFile Return Error");
        }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        else if (MN_MSG_MEM_STORE_NV == pstCfgParm->enSmMemStore)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
            /*广播上报来一条短信*/
            bcopId = MN_MSG_GetBCopId();
            stDeliverEvt.ulInex = ulSaveIndex;
            MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
            /*广播上报NVIM中短信已发生了改变*/
            MN_MSG_ReportSmChanged(MN_CLIENT_ALL,bcopId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
#endif
        else
        {
        }
    }
}

/***********************************************************************
函 数 名  : MSG_ProcNoClassSm
功能描述  : 处理无CLASS类型的短信
输入参数  : pstCfgParm:当前短信参数的配置
            pstScAddr:短信中心的地址
            pstRawData:TPDU的内容
            pstTsData:TPDU解析后的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2008年01月18日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月08日
   作    者   : 傅映君/f62575
   修改内容   : DTS2012111201995，DCM短信接收定制需求
 3.日    期   : 2013年10月17日
   作    者   : w00167002
   修改内容   : NETSCAN:在<MT>=3，收到CLASS3短信时候，按照+CMT方式上报。
 4.日    期   : 2014年4月2日
   作    者   : w00242748
   修改内容   : DTS2014040201835:删除无效打印
************************************************************************/
LOCAL VOS_VOID MSG_ProcNoClassSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;

    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received msg*/

    MN_INFO_LOG("MSG_ProcNoClassSm: Step into function.");
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);
    bcopId = MN_MSG_GetBCopId();
    MN_NORM_LOG1("MSG_ProcNoClassSm: pstCfgParm->enRcvSmAct is ", pstCfgParm->enRcvSmAct);



    /* 默认取配置中的SmAct,在<MT>=3,收到的是CLASS3短信时候，需要修改按照+CMT方式上报 */
    enRcvSmAct = pstCfgParm->enRcvSmAct;


    /* CLASS3类型短信按照+CMT方式上报 */
    if ( ( (MN_MSG_RCVMSG_ACT_STORE    == pstCfgParm->enRcvSmAct)
        && (MN_MSG_CNMI_MT_CLASS3_TYPE  == pstCfgParm->enMtType))
      && (MN_MSG_MSG_CLASS_3            == pstTsData->u.stDeliver.stDcs.enMsgClass) )
    {
        enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK;

        if ( MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS == pstCfgParm->enSmsServVersion )
        {
            enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
        }
    }

    if (MN_MSG_RCVMSG_ACT_DISCARD == enRcvSmAct)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_INFO_LOG("MSG_ProcNoClassSm:Rcv Sm but enRcvSmAct is MN_MSG_RCVMSG_ACT_DISCARD");
    }
    else if (MN_MSG_RCVMSG_ACT_STORE == enRcvSmAct)
    {
        MSG_ProcStoreSm(pstCfgParm,pstScAddr,pstRawData,pstTsData);
    }
    else if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY == enRcvSmAct)
    {
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;

        /*广播上报来一条短信*/
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*创建收短信相关信息*/
        MN_MSG_CreateMtInfo();

    }
    else
    {
        MN_MSG_GetCurAppMemStatus(&enAppMemStatus);
        MN_NORM_LOG1("MSG_ProcNoClassSm: enAppMemStatus is ", enAppMemStatus);
        if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_MEMORY_EXCEEDED,
                                    MN_MSG_TP_CAUSE_MEMORY_FULL);

            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

            MN_WARN_LOG("MSG_ProcNoClassSm:Rcv New Msg but App Mem Full");
        }
        else
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);


            /* 通知AT进行+CMT方式存储 */
            stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
            stDeliverEvt.ulInex     = 0;

            MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        }
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_RcvAndStoreClass0Msg
 功能描述  : 接收并保存CLASS0类短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月15日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID MN_MSG_RcvAndStoreClass0Msg(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    MN_MSG_CLASS0_TAILOR_U8             enClass0Tailor;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    MN_OPERATION_ID_T                   bcopId;

    /* 获取Class0短信定制 */
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);

    enClass0Tailor = MN_MSG_GetClass0Tailor();
    if (MN_MSG_CLASS0_VODAFONE == enClass0Tailor)
    {
        /* Vodafone Class0 短信定制,存储方式与class 2短信类似,
        亦即当有新class 0短信到来的时候，直接将短信存储到SIM卡中，
        不受CNMI以及CPMS设置的影响，同时采用＋CMTI上报短信存储位置。*/
        MSG_ProcClass2Msg(pstScAddr,pstRawData);
        return;
    }

    /*1: Italy TIM Class0 短信定制（即H3G Class0 短信定制）
        H3G与意大利TIM Class 0短信需求相同，不对短信进行存储，
        要求将CLASS 0 短信直接采用+CMT进行主动上报。不受CNMI
        以及CPMS设置的影响，如果后台已经打开，则后台对CLASS 0短信进行显示。
      2：27005协议CNMI指定处理方式
      <MT>为0存储到（U）SIM卡但不在AT端口上报；
      <MT>为1存储到（U）SIM卡并且在AT端口上报存储位置（即CMTI方式上报）；
      <MT>为2不存储到（U）SIM卡但会在AT端口上报短信内容（即CMT方式上报）；
      <MT>为3存储到（U）SIM卡并且在AT端口上报存储位置（即CMTI方式上报）；
      这两种情况只是在AT上的显示不一样,所以此处不需要进行任何处理
    */
    else if (MN_MSG_CLASS0_TIM == enClass0Tailor)
    {
        if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY != pstCfgParm->enRcvSmAct)
        {
            /* TIM和VIVO定制的差异:在<MT>=1/3时,即使CSMS=1，也不需要+CNMA ACK */
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        }
        else
        {
            /*如果是有应用回复Rp-Report,创建收短信相关信息*/
            MN_MSG_CreateMtInfo();
        }
        bcopId                  = MN_MSG_GetBCopId();
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;
        MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);
    }
    else if (MN_MSG_CLASS0_VIVO == enClass0Tailor)
    {
        if (MN_MSG_CSMS_MSG_VERSION_PHASE2 == pstCfgParm->enSmsServVersion)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        }
        else
        {
            /*如果是有应用回复Rp-Report,创建收短信相关信息*/
            MN_MSG_CreateMtInfo();
        }
        bcopId                  = MN_MSG_GetBCopId();
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;
        MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);
    }
    else
    {
        MSG_ProcNoClassSm(pstCfgParm, pstScAddr,pstRawData, pstTsData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MSG_IsRequireDownloadMsg
 功能描述  : 判断接收到的短信是否要求DOWNLOAD
 输入参数  : const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
 输出参数  : 无
 返 回 值  : VOS_TRUE 要求DOWNLOAD
             VOS_FALSE 不要求DOWNLOAD

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE
*****************************************************************************/
LOCAL VOS_UINT32 MSG_IsRequireDownloadMsg(
    const MN_MSG_TS_DATA_INFO_STRU     *pstTsData
)
{
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr = VOS_NULL_PTR;
    MN_MSG_USIM_EFUST_INFO_STRU         stEfUstInfo;

    PS_MEM_SET(&stEfUstInfo,0X00,sizeof(stEfUstInfo));
    MN_MSG_ReadUstInfo(&stEfUstInfo);

    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: pstCustomCfgAddr->ucSmsPpDownlodSupportFlg ", (VOS_INT32)pstCustomCfgAddr->ucSmsPpDownlodSupportFlg);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: stEfUstInfo.bSmsPpDataFlag is ", (VOS_INT32)stEfUstInfo.bSmsPpDataFlag);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: enPid is ", pstTsData->u.stDeliver.enPid);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: enMsgClass is ", pstTsData->u.stDeliver.stDcs.enMsgClass);

    /* 此处需要钩包输出ucSmsPpDownlodSupportFlg，bSmsPpDataFlag，enMsgClass和enPid数据 */

    /* NV项配置为MODEM不支持PP-DOWNLOAD功能，忽略DOWNLOAD属性 */
    if (MN_MSG_NV_ITEM_ACTIVE != pstCustomCfgAddr->ucSmsPpDownlodSupportFlg)
    {
        return VOS_FALSE;
    }

    /* (U)SIM配置不支持PP-DOWNLOAD功能，忽略DOWNLOAD属性 */
    if (VOS_TRUE != stEfUstInfo.bSmsPpDataFlag)
    {
        return VOS_FALSE;
    }

    /* 是OTA短信，要求DOWNLOAD */
    if ((MN_MSG_MSG_CLASS_2 == pstTsData->u.stDeliver.stDcs.enMsgClass)
     && ((MN_MSG_TP_PID_SIM_DATA_DOWNLOAD == pstTsData->u.stDeliver.enPid)
      || (MN_MSG_TP_PID_ANSI136_R_DATA == pstTsData->u.stDeliver.enPid)))
    {
        return VOS_TRUE;
    }

    /* 非OTA短信，不要求DOWNLOAD */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MSG_IsVsimCtrlDiscardMsg
 功能描述  : 判断接收到的短信VSIM特性是否要求丢弃
 输入参数  : const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
 输出参数  : 无
 返 回 值  : VOS_TRUE 要求丢弃
             VOS_FALSE 不要求丢弃

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE
*****************************************************************************/
LOCAL VOS_UINT32 MSG_IsVsimCtrlDiscardMsg(
    const MN_MSG_TS_DATA_INFO_STRU     *pstTsData
)
{
    VOS_UINT32                          ulRet;

    /* 未启用VSIM控制流程 */
    ulRet = NAS_VSIM_IsRequireVsimCtrl();
    if (VOS_TRUE != ulRet)
    {
        return VOS_FALSE;
    }

    /* 要求DOWNLOAD的短信不受VSIM特性控制 */
    ulRet = MSG_IsRequireDownloadMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MSG_ProcSmsDeliver
 功能描述  : 对收到的Deliver的短信进行处理
 输入参数  : pstScAddr:短信中心的地址
             pstRawData:短信的TPDU
             pstTsData:解析TPDU后的数据
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : AT2D16304, STK PP DOWN功能完善和SMS相关的(U)SIM文件REFRESH
  3.日    期   : 2010年4月15日
    作    者   : f62575
    修改内容   : AT2D18550, 重复接收到TP-PID为011111（Return Call Message）
                 的消息没有用新消息替换旧消息
  4.日    期   : 2011年6月10日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011061006066, EM三期短信定制需求
  5.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : V7R1 C30 SBM&EM定制需求:增加关闭短信功能定制
  5.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  6.日    期   : 2013年6月19日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
  7.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  8.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE
*****************************************************************************/
LOCAL VOS_VOID MSG_ProcSmsDeliver(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_UINT8                            ucRcvDomain
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    VOS_BOOL                            bSupportFlag;
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause;

    /* Added by w00176964 for V7R1 SBM&EM定制需求, 2012-3-17, begin */
    VOS_UINT8                           ucCloseSmsFlg;
    /* Added by w00176964 for V7R1 SBM&EM定制需求, 2012-3-17, end */

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    /*获取当前的短信的配置参数*/
    MN_MSG_GetCurCfgParm(&stCfgParm);

    MN_NORM_LOG1("MSG_ProcSmsDeliver: stCfgParm.enRcvSmAct is ", stCfgParm.enRcvSmAct);
    MN_NORM_LOG1("MSG_ProcSmsDeliver: enPid is ", pstTsData->u.stDeliver.enPid);
    MN_NORM_LOG1("MSG_ProcSmsDeliver: enMsgClass is ", pstTsData->u.stDeliver.stDcs.enMsgClass);

    f_ulMsgMtNum++;

    /* VSIM特性要求丢弃的短信，退出短信接收流程 */
    /* 启用VSIM控制流程时，非DOWNLOAD的短信，直接丢弃 */
    ulRet = MSG_IsVsimCtrlDiscardMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_NORM_LOG("MSG_DiscardVsimCtrlMsg: VSIM feature discard deliver message.");

        return;
    }

    MN_MSG_GetAndSaveActiveMessageInfo(&pstTsData->u.stDeliver);

    /* Modified by w00176964 for V7R1 SBM&EM定制需求, 2012-3-17, begin */
    /* 当前短信功能是否支持 */
    MN_MSG_GetCloseSMSFeature(&ucCloseSmsFlg);

    /*pid是"Short Message Type 0" (根据协议23040，该条短消息不进行保存，也不向应用层上报)*/
    if ((MN_MSG_TP_PID_SM_TYPE_0 == pstTsData->u.stDeliver.enPid)
     || (MN_MSG_NVIM_ITEM_ACTIVE == ucCloseSmsFlg))
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_NORM_LOG("MSG_ProcSmsDeliver:Pid = MN_MSG_TP_PID_SM_TYPE_0,Discard it");
        return;
    }
    /* Modified by w00176964 for V7R1 SBM&EM定制需求, 2012-3-17, end */

    MN_MSG_DeliverMsgNotSupport(pstTsData, &bSupportFlag, &enTpCause);
    if (VOS_FALSE == bSupportFlag)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE, MN_MSG_RP_CAUSE_IE_NON_EXISTENT, enTpCause);
        MN_NORM_LOG1("MSG_ProcSmsDeliver: deliver message is not supported. enTpCause is ", enTpCause);
        return;
    }

    /* 更新MT时的接收域，只有在状态不为MN_MSG_MT_STATE_NULL时才有效 */
    TAF_MSG_UpdateMtRcvDomain(ucRcvDomain);

    /*TP-PID为Replace Short Message Type 1-Replace Short Message Type 7或Return Call Message
    用新接收到的短信替换之前存储的短信*/
    if (VOS_TRUE == MSG_ProcReplaceSm(&stCfgParm,pstScAddr,pstRawData,pstTsData))
    {
        return;
    }

    /*(pid是(U)SIM Data download || pid是MN_MSG_TP_PID_ANSI136_R_DATA) && 该条短信是
    Class 2类型的 &&支持Data download via SMS-PP(不支持,则按照Class 2短信保留在USIM中)*/
    ulRet = MSG_IsRequireDownloadMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_SetMtTpPidAndDcs(pstTsData->u.stDeliver.enPid, pstTsData->u.stDeliver.stDcs);
        ulRet = MN_MSG_SmsPPEnvelopeReq(pstScAddr,pstRawData->aucData, pstRawData->ulLen);
        if (VOS_ERR == ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
        }
        return;
    }

    /*Class 2类型的短信只能存储在USIM中*/
    if (MN_MSG_MSG_CLASS_2 == pstTsData->u.stDeliver.stDcs.enMsgClass)
    {
        MSG_ProcClass2Msg(pstScAddr,pstRawData);
    }

    /*Class 0类型的短信的接收和存储*/
    else if (MN_MSG_MSG_CLASS_0 == pstTsData->u.stDeliver.stDcs.enMsgClass)
    {
        MN_MSG_RcvAndStoreClass0Msg(&stCfgParm,pstScAddr,pstRawData,pstTsData);
    }

    /*无Class类型的短信的接收和存储*/
    else
    {
        MSG_ProcNoClassSm(&stCfgParm,pstScAddr,pstRawData,pstTsData);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetStatusReportStorageInfo
 功能描述  : 获取短信状态报告存储位置
 输入参数  : 无
 输出参数  : MN_MSG_STORAGE_INFO_STRU            *pstStorageInfo 短信状态报告存储参数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数  DTS2011060803050 STATUS REPORT in ME
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_VOID MN_MSG_GetStatusReportStorageInfo(
    MN_MSG_STORAGE_INFO_STRU            *pstStorageInfo
)
{
    VOS_UINT32                          ulSmsrIndex;
    VOS_UINT32                          ulSmsrCapacity;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    MN_MSG_GetCurCfgParm(&stCfgParm);
    pstStorageInfo->enRcvSmAct = stCfgParm.enRcvStaRptAct;

    if (MN_MSG_RCVMSG_ACT_STORE != pstStorageInfo->enRcvSmAct)
    {
        return;
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
    {
        pstStorageInfo->usFileIndex = (VOS_UINT16)ulFileId[1];
        pstStorageInfo->enMemStore  = stCfgParm.enStaRptMemStore;
        pstStorageInfo->ulIndex     = MN_MSG_NO_AVAILABLE_SMS_REC;

        ulSmsrCapacity = MN_MSG_GetSmsrCapacity(stCfgParm.enStaRptMemStore);
        if (0 != ulSmsrCapacity)
        {
            ulSmsrIndex = MN_MSG_GetAvailSmsrRecIndex(stCfgParm.enStaRptMemStore);
            if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSmsrIndex)
            {
                MN_INFO_LOG("MN_MSG_GetStatusReportStorageInfo: Rcv StatusReport No Free smsr record.");
                /*若无空闲位置,则直接找到替换的一条短信状态报告的索引*/
                ulSmsrIndex = MN_MSG_GetReplaceSmsrRecIndex(stCfgParm.enStaRptMemStore);
            }

            pstStorageInfo->ulIndex = ulSmsrIndex;

        }

        if (MN_MSG_NO_AVAILABLE_SMS_REC == pstStorageInfo->ulIndex)
        {
            if (MN_MSG_CSMS_MSG_VERSION_PHASE2 == stCfgParm.enSmsServVersion)
            {
                pstStorageInfo->enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK;
            }
            else
            {
                pstStorageInfo->enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
            }

        }

    }
    else
    {
        pstStorageInfo->enMemStore  = stCfgParm.enSmMemStore;
        pstStorageInfo->usFileIndex = (VOS_UINT16)ulFileId[0];
        pstStorageInfo->ulIndex     = MN_MSG_GetAvailSmRecIndex(stCfgParm.enSmMemStore);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_StoreStatusReport
 功能描述  : 存储短信状态报告到文件
 输入参数  : const MN_MSG_BCD_ADDR_STRU          *pstScAddr         短信中心号码
             const MN_MSG_RAW_TS_DATA_STRU       *pstRawData        短信状态报告
             const MN_MSG_STORAGE_INFO_STRU      *pstStorageInfo    短信状态报告存储位置信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月30日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数  DTS2011060803050 STATUS REPORT in ME
*****************************************************************************/
VOS_UINT32 MN_MSG_StoreStatusReport(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_STORAGE_INFO_STRU      *pstStorageInfo
)
{
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulRet;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#endif
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    /* 创建短信状态报告记录 */
    PS_MEM_SET(&stSmaUsimInfo, 0X00, sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId          = MN_CLIENT_ALL;
    stSmaUsimInfo.opId              = 0;
    stSmaUsimInfo.usEfId            = pstStorageInfo->usFileIndex;
    stSmaUsimInfo.enDeleteType      = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex        = (VOS_UINT8)pstStorageInfo->ulIndex;
    stSmaUsimInfo.enSmaUsimAction   = MN_MSG_USIM_RCVSTARPT;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
            stWriteUsimInfo.stUsimInfo.opId = 0;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId[0];
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstStorageInfo->ulIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
            stWriteUsimInfo.bCreateNode = VOS_TRUE;
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                        VOS_NULL_PTR,
                                        &stWriteUsimInfo,
                                        aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                        &pstStorageInfo->ulIndex,
                                        VOS_NULL_PTR,
                                        aucSmContent);
        }
#endif

    }
    else
    {
        /* 写短信状态报告记录到文件 */
        if ((MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
         && (ulFileId[1]       == pstStorageInfo->usFileIndex))
        {
            /* 协议栈不支持SMS记录与SMSR的关联，SMSR记录的第一个字节"关联的SMS记录索引"填0 */
            MSG_CreateEFSmsrContent(pstRawData, 0, aucSmsrContent);
            ulRet = MN_MSG_WriteSmsrFile(pstStorageInfo->enMemStore,
                                         &stSmaUsimInfo,
                                         aucSmsrContent);

        }
        else
        {
            MN_MSG_CreateEFSmContent(pstScAddr,
                                     pstRawData,
                                     EF_SMS_STATUS_MT_TO_BE_READ,
                                     aucSmContent);

#if ( (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
   || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
            if (MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
            {
                PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
                stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
                stWriteUsimInfo.stUsimInfo.opId = 0;
                stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId[0];
                stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
                stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstStorageInfo->ulIndex;
                stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
                stWriteUsimInfo.bCreateNode = VOS_TRUE;
                ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                            VOS_NULL_PTR,
                                            &stWriteUsimInfo,
                                            aucSmContent);

            }
            else
            {
                ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                            &pstStorageInfo->ulIndex,
                                            VOS_NULL_PTR,
                                            aucSmContent);
            }
#endif
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MSG_ProcSmsStaRpt
 功能描述  : 对NAS层SMS模块发送的status report进行相应的处理
 输入参数  : pstScAddr:短信中心的地址
             pstRawData:短信的TPDU
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2009年12月9日
    作    者   : f62575
    修改内容   : 问题单号:AT2D15782, 短信存储区满时接收到短信状态报告给网络回复RP-ACK消息，
                                  与标竿相同情况下回复RP-ERROR(错误原因值22内存满不一致)；
  3.日    期   : 2011年3月21日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号:DTS2011031105471，短信溢出存储介质总是SM，没有对ME存储溢出显示问题
  4.日    期   : 2011年7月1日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号:DTS2011060803050 STATUS REPORT in ME
  5.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求
  6.日    期   : 2013年6月19日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
*****************************************************************************/
LOCAL VOS_VOID MSG_ProcSmsStaRpt(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_UINT8                            ucRcvDomain
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    MN_MSG_STORAGE_INFO_STRU            stStorageInfo;

    /* 获取短信状态报告可用存储参数 */
    PS_MEM_SET(&stStorageInfo, 0x00, sizeof(stStorageInfo));
    MN_MSG_GetStatusReportStorageInfo(&stStorageInfo);

    /* 短信状态报告不存储: 给网络回复RP-ACK,并丢弃短信状态报告 */
    if (MN_MSG_RCVMSG_ACT_DISCARD == stStorageInfo.enRcvSmAct)
    {
        MN_INFO_LOG("MSG_ProcSmsStaRpt: enRcvSmAct is MN_MSG_RCVMSG_ACT_DISCARD");
        MN_MSG_Internal_SendRpt(VOS_TRUE, 0, 0);
        return;
    }

    /* 更新MT时的接收域，只有在状态不为MN_MSG_MT_STATE_NULL时才有效 */
    TAF_MSG_UpdateMtRcvDomain(ucRcvDomain);

    /* 短信状态报告上报事件数据填充: 短信中心号码，短信状态报告PDU，广播OPID */
    PS_MEM_SET(&stDeliverEvt, 0X00, sizeof(stDeliverEvt));
    PS_MEM_CPY(&stDeliverEvt.stRcvMsgInfo.stScAddr,
               pstScAddr,
               sizeof(stDeliverEvt.stRcvMsgInfo.stScAddr));
    PS_MEM_CPY(&stDeliverEvt.stRcvMsgInfo.stTsRawData,
               pstRawData,
               sizeof(stDeliverEvt.stRcvMsgInfo.stTsRawData));
    bcopId = MN_MSG_GetBCopId();

    /* 存储短信状态报告处理流程 */
    if (MN_MSG_RCVMSG_ACT_STORE == stStorageInfo.enRcvSmAct)
    {

        /* 获取空闲存储记录失败: 给网络回复RP-ERROR，同时上报^SMMEMFULL: <mem> */
        if (MN_MSG_NO_AVAILABLE_SMS_REC == stStorageInfo.ulIndex)
        {
            MN_NORM_LOG("MSG_ProcSmsStaRpt: There is no record available.");
            MN_MSG_FailToWriteEfsms(stStorageInfo.enMemStore,
                                    MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
            return;
        }

        /* 存储短信状态报告到文件 */
        ulRet = MN_MSG_StoreStatusReport(pstScAddr, pstRawData, &stStorageInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ProcSmsStaRpt: MN_MSG_WriteSmsFile Return Error");
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            return;
        }

        /* 存储短信状态报告到文件 */
        if (MN_MSG_MEM_STORE_NV == stStorageInfo.enMemStore)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE, 0, 0);

            /*广播上报来一条短信*/
            stDeliverEvt.enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
            stDeliverEvt.enMemStore = stStorageInfo.enMemStore;
            stDeliverEvt.ulInex     = stStorageInfo.ulIndex;
            MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);

            /*广播上报NVIM中短信已发生了改变*/
            MN_MSG_ReportSmChanged(MN_CLIENT_ALL, bcopId, VOS_TRUE, MN_MSG_MEM_STORE_NV);
        }

    }
    else if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY == stStorageInfo.enRcvSmAct)
    {
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*创建收短信相关信息*/
        MN_MSG_CreateMtInfo();
    }
    else
    {
        MN_MSG_GetCurAppMemStatus(&enAppMemStatus);
        if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
        {
            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

            MN_WARN_LOG("MSG_ProcSmsStaRpt:Rcv New Status Report but App Mem Full");
        }

        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
    }
}

/*****************************************************************************
 函 数 名  : MSG_UpdateEfSmsInfo
 功能描述  : 更新USIM或NVIM中EFSMS的内容
 输入参数  : pstMoEntity:当前MO实体信息
             penMemStore:当前的存储器
 输出参数  : penMemStore:更新后的存储器
 返 回 值  : VOS_OK:更新成功
             VOS_ERR:更新失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MSG_UpdateEfSmsInfo
(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    MN_MSG_MEM_STORE_ENUM_U8            *penMemStore
)
{

    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulRet;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }


    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);

    ulRet = MN_MSG_ReadSmsInfo(pstMoEntity->enSaveArea,
                               pstMoEntity->ulSaveIndex,
                               aucSmContent);

    if (MN_ERR_NO_ERROR == ulRet)
    {
        aucSmContent[0] = EF_SMS_STATUS_MO_SEND_TO_NT;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
          || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = pstMoEntity->clientId;
        stSmaUsimInfo.opId = pstMoEntity->opId;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity->ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVMORPT;
        ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_FALSE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = pstMoEntity->clientId;
            stWriteUsimInfo.stUsimInfo.opId = pstMoEntity->opId;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity->ulSaveIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVMORPT;
            stWriteUsimInfo.bCreateNode = VOS_FALSE;
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,&pstMoEntity->ulSaveIndex,VOS_NULL_PTR,aucSmContent);
        }
#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_UpdateEfSmsInfo:Update Sms in Usim or Nvim Error");
            return VOS_ERR;
        }
        return VOS_OK;
    }
    else
    {
        *penMemStore = MN_MSG_MEM_STORE_NONE;
        MN_WARN_LOG("MSG_ProcSmsRpMoRpRpt:Read Sms Failed");
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : MSG_GetMoFailCause
 功能描述  : 发送MO消息时,收到网侧的submit report后相应的处理
             RP-ERROR消息携带TP-FCS部分，则上报TP层错误码，否则上报原错误码
 输入参数  : pstRawData     RP ERROR消息的RPDU部分
             enErrorCode    SMT上报的错误码
 输出参数  : 无
 返 回 值  : VOS_UINT32上报给APP的错误码

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_UINT32 MSG_GetMoFailCause(
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    VOS_UINT32                          ulRet;

    if ((SMR_SMT_ERROR_RP_ERROR_BEGIN == (enErrorCode & SMR_SMT_ERROR_RP_ERROR_BEGIN))
     && (pstRawData->ulLen > 0))
    {
        ulRet = MN_MSG_Decode(pstRawData, &f_stMsgTsData);
        if (MN_ERR_NO_ERROR == ulRet)
        {
            return (f_stMsgTsData.u.stSubmitRptErr.enFailCause | TAF_MSG_ERROR_TP_ERROR_BEGIN);
        }

        MN_WARN_LOG("MSG_GetMoFailCause: MN_MSG_Decode Error");
    }

    return enErrorCode;
}

/*****************************************************************************
 函 数 名  : MSG_ProcSmsRpMoRpRpt
 功能描述  : 发送MO消息时,收到网侧的submit report后相应的处理
 输入参数  : pstMoEntity:当前发送的相关参数
             pstRawData:收到TPDU的内容
             pstTsData:TPDU解析后的数据
             enErrorCode:收到RP-Error时的Rp-Cause的值
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
LOCAL VOS_VOID MSG_ProcSmsRpMoRpRpt(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    VOS_UINT32                          ulRet = VOS_FALSE;
    MN_MSG_MEM_STORE_ENUM_U8            enCurMemStore;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));
    stSubmitRptEvt.ucMr = pstMoEntity->ucMr;

    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* 此处需要适配新的TAF-AT接口，发送成功，则上报STCS信息，否则获取错误原因值 */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

    if (MN_MSG_TPDU_SUBMIT_RPT_ACK == pstRawData->enTpduType)
    {
        f_ulMsgMoNum++;

        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        stSubmitRptEvt.enErrorCode = TAF_MSG_ERROR_NO_ERROR;
        stSubmitRptEvt.enSaveArea  = pstMoEntity->enSaveArea;
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        enCurMemStore = pstMoEntity->enSaveArea;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
         || (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea))
#else
        if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
#endif
        {
            ulRet = MSG_UpdateEfSmsInfo(pstMoEntity,&enCurMemStore);
            MN_INFO_LOG1("MSG_ProcSmsRpMoRpRpt: result of MSG_UpdateEfSmsInfo is ",
                         (VOS_INT32)ulRet);
            stSubmitRptEvt.enSaveArea = enCurMemStore;
            stSubmitRptEvt.ulSaveIndex = pstMoEntity->ulSaveIndex;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            if ((MN_MSG_MEM_STORE_NV == enCurMemStore)
             && (VOS_OK == ulRet))
            {
                bcOpId = MN_MSG_GetBCopId();
                MN_MSG_ReportSmChanged(pstMoEntity->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
            }
#endif
        }
        MN_MSG_ReportSubmitRptEvent(pstMoEntity->clientId,
                                    pstMoEntity->opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_INFO_LOG("MSG_ProcSmsRpMoRpRpt:Rcv Rp-Ack");
    }
    else if (MN_MSG_TPDU_SUBMIT_RPT_ERR == pstRawData->enTpduType)
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        stSubmitRptEvt.enErrorCode = MSG_GetMoFailCause(pstRawData, enErrorCode);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
        /* 此处需要适配新的TAF-AT接口，发送成功，则上报STCS信息，否则获取错误原因值 */
        /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
        stSubmitRptEvt.enSaveArea = pstMoEntity->enSaveArea;
        stSubmitRptEvt.ulSaveIndex = pstMoEntity->ulSaveIndex;
        MN_MSG_ReportSubmitRptEvent(pstMoEntity->clientId,
                                    pstMoEntity->opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_INFO_LOG("MSG_ProcSmsRpMoRpRpt:Rcv Rp-Error");
    }
    else
    {
    }
}

/*****************************************************************************
 函 数 名  : MSG_ProcSmsRpSmmaRpRpt
 功能描述  : 发送SMMA消息时,收到网侧的短信报告后相应的处理
 输入参数  : pstMoEntity:当前MO实体信息
             pstRawData:收到网侧发送过来的TPDU的内容
             enErrorCode:收到RP-Error时的Rp-Cause的值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求
*****************************************************************************/
LOCAL VOS_VOID MSG_ProcSmsRpSmmaRpRpt(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    MN_MSG_MEMSTATUS_EVT_INFO_STRU      stMemStatusEvt;
    MN_OPERATION_ID_T                   bcopId;

    PS_MEM_SET(&stMemStatusEvt,0X00,sizeof(stMemStatusEvt));

    if (MN_MSG_TPDU_SUBMIT_RPT_ACK == pstRawData->enTpduType)
    {
        if (VOS_TRUE == pstMoEntity->bReportFlag)
        {
            (VOS_VOID)MN_MSG_UpdateAppMemStatus(MN_MSG_MEM_FULL_UNSET);
            stMemStatusEvt.bSuccess = VOS_TRUE;
            stMemStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
            stMemStatusEvt.enMemFlag = MN_MSG_MEM_FULL_UNSET;
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         pstMoEntity->opId,
                                         VOS_FALSE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_SET_MEMSTATUS);
            bcopId = MN_MSG_GetBCopId();
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         bcopId,
                                         VOS_TRUE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_MEMSTATUS_CHANGED);
        }

        MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);

        MN_INFO_LOG("MSG_ProcSmsRpSmmaRpRpt:Rcv Rp-Ack");
    }
    else if (MN_MSG_TPDU_SUBMIT_RPT_ERR == pstRawData->enTpduType)
    {
        if (VOS_TRUE == pstMoEntity->bReportFlag)
        {
            stMemStatusEvt.bSuccess = VOS_FALSE;
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            stMemStatusEvt.ulFailCause = MSG_GetMoFailCause(pstRawData, enErrorCode);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
            stMemStatusEvt.enMemFlag = MN_MSG_MEM_FULL_SET;
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         pstMoEntity->opId,
                                         VOS_FALSE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_SET_MEMSTATUS);
        }
        MN_INFO_LOG("MSG_ProcSmsRpSmmaRpRpt:Rcv Rp-Error");
    }
    else
    {
    }
}

/*****************************************************************************
 函 数 名  : MSG_RcvSmsRpData
 功能描述  : 处理收到NAS层SMS模块发送的RP-Data
 输入参数  : pRcvMsg:收到数据的内容,具体为协议24011中RP-Data的内容
             ucRcvLen:收到数据的长度
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年01月26日
    作    者   : f62575
    修改内容   : 问题单号AT2D16565
                 短信自动回复桩失效，修改自动回复桩，使其能完成自动回复功能；
  3.日    期   : 2013年6月19日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
  4.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 在收到RP data后，设置MT消息路由
*****************************************************************************/
LOCAL VOS_VOID MSG_RcvSmsRpData(
    SMR_SMT_EST_IND_STRU                *pstEstInd
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    MN_MSG_RP_DATA_STRU                 stRpData;

    const VOS_UINT8                    *pucRcvMsg = VOS_NULL_PTR;

    pucRcvMsg   = pstEstInd->aucData;

    MN_INFO_LOG("MSG_RcvSmsRpData: step into function.");
    ulRet = MN_MSG_CheckUsimStatus();
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-8, begin */
#if (FEATURE_IMS == FEATURE_ON)
        if (PS_PID_IMSA == pstEstInd->ulSenderPid)
        {
            MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);
        }
        else
        {
            MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
        }
#endif
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-8, end */

        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        MN_WARN_LOG("MSG_RcvSmsRpData:Usim is not Ready");
        return;
    }

    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stRpData,0X00,sizeof(stRpData));

    /*3GPP 24011 RP DATA (Network to Mobile Station)*/
    MSG_DecodeRpData(pucRcvMsg,&stRpData);
    MN_INFO_LOG1("MSG_RcvSmsRpData: message RP-MR is ", stRpData.ucRpMr);
    PS_MEM_CPY(&stScAddr,&stRpData.stOrgAddr,sizeof(stScAddr));

    stTsRawData.ulLen = stRpData.ucRpUserDataLen;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData,stTsRawData.ulLen);

    MN_NORM_LOG1("MSG_RcvSmsRpData: message TP-MTI is ", ((stTsRawData.aucData[0]) & (0x03)));
    switch ((stTsRawData.aucData[0]) & (0x03))
    {
        case MN_MSG_TP_MTI_DELIVER:
            stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER;
            break;
        case MN_MSG_TP_MTI_STATUS_REPORT:
            stTsRawData.enTpduType = MN_MSG_TPDU_STARPT;
            break;
        default:
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_MSG_TYPE_NON_EXISTENT,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_RcvSmsRpData:Invalid TPDU Type");
            return;
    }

    ulRet = MN_MSG_Decode(&stTsRawData,&f_stMsgTsData);

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#if (FEATURE_IMS == FEATURE_ON)
    if (PS_PID_IMSA == pstEstInd->ulSenderPid)
    {
        MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);
    }
    else
    {
        MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
    }
#endif
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    /*此处的错误原因应为MN_MSG_RP_CAUSE_INVALID_MSG_UNSPECIFIED
    参考24011 if the message was not an RP ERROR message, the MS shall ignore
    the message and return an RP ERROR message with cause value #95 "
    semantically incorrect message", if an appropriate connection exists*/
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_TPDU_NOT_SUPPORTED);
        MN_WARN_LOG("MSG_RcvSmsRpData: Fail to decode TPDU.");
        return;
    }

    MN_NORM_LOG1("MSG_RcvSmsRpData: TPDU type: ",stTsRawData.enTpduType);
    if (MN_MSG_TPDU_DELIVER == stTsRawData.enTpduType)
    {
        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_RECEIVE,
                        &stRpData.ucRpMr, NAS_OM_EVENT_SMS_RECEIVE_LEN);
        /* 参数改变:增加接收域 */
        MSG_ProcSmsDeliver(&stScAddr,&stTsRawData,&f_stMsgTsData, pstEstInd->ucRcvDomain);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MT_NOTIFY,
                        &stRpData.ucRpMr, NAS_OM_EVENT_SMS_MT_NOTIFY_LEN);
        /* 参数改变:增加接收域 */
        MSG_ProcSmsStaRpt(&stScAddr,&stTsRawData,&f_stMsgTsData, pstEstInd->ucRcvDomain);
    }

}

/*****************************************************************************
 函 数 名  : MSG_RcvSmsAttachInd
 功能描述  : 处理收到NAS层CS,PS域的注册情况
 输入参数  : ucDomain:CS域或PS域的相关标志
             bAttachFlag:注册标志,成功还是失败
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2009年10月16日
    作    者   : f62575
    修改内容   : 问题单号:AT2D15127, 服务域为PS ONLY，发送域为CS PREFER，参照标杆
                 短信首先尝试从CS域发送；
  3.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
*****************************************************************************/
LOCAL VOS_VOID  MSG_RcvSmsAttachInd(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
)
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_MO_STATE_ENUM_U8             enMoState;

    MN_MSG_UpdateRegState(ucDomain,bAttachFlag);

    /*如果当前已ATTACH上,则查看是否需要发送缓存消息*/
    if(VOS_TRUE == bAttachFlag)
    {
        enMoState = MN_MSG_GetMoState();
        if (MN_MSG_MO_STATE_WAIT_REPORT_IND != enMoState)
        {
            (VOS_VOID)MN_MSG_StartMo(&enSendDomain);
        }
        MN_MSG_StartMemNotification();
    }
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : MN_MSG_IsLteNeedSmsRetry
 功能描述  : 判断L下是否需要短信重发
 输入参数  : enErrCause - L LMM_SMS_ERR_IND回复的失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 短信需要重发
             VOS_FALSE - 短信无需重发
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_IsLteNeedSmsRetry(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause
)
{
    MN_MSG_RETRY_FLAG_U8                enRetryFlg;

    switch ( enErrCause )
    {
        case LMM_SMS_ERR_CAUSE_RRC_CONN_NOT_EXIST:
        case LMM_SMS_ERR_CAUSE_OTHERS:
            /* 需要尝试重发 */
            enRetryFlg = MSG_JudgeRetryFlg();

            if (MN_MSG_RETRY_BEGIN == enRetryFlg)
            {
                return VOS_TRUE;
            }

            return VOS_FALSE;

        case LMM_SMS_ERR_CAUSE_UE_MODE_PS_ONLY:
        case LMM_SMS_ERR_CAUSE_ACCESS_BARRED:
        case LMM_SMS_ERR_CAUSE_USIM_CS_INVALID:
        case LMM_SMS_ERR_CAUSE_USIM_PS_INVALID:
        case LMM_SMS_ERR_CAUSE_CS_SER_NOT_AVAILABLE:
        case LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED:
        case LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED:
        case LMM_SMS_ERR_CAUSE_T3402_RUNNING:
            return VOS_FALSE;

        default:
            MN_WARN_LOG("MN_MSG_IsLteNeedSmsRetry:error cause invalid");
            return VOS_FALSE;
    }


}

#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

/*****************************************************************************
 函 数 名  : TAF_MSG_IsSmsRetryCause_CmSrvRej
 功能描述  : 原因值是否需要重拨(CM_SRV_REJ)
 输入参数  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:呼叫失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要重拨
             VOS_FALSE:不需要重拨
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月29日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MSG_IsSmsRetryCause_CmSrvRej(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{

    VOS_UINT8                           ucIndex;
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);

    for (ucIndex = 0; ucIndex < stRetryInfo.ucSmsRetryCmSrvRejNum; ucIndex++)
    {
        if (enCause == stRetryInfo.aucSmsRetryCmSrvRejCause[ucIndex] + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MSG_IsSmsRetryCause_MmInterErr
 功能描述  : 原因值是否需要重拨(MM_INTER_ERR)
 输入参数  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:呼叫失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要重拨
             VOS_FALSE:不需要重拨
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月29日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MSG_IsSmsRetryCause_MmInterErr(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    /* NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL是GU报resume_ind时ucCsResumeResult为fail, GU接入层异常，没必要再重拨
       NAS_CC_CAUSE_MM_INTER_ERR_BACK_TO_LTE是CSFB异系统失败重回LTE, MMC会去GU下搜网，需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL是消息发送异常，不需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL是GAS回复的失败，需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE 不需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE 短信业务时不需要重拨 */

    switch (enCause)
    {
        /* cs LAU rej #12现在有NV定制有业务时会触发搜网，可以允许重拨 */
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}


/*****************************************************************************
 函 数 名  : TAF_MSG_IsSmsRetryCause_RrConnFail
 功能描述  : 原因值是否需要重拨(RR_CONN_FAIL)
 输入参数  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:呼叫失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要重拨
             VOS_FALSE:不需要重拨
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月29日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MSG_IsSmsRetryCause_RrConnFail(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    if ((NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT          == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                     == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MSG_IsSmsRetryCause_RrRel
 功能描述  : 原因值是否需要重拨(RR_REL)
 输入参数  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:呼叫失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要重拨
             VOS_FALSE:不需要重拨
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月29日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年11月23日
    作    者   : w00167002
    修改内容   : DTS2015112307317:在RL faiure场景继续重试
*****************************************************************************/
VOS_UINT32 TAF_MSG_IsSmsRetryCause_RrRel(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    if ( (NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ    == enCause)
      || (NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_IsGuNeedSmsRetry
 功能描述  : 根据原因值判断GU下是否需要短信重发
 输入参数  : enErrCause - 失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 短信需要重发
             VOS_FALSE - 短信无需重发
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月17日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_UINT32  MN_MSG_IsGuNeedSmsRetry(
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCmErrCause;
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;

    /* 是CS失败原因值，则判断CAUSE值 */
    if ( SMR_SMT_ERROR_CS_ERROR_BEGIN == (enErrCause & SMR_SMT_ERROR_CS_ERROR_BEGIN) )
    {

        enMmCmErrCause = (NAS_MMCM_REL_CAUSE_ENUM_UINT32)(enErrCause - SMR_SMT_ERROR_CS_ERROR_BEGIN);

        /* cm service reject */
        if ((enMmCmErrCause >= NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN)
         && (enMmCmErrCause <= NAS_MMCM_REL_CAUSE_CM_SRV_REJ_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_CmSrvRej(enMmCmErrCause);
        }
        /* est_cnf失败，与NAS_MM_IsAbleRecover_EstCnfFailResult的处理逻辑保持一致 */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_RR_CONN_FAIL_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_RrConnFail(enMmCmErrCause);

        }

        /* rel_ind, 除了鉴权被拒，其他原因值与NAS_MM_IsNeedCmServiceRetry_RelIndResult的处理逻辑保持一致 */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_RR_REL_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_RR_REL_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_RrRel(enMmCmErrCause);
        }

        /* MM INTER ERR */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_MM_INTER_ERR_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_MM_INTER_ERR_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_MmInterErr(enMmCmErrCause);
        }

        else
        {
            /* CSFB Service reject，CSFB LMM fail，在短信过程中不可能出现，不需要重拨 */
            ulRslt  = VOS_FALSE;
        }

    }

    /* 非CS域失败，需要进行重发 */
    return ulRslt;

}


/***********************************************************************
函 数 名  : MN_MSG_StartLinkCtrl
功能描述  : 获取中继协议链路连续性的启动标志
输入参数  : 无
输出参数  : 无
返 回 值  : 中继协议链路连续性的启动标志
            VOS_FALSE 不启动中继协议链路连续性
            VOS_TRUE    启动中继协议链路连续性
调用函数  :
被调函数  :

修改历史      :
 1. 日    期   : 2014年02月20日
    作    者   : f62575
    修改内容   : DTS2014012108756: 关闭2G接入技术下语音并发情况的短信连发功能
************************************************************************/
VOS_UINT8 MN_MSG_StartLinkCtrl(VOS_VOID)
{
    VOS_UINT8                           ucInCallFlg;
    VOS_UINT8                           ucRat;

    /* 2G接入技术且在呼叫中不启动短信连发功能 */
    ucInCallFlg = TAF_SDC_GetCsCallExistFlg();
    ucRat       = TAF_SDC_GetSysMode();
    if ((VOS_TRUE == ucInCallFlg)
     && (TAF_SDC_SYS_MODE_GSM == ucRat))
    {
        return MN_MSG_LINK_CTRL_DISABLE;
    }

    return MN_MSG_GetLinkCtrlParam();
}

/*lint -e438 -e830*/

/*****************************************************************************
 函 数 名  : MSG_RcvSmsRpRpt
 功能描述  : 处理收到NAS层SMS模块发送的RP-Report
 输入参数  : pRcvMsg:收到数据的内容,具体为协议24011中RP-REPORT的内容
             ucRcvLen:收到数据的长度
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
  3.日    期   : 2010年10月25日
    作    者   : 傅映君/f62575
    修改内容   : ERROR LOG
  4.日    期   : 2012年8月13日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  5.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  6.日    期   : 2013年10月22日
    作    者   : w00167002
    修改内容   : NETSCAN: 增加enErrCause，在CS短信失败时候，需要根据失败原因值来
                 判定是否需要短信重发。
  7.日    期   : 2015年05月22日
    作    者   : j00174725
    修改内容   : DTS2015052201409
*****************************************************************************/
VOS_VOID  MN_MSG_RcvSmsRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg)
{

    VOS_UINT32                          ulRet;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    MN_MSG_SEND_FAIL_FLAG_U8            enSendFailFlag;
    VOS_BOOL                            bIsTimerStart;
    VOS_BOOL                            bRetryProcess = VOS_FALSE;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    VOS_UINT32                          ulMoFailCause;


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrorCause;
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

    PS_MEM_SET(&stRawData,0X00,sizeof(stRawData));
    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    PS_MEM_SET(&stRpCause,0X00,sizeof(stRpCause));
    PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
    PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));

    MN_MSG_GetMoEntity(&stMoEntity);
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_RcvSmsRpRpt:Mo State is NULL");
        return;
    }

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    if (SMR_SMT_ERROR_NO_ERROR == pstMsg->enErrorCode)
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        MSG_DecodeRpAck(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpAck);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        if (VOS_TRUE == stRpAck.bRpUserDataExist)
        {
            stRawData.ulLen = stRpAck.ucRpUserDataLen;
            PS_MEM_CPY(stRawData.aucData,stRpAck.aucRpUserData,stRawData.ulLen);
        }
        stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ACK;
        /* 判断当前短信重发周期定时器是否已启动,如果已经启动,则停止定时器 */
        bIsTimerStart = MN_MSG_IsTimerStarting(MN_MSG_ID_WAIT_RETRY_PERIOD);
        if (VOS_TRUE == bIsTimerStart)
        {
            MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
        }
        /* 更新当前发送域发送成功 */
        enSendFailFlag = MN_MSG_GetSendFailFlag();
        if ( (MN_MSG_SEND_DOMAIN_PS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_PS_DOMAIN == (enSendFailFlag & MN_MSG_SEND_FAIL_PS_DOMAIN)))
        {
            enSendFailFlag ^= MN_MSG_SEND_FAIL_PS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
        if ( (MN_MSG_SEND_DOMAIN_CS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_CS_DOMAIN == (enSendFailFlag & MN_MSG_SEND_FAIL_CS_DOMAIN)))
        {
            enSendFailFlag ^= MN_MSG_SEND_FAIL_CS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
    }
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    else
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
        /* 更新当前发送域发送失败*/
        enSendFailFlag = MN_MSG_GetSendFailFlag();
        if ( (MN_MSG_SEND_DOMAIN_PS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_PS_DOMAIN != (enSendFailFlag & MN_MSG_SEND_FAIL_PS_DOMAIN)))
        {
            enSendFailFlag |= MN_MSG_SEND_FAIL_PS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
        if ( (MN_MSG_SEND_DOMAIN_CS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_CS_DOMAIN != (enSendFailFlag & MN_MSG_SEND_FAIL_CS_DOMAIN)))
        {
            enSendFailFlag |= MN_MSG_SEND_FAIL_CS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, begin */

        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        if ((NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
         && (SMR_SMT_ERROR_EPS_ERROR_BEGIN == (pstMsg->enErrorCode & SMR_SMT_ERROR_EPS_ERROR_BEGIN)))
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        {
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            enErrorCause = (LMM_SMS_ERR_CAUSE_ENUM_UINT32)(pstMsg->enErrorCode - SMR_SMT_ERROR_EPS_ERROR_BEGIN);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
            if (VOS_TRUE == MN_MSG_IsLteNeedSmsRetry(enErrorCause))
            {
                /* 需要进行重发,启动重发间隔定时器,定时器超时后再进行重发 */
                MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL, 0);
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                MN_MSG_SaveRpErrInfo(pstMsg);
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                return;
            }

            /* 重发过程结束,不需要进行任何操作,停止定时器 */
            MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
            stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;
            stRawData.ulLen      = 0;
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            MN_MNTN_RecordSmsMoFailure(MSG_GetMoFailCause(&stRawData, pstMsg->enErrorCode));
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(pstMsg->enErrorCode);
#endif

            /* SMS MO FAIL事件上报 */
            stSmsMoReportPara.ulCause = pstMsg->enErrorCode;
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, end */
        else
#endif

        {
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            MSG_DecodeRpErr(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpErr);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
            PS_MEM_CPY(&stRpCause,&stRpErr.stRpCause,sizeof(stRpCause));
            if (VOS_TRUE == stRpErr.bRpUserDataExist)
            {
                stRawData.ulLen = stRpErr.ucRpUserDataLen;
                PS_MEM_CPY(stRawData.aucData,stRpErr.aucRpUserData,stRawData.ulLen);
            }
            stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;

            ulMoFailCause = MSG_GetMoFailCause(&stRawData, pstMsg->enErrorCode);

            /* 判断当前是否需要进行重发 */
            bRetryProcess = MSG_IsProcessRetry(&stMoEntity, pstMsg->enErrorCode, ulMoFailCause);
            if (VOS_TRUE == bRetryProcess)
            {
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                MN_MSG_SaveRpErrInfo(pstMsg);
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                return;
            }

            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            MN_MNTN_RecordSmsMoFailure(ulMoFailCause);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(pstMsg->enErrorCode);
#endif

            /* SMS MO FAIL事件上报 */
            stSmsMoReportPara.ulCause = pstMsg->enErrorCode;
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        }

    }

    if ((MN_MSG_MO_TYPE_MO == stMoEntity.enSmsMoType)
     || (MN_MSG_MO_TYPE_BUFFER_STK == stMoEntity.enSmsMoType))
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        MSG_ProcSmsRpMoRpRpt(&stMoEntity, &stRawData, pstMsg->enErrorCode);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    }
    else
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        MSG_ProcSmsRpSmmaRpRpt(&stMoEntity,&stRawData, pstMsg->enErrorCode);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    }

    MN_MSG_DestroyMoInfo();

    MN_MSG_StopTimer(MN_MSG_TID_LINK_CTRL);
    enLinkCtrl = MN_MSG_StartLinkCtrl();
    if (MN_MSG_LINK_CTRL_DISABLE == enLinkCtrl)
    {
        MN_MSG_SendSmsCpAckReq();
        /*查看是否有缓存消息,继续发送,没有缓存消息则发送一个空消息过去,有缓存消息则发送一条新的短信*/
        ulRet = MN_MSG_StartMo(&enSendDomain);
    }
    else
    {
        /*查看是否有缓存消息,继续发送,没有缓存消息则发送一个空消息过去,有缓存消息则发送一条新的短信*/
        ulRet = MN_MSG_StartMo(&enSendDomain);
        if ((VOS_OK != ulRet) /*当前没有消息需要发送，等待用户发送指示*/
         || (MN_MSG_SEND_DOMAIN_CS == enSendDomain))/*当前消息有消息要发送，且发送域为CS域*/
        {
            MN_MSG_StartTimer(MN_MSG_TID_LINK_CTRL, 0);
        }
    }


    return;
}
/*lint +e438 +e830*/

/*****************************************************************************
 函 数 名  : MSG_RcvSmsMtErrInd
 功能描述  : 收到Tr2m超时后,向应用上报接收短信失败
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年04月30日
    作    者   : F62575
    修改内容   : 问题单号AT2D15403
                 短信以CMT方式上报且CSMS配置为1时若应用不下发CNMA命令确认新短信接收,
                 则后续短信既不上报也不存储到本地;
  3.日    期   : 2013年05月23日
    作    者   : l65478
    修改内容   : 增加NV项控制在收不到AP的RP ACK时,是否需要进行本地存储
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
LOCAL VOS_VOID MSG_RcvSmsMtErrInd(SMR_SMT_MT_ERR_STRU *pstMtErr)
{
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;

    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    MN_MSG_DestroyMtInfo();

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    if ((VOS_TRUE == pstMsCfgInfo->ucLocalStoreFlg)
     && (TAF_MSG_ERROR_TR2M_TIMEOUT == pstMtErr->enErrorCode))
    {
        MN_MSG_InitRcvPath();
    }

    MN_MSG_ReportDeliverErr((TAF_MSG_ERROR_ENUM_UINT32)pstMtErr->enErrorCode);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
}

/*****************************************************************************
 函 数 名  : MN_MSG_ProcSmsMsg
 功能描述  : 处理来自SMS的消息
 输入参数  : MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月19日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_VOID MN_MSG_ProcSmsMsg(
    VOS_VOID                            *pMsg
)
{
    SMT_SMR_DATA_STRU                  *pstData = (SMT_SMR_DATA_STRU*)pMsg;
    SMR_SMT_ATTACH_STRU                *pstAttachData;

    switch (pstData->ulMsgName)
    {
        case SMR_SMT_ATTACH_IND:
            pstAttachData = (SMR_SMT_ATTACH_STRU *)pstData->aucData;
            MSG_RcvSmsAttachInd(pstAttachData->ucDomain, pstAttachData->bAttachFlag);
            break;
        case SMR_SMT_DATA_IND:
            MSG_RcvSmsRpData((SMR_SMT_EST_IND_STRU *)pMsg);
            break;
        case SMR_SMT_REPORT_IND:
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            MN_MSG_RcvSmsRpRpt((SMR_SMT_MO_REPORT_STRU *)pstData);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
            break;
        case SMR_SMT_MT_ERR_IND:
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            MSG_RcvSmsMtErrInd((SMR_SMT_MT_ERR_STRU *)pstData);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(((SMR_SMT_MT_ERR_STRU *)pstData)->enErrorCode);
#endif

            NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MT_FAIL,
                            &(((SMR_SMT_MT_ERR_STRU *)pstData)->enErrorCode), sizeof(TAF_MSG_ERROR_ENUM_UINT32));

            break;
        case SMR_SMT_LINK_CLOSE_IND:
            MN_MSG_StopTimer(MN_MSG_TID_LINK_CTRL);
            break;

        default:
            MN_WARN_LOG("MN_MSG_ProcSmsMsg:Error MsgName");
            break;
    }

}

/***********************************************************************
函 数 名  : MN_MSG_PrintMoNum
功能描述  : 打印已发送短信条数的静态变量
输入参数  : None
输出参数  : None
返 回 值  : None
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年8月03日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintMoNum(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMoNum: f_ulMsgMoNum is ", (VOS_INT32)f_ulMsgMoNum);
    return;
}

/***********************************************************************
函 数 名  : MN_MSG_PrintMtNum
功能描述  : 打印已接收短信条数的静态变量
输入参数  : None
输出参数  : None
返 回 值  : None
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年8月03日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintMtNum(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMtNum: f_ulMsgMtNum is ", (VOS_INT32)f_ulMsgMtNum);
    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_AppStorageUnavailable
 功能描述  : 检查APP短信存储是否不可用
 输入参数  : MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct
             MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus

 输出参数  : VOS_BOOL                           *pbUnavailableFlag
             APP短信存储是否不可用  VOS_TRUE  APP短信存储不可用
                                    VOS_FALSE APP短信存储可用
 返 回 值  : VOS_UINT32 函数处理结果，本函数仅在输入参数错误时返回失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月1日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
   2.日    期   : 2012年11月08日
     作    者   : f62575
     修改内容   : DTS2012111201995 ： 删除参数ucClassType，错误原因值更新；

*****************************************************************************/
VOS_UINT32 MN_MSG_AppStorageUnavailable(
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct,
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus,
    VOS_BOOL                           *pbUnavailableFlag
)
{

    if ((MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK != enRcvSmAct)
     && (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY != enRcvSmAct)
     && (MN_MSG_RCVMSG_ACT_DISCARD != enRcvSmAct))
    {
        MN_WARN_LOG("MN_MSG_AppStorageUnavailable: invalid input parameter.");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_RCVMSG_ACT_DISCARD == enRcvSmAct)
    {
        *pbUnavailableFlag = VOS_FALSE;
        return MN_ERR_NO_ERROR;
    }

    if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
    {
        *pbUnavailableFlag = VOS_TRUE;
        return MN_ERR_NO_ERROR;
    }

    *pbUnavailableFlag = VOS_FALSE;
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UeStorageUnavailable
 功能描述  : 判断是否UE的所有存储区都已用尽，注意:所有存储介质为当前配置下可以用
             于存储短信的介质
 输入参数  : enSmMemStore 用户配置的存储介质
 输出参数  : *pbFlag      存储区已用尽
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月31日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求，仅检查指定的存储介质状态

*****************************************************************************/
VOS_UINT32 MN_MSG_UeStorageUnavailable(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_BOOL                           *pbUnavailableFlag
)
{
    VOS_UINT32                           ulRecInex;

    if ((MN_MSG_MEM_STORE_SIM != enSmMemStore)
     && (MN_MSG_MEM_STORE_NV != enSmMemStore))
    {
        MN_WARN_LOG("MN_MSG_UeStorageUnavailable: invalid input parameter.");
        return MN_ERR_INVALIDPARM;
    }

    ulRecInex = MN_MSG_GetAvailSmRecIndex(enSmMemStore);
    if (MN_MSG_NO_AVAILABLE_SMS_REC == ulRecInex)
    {
        *pbUnavailableFlag = VOS_TRUE;
        return MN_ERR_NO_ERROR;
    }

   *pbUnavailableFlag = VOS_FALSE;
   return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_ProcMoCtrl
 功能描述  : 根据发送短信内容,构造Envelop 命令到USIM卡中
 输入参数  : pucEfSmContent       - 短信的内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR:解析发送参数成功
             其他:解析发送参数失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月24日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011062201273 MO SMS CONTROL
  2.日    期   : 2012年10月11日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011062201273 MO SMS CONTROL
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理
  4.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:MN_MSG_MoSmsControlEnvelopeReq增加client ID参数
  5.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 MN_MSG_ProcMoCtrl(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    const VOS_UINT8                     aucRpDataInfo[]
)
{
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bBufferEntity;
    VOS_UINT32                          ulIndex;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl:Usim is now Enveloping");
        return MN_ERR_CLASS_SMS_USIM_ENVELOPEPENDING;
    }

    /* 获取SUBMIT消息参数: 短信中心号码，短信目的号码 */
    PS_MEM_SET(&stRpData, 0x00, sizeof(stRpData));
    MSG_DecodeRpData(aucRpDataInfo, &stRpData);

    PS_MEM_SET(&stTsRawData, 0x00, sizeof(stTsRawData));
    stTsRawData.ulLen       = stRpData.ucRpUserDataLen;
    stTsRawData.enTpduType  = MN_MSG_TPDU_SUBMIT;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);
    ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: MN_MSG_Decode fail.");
        return ulRet;
    }

    /* 转换短信目的号码类型为ENVELOPE所需的BCD码类型 */
    PS_MEM_SET(&stDestAddr, 0x00, sizeof(stDestAddr));
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertAsciiAddrToBcd(&f_stMsgTsData.u.stSubmit.stDestAddr,
                                  &stDestAddr);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: get TP-DA fail.");
        return ulRet;
    }

    /* 补充LAI信息，组装并发送ENVELPE消息到USIM */
    ulRet = MN_MSG_MoSmsControlEnvelopeReq(ClientId, &stRpData.stDestAddr, &stDestAddr);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SendFdnCheckInfo
 功能描述  : 发送短信FDN检查信息到(U)SIM模块
 输入参数  : MN_MSG_MO_ENTITY_STRU *pstMoEntity 短信发送实体
 输出参数  : 无
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR                 FDN检查数据发送成功
                其他，                          FDN检查数据发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，
  3.日    期   : 2013年5月15日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:FDN检查请求传入client ID
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
  5.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 MN_MSG_SendFdnCheckInfo(MN_MSG_MO_ENTITY_STRU *pstMoEntity)
{
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    VOS_UINT32                          ulRet;

    /* 获取SUBMIT消息参数: 短信中心号码，短信目的号码 */
    PS_MEM_SET(&stRpData, 0x00, sizeof(stRpData));
    MSG_DecodeRpData(pstMoEntity->aucRpDataInfo, &stRpData);

    PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
    stTsRawData.ulLen       = stRpData.ucRpUserDataLen;
    stTsRawData.enTpduType  = MN_MSG_TPDU_SUBMIT;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);

    ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: MN_MSG_Decode fail.");
        return ulRet;
    }

    /* 转换短信目的号码类型为FDN检查所需的BCD码类型 */
    PS_MEM_SET(&stDestAddr, 0x00, sizeof(stDestAddr));

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertAsciiAddrToBcd(&f_stMsgTsData.u.stSubmit.stDestAddr,
                                  &stDestAddr);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: get TP-DA fail.");
        return ulRet;
    }

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));

    stFdnInfo.ulNum1Len = stRpData.stDestAddr.ucBcdLen;
    PS_MEM_CPY(stFdnInfo.aucNum1,
               stRpData.stDestAddr.aucBcdNum,
               stFdnInfo.ulNum1Len);

    stFdnInfo.ulNum2Len = stDestAddr.ucBcdLen;
    PS_MEM_CPY(stFdnInfo.aucNum2,
               stDestAddr.aucBcdNum,
               stFdnInfo.ulNum2Len);

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, pstMoEntity->clientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    return MN_ERR_NO_ERROR;
}



#if ( VOS_WIN32 == VOS_OS_VER )
/*****************************************************************************
 函 数 名  : MN_MSG_StubClearEfsmssFlag
 功能描述  : PC工程桩函数，用于清除EFSMSS文件中内存溢出标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月31日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求

*****************************************************************************/
VOS_VOID MN_MSG_StubClearEfsmssFlag(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;

    MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);

    /* 释放缓存的SMMA消息 */
    ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
    if ((MN_MSG_NO_AVAILABLE_SMS_REC != ulStoreIndex)
     && (MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType))
    {
        MN_MSG_FreeStoreMsg(ulStoreIndex);
    }

    MN_INFO_LOG("MN_MSG_StubClearEfsmssFlag: SMSS clear stub.");

    return;
}
#endif

/***********************************************************************
函 数 名  : MN_MSG_CheckMemAvailable
功能描述  : 根据用户设置确认短信存储空间当前是否可用
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK:  可用
            其他:   不可用
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年03月20日
   作    者   : f62575
   修改内容   : 新生成函数
 2.日    期   : 2011年11月08日
   作    者   : 傅映君/f62575
   修改内容   : DTS2012111201995，DCM短信接收定制需求
 3.日    期   : 2013年8月3日
   作    者   : z60575
   修改内容   : TQE修改
************************************************************************/
VOS_UINT32 MN_MSG_CheckMemAvailable(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bUnavailableFlag;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;
    VOS_BOOL                            bSmUnavailableFlag;

    MN_INFO_LOG("MN_MSG_CheckMemAvailable: step into function.");

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    #if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucSetEfSmssClear)
    {
        MN_MSG_StubClearEfsmssFlag();
        return VOS_ERR;
    }
    #endif

    bUnavailableFlag    = VOS_TRUE;
    bSmUnavailableFlag  = VOS_TRUE;
    enMtCustomize       = MN_MSG_MT_CUSTOMIZE_NONE;
    MN_MSG_GetMtCustomizeInfo(&enMtCustomize);

    /* 获取用户的短信接收存储配置 */
    MN_MSG_GetCurCfgParm(&stCfgParm);

    /* 若用户配置的短信存储方式为非数据卡存储，则检查APP短信接收功能是否可用 */
    if (MN_MSG_RCVMSG_ACT_STORE != stCfgParm.enRcvSmAct)
    {
        ulRet = MN_MSG_AppStorageUnavailable(stCfgParm.enRcvSmAct,
                                            stCfgParm.enAppMemStatus,
                                            &bUnavailableFlag);
    }
    /* 若用户配置的短信存储方式为数据卡存储，
       否则根据用户设置的存储介质检查数据卡存储区短信接收功能是否可用 */
    else
    {
        ulRet = MN_MSG_UeStorageUnavailable(stCfgParm.enSmMemStore, &bUnavailableFlag);
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_ERR;
    }

    /*
    DCM定制要求: (U)SIM和用户指定的存储介质均为空闲状态，标示UE的短信存储介质空闲；
    主线版本要求: (U)SIM或用户指定的存储介质空闲，标示UE的短信存储介质空闲；
    */
    ulRet = MN_MSG_UeStorageUnavailable(MN_MSG_MEM_STORE_SIM, &bSmUnavailableFlag);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_ERR;
    }

    if (MN_MSG_MT_CUSTOMIZE_DCM == enMtCustomize)
    {
        if ((VOS_TRUE != bSmUnavailableFlag)
         && (VOS_TRUE != bUnavailableFlag))
        {
            return VOS_OK;
        }

    }
    else
    {
        if ((VOS_TRUE != bSmUnavailableFlag)
         || (VOS_TRUE != bUnavailableFlag))
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;

}

/*****************************************************************************
 函 数 名  : MN_MSG_MoCtrlAllowedWithModification
 功能描述  : MO SMS CONTROL过程的响应消息是ALLOWED MODIFY，更新短信中心或目
             的号码
 输入参数  : SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_UINT32 MN_MSG_MoCtrlAllowedWithModification(
    SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
)
{
    MN_MSG_BCD_ADDR_STRU                stTpBcdAddr;
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
     VOS_UINT32                         ulRet;

    PS_MEM_SET(&stTpBcdAddr, 0, sizeof(MN_MSG_BCD_ADDR_STRU));
    PS_MEM_SET(&stRpData, 0, sizeof(MN_MSG_RP_DATA_STRU));
    PS_MEM_SET(&stTsRawData, 0, sizeof(MN_MSG_RAW_TS_DATA_STRU));

    MSG_DecodeRpData(pstMoEntity->aucRpDataInfo, &stRpData);

    if (0 != pstMoCtrlRsp->OP_Addr1)
    {
        if ((pstMoCtrlRsp->Addr1.ucLen > MN_MSG_MAX_BCD_NUM_LEN)
         || (0 == pstMoCtrlRsp->Addr1.ucLen))
        {
            return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
        }

        stRpData.stDestAddr.ucBcdLen = pstMoCtrlRsp->Addr1.ucLen;
        stRpData.stDestAddr.addrType = pstMoCtrlRsp->Addr1.ucNumType;
        PS_MEM_CPY(stRpData.stDestAddr.aucBcdNum,
                   pstMoCtrlRsp->Addr1.pucAddr,
                   pstMoCtrlRsp->Addr1.ucLen);
    }

    /* 响应消息中存在TP-DA更新短信目的号码 */
    if (0 != pstMoCtrlRsp->OP_Addr2)
    {
        if ((pstMoCtrlRsp->Addr2.ucLen > MN_MSG_MAX_BCD_NUM_LEN)
         || (0 == pstMoCtrlRsp->Addr2.ucLen))
        {
            return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
        }

        stTpBcdAddr.ucBcdLen = pstMoCtrlRsp->Addr2.ucLen;
        stTpBcdAddr.addrType = pstMoCtrlRsp->Addr2.ucNumType;
        PS_MEM_CPY(stTpBcdAddr.aucBcdNum,
                   pstMoCtrlRsp->Addr2.pucAddr,
                   pstMoCtrlRsp->Addr2.ucLen);

        PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
        stTsRawData.ulLen = stRpData.ucRpUserDataLen;
        stTsRawData.enTpduType = MN_MSG_TPDU_SUBMIT;
        PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);

        ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = MN_MSG_BcdAddrToAscii(&stTpBcdAddr, &f_stMsgTsData.u.stSubmit.stDestAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = MN_MSG_Encode(&f_stMsgTsData, &stTsRawData);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*根据24011填写参数内容,7.3.1.2 RP DATA (Mobile Station to Network)*/
        stRpData.ucRpUserDataLen = (VOS_UINT8)stTsRawData.ulLen;
        PS_MEM_CPY(stRpData.aucRpUserData, stTsRawData.aucData, stTsRawData.ulLen);
    }

    MN_MSG_EncodeRpData(&stRpData,
                        pstMoEntity->aucRpDataInfo,
                        &pstMoEntity->ucRpDataLen);

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_RcvUsimEnvelopeCnf
 功能描述  : 处理ENVELOPE的响应消息
 输入参数  : VOS_VOID                            *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月15日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数, DTS2011062201273 MO SMS CONTROL
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  3.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID MN_MSG_RcvUsimEnvelopeCnf(
        VOS_VOID                            *pMsg
)
{
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope;

    pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *) pMsg;

    /* ucDataType STK用于透传EnvelopeType信息给业务发起模块 */
    if (SI_STK_ENVELOPE_PPDOWN == pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimEnvelopRsp(pstEnvelope);
        return;
    }

    if (SI_STK_ENVELOPE_SMSCRTL == pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimMoControlRsp(pstEnvelope);
        return;
    }

    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

    return;
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_MSG_ProcEfsmsFile
 功能描述  : 短信成功后，更新EFsms文件信心
 输入参数  : pstMoEntity －－ MO短信实体信息地址
             pstSubmitRptEvt －－短信report事件信息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS换域重拨功能
*****************************************************************************/
VOS_VOID TAF_MSG_ProcEfsmsFile(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU    *pstSubmitRptEvt
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MEM_STORE_ENUM_U8            enCurMemStore;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif
    enCurMemStore = MN_MSG_MEM_STORE_NONE;

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
     || (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea))
#else
    if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
#endif
    {
        ulRet = VOS_FALSE;

        ulRet = MSG_UpdateEfSmsInfo(pstMoEntity,&enCurMemStore);
        MN_INFO_LOG1("TAF_MSG_UpdateEfsmsInfo: result of TAF_MSG_UpdateEfsmsInfo is ",
                     (VOS_INT32)ulRet);

        pstSubmitRptEvt->enSaveArea   = enCurMemStore;
        pstSubmitRptEvt->ulSaveIndex = pstMoEntity->ulSaveIndex;

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_NV == enCurMemStore)
         && (VOS_OK == ulRet))
        {
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(pstMoEntity->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
#endif
    }
}

/*****************************************************************************
 函 数 名  : TAF_MSG_RcvImsaRpRpt
 功能描述  : 处理收到IMSA模块发送的RP-Report
 输入参数  : pstMsg:收到数据的内容,具体为协议24011中RP-REPORT的内容
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS换域重拨功能
*****************************************************************************/
VOS_VOID TAF_MSG_RcvImsaRpRpt(
    SMR_SMT_MO_REPORT_STRU *pstMsg
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    PS_MEM_SET(&stRpCause,0X00,sizeof(stRpCause));
    PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));
    PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));

    MN_MSG_GetMoEntity(&stMoEntity);
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_RcvSmsRpRpt:Mo State is NULL");
        return;
    }

    if (SMR_SMT_ERROR_NO_ERROR == pstMsg->enErrorCode)
    {
        MSG_DecodeRpAck(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpAck);
        if (VOS_TRUE == stRpAck.bRpUserDataExist)
        {
            stSubmitRptEvt.stRawData.ulLen = stRpAck.ucRpUserDataLen;
            PS_MEM_CPY(&(stSubmitRptEvt.stRawData.aucData[0]),
                       stRpAck.aucRpUserData,
                       stRpAck.ucRpUserDataLen);
        }
        stSubmitRptEvt.stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ACK;

        if ((MN_MSG_MO_TYPE_MO == stMoEntity.enSmsMoType)
         || (MN_MSG_MO_TYPE_BUFFER_STK == stMoEntity.enSmsMoType))
        {
            TAF_MSG_ProcEfsmsFile(&stMoEntity, &stSubmitRptEvt);
        }
        else
        {
            if (VOS_TRUE == stMoEntity.bReportFlag)
            {
                (VOS_VOID)MN_MSG_UpdateAppMemStatus(MN_MSG_MEM_FULL_UNSET);
            }

            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);
        }

        /* SMS MO SUCC事件上报 */
        stSmsMoReportPara.ulCause = MN_ERR_NO_ERROR;
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MO_SUCC,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));
    }
    else
    {
        MSG_DecodeRpErr(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpErr);
        PS_MEM_CPY(&stRpCause,&stRpErr.stRpCause,sizeof(stRpCause));
        if (VOS_TRUE == stRpErr.bRpUserDataExist)
        {
            stSubmitRptEvt.stRawData.ulLen = stRpErr.ucRpUserDataLen;
            PS_MEM_CPY(&(stSubmitRptEvt.stRawData.aucData[0]),
                       stRpErr.aucRpUserData,
                       stSubmitRptEvt.stRawData.ulLen);
        }
        stSubmitRptEvt.stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;

        MN_MNTN_RecordSmsMoFailure(MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode));

        /* SMS MO FAIL事件上报 */
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
        stSmsMoReportPara.ulCause = MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode);

        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));
    }

    stSubmitRptEvt.ucMr        = stMoEntity.ucMr;
    stSubmitRptEvt.ulSaveIndex = stMoEntity.ulSaveIndex;
    stSubmitRptEvt.enSaveArea  = stMoEntity.enSaveArea;
    stSubmitRptEvt.enErrorCode = MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode);

    /* 通知SPM短信发送结果 */
    TAF_MSG_SpmMsgReportInd(&stSubmitRptEvt, &stMoEntity, TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);

    /* destory MO entity*/
    MN_MSG_DestroyMoInfo();

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_ProcImsaIndMsg
 功能描述  : 处理来自IMSA的SMS消息
 输入参数  : pstMsg  消息指针

 输出参数  : 无

 返回值    : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_ProcImsaMsg(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                   *pstSmsMsg = VOS_NULL_PTR;

    pstSmsMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstSmsMsg->ulMsgName)
    {
        case ID_IMSA_MSG_DATA_IND:
            MSG_RcvSmsRpData((SMR_SMT_EST_IND_STRU *)pMsg);
            break;

        case ID_IMSA_MSG_REPORT_IND:
            TAF_MSG_RcvImsaRpRpt((SMR_SMT_MO_REPORT_STRU *)pMsg);
            break;

        case ID_IMSA_MSG_MT_ERR_IND:
            MSG_RcvSmsMtErrInd((SMR_SMT_MT_ERR_STRU*)pMsg);
            break;

        default:
            MN_WARN_LOG("TAF_MSG_ProcImsaMsg:Error MsgName");
            break;
    }
}
#endif
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

