#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "MnMsgTs.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#include "MnErrorCode.h"
#include "mnmsgcbencdec.h"
#include "TafStdlib.h"
#include "Taf_MmiStrParse.h"

/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_ENCODE_C

extern VOS_UINT32 MSG_EncodeUserData(
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_USER_DATA_STRU               *pstUserData,
    VOS_UINT8                           *pucUserData,
    VOS_UINT32                          *pucLen
);

extern VOS_UINT32 MN_MSG_DecodeDcsIf01(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
);

extern MN_MSG_CBLANG_ENUM_U8 MN_MSG_Iso639LangToDef(
    MN_MSG_ISO639_LANG_ENUM_U16         enIso639Lang
);

/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
extern VOS_BOOL MMI_DecodeScAndSi(
                           VOS_CHAR                            *pInMmiStr,
                           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
                           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
                           VOS_CHAR                            **ppOutMmiStr
);

extern VOS_BOOL MMI_MatchSsOpTbl(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           *pucNetSsCode
);

extern void UT_STUB_INIT(void);

#ifdef  __cplusplus
  #if  __cplusplus
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

/*****************************************************************************
类名     : Test_MN_MSG_EncodeTpRd
功能描述 : Test_MN_MSG_EncodeTpRd UT工程类
修改历史     :

1.日   期  : 2012-11-10
  作   者  : f62575
  修改内容 : 新生成类
*****************************************************************************/
class Test_MN_MSG_EncodeTpRd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};

/*******************************************************************
测试用例编号      : Test_MN_MSG_EncodeTpRd_001
测试用例标题      : 编码TP-RD参数到TP-FO：设置TP-RD为1
预期结果          : 输出正确置位的TP-FO
1.日   期  : 2012-11-10
  作   者  : f62575
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_MN_MSG_EncodeTpRd, Test_MN_MSG_EncodeTpRd_001)
{
    /*变量定义*/
    VOS_BOOL                            bRejectDuplicates;
    VOS_UINT8                           ucTpFo;
    VOS_UINT8                           ucTpCmpFo;

    /* 初始化变量 */
    ucTpFo = 33;
    bRejectDuplicates = VOS_TRUE;

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    MN_MSG_EncodeTpRd(bRejectDuplicates, &ucTpFo);

    /* 结果验证*/
    ucTpCmpFo = ucTpFo | 0x04;
    EXPECT_EQ(ucTpCmpFo, ucTpFo);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_MN_MSG_EncodeTpRd_002
测试用例标题      : 编码TP-RD参数到TP-FO：设置TP-RD为0
预期结果          : 输出正确置位的TP-FO
1.日   期  : 2012-11-10
  作   者  : f62575
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_MN_MSG_EncodeTpRd, Test_MN_MSG_EncodeTpRd_002)
{
    /*变量定义*/
    VOS_BOOL                            bRejectDuplicates;
    VOS_UINT8                           ucTpFo;
    VOS_UINT8                           ucTpCmpFo;

    /* 初始化变量 */
    ucTpFo = 33;
    bRejectDuplicates = VOS_FALSE;

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    MN_MSG_EncodeTpRd(bRejectDuplicates, &ucTpFo);

    /* 结果验证*/
    ucTpCmpFo = ucTpFo;
    EXPECT_EQ(ucTpCmpFo, ucTpFo);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
类名     : Test_MN_MSG_EncodeAddress
功能描述 : MN_MSG_EncodeAddress UT工程类
修改历史     :

1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*****************************************************************************/
class Test_MN_MSG_EncodeAddress: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};

/*******************************************************************
测试用例编号      : Test_MN_MSG_EncodeAddress_001
测试用例标题      : 短信中心号码编码失败；
预期结果          : 输出正确置位的TP-FO
1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*******************************************************************/
TEST_F(Test_MN_MSG_EncodeAddress, Test_MN_MSG_EncodeAddress_001)
{
    /*变量定义*/
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    VOS_UINT8                           aucAddr[255];
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucAsciiNum[] = {0x80, 0x31};
    VOS_UINT32                          ulRet;

    /* 初始化变量 */

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    PS_MEM_SET(&stAsciiAddr, 0, sizeof(stAsciiAddr));
    stAsciiAddr.enNumPlan = MN_MSG_NPI_SC_SPECIFIC1;
    stAsciiAddr.enNumType = MN_MSG_TON_ALPHANUMERIC;
    stAsciiAddr.ulLen     = 2;
    PS_MEM_CPY(stAsciiAddr.aucAsciiNum, aucAsciiNum, sizeof(aucAsciiNum));
    PS_MEM_SET(aucAddr, 0, sizeof(aucAddr));
    ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_FALSE, aucAddr, &ulLen);

    /* 结果验证*/
    EXPECT_EQ(MN_ERR_CLASS_INVALID_TP_ADDRESS, ulRet);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_MSG_EncodeUserData
功能描述 : MSG_EncodeUserData UT工程类
修改历史     :

1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*****************************************************************************/
class Test_MSG_EncodeUserData: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};

/*******************************************************************
测试用例编号      : Test_MSG_EncodeUserData_001
测试用例标题      : 短信中心号码编码失败；
预期结果          : 输出正确置位的TP-FO
1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*******************************************************************/
TEST_F(Test_MSG_EncodeUserData, Test_MSG_EncodeUserData_001)
{
    /*变量定义*/
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               stUserData;
    VOS_UINT8                           aucUserData[255];
    VOS_UINT8                           aucOrigUserData[] = {0x80, 0x31};
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    /* 初始化变量 */

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    PS_MEM_SET(&stUserData, 0, sizeof(stUserData));
    stUserData.ulLen = sizeof(aucOrigUserData);
    ulLen   = 0;
    PS_MEM_CPY(stUserData.aucOrgData, aucOrigUserData, sizeof(aucOrigUserData));
    ulRet = MSG_EncodeUserData(enMsgCoding, &stUserData, aucUserData, &ulLen);

    /* 结果验证*/
    EXPECT_EQ(MN_ERR_CLASS_INVALID_TP_UD, ulRet);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
类名     : Test_MN_MSG_DecodeCbsDcs
功能描述 : MN_MSG_DecodeCbsDcs UT工程类
修改历史 :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_MN_MSG_DecodeCbsDcs: public ::testing::Test
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
测试用例编号      : Test_MN_MSG_DecodeCbsDcs_001
测试用例标题      : 编码消息内容长度非法
预期结果          : 返回MN_ERR_CLASS_SMS_INVALID_MSG_LANG
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_MN_MSG_DecodeCbsDcs, Test_MN_MSG_DecodeCbsDcs_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucContent[TAF_MSG_CBA_LANG_LENGTH] = {0};
    VOS_UINT32                          ulContentLength;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo = {0};

    // 参数初始化
    ulContentLength = TAF_MSG_CBA_LANG_LENGTH - 1;
    ucDcs           = 0x10;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = MN_MSG_DecodeCbsDcs(ucDcs, aucContent, ulContentLength, &stDcsInfo);

    // 执行检查
    EXPECT_EQ(MN_ERR_CLASS_SMS_INVALID_MSG_LANG, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_MN_MSG_DecodeCbsDcs_002
测试用例标题      : 编码消息内容长度非法
预期结果          : 返回MN_ERR_CLASS_SMS_INVALID_MSG_LANG
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_MN_MSG_DecodeCbsDcs, Test_MN_MSG_DecodeCbsDcs_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucContent[TAF_MSG_CBA_LANG_LENGTH] = {0};
    VOS_UINT32                          ulContentLength;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo = {0};

    // 参数初始化
    ulContentLength = TAF_MSG_CBA_LANG_LENGTH;
    ucDcs           = 0x10;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(MN_MSG_DecodeDcsIf01)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MOCKER(TAF_STD_UnPack7Bit)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_MSG_Iso639LangToDef)
        .expects(exactly(1))
        .will(returnValue((MN_MSG_CBLANG_ENUM_U8)MN_MSG_CBLANG_ENGLISH));

    // 调用被测函数
    ulRet = MN_MSG_DecodeCbsDcs(ucDcs, aucContent, ulContentLength, &stDcsInfo);

    // 执行检查
    EXPECT_EQ(MN_ERR_NO_ERROR, ulRet);

    GlobalMockObject::verify();
}



