
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMI_STRPARSE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "Taf_MmiStrParse.h"
#include  "TafAppSsa.h"
#include  "MnErrorCode.h"
/* A核和C核编解码都要用到 */
#include  "MnMsgTs.h"
#include "TafStdlib.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


#define MN_MMI_SC_MAX_ENTRY (sizeof(f_stMmiScInfo)/sizeof(MN_MMI_SC_TABLE_STRU))

#define MN_MMI_BS_MAX_ENTRY (sizeof(f_stMmiBSInfo)/sizeof(MN_MMI_BS_TABLE_STRU))

/* 通用补充业务操作码映射表: 第一列补充业务操作码对应的MMI字符串，第二列补充业务操作码 */
MN_MMI_SS_OP_Tbl_STRU                   g_astTafMmiOporationTypeTbl[] = {
                                                    {"**", TAF_MMI_REGISTER_SS,    {0, 0, 0, 0, 0, 0, 0}},
                                                    {"*",  TAF_MMI_ACTIVATE_SS,    {0, 0, 0, 0, 0, 0, 0}},
                                                    {"#",  TAF_MMI_DEACTIVATE_SS,  {0, 0, 0, 0, 0, 0, 0}},
                                                    {"*#", TAF_MMI_INTERROGATE_SS, {0, 0, 0, 0, 0, 0, 0}},
                                                    {"##", TAF_MMI_ERASE_SS,       {0, 0, 0, 0, 0, 0, 0}},
                                                  };

/*****************************************************************************
  4 类型定义
*****************************************************************************/



/*****************************************************************************
  5 变量定义
*****************************************************************************/
MN_MMI_SC_TABLE_STRU     f_stMmiScInfo[] =

{
    {"",         TAF_ALL_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"30",       TAF_CLIP_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"31",       TAF_CLIR_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"76",       TAF_COLP_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"77",       TAF_COLR_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"21",       TAF_CFU_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"67",       TAF_CFB_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"61",       TAF_CFNRY_SS_CODE,                     {0, 0, 0, 0, 0, 0, 0}},
    {"62",       TAF_CFNRC_SS_CODE,                     {0, 0, 0, 0, 0, 0, 0}},
    {"002",      TAF_ALL_FORWARDING_SS_CODE,            {0, 0, 0, 0, 0, 0, 0}},
    {"004",      TAF_ALL_COND_FORWARDING_SS_CODE,       {0, 0, 0, 0, 0, 0, 0}},
    {"43",       TAF_CW_SS_CODE,                        {0, 0, 0, 0, 0, 0, 0}},
    {"37",       TAF_CCBS_A_SS_CODE,                    {0, 0, 0, 0, 0, 0, 0}},
    {"33",       TAF_BAOC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"331",      TAF_BOIC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"332",      TAF_BOICEXHC_SS_CODE,                  {0, 0, 0, 0, 0, 0, 0}},
    {"35",       TAF_BAIC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"351",      TAF_BICROAM_SS_CODE,                   {0, 0, 0, 0, 0, 0, 0}},
    {"330",      TAF_ALL_BARRING_SS_CODE,               {0, 0, 0, 0, 0, 0, 0}},
    {"333",      TAF_BARRING_OF_OUTGOING_CALLS_SS_CODE, {0, 0, 0, 0, 0, 0, 0}},
    {"353",      TAF_BARRING_OF_INCOMING_CALLS_SS_CODE, {0, 0, 0, 0, 0, 0, 0}}
};



MN_MMI_BS_TABLE_STRU  f_stMmiBSInfo[] =
{
 {"10",     TAF_ALL_TELESERVICES_TSCODE,                    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"11",     TAF_ALL_SPEECH_TRANSMISSION_SERVICES_TSCODE,    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"12",     TAF_ALL_DATA_TELESERVICES_TSCODE,               TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"13",     TAF_ALL_FACSIMILE_TRANSMISSION_SERVICES_TSCODE, TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"16",     TAF_ALL_SMS_SERVICES_TSCODE,                    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"19",     TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE,           TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"20",     TAF_ALL_BEARERSERVICES_BSCODE,                  TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"21",     TAF_ALL_ASYNCHRONOUS_SERVICES_BSCODE,           TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"22",     TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE,            TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"24",     TAF_ALL_DATA_CIRCUIT_SYNCHRONOUS_BSCODE,        TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"25",     TAF_ALL_DATA_CIRCUIT_ASYNCHRONOUS_BSCODE,       TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"50",     TAF_ALL_PLMN_SPECIFICTS_TSCODE,                 TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"51",     TAF_PLMN_SPECIFICTS_1_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"52",     TAF_PLMN_SPECIFICTS_2_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"53",     TAF_PLMN_SPECIFICTS_3_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"54",     TAF_PLMN_SPECIFICTS_4_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"55",     TAF_PLMN_SPECIFICTS_5_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"56",     TAF_PLMN_SPECIFICTS_6_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"57",     TAF_PLMN_SPECIFICTS_7_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"58",     TAF_PLMN_SPECIFICTS_8_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"59",     TAF_PLMN_SPECIFICTS_9_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"60",     TAF_PLMN_SPECIFICTS_A_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"61",     TAF_PLMN_SPECIFICTS_B_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"62",     TAF_PLMN_SPECIFICTS_C_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"63",     TAF_PLMN_SPECIFICTS_D_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"64",     TAF_PLMN_SPECIFICTS_E_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"65",     TAF_PLMN_SPECIFICTS_F_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"70",     TAF_ALL_PLMN_SPECIFICBS_BSCODE,                 TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"71",     TAF_PLMN_SPECIFICBS_1_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"72",     TAF_PLMN_SPECIFICBS_2_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"73",     TAF_PLMN_SPECIFICBS_3_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"74",     TAF_PLMN_SPECIFICBS_4_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"75",     TAF_PLMN_SPECIFICBS_5_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"76",     TAF_PLMN_SPECIFICBS_6_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"77",     TAF_PLMN_SPECIFICBS_7_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"78",     TAF_PLMN_SPECIFICBS_8_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"79",     TAF_PLMN_SPECIFICBS_9_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"80",     TAF_PLMN_SPECIFICBS_A_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"81",     TAF_PLMN_SPECIFICBS_B_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"82",     TAF_PLMN_SPECIFICBS_C_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"83",     TAF_PLMN_SPECIFICBS_D_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"84",     TAF_PLMN_SPECIFICBS_E_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"85",     TAF_PLMN_SPECIFICBS_F_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}}
};

MN_CALL_CLIR_CFG_ENUM_U8  f_enClirOperate = MN_CALL_CLIR_AS_SUBS;

/*lint -save -e958 */

/*****************************************************************************
  6 函数实现
*****************************************************************************/
/**********************************************************
 函 数 名  : MMI_GetOporationTypeTblSize
 功能描述  : 获取补充业务操作码映射表的容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 补充业务操作码映射表的容量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
*************************************************************/

VOS_UINT32 MMI_GetOporationTypeTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiOporationTypeTbl) / sizeof(g_astTafMmiOporationTypeTbl[0]);

    return ulTblSize;
}

/**********************************************************
 函 数 名  : MMI_GetOporationTypeTblAddr
 功能描述  : 获取通用补充业务操作码映射表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 通用补充业务操作码映射表的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
*************************************************************/
MN_MMI_SS_OP_Tbl_STRU *MMI_GetOporationTypeTblAddr(VOS_VOID)
{
    return g_astTafMmiOporationTypeTbl;
}

/*****************************************************************************
 函 数 名  : MMI_GetBSTblSize
 功能描述  : 获取BS表容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BS表容量

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_GetBSTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(f_stMmiBSInfo) / sizeof(f_stMmiBSInfo[0]);

    return ulTblSize;
}

/*****************************************************************************
 函 数 名  : MMI_GetBSTblAddr
 功能描述  : 获取BS表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BS表地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
MN_MMI_BS_TABLE_STRU *MMI_GetBSTblAddr(VOS_VOID)
{
    return f_stMmiBSInfo;
}

/*****************************************************************************
 函 数 名  : MMI_GetSCTblSize
 功能描述  : 获取SC表容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC表容量

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_GetSCTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(f_stMmiScInfo) / sizeof(f_stMmiScInfo[0]);

    return ulTblSize;
}

/*****************************************************************************
 函 数 名  : MMI_GetSCTblSize
 功能描述  : 获取SC表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC表地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
MN_MMI_SC_TABLE_STRU *MMI_GetSCTblAddr(VOS_VOID)
{
    return f_stMmiScInfo;
}

/*****************************************************************************
 函 数 名  : MMI_AtoI
 功能描述  : 将数字字符串转换成对应的整数
 输入参数  : pcSrc - 待转换的数字字符窜
 输出参数  : 无
 返 回 值  : 转换后的整数

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MMI_AtoI(
    const VOS_CHAR                      *pcSrc
)
{
    VOS_UINT32      i = 0;
    /*lint -e731*/
    while (MN_MMI_isdigit(*pcSrc))
    /*lint +e731*/
    {
        /*lint -e961*/
        i = (i * 10) + (*(pcSrc++) - '0');
        /*lint +e961*/
    }
    return i;
}



/*****************************************************************************
 函 数 名  : MMI_StrChr
 功能描述  : 在一定范围内的字符串中查找指定的字符
 输入参数  : pcFrom - 字符串的起始位置
             pcTo   - 字符串的终止位置
             char   - 待查找的字符
 输出参数  : 无
 返 回 值  : 返回所找到的字符串中的字符的地址，未查找到，则返回空指针

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_CHAR* MMI_StrChr(
    const VOS_CHAR                      *pcFrom,
    const VOS_CHAR                      *pcTo,
    VOS_INT                              ichar
)
{
    if (VOS_NULL_PTR == pcFrom)
    {
        return VOS_NULL_PTR;
    }

    for(; (*pcFrom != (VOS_CHAR) ichar) && MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo); ++pcFrom)
    {
        if ('\0' == *pcFrom )
        {
            return VOS_NULL_PTR;
        }
    }

    if ((VOS_NULL_PTR != pcTo) && (pcFrom > pcTo))
    {
        return VOS_NULL_PTR;
    }

    return (VOS_CHAR*)pcFrom;
}



/*****************************************************************************
 函 数 名  : MMI_Max
 功能描述  : 取得两个无符号整型数据中的较大值
 输入参数  : ulNumbera
             ulNumberb
 输出参数  : 无
 返 回 值  : 返回两个无符号整型数据中的较大值

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MMI_Max(const VOS_UINT32 ulNumbera, const VOS_UINT32 ulNumberb)
{
    return ((ulNumbera > ulNumberb) ? ulNumbera : ulNumberb);
}

/*****************************************************************************
 函 数 名  : MMI_DecodeScAndSi
 功能描述  : 对MMI字符串中的Sc和Si进行解析，输出解析后的内容
 输入参数  : pInMmiStr   - 待解析的MMI字符串
             pMmiOpParam - 指示对应的操作
 输出参数  : pstScSiPara - 解析后的Sc和Si的数据类型
             ppOutMmiStr - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE    - 解析成功
             VOS_FALSE   - 解析失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MMI_DecodeScAndSi(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutMmiStr
)
{
    VOS_CHAR                            aucTmpVal[MN_MMI_MAX_PARA_NUM][MN_MMI_MAX_BUF_SIZE];
    VOS_UINT16                          i = 0;
    VOS_UINT16                          j = 0;
    VOS_CHAR                            *pcNextStart;
    VOS_CHAR                            *pcEnd;
    VOS_CHAR                            *pcNextStop;
    VOS_BOOL                            bEndReached = VOS_FALSE;
    VOS_UINT16                          usOffset = 0;
    VOS_UINT32                          ulTmpMmiNum;

    ulTmpMmiNum  = 0;

    PS_MEM_SET(pstScSiPara, '\0', sizeof(MN_MMI_SC_SI_PARA_STRU));

    PS_MEM_SET(aucTmpVal, '\0', sizeof(aucTmpVal));


    if (TAF_MMI_REGISTER_PASSWD != pMmiOpParam->MmiOperationType)
    {
        /*跳过开始的几个字符*/
        for (i =0; (!MN_MMI_isdigit(pInMmiStr[i])) && (i < 2); i++)
        {
            usOffset++;
        }
    }

    pcNextStart = &pInMmiStr[i];

    if (VOS_NULL_PTR ==
           (pcEnd = MMI_StrChr(pcNextStart, VOS_NULL_PTR, MN_MMI_STOP_CHAR)))
    {
        return VOS_FALSE;
    }
    else
    {
        pcNextStop = MMI_StrChr(pcNextStart, pcEnd, MN_MMI_START_SI_CHAR);

        j = 0;
        while ((j < MN_MMI_MAX_PARA_NUM) && (VOS_FALSE == bEndReached))
        {
            if (VOS_NULL_PTR != pcNextStop)
            {
                ulTmpMmiNum = (VOS_UINT32)(pcNextStop - pcNextStart);
                if (ulTmpMmiNum > MN_MMI_MAX_BUF_SIZE)
                {
                    ulTmpMmiNum = MN_MMI_MAX_BUF_SIZE;
                }
                PS_MEM_CPY(&aucTmpVal[j][0],
                           pcNextStart,
                           ulTmpMmiNum);
                usOffset += (VOS_UINT16)((pcNextStop - pcNextStart) + 1);
                pcNextStart = pcNextStop + 1;
                pcNextStop = MMI_StrChr(pcNextStart, pcEnd, MN_MMI_START_SI_CHAR);
                j++;
            }
            else
            {
                ulTmpMmiNum = (VOS_UINT32)(pcEnd - pcNextStart);
                if (ulTmpMmiNum > MN_MMI_MAX_BUF_SIZE)
                {
                    ulTmpMmiNum = MN_MMI_MAX_BUF_SIZE;
                }
                PS_MEM_CPY(&aucTmpVal[j][0],
                           pcNextStart,
                           ulTmpMmiNum);
                usOffset += (VOS_UINT16)((pcEnd - pcNextStart) + 1);
                bEndReached = VOS_TRUE;
            }
        }
    }

    PS_MEM_CPY(pstScSiPara->acSsCode, &aucTmpVal[0][0], MN_MMI_MAX_SC_LEN);
    PS_MEM_CPY(pstScSiPara->acSia, &aucTmpVal[1][0], MN_MMI_MAX_SIA_LEN);
    PS_MEM_CPY(pstScSiPara->acSib, &aucTmpVal[2][0], MN_MMI_MAX_SIB_LEN);
    PS_MEM_CPY(pstScSiPara->acSic, &aucTmpVal[3][0], MN_MMI_MAX_SIC_LEN);

    *ppOutMmiStr = pInMmiStr + usOffset;

    return VOS_TRUE;


}


/*****************************************************************************
 函 数 名  : MMI_JudgePinOperation
 功能描述  : 判断字符串对应的操作是不是进行pin码操作，如果是pin码操作，填写对应的参数
 输入参数  : pMmiStr         - 待解析的字符串
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - pin操作相关的参数
             pulErrorNo      - 在解析出是pin码操作的情况下，如果后面的参数有错误，
                               那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
 返 回 值  : VOS_TRUE        - 是pin码操作
             VOS_FALSE       - 不是pin码操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgePinOperation(
    VOS_CHAR                            *pMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiPinStrOpTbl[] = {
                                                              {"**042*", TAF_MMI_CHANGE_PIN2,  {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**04*",  TAF_MMI_CHANGE_PIN,   {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**052*", TAF_MMI_UNBLOCK_PIN2, {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**05*",  TAF_MMI_UNBLOCK_PIN,  {0, 0, 0, 0, 0, 0, 0}},
                                                              {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                             };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stMmiPinStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pMmiStr,
                            stMmiPinStrOpTbl[i].pString,
                            VOS_StrLen(stMmiPinStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiPinStrOpTbl[i].enOperationType;
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stMmiPinStrOpTbl[i].pString)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == MMI_DecodeScAndSi(pMmiStr, pMmiOpParam, &stScSiPara, ppOutRestMmiStr))
    {
        if (0 == VOS_MemCmp(stScSiPara.acSib,
                            stScSiPara.acSic,
                            MMI_Max(VOS_StrLen(stScSiPara.acSib), VOS_StrLen(stScSiPara.acSic))))
        {
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->PinReq.aucOldPin,
                        (VOS_CHAR*)stScSiPara.acSia,
                        VOS_StrLen(stScSiPara.acSia) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->PinReq.aucNewPin,
                        (VOS_CHAR*)stScSiPara.acSib,
                        VOS_StrLen(stScSiPara.acSib) + 1);
            switch(pMmiOpParam->MmiOperationType)
            {
            case TAF_MMI_CHANGE_PIN2:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_CHANGE;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN2;
                break;

            case TAF_MMI_CHANGE_PIN:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_CHANGE;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN;
                break;

            case TAF_MMI_UNBLOCK_PIN2:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_UNBLOCK;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN2;
                break;

            case TAF_MMI_UNBLOCK_PIN:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_UNBLOCK;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN;
                break;

            default:
                /*该分支永远不会走到*/
                break;
            }

            *pulErrCode = MN_ERR_NO_ERROR;
        }
        else
        {
            *pulErrCode = MN_ERR_INVALIDPARM;
        }
    }
    else
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMI_JudgePwdOperation
 功能描述  : 判断字符串对应的操作是不是进行密码操作，如果是密码操作，填写对应的参数
 输入参数  : pMmiStr         - 待解析的字符串
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - 密码操作相关的参数
             pulErrorNo      - 在解析出是密码操作的情况下，如果后面的参数有错误，
                               那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
 返 回 值  : VOS_TRUE        - 是密码操作
             VOS_FALSE       - 不是密码操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgePwdOperation(
    VOS_CHAR                            *pMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiPwdStrOpTbl[] = {
                                                              {"**03*", TAF_MMI_REGISTER_PASSWD, {0, 0, 0, 0, 0, 0, 0}},
                                                              {"*03*",  TAF_MMI_REGISTER_PASSWD, {0, 0, 0, 0, 0, 0, 0}},
                                                              {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                             };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stMmiPwdStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pMmiStr,
                            stMmiPwdStrOpTbl[i].pString,
                            VOS_StrLen(stMmiPwdStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiPwdStrOpTbl[i].enOperationType;
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stMmiPwdStrOpTbl[i].pString)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == MMI_DecodeScAndSi(pMmiStr + VOS_StrLen(stMmiPwdStrOpTbl[i].pString),
                                      pMmiOpParam,
                                      &stScSiPara,
                                      ppOutRestMmiStr))
    {
#if 0
        if (0 == VOS_MemCmp(stScSiPara.acSib,
                            stScSiPara.acSic,
                            MMI_Max(VOS_StrLen(stScSiPara.acSib), VOS_StrLen(stScSiPara.acSic))))
        {
#endif
            if(0 == VOS_StrLen(stScSiPara.acSsCode))  /*for a common password for all appropriate services, delete the ZZ*/
            {
                pMmiOpParam->RegPwdReq.SsCode = TAF_ALL_SS_CODE;
            }
            else
            {
                i = 0;
                while (i < MN_MMI_SC_MAX_ENTRY)
                {
                    if (0 == VOS_MemCmp(f_stMmiScInfo[i].pcMmiSc,
                                        stScSiPara.acSsCode,
                                        MMI_Max(VOS_StrLen(stScSiPara.acSsCode), VOS_StrLen(f_stMmiScInfo[i].pcMmiSc))))
                    {
                        pMmiOpParam->RegPwdReq.SsCode = f_stMmiScInfo[i].ucNetSc;
                        break;
                    }
                    i++;
                }

                if (i >= MN_MMI_SC_MAX_ENTRY)
                {
                    *pulErrCode = MN_ERR_INVALIDPARM;
                    return VOS_TRUE;
                }
            }

            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucOldPwdStr,
                        (VOS_CHAR*)stScSiPara.acSia,
                        VOS_StrLen(stScSiPara.acSia) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucNewPwdStr,
                        (VOS_CHAR*)stScSiPara.acSib,
                        VOS_StrLen(stScSiPara.acSib) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucNewPwdStrCnf,
                        (VOS_CHAR*)stScSiPara.acSic,
                        VOS_StrLen(stScSiPara.acSic) + 1);

            *pulErrCode = MN_ERR_NO_ERROR;
#if 0
        }
        else
        {
            *pulErrCode = MN_ERR_INVALIDPARM;
        }
#endif
    }
    else
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MMI_JudgeTmpModeClirOp
 功能描述  : 判断字符串对应的操作是不是CLIR临时模式下的抑制或调用操作。
 输入参数  : pMmiStr         - 待解析的字符串
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - 密码操作相关的参数
 返 回 值  : VOS_TRUE        - 是线路相关操作
             VOS_FALSE       - 不是线路相关操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgeTmpModeClirOp(
    VOS_CHAR                            *pInMmiStr,
    VOS_CHAR                            **ppOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiLiStrOpTbl[]={
                                                            {"*31#", TAF_MMI_SUPPRESS_CLIR, {0, 0, 0, 0, 0, 0, 0}},
                                                            {"#31#", TAF_MMI_INVOKE_CLIR, {0, 0, 0, 0, 0, 0, 0}},
                                                            {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                          };
    while (VOS_NULL_PTR != stMmiLiStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pInMmiStr,
                            stMmiLiStrOpTbl[i].pString,
                            VOS_StrLen(stMmiLiStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiLiStrOpTbl[i].enOperationType;
            *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(stMmiLiStrOpTbl[i].pString);
            return VOS_TRUE;
        }
        i++;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : MMI_JudgeImeiOperation
 功能描述  : 判断字符串对应的操作是否是显示IMEI
 输入参数  : pMmiStr         - 待解析的字符串
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - 密码操作相关的参数
 返 回 值  : VOS_TRUE        - 是显示IMEI操作
             VOS_FALSE       - 不是显示IMEI操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgeImeiOperation(
    VOS_CHAR                            *pcInMmiStr,
    VOS_CHAR                            **ppcOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
)
{
    VOS_CHAR                            *pcImeiStr = "*#06#";

    if (0 == VOS_MemCmp(pcInMmiStr, pcImeiStr, VOS_StrLen(pcImeiStr)))
    {
        pstMmiOpParam->MmiOperationType = TAF_MMI_DISPLAY_IMEI;
        *ppcOutRestMmiStr = pcInMmiStr + VOS_StrLen(pcImeiStr);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MMI_JudgeUssdOperation
 功能描述  : 判断字符串对应的操作是否是USSD操作
 输入参数  : pMmiStr         - 待解析的字符串
 输出参数  : 无
 返 回 值  : VOS_TRUE        - 是显示IMEI操作
             VOS_FALSE       - 不是显示IMEI操作
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
 VOS_BOOL MMI_JudgeUssdOperation(
    VOS_CHAR                            *pcMmiStr
)
{
    VOS_UINT32       ulStrLen = VOS_StrLen(pcMmiStr);

    /*判断依据*/
    /*
    3) #-string:
    Input of the form.
    "Entry of any characters defined in the 3GPP TS 23.038 [8] Default Alphabet
    (up to the maximum defined in 3GPP TS 24.080 [10]), followed by #SEND".
    */
    if ((ulStrLen >= MN_MMI_MIN_USSD_LEN)
      &&(MN_MMI_STOP_CHAR == pcMmiStr[ulStrLen - 1]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MMI_TransMmiSsCodeToNetSsCode
 功能描述  : 将Mmi字串中的Ss Code转换成网络定义的Ss Code
 输入参数  : pstScSiPara  - MMI定义的Sc和Si的定义
 输出参数  : pucNetSsCode - 转换后的网络定义的Ss Code
 返 回 值  : VOS_OK       - 转换成功
             VOS_ERR    - 转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_TransMmiSsCodeToNetSsCode(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_UINT8                           *pucNetSsCode
)
{
    VOS_UINT8       i = 0;

    /*转换SS Code*/
    while(i < MN_MMI_SC_MAX_ENTRY)
    {
        if (0 == VOS_MemCmp(f_stMmiScInfo[i].pcMmiSc,
                            pstScSiPara->acSsCode,
                            MMI_Max(VOS_StrLen(f_stMmiScInfo[i].pcMmiSc), VOS_StrLen(pstScSiPara->acSsCode))))
        {
            *pucNetSsCode = f_stMmiScInfo[i].ucNetSc;
            break;
        }
        i++;
    }

    if (i >= MN_MMI_SC_MAX_ENTRY)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MMI_TransMmiBsCodeToNetBsCode
 功能描述  : 将Mmi字串中的Bs Code转换成网络定义的Bs Code
 输入参数  : pstScSiPara  - MMI定义的Sc和Si的定义
             ucNetSsCode  - 网络定义的Ss Code
 输出参数  : pucNetBsCode - 转换后的网络定义的Bs Code
             pucNetBsType - 转换后的网络定义的Bs Type
 返 回 值  : VOS_OK       - 转换成功
             VOS_ERR    - 转换失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MMI_TransMmiBsCodeToNetBsCode(
    VOS_UINT8                           ucNetSsCode,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_UINT8                           *pucNetBsCode,
    VOS_UINT8                           *pucNetBsType

)
{
    VOS_CHAR                            acBs[MN_MMI_MAX_SIA_LEN + 1];
    VOS_UINT16                          i;

    /*是不是需要设定那些需要调用此函数的限定?*/

    /*这一段是转换对应的BS code*/
    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0)))
    {
        PS_MEM_CPY(acBs, pstScSiPara->acSib, VOS_StrLen(pstScSiPara->acSib) + 1);
    }
    else if (TAF_CW_SS_CODE == ucNetSsCode)
    {
        PS_MEM_CPY(acBs, pstScSiPara->acSia, VOS_StrLen(pstScSiPara->acSia) + 1);
    }
    else
    {
        acBs[0] = '\0';
    }


    i = 0;
    while(i < MN_MMI_BS_MAX_ENTRY)
    {
        if (0 == VOS_MemCmp(f_stMmiBSInfo[i].pcMmiBs,
                            acBs,
                            MMI_Max(VOS_StrLen(f_stMmiBSInfo[i].pcMmiBs), VOS_StrLen(acBs))))
        {
            *pucNetBsCode = f_stMmiBSInfo[i].ucNetBsCode;
            *pucNetBsType = f_stMmiBSInfo[i].ucNetBsType;
            break;
        }
        i++;
    }

    if (MN_MMI_BS_MAX_ENTRY == i)
    {
        return VOS_ERR;
    }

    return VOS_OK;

    /* BS Code 的转换完成 */
}

/*****************************************************************************
 函 数 名  : MMI_FillInRegisterSSPara
 功能描述  : 填写RegisterSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - RegisterSS操作类型相应的参数
             pucErrCode    - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2008年09月02日
    作    者   : h44270
    修改内容   : AT2D05318
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS密码下移到SS模块
*****************************************************************************/
VOS_UINT32 MMI_FillInRegisterSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_REGISTERSS_REQ_STRU          *pstRegisterSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;

    pstRegisterSsReq = &pMmiOpParam->RegisterSsReq;

    PS_MEM_SET(pstRegisterSsReq, 0, sizeof(TAF_SS_REGISTERSS_REQ_STRU));

    pstRegisterSsReq->SsCode = ucNetSsCode;

    if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
    {
        pstRegisterSsReq->OP_FwdToNum = 1;
        pstRegisterSsReq->OP_NumType = 1;
        /*如果是带'+'号，认为是国际号码，号码类型的值为0x91*/
        if ('+' == pstScSiPara->acSia[0])
        {
            /*去除头部的'+'号*/
            pstRegisterSsReq->NumType = 0x91;
            PS_MEM_CPY(pstRegisterSsReq->aucFwdToNum,
                      pstScSiPara->acSia + 1,
                      VOS_StrLen(pstScSiPara->acSia));

        }
        else
        {
            pstRegisterSsReq->NumType = 0x81;
            PS_MEM_CPY(pstRegisterSsReq->aucFwdToNum,
                      pstScSiPara->acSia,
                      VOS_StrLen(pstScSiPara->acSia) + 1);
        }

        if ('\0' != pstScSiPara->acSic[0])
        {
            pstRegisterSsReq->OP_NoRepCondTime = 1;
            pstRegisterSsReq->NoRepCondTime = (VOS_UINT8)MMI_AtoI(pstScSiPara->acSic);
        }
    }


    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_ALL_BARRING_SS_CODE密码相关操作 */
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }

        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstRegisterSsReq->OP_BsService = 1;
        pstRegisterSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstRegisterSsReq->BsService.BsType = ucNetBsType;
    }



    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_FillInEraseSSPara
 功能描述  : 填写EraseSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - EraseSS操作类型相应的参数
             pucErrCode    - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS密码下移到SS模块
*****************************************************************************/
VOS_UINT32 MMI_FillInEraseSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ERASESS_REQ_STRU             *pstEraseSsReq;

    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;


    pstEraseSsReq = &pstMmiOpParam->EraseSsReq;

    PS_MEM_SET(pstEraseSsReq, 0, sizeof(TAF_SS_ERASESS_REQ_STRU));

    pstEraseSsReq->SsCode = ucNetSsCode;


    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_ALL_BARRING_SS_CODE密码相关操作 */
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstEraseSsReq->OP_BsService = 1;
        pstEraseSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstEraseSsReq->BsService.BsType = ucNetBsType;
    }


    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_FillInActivateSSPara
 功能描述  : 填写ActivateSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - ActivateSS操作类型相应的参数
             pucErrCode    - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS密码下移到SS模块
*****************************************************************************/
VOS_UINT32 MMI_FillInActivateSSPara(
    MN_MMI_SC_SI_PARA_STRU             *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU        *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ACTIVATESS_REQ_STRU          *pstActivateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;
    VOS_UINT32                          ulPasswordLen;

    /*
        呼叫转移业务注册前缀是*且存在参数A情况需要按注册处理
        参考协议3GPP 22030 6.5.2 struct of MMI
    */
    if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & TAF_SS_CODE_MASK))
    {
        if (0 != VOS_StrLen((VOS_CHAR *)pstScSiPara->acSia))
        {
            pMmiOpParam->MmiOperationType = TAF_MMI_REGISTER_SS;
            return MMI_FillInRegisterSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        }

    }

    pstActivateSsReq = &pMmiOpParam->ActivateSsReq;

    PS_MEM_SET(pstActivateSsReq, 0, sizeof(TAF_SS_ACTIVATESS_REQ_STRU));

    pstActivateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* 保存密码到激活消息参数结构 */
            ulPasswordLen = VOS_StrLen(pstScSiPara->acSia);
            if (TAF_SS_MAX_PASSWORD_LEN != ulPasswordLen)
            {
                return MN_ERR_INVALIDPARM;
            }

            PS_MEM_CPY(pMmiOpParam->ActivateSsReq.aucPassword,
                       pstScSiPara->acSia,
                       TAF_SS_MAX_PASSWORD_LEN);
            pMmiOpParam->ActivateSsReq.OP_Password = VOS_TRUE;

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }

        }

        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstActivateSsReq->OP_BsService = 1;
        pstActivateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstActivateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_FillInDeactivateCCBSPara
 功能描述  : 填写DeactivateSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - DeactivateSS操作类型相应的参数
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月24日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MMI_FillInDeactivateCCBSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ERASECC_ENTRY_REQ_STRU       *pstCcbsEraseReq;
    VOS_UINT32                          ulCcbsIndex;

    pstCcbsEraseReq = &pMmiOpParam->stCcbsEraseReq;

    PS_MEM_SET(pstCcbsEraseReq, 0, sizeof(TAF_SS_ERASECC_ENTRY_REQ_STRU));
    ulCcbsIndex = MMI_AtoI(pstScSiPara->acSia);
    if (0 != ulCcbsIndex)
    {
        if ((ulCcbsIndex > 5 )
        || (ulCcbsIndex < 1))
        {
            return MN_ERR_INVALIDPARM;
        }
        else
        {
            pstCcbsEraseReq->OP_CcbsIndex = VOS_TRUE;
            pstCcbsEraseReq->CcbsIndex = (TAF_UINT8)(ulCcbsIndex);
        }
    }
    pstCcbsEraseReq->SsCode = ucNetSsCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_FillInDeactivateSSPara
 功能描述  : 填写DeactivateSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - DeactivateSS操作类型相应的参数
             pucErrCode    - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS密码下移到SS模块
*****************************************************************************/
VOS_UINT32 MMI_FillInDeactivateSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_DEACTIVATESS_REQ_STRU        *pstDeactivateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;
    VOS_UINT32                          ulPasswordLen;

    pstDeactivateSsReq = &pMmiOpParam->DeactivateSsReq;

    PS_MEM_SET(pstDeactivateSsReq, 0, sizeof(TAF_SS_DEACTIVATESS_REQ_STRU));

    pstDeactivateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* 保存密码到去激活消息参数结构 */
            ulPasswordLen = VOS_StrLen(pstScSiPara->acSia);
            if (TAF_SS_MAX_PASSWORD_LEN != ulPasswordLen)
            {
                return MN_ERR_INVALIDPARM;
            }

            PS_MEM_CPY(pMmiOpParam->DeactivateSsReq.aucPassword,
                       pstScSiPara->acSia,
                       TAF_SS_MAX_PASSWORD_LEN);
            pMmiOpParam->DeactivateSsReq.OP_Password = VOS_TRUE;

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
         }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstDeactivateSsReq->OP_BsService = 1;
        pstDeactivateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstDeactivateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_FillInInterrogateSSPara
 功能描述  : 填写InterrogateSS操作需要的参数
 输入参数  : pstScSiPara   - 输入解析后的Sc和Si的数据类型
 输出参数  : pstMmiOpParam - InterrogateSS操作类型相应的参数
             pucErrCode    - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_FillInInterrogateSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_INTERROGATESS_REQ_STRU       *pstInterrogateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;

    pstInterrogateSsReq = &pstMmiOpParam->InterrogateSsReq;

    PS_MEM_SET(pstInterrogateSsReq, 0, sizeof(TAF_SS_INTERROGATESS_REQ_STRU));

    pstInterrogateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_MMI_GET_PASSWD密码相关操作 */

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstInterrogateSsReq->OP_BsService = 1;
        pstInterrogateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstInterrogateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 函 数 名  : MMI_FillInProcessUssdReqPara
 功能描述  : 填写ProcessUssdReq操作需要的参数
 输入参数  : pcInMmiStr       - MMI字串
 输出参数  : pstMmiOpParam    - ProcessUssdReq操作类型相应的参数
             ppcOutRestMmiStr - 剩余字符串的起始地址
 返 回 值  : VOS_TRUE      - 填写参数成功
             其余值        - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_UINT32 MMI_FillInProcessUssdReqPara(
    VOS_CHAR                            *pcInMmiStr,
    VOS_CHAR                            **ppcOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
)
{
    TAF_SS_PROCESS_USS_REQ_STRU         *pstProcessUssdReq;
    VOS_UINT32                          ulStrLen;

    pstProcessUssdReq = &pstMmiOpParam->ProcessUssdReq;

    ulStrLen =  VOS_StrLen(pcInMmiStr);
    if ( ulStrLen > TAF_SS_MAX_USSDSTRING_LEN )
    {
        return MN_ERR_INVALIDPARM;
    }

    PS_MEM_SET(pstProcessUssdReq, 0, sizeof(TAF_SS_PROCESS_USS_REQ_STRU));


    pstProcessUssdReq->DatacodingScheme = pstMmiOpParam->ProcessUssdReq.DatacodingScheme;

    pstProcessUssdReq->UssdStr.usCnt = (VOS_UINT8)VOS_StrLen(pcInMmiStr);

    if (pstProcessUssdReq->UssdStr.usCnt > (TAF_SS_MAX_USSDSTRING_LEN*2))
    {
        pstProcessUssdReq->UssdStr.usCnt = (TAF_SS_MAX_USSDSTRING_LEN*2);
    }

    PS_MEM_CPY(pstProcessUssdReq->UssdStr.aucUssdStr,
               pcInMmiStr,
               pstProcessUssdReq->UssdStr.usCnt);

    *ppcOutRestMmiStr = pcInMmiStr + VOS_StrLen(pcInMmiStr);

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 函 数 名  : MMI_FillInCallOrigPara
 功能描述  : 填写发起呼叫所需要的相关参数
 输入参数  : pcMmiStr        - 输入的MMI字串
 输出参数  : pstMmiOpParam   - 操作类型及其相应的参数
             ppOutRestMmiStr - 剩余字符串的起始地址
 返 回 值  : MN_ERR_NO_ERROR - 填写参数成功
             其余值          - 参数有错误

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2008年09月05日
    作    者   : h44270
    修改内容   : 问题单号：AT2D05508
  3.日    期   : 2011年10月26日
    作    者   : f00179208
    修改内容   : AT移植项目, 使用A核的API:AT_AsciiNumberToBcd替换之前的MN_AsciiNumberToBcd
  4.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
LOCAL VOS_UINT32 MMI_FillInCallOrigPara(
    VOS_CHAR                            *pcMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr
)
{
    VOS_UINT32                          ulRslt;


    /*输入的字串不能超过语音呼叫允许的最大长度*/
    if (VOS_StrLen(pcMmiStr) >  (MN_CALL_MAX_BCD_NUM_LEN*2))
    {
        return MN_ERR_INVALIDPARM;
    }

    if ('+' == pcMmiStr[0])
    {
        /*将Ascii码转换成对应的BCD码*/
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr + 1,
                                     pstMmiOpParam->MnCallOrig.stDialNumber.aucBcdNum,
                                     &pstMmiOpParam->MnCallOrig.stDialNumber.ucNumLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        pstMmiOpParam->MnCallOrig.stDialNumber.enNumType =
                             (VOS_UINT8)(0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);
    }
    else
    {
        /*将Ascii码转换成对应的BCD码*/
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr,
                                 pstMmiOpParam->MnCallOrig.stDialNumber.aucBcdNum,
                                 &pstMmiOpParam->MnCallOrig.stDialNumber.ucNumLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        pstMmiOpParam->MnCallOrig.stDialNumber.enNumType =
                             (VOS_UINT8)(0x80 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    }




    if (MN_ERR_NO_ERROR != ulRslt)
    {
        return ulRslt;
    }

    /*填写其他需要的参数*/
    pstMmiOpParam->MmiOperationType = TAF_MMI_CALL_ORIG;
    pstMmiOpParam->MnCallOrig.enCallType = MN_CALL_TYPE_VOICE;

    pstMmiOpParam->MnCallOrig.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_AUTO;

    pstMmiOpParam->MnCallOrig.enClirCfg = f_enClirOperate;
    pstMmiOpParam->MnCallOrig.stCugCfg.bEnable = VOS_FALSE;
    pstMmiOpParam->MnCallOrig.enCallMode = MN_CALL_MODE_SINGLE;

    *ppOutRestMmiStr = pcMmiStr + VOS_StrLen(pcMmiStr);

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MMI_JudgeMmiOperationType
 功能描述  : 判断MMI字串操作类型
 输入参数  : pInMmiStr  - 输入的MMI字串
 输出参数  : pstMmiOpParam - 操作类型及其相应的参数
             pstScSiPara - 解析后的Sc和Si的数据类型
             ppOutRestMmiStr - 剩余字符串的起始地址
             pulErrCode    - 在解析出是CHLD操作的情况下，如果后面的参数有错误，
                             那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
             pucNetSsCode - 转换后的网络定义的Ss Code
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除特性宏
*****************************************************************************/
 VOS_VOID MMI_JudgeMmiOperationType(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           ucNetSsCode
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    switch(pMmiOpParam->MmiOperationType)
    {
    case TAF_MMI_REGISTER_SS:
        *pulErrCode = MMI_FillInRegisterSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_ERASE_SS:
        *pulErrCode = MMI_FillInEraseSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_ACTIVATE_SS:
        *pulErrCode = MMI_FillInActivateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_DEACTIVATE_SS:
        *pulErrCode = MMI_FillInDeactivateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_INTERROGATE_SS:
    case TAF_MMI_INTERROGATE_CCBS:
        *pulErrCode = MMI_FillInInterrogateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_PROCESS_USSD_REQ:
        *pulErrCode = MMI_FillInProcessUssdReqPara(pInMmiStr,
                                                   ppOutRestMmiStr,
                                                   pMmiOpParam);
        break;

     /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
     case TAF_MMI_DEACTIVATE_CCBS:
        *pulErrCode = MMI_FillInDeactivateCCBSPara(pstScSiPara,
                                                   pMmiOpParam,
                                                   ucNetSsCode);
        break;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    default:
        break;

    }
    return;
}

/*****************************************************************************
 函 数 名  : MMI_MatchSsOpTbl
 功能描述  : 判断是否是呼叫无关补充业务相关的操作(register password除外),
             解析操作参数
 输入参数  : pInMmiStr  - 输入的MMI字串
 输出参数  : pstMmiOpParam - 操作类型及其相应的参数
             pstScSiPara - 解析后的Sc和Si的数据类型
             ppOutRestMmiStr - 剩余字符串的起始地址
             pulErrCode    - 在解析出是CHLD操作的情况下，如果后面的参数有错误，
                             那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
             pucNetSsCode - 转换后的网络定义的Ss Code
 返 回 值  : VOS_TRUE - 成功
             VOS_FALSE - 失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
*****************************************************************************/
 VOS_BOOL MMI_MatchSsOpTbl(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           *pucNetSsCode
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /* 获取特性控制NV地址 */
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (VOS_FALSE == MMI_DecodeScAndSi(pInMmiStr, pMmiOpParam, pstScSiPara, ppOutRestMmiStr))
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
        return VOS_FALSE;
    }

    if (VOS_OK != MMI_TransMmiSsCodeToNetSsCode(pstScSiPara, pucNetSsCode))
    {
        if (VOS_FALSE == MMI_JudgeUssdOperation(pInMmiStr))
        {
            *pulErrCode = MN_ERR_INVALIDPARM;
            return VOS_FALSE;
        }
        pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ((TAF_MMI_DEACTIVATE_SS == pMmiOpParam->MmiOperationType) && (TAF_CCBS_A_SS_CODE == *pucNetSsCode))
    {
        pMmiOpParam->MmiOperationType = TAF_MMI_DEACTIVATE_CCBS;
    }
    else if ((TAF_MMI_INTERROGATE_SS == pMmiOpParam->MmiOperationType) && (TAF_CCBS_A_SS_CODE == *pucNetSsCode))
    {
        pMmiOpParam->MmiOperationType = TAF_MMI_INTERROGATE_CCBS;
    }
    else
    {
        ;
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : MMI_JudgeChldOperation
 功能描述  : 判断是否是呼叫无关补充业务相关的操作(register password除外)
 输入参数  : pcInMmiStr    - 输入的MMI字串
 输出参数  : pstMmiOpParam - 操作类型及其相应的参数
             pucErrCode    - 在解析出是CHLD操作的情况下，如果后面的参数有错误，
                             那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
 返 回 值  : VOS_TRUE      - 是CHLD操作
             VOS_FALSE     - 不是CHLD操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 圈复杂度修改
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
*****************************************************************************/
 VOS_BOOL MMI_JudgeSsOperation(
    VOS_CHAR                            *pInMmiStr,
    VOS_CHAR                            **ppOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_BOOL                            bMatch = VOS_FALSE;
    VOS_CHAR                            acOpType[3];
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;
    VOS_UINT16                          i = 0;
    VOS_UINT32                          ulTableSize;
    MN_MMI_SS_OP_Tbl_STRU              *pstOperationType    = VOS_NULL_PTR;

    *pulErrCode = MN_ERR_NO_ERROR;
    PS_MEM_SET(acOpType, '\0', sizeof(acOpType));


    for (i =0; (!MN_MMI_isdigit(pInMmiStr[i])) && (i < 2); i++)
    {
        acOpType[i] = pInMmiStr[i];
    }

    ulTableSize         = MMI_GetOporationTypeTblSize();
    pstOperationType  = MMI_GetOporationTypeTblAddr();
    for (i = 0; i < ulTableSize; i++)
    {
        if (0 == VOS_MemCmp(pstOperationType->pcSsOpStr,
                             acOpType,
                             MMI_Max(VOS_StrLen(pstOperationType->pcSsOpStr), VOS_StrLen(acOpType))))
        {
            pMmiOpParam->MmiOperationType = pstOperationType->enSsOpType;
            bMatch = VOS_TRUE;
            break;
        }

        pstOperationType++;
    }

    if (VOS_FALSE == bMatch)
    {
        if (VOS_FALSE == MMI_JudgeUssdOperation(pInMmiStr))
        {
            return VOS_FALSE;
        }
        pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
    }
    else
    {
        if (VOS_FALSE == MMI_MatchSsOpTbl(pInMmiStr, pMmiOpParam, &stScSiPara, ppOutRestMmiStr,pulErrCode,&ucNetSsCode))
        {
            return VOS_FALSE;
        }
    }

    MMI_JudgeMmiOperationType(pInMmiStr, pMmiOpParam, &stScSiPara,ppOutRestMmiStr,pulErrCode,ucNetSsCode);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MMI_JudgeChldOperation
 功能描述  : 判断是否是CHLD操作
 输入参数  : pcInMmiStr    - 输入的MMI字串
 输出参数  : pstMmiOpParam - 操作类型及其相应的参数
             pucErrCode    - 在解析出是CHLD操作的情况下，如果后面的参数有错误，
                             那么输出对应的错误码，无错误时，填MN_ERR_NO_ERROR
 返 回 值  : VOS_TRUE      - 是CHLD操作
             VOS_FALSE     - 不是CHLD操作

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_BOOL MMI_JudgeChldOperation(
    VOS_CHAR                            *pcInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_CHLD_OP_Tbl_STRU             stChldOpTbl[] = {
                                                         {"0",           MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"1",           MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"10",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"11",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"12",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"13",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"14",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"15",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"16",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"17",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"18",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"19",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"2",           MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH, {0, 0, 0, 0, 0, 0, 0}},
                                                         {"20",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"21",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"22",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"23",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"24",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"25",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"26",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"27",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"28",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"29",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"3",           MN_CALL_SUPS_CMD_BUILD_MPTY,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"4",           MN_CALL_SUPS_CMD_ECT,               {0, 0, 0, 0, 0, 0, 0}},
                                                         {"4*",          MN_CALL_SUPS_CMD_DEFLECT_CALL,      {0, 0, 0, 0, 0, 0, 0}},
                                                         {"5",           MN_CALL_SUPS_CMD_ACT_CCBS,          {0, 0, 0, 0, 0, 0, 0}},
                                                         {VOS_NULL_PTR,  0,                                 {0, 0, 0, 0, 0, 0, 0}}
                                                        };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stChldOpTbl[i].pcMmiChldStr)
    {
        if(0 == VOS_MemCmp(pcInMmiStr,
                            stChldOpTbl[i].pcMmiChldStr,
                            MMI_Max(VOS_StrLen(pcInMmiStr), VOS_StrLen(stChldOpTbl[i].pcMmiChldStr))))
        {
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stChldOpTbl[i].pcMmiChldStr)
    {
        return VOS_FALSE;
    }

    pstMmiOpParam->MmiOperationType = TAF_MMI_CALL_CHLD_REQ;

    switch(stChldOpTbl[i].enChldOpType)
    {
    case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB;
        break;

    case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH;
        break;

    case MN_CALL_SUPS_CMD_REL_CALL_X:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_CALL_X;
        pstMmiOpParam->MnCallSupsReq.callId = (VOS_UINT8)(pcInMmiStr[1] - '0');
        break;

    case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;
        break;

    case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X;
        pstMmiOpParam->MnCallSupsReq.callId = (VOS_UINT8)(pcInMmiStr[1] - '0');
        break;

    case MN_CALL_SUPS_CMD_BUILD_MPTY:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_BUILD_MPTY;
        break;

    case MN_CALL_SUPS_CMD_ECT:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_ECT;
        break;

    case MN_CALL_SUPS_CMD_DEFLECT_CALL:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_DEFLECT_CALL;
        break;

    default:
        /*认为是CCBS,因为目前不支持CCBS,暂时没写处理代码*/
        *pulErrCode = MN_ERR_INVALIDPARM;
        break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MN_MmiStringParse
 功能描述  : 将Mmi字串进行解析，将当前的MMI字串解析成对应的操作，以及操作需要的参数
 输入参数  : pInMmiStr       - 输入的MMI字串
             inCall          - 当前呼叫的状态，是处于呼叫状态，还是处于空闲状态
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - 操作类型及其相应的参数
 返 回 值  : MN_ERR_NO_ERROR - 解析成功
             其余返回值      - 解析失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目:将变量f_enClirOperate的赋值移到本函数中
  3.日    期   : 2012年02月23日
    作    者   : l65478
    修改内容   : DTS2012021604543,GCF测试，CMMI命令发送数据错误
  4.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS密码下移到SS模块
  5.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
TAF_UINT32 MN_MmiStringParse(
    TAF_CHAR                            *pInMmiStr,
    TAF_BOOL                            inCall,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    TAF_CHAR                            **ppOutRestMmiStr
)
{
    TAF_UINT32                          ulRslt = MN_ERR_NO_ERROR;
    TAF_UINT32                          ulRtrnRslt;
    TAF_UINT32                          ulStrLen;


    if (VOS_NULL_PTR == pInMmiStr)
    {
        MN_ERR_LOG("MN_MmiStringParse: Input Invalid Param");
        return MN_ERR_INVALIDPARM;
    }

    ulStrLen = VOS_StrLen(pInMmiStr);
    if (   (0 == ulStrLen)
        || ((VOS_TRUE != inCall) && (VOS_FALSE != inCall))
        || (VOS_NULL_PTR == pMmiOpParam) || (VOS_NULL_PTR == ppOutRestMmiStr))
    {
        MN_ERR_LOG("MN_MmiStringParse: Input Invalid Param");
        return MN_ERR_INVALIDPARM;
    }

    PS_MEM_SET(pMmiOpParam, 0, sizeof(MN_MMI_OPERATION_PARAM_STRU));

    /*判断当前是不是显示IMEI操作*/
    if (VOS_TRUE == MMI_JudgeImeiOperation(pInMmiStr,
                                           ppOutRestMmiStr,
                                           pMmiOpParam))
    {
        return MN_ERR_NO_ERROR;
    }

    /*判断当前是不是临时模式下抑制或者激活CLIR操作*/
    if (VOS_TRUE == MMI_JudgeTmpModeClirOp(pInMmiStr,
                                           ppOutRestMmiStr,
                                           pMmiOpParam))
    {
        /* 作为独立的解码函数，不应与AT模块的业务功能耦合，删除AT模块业务全局变量的赋值操作 */
        return MN_ERR_NO_ERROR;
    }

    /*判断当前的操作类型是不是PIN操作类型 */
    if (VOS_TRUE == MMI_JudgePinOperation(pInMmiStr,
                                          pMmiOpParam,
                                          ppOutRestMmiStr,
                                          &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*判断当前的操作类型是不是修改密码操作 */
    if (VOS_TRUE == MMI_JudgePwdOperation(pInMmiStr,
                                          pMmiOpParam,
                                          ppOutRestMmiStr,
                                          &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*判断当前的操作类型是不是其他已知的呼叫无关补充业务操作*/
    if (VOS_TRUE == MMI_JudgeSsOperation(pInMmiStr,
                                         ppOutRestMmiStr,
                                         pMmiOpParam,
                                         &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*
    对于短字串的处理，根据协议22.030中的规定:
    "Entry of 1 or 2 characters defined in the 3GPP TS 23.038 [8] Default Alphabet followed by SEND"
    以及22.030中的对应的流程图处理
    */
    if ((2 == ulStrLen) || (1 == ulStrLen))
    {
        if (VOS_TRUE == inCall)
        {
            /*判定是不是CHLD命令*/
            if (VOS_TRUE == MMI_JudgeChldOperation(pInMmiStr, pMmiOpParam, &ulRtrnRslt))
            {
                *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(pInMmiStr);
                return ulRtrnRslt;
            }

            /* 如果不是CHLD命令，那么认为是USSD操作，填写相应的参数 */
            pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
            return MMI_FillInProcessUssdReqPara(pInMmiStr, ppOutRestMmiStr, pMmiOpParam);
        }
        else
        {
            /*在这种情况下，如果是'1'开头，那么认为应该发起一个呼叫*/
            if ('1' == pInMmiStr[0])
            {
                ulRslt = MMI_FillInCallOrigPara(pInMmiStr,
                                                pMmiOpParam,
                                                ppOutRestMmiStr);
                if (MN_ERR_NO_ERROR != ulRslt)
                {
                    return ulRslt;
                }
                return MN_ERR_NO_ERROR;
            }
            else
            {
                /*如果不是'1'开头，那么也是作为USSD字串来处理 */
                pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
                return MMI_FillInProcessUssdReqPara(pInMmiStr, ppOutRestMmiStr, pMmiOpParam);
            }
        }


    }

    return MMI_FillInCallOrigPara(pInMmiStr, pMmiOpParam, ppOutRestMmiStr);

    /* 先删除，对于字符'P','W'的处理，是否放在这里，尚待讨论，
       暂时不支持， */
    #if 0
    /*
    在最后认定是发起一个呼叫
    如果在字符串中携带有字符'p'，那么字符'p'之后的号码作为dtmf音发往网侧
    */
    pcTmp1 = MMI_StrChr(pInMmiStr, pInMmiStr + VOS_StrLen(pInMmiStr), 'p')
    pcTmp2 = MMI_StrChr(pInMmiStr, pInMmiStr + VOS_StrLen(pInMmiStr), 'p')

    if ((pcTmp1 != VOS_NULL_PTR) || (pcTmp2 != VOS_NULL_PTR))
    {
        pcTmp1 = (pcTmp1 == VOS_NULL_PTR)? pcTmp2 : pcTmp1;

        if ((pcTmp1 - pInMmiStr) > (MN_CALL_MAX_BCD_NUM_LEN * 2))
        {
            return MN_ERR_INVALIDPARM;
        }

        PS_MEM_CPY(acAsciiNum, pInMmiStr, pcTmp1 - pInMmiStr);
        acAsciiNum[pcTmp1 - pInMmiStr]='\0';

        pMmiOpParam->MmiOperationType = TAF_MMI_CALL_ORIG;
        pMmiOpParam->MnCallReq.callType = MN_CALL_TYPE_VOICE;
        pMmiOpParam->MnCallReq.dialNumber.NumType =
                 0x8000 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN;

        ulRtrnRslt = TAF_STD_ConvertAsciiNumberToBcd(acAsciiNum,
                                         pMmiOpParam->MnCallReq.dialNumber.BcdNum,
                                         &pMmiOpParam->MnCallReq.dialNumber.NumLen);
        if (MN_ERR_NO_ERROR != ulRtrnRslt)
        {
            return ulRtrnRslt;
        }

        pMmiOpParam->MnCallReq.dialNumber.BcdNum = ;

        pMmiOpParam->MnCallReq.ClirCfg = MN_CALL_CLIR_AS_SUBS;
        pMmiOpParam->MnCallReq.cugCfg.Enable = VOS_FALSE;
        pMmiOpParam->MnCallReq.callMode = MN_CALL_MODE_SINGLE;

        usDtmfStrLen = VOS_StrLen(pInMmiStr) - (pcTmp1 - pInMmiStr + 1);
        if (MMI_MAX_DTMF_STR_LEN < usDtmfStrLen)
        {
            return MN_ERR_INVALIDPARM;
        }

        pMmiOpParam->SubseqMmiOperationType = TAF_MMI_CALL_SEND_DTMF;
        PS_MEM_CPY(pMmiOpParam->aDtmfStr, pcTmp1 + 1, usDtmfStrLen);

        *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(pInMmiStr);
        return MN_ERR_NO_ERROR;
    }

    pMmiOpParam->MmiOperationType = TAF_MMI_CALL_ORIG;
    pMmiOpParam->MnCallReq.callType = MN_CALL_TYPE_VOICE;
    pMmiOpParam->MnCallReq.dialNumber.NumType =
             0x8000 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN;

    ulRtrnRslt = TAF_STD_ConvertAsciiNumberToBcd(pInMmiStr,
                                     pMmiOpParam->MnCallReq.dialNumber.BcdNum,
                                     &pMmiOpParam->MnCallReq.dialNumber.NumLen);
    if (MN_ERR_NO_ERROR != ulRtrnRslt)
    {
        return ulRtrnRslt;
    }

    pMmiOpParam->MnCallReq.dialNumber.BcdNum = ;

    pMmiOpParam->MnCallReq.ClirCfg = MN_CALL_CLIR_AS_SUBS;
    pMmiOpParam->MnCallReq.cugCfg.Enable = VOS_FALSE;
    pMmiOpParam->MnCallReq.callMode = MN_CALL_MODE_SINGLE;

    *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(pInMmiStr);

    return MN_ERR_NO_ERROR;

    #endif


}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

