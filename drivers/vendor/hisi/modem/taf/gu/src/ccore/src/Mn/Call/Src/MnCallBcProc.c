/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallBcProc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2006年12月1日
  最近修改   : 2006年12月1日
  功能描述   : 实现CS呼叫中承载能力相关参数的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年12月09日
    作    者   : s62952
    修改内容   :根据问题单AT2D06968
  3.日    期   : 2009年05月06日
    作    者   : s62952
    修改内容   :根据问题单AT2D11585
  4.日    期   : 2009年05月14日
    作    者   : h44270
    修改内容   : 问题单号:AT2D11670, 执行GCF 协议用例8.2.4.1.cs 由于NAS cc setup消息填充与脚本不匹配导致用例inconclusive
  5.日    期   : 2009年12月6日
    作    者   : h44270
    修改内容   : 问题单号:AT2D15311,增加手机支持的能力,半速率和AMR

  6.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  7.日    期   : 2010年4月7日
    作    者   : zhoujun /z40661
    修改内容   : 可配置当前CODEC类型
******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallBcProc.h"
#include "MnCallMsgDef.h"
#include "MnComm.h"
#include "NasIeUtil.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"

#include "MnCall.h"
#include "NVIM_Interface.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2 宏，结构和变量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_BC_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/


/* BC字段值的最大个数，定义BC字段最多有多少个值 */
#define MN_CALL_BC_FLD_VAL_MAX_NUM      14



/* BC字段名称定义 */
typedef enum
{
     MN_CALL_BC_FLD_RCR        =  0,                                            /* Radio channel requirement */
     MN_CALL_BC_FLD_CODING_STD,                                                 /* Coding standard  1*/
     MN_CALL_BC_FLD_TRANS_MOD,                                                  /* Transfer mode  2*/
     MN_CALL_BC_FLD_ITC,                                                        /* Information transfer capability 3*/
     MN_CALL_BC_FLD_CODING,                                                     /* Coding 4*/
     MN_CALL_BC_FLD_CTM,                                                        /* CTM 5*/
     MN_CALL_BC_FLD_SPCH_VER_IND,                                               /* Speech version indication 6*/
     MN_CALL_BC_FLD_COMPRESS,                                                   /* Compression 7*/
     MN_CALL_BC_FLD_STRUCTURE,                                                  /* Structure 8*/
     MN_CALL_BC_FLD_DUPL_MODE,                                                  /* Duplex mode 9*/
     MN_CALL_BC_FLD_CONFIGUR,                                                   /* Configuration 10*/
     MN_CALL_BC_FLD_NIRR,                                                       /* NIRR 11*/
     MN_CALL_BC_FLD_ESTABLI,                                                    /* Establishment 12*/
     MN_CALL_BC_FLD_ACCESS_ID,                                                  /* Access identity 13*/
     MN_CALL_BC_FLD_RA,                                                         /* Rate adaption 14*/
     MN_CALL_BC_FLD_SIGNAL,                                                     /* Signalling accesss protocol 15*/
     MN_CALL_BC_FLD_OTHER_ITC,                                                  /* Other ITC 16*/
     MN_CALL_BC_FLD_ORA,                                                        /* Ohter rate adaption 17*/
     MN_CALL_BC_FLD_HDR_NO_HDR,                                                 /* Rate adaption header/no header 18*/
     MN_CALL_BC_FLD_MULTI_FRAME,                                                /* Multiple frame establishment support 19*/
     MN_CALL_BC_FLD_MODE,                                                       /* Mode of operation 20*/
     MN_CALL_BC_FLD_LLI,                                                        /* Logical link identifier negotiation 21*/
     MN_CALL_BC_FLD_ASSIGNOR,                                                   /* Assignor/Assignee 22*/
     MN_CALL_BC_FLD_INB_NEG,                                                    /* In band/Out band negotiation 23*/
     MN_CALL_BC_FLD_LAYER1_ID,                                                  /* Layer 1 indenetity 24*/
     MN_CALL_BC_FLD_UIL1P,                                                      /* User information layer 1 protocol 25*/
     MN_CALL_BC_FLD_SYNC_ASYNC,                                                 /* Synchronous/asynchronous 26*/
     MN_CALL_BC_FLD_N_STOP_BIT,                                                 /* Number of stop bits 27*/
     MN_CALL_BC_FLD_NEGOTIATION,                                                /* Negotiation 28*/
     MN_CALL_BC_FLD_N_DATA_BIT,                                                 /* Number of data bits 29*/
     MN_CALL_BC_FLD_USER_RATE,                                                  /* User rate 30*/
     MN_CALL_BC_FLD_INTMD_RATE,                                                 /* Intermediate rate 31*/
     MN_CALL_BC_FLD_NIC_ON_TX,                                                  /* Network independent clock on Tx 32*/
     MN_CALL_BC_FLD_NIC_ON_RX,                                                  /* Network independent clock on Rx 33*/
     MN_CALL_BC_FLD_PARITY,                                                     /* Parity information 34*/
     MN_CALL_BC_FLD_CE,                                                         /* Connection element 35*/
     MN_CALL_BC_FLD_MODEM_TYPE,                                                 /* Modem type 36*/
     MN_CALL_BC_FLD_OMT,                                                        /* Other modem type 37*/
     MN_CALL_BC_FLD_FNUR,                                                       /* Fixed network user rate 38*/
     MN_CALL_BC_FLD_ACC,                                                        /* Acceptable channel codings 39*/
     MN_CALL_BC_FLD_MAX_TCH,                                                    /* Maximum number of traffic channels 40*/
     MN_CALL_BC_FLD_UIMI,                                                       /* User initiated modification indication 41*/
     MN_CALL_BC_FLD_WAIUR,                                                      /* Wanted air interface user rate 42*/
     MN_CALL_BC_FLD_EXT_ACC,                                                    /* Acceptable channel coding extended 43*/
     MN_CALL_BC_FLD_ASYM_IND,                                                   /* Channel coding asymmetry indication 44*/
     MN_CALL_BC_FLD_LAYER2_ID,                                                  /* Layer 2 identity 45*/
     MN_CALL_BC_FLD_UIL2P,                                                      /* User information layer 2 protocol 46*/
     MN_CALL_BC_NUM_OF_FIELD                                                    /* Number of BC fields, should be 47*/
} MN_CALL_BC_FLD_NAME_ENUM;

typedef enum
{
    MN_CALL_VAR_PARM_MT,                                    /* 返回的可变参数为Modem type */
    MN_CALL_VAR_PARM_OMT,                                   /* 返回的可变参数为Other modem type */
    MN_CALL_VAR_PARM_RA,                                    /* 返回的可变参数为Rate adaption */
    MN_CALL_VAR_PARM_ORA,                                   /* 返回的可变参数为Other rate adaption */
    MN_CALL_VAR_PARM_NO_OUTPUT,                             /* 可变参数没输出 */
    MN_CALL_VAR_PARM_ERROR                                  /* 发生错误 */
} MN_CALL_VAR_PARM_ENUM;



/* Structure of supported speech versions */
typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucVers[MN_CALL_BC_MAX_SPH_VER_NUM];
} MN_CALL_BC_SPEECH_VERS_STRU;

/* BC字段信息的结构
   ucFixedVal - 设定的值。有些BC字段在构造时不是根据输入参数而变化的，
                而是在编译时或初始化时就已经定好的。
   ucNumOfVals - 该字段支持的值的个数，0表示不需要对该字段做检查
   aucSupptVals - 该字段所有支持的值                               */
typedef struct
{
    VOS_UINT8  ucFixedVal;
    VOS_UINT8  ucNumOfVals;
    VOS_UINT8  aucSupptVals[MN_CALL_BC_FLD_VAL_MAX_NUM];
} MN_CALL_BC_FIELD_INFO_STRU;



LOCAL MN_CALL_UMTS_CODEC_TYPE_STRU  f_stMnCallUmtsCodecTypes;

/* Supported speech versions */
LOCAL MN_CALL_BC_SPEECH_VERS_STRU   f_stMnCallSphVers;

/* BC field informations list */
LOCAL MN_CALL_BC_FIELD_INFO_STRU    f_astMnCallBcFldInfo[MN_CALL_BC_NUM_OF_FIELD] = {
/* | Fixed value                    | NSVs |  Support values         | */
    {MN_CALL_BC_VAL_RCR_DUAL_FR,    0,        {0}                             },/* Radio channel requirement 0*/
    {MN_CALL_BC_VAL_CODSTD_GSM,     1,        {MN_CALL_BC_VAL_CODSTD_GSM}     },/* Coding standard 1*/
    {MN_CALL_BC_VAL_TM_CIRCUIT,     1,        {MN_CALL_BC_VAL_TM_CIRCUIT}     },/* Transfer mode 2*/
    {0,                             6,        {MN_CALL_BC_VAL_ITC_SPEECH,
                                               MN_CALL_BC_VAL_ITC_UDI,
                                               MN_CALL_BC_VAL_ITC_3D1K,
                                               MN_CALL_BC_VAL_ITC_FAX,
                                               MN_CALL_BC_VAL_ITC_OTHER,
                                               MN_CALL_BC_VAL_ITC_AUX_SPEECH} },/* Information transfer capability 3*/
    {MN_CALL_BC_VAL_CODING_EXT_ITC, 1,        {MN_CALL_BC_VAL_CODING_EXT_ITC} },/* Coding 4*/
    {MN_CALL_BC_VAL_CTM_N_SUPPORT,  1,        {MN_CALL_BC_VAL_CTM_N_SUPPORT}  },/* CTM 5*/
    {0,                             0,        {0}                             },/* Speech version indication 6*/

    /*In case of a Mobile Terminated Call, if the SETUP message does not contain
    a BC-IE, the MS shall behave as if the DC is set to "data compression not
    possible".If a sending entity, based on an earlier version of the protocol,
    sends a SETUP message containing "DC.. compression possible/ allowed" instead
    of the default value "NO.. compression  not possible/allowed"as defined in
    Table B.5 then the receiving MS or the receiving network may ignore the DC
    value and may return either "NO.. compression  not possible/allowed" or
    "DC.. compression possible/allowed" in the CALL CONF/CALL PROC message.*/
    {MN_CALL_BC_VAL_COMP_NOT_ALLOW, 2,        {MN_CALL_BC_VAL_COMP_NOT_ALLOW,
                                               MN_CALL_BC_VAL_COMP_ALLOW } },/* Compression 7*/
    {0,                             2,        {MN_CALL_BC_VAL_STRUCT_SDU,
                                               MN_CALL_BC_VAL_STRUCT_UNSTRU}  },/* Structure 8*/
    {MN_CALL_BC_FLD_DUPL_MODE,      2,        {MN_CALL_BC_VAL_DUPLMOD_HALF,
                                               MN_CALL_BC_VAL_DUPLMOD_FULL}   },/* Duplex mode 9*/
    {MN_CALL_BC_VAL_CONFIGUR_PTP,   1,        {MN_CALL_BC_VAL_CONFIGUR_PTP}   },/* Configuration 10*/
    {0,                             2,        {MN_CALL_BC_VAL_NIRR_NO_MEAN,
                                               MN_CALL_BC_VAL_NIRR_6K}        },/* NIRR 11*/
    {MN_CALL_BC_VAL_ESTABLI_DEMAND, 1,        {MN_CALL_BC_VAL_ESTABLI_DEMAND} },/* Establishment 12*/
    {MN_CALL_BC_VAL_ACCESS_ID_OCT,  1,        {MN_CALL_BC_VAL_ACCESS_ID_OCT}  },/* Access identity 13*/
    {MN_CALL_BC_VAL_RA_NO,          4,        {MN_CALL_BC_VAL_RA_NO,
                                               MN_CALL_BC_VAL_RA_V110,
                                               MN_CALL_BC_VAL_RA_X31,
                                               MN_CALL_BC_VAL_RA_OTHER}       },/* Rate adaption 14*/
    {MN_CALL_BC_VAL_SIGNAL_I440,    1,        {MN_CALL_BC_VAL_SIGNAL_I440}    },/* Signalling accesss protocol 15*/
    {MN_CALL_BC_VAL_OTHITC_RDI,     1,        {MN_CALL_BC_VAL_OTHITC_RDI}     },/* Other ITC 16*/
    {MN_CALL_BC_VAL_ORA_V120,       3,        {MN_CALL_BC_VAL_ORA_V120,
                                               MN_CALL_BC_VAL_ORA_H223_245,
                                               MN_CALL_BC_VAL_ORA_PIAFS}      },/* Ohter rate adaption 17*/
    {MN_CALL_BC_VAL_RA_HDR_INCLUD,  0,        {0}                             },/* Rate adaption header/no header 18*/
    {MN_CALL_BC_VAL_MF_SUPPT,       0,        {0}                             },/* Multiple frame establishment support 19*/
    {MN_CALL_BC_VAL_PROT_SENSI_MODE,0,        {0}                             },/* Mode of operation 20*/
    {MN_CALL_BC_VAL_LLI_DEFAULT,    0,        {0}                             },/* Logical link identifier negotiation 21*/
    {MN_CALL_BC_VAL_DEF_ASSIGNEE,   0,        {0}                             },/* Assignor/Assignee 22*/
    {MN_CALL_BC_VAL_INBNEG_INB,     0,        {0}                             },/* In band/Out band negotiation 23*/
    {MN_CALL_BC_VAL_L1_ID_OCT,      1,        {MN_CALL_BC_VAL_L1_ID_OCT}      },/* Layer 1 indenetity 24*/
    {MN_CALL_BC_VAL_UIL1P_DEFAULT,  1,        {MN_CALL_BC_VAL_UIL1P_DEFAULT}  },/* User information layer 1 protocol 25*/
    {0,                             0,        {0}                             },/* Synchronous/asynchronous 26*/
    {MN_CALL_BC_VAL_NSB_1BIT,       0,        {0}                             },/* Number of stop bits 27*/
    {MN_CALL_BC_VAL_NEG_NO_IBN,     1,        {MN_CALL_BC_VAL_NEG_NO_IBN}     },/* Negotiation 28*/
    {MN_CALL_BC_VAL_NDB_8BIT,       0,        {0}                             },/* Number of data bits 29*/
    {MN_CALL_BC_VAL_UR_9K6,         5,        {MN_CALL_BC_VAL_UR_300,
                                               MN_CALL_BC_VAL_UR_1K2,
                                               MN_CALL_BC_VAL_UR_2K4,
                                               MN_CALL_BC_VAL_UR_4K8,
                                               MN_CALL_BC_VAL_UR_9K6}         },/* User rate 30*/
    {0,                             2,        {MN_CALL_BC_VAL_IR_8K,
                                               MN_CALL_BC_VAL_IR_16K}         },/* Intermediate rate 31*/
    {MN_CALL_BC_VAL_NICTX_N_SUPPT,  1,        {MN_CALL_BC_VAL_NICTX_N_SUPPT}  },/* Network independent clock on Tx 32*/
    {MN_CALL_BC_VAL_NICRX_N_SUPPT,  1,        {MN_CALL_BC_VAL_NICRX_N_SUPPT}  },/* Network independent clock on Rx 33*/
    {MN_CALL_BC_VAL_PARITY_NONE,    5,        {MN_CALL_BC_VAL_PARITY_ODD,
                                               MN_CALL_BC_VAL_PARITY_EVEN,
                                               MN_CALL_BC_VAL_PARITY_NONE,
                                               MN_CALL_BC_VAL_PARITY_FORCE_0,
                                               MN_CALL_BC_VAL_PARITY_FORCE_1} },/* Parity information 34*/
    {0,                             0,        {0}                             },/* Connection element 35*/
    {0,                             7,        {MN_CALL_BC_VAL_MT_NONE,
                                               MN_CALL_BC_VAL_MT_V21,
                                               MN_CALL_BC_VAL_MT_V22,
                                               MN_CALL_BC_VAL_MT_V22BIS,
                                               MN_CALL_BC_VAL_MT_V26,
                                               MN_CALL_BC_VAL_MT_V32,
                                               MN_CALL_BC_VAL_MT_AUTOBAUD}    },/* Modem type 36*/
    {MN_CALL_BC_VAL_OMT_NONE,       2,        {MN_CALL_BC_VAL_OMT_NONE,
                                               MN_CALL_BC_VAL_OMT_V34}        },/* Other modem type 37*/
    {MN_CALL_BC_VAL_FNUR_NA,        6,        {MN_CALL_BC_VAL_FNUR_NA,
                                               MN_CALL_BC_VAL_FNUR_9K6,
                                               MN_CALL_BC_VAL_FNUR_14K4,
                                               MN_CALL_BC_VAL_FNUR_19K2,
                                               MN_CALL_BC_VAL_FNUR_28K8,
                                               MN_CALL_BC_VAL_FNUR_64K }      },/* Fixed network user rate 38*/
    {0,                             0,        {0}                             },/* Acceptable channel codings 39*/
    {MN_CALL_BC_VAL_MTCH_1,         1,        {0}                             },/* Maximum number of traffic channels 40*/
    {MN_CALL_BC_VAL_UIMI_NA,        0,        {0}                             },/* User initiated modification indication 41*/
    {MN_CALL_BC_VAL_WAIUR_NA,       1,        {0}                             },/* Wanted air interface user rate 42*/
    {0,                             0,        {0}                             },/* Acceptable channel coding extended 43*/
    {0,                             0,        {0}                             },/* Channel coding asymmetry indication 44*/
    {MN_CALL_BC_VAL_L2_ID_OCT,      1,        {MN_CALL_BC_VAL_L2_ID_OCT}      },/* Layer 2 identity 45*/
    {MN_CALL_BC_VAL_UIL2P_DC1_DC3,  2,        {MN_CALL_BC_VAL_UIL2P_DC1_DC3,
                                               MN_CALL_BC_VAL_UIL2P_COPNOFLCT}} /* User information layer 2 protocol 46*/
};

/*lint -e961*/

/* 检查BC的一个字段 */
#define MN_CALL_BC_CHECK_FIELD(name, val)  \
        if (VOS_FALSE == MN_CALL_BcIsValueSupported((name), (val))) \
        { \
            return VOS_ERR; \
        }

/* 取得BC参数中为固定值的字段的值 */
#define MN_CALL_BC_FIXED_FLD_VAL(name)  \
    f_astMnCallBcFldInfo[(name)].ucFixedVal
/*lint +e961*/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/



/*****************************************************************************
 函 数 名  : MN_CALL_IsCodecTypeValid
 功能描述  : 判断当前的参数是否合法
 输入参数  : ucCodecType    - 当前的codec类型是否合法
 输出参数  : 无
 返 回 值  : VOS_TRUE:合法
              VOS_FALSE:非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MN_CALL_IsCodecTypeValid(
    VOS_UINT8                           ucCodecType
)
{
    if ( ( MN_CALL_BC_VAL_SPH_VER_FR_1 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_2 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_3 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_HR_1 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_HR_3 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_5 != ucCodecType ))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MN_CALL_IsUmtsCodecTypeValid
 功能描述  : 判断UMTS的codec类型是否合法
 输入参数  : ucUmtsCodecType:UMTS的codec类型
 输出参数  : 无
 返 回 值  : VOS_TRUE:合法
             VOS_FALSE:非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MN_CALL_IsUmtsCodecTypeValid(
    VOS_UINT8                           ucUmtsCodecType
)
{
    if ( ( MN_CALL_UMTS_CODEC_TYPE_AMR != ucUmtsCodecType )
      && ( MN_CALL_UMTS_CODEC_TYPE_AMR2 != ucUmtsCodecType )
      && ( MN_CALL_UMTS_CODEC_TYPE_AMRWB != ucUmtsCodecType ))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MN_CALL_GsmCapaProcInit
 功能描述  : 2G下支持的语音能力初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年07月22日
    作    者   : j00177245
    修改内容   : 清理Coverity

*****************************************************************************/
VOS_VOID  MN_CALL_GsmCapaProcInit( VOS_VOID )
{
    /* 初始化语音编码版本列表 */
    MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU   stCodecType;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;


    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    ulDefaultValue          = VOS_FALSE;
    if ( NV_OK != NV_Read(en_NV_Item_MED_CODEC_TYPE,
                         &stCodecType,
                          sizeof(stCodecType)))
    {
        ulDefaultValue = VOS_TRUE;
    }

    /* 检查NVIM中的参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( stCodecType.ucCodecTypeNum > MN_CALL_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue = VOS_TRUE;
        stCodecType.ucCodecTypeNum = MN_CALL_BC_MAX_SPH_VER_NUM;
    }

    f_stMnCallSphVers.ucCnt = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < stCodecType.ucCodecTypeNum; i++ )
    {
        if ( VOS_FALSE == MN_CALL_IsCodecTypeValid(stCodecType.aucCodecType[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }


        /* 将NVIM中的语音能力加入到内存中 */
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt] = stCodecType.aucCodecType[i];
        f_stMnCallSphVers.ucCnt++;
    }

    /* 此处表示需要使用默认值 */
    if ( VOS_TRUE == ulDefaultValue )
    {
        /*lint -e961*/
        f_stMnCallSphVers.ucCnt  = 0;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_3;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_HR_3;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_2;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_1;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_HR_1;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_5;
        /*lint +e961*/
    }
}


/*****************************************************************************
 函 数 名  : MN_CALL_UmtsCapaProcInit
 功能描述  : 3G下支持的语音能力初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity

*****************************************************************************/
VOS_VOID  MN_CALL_UmtsCapaProcInit( VOS_VOID )
{
    MN_CALL_UMTS_CODEC_TYPE_STRU        stCodecType;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    ulDefaultValue          = VOS_FALSE;
    if ( NV_OK != NV_Read(en_NV_Item_UMTS_CODEC_TYPE,
                         &stCodecType,
                          sizeof(stCodecType)))
    {
        ulDefaultValue = VOS_TRUE;
    }

    /* 检查NVIM中的参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( stCodecType.ucCnt > MN_CALL_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue = VOS_TRUE;
        stCodecType.ucCnt = MN_CALL_MAX_UMTS_CODEC_TYPE_NUM;
    }

    f_stMnCallUmtsCodecTypes.ucCnt = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < stCodecType.ucCnt; i++ )
    {
        if ( VOS_FALSE == MN_CALL_IsUmtsCodecTypeValid(stCodecType.aucUmtsCodec[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }


        /* 将NVIM中的语音能力加入到内存中 */
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt]= stCodecType.aucUmtsCodec[i];
        f_stMnCallUmtsCodecTypes.ucCnt++;
    }


    if ( VOS_TRUE == ulDefaultValue )
    {
        f_stMnCallUmtsCodecTypes.ucCnt = 0;
        /*lint -e961*/
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt++] = MN_CALL_UMTS_CODEC_TYPE_AMR;
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt++] = MN_CALL_UMTS_CODEC_TYPE_AMR2;
        /*lint +e961*/
    }
}




/*****************************************************************************
 函 数 名  : MN_CALL_CapaProcInit
 功能描述  : 初始化Capability Proc模块。主要是初始化语音编码版本列表和
             BC字段信息列表。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年12月09日
    作    者   : s62952
    修改内容   :根据问题单AT2D06968
 3.日    期   : 2009年05月06日
    作    者   : s62952
    修改内容   :根据问题单AT2D11585
 4.日    期   : 2009年06月23日
    作    者   : z00161729
    修改内容   :根据问题单DTS2010062200036,修改支持的语音编码版本顺序

 5.日    期   : 2012年2月9日
   作    者   : z40661
   修改内容   : 将语音能力和优先级写入NVIM中，支持后续扩展
 6.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理

  7.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : DTS2012101809567,语音支持的能力需要区分G和W模式
*****************************************************************************/
VOS_VOID MN_CALL_CapaProcInit()
{
    MN_CALL_GsmCapaProcInit();

    MN_CALL_UmtsCapaProcInit();

    return;

} /* MN_CALL_CapaProcInit */


/*****************************************************************************
 函 数 名  : MN_CALL_ConfigGsmCapaProc
 功能描述  : 可配置当前CODEC类型
 输入参数  : enCapaConfig  - 当前需要配置的GSM支持的CODEC类型
 输出参数  : 无
 返 回 值  : VOS_UINT32 - 设置成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月7日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_ConfigGsmCapaProc(
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enCapaConfig
)
{
    VOS_UINT32 ulRlst;

    if ((enCapaConfig < NAS_OM_GSM_CODEC_FR)
     || (enCapaConfig > NAS_OM_GSM_CODEC_FR_EFR_HR_AMR))
    {
        return VOS_ERR;
    }

    /*
    HR   ->  MN_CALL_BC_VAL_SPH_VER_HR_1  MN_CALL_BC_VAL_SPH_VER_HR_3
    FR   ->  MN_CALL_BC_VAL_SPH_VER_FR_1
    EFR  ->  MN_CALL_BC_VAL_SPH_VER_FR_2
    AMR-FR/AMR-HR -> MN_CALL_BC_VAL_SPH_VER_FR_3
    */
    ulRlst = VOS_OK;
    /*lint -e961*/
    switch ( enCapaConfig )
    {
        case NAS_OM_GSM_CODEC_FR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_HR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_HR_1;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_HR_3;
            break;

        case NAS_OM_GSM_CODEC_FR_EFR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_2;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_AMR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_3;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_EFR_HR_AMR :
            MN_CALL_CapaProcInit();
            break;

        default:
            MN_WARN_LOG1("MN_CALL_ConfigGsmCapaProc:Invalid Para",enCapaConfig);
            ulRlst = VOS_ERR;
            break;
    }
    /*lint +e961*/

    return ulRlst;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ConvertMnCodecToOmCodec
 功能描述  : 将GSM当前使用的Codec类型，转换为Om接口中的类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回转换后的参数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月17日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 增加AMR-WB
*****************************************************************************/
NAS_OM_CURR_CODEC_TYPE_ENUM_U8  MN_CALL_ConvertMnCodecToOmCodec(
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType
)
{
    NAS_OM_CURR_CODEC_TYPE_ENUM_U8      enCurrentOmCodecType;

    switch ( enCodecType )
    {
        case MN_CALL_CODEC_TYPE_AMR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMR;
            break;

        case MN_CALL_CODEC_TYPE_EFR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_EFR;
            break;

        case MN_CALL_CODEC_TYPE_FR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_FR;
            break;

        case MN_CALL_CODEC_TYPE_HR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_HR;
            break;

        case MN_CALL_CODEC_TYPE_AMR2 :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMR2;
            break;

        case MN_CALL_CODEC_TYPE_AMRWB:
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMRWB;
            break;


        default:
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_BUTT;
            break;
    }

    return enCurrentOmCodecType;
}

/*****************************************************************************
 函 数 名  : MN_CALL_Convet
 功能描述  : 将GSM支持的语音版本转换为FR，HR，EFR，AMR等
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回转换后的参数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月9日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

  2.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 增加支持AMR-WB功能
*****************************************************************************/
NAS_OM_GSM_CODEC_CONFIG_ENUM_U8  MN_CALL_ConvertSpeechVers(VOS_VOID )
{
    VOS_UINT32                          i = 0;
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodecConfig;

    /*
    HR   ->  MN_CALL_BC_VAL_SPH_VER_HR_1  MN_CALL_BC_VAL_SPH_VER_HR_3
    FR   ->  MN_CALL_BC_VAL_SPH_VER_FR_1
    EFR  ->  MN_CALL_BC_VAL_SPH_VER_FR_2
    AMR-FR -> MN_CALL_BC_VAL_SPH_VER_FR_3
    */

    enGsmCodecConfig = 0;
    for ( i = 0 ; i < f_stMnCallSphVers.ucCnt ; i++ )
    {
        if ( (MN_CALL_BC_VAL_SPH_VER_HR_1 == f_stMnCallSphVers.aucVers[i])
          || (MN_CALL_BC_VAL_SPH_VER_HR_3 == f_stMnCallSphVers.aucVers[i]))
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_HR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_1  == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_FR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_2 == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_EFR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_5 == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_AMRWB;
        }
        else
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_AMR;
        }

    }

    return enGsmCodecConfig;
}

/*****************************************************************************
 函 数 名  : MN_CALL_BcIsValueSupported
 功能描述  : 判断某个BC字段是否支持某个特定的值
 输入参数  : enFldName - 字段名称
              ucValue   - 需要判断的值
 输出参数  : 无
 返 回 值  : VOS_TRUE表示支持，VOS_FALSE表示不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_CALL_BcIsValueSupported(
    MN_CALL_BC_FLD_NAME_ENUM            enFldName,
    VOS_UINT8                           ucValue
)
{
    VOS_UINT32 i;

    /* Modified by z00234330 for PCLINT清理, 2014-07-07, begin */
    if (MN_CALL_BC_NUM_OF_FIELD <= enFldName)
    /* Modified by z00234330 for PCLINT清理, 2014-07-07, end */
    {
        /* 字段名错误 */
        return VOS_FALSE;
    }

    if (0 == f_astMnCallBcFldInfo[enFldName].ucNumOfVals)
    {
        /* ucNumOfVals为0表示不需要对该字段进行检查，
           直接返回成功 */
        return VOS_TRUE;
    }

    /* 查看输入的ucValue是否在定义的值域中 */
    for (i=0; i<f_astMnCallBcFldInfo[enFldName].ucNumOfVals; i++)
    {
        if (ucValue == f_astMnCallBcFldInfo[enFldName].aucSupptVals[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

} /* MN_CALL_BcIsValueSupported */


/*****************************************************************************
 函 数 名  : MN_CALL_GetInfoFromBstSpeed
 功能描述  : 从CBST设置的Speed参数中获取信息
 输入参数  : enSpeed - 当前CBST设置的Speed参数
 输出参数  : pucUserRate - User rate
              pucFnur     - Fixed network user rate
              pucVarParm  - 可变参数，不同的返回值表示不同的含义
 返 回 值  : 可变参数的含义，详见MN_CALL_VAR_PARM_ENUM的定义
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年05月14日
    作    者   : h44270
    修改内容   : 问题单号:AT2D11670, 执行GCF 协议用例8.2.4.1.cs 由于NAS cc setup消息填充与脚本不匹配导致用例inconclusive
*****************************************************************************/
MN_CALL_VAR_PARM_ENUM  MN_CALL_GetInfoFromBstSpeed(
    MN_CALL_BST_SPEED_ENUM_UINT8        enSpeed,
    VOS_UINT8                           *pucUserRate,
    VOS_UINT8                           *pucFnur,
    VOS_UINT8                           *pucVarParm
)
{
    switch(enSpeed)
    {
    case MN_CALL_BST_SPD_300_V110:
    case MN_CALL_BST_SPD_300_V21:
        *pucUserRate = MN_CALL_BC_VAL_UR_300;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_1K2_V110:
    case MN_CALL_BST_SPD_1K2_V120:
    case MN_CALL_BST_SPD_1K2_V22:
        *pucUserRate = MN_CALL_BC_VAL_UR_1K2;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_2K4_V110:
    case MN_CALL_BST_SPD_2K4_V120:
    case MN_CALL_BST_SPD_2K4_V22BIS:
    case MN_CALL_BST_SPD_2K4_V26TER:
        *pucUserRate = MN_CALL_BC_VAL_UR_2K4;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_4K8_V110:
    case MN_CALL_BST_SPD_4K8_V120:
    case MN_CALL_BST_SPD_4K8_V32:
        *pucUserRate = MN_CALL_BC_VAL_UR_4K8;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_9K6_V110:
    case MN_CALL_BST_SPD_9K6_V120:
    case MN_CALL_BST_SPD_9K6_V32:
    case MN_CALL_BST_SPD_9K6_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_9K6;
        break;

    case MN_CALL_BST_SPD_14K4_V110:
    case MN_CALL_BST_SPD_14K4_V120:
    case MN_CALL_BST_SPD_14K4_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_14K4;
        break;

    case MN_CALL_BST_SPD_19K2_V110:
    case MN_CALL_BST_SPD_19K2_V120:
    case MN_CALL_BST_SPD_19K2_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_19K2;
        break;

    case MN_CALL_BST_SPD_28K8_V110:
    case MN_CALL_BST_SPD_28K8_V120:
    case MN_CALL_BST_SPD_28K8_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_28K8;
        break;

    case MN_CALL_BST_SPD_38K4_V110:
    case MN_CALL_BST_SPD_38K4_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_38K4;
        break;

    case MN_CALL_BST_SPD_48K_V110:
    case MN_CALL_BST_SPD_48K_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_48K;
        break;

    case MN_CALL_BST_SPD_56K_FTM:
    case MN_CALL_BST_SPD_56K_BT:
    case MN_CALL_BST_SPD_56K_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_56K;
        break;

    case MN_CALL_BST_SPD_64K_MULTI:
    case MN_CALL_BST_SPD_64K_FTM:
    case MN_CALL_BST_SPD_64K_BT:
    case MN_CALL_BST_SPD_64K_PIAFS:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_64K;
        break;

    case MN_CALL_BST_SPD_33K6_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_33K6;
        break;

    case MN_CALL_BST_SPD_32K_PIAFS:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_32K;
        break;

    case MN_CALL_BST_SPD_AUTOBAUD:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_28K8;
        break;

    default:
        return MN_CALL_VAR_PARM_ERROR;
    }

    if (MN_CALL_BST_SPD_AUTOBAUD == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_AUTOBAUD;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_300_V21 == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V21;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_1K2_V22 == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V22;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_2K4_V22BIS == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V22BIS;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_2K4_V26TER == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V26;
        return MN_CALL_VAR_PARM_MT;
    }
    else if ((MN_CALL_BST_SPD_4K8_V32 == enSpeed) ||
        (MN_CALL_BST_SPD_9K6_V32 == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V32;
        return MN_CALL_VAR_PARM_MT;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_9K6_V34) &&
        (enSpeed <= MN_CALL_BST_SPD_33K6_V34))
    {
        *pucVarParm = MN_CALL_BC_VAL_OMT_V34;
        return MN_CALL_VAR_PARM_OMT;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_1K2_V120) &&
        (enSpeed <= MN_CALL_BST_SPD_56K_V120))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_V120;
        return MN_CALL_VAR_PARM_ORA;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_300_V110) &&
        (enSpeed <= MN_CALL_BST_SPD_48K_V110))
    {
        *pucVarParm = MN_CALL_BC_VAL_RA_V110;
        return MN_CALL_VAR_PARM_RA;
    }
    else if ((MN_CALL_BST_SPD_56K_FTM == enSpeed) ||
        (MN_CALL_BST_SPD_64K_FTM == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_RA_X31;
        return MN_CALL_VAR_PARM_RA;
    }
    else if((MN_CALL_BST_SPD_56K_BT == enSpeed) ||
        (MN_CALL_BST_SPD_64K_BT == enSpeed))
    {
        return MN_CALL_VAR_PARM_NO_OUTPUT;
    }
    else if((MN_CALL_BST_SPD_32K_PIAFS == enSpeed) ||
        (MN_CALL_BST_SPD_64K_PIAFS == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_PIAFS;
        return MN_CALL_VAR_PARM_ORA;
    }
    #if 0
    else if((MN_CALL_BST_SPD_32K_PIAFS == enSpeed) ||
        (MN_CALL_BST_SPD_64K_PIAFS == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_PIAFS;
        return MN_CALL_VAR_PARM_ORA;
    }
    #endif
    else /* 64k multimedia */
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_H223_245;
        return MN_CALL_VAR_PARM_ORA;
    }

} /* MN_CALL_CcaGetInfoFromBstSpeed */
/*****************************************************************************
 函 数 名  : TAF_CALL_GetRealSpeechVers
 功能描述  : 获得真实的SpeechVers
 输入参数  : bIsSupportTTYModeFlg   --是否支持TTY MODE
 输出参数  : pstSpeechVers
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_GetRealSpeechVers(
    VOS_BOOL                            bIsSupportTTYModeFlg,
    MN_CALL_BC_SPEECH_VERS_STRU        *pstSpeechVers
)
{
    VOS_UINT32                          i;

    if (VOS_FALSE == bIsSupportTTYModeFlg)
    {
        PS_MEM_CPY(pstSpeechVers,&f_stMnCallSphVers,sizeof(MN_CALL_BC_SPEECH_VERS_STRU));
        return;
    }

    pstSpeechVers->ucCnt = 0;

    for (i = 0; i < f_stMnCallSphVers.ucCnt; i++)
    {
        if (MN_CALL_BC_VAL_SPH_VER_FR_5 == f_stMnCallSphVers.aucVers[i])
        {
            continue;
        }

        pstSpeechVers->aucVers[pstSpeechVers->ucCnt] = f_stMnCallSphVers.aucVers[i];
        pstSpeechVers->ucCnt++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_BuildBcForSpeech
 功能描述  : 构造语音业务的BC参数
 输入参数  : 无
 输出参数  : pstBc - 构造好的BC参数。
 返 回 值  : 构造的结果，VOS_OK表示构造成功，VOS_ERR表示构造失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加ALS多线路支持

  3.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : M项目TTY功能: 增加根据TTY MODE来置CTM标志位
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildBcForSpeech(
    NAS_CC_IE_BC_STRU                   *pstBc,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucExtVal;
    NAS_CC_IE_BC_OCTET3B_STRU           *pstOctet3x = VOS_NULL_PTR;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    VOS_BOOL                            bIsSupportTTYModeFlg;
    MN_CALL_BC_SPEECH_VERS_STRU         stSpeechVers;

    bIsSupportTTYModeFlg                = TAF_CALL_IsSupportTTYMode();
    PS_MEM_SET(&stSpeechVers, 0x00, sizeof(MN_CALL_BC_SPEECH_VERS_STRU));

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (f_stMnCallSphVers.ucCnt > MN_CALL_BC_MAX_SPH_VER_NUM)
    {
        MN_ERR_LOG("f_stMnCallSphVers.ucCnt > MN_CALL_BC_MAX_SPH_VER_NUM");
        return VOS_ERR;
    }

    /* 设置存在BC参数 */
    NAS_IE_SET_PRESENT(pstBc);

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /* 填写BC参数的Octet 3*/
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {

        if ( ( MN_CALL_ALS_LINE_NO_2 == MN_CALL_GetAlsLineInfo() )
          && ( MN_CALL_DIR_MT != enCallDir )
          && ( MN_CALL_TYPE_EMERGENCY != enCallType ) )
        {
            /*ITC需要根据当前使用的线路号进行赋值,线路1时ITC取值speech,线路2时取
              值Auxiliary speech*/
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_AUXILIARY_SPEECH;
        }
        else
        {
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_SPEECH;
        }
    }
    else
    {
        pstBc->Octet3.InfoTransCap = NAS_CC_ITC_SPEECH;
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    pstBc->Octet3.TransferMode = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_TRANS_MOD);
    pstBc->Octet3.CodingStd = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CODING_STD);
    pstBc->Octet3.RadioChReq = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_RCR);

    /* 支持TTY模式时，不支持AMRWB宽带语音 */
    TAF_CALL_GetRealSpeechVers(bIsSupportTTYModeFlg, &stSpeechVers);

    if (stSpeechVers.ucCnt > 0)
    {
        /* 需要在BC中列出speech version */
        pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_EXTEND;
        /* 这里没有设定EXT的宏定义，暂时用0，1来表示 */
        for (i=0; i < stSpeechVers.ucCnt; i++)
        {
            if (0 == i)
            {
                /* Octet3a的赋值 */
                pstBc->Octet3a.SpeechVer = stSpeechVers.aucVers[i];
                pstBc->Octet3a.Spare = 0;
                pstBc->Octet3a.Ctm = ((VOS_TRUE == bIsSupportTTYModeFlg) ? NAS_CC_CTM_TEXT_SUPPORTED : NAS_CC_CTM_TEXT_NOT_SUPPORTED);
                pstBc->Octet3a.Coding= 0;

                /* 根据有没有后续内容，设定ext的值 */
                ucExtVal = (stSpeechVers.ucCnt > 1) ? MN_CALL_BC_VAL_EXT_EXTEND : MN_CALL_BC_VAL_EXT_NO_EXT;
                pstBc->Octet3a.Ext = ucExtVal;
                pstOctet3x = (NAS_CC_IE_BC_OCTET3B_STRU*)&pstBc->Octet3a;
            }
            else
            {
                /* Octet3a之后Octet3x(x=b,c,d,e)的赋值，*/
                pstOctet3x = ((NAS_CC_IE_BC_OCTET3B_STRU*)(&pstBc->Octet3b) + i) - 1;
                pstOctet3x->SpeechVer = stSpeechVers.aucVers[i];
                pstOctet3x->Spare = 0;
                pstOctet3x->Coding= 0;

                /* 根据有没有后续内容，设定ext的值 */
                ucExtVal = (stSpeechVers.ucCnt == (i + 1)) ? MN_CALL_BC_VAL_EXT_NO_EXT : MN_CALL_BC_VAL_EXT_EXTEND ;
                pstOctet3x->Ext = ucExtVal;

            }
        }
        pstBc->LastOctOffset = ((VOS_UINT8)((VOS_UINT32)pstOctet3x - (VOS_UINT32)pstBc) - 1);
    }
    else
    {
        /* 不需要在BC中列出speech version */
        pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet3);
    }

    /* 语音业务的BC参数中没有4~7的可选字节 */
    /* 最后结构是结构体 */

    return VOS_OK;

} /* MN_CALL_BuildBcForSpeech */

/*****************************************************************************
 函 数 名  : MN_CALL_GetWaiurFromFunr
 功能描述  : 获取当前呼叫需要的空口用户速率；
 输入参数  : NULL
 输出参数  : NULL
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年7月10日
    作    者   : 傅映君62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_CALL_GetWaiurFromFunr(
    VOS_UINT32                          ulFnur
)
{
    VOS_UINT32                          ulWaiur;

    switch (ulFnur)
    {
    case MN_CALL_BC_VAL_FNUR_9K6:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_9K6;
        break;

    case MN_CALL_BC_VAL_FNUR_14K4:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_14K4;
        break;

    case MN_CALL_BC_VAL_FNUR_19K2:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_19K2;
        break;

    case MN_CALL_BC_VAL_FNUR_28K8:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_28K8;
        break;

    case MN_CALL_BC_VAL_FNUR_38K4:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    case MN_CALL_BC_VAL_FNUR_48K:/*GSM only*/
        ulWaiur = MN_CALL_BC_VAL_WAIUR_9K6;
        break;

    case MN_CALL_BC_VAL_FNUR_56K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_57K6;
        break;

    case MN_CALL_BC_VAL_FNUR_64K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_NA; /* !!Currently,inavailable; */
        break;

    case MN_CALL_BC_VAL_FNUR_33K6:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    case MN_CALL_BC_VAL_FNUR_32K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    default:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_NA;
        break;
    }

    return ulWaiur;
}



/*****************************************************************************
 函 数 名  : MN_CALL_BuildBcForData
 功能描述  : 构造数据业务的BC参数
 输入参数  : enTaMode - TA模式
              pstDataCfg - 承载业务类型
 输出参数  : pstBc - 构造好的BC参数。
 返 回 值  : 构造BC的数目，0表示构造失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012052100994,拨打可视电话，发给网侧的承载类型不对
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildBcForData(
    MN_CALL_TA_MODE_ENUM_UINT8          enTaMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc
)
{
    VOS_UINT8                           ucUserRate;
    VOS_UINT8                           ucFnur;
    VOS_UINT8                           ucVarParm;
    MN_CALL_VAR_PARM_ENUM               enVarParmType;

    /* Get information from +CBST parmameter */
    enVarParmType = MN_CALL_GetInfoFromBstSpeed
        (pstDataCfg->enSpeed, &ucUserRate, &ucFnur, &ucVarParm);

    if (MN_CALL_VAR_PARM_ERROR == enVarParmType)
    {
        MN_ERR_LOG("Failed to get info from +CBST parmameter.");
        return VOS_ERR;
    }

    /* ITC */
    if (MN_CALL_TA_MODE_FAX_CLASS1 == enTaMode)
    {
        pstBc->Octet3.InfoTransCap = NAS_CC_ITC_FAX;
    }
    else
    {
        if ((MN_CALL_CSD_NAME_ASYNC_UDI == pstDataCfg->enName)
         || (MN_CALL_CSD_NAME_SYNC_UDI == pstDataCfg->enName))
        {
            if ((MN_CALL_VAR_PARM_MT == enVarParmType)
             || (MN_CALL_VAR_PARM_OMT == enVarParmType))
            {
                pstBc->Octet3.InfoTransCap = NAS_CC_ITC_3D1K;
            }
            else
            {
                pstBc->Octet3.InfoTransCap = NAS_CC_ITC_UDI;
            }
        }
        else
        {
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_OTHER;
        }
    }
    pstBc->Octet3.TransferMode = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_TRANS_MOD);
    pstBc->Octet3.CodingStd = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CODING_STD);
    pstBc->Octet3.RadioChReq = NAS_CC_RADIO_CH_FULL_RATE;
    /* No Octet 3a for data call */
    pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* Octet 4 */
    pstBc->Octet4.Establishment   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ESTABLI);
    pstBc->Octet4.Nirr      = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIRR);
    pstBc->Octet4.Configuation  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CONFIGUR);
    pstBc->Octet4.DuplexMode  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_DUPL_MODE);
    if (MN_CALL_CSD_CE_NT == pstDataCfg->enConnElem)
    {
        pstBc->Octet4.Structure = NAS_CC_STRUCTURE_STRUCTERD;
    }
    else
    {
        pstBc->Octet4.Structure = NAS_CC_STRUCTURE_UNSTRUCTURED;
    }
    pstBc->Octet4.Compression  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_COMPRESS);
    pstBc->Octet4.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* Octet 5 */
    pstBc->Octet5.SigAccProtocol   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_SIGNAL);
    if (MN_CALL_VAR_PARM_RA == enVarParmType)
    {
        pstBc->Octet5.RateAdaption = ucVarParm;
    }
    else if (MN_CALL_VAR_PARM_ORA == enVarParmType)
    {
        pstBc->Octet5.RateAdaption = MN_CALL_BC_VAL_RA_OTHER;
    }
    else
    {
        pstBc->Octet5.RateAdaption = MN_CALL_BC_VAL_RA_NO;
    }
    pstBc->Octet5.AccessId = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ACCESS_ID);

    /* If RA is other RA or ITC is other ITC, Octet 5a shall be included */
    if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
     || (NAS_CC_ITC_OTHER == pstBc->Octet3.InfoTransCap))
    {
        pstBc->Octet5.Ext = MN_CALL_BC_VAL_EXT_EXTEND;
        pstBc->Octet5a.OtherITC = NAS_CC_OTHER_ITC_RDI;
        if(MN_CALL_VAR_PARM_ORA == enVarParmType)
        {
            pstBc->Octet5a.OtherRA = ucVarParm;
        }
        else
        {
            pstBc->Octet5a.OtherRA = NAS_CC_OTHER_RA_V120;
        }
        pstBc->Octet5a.Spare = 0;

        /* If ORA is V.120, Octet 5b shall be included */
        if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
         && (NAS_CC_OTHER_RA_V120 == pstBc->Octet5a.OtherRA))
        {
            pstBc->Octet5a.Ext          = MN_CALL_BC_VAL_EXT_EXTEND;

            pstBc->Octet5b.Spare        = 0;
            pstBc->Octet5b.InOutBandNeg = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_INB_NEG);
            pstBc->Octet5b.Assignore    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ASSIGNOR);
            pstBc->Octet5b.LLI          = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LLI);
            pstBc->Octet5b.OpMode       = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_MODE);
            pstBc->Octet5b.MultiFrame   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_MULTI_FRAME);
            pstBc->Octet5b.Header       = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_HDR_NO_HDR);
            pstBc->Octet5b.Ext        = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
        else
        {
            pstBc->Octet5a.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
    }
    else
    {
        pstBc->Octet5.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }

    /* Octet 6 */
    if ((MN_CALL_CSD_NAME_ASYNC_UDI == pstDataCfg->enName)
     || (MN_CALL_CSD_NAME_ASYNC_RDI == pstDataCfg->enName))
    {
        pstBc->Octet6.SyncAsync = NAS_CC_ASYNC;
    }
    else if ((MN_CALL_CSD_NAME_SYNC_UDI == pstDataCfg->enName)
          || (MN_CALL_CSD_NAME_SYNC_RDI == pstDataCfg->enName))
    {
        pstBc->Octet6.SyncAsync = NAS_CC_SYNC;
    }
    else
    {
        MN_ERR_LOG("Bad name parmameter of CBST setting.");
        return VOS_ERR;
    }
    pstBc->Octet6.UserInfoL1 = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL1P);
    pstBc->Octet6.Layer1Id   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER1_ID);
    pstBc->Octet6.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6a */
    pstBc->Octet6a.UserRate         = ucUserRate;
    pstBc->Octet6a.NumOfDataBits    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT);
    pstBc->Octet6a.Negotiation      = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NEGOTIATION);
    pstBc->Octet6a.NumOfStopBits    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT);
    pstBc->Octet6a.Ext              = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6b */
    pstBc->Octet6b.ParityInfo   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY);
    pstBc->Octet6b.RxNIC        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIC_ON_RX);
    pstBc->Octet6b.TxNIC        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIC_ON_TX);
    if (NAS_CC_USER_RATE_9600 == pstBc->Octet6a.UserRate)
    {
        pstBc->Octet6b.InterRate = NAS_CC_INTER_RATE_16K;
    }
    else
    {
        pstBc->Octet6b.InterRate = NAS_CC_INTER_RATE_8K;
    }
    pstBc->Octet6b.Ext       = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6c */
    /* Modem type */
    if (MN_CALL_VAR_PARM_MT == enVarParmType)
    {
        pstBc->Octet6c.ModemType = ucVarParm;
    }
    else if(MN_CALL_VAR_PARM_OMT == enVarParmType)
    {
        /* When the MT indicates "autobauding" , "modem for
        undefined interface" or "none", the OMT shall be set
        to "no other modem type". Any other values of the MT
        is overridden by the OMT value. (27.001) */
        pstBc->Octet6c.ModemType = MN_CALL_BC_VAL_MT_V21;
    }
    else
    {
        pstBc->Octet6c.ModemType = MN_CALL_BC_VAL_MT_NONE;
    }

    /* Connection element */
    if (MN_CALL_CSD_CE_T == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_T;
    }
    else if(MN_CALL_CSD_CE_NT == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_NT;
    }
    else if(MN_CALL_CSD_CE_BOTH_T == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_BOTH_T;
    }
    else
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_BOTH_NT;
    }
    pstBc->Octet6c.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6d */
    pstBc->Octet6d.FNUR = ucFnur;
    if (MN_CALL_VAR_PARM_OMT == enVarParmType)
    {
        pstBc->Octet6d.OtherModemType = ucVarParm;
    }
    else
    {
        pstBc->Octet6d.OtherModemType = NAS_CC_OTHER_MODEM_NONE;
    }
    pstBc->Octet6d.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* 如果业务是Fax，Modem type和Other modem type都置为none */
    if (NAS_CC_ITC_FAX == pstBc->Octet3.InfoTransCap)
    {
        pstBc->Octet6c.ModemType      = MN_CALL_BC_VAL_MT_NONE;
        pstBc->Octet6d.OtherModemType = MN_CALL_BC_VAL_OMT_NONE;
    }

    /* Octet 6e */
    pstBc->Octet6e.MaxTchNum = NAS_CC_MAX_1TCH;
    pstBc->Octet6e.TchF96    = NAS_CC_TCH_F9_6_NOT_ACCEPTABLE;
    pstBc->Octet6e.TchF144   = NAS_CC_TCH_F14_4_NOT_ACCEPTABLE;
    pstBc->Octet6e.Ext       = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6f */
    if (MN_CALL_CSD_CE_T == pstDataCfg->enConnElem)
    {
        /* This parameter shall be included only for
        non-transparent services and in case the
        parameter 'fixed network user rate' is included. (27.001) */
        pstBc->Octet6f.WAIUR = NAS_CC_WAIUR_NONE;
    }
    else
    {
        /* This parameter has to be included if EDGE channel coding(s)
        are included in Acceptable channel codings. (27.001) */

        /* 目前只支持一个TCH，该参数填暂设为Not applicable */
/*->f62575 for CCA*/
        if ((MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6c.Ext)
         && (NAS_CC_FNUR_NONE != pstBc->Octet6d.FNUR))
        {
            /*lint -e522*/
            pstBc->Octet6f.WAIUR = MN_CALL_GetWaiurFromFunr((pstBc->Octet6d.FNUR));
            /*lint +e522*/
        }
        else
        {
            pstBc->Octet6f.WAIUR = NAS_CC_WAIUR_9600;
        }
    }
/*<-f62575 for CCA*/

    pstBc->Octet6f.UIMI = NAS_CC_UIMI_NONE;
    /* Octet 6g暂不填写, only for EDGE */
    pstBc->Octet6f.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* The MS is not allowed to indicate support of both transparent
    and non transparent, if the MS also requests out-band flow control,
    i.e. it does not indicate a layer 2 protocol. (27.001)*/
    if (NAS_CC_CONNECTION_T != pstBc->Octet6c.ConnElement)
    {
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet7);
        pstBc->Octet7.UserInfoL2 = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
        pstBc->Octet7.Layer2Id = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
        pstBc->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }
    else
    {
        /* 不携带octet 7，表明使用ITU-T V.42 out-band流控方式 */
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet6f);
    }

    NAS_IE_SET_OCTET(pstBc, IsExist, 1);

    return VOS_OK;

} /* MN_CALL_BuildBcForData */


/*****************************************************************************
 函 数 名  : MN_CALL_BuildBcOfSetup
 功能描述  : 构造SETUP消息中的BC参数
 输入参数  : enCallType - 本次呼叫的呼叫类型。如果呼叫模式不为single，则该参数为
                       第一个业务的类型。
              enCallMode - 本次呼叫的呼叫模式
              enTaMode   - 本次呼叫的TA模式，只对数据呼叫有效。
              pstBsType  - 本次呼叫的承载业务类型，只对数据呼叫有效。
 输出参数  : pstBc1 - 第一个业务的承载能力。
              pstBc2 - 第二个业务的承载能力，当呼叫模式不为single时，将输出该参数。
 返 回 值  : 构造的BC参数的个数，可能的值为0、1、2，0表示构造失败。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012052100994,拨打可视电话，发给网侧的承载类型不对
  3.日    期   : 2014年04月15日
    作    者   : y00245242
    修改内容   : 为eCall feature功能修改
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildBcOfSetup(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2
)
{
    VOS_UINT32                          ulBcCnt = 0;
    VOS_UINT32                          ulRes;

    /* 构造第一个BC参数 */
    switch(enCallType)
    {
    case MN_CALL_TYPE_VOICE:
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-13, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_TYPE_TEST:
    case MN_CALL_TYPE_RECFGURATION:
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-13, end */
        /* 构造语音呼叫的BC参数 */
        ulRes = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MO,MN_CALL_TYPE_VOICE);
        break;

    case MN_CALL_TYPE_EMERGENCY:
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-13, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_TYPE_MIEC:
    case MN_CALL_TYPE_AIEC:
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-13, end */
        /* 构造紧急呼叫的BC参数 */
        ulRes = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MO,MN_CALL_TYPE_EMERGENCY);
        break;

    case MN_CALL_TYPE_CS_DATA:
    case MN_CALL_TYPE_VIDEO:
    case MN_CALL_TYPE_VIDEO_TX:
    case MN_CALL_TYPE_VIDEO_RX:
        /* 构造数据的BC参数 */
        ulRes = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_DATA, pstDataCfg, pstBc1);
        break;

    case MN_CALL_TYPE_FAX:
        /* 构造传真的BC参数 */
        ulRes = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1);
        break;
    /*遗留 MN_CALL_TYPE_VIDEO 该如何处理*/
    default:
        ulRes = VOS_ERR;
        break;
    }

    if (ulRes != VOS_OK)
    {
        return 0;
    }

    ulBcCnt++;

    if (MN_CALL_MODE_AVF == enCallMode)
    {
        /* 构造第二个BC参数 */
        if (MN_CALL_TYPE_VOICE == enCallType)
        {
            /* 第一个构造的是语音参数，现在构造FAX的BC参数 */
            ulRes = MN_CALL_BuildBcForData(MN_CALL_TYPE_FAX, pstDataCfg, pstBc2);
        }
        else
        {
            /* 第一个构造的是数据参数，现在构造语音呼叫的BC参数 */
            ulRes = MN_CALL_BuildBcForSpeech(pstBc2,MN_CALL_DIR_MO,MN_CALL_TYPE_VOICE);
        }

        if (ulRes != VOS_OK)
        {
            return 0;
        }

        ulBcCnt++;
    }

    return ulBcCnt;

} /* MN_CALL_BuildBcOfSetup */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChkOct3
 功能描述  : 对BC参数的Octet3, 3a及3b etc进行兼容性检查
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct3(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    /* 检查Octet 3 */
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ITC, pstBc->Octet3.InfoTransCap);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_TRANS_MOD, pstBc->Octet3.TransferMode);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CODING_STD, pstBc->Octet3.CodingStd);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_RCR, pstBc->Octet3.RadioChReq);

    /* 根据协议，忽略Octet 3a */

    /* 检查通过 */
    return VOS_OK;

} /* MN_CALL_BcCompChkOct3 */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChkOct4
 功能描述  : 对BC参数的Octet4进行兼容性检查
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct4(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ESTABLI, pstBc->Octet4.Establishment);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIRR, pstBc->Octet4.Nirr);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CONFIGUR, pstBc->Octet4.Configuation);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_DUPL_MODE, pstBc->Octet4.DuplexMode);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_STRUCTURE, pstBc->Octet4.Structure);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_COMPRESS, pstBc->Octet4.Compression);

    /* Octet 4的Ext字段肯定为1 */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet4.Ext)
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

} /* MN_CALL_BcCompChkOct4 */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChkOct5
 功能描述  : 对BC参数的Octet5, 5a, 5b进行兼容性检查
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct5(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_SIGNAL, pstBc->Octet5.SigAccProtocol);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_RA, pstBc->Octet5.RateAdaption);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ACCESS_ID, pstBc->Octet5.AccessId);

    /* 如果Octet 5a存在, 需要检查5a */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet5.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ORA, pstBc->Octet5a.OtherRA);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_OTHER_ITC, pstBc->Octet5a.OtherITC);
    }
    else
    {
        /* 如果ITC或RA为Other，则Octet 5a不存在将导致检查失败 */
        if ((NAS_CC_ITC_OTHER== pstBc->Octet3.InfoTransCap)
         || (NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption))
        {
            return VOS_ERR;
        }
        else
        {
            /* 检查结束，返回成功 */
            return VOS_OK;
        }
    }

    /* 如果Octet 5b存在, 需要检查5b */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet5a.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_INB_NEG, pstBc->Octet5b.InOutBandNeg);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ASSIGNOR, pstBc->Octet5b.Assignore);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LLI, pstBc->Octet5b.LLI);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MODE, pstBc->Octet5b.OpMode);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MULTI_FRAME, pstBc->Octet5b.MultiFrame);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_HDR_NO_HDR, pstBc->Octet5b.Header);
    }
    else
    {
        /* 如果RA为V120，则Octet 5b不存在将导致检查失败 */
        if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
         && (NAS_CC_OTHER_RA_V120 == pstBc->Octet5a.OtherRA))
        {
            return VOS_ERR;
        }
        else
        {
            /* 检查结束，返回成功 */
            return VOS_OK;
        }
    }

    return VOS_OK;

} /* MN_CALL_BcCompChkOct5 */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChkOct6
 功能描述  : 对BC参数的Octet6, 6a, 6b, 6c, 6d, 6e, 6f, 6g进行兼容性检查
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct6(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_SYNC_ASYNC, pstBc->Octet6.SyncAsync);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIL1P, pstBc->Octet6.UserInfoL1);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LAYER1_ID, pstBc->Octet6.Layer1Id);

    /* 如果Octet 6a存在, 需要检查6a */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_USER_RATE, pstBc->Octet6a.UserRate);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_N_DATA_BIT, pstBc->Octet6a.NumOfDataBits);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NEGOTIATION, pstBc->Octet6a.Negotiation);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_N_STOP_BIT, pstBc->Octet6a.NumOfStopBits);
    }
    else
    {
        /* 如果Octet 6存在，则Octet 6a必须存在 */
        return VOS_ERR;
    }

    /* 如果Octet 6b存在, 需要检查6b */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6a.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_PARITY, pstBc->Octet6b.ParityInfo);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIC_ON_RX, pstBc->Octet6b.RxNIC);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIC_ON_TX, pstBc->Octet6b.TxNIC);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_INTMD_RATE, pstBc->Octet6b.InterRate);
    }
    else
    {
        /* 如果Octet 6存在，则Octet 6b必须存在 */
        return VOS_ERR;
    }

    /* 如果Octet 6c存在, 需要检查6c */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6b.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MODEM_TYPE, pstBc->Octet6c.ModemType);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CE, pstBc->Octet6c.ConnElement);

        /* 同步非透明这种模式是明确不支持的 */
        if ((NAS_CC_CONNECTION_NT == pstBc->Octet6c.ConnElement)
         && (NAS_CC_SYNC == pstBc->Octet6.SyncAsync))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* 如果Octet 6存在，则Octet 6c必须存在 */
        return VOS_ERR;
    }

    /* 如果Octet 6d存在, 需要检查6d */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6c.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_FNUR, pstBc->Octet6d.FNUR);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_OMT, pstBc->Octet6d.OtherModemType);
    }
    else
    {
        /* 检查结束，返回成功 */
        return VOS_OK;
    }

    /* 如果Octet 6e存在, 需要检查6e */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6d.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MAX_TCH, pstBc->Octet6e.MaxTchNum);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ACC, NAS_IE_GET_OCTET(pstBc,Octet6e));
    }
    else
    {
        /* 检查结束，返回成功 */
        return VOS_OK;
    }

    /* 如果Octet 6f存在, 需要检查6f */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6e.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_WAIUR, pstBc->Octet6f.WAIUR);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIMI, pstBc->Octet6f.UIMI);
    }
    else
    {
        /* 检查结束，返回成功 */
        return VOS_OK;
    }

    /* 如果Octet 6g存在, 需要检查6g */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6f.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ASYM_IND, pstBc->Octet6g.CCAI);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_EXT_ACC, NAS_IE_GET_OCTET(pstBc,Octet6g));
    }
    else
    {
        /* 检查结束，返回成功 */
        return VOS_OK;
    }

    return VOS_OK;

} /* MN_CALL_BcCompChkOct6 */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChkOct7
 功能描述  : 对BC参数的Octet7进行兼容性检查
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct7(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIL2P, pstBc->Octet7.UserInfoL2);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LAYER2_ID, pstBc->Octet7.Layer2Id);
    /* Octet 7的Ext字段肯定为1 */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet7.Ext)
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

} /* MN_CALL_BcCompChkOct7 */


/*****************************************************************************
 函 数 名  : MN_CALL_BcCompChk
 功能描述  : 对BC参数进行兼容性检查。
 输入参数  : pstBc - 要检查的BC参数
 输出参数  : 无
 返 回 值  : VOS_OK  - 兼容性检查通过
             VOS_ERR - 兼容性检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 支持ALS多线路呼叫
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChk(
    const NAS_CC_IE_BC_STRU            *pstBc
)
{
    if (VOS_NULL_PTR == pstBc)
    {
        return VOS_ERR;
    }

    /* 检查Octet3, 3a, 3b etc */
    if (VOS_ERR == MN_CALL_BcCompChkOct3(pstBc))
    {
        return VOS_ERR;
    }

    /* 检查Octet 4 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet4) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct4(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* 对于非语音呼叫，Octet 4不存在将导致检查失败 */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH) )
        {
            return VOS_ERR;
        }
    }

    /* 检查Octet 5 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet5) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct5(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* 对于非语音呼叫，Octet 5不存在将导致检查失败 */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH))
        {
            return VOS_ERR;
        }
    }

    /* 检查Octet 6 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet6) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct6(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* 对于非语音呼叫，Octet 6不存在将导致检查失败 */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH))
        {
            return VOS_ERR;
        }
    }

    /* 检查Octet 7 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet7) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct7(pstBc))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;

} /* MN_CALL_BcCompChk */

/*****************************************************************************
 函 数 名  : MN_CALL_NegotSpeechBcForCallConf
 功能描述  : 协商语音呼叫SETUP消息中的BC参数，得到CALL CONFIRM消息需要的BC参数。
 输入参数  : pstBcOfSetup - 当前设置的承载业务类型，当SETUP消息的呼叫类型为VOICE时该参数将被忽略。
             pstBcOfConf     - SETUP消息中的BC参数
 输出参数  : pstBcOfConf     - 协商后的BC参数
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月29日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2015年2月15日
    作    者   : w00316404
    修改内容   : 支持TTY MODE的情况下，修改CTM标志位
*****************************************************************************/
VOS_VOID  MN_CALL_NegotSpeechBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucExtVal;
    NAS_CC_IE_BC_OCTET3B_STRU           *pstOctet3x;
    VOS_BOOL                            bIsSupportTTYModeFlg;
    MN_CALL_BC_SPEECH_VERS_STRU         stSpeechVers;

    bIsSupportTTYModeFlg                = TAF_CALL_IsSupportTTYMode();
    PS_MEM_SET(&stSpeechVers, 0x00, sizeof(MN_CALL_BC_SPEECH_VERS_STRU));

    pstOctet3x = VOS_NULL_PTR;
    /* 在BC参数中填入支持的speech version */

    /* 支持TTY模式时，不支持AMRWB宽带语音 */
    TAF_CALL_GetRealSpeechVers(bIsSupportTTYModeFlg, &stSpeechVers);

    if (stSpeechVers.ucCnt > 0)
    {
        /* 需要在BC中列出speech version */
        pstBcOfConf->Octet3.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

        for (i=0; i<stSpeechVers.ucCnt; i++)
        {
            /* 支持TTY模式时，不支持AMRWB宽带语音 */
            if ( (VOS_TRUE == bIsSupportTTYModeFlg)
              && (stSpeechVers.aucVers[i] == MN_CALL_BC_VAL_SPH_VER_FR_5) )
            {
                continue;
            }
            if (0 == i )
            {
                /* Octet3a的赋值 */
                pstBcOfConf->Octet3a.SpeechVer = stSpeechVers.aucVers[i];
                pstBcOfConf->Octet3a.Spare = 0;
                pstBcOfConf->Octet3a.Ctm = ((VOS_TRUE == bIsSupportTTYModeFlg) ? NAS_CC_CTM_TEXT_SUPPORTED : NAS_CC_CTM_TEXT_NOT_SUPPORTED);
                pstBcOfConf->Octet3a.Coding = 0;

                /* 根据有没有后续内容，设定ext的值 */
                ucExtVal = (stSpeechVers.ucCnt > 1)?
                            MN_CALL_BC_VAL_EXT_EXTEND: MN_CALL_BC_VAL_EXT_NO_EXT;
                pstBcOfConf->Octet3a.Ext = ucExtVal;
            }
            else
            {
                /* Octet3a之后Octet3x(x=b,c,d,e)的赋值，*/
                pstOctet3x = ((NAS_CC_IE_BC_OCTET3B_STRU*)(&pstBcOfConf->Octet3b) + i) - 1;
                pstOctet3x->SpeechVer = stSpeechVers.aucVers[i];
                pstOctet3x->Spare = 0;
                pstOctet3x->Coding = 0;

                /* 根据有没有后续内容，设定ext的值 */
                ucExtVal = (stSpeechVers.ucCnt == (i + 1))?
                            MN_CALL_BC_VAL_EXT_NO_EXT: MN_CALL_BC_VAL_EXT_EXTEND;
                pstOctet3x->Ext = ucExtVal;

            }
        }
        pstBcOfConf->LastOctOffset = ((VOS_UINT8)((VOS_UINT32)pstOctet3x
                    - (VOS_UINT32)pstBcOfConf) - 1);
    }
    else
    {
        /* 不需要在BC中列出speech version */
        pstBcOfConf->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }

}

/*****************************************************************************
 函 数 名  : MN_CALL_NegotUIL2PForCallConf
 功能描述  : 协商数据呼叫SETUP消息中的BC参数中UIL2P，得到CALL CONFIRM消息需要的BC参数中UIL2P。
 输入参数  : pstBcOfSetup - 当前设置的承载业务类型，当SETUP消息的呼叫类型为VOICE时该参数将被忽略。
             pstBcOfConf     - SETUP消息中的BC参数
 输出参数  : pstBcOfConf     - 协商后的BC参数
 返 回 值  : VOS_TRUE 表示CALL CONF消息中需要携带该BC参数；
             VOS_FALSE 表示CALL CONF消息中不需要携带该BC参数。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月29日
    作    者   : 周君 40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_NegotUIL2PForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          ulIncBc;

    ulIncBc = VOS_FALSE;
    /* 协商UIL2P */
    if (NAS_CC_CONNECTION_T == pstBcOfSetup->Octet6c.ConnElement)
    {
        /* 不携带octet 7，表明使用ITU-T V.42 out-band流控方式 */
        if (pstBcOfSetup->LastOctOffset >
              ((VOS_UINT32)&pstBcOfSetup->Octet7 - (VOS_UINT32)&pstBcOfSetup->Octet3))
        {
            NAS_IE_SET_LAST_OCTET_OFFSET(pstBcOfConf, Octet6);
            ulIncBc = VOS_TRUE;
        }
        else
        {
            ulIncBc = VOS_TRUE;
        }
    }
    else
    {
        if (pstBcOfSetup->LastOctOffset <
              ((VOS_UINT32)&pstBcOfSetup->Octet7 - (VOS_UINT32)&pstBcOfSetup->Octet3))
        {
            NAS_IE_SET_LAST_OCTET_OFFSET(pstBcOfConf, Octet7);
            pstBcOfConf->Octet7.UserInfoL2
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
            pstBcOfConf->Octet7.Layer2Id
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
            pstBcOfConf->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
            ulIncBc = VOS_TRUE;
        }
        else
        {
            if(NAS_CC_L2_PROTOCOL_ISO6429 != pstBcOfSetup->Octet7.UserInfoL2)
            {
                pstBcOfConf->Octet7.UserInfoL2
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
                pstBcOfConf->Octet7.Layer2Id
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
                pstBcOfConf->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
                ulIncBc = VOS_TRUE;
            }
        }
    }
    return ulIncBc;
}

/*****************************************************************************
 函 数 名  : MN_CALL_NegotBcForCallConf
 功能描述  : 协商SETUP消息中的BC参数，得到CALL CONFIRM消息需要的BC参数。
 输入参数  : pstBcOfSetup - 当前设置的承载业务类型，当SETUP消息的呼叫类型为VOICE时该参数将被忽略。
              pstBcOfConf     - SETUP消息中的BC参数
 输出参数  : pstBcOfConf     - 协商后的BC参数
 返 回 值  : VOS_TRUE 表示CALL CONF消息中需要携带该BC参数；
             VOS_FALSE 表示CALL CONF消息中不需要携带该BC参数。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : R7协议升级修改函数圈复杂度
*****************************************************************************/
VOS_UINT32  MN_CALL_NegotBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          ulIncBc;

    PS_MEM_CPY(pstBcOfConf, pstBcOfSetup, sizeof(NAS_CC_IE_BC_STRU));

    /* 协商语音业务的BC参数 */
    if ( (MN_CALL_BC_VAL_ITC_SPEECH == pstBcOfSetup->Octet3.InfoTransCap)
       ||(MN_CALL_BC_VAL_ITC_AUX_SPEECH == pstBcOfSetup->Octet3.InfoTransCap) )
    {
        /* BC shall be included if the "radio channel requirement" of
        the MS is other than "full rate support only mobile station" */
        pstBcOfConf->Octet3.RadioChReq = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_RCR);
        MN_CALL_NegotSpeechBcForCallConf(pstBcOfSetup,pstBcOfConf);
        return VOS_TRUE;
    }

    /* 协商数据业务的BC参数 */
    ulIncBc = VOS_FALSE;
    /* 协商Number of data bits */
    if (pstBcOfSetup->Octet6a.NumOfDataBits != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT))
    {
        pstBcOfConf->Octet6a.NumOfDataBits = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT);
        ulIncBc = VOS_TRUE;
    }

    /* 协商Number of stop bits */
    if (pstBcOfSetup->Octet6a.NumOfStopBits != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT))
    {
        pstBcOfConf->Octet6a.NumOfStopBits = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT);
        ulIncBc = VOS_TRUE;
    }

    /* 协商Parity */
    if (pstBcOfSetup->Octet6b.ParityInfo != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY))
    {
        pstBcOfConf->Octet6b.ParityInfo = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY);
        ulIncBc = VOS_TRUE;
    }

    /* 协商Connection element，此处和原来的方案不同 */
    if ((NAS_CC_CONNECTION_BOTH_T == pstBcOfSetup->Octet6c.ConnElement)
     || (NAS_CC_CONNECTION_T == pstBcOfSetup->Octet6c.ConnElement))
    {

        pstBcOfConf->Octet6c.ConnElement = NAS_CC_CONNECTION_T;
        pstBcOfConf->Octet4.Structure = NAS_CC_STRUCTURE_UNSTRUCTURED;
        ulIncBc = VOS_TRUE;
    }
    else
    {
        pstBcOfConf->Octet6c.ConnElement = NAS_CC_CONNECTION_NT;
        pstBcOfConf->Octet4.Structure = NAS_CC_STRUCTURE_STRUCTERD;
    }

    /* 协商Intermediate rate */
    if (NAS_CC_NIRR_ENABLE == pstBcOfSetup->Octet4.Nirr)
    {
        pstBcOfConf->Octet4.Nirr = NAS_CC_NIRR_DISABLE;
        pstBcOfConf->Octet6b.InterRate = NAS_CC_INTER_RATE_16K;
        ulIncBc = VOS_TRUE;
    }

    /* 协商Modem type ... 暂不协商 */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6c.Ext)
    {
        /* BC shall be included if bc received in the SETUP message
        included the "fixed network user rate" parameter. (24.008) */
        ulIncBc = VOS_TRUE;

        /* 通知网侧我们支持9.6和14.4两种编码方式，最多1个TCH */
        pstBcOfConf->Octet6e.TchF48    = NAS_CC_TCH_F4_8_NOT_ACCEPTABLE;
        pstBcOfConf->Octet6e.TchF96    = NAS_CC_TCH_F9_6_ACCEPTABLE;
        pstBcOfConf->Octet6e.TchF144   = NAS_CC_TCH_F9_6_ACCEPTABLE;
        pstBcOfConf->Octet6e.MaxTchNum = NAS_CC_MAX_1TCH;

        /* UIMI shall be included by the MS only in case
        it was received from the network. (27.001)*/
        if ((MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6d.Ext)
         && (MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6e.Ext))
        {
            pstBcOfConf->Octet6f.UIMI     = NAS_CC_UIMI_NONE;
            pstBcOfConf->Octet6f.WAIUR  = MN_CALL_BC_VAL_WAIUR_NA;
            pstBcOfConf->Octet6f.Ext    = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
        else
        {
            pstBcOfConf->Octet6d.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
            pstBcOfConf->Octet6e.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
    }

    ulIncBc = MN_CALL_NegotUIL2PForCallConf(pstBcOfSetup,pstBcOfConf);

    return ulIncBc;

} /* MN_CALL_NegotBcForCallConf */


/*****************************************************************************
 函 数 名  : MN_CALL_BuildBcForSns
 功能描述  : 构造单号码方案的BC参数
 输入参数  : enSnsMode - 当前设置的单号码方案模式
              pstBsType - 本次呼叫的承载业务类型，当单号码方案模式为VOICE时忽略该参数。
 输出参数  : pstBc1 - 第一个业务的BC参数
              pstBc2 - 第二个业务的BC参数
 返 回 值  : 构造的BC参数的个数，可能的值为0、1、2，0表示构造失败。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012052100994,拨打可视电话，发给网侧的承载类型不对
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildBcForSns(
    MN_CALL_SNS_MODE_ENUM_UINT8         enSnsMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2,
    VOS_UINT8                           *pucBcRepInd
)
{
    VOS_UINT32                          ulRslt1,ulRslt2;
    /* -> f62575 CCA */
    *pucBcRepInd = 0;
    /* <- f62575 CCA */
    switch(enSnsMode)
    {
    case MN_CALL_SNS_MODE_VOICE:
        if (VOS_OK == MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_ALTER_VF_V_FIRST:
        ulRslt1 = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE);
        ulRslt2 = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc2);
        if ((VOS_OK == ulRslt1) && (VOS_OK == ulRslt2))
        {
            *pucBcRepInd = MN_CALL_REP_IND_ALTER;
            return 2;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_FAX:
        if (VOS_OK == MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_DATA:
        if (VOS_OK == MN_CALL_BuildBcForData(MN_CALL_TA_MODE_DATA, pstDataCfg, pstBc1))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_ALTER_VF_F_FIRST:
        ulRslt1 = MN_CALL_BuildBcForSpeech(pstBc2,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE);
        ulRslt2 = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1);
        if ((VOS_OK == ulRslt1) && (VOS_OK == ulRslt2))
        {
            /* -> f62575 CCA */
            *pucBcRepInd = MN_CALL_REP_IND_ALTER;
            /* <- f62575 CCA */
            return 2;
        }
        else
        {
            return 0;
        }

    default:
        return 0;
    }

} /* MN_CALL_BuildBcForSns */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */


/*****************************************************************************
 函 数 名  : MN_CALL_FillGsmSupCodecList
 功能描述  : 填写GSM支持的codec list
 输入参数  : 无
 输出参数  : punCodecList :当前GSM支持的codec类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 新生成函数

  2.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : M项目TTY功能: 增加根据TTY MODE来置CTM标志位
*****************************************************************************/
VOS_VOID  MN_CALL_FillGsmSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < f_stMnCallSphVers.ucCnt ; i++ )
    {
        switch ( f_stMnCallSphVers.aucVers[i])
        {
            case MN_CALL_BC_VAL_SPH_VER_FR_1 :
                punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_2 :
                punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_3 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_HR_1 :
                punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_HR_3 :
                punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_5 :
                if (VOS_FALSE == TAF_CALL_IsSupportTTYMode())
                {
                    punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
                }
                break;
            default:
                MN_INFO_LOG("MN_CALL_FillGsmSupCodecList: invalid speech version");
                break;
        }
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_FillUmtsSupCodecList
 功能描述  : 填写UMTS支持的codec list
 输入参数  : 无
 输出参数  : punCodecList :当前UMTS支持的codec类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : DTS2012101809567,语音支持的能力需要区分G和W模式
  3.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : M项目TTY功能: 增加根据TTY MODE来置CTM标志位
*****************************************************************************/
VOS_VOID  MN_CALL_FillUmtsSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < f_stMnCallUmtsCodecTypes.ucCnt ; i++ )
    {
        switch ( f_stMnCallUmtsCodecTypes.aucUmtsCodec[i])
        {
            case MN_CALL_UMTS_CODEC_TYPE_AMR :
                punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
                break;

            case MN_CALL_UMTS_CODEC_TYPE_AMR2 :
                punCodecList->stSupportCodec.CodecType_UMTSAMR2     = VOS_TRUE;
                break;

            case MN_CALL_UMTS_CODEC_TYPE_AMRWB :
                if (VOS_FALSE == TAF_CALL_IsSupportTTYMode())
                {
                    punCodecList->stSupportCodec.CodecType_UMTSAMRWB   = VOS_TRUE;
                }
                break;
            default:
                MN_INFO_LOG("MN_CALL_FillUmtsSupCodecList: invalid speech version");
                break;
        }
    }
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
