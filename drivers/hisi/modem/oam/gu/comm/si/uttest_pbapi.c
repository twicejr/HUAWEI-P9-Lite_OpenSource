
#include "TafTypeDef.h"
#include "siapppb.h"


/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_SI_PB_Read_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

	if (TAF_FAILURE != SI_PB_Read(0,0,0,1,10))
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
VOS_UINT32 uttest_SI_PB_SRead_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (TAF_FAILURE != SI_PB_SRead(0,0,0,1,10))
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
VOS_UINT32 uttest_SI_PB_Query_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (TAF_FAILURE != SI_PB_Query(0,0))
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
VOS_UINT32 uttest_SI_PB_Set_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (TAF_FAILURE != SI_PB_Set(0,0,0))
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
VOS_UINT32 uttest_SI_PB_Add_ReturnFail(VOS_VOID)
{
	SI_PB_RECORD_STRU       Record = {0};

    if (TAF_SUCCESS == SI_PB_Add(0,0,0, &Record))
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
VOS_UINT32 uttest_SI_PB_SAdd_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_PB_RECORD_STRU       Record = {0};

	if (TAF_FAILURE != SI_PB_SAdd(0,0,0, &Record))
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
VOS_UINT32 uttest_SI_PB_Modify_ReturnFail(VOS_VOID)
{
	SI_PB_RECORD_STRU       Record = {0};

	if (TAF_SUCCESS == SI_PB_Modify(0,0,0, &Record))
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
VOS_UINT32 uttest_SI_PB_SModify_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_PB_RECORD_STRU       Record = {0};

	if (TAF_FAILURE != SI_PB_SModify(0,0,0, &Record))
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
VOS_UINT32 uttest_SI_PB_Delete_ReturnFail(VOS_VOID)
{
	SI_PB_RECORD_STRU       Record = {0};

	if (TAF_SUCCESS == SI_PB_Delete(0,0,0,1))
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
VOS_UINT32 uttest_SI_PB_Search_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8       aucData[100] = {0};

	if (TAF_FAILURE != SI_PB_Search(0,0,0,sizeof(aucData), aucData))
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
VOS_UINT32 uttest_SI_PB_GetStorateType_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8       aucData[100] = {0};

	if (SI_PB_STORAGE_UNSPECIFIED != SI_PB_GetStorateType())
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
VOS_UINT32 uttest_SI_PB_GetSPBFlag_ReturnFail(VOS_VOID)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8       aucData[100] = {0};

	if (VOS_FALSE != SI_PB_GetSPBFlag())
	{
	    return VOS_ERR;
	}
#endif

	return VOS_OK;

}


