#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include  "vos.h"
#include  "Taf_MmiStrParse.h"
#include  "TafAppSsa.h"
#include  "MnErrorCode.h"
/* A核和C核编解码都要用到 */
#include  "MnMsgTs.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define MN_MMI_MIN_USSD_LEN             2

#define MN_MMI_DONT_CARE_CHAR           '?'
#define MN_MMI_START_SI_CHAR            '*'
#define MN_MMI_STOP_CHAR                '#'

#define MN_MMI_isdigit(c)               (((c) >= '0') && ((c) <= '9'))

#define MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo)   ((VOS_NULL_PTR == (pcTo)) || ((VOS_NULL_PTR != (pcTo)) && ((pcFrom) <= (pcTo))))

#define MN_MMI_MAX(a, b)                (((a) > (b)) ? (a) : (b))

#define MN_MMI_MAX_SC_LEN               3                                       /* 目前来说，最大长度为3*/
#define MN_MMI_MAX_SIA_LEN              30                                      /* 来自于号码长度的最大限制 */
#define MN_MMI_MAX_SIB_LEN              8                                       /* PWD和PIN的长度 */
#define MN_MMI_MAX_SIC_LEN              8                                       /* PWD和PIN的长度 */

#define MN_MMI_MAX_BUF_SIZE             64
#define MN_MMI_MAX_PARA_NUM             4


#define MN_MMI_SC_MAX_ENTRY (sizeof(f_stMmiScInfo)/sizeof(MN_MMI_SC_TABLE_STRU))

#define MN_MMI_BS_MAX_ENTRY (sizeof(f_stMmiBSInfo)/sizeof(MN_MMI_BS_TABLE_STRU))


/*****************************************************************************
  4 类型定义
*****************************************************************************/

extern VOS_UINT32 MMI_AtoI(
           const VOS_CHAR                      *pcSrc
       );
extern VOS_BOOL MMI_DecodeScAndSi(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutMmiStr
       );
extern VOS_UINT32 MMI_FillInActivateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInCallOrigPara(
           VOS_CHAR                            *pcMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr
       );
extern VOS_UINT32 MMI_FillInDeactivateCCBSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInDeactivateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInEraseSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInInterrogateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInProcessUssdReqPara(
           VOS_CHAR                            *pcInMmiStr,
           VOS_CHAR                            **ppcOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
       );
extern VOS_UINT32 MMI_FillInRegisterSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_BOOL MMI_JudgeChldOperation(
           VOS_CHAR                            *pcInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT32                          *pulErrCode
       );
extern VOS_BOOL MMI_JudgeImeiOperation(
           VOS_CHAR                            *pcInMmiStr,
           VOS_CHAR                            **ppcOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
       );
extern VOS_VOID MMI_JudgeMmiOperationType(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode,
           VOS_UINT8                           ucNetSsCode
       );
extern  VOS_BOOL MMI_JudgePinOperation(
           VOS_CHAR                            *pMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgePwdOperation(
           VOS_CHAR                            *pMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgeSsOperation(
           VOS_CHAR                            *pInMmiStr,
           VOS_CHAR                            **ppOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgeTmpModeClirOp(
           VOS_CHAR                            *pInMmiStr,
           VOS_CHAR                            **ppOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam
       );
extern  VOS_BOOL MMI_JudgeUssdOperation(
           VOS_CHAR                            *pcMmiStr
       );
extern  VOS_BOOL MMI_MatchSsOpTbl(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode,
           VOS_UINT8                           *pucNetSsCode
       );
extern VOS_UINT32 MMI_Max(const VOS_UINT32 ulNumbera, const VOS_UINT32 ulNumberb);
extern VOS_CHAR* MMI_StrChr(
           const VOS_CHAR                      *pcFrom,
           const VOS_CHAR                      *pcTo,
           VOS_INT                              ichar
       );
extern VOS_UINT32 MMI_TransMmiBsCodeToNetBsCode(
           VOS_UINT8                           ucNetSsCode,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_UINT8                           *pucNetBsCode,
           VOS_UINT8                           *pucNetBsType
       
       );
extern VOS_UINT32 MMI_TransMmiSsCodeToNetSsCode(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_UINT8                           *pucNetSsCode
       );
extern TAF_UINT32 MN_MmiStringParse(
           TAF_CHAR                            *pInMmiStr,
           TAF_BOOL                            inCall,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           TAF_CHAR                            **ppOutRestMmiStr
       );

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

//说明：经过改造后的gtest+，测试套和测试用例名字不允许为空
//      请避免用和gtest相同的关键字，避免不必要的麻烦
//      gtest提供 EXPECT 和 ASSERT 两套,具体含义可以看胶片，两套宏都是一一对应的，下面以EXPECT为例

//1、比对布尔类型 EXPECT_TRUE　EXPECT_FALSE/ASSERT_TRUE
//2、比较整形 EXPECT_EQ EXPECT_NE
//3、比较字符串 EXPECT_STREQ
//4、设置失败输出信息 ADD_FAILUREd
//5、设置成功和失败 SUCCEED FAIL
//6、自定义格式 EXPECT_PRED_FORMAT3
//7、期望带入参数返回TRUE EXPECT_PRED1
//8、浮点型比较 EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9、类型检查 StaticAssertTypeEq
//10、设置3种测试级别事件
//11、获取测试用例名字 test_case_name()
//12、比较异常 EXPECT_THROW
//13、结构体类型比较ASSERT_SAME_DATA ASSERT_SAME_MEMORY


#if (NAS_FEATURE_CCBS == FEATURE_ON)
/******************************************************************************
类名     : Test_MMI_FillInDeactivateCCBSPara
功能描述 : MMI_FillInDeactivateCCBSPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MMI_FillInDeactivateCCBSPara: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};
/*******************************************************************
*测试项:           填写Deactivate CCBS操作需要的参数,不带Ccbsindex参数
*被测函数功能描述: 填写Deactivate CCBS操作需要的参数,不带Ccbsindex参数的处理
*预期结果：        返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_01)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(0));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_NO_ERROR);

    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.OP_CcbsIndex, VOS_FALSE);
    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.SsCode,TAF_CCBS_A_SS_CODE);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           填写Deactivate CCBS操作需要的参数,带合法Ccbsindex参数
*被测函数功能描述: 填写Deactivate CCBS操作需要的参数,带合法Ccbsindex参数的处理
*预期结果：        返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_02)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(1));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_NO_ERROR);

    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.OP_CcbsIndex, VOS_TRUE);
    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.SsCode,TAF_CCBS_A_SS_CODE);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           填写Deactivate CCBS操作需要的参数,带Ccbsindex但取值不合法>5
*被测函数功能描述: 填写Deactivate CCBS操作需要的参数,带Ccbsindex但取值不合法大于5的处理
*预期结果：        返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_03)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(6));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           填写Deactivate CCBS操作需要的参数,带Ccbsindex但取值不合法<1
*被测函数功能描述: 填写Deactivate CCBS操作需要的参数,带Ccbsindex但取值不合法小于1的处理
*预期结果：        返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_04)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(-1));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

#endif

/******************************************************************************
类名     : Test_MMI_MatchSsOpTbl
功能描述 : MMI_MatchSsOpTbl UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MMI_MatchSsOpTbl: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,解析MMI字串的Sc和Si失败
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,解析MMI字串的Sc和Si失败的处理
*预期结果：        函数返回VOS_FALSE,ulErrCode为MN_ERR_INVALIDPARM
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_01)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_FALSE);

    EXPECT_EQ(ulErrCode,MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,将Mmi字串中的Ss Code转换成网络定义的Ss Code失败,且不是USSD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,将Mmi字串中的Ss Code转换成网络定义的Ss Code失败,且不是USSD操作的处理
*预期结果：        函数返回VOS_FALSE,ulErrorCode为MN_ERR_INVALIDPARM
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_02)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_FALSE);

    EXPECT_EQ(ulErrCode,MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,将Mmi字串中的Ss Code转换成网络定义的Ss Code失败,但是USSD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,将Mmi字串中的Ss Code转换成网络定义的Ss Code失败,但是USSD操作的处理
*预期结果：        函数返回VOS_TRUE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_03)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_PROCESS_USSD_REQ);

    GlobalMockObject::verify();

}
#if(NAS_FEATURE_CCBS == FEATURE_ON)
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,是去激活CCBS的操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,是去激活CCBS的操作处理
*预期结果：        函数返回VOS_TRUE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_04)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    ucNetSsCode = TAF_CCBS_A_SS_CODE;
    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_DEACTIVATE_CCBS);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,是查询CCBS的操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,是查询CCBS的操作处理
*预期结果：        函数返回VOS_TRUE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_05)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    ucNetSsCode = TAF_CCBS_A_SS_CODE;
    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_INTERROGATE_CCBS);

    GlobalMockObject::verify();

}
#endif
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,是非CCBS相关操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,是非CCBS相关的操作处理
*预期结果：        函数返回VOS_TRUE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_06)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_DEACTIVATE_SS);

    GlobalMockObject::verify();

}

/******************************************************************************
类名     : Test_MMI_JudgeSsOperation
功能描述 : MMI_JudgeSsOperation UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MMI_JudgeSsOperation: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,SsOpTbl中找到相应操作,是CHLD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,SsOpTbl中找到相应操作,是CHLD操作的处理
*预期结果：        函数返回VOS_TRUE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_01)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(0));

    MOCKER(MMI_MatchSsOpTbl)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(exactly(1));
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_TRUE);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,SsOpTbl中找到相应操作,不是CHLD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,SsOpTbl中找到相应操作,不是CHLD操作的处理
*预期结果：        函数返回VOS_FALSE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_02)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(0));

    MOCKER(MMI_MatchSsOpTbl)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(never());
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_FALSE);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,SsOpTbl中未找到相应操作,不是USSD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,SsOpTbl中未找到相应操作,不是USSD操作的处理
*预期结果：        函数返回VOS_FALSE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_03)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(1));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(never());
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_FALSE);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,SsOpTbl中未找到相应操作,是USSD操作
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,SsOpTbl中未找到相应操作,是USSD操作的处理
*预期结果：        函数返回VOS_FALSE
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_04)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(1));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(exactly(1));
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_PROCESS_USSD_REQ);

    GlobalMockObject::verify();

}

/******************************************************************************
类名     : Test_MMI_JudgeMmiOperationType
功能描述 : MMI_JudgeMmiOperationType UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MMI_JudgeMmiOperationType: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }

};
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_REGISTER_SS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_REGISTER_SS的处理
*预期结果：        调用MMI_FillInRegisterSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_01)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_REGISTER_SS;

    MOCKER(MMI_FillInRegisterSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_ERASE_SS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_ERASE_SS的处理
*预期结果：        调用MMI_FillInEraseSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_02)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_ERASE_SS;

    MOCKER(MMI_FillInEraseSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_ACTIVATE_SS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_ACTIVATE_SS的处理
*预期结果：        调用MMI_FillInEraseSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_03)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_ACTIVATE_SS;

    MOCKER(MMI_FillInActivateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_DEACTIVATE_SS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_DEACTIVATE_SS的处理
*预期结果：        调用MMI_FillInDeactivateSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_04)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_FillInDeactivateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_INTERROGATE_SS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_INTERROGATE_SS的处理
*预期结果：        调用MMI_FillInInterrogateSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_05)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_SS;

    MOCKER(MMI_FillInInterrogateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_INTERROGATE_CCBS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_INTERROGATE_CCBS的处理
*预期结果：        调用MMI_FillInInterrogateSSPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_06)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_CCBS;

    MOCKER(MMI_FillInInterrogateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_PROCESS_USSD_REQ
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_PROCESS_USSD_REQ的处理
*预期结果：        调用MMI_FillInProcessUssdReqPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_07)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;

    MOCKER(MMI_FillInProcessUssdReqPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}
#if (NAS_FEATURE_CCBS == FEATURE_ON)
/*******************************************************************
*测试项:           判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_DEACTIVATE_CCBS
*被测函数功能描述: 判断是否是呼叫无关补充业务相关的操作,操作类型是TAF_MMI_DEACTIVATE_CCBS的处理
*预期结果：        调用MMI_FillInProcessUssdReqPara()返回成功
************************* 修改记录 *************************
#  1.日    期: 2009年12月28日
#    作    者: z161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_08)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_CCBS;

    MOCKER(MMI_FillInDeactivateCCBSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}
#endif
