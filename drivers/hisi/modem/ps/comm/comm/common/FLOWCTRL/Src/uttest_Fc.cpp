#if 1


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

using namespace testing;

#if 0
class Test_FC_POINT_Init2:public Test
{
protected:
	static void SetUpTestCase();
	static void TearDownTestCase();

	void SetUp();
	void TearDown();
};
#endif

#ifdef __cplusplus

extern "C"
{
#endif


	extern void  FC_POINT_Init( void );
	extern int  stub_FC_POINT_Init( void );
	extern unsigned int  FC_SetDebugLev( unsigned int ulLev );
	extern int stub_FC_LOG(unsigned int ulLevel, char *pcString);
	extern long vos_printf(const char * format);
	extern int stub_FC_LOG1(unsigned int ulLevel,char *pcString,int lPara1);
	extern int stub_FC_LOG2(unsigned int ulLevel,char *pcString,int lPara1,int lPara2);
	extern int stub_FC_LOG3(unsigned int ulLevel,char *pcString,int lPara1,int lPara2,int lPara3);
	extern int stub_FC_LOG4(unsigned int ulLevel,char *pcString,int lPara1,int lPara2,int lPara3,int lPara4);
	extern void FC_MNTN_TraceEvent(void *pMsg);
	extern void OM_AcpuTraceMsgHook(void * pMsg);
	extern int stub_FC_MNTN_TracePointFcEvent(void);
	extern int stub_FC_MNTN_TracePolicy(void);
	extern int stub_FC_MNTN_TraceCpuLoad(void);
	extern int stub_FC_MNTN_TraceDrvAssemPara(void);
	extern int stub_FC_IsPolicyEnable(int ulPointPolicyMask, short enModemId);
	extern void stub_FC_IsPolicyEnable_end(void);
	extern unsigned int stub_FC_RegPoint(void *pstFcRegPoint);
	extern unsigned int FC_SndRegPointMsg(void *pstFcRegPoint);
	extern int stub_FC_SetFcEnableMsk(int mask);
	extern int  stub_FC_DeRegPoint(char FcId,short ModemId);
	extern void FC_LOG1(unsigned int ulLevel,const char *pcString,int lPara1);
	extern unsigned int FC_SndDeRegPointMsg(char FcId,short ModemId);
	extern int  stub_FC_ChangePoint(char FcId,char PolicyId,char Pri,short ModemId);
	extern unsigned int FC_SndChangePointMsg(char FcId,char PolicyId,char Pri,short ModemId);
	extern int  stub_FC_POINT_Get_MaxPointNum(char FcId);
	extern int  stub_FC_POINT_Get_Fail(char FcId);
	extern int  stub_FC_POINT_Get_Succ(char FcId);
	extern int  stub_FC_POINT_Add(void);
	extern void  stub_FC_POINT_SetPointNum(int Num);
	extern void  stub_FC_POINT_Add_SetPointInfo(char FcId);
	extern void stub_FC_POINT_MemSet(void);
	extern int  stub_FC_POINT_Del(char FcId);
	extern int  stub_FC_POINT_SetFc(unsigned int PolicyMask, char FcId);
	extern void *FC_POINT_Get(char enFcId);
	extern void stub_FC_POINT_SetFc_SetPoint(unsigned int PolicyMask, char FcId, int FcMask, short ModemId,void *pSetFunc, void *pClrFunc);
	extern int  stub_FC_POINT_ClrFc(unsigned int PolicyMask, char FcId);
	extern void FC_MNTN_TracePointFcEvent(short enMsgName,void *pstFcPoint,unsigned int ulIsFuncInvoked,unsigned int ulResult);
	extern unsigned int FC_POINT_Add(void *pstFcRegPoint);
	extern int  stub_FC_POINT_Reg(void);
	extern void  FC_LOG(unsigned int ulLevel,const char *pcString);
	extern char FC_POLICY_GetPriWithFcId(char enPolicyId, char enFcId);
	extern void  FC_POLICY_AddPoint(char enPolicyId, char enFcId, char enPointPri);
	extern int  stub_FC_POINT_DeReg(char FcId, short ModemId);
	extern void  FC_POLICY_DelPoint(char enPolicyId,char enFcId);
	extern void  FC_POINT_Del(char enFcId);
	extern int  stub_FC_POINT_Change(char FcId, char PolicyId, char NewPri, short ModemId);
	extern char  FC_POLICY_GetPriWithFcId(char enPolicyId,char enFcId);
	extern int stub_FC_POLICY_TrimInvalidPri(char DonePri);
	extern int stub_FC_POLICY_UpWithOnePri(char FcIdCnt);
	extern int stub_FC_POLICY_DownWithOnePri(char FcIdCnt);
	extern int stub_FC_POLICY_Up(char DonePri, char HighestPri, char Valid);
	extern void FC_POLICY_UpWithOnePri(void *pFcPolicy, void *pstPri);
	extern void FC_MNTN_TracePolicy(short enMsgName, void *pPolicy);
    extern int stub_FC_POLICY_UpToTargetPri(char DonePri, char TargetPri, char Valid);
	extern int stub_FC_POLICY_Down(char DonePri, char Valid);
	extern void  FC_POLICY_DownWithOnePri(void *pPolicy,void *pstPri);
	extern int stub_FC_POLICY_DownToTargetPri(char DonePri, char TargetPri, char Valid);
	extern int stub_FC_POLICY_UpdateHighestPri(char Valid);
	extern int stub_FC_POLICY_AddPointForPri(char Valid, char Cnt, char PointPri, char FcId);
	extern int stub_FC_POLICY_DelPointForPri(char Cnt, char PointPri, char FcId);
	extern unsigned int FC_POLICY_ADJUST_FOR_UP_FUNC_TEMP(char enPointPri, char enFcId);
	extern int stub_FC_POLICY_AddPoint(void *pAdjustForUpFunc, char PointPri, char DonePri);
	extern void FC_POINT_SetFc(unsigned int ulPolicyMask,char enFcId);
	extern int stub_FC_POLICY_GetPriWithFcId(char FcId, char TestcaseNum);
	extern int stub_FC_POLICY_DelPoint(void *pAdjustForUpFunc);
	extern void  FC_POINT_ClrFc(unsigned int ulPolicyMask, char enFcId);
	extern char  FC_POLICY_GetPriWithFcId(char enPolicyId,char enFcId);
	extern void  FC_POLICY_DelPointForPri(void *pPolicy,char enFcId,char enPointPri);
	extern int stub_FC_POLICY_ChangePoint(void *pAdjustForUpFunc, char DonePri, char NewPri, char OldPri);
	extern void FC_POINT_ClrFc(unsigned int ulPolicyMask, char enFcId);
	extern void FC_POINT_SetFc(unsigned int ulPolicyMask, char enFcId);
	extern int stub_FC_POLICY_GetPriCnt(int Cnt);
	extern int stub_FC_POLICY_Init(void);
	extern int stub_FC_CFG_CheckCpuParam(int CpuOverLoadVal, int CpuUnderLoadVal);
	extern int stub_FC_CFG_CheckMemParam(int ThresholdCnt, int SetThreshold, int StopThreshold);
	extern int stub_FC_CFG_CheckUlRateParam(char Cnt);
	extern int stub_FC_CFG_CheckParam(int TimerLen);
	extern unsigned int  FC_CFG_CheckCpuParam( void *pstFcCfgCpu );
	extern unsigned int  FC_CFG_CheckMemParam( void *pstFcCfgMem );
	extern unsigned int FC_CFG_CheckUlRateParam( void *pstFcCfgUmUlRate );
	extern int stub_FC_CFG_SetDefaultValue(void);
	extern int stub_FC_CFG_SetNvValue(void);
	extern int stub_FC_CFG_Init(void);
	extern unsigned int NV_ReadEx(short enModemID,short usID,void *pItem,unsigned int ulLength);
	extern void  FC_CFG_SetDefaultValue( void *pstFcCfg );
	extern unsigned int  FC_CFG_CheckParam( void *pstFcCfg );
	extern void FC_CFG_SetDefaultValue( void *pstFcCfg );
	extern int stub_FC_SndCpuMsg(void);
	extern void * V_AllocMsg( unsigned int Pid, unsigned int  ulLength, unsigned int  ulFileID, unsigned int  usLineNo );
	extern unsigned int V_SendMsg( unsigned int Pid, void **ppMsg,unsigned int ulFileID, unsigned int usLineNo );
	extern int stub_FC_SndRegPointMsg(void);
	extern int stub_FC_SndDeRegPointMsg(void);
	extern int stub_FC_SndChangePointMsg(void);
	extern int stub_FC_CommInit(void);
	extern unsigned int  FC_CFG_Init( void );
	extern int stub_FC_SetDebugLev(unsigned int ulLev);
	extern int stub_FC_SetFcEnableMask(unsigned int ulEnableMask);
	extern int stub_FC_SetThreshold(int PolicyId,int Param1);
	extern int stub_FC_Help(int PointNum, int Valid, int FcIdCnt);
	extern void * V_MemCpy( void * Dest, const void * Src, unsigned long Count,
                       unsigned long ulFileID, unsigned long usLineNo );



	extern unsigned long *g_ulFcPointMgr;


#ifdef __cplusplus
}
#endif

#endif


TEST(Test_FC_POINT_Init,UT01_init)
{
	int ret = 1;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	stub_FC_POINT_MemSet();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/	

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ret = stub_FC_POINT_Init();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_LOG,UT01_print)
{
	char *s;
	unsigned int lever;
	int ret;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(2);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 0;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(vos_printf).expects(once());
    ret = stub_FC_LOG(lever,s);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
	// 还原打的函数桩
    GlobalMockObject::reset();
};


TEST(Test_FC_LOG,UT02_notprint)
{
	char *s;
	unsigned int lever;
	int ret;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(1);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 1;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	ret = stub_FC_LOG(lever,s);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_LOG1,UT01_print)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(2);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 0;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(vos_printf).expects(once());
    ret = stub_FC_LOG1(lever,s,lpara);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
	// 还原打的函数桩
    GlobalMockObject::reset();
};


TEST(Test_FC_LOG1,UT02_notprint)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(1);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 1;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	ret = stub_FC_LOG1(lever,s,lpara);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_LOG2,UT01_print)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(2);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 0;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(vos_printf).expects(once());
    ret = stub_FC_LOG2(lever,s,lpara1,lpara2);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
	// 还原打的函数桩
    GlobalMockObject::reset();
};


TEST(Test_FC_LOG2,UT02_notprint)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(1);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 1;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	ret = stub_FC_LOG2(lever,s,lpara1,lpara2);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_LOG3,UT01_print)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;
	int lpara3;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(2);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 0;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(vos_printf).expects(once());
    ret = stub_FC_LOG3(lever,s,lpara1,lpara2,lpara3);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
	// 还原打的函数桩
    GlobalMockObject::reset();
};


TEST(Test_FC_LOG3,UT02_notprint)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;
	int lpara3;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(1);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 1;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	ret = stub_FC_LOG3(lever,s,lpara1,lpara2,lpara3);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_LOG4,UT01_print)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;
	int lpara3;
	int lpara4;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(2);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 0;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(vos_printf).expects(once());
    ret = stub_FC_LOG4(lever,s,lpara1,lpara2,lpara3,lpara4);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
	// 还原打的函数桩
    GlobalMockObject::reset();
};


TEST(Test_FC_LOG4,UT02_notprint)
{
	char *s;
	unsigned int lever;
	int ret;
	int lpara1;
	int lpara2;
	int lpara3;
	int lpara4;

	/*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
	FC_SetDebugLev(1);

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	lever = 2;
	ret = 1;

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	ret = stub_FC_LOG4(lever,s,lpara1,lpara2,lpara3,lpara4);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0,ret);

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/

};


TEST(Test_FC_MNTN_TraceEvent,UT01_print)
{
	void *pMsg;

	MOCKER(OM_AcpuTraceMsgHook).expects(once());

	FC_MNTN_TraceEvent(pMsg);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_MNTN_TracePointFcEvent,UT01_print)
{
	int ret = 0;

	MOCKER(FC_MNTN_TraceEvent).expects(once());

	ret = stub_FC_MNTN_TracePointFcEvent();

	EXPECT_EQ(1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_MNTN_TracePolicy,UT01_print)
{
	int ret = 0;

	MOCKER(FC_MNTN_TraceEvent).expects(once());

	ret = stub_FC_MNTN_TracePolicy();

	EXPECT_EQ(1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_MNTN_TraceCpuLoad,UT01_print)
{
	int ret = -1;

	MOCKER(FC_MNTN_TraceEvent).expects(once());

	ret = stub_FC_MNTN_TraceCpuLoad();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_MNTN_TraceDrvAssemPara,UT01_print)
{
	int ret = -1;

	MOCKER(FC_MNTN_TraceEvent).expects(once());

	ret = stub_FC_MNTN_TraceDrvAssemPara();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_IsPolicyEnable,UT01_Modem0)
{
	int ulPointPolicyMask = 0x03FF;
	short enModemId = 0;
	int ret = 0;

	ret = stub_FC_IsPolicyEnable(ulPointPolicyMask, enModemId);

	EXPECT_EQ(0x7F, ret);

	stub_FC_IsPolicyEnable_end();
}


TEST(Test_FC_IsPolicyEnable,UT02_Modem1)
{
	int ulPointPolicyMask = 0x03FF;
	short enModemId = 1;
	int ret = 0;

	ret = stub_FC_IsPolicyEnable(ulPointPolicyMask, enModemId);

	EXPECT_EQ(0x07, ret);

	stub_FC_IsPolicyEnable_end();
}


TEST(Test_FC_RegPoint,UT01_NULL_PTR)
{
	int ret = 0;

	ret = stub_FC_RegPoint(NULL);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT02_ModemIdError)
{
	int ret = 0;

	char RegPoint[40] = {0x02,0x00,0x03,0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(&RegPoint[0]));

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT03_PolicyIdError)
{
	int ret = 0;

	char RegPoint[40] = {0x01,0x00,0x07,0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(&RegPoint[0]));

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT04_FcIdError)
{
	int ret = 0;

	char RegPoint[40] = {0x01,0x00,0x03,0x28,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT05_FcPriError1)
{
	int ret = 0;

	char RegPoint[40] = {0x01,0x00,0x03,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT06_FcPriError2)
{
	int ret = 0;

	char RegPoint[40] = {0x01,0x00,0x03,0x08,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_RegPoint,UT07_PolicyDisabled)
{
	int ret = 1;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x06,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(0, ret);

	stub_FC_SetFcEnableMsk(0);
}


TEST(Test_FC_RegPoint,UT08_MemPolicyPriError1)
{
	int ret = 0;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x00,0x08,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);

	stub_FC_SetFcEnableMsk(0);
}


TEST(Test_FC_RegPoint,UT09_MemPolicyPriError2)
{
	int ret = 0;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);

	stub_FC_SetFcEnableMsk(0);
}


TEST(Test_FC_RegPoint,UT10_pSetFuncIsNull)
{
	int ret = 0;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x02,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);

	stub_FC_SetFcEnableMsk(0);
}


TEST(Test_FC_RegPoint,UT11_pClrFuncIsNull)
{
	int ret = 0;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x02,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);

	stub_FC_SetFcEnableMsk(0);
}
#if 0

TEST(Test_FC_RegPoint,UT12_pRstFuncIsNull)
{
	int ret = 0;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x02,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(1, ret);

	stub_FC_SetFcEnableMsk(0);
}
#endif


TEST(Test_FC_RegPoint,UT13_Success)
{
	int ret = 1;

	stub_FC_SetFcEnableMsk(0x0F);

	char RegPoint[40] = {0x01,0x00,0x02,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00};

	MOCKER(FC_SndRegPointMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_RegPoint((void *)(RegPoint));

	EXPECT_EQ(0, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_DeRegPoint,UT01_FcIdInvalid)
{
    char FcId = 45;
    short ModemId = 0;
	int ret = 1;

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(-1, ret);

	FC_POINT_Init();
}


TEST(Test_FC_DeRegPoint,UT02_ModemIdInvalid)
{
    char FcId = 20;
    short ModemId = 3;
	int ret = 1;

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(-1, ret);

	FC_POINT_Init();
}


TEST(Test_FC_DeRegPoint,UT03_FcPointNone)
{
    char FcId = 20;
    short ModemId = 0;
	int ret = 1;

	FC_POINT_Init();

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(0, ret);

	FC_POINT_Init();
}


TEST(Test_FC_DeRegPoint,UT04_PolicyDisabled)
{
    char FcId = 1;
    short ModemId = 0;
	int ret = 1;

	FC_POINT_Init();
	stub_FC_SetFcEnableMsk(0);

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(0, ret);

	FC_POINT_Init();
}


TEST(Test_FC_DeRegPoint,UT05_SndMsgFail)
{
    char FcId = 1;
    short ModemId = 0;
	int ret = 1;

	FC_POINT_Init();
	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_SndDeRegPointMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(0, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();

	FC_POINT_Init();
}


TEST(Test_FC_DeRegPoint,UT06_SndMsgSucc)
{
    char FcId = 1;
    short ModemId = 0;
	int ret = 1;

	FC_POINT_Init();
	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_SndDeRegPointMsg).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_DeRegPoint(FcId, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();

	FC_POINT_Init();
}


TEST(Test_FC_ChangePoint,UT01_FcIdError)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 45;
	PolicyId = 6;
	Pri = 3;
	ModemId = 0;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT02_FcPriError1)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 0;
	ModemId = 0;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT03_FcPriError2)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 10;
	ModemId = 0;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT04_PolicyIdInvalid)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 7;
	Pri = 5;
	ModemId = 0;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT05_ModemIdInvalid)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 5;
	ModemId = 2;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT06_Disabled)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 5;
	ModemId = 1;

	stub_FC_SetFcEnableMsk(0x00);

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(0, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT07_SndMsgFail)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 5;
	ModemId = 1;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());
	MOCKER(FC_SndChangePointMsg).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(-1, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_ChangePoint,UT08_SndMsgSucc)
{
	char FcId;
	char PolicyId;
	char Pri;
	short ModemId;
	int ret = 1;

	FcId = 25;
	PolicyId = 6;
	Pri = 5;
	ModemId = 1;

	stub_FC_SetFcEnableMsk(0x7F);

	MOCKER(FC_LOG1).expects(once());
	MOCKER(FC_SndChangePointMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_ChangePoint(FcId, PolicyId, Pri, ModemId);

	EXPECT_EQ(0, ret);

	stub_FC_SetFcEnableMsk(0);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POINT_Get,UT01_ExceedMaxPointNum)
{
	int ret = 1;
	char FcId = 3;

	ret = stub_FC_POINT_Get_MaxPointNum(FcId);

	EXPECT_EQ(-1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Get,UT02_None)
{
	int ret = 1;
	char FcId = 3;

	ret = stub_FC_POINT_Get_Fail(FcId);

	EXPECT_EQ(-1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Get,UT03_Succ)
{
	int ret = 1;
	char FcId = 3;

	ret = stub_FC_POINT_Get_Succ(FcId);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Add,UT01_ExceedMaxNum)
{
	int ret = 1;

	stub_FC_POINT_SetPointNum(11);

	ret = stub_FC_POINT_Add();

	EXPECT_EQ(-1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Add,UT02_FcIdAlreadyExist)
{
	int ret = 1;

	stub_FC_POINT_Add_SetPointInfo(3);

	ret = stub_FC_POINT_Add();

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Add,UT03_FcIdNotFound)
{
	int ret = 1;

	stub_FC_POINT_Add_SetPointInfo(5);

	ret = stub_FC_POINT_Add();

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Add,UT04_ReachMaxNum)
{
	int ret = 1;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_SetPointNum(10);

	ret = stub_FC_POINT_Add();

	EXPECT_EQ(-1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Del,UT01_ExceedMaxNum)
{
	int ret = 1;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_SetPointNum(11);

	ret = stub_FC_POINT_Del(3);

	EXPECT_EQ(-1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Del,UT02_FoundFcPoint)
{
	int ret = 1;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_Add_SetPointInfo(3);

	ret = stub_FC_POINT_Del(3);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Del,UT03_FoundFcPoint2)
{
	int ret = 1;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_Add_SetPointInfo(3);

	ret = stub_FC_POINT_Del(0);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Del,UT04_NotFoundFcPoint)
{
	int ret = 1;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_Add_SetPointInfo(5);

	ret = stub_FC_POINT_Del(3);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}



TEST(Test_FC_POINT_SetFc,UT01_NotFoundFcPoint)
{
	int ret = -1;
	unsigned int PolicyMask = 0x7F;
	char FcId = 3;

	MOCKER(FC_POINT_Get).stubs().will(returnValue((void *)0));

	ret = stub_FC_POINT_SetFc(PolicyMask, FcId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POINT_SetFc,UT02_NeedSetTrueSetFuncExists)
{
	int ret = -1;
	unsigned int PolicyMask = 0x7F;
	int FcMask = 0;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	ret = stub_FC_POINT_SetFc(PolicyMask, FcId);

	EXPECT_EQ(1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_SetFc,UT03_NeedSetTrueSetFuncNull)
{
	int ret = -1;
	unsigned int PolicyMask = 0x7F;
	int FcMask = 0;
	void *pSetFunc = (void *)0;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,NULL, NULL);

	ret = stub_FC_POINT_SetFc(PolicyMask, FcId);

	EXPECT_EQ(1, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_SetFc,UT04_NeedSetFalse)
{
	int ret = -1;
	unsigned int PolicyMask = 0x7F;
	int FcMask = 1;
	void *pSetFunc = (void *)0;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,NULL, NULL);

	ret = stub_FC_POINT_SetFc(PolicyMask, FcId);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_ClrFc,UT01_NotFoundFcPoint)
{
	int ret = -1;
	unsigned int PolicyMask = 0x7F;
	char FcId = 3;

	MOCKER(FC_POINT_Get).stubs().will(returnValue((void *)0));

	ret = stub_FC_POINT_ClrFc(PolicyMask, FcId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POINT_ClrFc,UT02_NoMask)
{
	int ret = -1;
	unsigned int PolicyMask = 0x00;
	int FcMask = 1;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	ret = stub_FC_POINT_ClrFc(PolicyMask, FcId);

	EXPECT_EQ(0, ret);

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_ClrFc,UT03_NeedSetFalse)
{
	int ret = -1;
	unsigned int PolicyMask = 0x01;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_MNTN_TracePointFcEvent).expects(once());

	ret = stub_FC_POINT_ClrFc(PolicyMask, FcId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_ClrFc,UT04_NeedSetTrueSetFuncExists)
{
	int ret = -1;
	unsigned int PolicyMask = 0x01;
	int FcMask = 1;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_MNTN_TracePointFcEvent).expects(once());

	ret = stub_FC_POINT_ClrFc(PolicyMask, FcId);

	EXPECT_EQ(1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_ClrFc,UT05_NeedSetTrueSetFuncNull)
{
	int ret = -1;
	unsigned int PolicyMask = 0x01;
	int FcMask = 1;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;;
	char FcId = 3;

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask, 0,NULL, NULL);

	MOCKER(FC_MNTN_TracePointFcEvent).expects(once());

	ret = stub_FC_POINT_ClrFc(PolicyMask, FcId);

	EXPECT_EQ(1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();
}


TEST(Test_FC_POINT_Reg,UT01_AddFail)
{
	int ret = 1;

	MOCKER(FC_POINT_Add).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_POINT_Reg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POINT_Reg,UT02_PolicyHasThisFcId)
{
	int ret = 1;

	MOCKER(FC_POINT_Add).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)5));

	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_POINT_Reg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POINT_Reg,UT03_Succ)
{
	int ret = 1;

	MOCKER(FC_POINT_Add).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)10));

	MOCKER(FC_POLICY_AddPoint).expects(once());

	ret = stub_FC_POINT_Reg();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POINT_DeReg,UT01_PointNotFound)
{
	int ret = 1;
	char FcId = 3;
	short ModemId = 0;

	MOCKER(FC_POINT_Get).stubs().will(returnValue((void *)0));

	ret = stub_FC_POINT_DeReg(FcId, ModemId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POINT_DeReg,UT02_FromTheOtherModem)
{
	int ret = 1;
	char FcId = 3;
	short ModemId = 0;
	unsigned int PolicyMask = 0x01;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,1,(void *)pSetFunc, (void *)pClrFunc);

	ret = stub_FC_POINT_DeReg(FcId, ModemId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();
}


TEST(Test_FC_POINT_DeReg,UT03_FindPolicy)
{
	int ret = 1;
	char FcId = 3;
	short ModemId = 0;
	unsigned int PolicyMask = 0x03;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_SetFcEnableMsk(0x01);

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_POLICY_DelPoint).expects(once());
	MOCKER(FC_POINT_Del).expects(once());

	ret = stub_FC_POINT_DeReg(FcId, ModemId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();
}


TEST(Test_FC_POINT_DeReg,UT04_FindPolicyButDisabled)
{
	int ret = 1;
	char FcId = 3;
	short ModemId = 0;
	unsigned int PolicyMask = 0x03;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_SetFcEnableMsk(0x00);

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_POINT_Del).expects(once());

	ret = stub_FC_POINT_DeReg(FcId, ModemId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();
}


TEST(Test_FC_POINT_DeReg,UT05_NotFindPolicy)
{
	int ret = 1;
	char FcId = 3;
	short ModemId = 0;
	unsigned int PolicyMask = 0;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_SetFcEnableMsk(0x00);

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,0,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_POINT_Del).expects(once());

	ret = stub_FC_POINT_DeReg(FcId, ModemId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();
}


TEST(Test_FC_POINT_Change,UT01_NotFindPoint)
{
	int   ret = 1;
	char  FcId = 3;
	char  PolicyId;
	char  NewPri;
	short ModemId;

	MOCKER(FC_POINT_Get).stubs().will(returnValue((void *)0));

	ret = stub_FC_POINT_Change(FcId, PolicyId, NewPri, ModemId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POINT_Change,UT02_OldPriInvalid)
{
	int   ret = 1;
	char  FcId = 3;
	char  PolicyId = 0;
	char  NewPri = 0;
	short ModemId = 0;
	unsigned long Point;

	MOCKER(FC_POINT_Get).stubs().will(returnValue((void *)(&Point)));
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)10));

	ret = stub_FC_POINT_Change(FcId, PolicyId, NewPri, ModemId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POINT_Change,UT03_OldEqualsNew)
{
	int   ret = 1;
	char  FcId = 3;
	char  PolicyId = 0;
	char  NewPri = 5;
	short ModemId = 0;
	unsigned int PolicyMask = 0x01;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,1,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)5));

	ret = stub_FC_POINT_Change(FcId, PolicyId, NewPri, ModemId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POINT_Change,UT03_OldNotEqualsNew)
{
	int   ret = 1;
	char  FcId = 3;
	char  PolicyId = 0;
	char  NewPri = 6;
	short ModemId = 0;
	unsigned int PolicyMask = 0x01;
	int FcMask = 3;
	void *pSetFunc = (void *)0x123;
	void *pClrFunc = (void *)0x123;

	stub_FC_POINT_MemSet();

	stub_FC_POINT_SetFc_SetPoint(PolicyMask, FcId, FcMask,1,(void *)pSetFunc, (void *)pClrFunc);

	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)5));

	ret = stub_FC_POINT_Change(FcId, PolicyId, NewPri, ModemId);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

	stub_FC_POINT_MemSet();

}


TEST(Test_FC_POLICY_TrimInvalidPri,UT01_InvalidPri)
{
	char DonePri = 0;
	int ret = -1;

	ret = stub_FC_POLICY_TrimInvalidPri(DonePri);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_POLICY_TrimInvalidPri,UT02_AllPriValidFalse)
{
	char DonePri = 1;
	int ret = -1;

	ret = stub_FC_POLICY_TrimInvalidPri(DonePri);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_POLICY_TrimInvalidPri,UT03_NotAllPriValidFalse)
{
	char DonePri = 4;
	int ret = -1;

	ret = stub_FC_POLICY_TrimInvalidPri(DonePri);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_POLICY_UpWithOnePri,UT01_ExceedMaxNum)
{
	char FcIdCnt = 11;
	int ret = -1;

	ret = stub_FC_POLICY_UpWithOnePri(FcIdCnt);

	EXPECT_EQ(0,ret);

}


TEST(Test_FC_POLICY_UpWithOnePri,UT02_CntEquals0)
{
	char FcIdCnt = 0;
	int ret = -1;

	ret = stub_FC_POLICY_UpWithOnePri(FcIdCnt);

	EXPECT_EQ(1,ret);

}



TEST(Test_FC_POLICY_UpWithOnePri,UT03_CntValid)
{
	char FcIdCnt = 2;
	int ret = -1;

	ret = stub_FC_POLICY_UpWithOnePri(FcIdCnt);

	EXPECT_EQ(1,ret);

}


TEST(Test_FC_POLICY_DownWithOnePri,UT01_ExceedMaxNum)
{
	char FcIdCnt = 11;
	int ret = -1;

	ret = stub_FC_POLICY_DownWithOnePri(FcIdCnt);

	EXPECT_EQ(0,ret);

}


TEST(Test_FC_POLICY_DownWithOnePri,UT02_CntEquals0)
{
	char FcIdCnt = 0;
	int ret = -1;

	ret = stub_FC_POLICY_DownWithOnePri(FcIdCnt);

	EXPECT_EQ(1,ret);

}



TEST(Test_FC_POLICY_DownWithOnePri,UT03_CntValid)
{
	char FcIdCnt = 2;
	int ret = -1;

	ret = stub_FC_POLICY_DownWithOnePri(FcIdCnt);

	EXPECT_EQ(1,ret);

}


TEST(Test_FC_POLICY_Up,UT01_DoneHigherThanHighest)
{
	int ret = -1;
	char DonePri = 3;
	char HighestPri = 3;
	char Valid = 1;

	ret = stub_FC_POLICY_Up(DonePri, HighestPri, Valid);

	EXPECT_EQ(0,ret);

}


TEST(Test_FC_POLICY_Up,UT02_PriValid)
{
	int ret = -1;
	char DonePri = 3;
	char HighestPri = 7;
	char Valid = 1;

	MOCKER(FC_POLICY_UpWithOnePri).expects(once());
	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_Up(DonePri, HighestPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_Up,UT03_PriInvalid)
{
	int ret = -1;
	char DonePri = 3;
	char HighestPri = 7;
	char Valid = 0;

	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_Up(DonePri, HighestPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_UpToTargetPri,UT01_TargetInvalid)
{
	int ret = 1;
	char DonePri = 4;
	char TargetPri = 10;
	char Valid = 1;

	ret = stub_FC_POLICY_UpToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(-1,ret);

}


TEST(Test_FC_POLICY_UpToTargetPri,UT02_DoneHigherThanTarget)
{
	int ret = -1;
	char DonePri = 4;
	char TargetPri = 3;
	char Valid = 1;

	ret = stub_FC_POLICY_UpToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

}


TEST(Test_FC_POLICY_UpToTargetPri,UT03_PriValid)
{
	int ret = -1;
	char DonePri = 4;
	char TargetPri = 7;
	char Valid = 1;

	MOCKER(FC_POLICY_UpWithOnePri).expects(once());
	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_UpToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_UpToTargetPri,UT04_PriInvalid)
{
	int ret = -1;
	char DonePri = 4;
	char TargetPri = 7;
	char Valid = 0;

	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_UpToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_Down,UT01_DonePriInvalid)
{
	int ret = -1;
	char DonePri = 0;
	char Valid = 0;

	ret = stub_FC_POLICY_Down(DonePri,Valid);

	EXPECT_EQ(0,ret);
}


TEST(Test_FC_POLICY_Down,UT02_PriInvalid)
{
	int ret = -1;
	char DonePri = 3;
	char Valid = 0;

	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_Down(DonePri,Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_Down,UT03_PriValid)
{
	int ret = -1;
	char DonePri = 3;
	char Valid = 1;

	MOCKER(FC_MNTN_TracePolicy).expects(once());
	MOCKER(FC_POLICY_DownWithOnePri).expects(once());

	ret = stub_FC_POLICY_Down(DonePri,Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_DownToTargetPri,UT01_TargetInvalid)
{
	int ret = 1;
	char DonePri = 4;
	char TargetPri = 10;
	char Valid = 1;

	ret = stub_FC_POLICY_DownToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

}


TEST(Test_FC_POLICY_DownToTargetPri,UT02_PriInvalid)
{
	int ret = 1;
	char DonePri = 4;
	char TargetPri = 1;
	char Valid = 0;

	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_DownToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_DownToTargetPri,UT03_PriValid)
{
	int ret = 1;
	char DonePri = 4;
	char TargetPri = 1;
	char Valid = 1;

	MOCKER(FC_MNTN_TracePolicy).expects(once());
	MOCKER(FC_POLICY_DownWithOnePri).expects(once());

	ret = stub_FC_POLICY_DownToTargetPri(DonePri, TargetPri, Valid);

	EXPECT_EQ(0,ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_POLICY_UpdateHighestPri,UT01_PriValid)
{
	int ret = -1;
	char Valid = 1;

	ret = stub_FC_POLICY_UpdateHighestPri(Valid);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_POLICY_UpdateHighestPri,UT02_PriInvalid)
{
	int ret = -1;
	char Valid = 0;

	ret = stub_FC_POLICY_UpdateHighestPri(Valid);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_POLICY_AddPointForPri,UT01_PointPriInvalid)
{
	char Valid = 0;
	char Cnt = 1;
	char PointPri = 11;
	char FcId = 3;
	int ret = 1;

	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_POLICY_AddPointForPri(Valid, Cnt, PointPri, FcId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_AddPointForPri,UT02_ExceedMaxCnt)
{
	char Valid = 0;
	char Cnt = 11;
	char PointPri = 3;
	char FcId = 3;
	int ret = 1;

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_POLICY_AddPointForPri(Valid, Cnt, PointPri, FcId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_AddPointForPri,UT03_PriValidSameFcId)
{
	char Valid = 1;
	char Cnt = 6;
	char PointPri = 3;
	char FcId = 3;
	int ret = 1;

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_POLICY_AddPointForPri(Valid, Cnt, PointPri, FcId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_AddPointForPri,UT04_PriValidDifferentFcId)
{
	char Valid = 1;
	char Cnt = 6;
	char PointPri = 3;
	char FcId = 5;
	int ret = 1;

	ret = stub_FC_POLICY_AddPointForPri(Valid, Cnt, PointPri, FcId);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_POLICY_AddPointForPri,UT05_PriInvalid)
{
	char Valid = 0;
	char Cnt = 6;
	char PointPri = 3;
	char FcId = 5;
	int ret = 1;

	ret = stub_FC_POLICY_AddPointForPri(Valid, Cnt, PointPri, FcId);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_POLICY_DelPointForPri,UT01_PointPriInvalid)
{
	char Cnt = 1;
	char PointPri = 11;
	char FcId = 3;
	int ret = 1;

	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_POLICY_DelPointForPri(Cnt, PointPri, FcId);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_DelPointForPri,UT02_SameFcId)
{
	char Cnt = 5;
	char PointPri = 2;
	char FcId = 3;
	int ret = 1;

	ret = stub_FC_POLICY_DelPointForPri(Cnt, PointPri, FcId);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_POLICY_DelPointForPri,UT03_SameFcId2)
{
	char Cnt = 1;
	char PointPri = 2;
	char FcId = 3;
	int ret = 1;

	ret = stub_FC_POLICY_DelPointForPri(Cnt, PointPri, FcId);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_POLICY_DelPointForPri,UT04_DifferentFcId)
{
	char Cnt = 3;
	char PointPri = 2;
	char FcId = 5;
	int ret = 1;

	ret = stub_FC_POLICY_DelPointForPri(Cnt, PointPri, FcId);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_POLICY_AddPoint,UT01_pAdjustForUpFuncIsNull)
{
	void *pAdjustForUpFunc = NULL;
	char PointPri = 3;
	char DonePri = 3;

	int ret = 1;

	MOCKER(FC_POINT_SetFc).expects(once());
	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_AddPoint(pAdjustForUpFunc, PointPri, DonePri);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_AddPoint,UT02_pAdjustForUpFuncIsNotNull)
{
	void *pAdjustForUpFunc = (void *)FC_POLICY_ADJUST_FOR_UP_FUNC_TEMP;
	char PointPri = 3;
	char DonePri = 2;

	int ret = 1;

	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_AddPoint(pAdjustForUpFunc, PointPri, DonePri);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_GetPriWithFcId,UT01_AllFcIdCntInvalid)
{
	char TestcaseNum = 1;
	char FcId  = 6;

	int ret = -1;

	ret = stub_FC_POLICY_GetPriWithFcId(FcId, TestcaseNum);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_POLICY_GetPriWithFcId,UT02_AllDifferentFcId)
{
	char TestcaseNum = 2;
	char FcId  = 6;

	int ret = -1;

	ret = stub_FC_POLICY_GetPriWithFcId(FcId, TestcaseNum);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_POLICY_GetPriWithFcId,UT03_SameFcId)
{
	char TestcaseNum = 3;
	char FcId  = 6;

	int ret = -1;

	ret = stub_FC_POLICY_GetPriWithFcId(FcId, TestcaseNum);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_POLICY_DelPoint,UT01_InvalidPointPri)
{
	void *pAdjustForDownFunc = NULL;
	int ret = 1;

	MOCKER(FC_POINT_ClrFc).expects(once());
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)10));

	ret = stub_FC_POLICY_DelPoint(pAdjustForDownFunc);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_DelPoint,UT02_AdjustForDownFuncIsNull)
{
	void *pAdjustForDownFunc = NULL;
	int ret = 1;

	MOCKER(FC_POINT_ClrFc).expects(once());
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)2));
	MOCKER(FC_POLICY_DelPointForPri).expects(once());
	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_DelPoint(pAdjustForDownFunc);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_DelPoint,UT03_AdjustForDownFuncIsNotNull)
{
	void *pAdjustForDownFunc = (void *)FC_POLICY_ADJUST_FOR_UP_FUNC_TEMP;
	int ret = 1;

	MOCKER(FC_POINT_ClrFc).expects(once());
	MOCKER(FC_POLICY_GetPriWithFcId).stubs().will(returnValue((unsigned char)2));
	MOCKER(FC_POLICY_DelPointForPri).expects(once());
	MOCKER(FC_MNTN_TracePolicy).expects(once());

	ret = stub_FC_POLICY_DelPoint(pAdjustForDownFunc);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_ChangePoint,UT01_AdjustForUpFuncIsNotNullClrFlowCtrl)
{
	void *pAdjustForUpFunc = (void *)FC_POLICY_ADJUST_FOR_UP_FUNC_TEMP;
	char DonePri = 2;
	char NewPri = 3;
	char OldPri = 1;

	int ret = 1;

	MOCKER(FC_POINT_ClrFc).expects(once());

	ret = stub_FC_POLICY_ChangePoint(pAdjustForUpFunc, DonePri, NewPri, OldPri);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_ChangePoint,UT02_AdjustForUpFuncIsNullSetFlowCtrl)
{
	void *pAdjustForUpFunc = NULL;
	char DonePri = 2;
	char NewPri = 1;
	char OldPri = 3;

	int ret = 1;

	MOCKER(FC_POINT_SetFc).expects(once());

	ret = stub_FC_POLICY_ChangePoint(pAdjustForUpFunc, DonePri, NewPri, OldPri);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_POLICY_GetPriCnt,UT01_GetCnt)
{
	int Cnt = 10;
	int ret = -1;

	ret = stub_FC_POLICY_GetPriCnt(Cnt);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_POLICY_Init,UT01_Init)
{
	int ret = -1;

	ret = stub_FC_POLICY_Init();

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_CFG_CheckCpuParam,UT01_OverLoadIsLowerThanUnderLoad)
{
	int CpuOverLoadVal = 20;
	int CpuUnderLoadVal = 30;

	int ret = 1;

	ret = stub_FC_CFG_CheckCpuParam(CpuOverLoadVal, CpuUnderLoadVal);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckCpuParam,UT02_OverLoadIs0)
{
	int CpuOverLoadVal = 0;
	int CpuUnderLoadVal = 0;

	int ret = 1;

	ret = stub_FC_CFG_CheckCpuParam(CpuOverLoadVal, CpuUnderLoadVal);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckCpuParam,UT03_OverLoadIsOver100)
{
	int CpuOverLoadVal = 101;
	int CpuUnderLoadVal = 20;

	int ret = 1;

	ret = stub_FC_CFG_CheckCpuParam(CpuOverLoadVal, CpuUnderLoadVal);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckCpuParam,UT04_CheckPass)
{
	int CpuOverLoadVal = 50;
	int CpuUnderLoadVal = 20;

	int ret = 1;

	ret = stub_FC_CFG_CheckCpuParam(CpuOverLoadVal, CpuUnderLoadVal);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_CFG_CheckMemParam,UT01_ThresholdCntInvalid)
{
	int ThresholdCnt = 9;
	int SetThreshold = 10;
	int StopThreshold = 10;

	int ret = 1;

	ret = stub_FC_CFG_CheckMemParam(ThresholdCnt, SetThreshold, StopThreshold);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckMemParam,UT02_ThresholdCntIs0)
{
	int ThresholdCnt = 0;
	int SetThreshold = 10;
	int StopThreshold = 10;

	int ret = 1;

	ret = stub_FC_CFG_CheckMemParam(ThresholdCnt, SetThreshold, StopThreshold);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_CFG_CheckMemParam,UT03_MemSetIsFree)
{
	int ThresholdCnt = 5;
	int SetThreshold = 20;
	int StopThreshold = 10;

	int ret = 1;

	ret = stub_FC_CFG_CheckMemParam(ThresholdCnt, SetThreshold, StopThreshold);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckMemParam,UT04_MemSetIsNotFree)
{
	int ThresholdCnt = 4;
	int SetThreshold = 20;
	int StopThreshold = 30;

	int ret = 1;

	ret = stub_FC_CFG_CheckMemParam(ThresholdCnt, SetThreshold, StopThreshold);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_CFG_CheckUlRateParam,UT01_RateCntInvalid)
{
	char Cnt = 12;
	int ret = 1;

	ret = stub_FC_CFG_CheckUlRateParam(Cnt);

	EXPECT_EQ(-1, ret);
}


TEST(Test_FC_CFG_CheckUlRateParam,UT02_RateCntValid)
{
	char Cnt = 6;
	int ret = 1;

	ret = stub_FC_CFG_CheckUlRateParam(Cnt);

	EXPECT_EQ(0, ret);
}


TEST(Test_FC_CFG_CheckParam,UT01_TimerLenError)
{
	int ret = 1;
	int TimerLen = 1;

	MOCKER(FC_LOG1).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT02_FcCfgCpuAParamError)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT03_FcCfgCpuCParamError)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT04_FcCfgMemParamError)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)0));
	MOCKER(FC_CFG_CheckMemParam).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT05_FcCfgUmUlRateForCpuParamError)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)0));
	MOCKER(FC_CFG_CheckMemParam).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_CFG_CheckUlRateParam).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT06_FcCfgUmUlRateForTmpParamError)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)0));
	MOCKER(FC_CFG_CheckMemParam).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_CFG_CheckUlRateParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)1));
	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_CheckParam,UT07_Pass)
{
	int ret = 1;
	int TimerLen = 3;

	MOCKER(FC_CFG_CheckCpuParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)0));
	MOCKER(FC_CFG_CheckMemParam).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_CFG_CheckUlRateParam).stubs().will(returnObjectList((unsigned int)0,(unsigned int)0));

	ret = stub_FC_CFG_CheckParam(TimerLen);

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_SetDefaultValue,UT01_SetDefaultValue)
{
	int ret = 1;

	MOCKER(FC_LOG).expects(once());

	ret = stub_FC_CFG_SetDefaultValue();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();

}


TEST(Test_FC_CFG_SetNvValue,UT01_SetNvValue)
{
	int ret = 1;

	ret = stub_FC_CFG_SetNvValue();

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_CFG_Init,UT01_NvReadFail)
{
	int ret = 1;

	MOCKER(NV_ReadEx).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_LOG1).expects(once());
	MOCKER(FC_CFG_SetDefaultValue).expects(once());

	ret = stub_FC_CFG_Init();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_Init,UT02_CheckParamFail)
{
	int ret = 1;

	MOCKER(NV_ReadEx).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_LOG).expects(once());
	MOCKER(FC_CFG_CheckParam).stubs().will(returnValue((unsigned int)1));
	MOCKER(FC_CFG_SetDefaultValue).expects(once());

	ret = stub_FC_CFG_Init();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CFG_Init,UT03_OK)
{
	int ret = 1;

	MOCKER(NV_ReadEx).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_LOG).expects(never());
	MOCKER(FC_CFG_CheckParam).stubs().will(returnValue((unsigned int)0));
	MOCKER(FC_CFG_SetDefaultValue).expects(never());

	ret = stub_FC_CFG_Init();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndCpuMsg,UT01_AllocMsgFail)
{
	int ret = 1;

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)0));

	ret = stub_FC_SndCpuMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndCpuMsg,UT02_SendMsgFail)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_SndCpuMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndCpuMsg,UT03_SendMsgSucc)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_SndCpuMsg();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndRegPointMsg,UT01_AllocMsgFail)
{
	int ret = 1;

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)0));

	ret = stub_FC_SndRegPointMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndRegPointMsg,UT02_SendMsgFail)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)1));
	MOCKER(V_MemCpy).stubs().will(returnValue((void *)0));
#if 1
	ret = stub_FC_SndRegPointMsg();

	EXPECT_EQ(-1, ret);
#endif
	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndRegPointMsg,UT03_SendMsgSucc)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)0));
	MOCKER(V_MemCpy).stubs().will(returnValue((void *)0));

	ret = stub_FC_SndRegPointMsg();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndDeRegPointMsg,UT01_AllocMsgFail)
{
	int ret = 1;

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)0));

	ret = stub_FC_SndDeRegPointMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndDeRegPointMsg,UT02_SendMsgFail)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_SndDeRegPointMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndDeRegPointMsg,UT03_SendMsgSucc)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_SndDeRegPointMsg();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndChangePointMsg,UT01_AllocMsgFail)
{
	int ret = 1;

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)0));

	ret = stub_FC_SndChangePointMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndChangePointMsg,UT02_SendMsgFail)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_SndChangePointMsg();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SndChangePointMsg,UT03_SendMsgSucc)
{
	int ret = 1;

	char a[36] = {0};

	MOCKER(V_AllocMsg).stubs().will(returnValue((void *)&a[0]));
	MOCKER(V_SendMsg).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_SndChangePointMsg();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CommInit,UT01_FCCFGInitFail)
{
	int ret = 1;

	MOCKER(FC_CFG_Init).stubs().will(returnValue((unsigned int)1));

	ret = stub_FC_CommInit();

	EXPECT_EQ(-1, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_CommInit,UT02_Pass)
{
	int ret = 1;

	MOCKER(FC_CFG_Init).stubs().will(returnValue((unsigned int)0));

	ret = stub_FC_CommInit();

	EXPECT_EQ(0, ret);

	// 还原打的函数桩
    GlobalMockObject::reset();
}


TEST(Test_FC_SetDebugLev,UT01_Pass)
{
	int ret = 0;
	unsigned int lev = 30;

	ret = stub_FC_SetDebugLev(lev);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_SetFcEnableMask,UT01_Pass)
{
	int ret = 0;
	unsigned int ulEnableMask = 127;

	ret = stub_FC_SetFcEnableMask(ulEnableMask);

	EXPECT_EQ(1, ret);
}


TEST(Test_FC_SetThreshold,UT01_PolicyIsMem)
{
	int ret = -1;

	int PolicyId = 0;
	int Param1 = 0;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT02_PolicyIsCpuA)
{
	int ret = -1;

	int PolicyId = 1;
	int Param1 = 0;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT03_PolicyIsCds)
{
	int ret = -1;

	int PolicyId = 2;
	int Param1 = 0;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT04_PolicyIsCst)
{
	int ret = -1;

	int PolicyId = 3;
	int Param1 = 0;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT05_PolicyIsGors1)
{
	int ret = -1;

	int PolicyId = 4;
	int Param1 = 0;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT06_PolicyIsGors2)
{
	int ret = -1;

	int PolicyId = 4;
	int Param1 = 1;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT07_PolicyIsTmp)
{
	int ret = -1;

	int PolicyId = 5;
	int Param1 = 1;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT08_PolicyIsCpuC)
{
	int ret = -1;

	int PolicyId = 6;
	int Param1 = 1;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(1, ret);

}


TEST(Test_FC_SetThreshold,UT09_PolicyIsOtherType)
{
	int ret = -1;

	int PolicyId = 7;
	int Param1 = 1;

	ret = stub_FC_SetThreshold(PolicyId, Param1);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_Help,UT01_PointNumIs0PriInvalid)
{
	int ret = -1;

	int PointNum = 0;
	int Valid = 0;
	int FcIdCnt = 3;

	ret = stub_FC_Help(PointNum, Valid, FcIdCnt);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_Help,UT02_PriValidFcIdCntIs0)
{
	int ret = -1;

	int PointNum = 3;
	int Valid = 1;
	int FcIdCnt = 0;

	ret = stub_FC_Help(PointNum, Valid, FcIdCnt);

	EXPECT_EQ(0, ret);

}


TEST(Test_FC_Help,UT03_PriValidFcIdCntIsNot0)
{
	int ret = -1;

	int PointNum = 3;
	int Valid = 1;
	int FcIdCnt = 3;

	ret = stub_FC_Help(PointNum, Valid, FcIdCnt);

	EXPECT_EQ(0, ret);

}



