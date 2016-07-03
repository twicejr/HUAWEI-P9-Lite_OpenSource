#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include <stdio.h>
#include <stdlib.h>

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
extern "C"
{
#endif
	extern VOS_UINT32 VOS_RegisterPIDInfo( VOS_PID ulPID,
                                Init_Fun_Type pfnInitFun,
                                Msg_Fun_Type pfnMsgFun);
								
	extern VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
	extern VOS_VOID   SI_PB_PidMsgProc(struct MsgCB *pstPBMsg);
	extern VOS_VOID   PCSC_AcpuMsgProc(MsgBlock *pMsg);

    extern unsigned int uttest_CBTAPPFUN_USIMM_APP_FID_Init_case1(void);
	extern unsigned int uttest_CBTAPPFUN_USIMM_APP_FID_Init_case2(void);

#ifdef __cplusplus	
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0 
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif


TEST(CBTAPPFUN_AppFidInit1, UT)
{
    MOCKER(VOS_RegisterPIDInfo)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK)); 

    EXPECT_EQ(VOS_OK, uttest_OM_AcpuFidInit_case1());

    GlobalMockObject::reset();
}


TEST(CBTAPPFUN_AppFidInit2, UT)
{
    MOCKER(VOS_RegisterPIDInfo)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_ERR, uttest_OM_AcpuFidInit_case1());

    GlobalMockObject::reset();
}


TEST(CBTAPPFUN_AppFidInit3, UT)
{
    MOCKER(VOS_RegisterPIDInfo)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR)); 

    EXPECT_EQ(VOS_ERR, uttest_OM_AcpuFidInit_case1());

    GlobalMockObject::reset();
}

TEST(CBTAPPFUN_AppFidInit4, UT)
{
    EXPECT_EQ(VOS_OK, uttest_OM_AcpuFidInit_case2());

    GlobalMockObject::reset();
}
#if 0

TEST(CBTPPM_OamCbtPortInit2, UT)
{
	MOCKER(NV_ReadEx)
		.stubs()
		.with(any(), any(),outBoundP(uttest_GetPortTypePtr()), any())
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTPPM_OamVComCbtPortInit)
		.expects(once());

	uttest_CBTPPM_OamCbtPortInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtPortInit1, UT)
{
	MOCKER(CBTCPM_PortRcvReg)
		.expects(once());

	MOCKER(APP_VCOM_RegDataCallback)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTCPM_PortSndReg)
		.expects(once());

	uttest_CBTPPM_OamVComCbtPortInit_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtSendData1, UT)
{
	MOCKER(APP_VCOM_Send)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK,uttest_CBTPPM_OamVComCbtSendData_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData1, UT)
{
	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamVComCbtReadData_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData2, UT)
{
	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamVComCbtReadData_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData3, UT)
{
	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamVComCbtReadData_case3());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData4, UT)
{
	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue((void *)0));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamVComCbtReadData_case4());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData5, UT)
{
	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr1()));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamVComCbtReadData_case5());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamVComCbtReadData6, UT)
{
	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr2()));

	EXPECT_EQ(VOS_OK, uttest_CBTPPM_OamVComCbtReadData_case6());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtPortInit1, UT)
{
	MOCKER(CBTCPM_PortRcvReg)
		.expects(once());

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	MOCKER(CBTCPM_PortSndReg)
		.expects(once());

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtPortInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtPortInit2, UT)
{
	MOCKER(CBTCPM_PortRcvReg)
		.expects(once());

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTCPM_PortSndReg)
		.expects(once());

	MOCKER(BSP_USB_RegUdiEnableCB)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(BSP_USB_RegUdiDisableCB)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_CBTPPM_OamUsbCbtPortInit_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit1, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	uttest_CBTPPM_OamCbtPortDataInit_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit2, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)-1));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit3, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit4, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((int)VOS_OK, (int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit5, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((int)VOS_OK, (int)VOS_OK, (int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit6, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((int)VOS_OK, (int)VOS_OK,  (int)VOS_OK,(int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit7, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((int)VOS_OK, (int)VOS_OK, (int)VOS_OK, (int)VOS_OK,(int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit8, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((int)VOS_OK, (int)VOS_OK, (int)VOS_OK, (int)VOS_OK, (int)VOS_OK,(int)VOS_ERR));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataInit9, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_open)
		.stubs()
		.will(returnValue((int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((int)VOS_OK));

	uttest_CBTPPM_OamCbtPortDataInit_case2();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtReadDataCB1, UT)
{
	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtReadDataCB_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtReadDataCB2, UT)
{
	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtReadDataCB_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtReadDataCB3, UT)
{
	MOCKER(udi_ioctl)
		.stubs()
		.will(returnObjectList((unsigned int)VOS_ERR, (unsigned int)VOS_OK));

	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr1()));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtReadDataCB_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtReadDataCB4, UT)
{
	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr2()));

	EXPECT_EQ(VOS_OK, uttest_CBTPPM_OamUsbCbtReadDataCB_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtStatusCB1, UT)
{
    MOCKER(CBTCPM_GetRcvFunc)
        .stubs()
        .will(returnValue((void *)1));

    MOCKER(PPM_DisconnectGUPort)
		.expects(once())
        .will(returnValue((unsigned int)VOS_OK));

	uttest_CBTPPM_OamUsbCbtStatusCB_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtStatusCB2, UT)
{
	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue((void *)0));

	MOCKER(PPM_DisconnectGUPort)
		.expects(exactly(0))
        .will(returnValue((unsigned int)VOS_OK));

	uttest_CBTPPM_OamUsbCbtStatusCB_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtWriteDataCB1, UT)
{
	MOCKER(VOS_SmV)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	uttest_CBTPPM_OamUsbCbtWriteDataCB_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtPortClose0, UT)
{
	uttest_CBTPPM_OamUsbCbtPortClose_case0();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtPortClose1, UT)
{
	MOCKER(udi_close)
		.stubs()
		.will(returnValue((int)0));

	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue((void *)0));

	uttest_CBTPPM_OamUsbCbtPortClose_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtPortClose2, UT)
{
	MOCKER(udi_close)
		.stubs()
		.will(returnValue((int)0));

	MOCKER(CBTCPM_GetRcvFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr1()));

	MOCKER(PPM_DisconnectGUPort)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	uttest_CBTPPM_OamUsbCbtPortClose_case1();

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataSnd1, UT)
{
	MOCKER(CBTCPM_GetSndFunc)
		.stubs()
		.will(returnValue((void *)0));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamCbtPortDataSnd_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamCbtPortDataSnd2, UT)
{
	MOCKER(CBTCPM_GetSndFunc)
		.stubs()
		.will(returnValue(uttest_CBTCPM_GetRcvFuncPtr1()));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamCbtPortDataSnd_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData1, UT)
{
	EXPECT_EQ(2, uttest_CBTPPM_OamUsbCbtSendData_case1());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData2, UT)
{	
	EXPECT_EQ(2, uttest_CBTPPM_OamUsbCbtSendData_case2());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData3, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)100));

	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(VOS_SmP)
		.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtSendData_case3());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData4, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)100));

	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)120));

	MOCKER(VOS_SmP)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_CBTPPM_OamUsbCbtSendData_case3());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData5, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)100));

	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue(-1));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtSendData_case3());

	GlobalMockObject::reset();
}


TEST(CBTPPM_OamUsbCbtSendData6, UT)
{
	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)100));

	MOCKER(OM_GetSlice)
		.stubs()
		.will(returnValue((unsigned int)80));

	MOCKER(BSP_MNTN_SystemError)
		.expects(once());

	MOCKER(udi_ioctl)
		.stubs()
		.will(returnValue(-1));

	EXPECT_EQ(VOS_ERR, uttest_CBTPPM_OamUsbCbtSendData_case3());

	GlobalMockObject::reset();
}
#endif