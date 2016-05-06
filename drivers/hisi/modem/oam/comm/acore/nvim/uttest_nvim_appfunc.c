
#include "nvim_internalfunc.h"

unsigned char g_aucVhwMemDDR[10240] = {0};

extern unsigned long g_ulNVMemAddr;

/*******************************************************************
*测试项:             获得地址信息失败
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_Init_case1(void)
{
    if (NV_INIT_FAIL != NV_Init())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_Init_case2(void)
{
    memset(g_aucVhwMemDDR, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);

    if (VOS_ERR != NV_Init())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_Init_case3(void)
{
    memset(g_aucVhwMemDDR, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);

    if (NV_INIT_FAIL != NV_Init())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_GetLength_case1(void)
{
	VOS_UINT16 usID = 10;
	VOS_UINT32 *pulLength = VOS_NULL_PTR;

    if (NV_BUFFER_NOT_EXIST != NV_GetLength(usID, pulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_GetLength_case2(void)
{
	VOS_UINT16 usID = 10;
	VOS_UINT32 ulLength;

    if (NV_ID_NOT_EXIST != NV_GetLength(usID, &ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

NV_FILE_LIST_INFO_STRU      g_stFileListInfo;
NV_REFERENCE_DATA_INFO_STRU g_stNvIdInfo;

VOS_UINT32 uttest_NV_Ctrl_File_Search_InMemory_stub1(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo)
{
    g_stNvIdInfo.usNvLength = 10;
    memcpy(pstNvIdInfo, &g_stNvIdInfo, sizeof(g_stNvIdInfo));

    return VOS_OK;
}


/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_GetLength_case3(void)
{
	VOS_UINT16 usID = 10;
	VOS_UINT32 ulLength;

    if (NV_OK != NV_GetLength(usID, &ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NVIM_MemCpy_case1(void)
{
	VOS_UINT8 aucDst[100] = {0};
	VOS_UINT8 aucSrc[10];

	memset(aucSrc, 0xA5, sizeof(aucSrc));

	NVIM_MemCpy(aucDst, aucSrc, sizeof(aucSrc));

	if (0 != memcmp(aucDst, aucSrc, sizeof(aucSrc)))
	{
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemDump_case1(void)
{
	NV_MemDump(100, 100, 10,0,0);
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemDump_case2(void)
{
	NV_MemDump(100, 100, 10,0,0);
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemCpy_case1(void)
{
	VOS_UINT8 aucDst[100];

    VOS_UINT32 pucData;

	pucData = NV_MAGICNUM_ADDR;

	NV_MemCpy(aucDst, (const VOS_VOID *)(pucData - 100), 10,0,0);
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemCpy_case2(void)
{
	VOS_UINT8 aucDst[100];
	VOS_UINT32 pucData;

	pucData = NV_MAGICNUM_ADDR;

	NV_MemCpy(aucDst, (const VOS_VOID *)(pucData+NV_BUFFER_SIZE+1), 10,0,0);
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemCpy_case3(void)
{
	VOS_UINT8 aucDst[100];
	VOS_UINT32 pucData;

	pucData = NV_MAGICNUM_ADDR;

	NV_MemCpy(aucDst, (const VOS_VOID *)(pucData+NV_BUFFER_SIZE), 10,0,0);
}

/*******************************************************************
*测试项:             正常转换
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
void uttest_NV_MemCpy_case4(void)
{
	VOS_UINT8 aucDst[100];
	VOS_UINT32 pucData;

	pucData = NV_MAGICNUM_ADDR;

	NV_MemCpy(aucDst, (const VOS_VOID *)(pucData), 10,0,0);
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case1(void)
{
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_UINT8  aucItem[10];
	VOS_UINT32 ulLength = 10;

    if (NV_MODEM_ID_ERR != NV_ReadPartEx(4, usID,ulOffset,aucItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case2(void)
{
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem = VOS_NULL_PTR;
	VOS_UINT32 ulLength = 10;

    if (NV_BUFFER_NOT_EXIST != NV_ReadPartEx(0, usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case3(void)
{
	char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 0;

	pItem = aucTemp;

    if (NV_BUFFER_NOT_EXIST != NV_ReadPartEx(0, usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case4(void)
{
	char aucTemp[20];
	VOS_UINT16 usID = 5;
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;
	g_astNvFileHandle[0].ulSize = 100;

    if (NV_ID_NOT_EXIST != NV_ReadPartEx(0,usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 uttest_NV_Ctrl_File_Search_InMemory_stub2(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo)
{
    g_stNvIdInfo.usNvLength = 20;

    memcpy(pstFileListInfo, &g_stFileListInfo, sizeof(g_stFileListInfo));
    memcpy(pstNvIdInfo, &g_stNvIdInfo, sizeof(g_stNvIdInfo));

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case5(void)
{
    char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 21;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;
    if (NV_PART_DATA_ERR != NV_ReadPartEx(0, usID, ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case6(void)
{
    char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 16;

    pItem = aucTemp;

    if (NV_PART_DATA_ERR != NV_ReadPartEx(0,usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 uttest_NV_Ctrl_File_Search_InMemory_stub3(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo)
{
	g_stNvIdInfo.ulNvOffset = 5;
	g_stNvIdInfo.usFileId = 5;
	g_stNvIdInfo.ucModemNum = 1;
    g_stNvIdInfo.usNvLength = 20;

    memcpy(pstFileListInfo, &g_stFileListInfo, sizeof(g_stFileListInfo));
    memcpy(pstNvIdInfo, &g_stNvIdInfo, sizeof(g_stNvIdInfo));

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case7(void)
{
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;
	char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;

	stNvIdInfo.usFileId = 5;

	g_astNvFileHandle[stNvIdInfo.usFileId].ulOffset = 10;

    if (NV_OK != NV_ReadPartEx(0, usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 uttest_NV_Ctrl_File_Search_InMemory_stub4(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo)
{
	g_stNvIdInfo.ulNvOffset = 5;
	g_stNvIdInfo.usFileId = 5;
	g_stNvIdInfo.ucModemNum = 0;
    g_stNvIdInfo.usNvLength = 20;

    memcpy(pstFileListInfo, &g_stFileListInfo, sizeof(g_stFileListInfo));
    memcpy(pstNvIdInfo, &g_stNvIdInfo, sizeof(g_stNvIdInfo));

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadPartEx_case8(void)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;
	char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;

	stNvIdInfo.usFileId = 5;

	g_astNvFileHandle[stNvIdInfo.usFileId-1].ulOffset = 10;

    if (NV_OK != NV_ReadPartEx(1, usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_Printf_case1(void)
{
    if (VOS_ERR != NV_Printf("test"))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case1(void)
{
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_UINT8  aucItem[10];
	VOS_UINT32 ulLength = 10;

    if (NV_MODEM_ID_ERR != NV_ReadEx(4, usID,aucItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case2(void)
{
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem = VOS_NULL_PTR;
	VOS_UINT32 ulLength = 10;

    if (NV_BUFFER_NOT_EXIST != NV_ReadPartEx(0, usID,ulOffset,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case3(void)
{
	char aucTemp[20];

	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem = aucTemp;
	VOS_UINT32 ulLength = 0;

    if (NV_BUFFER_NOT_EXIST != NV_ReadEx(0, usID,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case4(void)
{
	char aucTemp[20];
	VOS_UINT16 usID = 5;
	VOS_UINT32 ulOffset = 1;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;

    if (NV_ID_NOT_EXIST != NV_ReadEx(0,usID,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case5(void)
{
	char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 21;

    pItem = aucTemp;

    if (NV_PART_DATA_ERR != NV_ReadEx(0,usID,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case6(void)
{
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;
	char aucTemp[20];
	VOS_UINT16 usID = 5;			//SN对应 NV_ID项 = 5;length = 20 byte.
	VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
	VOS_UINT32 ulLength = 10;

    pItem = aucTemp;

	stNvIdInfo.usFileId = 5;

	g_astNvFileHandle[stNvIdInfo.usFileId-1].ulOffset = 10;

    if (NV_OK != NV_ReadEx(0, usID,pItem,ulLength))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_NV_ReadEx_case7(void)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;
    char aucTemp[20];
    VOS_UINT16 usID = 5;            //SN对应 NV_ID项 = 5;length = 20 byte.
    VOS_UINT32 ulOffset = 5;
    VOS_VOID *pItem;
    VOS_UINT32 ulLength = 10;

	pItem = aucTemp;

	stNvIdInfo.usFileId = 5;

	g_astNvFileHandle[stNvIdInfo.usFileId-1].ulOffset = 10;

    if (NV_OK != NV_ReadEx(1, usID,pItem,ulLength))
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

