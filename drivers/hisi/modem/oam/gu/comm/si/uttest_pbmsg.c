#include "siapppb.h"
#include "si_pb.h"

extern void *malloc(int size);
extern void free(void *where);
extern VOS_UINT32 SI_PBUpdateAGlobal(PBMsgBlock *pMsg);
extern VOS_UINT32 SI_PBUpdateACurPB(PBMsgBlock *pMsg);
extern VOS_UINT32 SI_PB_SReadEMLProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord);
extern VOS_UINT32 SI_PB_SReadANRProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord);

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
void uttest_SI_PB_PidMsgProc_case1(void)
{
    PBMsgBlock *pstPBMsg;

    pstPBMsg = (PBMsgBlock *)malloc(100);

    pstPBMsg->ulMsgName = SI_PB_READ_REQ;

    SI_PB_PidMsgProc((struct MsgCB*)pstPBMsg);

    free(pstPBMsg);
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
void uttest_SI_PB_PidMsgProc_case2(void)
{
    PBMsgBlock *pstPBMsg;

    pstPBMsg = (PBMsgBlock *)malloc(100);

    pstPBMsg->ulMsgName = SI_PB_SET_REQ;

    SI_PB_PidMsgProc((struct MsgCB*)pstPBMsg);

    free(pstPBMsg);
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
unsigned int uttest_SI_PBUpdateAGlobal_case1(void)
{
    SI_PB_UPDATEGLOBAL_IND_STRU stMsg;

    stMsg.stPBInitState.enPBInitStep = 1;

    gstPBInitState.enPBInitStep = 0;

    SI_PBUpdateAGlobal((PBMsgBlock *)&stMsg);

    if (1 == gstPBInitState.enPBInitStep)
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
unsigned int uttest_SI_PBUpdateACurPB_case1(void)
{
    SI_PB_SETPB_IND_STRU stMsg;

    stMsg.enPBCurType = 1;

    gstPBCtrlInfo.enPBCurType = 5;

    SI_PBUpdateACurPB((PBMsgBlock *)&stMsg);

    if (1 == gstPBCtrlInfo.enPBCurType)
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
unsigned int uttest_SI_PB_SReadEMLProc_case1(void)
{
	SI_PB_RECORD_STRU stRecord;

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE1;

	gstEMLContent.usTotalNum = 20;

    return SI_PB_SReadEMLProc(10,20,&stRecord);
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
unsigned int uttest_SI_PB_SReadEMLProc_case2(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE1;

	gstEMLContent.pContent = aucData;

	gstEMLContent.usTotalNum = 20;

    return SI_PB_SReadEMLProc(10,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadEMLProc_case3(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

    gstPBCtrlInfo.ulEMLFileNum = 1;

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = 0;

	gstEMLContent.pContent = aucData;

	gstEMLContent.usTotalNum = 20;

    if (TAF_ERR_PB_STORAGE_OP_FAIL == SI_PB_SReadEMLProc(10,0,&stRecord))
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
unsigned int uttest_SI_PB_SReadEMLProc_case4(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = aucData;

	gstEMLContent.pContent = aucData;

	gstEMLContent.usTotalNum = 20;

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum = 10;

    return SI_PB_SReadEMLProc(1,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadEMLProc_case5(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = aucData;

	gstEMLContent.pContent = aucData;

	gstEMLContent.usTotalNum = 20;

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum = 10;

	return SI_PB_SReadEMLProc(1,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadEMLProc_case6(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	memset(aucData, 0xA5, sizeof(aucData));

	gstPBCtrlInfo.astEMLInfo[0].enEMLType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = aucData;

	gstEMLContent.pContent = aucData;

	gstEMLContent.usTotalNum = 20;

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum = 10;

    return SI_PB_SReadEMLProc(1,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadANRProc_case1(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};
	VOS_UINT8			aucEmaIndex = 1;

	gstPBCtrlInfo.ulANRStorageNum = 1;

	gastANRContent[0].pContent = 0;

	memset(aucData, 0xA5, sizeof(aucData));

    if (TAF_ERR_PB_STORAGE_OP_FAIL == SI_PB_SReadANRProc(1,0,&stRecord))
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
unsigned int uttest_SI_PB_SReadANRProc_case2(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};


	gstPBCtrlInfo.ulANRStorageNum = 1;

	gastANRContent[0].pContent = aucData;

	gstPBCtrlInfo.astANRInfo[0][0].enANRType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = 0;

	memset(aucData, 0xA5, sizeof(aucData));

    if (TAF_ERR_PB_STORAGE_OP_FAIL, SI_PB_SReadANRProc(1,0,&stRecord))
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
unsigned int uttest_SI_PB_SReadANRProc_case3(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.ulANRStorageNum = 1;

	gastANRContent[0].pContent = aucData;

	gstPBCtrlInfo.astANRInfo[0][0].enANRType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = aucData;

	memset(aucData, 0xA5, sizeof(aucData));

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astANRInfo[0][0].ulANRTagNum = 1;

    return SI_PB_SReadANRProc(1,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadANRProc_case4(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.ulANRStorageNum = 1;
	gastANRContent[0].pContent = aucData;

	gstPBCtrlInfo.astANRInfo[0][0].enANRType = PB_FILE_TYPE2;

	gstIAPContent.pIAPContent = aucData;

	memset(aucData, 0xA5, sizeof(aucData));

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astANRInfo[0][0].ulANRTagNum = 1;

	return SI_PB_SReadANRProc(1,0,&stRecord);
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
unsigned int uttest_SI_PB_SReadANRProc_case5(void)
{
	SI_PB_RECORD_STRU	stRecord;
	VOS_UINT8			aucData[1024] = {0};

	gstPBCtrlInfo.ulANRStorageNum = 1;

	gastANRContent[0].pContent = aucData;

	gstPBCtrlInfo.astANRInfo[0][0].enANRType = PB_FILE_TYPE1;

	gstIAPContent.pIAPContent = aucData;

	memset(aucData, 0xA5, sizeof(aucData));

	gstIAPContent.ucRecordLen = 5;

	gstPBCtrlInfo.astANRInfo[0][0].ulANRTagNum = 1;

    return SI_PB_SReadANRProc(1,0,&stRecord);
}

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_001
测试用例标题      : VOS_IP_LOAD_CONFIG阶段初始化全局变量
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
unsigned int uttest_Test_WuepsPBPidInit_case1(void)
{
    // 变量声明
	enum VOS_INIT_PHASE_DEFINE			InitPhrase;
	VOS_UINT32							ulRslt;

    //参数初始化
	InitPhrase	=	VOS_IP_LOAD_CONFIG;

    // 初始化全局变量;


    // MOCKER操作;

    // 调用被测函数
    return WuepsPBPidInit(InitPhrase);
}

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_002
测试用例标题      : VOS_IP_BUTT阶段给PB注册USIM事件
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
unsigned int uttest_Test_WuepsPBPidInit_case2(void)
{
    // 变量声明
	enum VOS_INIT_PHASE_DEFINE			InitPhrase;
	VOS_UINT32							ulRslt;

    //参数初始化
	InitPhrase	=	VOS_IP_RESTART;

    // 初始化全局变量;

    // 调用被测函数
    return WuepsPBPidInit(InitPhrase);
}

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_003
测试用例标题      : Default分支
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
unsigned int uttest_Test_WuepsPBPidInit_case3(void)
{
    // 变量声明
	enum VOS_INIT_PHASE_DEFINE			InitPhrase;
	VOS_UINT32							ulRslt;

    //参数初始化
	InitPhrase	=	VOS_IP_STANDBY;

    // 初始化全局变量;

    // 调用被测函数
    return WuepsPBPidInit(InitPhrase);
}

