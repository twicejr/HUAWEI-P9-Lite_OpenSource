#include "si_pb.h"
#include "siapppih.h"
#include "NVIM_Interface.h"
#include "si_pih.h"

extern VOS_UINT32 SI_PIH_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid);

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GetReceiverPid_case1(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT32                          ulPID;

    if (VOS_ERR != SI_PIH_GetReceiverPid(0, &ulPID))
    {
	    return VOS_ERR;
    }
#endif

    return VOS_OK;

}

/*******************************************************************
*测试项:MODEMID0
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GetReceiverPid_case2(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT32                          ulPID;

	if ((VOS_OK != SI_PIH_GetReceiverPid(0, &ulPID))
        || (I0_MAPS_PIH_PID != ulPID))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GetReceiverPid_case3(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulPID;

    if ((VOS_OK != SI_PIH_GetReceiverPid(0, &ulPID))
        || (I1_MAPS_PIH_PID != ulPID))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GetReceiverPid_case4(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulPID;

    if ((VOS_OK != SI_PIH_GetReceiverPid(0, &ulPID))
        || (I0_MAPS_PIH_PID != ulPID))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_IsSvlte_case1(VOS_VOID)
{
    if (VOS_FALSE == SI_PIH_IsSvlte())
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

SVLTE_SUPPORT_FLAG_STRU             g_stSvlteFlag;

VOS_UINT32 uttest_NV_ReadEx_stub1(MODEM_ID_ENUM_UINT16           enModemID,
                     VOS_UINT16                  usID,
                     VOS_VOID                   *pItem,
                     VOS_UINT32                  ulLength)
{
    g_stSvlteFlag.ucSvlteSupportFlag = VOS_TRUE;

    memcpy(pItem, &g_stSvlteFlag, sizeof(SVLTE_SUPPORT_FLAG_STRU));

    return NV_OK;
}

/*******************************************************************
*测试项:NV项读取成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_IsSvlte_case2(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (VOS_TRUE == SI_PIH_IsSvlte())
#else
    if (VOS_FALSE == SI_PIH_IsSvlte())
#endif
    {

        return VOS_OK;
    }

    return VOS_ERR;
}


/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnBdnQuery_case1(VOS_VOID)
{
	if (TAF_FAILURE == SI_PIH_FdnBdnQuery(0,0,0))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnBdnQuery_case2(VOS_VOID)
{
	if (TAF_SUCCESS == SI_PIH_FdnBdnQuery(0,0,0))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项: 查询当前的BDN状态
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnBdnQuery_case3(VOS_VOID)
{
    if (TAF_SUCCESS == SI_PIH_FdnBdnQuery(0,0,1))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnBdnQuery_case4(VOS_VOID)
{
    if (TAF_FAILURE == SI_PIH_FdnBdnQuery(0,0,1))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnBdnQuery_case5(VOS_VOID)
{
    if (TAF_FAILURE == SI_PIH_FdnBdnQuery(0,0,1))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case1(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 0;

	if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case2(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 0;

    if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case3(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 20;

    if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case4(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 2;

    if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case5(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 2;

    if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case6(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU            stData;

	stData.ulLen = 20;

    if (TAF_FAILURE == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_GenericAccessReq_case7(VOS_VOID)
{
	SI_PIH_CSIM_COMMAND_STRU stData;

	stData.ulLen = 5;

    if (TAF_SUCCESS == SI_PIH_GenericAccessReq(0,0,&stData))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnEnable_case1(VOS_VOID)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

	if (TAF_FAILURE == SI_PIH_FdnEnable(ClientId,OpId,aucPIN2))
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnEnable_case2(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_OFF)
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

	if (TAF_FAILURE != SI_PIH_FdnEnable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}
#else
    return VOS_OK;
#endif
}

/*******************************************************************
*测试项:申请消息内存失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnEnable_case3(VOS_VOID)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

	if (TAF_FAILURE != SI_PIH_FdnEnable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}

	return VOS_OK;
}

/*******************************************************************
*测试项:消息发送失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnEnable_case4(VOS_VOID)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

	if (TAF_FAILURE != SI_PIH_FdnEnable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}

    return VOS_OK;
}

/*******************************************************************
*测试项:消息发送成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PIH_FdnEnable_case5(VOS_VOID)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

    if (TAF_SUCCESS != SI_PIH_FdnEnable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}

    return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_FdnDisable_case1(void)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

	if (TAF_FAILURE != SI_PIH_FdnDisable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}

	return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_FdnDisable_case2(void)
{
#if (FEATURE_MULTI_MODEM == FEATURE_OFF)

	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

	if (TAF_FAILURE != SI_PIH_FdnDisable(ClientId,OpId,aucPIN2))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_FdnDisable_case3(void)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

	if (TAF_FAILURE != SI_PIH_FdnDisable(ClientId,OpId,aucPIN2))
    {
	    return VOS_ERR;
	}

	return VOS_OK;

}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_FdnDisable_case4(void)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

	if (TAF_FAILURE != SI_PIH_FdnDisable(ClientId,OpId,aucPIN2))
    {
	    return VOS_ERR;
	}

	return VOS_OK;
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_FdnDisable_case5(void)
{
	MN_CLIENT_ID_T     ClientId;
	MN_OPERATION_ID_T  OpId;
	VOS_UINT8          aucPIN2[10];

	ClientId = 0;
	OpId = 0;

	gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

	if (TAF_SUCCESS != SI_PIH_FdnDisable(ClientId,OpId,aucPIN2))
	{
	    return VOS_ERR;
	}

	return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_001
测试用例标题      : 输入的APDU长度为0
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_IsdbAccessReq_case1(void)
{
	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;
	stData.ulLen						=	0;

	// 调用被测函数
	ulRet = SI_PIH_IsdbAccessReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_001
测试用例标题      : 输入的APDU长度为0
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_IsdbAccessReq_case2(void)
{

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;
	stData.ulLen						=	0;

	// 调用被测函数
	ulRet = SI_PIH_IsdbAccessReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_IsdbAccessReq_case3(void)
{

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;
	stData.ulLen						=	20;

	stData.aucCommand[4]				=	15;

	// 调用被测函数
	ulRet = SI_PIH_IsdbAccessReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_IsdbAccessReq_case4(void)
{

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;
	stData.ulLen						=	8;

	stData.aucCommand[4]				=	3;

	// 调用被测函数
	ulRet = SI_PIH_IsdbAccessReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_IsdbAccessReq_case5(void)
{

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;
	stData.ulLen						=	8;

	stData.aucCommand[4]				=	3;

	// 调用被测函数
	ulRet = SI_PIH_IsdbAccessReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_001
测试用例标题      : 参数检测失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchoSetReq_case1(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CCHO_COMMAND_STRU            stCchoCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCchoCmd.ulAIDLen      			=	USIMM_AID_LEN_MAX*2 + 1;

    // 调用被测函数
    ulRet = SI_PIH_CchoSetReq(ClientId, OpId, &stCchoCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_002
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchoSetReq_case2(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CCHO_COMMAND_STRU            stCchoCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCchoCmd.ulAIDLen      			=	USIMM_AID_LEN_MAX;

    // 调用被测函数
    ulRet = SI_PIH_CchoSetReq(ClientId, OpId, &stCchoCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_003
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchoSetReq_case3(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CCHO_COMMAND_STRU            stCchoCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCchoCmd.ulAIDLen      			=	USIMM_AID_LEN_MAX;

    // 调用被测函数
    ulRet = SI_PIH_CchoSetReq(ClientId, OpId, &stCchoCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchoSetReq_case4(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CCHO_COMMAND_STRU            stCchoCmd;
    SI_PIH_CCHO_SET_REQ_STRU            stCchoMsg;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCchoCmd.ulAIDLen      			=	USIMM_AID_LEN_MAX;
    stCchoCmd.pucADFName                =   stCchoMsg.aucADFName;

    // 调用被测函数
    ulRet = SI_PIH_CchoSetReq(ClientId, OpId, &stCchoCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_005
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchoSetReq_case5(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CCHO_COMMAND_STRU            stCchoCmd;
    SI_PIH_CCHO_SET_REQ_STRU            stCchoMsg;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCchoCmd.ulAIDLen      			=	USIMM_AID_LEN_MAX;
    stCchoCmd.pucADFName                =   stCchoMsg.aucADFName;

    // 调用被测函数
    ulRet = SI_PIH_CchoSetReq(ClientId, OpId, &stCchoCmd);

    // 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_001
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchcSetReq_case1(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT32                          ulSessionID;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    ulSessionID              			=	1;

    // 调用被测函数
    ulRet = SI_PIH_CchcSetReq(ClientId, OpId, ulSessionID);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_002
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchcSetReq_case2(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT32                          ulSessionID;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    ulSessionID              			=	1;

    // 调用被测函数
    ulRet = SI_PIH_CchcSetReq(ClientId, OpId, ulSessionID);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchcSetReq_case3(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT32                          ulSessionID;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    ulSessionID              			=	1;

    // 调用被测函数
    ulRet = SI_PIH_CchcSetReq(ClientId, OpId, ulSessionID);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_004
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CchcSetReq_case4(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT32                          ulSessionID;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    ulSessionID              			=	1;

    // 调用被测函数
    ulRet = SI_PIH_CchcSetReq(ClientId, OpId, ulSessionID);

    // 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_001
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CglaSetReq_case1(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CGLA_COMMAND_STRU            stCglaCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCglaCmd.ulLen           			=	0;

    // 调用被测函数
    ulRet = SI_PIH_CglaSetReq(ClientId, OpId, &stCglaCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_002
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CglaSetReq_case2(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CGLA_COMMAND_STRU            stCglaCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCglaCmd.ulLen           			=	0;

    // 调用被测函数
    ulRet = SI_PIH_CglaSetReq(ClientId, OpId, &stCglaCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CglaSetReq_case3(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CGLA_COMMAND_STRU            stCglaCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCglaCmd.ulLen           			=	0;

    // 调用被测函数
    ulRet = SI_PIH_CglaSetReq(ClientId, OpId, &stCglaCmd);

    // 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_004
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
unsigned int uttest_SI_PIH_CglaSetReq_case4(void)
{
    // 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_CGLA_COMMAND_STRU            stCglaCmd;
    SI_UINT32                           ulRet;

    ClientId							=	1;
    OpId								=	1;
    stCglaCmd.ulLen           			=	0;

    // 调用被测函数
    ulRet = SI_PIH_CglaSetReq(ClientId, OpId, &stCglaCmd);

    // 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_001
测试用例标题      : 参数检测空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    VSIM_KEYDATA_STRU                  *pstSKey = VOS_NULL_PTR;

    if (TAF_FAILURE != SI_PIH_HvsDHSet(0, 0, pstSKey))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_002
测试用例标题      : 参数检测长度过大
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    VSIM_KEYDATA_STRU                   stSKey;

    stSKey.ulKeyLen = VSIM_KEYLEN_MAX + 1;

    if (TAF_FAILURE != SI_PIH_HvsDHSet(0, 0, &stSKey))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_003
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	VSIM_KEYDATA_STRU                   stSKey;

	stSKey.ulKeyLen = VSIM_KEYLEN_MAX;

	if (TAF_FAILURE != SI_PIH_HvsDHSet(0, 0, &stSKey))
	{
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_004
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    VSIM_KEYDATA_STRU                   stSKey;

    stSKey.ulKeyLen = VSIM_KEYLEN_MAX;

    if (TAF_FAILURE != SI_PIH_HvsDHSet(0, 0, &stSKey))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_005
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case5(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    VSIM_KEYDATA_STRU                   stSKey;

    stSKey.ulKeyLen = 4;

    if (TAF_FAILURE != SI_PIH_HvsDHSet(0, 0, &stSKey))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_006
测试用例标题      : 服务器密钥设置请求发到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHSet_case6(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    VSIM_KEYDATA_STRU                   stSKey;

    stSKey.ulKeyLen = 4;

    if (TAF_SUCCESS != SI_PIH_HvsDHSet(0, 0, &stSKey))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_001
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHQuery_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvsDHQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHQuery_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvsDHQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHQuery_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvsDHQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_004
测试用例标题      : 密钥查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsDHQuery_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_SUCCESS, SI_PIH_HvsDHQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;

}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_001
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsContQuery_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE, SI_PIH_HvsContQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}


/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsContQuery_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE, SI_PIH_HvsContQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsContQuery_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE, SI_PIH_HvsContQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_004
测试用例标题      : 文件内容查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvsContQuery_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_SUCCESS != SI_PIH_HvsContQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_001
测试用例标题      : client转换为ulReceiverPid失败)
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstQuery_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvSstQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}


/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstQuery_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvSstQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstQuery_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    SI_PIH_MSG_HEADER_STRU              stMsg;

    if (TAF_FAILURE != SI_PIH_HvSstQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_004
测试用例标题      : 卡状态查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstQuery_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_SUCCESS != SI_PIH_HvSstQuery(0, 0))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_001
测试用例标题      : 参数检测失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstSet_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    if (TAF_FAILURE != SI_PIH_HvSstSet(0, 0, VOS_NULL_PTR))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_002
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstSet_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_HVSST_SET_STRU              stHvSStSet;

	if (TAF_FAILURE != SI_PIH_HvSstSet(0, 0, &stHvSStSet))
	{
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_003
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstSet_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    SI_PIH_HVSST_SET_STRU              stHvSStSet;

    if (TAF_FAILURE != SI_PIH_HvSstSet(0, 0, &stHvSStSet))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstSet_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    SI_PIH_HVSST_SET_STRU              stHvSStSet;

    if (TAF_FAILURE != SI_PIH_HvSstSet(0, 0, &stHvSStSet))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_005
测试用例标题      : 卡状态设置发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
unsigned int uttest_SI_PIH_HvSstSet_case5(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

    SI_PIH_HVSST_SET_STRU              stHvSStSet;

    if (TAF_SUCCESS != SI_PIH_HvSstSet(0, 0, &stHvSStSet))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_001
*被测函数功能描述:client转换为ulReceiverPid失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case1(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_002
*被测函数功能描述:pstData为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case2(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     *pstData;

	pstData = VOS_NULL_PTR;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}


/*******************************************************************
*测试项:SI_PIH_AtFileWrite_003
*被测函数功能描述:1 pstData不为空
                  2 pstData中文件内容为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case3(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    pstData.ulIndex = 1;

	pstData.stFileData.pucData = VOS_NULL_PTR;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_004
*被测函数功能描述:1 pstData不为空
                  2 pstData中文件长度为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case4(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    pstData.ulIndex = 1;

	pstData.stFileData.ulDataLen = VOS_NULL_PTR;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_005
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case5(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    pstData.ulIndex = 1;

    VOS_UINT8 ucFileName[6] = "test1";
	VOS_UINT8 ucFileData[5] = "name";

	pstData.stFileData.ulDataLen = 6;
	pstData.stFileData.pucData = ucFileData;
    pstData.stFileName.pucData = ucFileName;
	pstData.stFileName.ulDataLen = 4;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_006
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存成功
                  4 发送消息失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case6(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    pstData.ulIndex = 1;

    VOS_UINT8 ucFileName[6] = "test1";
	VOS_UINT8 ucFileData[4] = "msg";

	pstData.stFileData.ulDataLen = 6;
	pstData.stFileData.pucData = ucFileData;
    pstData.stFileName.pucData = ucFileName;
	pstData.stFileName.ulDataLen = 4;

    if (TAF_FAILURE != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_007
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存成功
                  4 发送消息成功
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_PIH_AtFileWrite_case7(void)
{
#if (FEATURE_VSIM == FEATURE_ON)

	SI_PIH_FILEWRITE_DATA_STRU     pstData;

    pstData.ulIndex = 1;

    VOS_UINT8 ucFileName[6] = "test1";
	VOS_UINT8 ucFileData[4] = "msg";

	pstData.stFileData.ulDataLen = 6;
	pstData.stFileData.pucData = ucFileData;
    pstData.stFileName.pucData = ucFileName;
	pstData.stFileName.ulDataLen = 4;

    if (TAF_SUCCESS != SI_PIH_AtFileWrite(0, 0, &pstData))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_001
测试用例标题      : Client Id转换失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_UiccAuthReq_case1(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_UICCAUTH_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_UICCAUTH_STRU));

	// 调用被测函数
	ulRet = SI_PIH_UiccAuthReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_002
测试用例标题      : 鉴权参数为空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_UiccAuthReq_case2(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	// 调用被测函数
	ulRet = SI_PIH_UiccAuthReq(ClientId, OpId, VOS_NULL_PTR);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_UiccAuthReq_case3(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_UICCAUTH_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_UICCAUTH_STRU));

	// 调用被测函数
	ulRet = SI_PIH_UiccAuthReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_UiccAuthReq_case4(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_UICCAUTH_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_UICCAUTH_STRU));

	// 调用被测函数
	ulRet = SI_PIH_UiccAuthReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_UiccAuthReq_case5(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_UICCAUTH_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_UICCAUTH_STRU));

	// 调用被测函数
	ulRet = SI_PIH_UiccAuthReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_001
测试用例标题      : Client Id转换失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_AccessUICCFileReq_case1(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ACCESSFILE_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_ACCESSFILE_STRU));

	// 调用被测函数
	ulRet = SI_PIH_AccessUICCFileReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_002
测试用例标题      : 鉴权参数为空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_AccessUICCFileReq_case2(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ACCESSFILE_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_ACCESSFILE_STRU));

	// 调用被测函数
	ulRet = SI_PIH_AccessUICCFileReq(ClientId, OpId, VOS_NULL_PTR);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_AccessUICCFileReq_case3(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ACCESSFILE_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_ACCESSFILE_STRU));

	// 调用被测函数
	ulRet = SI_PIH_AccessUICCFileReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_AccessUICCFileReq_case4(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ACCESSFILE_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_ACCESSFILE_STRU));

	// 调用被测函数
	ulRet = SI_PIH_AccessUICCFileReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_SUCCESS != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
unsigned int uttest_SI_PIH_AccessUICCFileReq_case5(void)
{
#if (FEATURE_ON == FEATURE_IMS)

	// 变量声明
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    SI_PIH_ACCESSFILE_STRU				stData;
	VOS_UINT32                          ulRet;

	ClientId							=	1;
	OpId								=	1;

	memset(&stData, 0, sizeof(SI_PIH_ACCESSFILE_STRU));

	// 调用被测函数
	ulRet = SI_PIH_AccessUICCFileReq(ClientId, OpId, &stData);

	// 执行检查
    if (TAF_FAILURE != ulRet)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

