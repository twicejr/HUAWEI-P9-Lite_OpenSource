/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r34ZLfiqc2ejWRk2Iedq639isOkVz9qClVDwndCHH6Ikgf8vCX52dIFe0mIFdXgETYijs
IUfTizf5IPt+qq3nqKDPkGgiDN6l8GBZbw42bpRWFOXdUQtFXgvFdhP37y/LMA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : avs_vfmw.c
    版 本 号   : 初稿
    作    者   : y62639
    生成日期   : 2007年12月14日
    最近修改   :
    功能描述   : firmware file
    修改历史   :
    1.日    期   : 2007年12月14日
    作    者   : y62639
    修改内容   : 创建文件

    2.日    期   : 2007年12月17日
    作    者   : y62639
    修改内容   : 加入AVS slice以上头解析函数

    3.日    期   : 2007年12月20日
    作    者   : y62639
    修改内容   : 加入资源管理和解码框架函数

    4.日    期   : 2008年1月11日
    作    者   : y62639
    修改内容   : 修改扩展头解析，加入扩展头和用户头入口函数

    5.日    期   : 2008年5月7日
    作    者   : y62639
    修改内容   : 为EDA和FPGA准备
******************************************************************************/

#ifndef __AVS_C__
#define __AVS_C__

#include    "syntax.h"
#include    "avs.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"
#include	"vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"

#ifdef AVS_ENABLE

/*----------------------------------------------*
* 内部函数原型说明                             *
*----------------------------------------------*/
SINT32 AVS_ParseHeader(AVS_CTX_S *pCtx);
SINT32 AVS_next_start_code(BS *pBs);
SINT32 AVS_sequence_header(AVS_CTX_S *pCtx, AVS_SYNTAX *pSyntax);
SINT32 AVS_i_picture_header(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_pb_picture_header(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_user_data(AVS_CTX_S *pCtx, SINT32 ExtFrm);
SINT32 AVS_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_extension_and_userdata(AVS_CTX_S *pCtx, SINT32 ExtFrm);
SINT32 AVS_sequence_display_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_copyright_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_camera_parameters_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_picture_display_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax);
SINT32 AVS_DecodeArbiter(AVS_CTX_S *pCtx);
SINT32 AVS_AllocateAHB(AVS_CODECINF *pCodecInf);
SINT32 AVS_AllocateVHB(AVS_CTX_S *pCtx);
SINT32 AVS_GetStreamInf(AVS_CTX_S *pCtx);
SINT32 AVS_PrepareDecode(AVS_CTX_S *pCtx);
SINT32 AVS_StartDecode(AVS_CTX_S *pCtx);
SINT32 AVS_GetImageBuffer(AVS_CTX_S *pCtx);
SINT32 AVS_OutputOneFrame(FRAME_OBJ *pOutput, AVS_CTX_S *pCtx);
SINT32 AVS_UpdatePmvTable(AVS_CODECINF *pCodecInf);
SINT32 AVS_VerifyMemPara(VOID);
SINT32 ClearSlice(SINT32 ChanID,AVS_SLCSTR_S *pSlcStr);
SINT32 ClearPacket(AVS_CTX_S *pCtx);
SINT32 WriteAvsSliceMsg(AVS_CTX_S *pCtx);
VOID  Avs_Vfmw_WQMatrix(AVS_SYNTAX *pSyntax);

AVS_VDMCFG g_AvsCfg;

SINT16 wq_param_default[2][6]=
{
	{135,143,143,160,160,213},   
	{128, 98,106,116,116,128}     
};
static const UINT8 WeightQuantModel[4][64] =
{
//     l a b c d h
//	 0 1 2 3 4 5
	{ 	
       // Mode 0
		0,0,0,4,4,4,5,5,
		0,0,3,3,3,3,5,5,
		0,3,2,2,1,1,5,5,
		4,3,2,2,1,5,5,5,
		4,3,1,1,5,5,5,5,
		4,3,1,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
    },
	{  
       // Mode 1
		0,0,0,4,4,4,5,5,
		0,0,4,4,4,4,5,5,
		0,3,2,2,2,1,5,5,
		3,3,2,2,1,5,5,5,
		3,3,2,1,5,5,5,5,
		3,3,1,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
    },
	{   
       // Mode 2
		0,0,0,4,4,3,5,5,
		0,0,4,4,3,2,5,5,
		0,4,4,3,2,1,5,5,
		4,4,3,2,1,5,5,5,
		4,3,2,1,5,5,5,5,
		3,2,1,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
    },
	{  
	// Mode 3
		0,0,0,3,2,1,5,5,
		0,0,4,3,2,1,5,5,
		0,4,4,3,2,1,5,5,
		3,3,3,3,2,5,5,5,
		2,2,2,2,5,5,5,5,
		1,1,1,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
    }
};
#define AVS_ATTACHUDINF(dst,src) {if(0!=(src)){(dst)=(src);(src)=0;}}
#define AVS_CLEARREFFLAG do{\
    IMAGE *pImg;\
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);\
    if (NULL != pImg)\
    {\
        FSP_ClearLogicFs(pCtx->ChanID, pCodecInf->pCurFrm->FspID, 1);\
        FSP_ClearLogicFs(pCtx->ChanID, pCodecInf->pRef[0]->FspID, 1);\
        FSP_ClearLogicFs(pCtx->ChanID, pCodecInf->pRef[1]->FspID, 1);\
        FSP_ClearLogicFs(pCtx->ChanID, pCodecInf->pRef[2]->FspID, 1);\
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);\
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);\
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[2]);\
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[3]);\
        pImg->p_usrdat[0] = NULL; \
        pImg->p_usrdat[1] = NULL; \
        pImg->p_usrdat[2] = NULL; \
        pImg->p_usrdat[3] = NULL; \
        pCodecInf->pRef[0] =\
        pCodecInf->pRef[1] =\
        pCodecInf->pRef[2] =\
        pCodecInf->pCurFrm = &(pCodecInf->ZeroFrm);\
        pCodecInf->pRef[0]->FspID=pCodecInf->pRef[1]->FspID=pCodecInf->pRef[2]->FspID=pCodecInf->pCurFrm->FspID=FSP_GetNullLogicFs(pCtx->ChanID);\
    }\
}while(0)

#define AVS_ASSERT_RET( cond, ret )\
do{\
    if( !(cond) )\
    {\
        dprint(PRN_FATAL, "line: %d\n", __LINE__);\
        return (ret);\
    }\
}while (0)



#define AVS_CLEARREFNUM do{pCodecInf->RefNum=0;}while(0)


/*****************************************************************************
函 数 名  : avs_u_v
功能描述  : 从码流中取无符号数
输入参数  : BS *pBs      
SINT32 v     
SINT8 *Name  
输出参数  : 无
返 回 值  : UINT32
调用函数  : 
被调函数  : 

  修改历史      :
  1.日    期   : 2008年1月9日
  作    者   : y62639
  修改内容   : 新生成函数
  
*****************************************************************************/
UINT32 avs_u_v(BS *pBs,SINT32 v, SINT8 *Name)
{
    UINT32 Code;
    
    Code = BsGet(pBs,v);
    dprint(PRN_STREAM,"%-40s     %#-8x(%db)\n", Name, Code,v);
    
    return Code;
}


/*****************************************************************************
函 数 名  : f_v
功能描述  : 从码流中取固定值
输入参数  : BS *pBs      
SINT32 v     
SINT8 *Name  
输出参数  : 无
返 回 值  : UINT32
调用函数  : 
被调函数  : 

  修改历史      :
  1.日    期   : 2008年1月9日
  作    者   : y62639
  修改内容   : 新生成函数
  
*****************************************************************************/
UINT32 avs_f_v(BS *pBs,SINT32 v, SINT8 *Name)
{
    UINT32 Code;
    
    Code = BsGet(pBs,v);
    dprint(PRN_STREAM,"%-40s     %#-8x(%db)\n",Name,Code,v);
    
    return Code;
}


/*****************************************************************************
函 数 名  : avs_ue_v
功能描述  : 解0 阶无符号哥伦布码
输入参数  : BS *pBs  
SINT8 *Name
输出参数  : 无
返 回 值  : UINT32
调用函数  : 
被调函数  : 

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数
  
*****************************************************************************/
UINT32 avs_ue_v(BS *pBs, SINT8 *Name)
{
    UINT32 NumBits, tmpbits;
    UINT32 Info;    
    UINT32 LeadingZeros;
    
    tmpbits = BsShow(pBs, 32);
    LeadingZeros = ZerosMS_32(tmpbits);
    if (LeadingZeros < 32)
    {
        /* 因为最大的数为2的31次方，所以zeros+1的最大个数为32  */
        BsSkip(pBs, LeadingZeros);
        Info = BsShow(pBs, (LeadingZeros+1)) - 1;        
        BsSkip(pBs, (LeadingZeros+1));
        NumBits = (LeadingZeros<<1) + 1; 
    }
    else
    {
        /* 这时有32个零，说明有错误发生  */
        Info = 0xffffffff;
        NumBits = 32;
    }
    
    dprint(PRN_STREAM, "%-40s     %#-8x(%db)\n",Name,Info,NumBits);
    
    return Info;    
}


/*****************************************************************************
函 数 名  : se_v
功能描述  : 解0 阶有符号哥伦布码
输入参数  : BS *pBs  
SINT8 *Name
输出参数  : 无
返 回 值  : SINT32
调用函数  : 
被调函数  : 

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数
  
*****************************************************************************/
SINT32 avs_se_v(BS *pBs, SINT8 *Name)
{ 
    UINT32 NumBits, tmpbits;
    SINT32 Info;   
    UINT32 LeadingZeros;
    UINT32 InfoLastBit;
    
    tmpbits = BsShow(pBs, 32);
    LeadingZeros   = ZerosMS_32(tmpbits);
    
    /* 因为最大的数为2的31次方，所以zeros的最大个数为32，所以在这种情况下需要BsShow两次  */
    if (LeadingZeros < 32)
    {
        BsSkip(pBs, LeadingZeros);
        Info = BsShow(pBs, (LeadingZeros+1)) - 1;  
        InfoLastBit = Info&1;
        Info = Info>>1;
        Info = ((InfoLastBit&1) ? (Info+1) : -1*Info);
        BsSkip(pBs, (LeadingZeros+1));
        NumBits = (LeadingZeros<<1) + 1; 
    }
    else
    {
        /* 这时有32个零，说明有错误发生  */
        Info = 0x7fffffff;
        NumBits = 32;
    }
    dprint(PRN_STREAM, "%-40s     %#-8x(%db)\n",Name,Info,NumBits);
    
    return Info;
}


/*****************************************************************************
函 数 名  : AVS_ParseHeader
功能描述  : 解析AVS slice以上层的语法
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_ParseHeader(AVS_CTX_S *pCtx)
{
    UINT32 Code;
    UINT32 end_code1, end_code2;
    BS *pBs;
    AVS_CODECINF *pCodecInf;
    AVS_SYNTAX *pSyntax;
    AVS_DEC_PARAM_S *pDecParam;
  
    pCodecInf = &pCtx->CodecInfo;
    pSyntax = &pCtx->SyntaxNew;
    pDecParam = &pCtx->AvsDecParam;
    pBs = pCodecInf->pBs;
    pCtx->IsPackWaitDec = 0;
    Code  = BsShow(pBs, 32);
    Code &= 0xff;

    switch (Code)
    {
    case CODE_SEQSTART:
        if((pCodecInf->Integrity & AVS_FOUND_SLCHDR) == AVS_FOUND_SLCHDR)
        {
            pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
        }
        else if((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
              /*||((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR))*/
        {
            pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
            AVS_sequence_header(pCtx, pSyntax);
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        else
        {
            AVS_sequence_header(pCtx, pSyntax);
            ClearPacket(pCtx);
            //pCtx->IsPackWaitDec = 0;
        }
        break;
    case CODE_IPIC:
        if((pCodecInf->Integrity & AVS_FOUND_SLCHDR) == AVS_FOUND_SLCHDR)
        {
            pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
			Avs_Vfmw_WQMatrix(pSyntax);	
        }
        else if/*(((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
              ||*/((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR)
        {
            pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
            AVS_i_picture_header(pCodecInf, pSyntax);
			Avs_Vfmw_WQMatrix(pSyntax);	
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        else
        {
            AVS_i_picture_header(pCodecInf, pSyntax);
			Avs_Vfmw_WQMatrix(pSyntax);	
            ClearPacket(pCtx);
            //pCtx->IsPackWaitDec = 0;
        }
        break;
    case CODE_PBPIC:
        if((pCodecInf->Integrity & AVS_FOUND_SLCHDR) == AVS_FOUND_SLCHDR)
        {
            pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
			Avs_Vfmw_WQMatrix(pSyntax);	
        }
        else if/*(((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
              ||*/((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR)
        {
            pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
            AVS_pb_picture_header(pCodecInf, pSyntax);
			Avs_Vfmw_WQMatrix(pSyntax);	
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        else
        {
            AVS_pb_picture_header(pCodecInf, pSyntax);
			Avs_Vfmw_WQMatrix(pSyntax);	
            ClearPacket(pCtx);
            //pCtx->IsPackWaitDec = 0;
        }
        break;
    case CODE_UDSTART:
        if((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR)
        {
            AVS_user_data(pCtx, PIC_EXT_AND_USD);
            ClearPacket(pCtx);
        }
        else if((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
        {
            AVS_user_data(pCtx, SEQ_EXT_AND_USD);
            ClearPacket(pCtx);
        }
        else
        {	
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        break;      
    case CODE_EXT:
        if(((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
         ||((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR))
        {
            AVS_extension(pCodecInf, pSyntax);
            ClearPacket(pCtx);
        }
        else
        {
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        break;
    case CODE_EDIT:
        if((pCodecInf->Integrity & AVS_FOUND_SLCHDR) == AVS_FOUND_SLCHDR)
        {
            pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
        }
        else if(((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
              ||((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR))
        {
            pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        break;
    case CODE_SEQEND:
        if((pCodecInf->Integrity & AVS_FOUND_SLCHDR) == AVS_FOUND_SLCHDR)
        {
            pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
        }
        else if(((pCodecInf->Integrity & AVS_FOUND_SEQHDR) == AVS_FOUND_SEQHDR)
              ||((pCodecInf->Integrity & AVS_FOUND_PICHDR) == AVS_FOUND_PICHDR))
        {
            pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
            ClearPacket(pCtx);
            return AVS_FALSE;
        }
        break;
    case CODE_RSV0:
    case CODE_RSV1:
		ClearPacket(pCtx);
        break;

    case HISI_AVS_STREAM_END_CODE:
	 BsSkip(pBs, 32);
        end_code1 = (UINT32)BsGet(pBs, 32);
	 end_code2 = (UINT32)BsGet(pBs, 32);
        if (HISI_STREAM_END_CODE1 == end_code1 && HISI_STREAM_END_CODE2 == end_code2)
        {		
	     pCtx->IsStreamEndFlag = 1;              // last frame
	     pCtx->IsPackWaitDec = 1;
            pCodecInf->Integrity |= AVS_FOUND_NEXTHDR;
	     ClearPacket(pCtx);
            return AVS_TRUE;
        }
	 else
	 {
	     ClearPacket(pCtx);
            return AVS_FALSE;
	 }
        break;

    default:
        if (Code <= 0xaf)/*slice start Code*/
        {
            if ((pCodecInf->Integrity & AVS_BASIC_HDR) == AVS_BASIC_HDR)
            {
                pCodecInf->Integrity |= AVS_FOUND_SLCHDR;
                if(AVS_FALSE == WriteAvsSliceMsg(pCtx))
                {
                    ClearPacket(pCtx);
                    return AVS_FALSE;
                }
                break;
            }
        }
        //pCodecInf->Integrity &= ~AVS_FOUND_SLCHDR;
        ClearPacket(pCtx);
        //return AVS_FALSE;
    }
    
    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_next_start_code
功能描述  : 在AVS码流中搜索下一个起始码
输入参数  : BS *pBs
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月14日
  作    者   : y62639
  修改内容   : 新生成函数

    2.日    期   : 2007年12月17日
    作    者   : y62639
    修改内容   : 暂时屏蔽stuffing的值检查
*****************************************************************************/
SINT32 AVS_next_start_code(BS *pBs)
{
    SINT32 i, RemainByte;

    BsToNextByte(pBs); /*这些填充则应该全部为0*/
    RemainByte = (BsResidBits(pBs) / 8) - 3;

    for (i = 0; i < RemainByte; i++)
    {
        if (BsShow(pBs, 24) == 0x01L)
        {
            return AVS_TRUE;
        }

        BsSkip(pBs, 8);
    }

    return AVS_FALSE;
}


/*****************************************************************************
函 数 名  : AVS_sequence_header
功能描述  : 解AVS 序列头
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_sequence_header(AVS_CTX_S *pCtx, AVS_SYNTAX *pSyntax)
{
    AVS_CODECINF *pCodecInf = &pCtx->CodecInfo;
    BS *pBs = pCodecInf->pBs;
    AVS_SYNTAX *pCurSyn = &pCodecInf->Syntax;
    pCodecInf->Integrity &= ~AVS_FOUND_SEQHDR;

    avs_f_v(pBs, 32, "video_sequence_start_code");
    pSyntax->syn_seq.profile_id = avs_u_v(pBs, 8, "profile_id");
    pSyntax->syn_seq.level_id = avs_u_v(pBs, 8, "level_id");
    pSyntax->syn_seq.progressive_sequence = avs_u_v(pBs, 1, "progressive_sequence");
    pSyntax->syn_seq.horizontal_size = avs_u_v(pBs, 14, "horizontal_size");
    pSyntax->syn_seq.vertical_size = avs_u_v(pBs, 14, "vertical_size");
    pSyntax->syn_seq.chroma_format = avs_u_v(pBs, 2, "chroma_format");
    pSyntax->syn_seq.sample_precision = avs_u_v(pBs, 3, "sample_precision");
    pSyntax->syn_seq.aspect_ratio = avs_u_v(pBs, 4, "aspect_ratio");
    pSyntax->syn_seq.frame_rate_code = avs_u_v(pBs, 4, "frame_rate_code");
    pSyntax->syn_seq.bit_rate_lower = avs_u_v(pBs, 18, "bit_rate_lower");
    pSyntax->syn_seq.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    pSyntax->syn_seq.bit_rate_upper = avs_u_v(pBs, 12, "bit_rate_upper");
    pSyntax->syn_seq.low_delay  = avs_u_v(pBs, 1, "low_delay");
    pSyntax->syn_seq.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    pSyntax->syn_seq.bbv_buffer_size = avs_u_v(pBs, 18, "bbv_buffer_size");
    pSyntax->syn_seq.reserved_bits = avs_u_v(pBs, 3, "reserved_bits");

    /*!!!此处对序列头信息进行检查，失败则应返回错误*/
    if ((pSyntax->syn_seq.horizontal_size != pCurSyn->syn_seq.horizontal_size)
       || (pSyntax->syn_seq.vertical_size != pCurSyn->syn_seq.vertical_size))
    {
        pCodecInf->SizeChanged = AVS_TRUE;
        REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pCurSyn->syn_seq.horizontal_size, pCurSyn->syn_seq.vertical_size, 
            pSyntax->syn_seq.horizontal_size, pSyntax->syn_seq.vertical_size);
    }
    else
    {
        //pCodecInf->SizeChanged = AVS_FALSE;  //del by z56361, 20090412
    }

    *pCurSyn = *pSyntax;
    pCodecInf->NewSeq = AVS_TRUE;
    pCodecInf->SeqCnt++;
    pCodecInf->Integrity |= AVS_FOUND_SEQHDR;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_i_picture_header
功能描述  : 解AVS I图图像头
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_i_picture_header(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    SINT32 i;
    BS *pBs = pCodecInf->pBs;
    memset(&pSyntax->syn_pic, 0, sizeof(AVS_PIC));
    pCodecInf->Integrity &= ~AVS_FOUND_PICHDR;
    avs_f_v(pBs, 32, "i_picture_start_code");
    pSyntax->syn_pic.bbv_delay = avs_u_v(pBs, 16, "bbv_delay");
    if( 0x48 == pSyntax->syn_seq.profile_id)
    {
        pSyntax->syn_pic.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    	pSyntax->syn_pic.bbv_delay_extension = avs_u_v(pBs, 7, "bbv_delay_extension");

    	pSyntax->syn_pic.bbv_delay <<= 7;
    	pSyntax->syn_pic.bbv_delay |= pSyntax->syn_pic.bbv_delay_extension;
    }
   // end profile_id=48,2013.2.27
    pSyntax->syn_pic.time_code_flag = avs_u_v(pBs, 1, "time_code_flag");
    if (pSyntax->syn_pic.time_code_flag == 1)
    {
        pSyntax->syn_pic.time_code = avs_u_v(pBs, 24, "time_code");
    }

    pSyntax->syn_pic.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    pSyntax->syn_pic.picture_distance = avs_u_v(pBs, 8, "picture_distance");
    if (pSyntax->syn_seq.low_delay == 1)
    {
        pSyntax->syn_pic.bbv_check_times = avs_ue_v(pBs, "bbv_check_times");
    }

    pSyntax->syn_pic.progressive_frame = avs_u_v(pBs, 1, "progressive_frame");
    if (pSyntax->syn_seq.progressive_sequence == 1)
    {
        /*语法容错，确保两个信息一致*/
        pSyntax->syn_pic.progressive_frame = 1;
    }

    if (pSyntax->syn_pic.progressive_frame == 0)
    {
        pSyntax->syn_pic.picture_structure = avs_u_v(pBs, 1, "picture_structure");
    }
    else
    {
        pSyntax->syn_pic.picture_structure = 1;
    }

    pSyntax->syn_pic.top_field_first = avs_u_v(pBs, 1, "top_field_first");
    pSyntax->syn_pic.repeat_first_field = avs_u_v(pBs, 1, "repeat_first_field");
    pSyntax->syn_pic.fixed_picture_qp = avs_u_v(pBs, 1, "fixed_picture_qp");
    pSyntax->syn_pic.picture_qp = avs_u_v(pBs, 6, "picture_qp");
    if ((pSyntax->syn_pic.progressive_frame == 0) && (pSyntax->syn_pic.picture_structure == 0))
    {
        pSyntax->syn_pic.skip_mode_flag = avs_u_v(pBs, 1, "skip_mode_flag");
    }

    pSyntax->syn_pic.reserved_bits = avs_u_v(pBs, 4, "reserved_bits");
    pSyntax->syn_pic.loop_filter_disable = avs_u_v(pBs, 1, "loop_filter_disable");
    pSyntax->syn_pic.alpha_c_offset = 0;
    pSyntax->syn_pic.beta_offset = 0;
    if (pSyntax->syn_pic.loop_filter_disable == 0)
    {
        pSyntax->syn_pic.loop_filter_parameter_flag = avs_u_v(pBs, 1, "loop_filter_parameter_flag");
        if (pSyntax->syn_pic.loop_filter_parameter_flag)
        {
            pSyntax->syn_pic.alpha_c_offset = avs_se_v(pBs, "alpha_c_offset");
            pSyntax->syn_pic.beta_offset = avs_se_v(pBs, "beta_offset");
        }
    }
    if ( 0x48 == pSyntax->syn_seq.profile_id)
    {
        pSyntax->syn_pic.weighting_quant_flag = avs_u_v(pBs, 1, "weighting_quant_flag");
    	if (pSyntax->syn_pic.weighting_quant_flag)
    	{
	      pSyntax->syn_pic.mb_adapt_weighting_quant_disable = avs_u_v(pBs, 1, "mb_adapt_weighting_quant_disable");
	      pSyntax->syn_pic.chroma_quant_param_disable = avs_u_v(pBs, 1, "chroma_quant_param_disable");
	      if (!pSyntax->syn_pic.chroma_quant_param_disable)
	      {
	          pSyntax->syn_pic.chroma_quant_param_delta_u = avs_se_v(pBs, "chroma_quant_param_delta_u");
     		  pSyntax->syn_pic.chroma_quant_param_delta_v = avs_se_v(pBs, "chroma_quant_param_delta_v");
	      }
	      pSyntax->syn_pic.weighting_quant_param_index = avs_u_v(pBs, 2, "weighting_quant_param_index");
	      pSyntax->syn_pic.weighting_quant_model = avs_u_v(pBs, 2, "weighting_quant_model");
	      if ((1 == pSyntax->syn_pic.weighting_quant_param_index)
		  	|| ((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable) && (3 == pSyntax->syn_pic.weighting_quant_param_index)))
	      {
	          for (i=0; i<6; i++)
	          {
	               pSyntax->syn_pic.weighting_quant_param_delta1[i] = avs_se_v(pBs, "weighting_quant_param_deltal1");
	          }
	      }
	      if ((2 == pSyntax->syn_pic.weighting_quant_param_index)
		  	|| ((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable) && (3 == pSyntax->syn_pic.weighting_quant_param_index)))
	      {
	          for (i=0; i<6; i++)
	          {
	               pSyntax->syn_pic.weighting_quant_param_delta2[i] = avs_se_v(pBs, "weighting_quant_param_deltal2");
	          }
	      }
	  }
	  pSyntax->syn_pic.aec_enable = avs_u_v(pBs, 1, "aec_enable");
    }
    pSyntax->syn_pic.picture_reference_flag = 1;

    /*为了便于后续操作引用，将图像类型进行翻译*/
    pSyntax->syn_pic.derived_pic_coding_type = I_PICTURE;
    pCodecInf->Integrity |= AVS_FOUND_PICHDR;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_pb_picture_header
功能描述  : 解AVS pb 图图像头
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_pb_picture_header(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    UINT32 i;
    BS *pBs = pCodecInf->pBs;
    memset(&pSyntax->syn_pic, 0, sizeof(AVS_PIC));
    pCodecInf->Integrity &= ~AVS_FOUND_PICHDR;
    avs_f_v(pBs, 32, "pb_picture_start_code");
    pSyntax->syn_pic.bbv_delay = avs_u_v(pBs, 16, "bbv_delay");
    if( 0x48 == pSyntax->syn_seq.profile_id)
    {
        pSyntax->syn_pic.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    	pSyntax->syn_pic.bbv_delay_extension = avs_u_v(pBs, 7, "bbv_delay_extension");

    	pSyntax->syn_pic.bbv_delay <<= 7;
    	pSyntax->syn_pic.bbv_delay |= pSyntax->syn_pic.bbv_delay_extension;
    }
    // end profile_id=0x48,2013.2.27
	pSyntax->syn_pic.picture_coding_type = avs_u_v(pBs, 2, "picture_coding_type");
    pSyntax->syn_pic.picture_distance = avs_u_v(pBs, 8, "picture_distance");
    if (pSyntax->syn_seq.low_delay == 1)
    {
        //pSyntax->syn_pic.marker_bit = BsGet(pBs,1);
        pSyntax->syn_pic.bbv_check_times = avs_ue_v(pBs, "bbv_check_times");
    }

    pSyntax->syn_pic.progressive_frame = avs_u_v(pBs, 1, "progressive_frame");
    if (pSyntax->syn_pic.progressive_frame == 0)
    {
        pSyntax->syn_pic.picture_structure = avs_u_v(pBs, 1, "picture_structure");
        if (pSyntax->syn_pic.picture_structure == 0)
        {
            pSyntax->syn_pic.advanced_pred_mode_disable = avs_u_v(pBs, 1, "advanced_pred_mode_disable");
        }
    }
    else
    {
        pSyntax->syn_pic.picture_structure = 1;
    }

    pSyntax->syn_pic.top_field_first = avs_u_v(pBs, 1, "top_field_first");
    pSyntax->syn_pic.repeat_first_field = avs_u_v(pBs, 1, "repeat_first_field");
    pSyntax->syn_pic.fixed_picture_qp = avs_u_v(pBs, 1, "fixed_picture_qp");
    pSyntax->syn_pic.picture_qp = avs_u_v(pBs, 6, "picture_qp");
    if (!((pSyntax->syn_pic.picture_coding_type == 2) && (pSyntax->syn_pic.picture_structure == 1)))
    {
        pSyntax->syn_pic.picture_reference_flag = avs_u_v(pBs, 1, "picture_reference_flag");
    }
    else
    {
        /*B帧情况下，使用的参考帧是确定的，不由宏块决定*/
        pSyntax->syn_pic.picture_reference_flag = 1;
    }

    pSyntax->syn_pic.no_forward_reference_flag = avs_u_v(pBs, 1, "no_forward_reference_flag");
    pSyntax->syn_pic.p_filed_enhanced_flag = 0;
    pSyntax->syn_pic.b_filed_enhanced_flag = 0;
    if (2 == pSyntax->syn_pic.picture_coding_type)
    {
        pSyntax->syn_pic.b_filed_enhanced_flag = avs_u_v(pBs, 1, "b_filed_enhanced_flag");
    }
    else
    {
        pSyntax->syn_pic.p_filed_enhanced_flag = avs_u_v(pBs, 1, "p_filed_enhanced_flag");
    }
    if (1 == pSyntax->syn_pic.picture_structure || 0x48 != pSyntax->syn_seq.profile_id)
    {
        pSyntax->syn_pic.p_filed_enhanced_flag = 0;
        pSyntax->syn_pic.b_filed_enhanced_flag = 0; 
    }
    pSyntax->syn_pic.reserved_bits  = avs_u_v(pBs, 2, "reserved_bits");

    //pSyntax->syn_pic.reserved_bits  = avs_u_v(pBs, 3, "reserved_bits");
    pSyntax->syn_pic.skip_mode_flag = avs_u_v(pBs, 1, "skip_mode_flag");
    pSyntax->syn_pic.loop_filter_disable = avs_u_v(pBs, 1, "loop_filter_disable");
    pSyntax->syn_pic.alpha_c_offset = 0;
    pSyntax->syn_pic.beta_offset = 0;
    if (pSyntax->syn_pic.loop_filter_disable == 0)
    {
        pSyntax->syn_pic.loop_filter_parameter_flag = avs_u_v(pBs, 1, "loop_filter_parameter_flag");
        if (pSyntax->syn_pic.loop_filter_parameter_flag)
        {
            pSyntax->syn_pic.alpha_c_offset = avs_se_v(pBs, "alpha_c_offset");
            pSyntax->syn_pic.beta_offset = avs_se_v(pBs, "beta_offset");
        }
    }
    if ( 0x48 == pSyntax->syn_seq.profile_id)
    {
      pSyntax->syn_pic.weighting_quant_flag = avs_u_v(pBs, 1, "weighting_quant_flag");
	  if (1 == pSyntax->syn_pic.weighting_quant_flag)
	  {
	      pSyntax->syn_pic.mb_adapt_weighting_quant_disable = avs_u_v(pBs, 1, "mb_adapt_weighting_quant_disable");
	      pSyntax->syn_pic.chroma_quant_param_disable = avs_u_v(pBs, 1, "chroma_quant_param_disable");
	      if (0 == pSyntax->syn_pic.chroma_quant_param_disable)
	      {
	           pSyntax->syn_pic.chroma_quant_param_delta_u = avs_se_v(pBs, "chroma_quant_param_delta_u");
    		   pSyntax->syn_pic.chroma_quant_param_delta_v = avs_se_v(pBs, "chroma_quant_param_delta_v");
	      }
	      pSyntax->syn_pic.weighting_quant_param_index = avs_u_v(pBs, 2, "weighting_quant_param_index");
	      pSyntax->syn_pic.weighting_quant_model = avs_u_v(pBs, 2, "weighting_quant_model");
	      if ((1 == pSyntax->syn_pic.weighting_quant_param_index)
		  	|| ((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable) && (3 == pSyntax->syn_pic.weighting_quant_param_index)))
	      {
	          for (i=0; i<6; i++)
	          {
	               pSyntax->syn_pic.weighting_quant_param_delta1[i] = avs_se_v(pBs, "weighting_quant_param_deltal1");
	          }
	      }
	      if ((2 == pSyntax->syn_pic.weighting_quant_param_index)
		  	|| ((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable) && (3 == pSyntax->syn_pic.weighting_quant_param_index)))
	      {
	          for (i=0; i<6; i++)
	          {
	               pSyntax->syn_pic.weighting_quant_param_delta2[i] = avs_se_v(pBs, "weighting_quant_param_deltal2");
	          }
	      }
	  }
	  pSyntax->syn_pic.aec_enable = avs_u_v(pBs, 1, "aec_enable");
    }

    /*为了便于后续操作引用，将图像类型进行翻译*/
    if (pSyntax->syn_pic.picture_coding_type == 1)
    {
        pSyntax->syn_pic.derived_pic_coding_type = P_PICTURE;
    }
    else
    {
        pSyntax->syn_pic.derived_pic_coding_type = B_PICTURE;
    }

    pCodecInf->Integrity |= AVS_FOUND_PICHDR;

    return AVS_TRUE;
}


UINT8  g_tmp[MAX_USRDAT_SIZE];
/*****************************************************************************
函 数 名  : AVS_user_data
功能描述  : 解AVS 的user data
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_user_data(AVS_CTX_S *pCtx, SINT32 ExtFrm)
{
    BS *pBs;
    AVS_CODECINF *pCodecInf;
    AVS_SYNTAX *pSyntax;

    pCodecInf = &pCtx->CodecInfo;
    pSyntax = &pCtx->SyntaxNew;
    pBs = pCodecInf->pBs;

    avs_f_v(pBs, 32, "user_data_start_code");
    pCodecInf->Integrity |= AVS_FOUND_UD;
    if (SEQ_EXT_AND_USD == ExtFrm)
    {
        if (NULL != pCodecInf->pSeqUD)
        {
            FreeUsdByDec(pCtx->ChanID, pCodecInf->pSeqUD);
            pCodecInf->pSeqUD = NULL;
        }

        //only empty pointer need get, otherwise just overwrite pointer's content
        pCodecInf->pSeqUD = GetUsd(pCtx->ChanID);
        if( pCodecInf->pSeqUD == NULL )
        {
            return AVS_FALSE;
        }

        pCodecInf->pSeqUD->PTS = pCtx->pstExtraData->pts;
        pCodecInf->pSeqUD->from = USD_AVSSEQ;
        pCodecInf->pSeqUD->seq_cnt = pCodecInf->SeqCnt;
#if 0        
        pCodecInf->pSeqUD->data_size = pCtx->LastPacket.StreamPack[0].LenInByte 
                                     + pCtx->LastPacket.StreamPack[0].LenInByte
                                     - 4;//cnt;
#endif
        pCodecInf->pSeqUD->data_size = pCtx->LastPacket.StreamPack[0].LenInByte - 4; 
        if(pCodecInf->pSeqUD->data_size > MAX_USRDAT_SIZE)
        {
            pCodecInf->pSeqUD->data_size = MAX_USRDAT_SIZE;
        }
        memcpy(pCodecInf->pSeqUD->data, pCtx->LastPacket.StreamPack[0].VirAddr+4,
                                        pCodecInf->pSeqUD->data_size);
                                        //g_tmp,pCodecInf->pSeqUD->data_size);
        if(0 == pCtx->LastPacket.StreamPack[0].IsLastSeg)
        {
            pCodecInf->pSeqUD->data_size += pCtx->LastPacket.StreamPack[1].LenInByte;
            if(pCodecInf->pSeqUD->data_size > MAX_USRDAT_SIZE)
            {
                pCodecInf->pSeqUD->data_size = MAX_USRDAT_SIZE;
            }
            if((pCodecInf->pSeqUD->data_size - (pCtx->LastPacket.StreamPack[0].LenInByte - 4))>0)
            {
                memcpy(pCodecInf->pSeqUD->data + pCtx->LastPacket.StreamPack[0].LenInByte - 4,
                       pCtx->LastPacket.StreamPack[1].VirAddr,
                       pCodecInf->pSeqUD->data_size - (pCtx->LastPacket.StreamPack[0].LenInByte - 4));
                       //g_tmp,pCodecInf->pSeqUD->data_size);
            }
        }

        REPORT_USRDAT( pCtx->ChanID, pCodecInf->pSeqUD );
    }
    else
    {
        if (NULL != pCodecInf->pPicUD)
        {
            FreeUsdByDec(pCtx->ChanID, pCodecInf->pPicUD);
            pCodecInf->pPicUD = NULL;
        }
        //only empty pointer need get, otherwise just overwrite pointer's content
        pCodecInf->pPicUD = GetUsd(pCtx->ChanID);
        if( pCodecInf->pPicUD == NULL )
        {
            return AVS_FALSE;
        }
        pCodecInf->pPicUD->PTS = pCtx->pstExtraData->pts;   
        pCodecInf->pPicUD->from = USD_AVSPIC;
        pCodecInf->pPicUD->seq_cnt = pCodecInf->SeqCnt;
        pCodecInf->pPicUD->data_size = pCtx->LastPacket.StreamPack[0].LenInByte - 4; 
        if(pCodecInf->pPicUD->data_size > MAX_USRDAT_SIZE)
        {
            pCodecInf->pPicUD->data_size = MAX_USRDAT_SIZE;
        }

        memcpy(pCodecInf->pPicUD->data, pCtx->LastPacket.StreamPack[0].VirAddr+4,
                                        pCodecInf->pPicUD->data_size);
                                        //g_tmp,pCodecInf->pSeqUD->data_size);
        if(0 == pCtx->LastPacket.StreamPack[0].IsLastSeg)
        {
            pCodecInf->pPicUD->data_size += pCtx->LastPacket.StreamPack[1].LenInByte;
            if(pCodecInf->pPicUD->data_size > MAX_USRDAT_SIZE)
            {
                pCodecInf->pPicUD->data_size = MAX_USRDAT_SIZE;
            }
            if((pCodecInf->pPicUD->data_size - (pCtx->LastPacket.StreamPack[0].LenInByte - 4))>0)
            {
                memcpy(pCodecInf->pPicUD->data + pCtx->LastPacket.StreamPack[0].LenInByte - 4,
                       pCtx->LastPacket.StreamPack[1].VirAddr,
                       pCodecInf->pPicUD->data_size - (pCtx->LastPacket.StreamPack[0].LenInByte - 4));
                       //g_tmp,pCodecInf->pSeqUD->data_size);
            }
        }
        REPORT_USRDAT( pCtx->ChanID, pCodecInf->pPicUD );   
    }

        return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_extension
功能描述  : 解AVS 扩展头
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    UINT32 Code;
    SINT32 ret = AVS_FALSE;
    BS *pBs = pCodecInf->pBs;

    avs_f_v(pBs, 32, "extension_start_code");
    Code = BsShow(pBs, 4);
    switch (Code)
    {
        case EXTCODE_SEQDISP:
            ret = AVS_sequence_display_extension(pCodecInf, pSyntax);
            break;
        case EXTCODE_PICDISP:
            ret = AVS_picture_display_extension(pCodecInf, pSyntax);
            break;
        case EXTCODE_COPYRT:
            ret = AVS_copyright_extension(pCodecInf, pSyntax);
            break;
        case EXTCODE_CMRPRM:
            ret = AVS_camera_parameters_extension(pCodecInf, pSyntax);
            break;
        default:    /* reserved_extension_data_byte */
            BsSkip(pBs, 4);
            return AVS_FALSE;
    }

    return ret;
}


/*****************************************************************************
函 数 名  : AVS_extension_and_userdata
功能描述  : 扩展头和用户数据头入口函数
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2008年1月11日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_extension_and_userdata(AVS_CTX_S *pCtx, SINT32 ExtFrm)
{
    BS *pBs;
    UINT32 Code;
    AVS_CODECINF *pCodecInf;
    AVS_SYNTAX *pSyntax;
  
    pCodecInf = &pCtx->CodecInfo;
    pSyntax = &pCtx->SyntaxNew;
    pBs = pCodecInf->pBs;

    while (BsResidBits(pBs) > 40)
    {
        AVS_next_start_code(pBs);
        Code  = BsShow(pBs, 32);
        Code &= 0xff;
        if ((Code != CODE_EXT) && (Code != CODE_UDSTART))
        {
            return AVS_TRUE;
        }

        if (CODE_EXT == Code)
        {
            AVS_extension(pCodecInf, pSyntax);
        }

        Code  = BsShow(pBs, 32);
        Code &= 0xff;
        if (CODE_UDSTART == Code)
        {
            AVS_user_data(pCtx, ExtFrm);
        }
    }

    return AVS_FALSE;
}


/*****************************************************************************
函 数 名  : AVS_sequence_display_extension
功能描述  : 解AVS 序列显示扩展
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_sequence_display_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    BS *pBs = pCodecInf->pBs;

    avs_u_v(pBs, 4, "extension_ID");
    pSyntax->syn_sdext.video_format = avs_u_v(pBs, 3, "video_format");
    pSyntax->syn_sdext.sample_range = avs_u_v(pBs, 1, "sample_range");
    pSyntax->syn_sdext.colour_description = avs_u_v(pBs, 1, "colour_description");
    if (1 == pSyntax->syn_sdext.colour_description)
    {
        pSyntax->syn_sdext.colour_primaries = avs_u_v(pBs, 8, "colour_primaries");
        pSyntax->syn_sdext.transfer_characteristics = avs_u_v(pBs, 8, "transfer_characteristics");
        pSyntax->syn_sdext.matrix_coefficients = avs_u_v(pBs, 8, "matrix_coefficients");
    }

    pSyntax->syn_sdext.display_horizontal_size = avs_u_v(pBs, 14, "display_horizontal_size");
    pSyntax->syn_sdext.marker_bit = avs_f_v(pBs, 1, "marker_bit");
    pSyntax->syn_sdext.display_vertical_size = avs_u_v(pBs, 14, "display_vertical_size");
    pSyntax->syn_sdext.reserved_bits = avs_u_v(pBs, 2, "reserved_bits");
    AVS_next_start_code(pBs);
    pCodecInf->Integrity |= AVS_FOUND_SEQDSPHDR;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_copyright_extension
功能描述  : 解AVS 版权扩展
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_copyright_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    BS *pBs = pCodecInf->pBs;

    avs_u_v(pBs, 4, "extension_ID");
    avs_u_v(pBs, 1, "copyright_flag");
    avs_u_v(pBs, 8, "copyright_id");
    avs_u_v(pBs, 1, "original_or_copy");
    avs_u_v(pBs, 7, "reserved_bits");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 20, "copyright_number_1");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "copyright_number_2");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "copyright_number_3");
    AVS_next_start_code(pBs);
    pCodecInf->Integrity |= AVS_FOUND_COPYRT;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_camera_parameters_extension
功能描述  : 解AVS 摄像机参数扩展
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_camera_parameters_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    BS *pBs = pCodecInf->pBs;

    avs_u_v(pBs, 4, "extension_ID");
    avs_u_v(pBs, 1, "reserved_bits");
    avs_u_v(pBs, 7, "camera_id");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "height_of_image_device");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "focal_length");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "f_number");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "vertical_angle_of_view");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_x_upper");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_x_lower");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_y_upper");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_y_lower");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_z_upper");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 16, "camera_position_z_lower");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "camera_direction_x");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "camera_direction_y");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "camera_direction_z");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "image_plane_vertical_x");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "image_plane_vertical_y");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 22, "image_plane_vertical_z");
    avs_f_v(pBs, 1, "marker_bit");
    avs_u_v(pBs, 32, "reserved_bits");
    AVS_next_start_code(pBs);
    pCodecInf->Integrity |= AVS_FOUND_CMRPRM;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_picture_display_extension
功能描述  : 解AVS图像显示扩展
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_picture_display_extension(AVS_CODECINF *pCodecInf, AVS_SYNTAX *pSyntax)
{
    BS *pBs = pCodecInf->pBs;
    SINT32 i;

    avs_u_v(pBs, 4, "extension_ID");
    if (pSyntax->syn_seq.progressive_sequence == 1)
    {
        if (pSyntax->syn_pic.repeat_first_field == 1)
        {
            if (pSyntax->syn_pic.top_field_first == 1)
            {
                pSyntax->NumOfFrameCentreOffsets = 3;
            }
            else
            {
                pSyntax->NumOfFrameCentreOffsets = 2;
            }
        }
        else
        {
            pSyntax->NumOfFrameCentreOffsets = 1;
        }
    }
    else
    {
        if (pSyntax->syn_pic.picture_structure == 0)
        {
            pSyntax->NumOfFrameCentreOffsets = 1;
        }
        else
        {
            if (pSyntax->syn_pic.repeat_first_field == 1)
            {
                pSyntax->NumOfFrameCentreOffsets = 3;
            }
            else
            {
                pSyntax->NumOfFrameCentreOffsets = 2;
            }
        }
    }

    for (i = 0; i < (SINT32)pSyntax->NumOfFrameCentreOffsets; i++)
    {
        pSyntax->syn_pdext.frame_centre_horizontal_offset[i] = avs_u_v(pBs, 16, "frame_centre_horizontal_offset");
        avs_f_v(pBs, 1, "marker_bit");
        pSyntax->syn_pdext.frame_centre_vertical_offset[i] = avs_u_v(pBs, 16, "frame_centre_vertical_offset");
        avs_f_v(pBs, 1, "marker_bit");
    }

    AVS_next_start_code(pBs);
    pCodecInf->Integrity |= AVS_FOUND_PICDSPHDR;

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_DecodeArbiter
功能描述  : 对完成头解析的码流进行是否可以解码进行判定
输入参数  : AVS_CODECINF *pCodecInf
AVS_SYNTAX *pSyntax
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月19日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_DecodeArbiter(AVS_CTX_S *pCtx)
{
    SINT32  DecMode;
    SINT32  ret;
    AVS_CODECINF *pCodecInf;
    AVS_SYNTAX *pSyntax;
  
    pCodecInf = &pCtx->CodecInfo;
    pSyntax = &pCtx->SyntaxNew;

    /* 头是否已经解全 */
    if ( AVS_PIC_OK != (pCodecInf->Integrity & AVS_PIC_OK) )
    {
        return AVS_FALSE;
    }

    /* 解码模式 */
    DecMode = pCtx->pstExtraData->s32DecMode;
    ret = AVS_TRUE;
    switch( DecMode )
    {
    case IPB_MODE:  /* IPB */
    case DISCARD_B_BF_P_MODE:  /* IPB */
        if( pCodecInf->UsedDecMode == I_MODE )
        {
            pCodecInf->RefNum = 0;   /* 必须到下一个I帧才能真正切换到IPB模式 */
        }
        break;
    case IP_MODE:  /* IP */
        if( pCodecInf->UsedDecMode == I_MODE )
        {
            pCodecInf->RefNum = 0;   /* 必须到下一个I帧才能真正切换到IP模式 */
        }
        if( B_PICTURE == pSyntax->syn_pic.derived_pic_coding_type )
        {
            ret = AVS_FALSE;
        }
        break;
    case I_MODE:  /* I */
        if( I_PICTURE != pSyntax->syn_pic.derived_pic_coding_type )
        {
            ret = AVS_FALSE;
        }
        break;
    }

    pCodecInf->UsedDecMode = DecMode;
    if( AVS_FALSE == ret )
    {
        //AVS_CLEARREFFLAG;
        //AVS_CLEARREFNUM;
        //ResetVoQueue(&(pCtx->ImageQue));//add by p56607 2009 7 18
        AVS_ClearCurPic(pCtx);
//        ReleasePacket(VFMW_AVS, pCtx);
		pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);

        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        return AVS_FALSE;
    }

    /* 参考图是否够 */
    if( (P_PICTURE == pSyntax->syn_pic.derived_pic_coding_type && pCodecInf->RefNum < 1) ||
        (B_PICTURE == pSyntax->syn_pic.derived_pic_coding_type && pCodecInf->RefNum < 2) )
    {
        //AVS_CLEARREFFLAG;
        //AVS_CLEARREFNUM;    
        AVS_ClearCurPic(pCtx);
//        ReleasePacket(VFMW_AVS, pCtx);
		pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);

        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        return AVS_FALSE;
    }

    pCodecInf->Syntax = *pSyntax;

    // if(g_AvsCodecInf.PicCnt == 1) exit(-1) ;
    dprint(PRN_PIC, "-----Pic %5d, type %d, struct %d-----\n",
    pCodecInf->PicCnt,
    pCodecInf->Syntax.syn_pic.derived_pic_coding_type,
    pCodecInf->Syntax.syn_pic.picture_structure);
	
    pCodecInf->Integrity &= ~(AVS_FOUND_PICHDR | AVS_FOUND_SLCHDR |AVS_FOUND_NEXTHDR);
    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_AllocateVHB
功能描述  : 分配VHB帧存
输入参数  : AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月19日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_AllocateVHB(AVS_CTX_S *pCtx)
{
	AVS_CODECINF pCodecInf = pCtx->CodecInfo;
	FSP_INST_CFG_S  FspInstCfg;
    AVS_SEQ *pSyntaxSeqInfNew = &pCodecInf.Syntax.syn_seq;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;
    SINT32 Ret, UsedMemSize;

    if( pSyntaxSeqInfNew->horizontal_size < 32 || pSyntaxSeqInfNew->vertical_size < 32 )
    {
        dprint(PRN_FATAL, "ERROR: image size abnormal(%dx%d)\n", pSyntaxSeqInfNew->horizontal_size, pSyntaxSeqInfNew->vertical_size );
        return AVS_FALSE;
    }

    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if (pSyntaxSeqInfNew->horizontal_size > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxSeqInfNew->vertical_size > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "avs actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxSeqInfNew->horizontal_size, pSyntaxSeqInfNew->vertical_size,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			//pCtx->FspPartitionOK = 0;
			return AVS_FALSE;
		}
				
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pCtx->FspPartitionOK == 1)
        {
            return AVS_TRUE;
		}
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}	
	else if (pCtx->pstExtraData->eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION)
	{
        PicWidth  = pSyntaxSeqInfNew->horizontal_size;
        PicHeight = pSyntaxSeqInfNew->vertical_size;	
		DecFsNum = 4;
		PmvNum = 4;
		DispFsNum = 5;		
	}
	else
	{
        if (pSyntaxSeqInfNew->horizontal_size > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxSeqInfNew->vertical_size > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "avs actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxSeqInfNew->horizontal_size, pSyntaxSeqInfNew->vertical_size,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			//pCtx->FspPartitionOK = 0;
			return AVS_FALSE;
		}
        PicWidth  = pSyntaxSeqInfNew->horizontal_size;
        PicHeight = pSyntaxSeqInfNew->vertical_size;	
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}
	

    memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
	FspInstCfg.s32DecFsWidth        = (pSyntaxSeqInfNew->horizontal_size+15)/16*16; //内存分配对齐
	FspInstCfg.s32DecFsHeight       = (pSyntaxSeqInfNew->vertical_size+15)/16*16;
	FspInstCfg.s32DispFsWidth       = pSyntaxSeqInfNew->horizontal_size;
	FspInstCfg.s32DispFsHeight      = pSyntaxSeqInfNew->vertical_size;
	FspInstCfg.s32ExpectedDecFsNum  = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: DecFsNum;
	FspInstCfg.s32ExpectedDispFsNum = DispFsNum;
	FspInstCfg.s32ExpectedPmvNum    = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvNum;
	
	/* 配置FSP实例，并分割帧存 */
 	if (FSP_OK == FSP_ConfigInstance(pCtx->ChanID, &FspInstCfg))
 	{
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
			        pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
        if(FSP_WAIT_ARRANGE == Ret)
        {
            return AVS_WAIT;
        }
		else if (Ret != FSP_OK)
		{
		    dprint(PRN_FATAL, "ERROR: partition fs memory fail!\n");
            // 分割帧存失败，返回
            return AVS_FALSE;
		}
	}
	else
	{
	    dprint(PRN_FATAL, "ERROR: FSP_ConfigInstance fail!\n");
	    return AVS_FALSE;
	}
	
    pCtx->FspPartitionOK = 1;
	
    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_GetStreamInf
功能描述  : 对码流信息信息进行检查和处理，生成解码所需要的各种码流和配置信息
输入参数  : AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月19日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_GetStreamInf(AVS_CTX_S *pCtx)
{
	UINT32 i;
    AVS_CODECINF *pCodecInf = &pCtx->CodecInfo;
    AVS_SYNTAX *pCurSyn = &pCodecInf->Syntax;
	IMAGE *pImage;
    AVS_VDMCFG* p_AvsCfg;
    SINT32 ret = AVS_FALSE;

    p_AvsCfg = &pCtx->AvsCfg;
    /*序列级信息处理*/
	pCodecInf->sample_precision = pCurSyn->syn_seq.sample_precision;
 
    if ((pCodecInf->SizeChanged == AVS_TRUE) || (1 != pCtx->FspPartitionOK ))
    {
        dprint(PRN_DBG, "size change\n");
        /*图像大小发生变化,重新划分帧存结构*/
        pCodecInf->PicMbWidth = (pCurSyn->syn_seq.horizontal_size + 15) / 16;
        if (1 == pCurSyn->syn_seq.progressive_sequence)
        {
            pCodecInf->PicMbHeight = (pCurSyn->syn_seq.vertical_size + 15) / 16;
        }
        else
        {
            pCodecInf->PicMbHeight = (pCurSyn->syn_seq.vertical_size + 31) / 32 * 2;
        }

        if ((pCodecInf->PicMbWidth > MAX_IMG_WIDTH_IN_MB) || (pCodecInf->PicMbHeight > MAX_IMG_HEIGHT_IN_MB))
        {
            dprint(PRN_PIC, "MbWidth = %d, MbHeight = %d, don't support!\n", pCodecInf->PicMbWidth,
                   pCodecInf->PicMbHeight);
            return AVS_FALSE;
        }

        AVS_CLEARREFFLAG;
        AVS_CLEARREFNUM;
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
                    
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (pCtx->FspPartitionOK == 0)
            {
                ResetVoQueue(&pCtx->ImageQue);
            }
        }
        else
        {    
            ResetVoQueue(&pCtx->ImageQue); 
        }
		
        /*图像大小变化后，参考帧列表需要清零*/
        pCodecInf->pRef[0] =
        pCodecInf->pRef[1] =
        pCodecInf->pRef[2] =
        pCodecInf->pCurFrm = &(pCodecInf->ZeroFrm);
        pCodecInf->SizeChanged = 0;
		ret = AVS_AllocateVHB(pCtx);
        if(AVS_WAIT == ret)
        {
            return AVS_WAIT;
        }
        else if ( ret == AVS_FALSE)
        {
            dprint(PRN_ERROR, "ERROR: allocate vhb\n");        
            return AVS_FALSE;
        }
        else
        {
            pCodecInf->SizeChanged = AVS_FALSE;
        }
    }
    pCodecInf->chroma_format = pCurSyn->syn_seq.chroma_format;
    /*图像级信息处理*/
    /*获取帧存  */
	pCodecInf->pCurFrm->PicStruct = pCurSyn->syn_pic.picture_structure;
    if (AVS_GetImageBuffer(pCtx) == AVS_FALSE)
    {
        dprint(PRN_ERROR, "ERROR: get img buf err\n");   
        return AVS_FALSE;
    }
    pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
     
	pImage->PTS = pCtx->pstExtraData->pts;
	pImage->Usertag = pCtx->pstExtraData->Usertag;
	pImage->DispTime = pCtx->pstExtraData->DispTime;
   	pImage->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
	pImage->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
   	pImage->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
	pImage->GopNum = pCtx->pstExtraData->GopNum;

	pImage->is_fld_save = (0==pCurSyn->syn_pic.picture_structure);
    pCtx->pstExtraData->pts = -1;
	dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImage->PTS, pImage->Usertag);

    pCodecInf->pCurFrm->pic_distance = pCurSyn->syn_pic.picture_distance;
    pCodecInf->pCurFrm->PicStruct = pCurSyn->syn_pic.picture_structure;
    pCodecInf->pCurFrm->PicCodingType = pCurSyn->syn_pic.derived_pic_coding_type;
    //pCodecInf->pCurFrm->TopFldFirst = pCurSyn->syn_pic.top_field_first;
	pCodecInf->pCurFrm->TopFldFirst = (0 == pCurSyn->syn_pic.picture_structure) ? 1 : pCurSyn->syn_pic.top_field_first;
    if ((0 == pCurSyn->syn_pic.picture_structure)
       && (pCurSyn->syn_pic.derived_pic_coding_type == I_PICTURE))
    {
        /*IP-pair field picture should ref to itself*/
		FSP_SetRef(pCtx->ChanID, pCodecInf->pCurFrm->FspID, 1);
        /* 为了参考自己，必须提前做参考维护 */
        if (pCodecInf->pRef[2] != &(pCodecInf->ZeroFrm))
        {            
			FSP_SetRef(pCtx->ChanID, pCodecInf->pRef[2]->FspID, 0);
        }
        pCodecInf->pRef[2] = pCodecInf->pRef[1];
        pCodecInf->pRef[1] = pCodecInf->pRef[0];
        pCodecInf->pRef[0] = pCodecInf->pCurFrm;
    }
    pCodecInf->b_filed_enhanced_flag = pCurSyn->syn_pic.b_filed_enhanced_flag;
    AVS_UpdatePmvTable(pCodecInf);

    /*下行消息信息*/
    p_AvsCfg->mbamt_to_dec = pCodecInf->PicMbWidth * pCodecInf->PicMbHeight - 1;
#ifdef VFMW_VDH_V400R004_SUPPORT
    p_AvsCfg->mv_output_en = 1;
#else
	p_AvsCfg->mv_output_en = 0;
#endif
	p_AvsCfg->load_qmatrix_flag = 1;
    p_AvsCfg->ddr_stride = (pCodecInf->DDR_Stride / 64); //AVS_MSG_STRIDE;
    p_AvsCfg->video_standard = STD_AVS;
 
    //p_AvsCfg->ystaddr_1d = pCodecInf->pCurFrm->img.luma_phy_addr;
    p_AvsCfg->pic_width_in_mb  = pCodecInf->PicMbWidth;
    p_AvsCfg->pic_height_in_mb = pCodecInf->PicMbHeight;
    p_AvsCfg->sample_precision = pCodecInf->sample_precision;
    p_AvsCfg->chroma_format = pCodecInf->chroma_format;
    p_AvsCfg->no_fwd_ref_flag = pCurSyn->syn_pic.no_forward_reference_flag;
    p_AvsCfg->pic_ref_flag = pCurSyn->syn_pic.picture_reference_flag;
    p_AvsCfg->ad_pred_mode_disable = pCurSyn->syn_pic.advanced_pred_mode_disable;
    p_AvsCfg->skip_mode_flag = pCurSyn->syn_pic.skip_mode_flag;
    p_AvsCfg->pic_qp = pCurSyn->syn_pic.picture_qp;
    p_AvsCfg->fix_qp = pCurSyn->syn_pic.fixed_picture_qp;
    p_AvsCfg->repeat_first_field = pCurSyn->syn_pic.repeat_first_field;
    p_AvsCfg->top_field_first   = pCurSyn->syn_pic.top_field_first;
    p_AvsCfg->pic_coding_type   = pCurSyn->syn_pic.derived_pic_coding_type;
    p_AvsCfg->picture_structure = pCurSyn->syn_pic.picture_structure==0?1:3;
    p_AvsCfg->progressive_frame = pCurSyn->syn_pic.progressive_frame;
    p_AvsCfg->beta_offset = pCurSyn->syn_pic.beta_offset;
    p_AvsCfg->alpha_c_offset = pCurSyn->syn_pic.alpha_c_offset;
    p_AvsCfg->loop_flt_para_flag = pCurSyn->syn_pic.loop_filter_parameter_flag;
    p_AvsCfg->loop_flt_disable = pCurSyn->syn_pic.loop_filter_disable;
    p_AvsCfg->weighting_quant_flag = pCurSyn->syn_pic.weighting_quant_flag;
    p_AvsCfg->chroma_quant_param_disable = pCurSyn->syn_pic.chroma_quant_param_disable;
    p_AvsCfg->chroma_quant_param_delta_u = pCurSyn->syn_pic.chroma_quant_param_delta_u;
    p_AvsCfg->chroma_quant_param_delta_v = pCurSyn->syn_pic.chroma_quant_param_delta_v;
    for (i=0; i<64; i++)
    {
         p_AvsCfg->cur_wq_matrix[i] = pCurSyn->syn_pic.cur_wq_matrix[i];
    }
    p_AvsCfg->aec_enable = pCurSyn->syn_pic.aec_enable;
    p_AvsCfg->b_filed_enhanced_flag = pCurSyn->syn_pic.b_filed_enhanced_flag;
    p_AvsCfg->p_filed_enhanced_flag = pCurSyn->syn_pic.p_filed_enhanced_flag;
	if (B_PICTURE == pCodecInf->pCurFrm->PicCodingType)
    {
    	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
        p_AvsCfg->bwd_picture_structure = pCodecInf->pRef[0]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->bwd_top_field_first = pCodecInf->pRef[0]->TopFldFirst;		
        p_AvsCfg->bwd_address_0 = pImage->luma_phy_addr;
		
		pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[1]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
        p_AvsCfg->fwd_picture_structure_0 = pCodecInf->pRef[1]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->fwd_top_field_first_0 = pCodecInf->pRef[1]->TopFldFirst;		
        p_AvsCfg->fwd_address_0 = pImage->luma_phy_addr;

		pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[2]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
        p_AvsCfg->fwd_picture_structure_1 = pCodecInf->pRef[2]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->fwd_top_field_first_1 = pCodecInf->pRef[2]->TopFldFirst;		
        p_AvsCfg->fwd_address_1 = pImage->luma_phy_addr;
    }
    else
    {
    	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
        p_AvsCfg->bwd_picture_structure = pCodecInf->pRef[0]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->bwd_top_field_first = pCodecInf->pRef[0]->TopFldFirst;
        p_AvsCfg->bwd_address_0 = pImage->luma_phy_addr;		
        p_AvsCfg->fwd_picture_structure_0 = pCodecInf->pRef[0]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->fwd_top_field_first_0 = pCodecInf->pRef[0]->TopFldFirst;
        p_AvsCfg->fwd_address_0 = pImage->luma_phy_addr;

		pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[1]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
        p_AvsCfg->fwd_picture_structure_1 = pCodecInf->pRef[1]->PicStruct == 1 ? 3 : 1;
        p_AvsCfg->fwd_top_field_first_1 = pCodecInf->pRef[1]->TopFldFirst;
        p_AvsCfg->fwd_address_1 = pImage->luma_phy_addr;
    }

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
	p_AvsCfg->ref_pic_type0 = pImage->is_fld_save;  //bwd

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[1]->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
	p_AvsCfg->ref_pic_type1 = pImage->is_fld_save;  //fwd0

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[2]->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
	p_AvsCfg->ref_pic_type2 = pImage->is_fld_save;  //fwd1
		
	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);
	p_AvsCfg->ref_pic_type3 = pImage->is_fld_save;  //curr
	p_AvsCfg->ystaddr_1d = pImage->luma_phy_addr;
	//pCur = FSP_GetLogicFs(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
	p_AvsCfg->rcn_address = pImage->luma_2d_phy_addr;

    p_AvsCfg->col_pic_struct = pCodecInf->pRef[0]->PicStruct ==1? 3:1;
    p_AvsCfg->col_pic_type = (pCodecInf->pRef[0]->PicCodingType == I_PICTURE ? 0 : 1);
    p_AvsCfg->current_pmv_addr = FSP_GetPmvAddr(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
	p_AvsCfg->colpic_mv_addr = FSP_GetPmvAddr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);


    {
        SINT32 iCnt, MvENum, DirNum, SymNum, BBlkNum;
        MvENum  = 0;
        DirNum  = 0;
        SymNum  = 0;
        BBlkNum = 0;
        switch (pCurSyn->syn_pic.derived_pic_coding_type)
        {
            case P_PICTURE:
                MvENum = 32;
                break;
            case B_PICTURE:
                MvENum  = 16;
                DirNum  = 8;
                BBlkNum = 4;
                SymNum  = 4;
                break;
            default:
                MvENum = 32;
                break;
        }

        for (iCnt = 0; iCnt < MvENum; iCnt++)
        {
            p_AvsCfg->pmvtable[iCnt] = pCodecInf->MvEScale[iCnt] & 0x3ffff;
        }

        for (iCnt = 0; iCnt < DirNum; iCnt++)
        {
            p_AvsCfg->pmvtable[16 + iCnt] = pCodecInf->DirectScale[iCnt] & 0x7fff;
        }

        for (iCnt = 0; iCnt < BBlkNum; iCnt++)
        {
            p_AvsCfg->pmvtable[24 + iCnt] =
                (pCodecInf->BBlkDist[iCnt * 2] & 0x1ff) | ((pCodecInf->BBlkDist[iCnt * 2 + 1] & 0x1ff) << 9);
        }

        for (iCnt = 0; iCnt < SymNum; iCnt++)
        {
            p_AvsCfg->pmvtable[28 + iCnt] = pCodecInf->SymScale[iCnt] & 0x3ffff;
        }
    }
	p_AvsCfg->pmv_colmb_addr = pCodecInf->pmv_colmb_buf_phyaddr;
    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_PrepareDecode
功能描述  : 为开始解码整理码流信息和解码器资源
输入参数  : AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月20日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_PrepareDecode(AVS_CTX_S *pCtx)
{
    SINT32 ret = AVS_FALSE;

    ret = AVS_GetStreamInf(pCtx);
    if(AVS_WAIT == ret)
    {
        return ret;
    }
    else if (ret == AVS_FALSE)
    {
        /*获取码流信息失败，返回失败，准备异常处理*/
        return AVS_FALSE;
    }

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVS_StartDecode
功能描述  : 根据已知信息配置启动VDM
输入参数  : AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月20日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_StartDecode(AVS_CTX_S *pCtx)
{
    SINT32 iCnt;
    AVS_DEC_PARAM_S *pAvsDecParam = NULL;
	FSP_LOGIC_FS_S* pLogic;
	STREAM_SEG_PACKET_S *pSegMan;
    AVS_VDMCFG* p_AvsCfg;

    p_AvsCfg = &pCtx->AvsCfg;
    pAvsDecParam = &pCtx->AvsDecParam;
	//pSegMan = pAvsDecParam->pSegMan; // Save pSegman
	pSegMan = &pCtx->pstExtraData->stSegPacket;

//    memset( pAvsDecParam, 0, sizeof(AVS_DEC_PARAM_S) );
	pAvsDecParam->mbamt_to_dec         = p_AvsCfg->mbamt_to_dec;
	pAvsDecParam->mv_output_en         = p_AvsCfg->mv_output_en;
	pAvsDecParam->load_qmatrix_flag    = p_AvsCfg->load_qmatrix_flag;
	pAvsDecParam->ddr_stride           = p_AvsCfg->ddr_stride;
	pAvsDecParam->video_standard       = p_AvsCfg->video_standard;
	pAvsDecParam->tab_base_addr        = p_AvsCfg->tab_base_addr;
	pAvsDecParam->StreamBaseAddr       = p_AvsCfg->stream_base_addr;
	pAvsDecParam->ystaddr_1d           = p_AvsCfg->ystaddr_1d;
    pAvsDecParam->StreamPhyAddr[0]     = p_AvsCfg->bit_stream_address_0;
    pAvsDecParam->StreamPhyAddr[1]     = p_AvsCfg->bit_stream_address_1;
    pAvsDecParam->StreamBitOffset[0]   = p_AvsCfg->bit_offset_0;
    pAvsDecParam->StreamBitOffset[1]   = p_AvsCfg->bit_offset_1;
    pAvsDecParam->StreamLength[0]      = p_AvsCfg->bit_len_0;
    pAvsDecParam->StreamLength[1]      = p_AvsCfg->bit_len_1;
    pAvsDecParam->PicWidthInMb       = p_AvsCfg->pic_width_in_mb;
    pAvsDecParam->PicHeightInMb      = p_AvsCfg->pic_height_in_mb;
	pAvsDecParam->SamplePrecision      = p_AvsCfg->sample_precision;
	pAvsDecParam->ChromaFormat         = p_AvsCfg->chroma_format;
    pAvsDecParam->PicCodingType      = p_AvsCfg->pic_coding_type;
    pAvsDecParam->PicStruct          = p_AvsCfg->picture_structure;
    pAvsDecParam->NoFwdRefFlag       = p_AvsCfg->no_fwd_ref_flag;
    pAvsDecParam->PicRefFlag         = p_AvsCfg->pic_ref_flag;
    pAvsDecParam->SkipModeFlag       = p_AvsCfg->skip_mode_flag;
    pAvsDecParam->PicQuant           = p_AvsCfg->pic_qp;
    pAvsDecParam->FixQPFlag          = p_AvsCfg->fix_qp;
    pAvsDecParam->RepeatFirstField   = p_AvsCfg->repeat_first_field;
    pAvsDecParam->TopFieldFirst      = p_AvsCfg->top_field_first;
    pAvsDecParam->ProgrsvFrame       = p_AvsCfg->progressive_frame;
    pAvsDecParam->BetaOffset         = p_AvsCfg->beta_offset;
    pAvsDecParam->AlphaOffset        = p_AvsCfg->alpha_c_offset;
    pAvsDecParam->LoopFiltParamFlag  = p_AvsCfg->loop_flt_para_flag;
    pAvsDecParam->LoopFiltDisable    = p_AvsCfg->loop_flt_disable;
    pAvsDecParam->ColPicStruct       = p_AvsCfg->col_pic_struct;
    pAvsDecParam->AdvPredModeDisable = p_AvsCfg->ad_pred_mode_disable;
    pAvsDecParam->BwdTopFieldFirst   = p_AvsCfg->bwd_top_field_first;
    pAvsDecParam->BwdPicStruct       = p_AvsCfg->bwd_picture_structure;
    pAvsDecParam->FwdTopFieldFirst0  = p_AvsCfg->fwd_top_field_first_0;
    pAvsDecParam->FwdPicStruct0      = p_AvsCfg->fwd_picture_structure_0;
    pAvsDecParam->FwdTopFieldFirst1  = p_AvsCfg->fwd_top_field_first_1;
    pAvsDecParam->FwdPicStruct1      = p_AvsCfg->fwd_picture_structure_1;
    pAvsDecParam->ColPicType         = p_AvsCfg->col_pic_type;
    pAvsDecParam->BwdRefPicAddr      = p_AvsCfg->bwd_address_0;
    pAvsDecParam->FwdRefPic0Addr     = p_AvsCfg->fwd_address_0;
    pAvsDecParam->FwdRefPic1Addr     = p_AvsCfg->fwd_address_1;
    
    pAvsDecParam->CurPmvAddr         = p_AvsCfg->current_pmv_addr;
    pAvsDecParam->ColPmvAddr         = p_AvsCfg->colpic_mv_addr;
	pLogic = FSP_GetLogicFs(pCtx->ChanID, pCtx->CodecInfo.pCurFrm->FspID);
    if (NULL == pLogic)
    {
        dprint(PRN_FATAL, "line: %d, pImage is NULL!\n", __LINE__);
        return AVS_FALSE;
    }
    
    pAvsDecParam->VahbStride         = pLogic->pstDispOutFs->Stride;
	pAvsDecParam->CurPicAddr         = p_AvsCfg->ystaddr_1d;
	pAvsDecParam->rcn_address        = p_AvsCfg->rcn_address;
    pAvsDecParam->pmv_colmb_addr              = p_AvsCfg->pmv_colmb_addr;
    pAvsDecParam->weighting_quant_flag        = p_AvsCfg->weighting_quant_flag;
    pAvsDecParam->chroma_quant_param_disable  = p_AvsCfg->chroma_quant_param_disable;
    pAvsDecParam->chroma_quant_param_delta_u  = p_AvsCfg->chroma_quant_param_delta_u;
    pAvsDecParam->chroma_quant_param_delta_v  = p_AvsCfg->chroma_quant_param_delta_v;
    pAvsDecParam->aec_enable                  = p_AvsCfg->aec_enable;
	pAvsDecParam->p_filed_enhanced_flag       = p_AvsCfg->p_filed_enhanced_flag;
    pAvsDecParam->b_filed_enhanced_flag       = p_AvsCfg->b_filed_enhanced_flag;
    /* WQ Matrix */
    for(iCnt = 0; iCnt < 64; iCnt++)
    {
    	pAvsDecParam->cur_wq_matrix[iCnt]     = p_AvsCfg->cur_wq_matrix[iCnt];
   	}
	pAvsDecParam->RefPicType0 = p_AvsCfg->ref_pic_type0;  //bwd
    pAvsDecParam->RefPicType1 = p_AvsCfg->ref_pic_type1;  //fwd0
    pAvsDecParam->RefPicType2 = p_AvsCfg->ref_pic_type2;  //fwd1
    pAvsDecParam->RefPicType3 = p_AvsCfg->ref_pic_type3;  //curr

#if 0
	//pAvsDecParam->pSegMan = pSegMan; // restore pSegMan
    for(iCnt=0; iCnt<pSegMan->SegNum; iCnt++)
    {
        pAvsDecParam->SSeg[iCnt].PhyAddr = pSegMan->StreamSeg[iCnt].PhyAddr;
        pAvsDecParam->SSeg[iCnt].VirAddr = pSegMan->StreamSeg[iCnt].VirAddr;
        pAvsDecParam->SSeg[iCnt].LenInByte = pSegMan->StreamSeg[iCnt].LenInByte;
        pAvsDecParam->SSeg[iCnt].IsLastSeg = pSegMan->StreamSeg[iCnt].IsLastSeg;		
    }
	pAvsDecParam->SegNum = pSegMan->SegNum;
#endif    
	
    for (iCnt = 0; iCnt < 32; iCnt++)
    {
        pAvsDecParam->PmvConfigTab[iCnt] = p_AvsCfg->pmvtable[iCnt];
    }
    pCtx->CodecInfo.PicCnt++;
	
    pCtx->pAvsDecParam = &pCtx->AvsDecParam;
    
    if (1 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((NULL != pCtx->pAvsDecParam) && (B_PICTURE == pCtx->CodecInfo.pCurFrm->PicCodingType))
        {
            pCtx->pAvsDecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID,  pCtx->CodecInfo.pCurFrm->FspID,  0);
            return AVS_FALSE;
        }
    }
    else if (2 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((pCtx->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pCtx->pAvsDecParam) && 
            (B_PICTURE ==pCtx->CodecInfo.pCurFrm->PicCodingType))
        {
            pCtx->pAvsDecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID,  pCtx->CodecInfo.pCurFrm->FspID,  0);
            pCtx->pstExtraData->stDisParams.s32DisNums--;
            return AVS_FALSE;
        }
    }
    
    pCtx->pAvsDecParam->Compress_en = pCtx->pstExtraData->s32Compress_en;

    /*
    pCtx->pAvsDecParam = &pCtx->AvsDecParam;
    pCtx->pAvsDecParam->Compress_en = pCtx->pstExtraData->s32Compress_en;
    */
    return AVS_TRUE;
}

VOID AVS_SetImgFormat(AVS_CTX_S *pCtx)
{
    UINT32 codtype, csp, vfmt, sfmt, fldflg, fldfst=0, dar;
	AVS_CODECINF *pCodecInf = &(pCtx->CodecInfo);
	IMAGE *pImage;

    AVS_SYNTAX *pCurSyn = &pCodecInf->Syntax;

    codtype = pCurSyn->syn_pic.derived_pic_coding_type;
    csp = 0;
    vfmt = pCurSyn->syn_sdext.video_format;
    fldflg = 3;
    sfmt = !((1 == pCurSyn->syn_seq.progressive_sequence) || (1 == pCurSyn->syn_pic.progressive_frame));
    fldfst = pCurSyn->syn_pic.top_field_first;  //非逐行的帧编码场序由码流确定

    switch (pCurSyn->syn_seq.aspect_ratio)
    {
        case 1:
            dar = DAR_IMG_SIZE;
            break;
        case 2:
            dar = DAR_4_3;
            break;
        case 3:
            dar = DAR_16_9;
            break;
        case 4:
            dar = DAR_221_100;
			break;
        default:
            dar = DAR_UNKNOWN;
            break;
    }

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
    if (NULL == pImage)
    {
        dprint(PRN_FATAL, "line: %d pImage is null\n",__LINE__);
        return;
    }

	pImage->format = ((dar&7)<<14)|((fldfst&0x3)<<12)|((fldflg&3)<<10)|((sfmt&3)<<8)|((vfmt&3)<<5)|((csp&7)<<2)|(codtype&3);
    pImage->error_level = pCodecInf->ErrRatio;
    pImage->top_fld_type = codtype&3;
    pImage->bottom_fld_type = codtype&3;

	SetAspectRatio(pImage, (VDEC_DAR_E)dar);

    //pImage->image_width=pCurSyn->syn_seq.horizontal_size;
    //pImage->image_height=pCurSyn->syn_seq.vertical_size;
    pImage->image_width=(pCurSyn->syn_seq.horizontal_size+15)/16*16;    //解码宽高对齐
    pImage->image_height=(pCurSyn->syn_seq.vertical_size+15)/16*16;
    if ((pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
	{
	    SINT32  Stride = pImage->image_stride;//(pImg->image_width + 63) & (~63);
		SINT32  ChromOfst = Stride * ((pImage->image_height + 15)/16)*16;

		pImage->chrom_phy_addr = pImage->luma_phy_addr + ChromOfst;			
	    pImage->top_luma_phy_addr  = pImage->luma_phy_addr;
	    pImage->top_chrom_phy_addr = pImage->top_luma_phy_addr + ChromOfst;
	    pImage->btm_luma_phy_addr  = pImage->top_luma_phy_addr + Stride;
	    pImage->btm_chrom_phy_addr = pImage->top_chrom_phy_addr + Stride;
	    pImage->luma_2d_phy_addr   = pImage->luma_phy_addr;
		pImage->chrom_2d_phy_addr  = pImage->top_chrom_phy_addr;
	}	
}


/*****************************************************************************
函 数 名  : AVS_GetImageBuffer
功能描述  : 获取一个帧存空间
输入参数  : AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月20日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_GetImageBuffer(AVS_CTX_S *pCtx)
{
    SINT32 ret = AVS_FALSE;
	AVS_CODECINF *pCodecInf;
	FSP_LOGIC_FS_S *pLf;

    pCodecInf = &pCtx->CodecInfo;		
	if (B_PICTURE != pCtx->SyntaxNew.syn_pic.derived_pic_coding_type)			
	{
		pCodecInf->pCurFrm = &(pCodecInf->FrameObj[pCodecInf->CurFrameObjId]);	
		pCodecInf->CurFrameObjId++;
		pCodecInf->CurFrameObjId = pCodecInf->CurFrameObjId%4;
	}
	else
	{
		pCodecInf->pCurFrm = &(pCodecInf->FrameObj[4]);	
	}

    pCodecInf->pCurFrm->FspID = FSP_NewLogicFs(pCtx->ChanID, 1);

	if (pCodecInf->pCurFrm->FspID < 0)
	{
        /* 获取帧存失败 */
		dprint(PRN_FATAL,"ERROR: get frame store fail!\n");
		AVS_CLEARREFFLAG;
		AVS_CLEARREFNUM;		
		#if 0
		ResetVoQueue(&pCtx->ImageQue);
		FSP_EmptyInstance(pCtx->ChanID);
		#else
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		#endif
		
		return 0;
	}
	else
	{
		pLf = FSP_GetLogicFs(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
        if (NULL == pLf)
        {
            dprint(PRN_FATAL, "line: %d, pImage is NULL!\n", __LINE__);
            return AVS_FALSE;
        }

		dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pCodecInf->pCurFrm->FspID);
		if ( (NULL!=pLf->pstDecodeFs) && (NULL!=pLf->pstDispOutFs) && (NULL!=pLf->pstTfOutFs) )
		{
	        dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
        }
		pLf->stDispImg.error_level = 0;	
	}
    ret = AVS_TRUE;

	return ret;

}

/*****************************************************************************
函 数 名  : AVS_OutputOneFrame
功能描述  : 输出重构图像
输入参数  : FRAME_OBJ *pOutput
AVS_CODECINF *pCodecInf
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月20日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVS_OutputOneFrame(FRAME_OBJ *pOutput, AVS_CTX_S *pCtx)
{
	IMAGE *pImage = NULL;

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pOutput->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);

	FSP_SetDisplay(pCtx->ChanID, pOutput->FspID, 1);
	if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_AVS, pCtx, &pCtx->ImageQue, pImage))
    {
	    FSP_SetDisplay(pCtx->ChanID, pOutput->FspID, 0);
		dprint(PRN_ERROR, "ERROR: AVS_OutputOneFrame is err(%d)\n", pOutput->FspID );
        return AVS_FALSE;
    }

    return AVS_TRUE;
}


SINT32 AVS_UpdateTableIdx2Dist(AVS_CODECINF *pCodecInf)
{
    if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
    {
        /*frame structure picture*/
        if (P_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            pCodecInf->Idx2Dist[0] = pCodecInf->pRef[0]->pic_distance * 2;
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[1])
            {
                pCodecInf->Idx2Dist[1] = pCodecInf->pRef[1]->pic_distance * 2;
            }
        }

        if (B_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[1])
            {
                pCodecInf->Idx2Dist[0] = pCodecInf->pRef[1]->pic_distance * 2;/*forward*/
            }

            pCodecInf->Idx2Dist[2] = pCodecInf->pRef[0]->pic_distance * 2;/*backward*/
        }
    }
    else
    {
        /*field structure picture*/
        if (I_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            pCodecInf->Idx2Dist[4] = pCodecInf->pRef[0]->pic_distance * 2;
        }

        if (P_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            /*top field (ref fld 3 to 0)*/
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[1])
            {
                pCodecInf->Idx2Dist[3] = pCodecInf->pRef[1]->pic_distance * 2;
            }

            pCodecInf->Idx2Dist[2] = pCodecInf->Idx2Dist[3] + 1;
            pCodecInf->Idx2Dist[1] = pCodecInf->pRef[0]->pic_distance * 2;
            pCodecInf->Idx2Dist[0] = pCodecInf->Idx2Dist[1] + 1;

            /*bottom field (ref fld 3 to 0)*/
            pCodecInf->Idx2Dist[7] = pCodecInf->Idx2Dist[2];
            pCodecInf->Idx2Dist[6] = pCodecInf->Idx2Dist[1];
            pCodecInf->Idx2Dist[5] = pCodecInf->Idx2Dist[0];
            pCodecInf->Idx2Dist[4] = pCodecInf->pCurFrm->pic_distance * 2;
        }

        if (B_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            /*top field*/
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[1])
            {
                pCodecInf->Idx2Dist[1] = pCodecInf->pRef[1]->pic_distance * 2;
            }

            pCodecInf->Idx2Dist[0] = pCodecInf->Idx2Dist[1] + 1;
            pCodecInf->Idx2Dist[2] = pCodecInf->pRef[0]->pic_distance * 2;
            pCodecInf->Idx2Dist[3] = pCodecInf->Idx2Dist[2] + 1;

            /*bottom field*/
            pCodecInf->Idx2Dist[7] = pCodecInf->Idx2Dist[3];
            pCodecInf->Idx2Dist[6] = pCodecInf->Idx2Dist[2];
            pCodecInf->Idx2Dist[5] = pCodecInf->Idx2Dist[1];
            pCodecInf->Idx2Dist[4] = pCodecInf->Idx2Dist[0];
        }
    }

    return AVS_TRUE;
}


SINT32 AVS_UpdateTableMvEScale(AVS_CODECINF *pCodecInf)
{
    SINT32 CurDistIdx, CurBlkDist, NeiBlkDist;
    SINT32 CurFld, CurRefIdx, NeiRefIdx;

    CurDistIdx = 0;
    CurBlkDist = 0;
    NeiBlkDist = 0;
    CurFld = 0;
    CurRefIdx = 0;
    NeiRefIdx = 0;

    if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
    {
        /*frame structure picture*/
        CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2;
        if (P_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            for (CurRefIdx = 0; CurRefIdx < 2; CurRefIdx++)
            {
                for (NeiRefIdx = 0; NeiRefIdx < 2; NeiRefIdx++)
                {
                    CurBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[CurRefIdx]) + 512) & 511;
                    NeiBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[NeiRefIdx]) + 512) & 511;
                    if (0 == NeiBlkDist)
                    {
                        NeiBlkDist = 512;
                    }

                    pCodecInf->MvEScale[CurRefIdx * 4 + NeiRefIdx] = (512 / NeiBlkDist) * CurBlkDist;
                }
            }
        }

        if (B_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            CurBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[0]) + 512) & 511;
            NeiBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[0]) + 512) & 511;
            if (0 == NeiBlkDist)
            {
                NeiBlkDist = 512;
            }

            pCodecInf->MvEScale[0] = (512 / NeiBlkDist) * CurBlkDist;

            CurBlkDist = ((pCodecInf->Idx2Dist[2] - CurDistIdx) + 512) & 511;
            NeiBlkDist = ((pCodecInf->Idx2Dist[2] - CurDistIdx) + 512) & 511;
            if (0 == NeiBlkDist)
            {
                NeiBlkDist = 512;
            }

            pCodecInf->MvEScale[4] = (512 / NeiBlkDist) * CurBlkDist;
        }
    }
    else
    {
        /*field structure picture*/
        if (I_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            /*table MvEScale*/
            pCodecInf->MvEScale[16] = 512;
        }

        if (P_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            for (CurFld = 0; CurFld < 2; CurFld++)
            {
                CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2 + CurFld;
                for (CurRefIdx = 0; CurRefIdx < 4; CurRefIdx++)
                {
                    for (NeiRefIdx = 0; NeiRefIdx < 4; NeiRefIdx++)
                    {
                        CurBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[CurFld * 4 + CurRefIdx]) + 512) & 511;
                        NeiBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[CurFld * 4 + NeiRefIdx]) + 512) & 511;
                        if (0 == NeiBlkDist)
                        {
                            NeiBlkDist = 512;
                        }

                        pCodecInf->MvEScale[CurFld * 16 + CurRefIdx * 4 + NeiRefIdx] = (512 / NeiBlkDist) * CurBlkDist;
                    }
                }
            }
        }

        if (B_PICTURE == pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
        {
            for (CurFld = 0; CurFld < 2; CurFld++)
            {
                CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2 + CurFld;

                //forward
                for (CurRefIdx = 0; CurRefIdx < 2; CurRefIdx++)
                {
                    for (NeiRefIdx = 0; NeiRefIdx < 2; NeiRefIdx++)
                    {
                        CurBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[CurFld * 4 + CurRefIdx]) + 512) & 511;
                        NeiBlkDist = ((CurDistIdx - pCodecInf->Idx2Dist[CurFld * 4 + NeiRefIdx]) + 512) & 511;
                        if (0 == NeiBlkDist)
                        {
                            NeiBlkDist = 512;
                        }

                        pCodecInf->MvEScale[CurFld * 8 + CurRefIdx * 2 + NeiRefIdx] = (512 / NeiBlkDist) * CurBlkDist;
                    }
                }

                //backward
                for (CurRefIdx = 0; CurRefIdx < 2; CurRefIdx++)
                {
                    for (NeiRefIdx = 0; NeiRefIdx < 2; NeiRefIdx++)
                    {
                        CurBlkDist = ((pCodecInf->Idx2Dist[CurFld * 4 + 2 + CurRefIdx] - CurDistIdx) + 512) & 511;
                        NeiBlkDist = ((pCodecInf->Idx2Dist[CurFld * 4 + 2 + NeiRefIdx] - CurDistIdx) + 512) & 511;
                        if (0 == NeiBlkDist)
                        {
                            NeiBlkDist = 512;
                        }
                        pCodecInf->MvEScale[CurFld*8+4+CurRefIdx*2+NeiRefIdx] = (512/NeiBlkDist)*CurBlkDist;
                    }
                }
            }
        }
    }

    return AVS_TRUE;
}

SINT32 AVS_UpdateTableDirectScale(AVS_CODECINF *pCodecInf)
{
    SINT32 ColRefIdx, ColRefDistIdx, ColDistIdx, ColBlkDist;

    ColRefIdx = 0;
    ColRefDistIdx = 0;
    ColDistIdx = 0;
    ColBlkDist = 0;

    if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
    {
        /*current is frame picture*/
        ColDistIdx = pCodecInf->pRef[0]->pic_distance * 2;
        for (ColRefIdx = 0; ColRefIdx < 2; ColRefIdx++)
        {
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[ColRefIdx + 1])
            {
                ColRefDistIdx = pCodecInf->pRef[ColRefIdx + 1]->pic_distance * 2;
                ColBlkDist = ((ColDistIdx - ColRefDistIdx) + 512) & 511;
                if (0 == ColBlkDist)
                {
                    pCodecInf->DirectScale[ColRefIdx] = 16384 / 512;
                }
                else
                {
                    pCodecInf->DirectScale[ColRefIdx] = 16384 / ColBlkDist;
                }
            }
        }
    }
    else
    {
        /*current is field picture*/
        /*top field*/
        ColDistIdx = pCodecInf->pRef[0]->pic_distance * 2;
        for (ColRefIdx = 0; ColRefIdx < 4; ColRefIdx++)
        {
            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[(ColRefIdx / 2) + 1])
            {
                ColRefDistIdx = pCodecInf->pRef[(ColRefIdx / 2) + 1]->pic_distance * 2 + ((ColRefIdx + 1) & 1);
                ColBlkDist = ((ColDistIdx - ColRefDistIdx) + 512) & 511;
                if (0 == ColBlkDist)
                {
                    pCodecInf->DirectScale[ColRefIdx] = 16384 / 512;
                }
                else
                {
                    pCodecInf->DirectScale[ColRefIdx] = 16384 / ColBlkDist;
                }
            }
        }

        /*bottom field*/
        //ColDistIdx = pCodecInf->pRef[0]->pic_distance * 2 + 1;
    	if(pCodecInf->b_filed_enhanced_flag)
    	{
            ColDistIdx = pCodecInf->pRef[0]->pic_distance * 2;
    	}
    	else
    	{
            ColDistIdx = pCodecInf->pRef[0]->pic_distance * 2 + 1;
    	}
        for (ColRefIdx = 0; ColRefIdx < 4; ColRefIdx++)
        {
	         if(pCodecInf->b_filed_enhanced_flag)
			 {
	            if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[(ColRefIdx / 2) +1])
	            {
	                ColRefDistIdx = pCodecInf->pRef[(ColRefIdx /2) +1]->pic_distance * 2 + ((ColRefIdx+1) & 1);
	                ColBlkDist = ((ColDistIdx - ColRefDistIdx) + 512) % 512;
	                if (0 == ColBlkDist)
	                {
	                    pCodecInf->DirectScale[ColRefIdx] = 16384 / 512;
	                }
	                else
	                {
	                    pCodecInf->DirectScale[ColRefIdx] = 16384 / ColBlkDist;
	                }
	            }
	         }
			 else
		     {
	                if (&(pCodecInf->ZeroFrm) != pCodecInf->pRef[(ColRefIdx + 1) / 2])
	                {
	                    ColRefDistIdx = pCodecInf->pRef[(ColRefIdx + 1) / 2]->pic_distance * 2 + (ColRefIdx & 1);
	                }  
		     }
            ColBlkDist = ((ColDistIdx - ColRefDistIdx) + 512) % 512;
            if (0 == ColBlkDist)
            {
                pCodecInf->DirectScale[4 + ColRefIdx] = 16384 / 512;
            }
            else
            {
                pCodecInf->DirectScale[4 + ColRefIdx] = 16384 / ColBlkDist;
            }
				
        }
    }
    

    return AVS_TRUE;
}


SINT32 AVS_UpdateTableSymScale(AVS_CODECINF *pCodecInf)
{
    SINT32 BlkDistFw, BlkDistBw;
    SINT32 CurDistIdx;
    SINT32 CurFld, RefIdxFw, RefIdxBw;

    BlkDistFw = 0;
    BlkDistBw = 0;
    CurDistIdx = 0;
    CurFld = 0;
    RefIdxFw = 0;
    RefIdxBw = 0;

    if (&(pCodecInf->ZeroFrm) == pCodecInf->pRef[1])
    {
        /*fw or sym mode is not allowed, but maybe the picture still can be decoded*/
        return AVS_FALSE;
    }

    if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
    {
        CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2;
        BlkDistFw = pCodecInf->pRef[1]->pic_distance * 2;
        BlkDistFw = ((CurDistIdx - BlkDistFw) + 512) & 0x1FF;
        BlkDistBw = pCodecInf->pRef[0]->pic_distance * 2;
        BlkDistBw = ((BlkDistBw - CurDistIdx) + 512) & 0x1FF;
        // BlkDistFw 在后面会作为除数，需要对零进行判断
        if (0 == BlkDistFw)
        {
            BlkDistFw = 512;
        }
        pCodecInf->SymScale[0] = BlkDistBw * (512 / BlkDistFw);
    }
    else
    {
        for (CurFld = 0; CurFld < 2; CurFld++)
        {
            CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2 + CurFld;
            for (RefIdxFw = 0; RefIdxFw < 2; RefIdxFw++)
            {
                RefIdxBw  = 1 - RefIdxFw;
                BlkDistFw = pCodecInf->Idx2Dist[CurFld * 4 + RefIdxFw];
                BlkDistFw = ((CurDistIdx - BlkDistFw) + 512) & 511;
                BlkDistBw = pCodecInf->Idx2Dist[CurFld * 4 + 2 + RefIdxBw];
                BlkDistBw = ((BlkDistBw - CurDistIdx) + 512) & 511;
                // BlkDistFw 在后面会作为除数，需要对零进行判断
				if (0 == BlkDistFw)
                {
                    BlkDistFw = 512;
                }
                pCodecInf->SymScale[CurFld * 2 + RefIdxFw] = BlkDistBw * (512 / BlkDistFw);
            }
        }
    }

    return AVS_TRUE;
}


SINT32 AVS_UpdateTabBBlkDist(AVS_CODECINF *pCodecInf)
{
    SINT32 BlkDistFw, BlkDistBw;
    SINT32 CurDistIdx;
    SINT32 CurFld, RefIdx;

    if (&(pCodecInf->ZeroFrm) == pCodecInf->pRef[1])
    {
        return AVS_FALSE;
    }

    if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
    {
        CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2;
        BlkDistFw = pCodecInf->pRef[1]->pic_distance * 2;
        BlkDistFw = ((CurDistIdx - BlkDistFw) + 512) & 0x1FF;
        BlkDistBw = pCodecInf->pRef[0]->pic_distance * 2;
        BlkDistBw = ((BlkDistBw - CurDistIdx) + 512) & 0x1FF;
        pCodecInf->BBlkDist[0] = BlkDistFw;
        pCodecInf->BBlkDist[2] = BlkDistBw;
    }
    else
    {
        for (CurFld = 0; CurFld < 2; CurFld++)
        {
            CurDistIdx = pCodecInf->pCurFrm->pic_distance * 2 + CurFld;
            for (RefIdx = 0; RefIdx < 2; RefIdx++)
            {
                BlkDistFw = pCodecInf->Idx2Dist[CurFld * 4 + RefIdx];
                BlkDistFw = ((CurDistIdx - BlkDistFw) + 512) & 511;
                BlkDistBw = pCodecInf->Idx2Dist[CurFld * 4 + 2 + RefIdx];
                BlkDistBw = ((BlkDistBw - CurDistIdx) + 512) & 511;
                pCodecInf->BBlkDist[CurFld * 4 + 0 + RefIdx] = BlkDistFw;
                pCodecInf->BBlkDist[CurFld * 4 + 2 + RefIdx] = BlkDistBw;
            }
        }
    }

    return AVS_TRUE;
}


SINT32 AVS_UpdatePmvTable(AVS_CODECINF *pCodecInf)
{
    switch (pCodecInf->Syntax.syn_pic.derived_pic_coding_type)
    {
        case I_PICTURE:
            if (1 == pCodecInf->Syntax.syn_pic.picture_structure)
            {
                return AVS_TRUE;
            }
            else  // IP场对
            {
                AVS_UpdateTableIdx2Dist(pCodecInf);
                AVS_UpdateTableMvEScale(pCodecInf);
            }
        
            break;
        case P_PICTURE:
            AVS_UpdateTableIdx2Dist(pCodecInf);
            AVS_UpdateTableMvEScale(pCodecInf);
            break;
        case B_PICTURE:
            AVS_UpdateTableIdx2Dist(pCodecInf);
            AVS_UpdateTableMvEScale(pCodecInf);
            AVS_UpdateTableDirectScale(pCodecInf);
            AVS_UpdateTabBBlkDist(pCodecInf);
            AVS_UpdateTableSymScale(pCodecInf);
            break;
        default:
            return AVS_FALSE;
    }

    return AVS_TRUE;
}


SINT32 AVS_VerifyMemPara(VOID)
{
    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVSDEC_Init
功能描述  : 初始化AVS firmware
输入参数  : VOID
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVSDEC_Init(AVS_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    AVS_CODECINF *pAvsCodecInfo;
    BS  *pBs;
    SINT32  ImgQueRstMagic;

    //初始化
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(AVS_CTX_S));
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
    
    pCtx->pstExtraData = pstExtraData;

    pAvsCodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;

    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }

    if (AVS_FALSE == AVS_VerifyMemPara())
    {
        //return -1;
    }

    //初始化
    memset(pAvsCodecInfo, 0, sizeof(AVS_CODECINF));
    //memset(pAvsCodecInfo, 0, sizeof(AVS_SYNTAX) );
    pAvsCodecInfo->pBs = pBs;
    pAvsCodecInfo->DDR_Stride = 0x400;

    pAvsCodecInfo->pRef[0] =
    pAvsCodecInfo->pRef[1] =
    pAvsCodecInfo->pRef[2] =
    pAvsCodecInfo->pCurFrm = &(pAvsCodecInfo->ZeroFrm);

    pAvsCodecInfo->pstImgQue = &pCtx->ImageQue;

    pCtx->pstExtraData->s32WaitFsFlag = 0;

    return VF_OK;
}


/*****************************************************************************
函 数 名  : AVSDEC_Destroy
功能描述  : 销毁AVS firmware
输入参数  : VOID
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVSDEC_Destroy(AVS_CTX_S *pCtx)
{

    return AVS_TRUE;
}


/*****************************************************************************
函 数 名  : AVSDEC_Decode
功能描述  : 对一个AVS 帧或者场对进行解码
输入参数  : STREAM_PARAM *p_Packet
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVSDEC_Decode(AVS_CTX_S *pCtx, DEC_STREAM_PACKET_S *p_Packet)
{
    SINT32 ret = AVS_TRUE;
    AVS_CODECINF *pAvsCodecInfo;
    BS *pBs;
    AVS_SYNTAX *pSynNew;

    pAvsCodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSynNew = &pCtx->SyntaxNew;

    BsInit(pBs, p_Packet->StreamPack[0].VirAddr, p_Packet->StreamPack[0].LenInByte);
    memcpy(&(pCtx->LastPacket), p_Packet, sizeof(DEC_STREAM_PACKET_S));
    pAvsCodecInfo->u32LastIntegrity = pAvsCodecInfo->Integrity;
    
    if (AVS_ParseHeader(pCtx) == AVS_FALSE)
    {
        dprint(PRN_ERROR, "ERROR: paseHeader err\n");
        ret = AVS_FALSE;
        AVS_ClearCurPic(pCtx);
//        ReleasePacket(VFMW_AVS, pCtx);
        return ret;
    }
    if (AVS_DecodeArbiter(pCtx) == AVS_FALSE)
    {
        //dprint(PRN_ERROR, "ERROR: AVS_DecodeArbiter err\n");
        ret = AVS_FALSE;
        return ret;
    }
    ret = AVS_PrepareDecode(pCtx);
    if(AVS_WAIT == ret)
    {
        pAvsCodecInfo->Integrity = pAvsCodecInfo->u32LastIntegrity;
        return ret;
    }
    else if(AVS_FALSE == ret)
    {
        dprint(PRN_ERROR, "ERROR: AVS_PrepareDecode err\n");    
        AVS_ClearCurPic(pCtx);
//        ReleasePacket(VFMW_AVS, pCtx);
        ret = AVS_FALSE;
        return ret;
    }
    if (AVS_StartDecode(pCtx) == AVS_FALSE)
    {
        dprint(PRN_ERROR, "ERROR: AVS_StartDecode err\n");   
        AVS_ClearCurPic(pCtx);
        ret = AVS_FALSE;
        return ret;
    }

    return ret;
}


/*****************************************************************************
函 数 名  : AVSDEC_RecycleImage
功能描述  : 回收一个已经显示的帧存
输入参数  : UINT32 img_id
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :

  修改历史      :
  1.日    期   : 2007年12月17日
  作    者   : y62639
  修改内容   : 新生成函数

*****************************************************************************/
SINT32 AVSDEC_RecycleImage(AVS_CTX_S *pCtx, UINT32 img_id)
{
    AVS_CODECINF  *pAvsCodecInfo;
    IMAGE *pImg;

    pAvsCodecInfo = &pCtx->CodecInfo;

    FSP_SetDisplay(pCtx->ChanID, img_id, 0);
	pImg = FSP_GetFsImagePtr(pCtx->ChanID, img_id);
	if (NULL != pImg)
	{
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
	}
    return AVS_TRUE;
}


SINT32 AVSDEC_GetRemainImg(AVS_CTX_S *pCtx)
{
    AVS_CODECINF  *pAvsCodecInfo;
    IMAGE *pImage = NULL;
    SINT32 i, display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;
	
    pAvsCodecInfo = &pCtx->CodecInfo;

    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = LAST_ALREADY_OUT;
    }
    else
    {
	for (i = 3; i >0 ; i--)
	{
	     pImage = FSP_GetFsImagePtr(pCtx->ChanID, pAvsCodecInfo->pRef[i-1]->FspID);
	     if (pImage != NULL)
	     {
    	          display_flag = FSP_GetDisplay(pCtx->ChanID, pAvsCodecInfo->pRef[i-1]->FspID);
	          if (FS_DISP_STATE_DEC_COMPLETE == display_flag)
	          {
	              AVS_SetImgFormat(pCtx);
	              if (0 == i-1)             // 0为最近解出来的参考帧，即最后一帧
	              {
                         pImage->last_frame = 1;      // last frame
	              }
				  
		       FSP_SetDisplay (pCtx->ChanID,pAvsCodecInfo->pRef[i-1]->FspID,1);
	              if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_AVS, pCtx, &pCtx->ImageQue, pImage))
	              { 
                         AVSDEC_RecycleImage(pCtx, pImage->image_id);
                         FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[0]);
                         pImage->p_usrdat[0] = NULL;
                         FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[1]);
                         pImage->p_usrdat[1] = NULL;
			    ret = LAST_OUTPUT_FAIL;
	              }
		       else if ( pImage->error_level > 100 || pImage->image_width < 32 || pImage->image_height < 32 )        // 特殊情况下返回的VF_OK，并没实际插到队列中
                     {
                         ret = LAST_OUTPUT_FAIL;
	              }
		       else
			{
                         ret = LAST_OUTPUT_OK;
		       }
	          }
		   else
		   {
                     ret = LAST_ALREADY_OUT;
		   }
	     }
	}
    }

    if (LAST_OUTPUT_OK != ret)
    {
        ret = GetVoLastImageID(&pCtx->ImageQue);
    }

    return ret;
}

SINT32 AVSDEC_VDMPostProc(AVS_CTX_S *pCtx, SINT32 ErrRatio)
{
    AVS_CODECINF *pCodecInf;
    AVS_SYNTAX *pCurSyn;
    FRAME_OBJ *pOutput = 0;
  	SINT32 RefErrThr, OutErrThr;
	SINT32 RefErrLevel;
	IMAGE *pImage;
	
    pCodecInf = &pCtx->CodecInfo;
    pCurSyn = &pCodecInf->Syntax;

    AVS_ClearCurPic(pCtx);
    memset(&(pCtx->AvsDecParam), 0, sizeof(AVS_DEC_PARAM_S));
//  ReleasePacket(VFMW_AVS, pCtx);

    if ( I_PICTURE == pCurSyn->syn_pic.derived_pic_coding_type )
    {
        pCodecInf->ErrRatio = ErrRatio;
    }
    else  /* P帧或者B帧的错误率要继承参考帧 */
    {
		pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[0]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);

		RefErrLevel = pImage->error_level;
		pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pRef[1]->FspID);
        AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);

        RefErrLevel = RefErrLevel + pImage->error_level;
        pCodecInf->ErrRatio = ErrRatio + RefErrLevel;
        pCodecInf->ErrRatio = ( pCodecInf->ErrRatio > 100 )? 100: pCodecInf->ErrRatio;
    }

    RefErrThr = pCtx->pstExtraData->s32RefErrThr;
    if ( B_PICTURE != pCurSyn->syn_pic.derived_pic_coding_type && pCodecInf->ErrRatio > RefErrThr )
    {
        dprint(PRN_ERROR, "ERROR: err_level(%d) over ref_thr(%d)\n", pCodecInf->ErrRatio, RefErrThr );
        pCodecInf->RefNum = 0;  // 强制找下一个I帧
        AVS_CLEARREFFLAG;
        AVS_CLEARREFNUM;
        return AVS_FALSE;
    }
    AVS_SetImgFormat(pCtx);

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pCodecInf->pCurFrm->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);

    AVS_ATTACHUDINF(pImage->p_usrdat[0], pCodecInf->pSeqUD);
    pCodecInf->pSeqUD = NULL;
    AVS_ATTACHUDINF(pImage->p_usrdat[1], pCodecInf->pPicUD);
    pCodecInf->pPicUD = NULL;
	
    if (pCurSyn->syn_pic.derived_pic_coding_type < B_PICTURE)
    {
        /* 最新解码出来的是一个参考图 */
        pCodecInf->RefNum = (pCodecInf->RefNum < 2)? (pCodecInf->RefNum+1): pCodecInf->RefNum;
    
        /*参考图列表更新*/
        if ((1 == pCurSyn->syn_pic.picture_structure)  // 帧图
           || (pCurSyn->syn_pic.derived_pic_coding_type != I_PICTURE))
        {
            /* 非IP场对，解码前没有做参考维护，这里做 */
			FSP_SetRef(pCtx->ChanID,pCodecInf->pCurFrm->FspID,1);
            if (pCodecInf->pRef[2] != &(pCodecInf->ZeroFrm))
            {
				FSP_SetRef(pCtx->ChanID,pCodecInf->pRef[2]->FspID,0);
            }
            pCodecInf->pRef[2] = pCodecInf->pRef[1];
            pCodecInf->pRef[1] = pCodecInf->pRef[0];
            pCodecInf->pRef[0] = pCodecInf->pCurFrm;
		}
    	pOutput = (pCtx->pstExtraData->s32DecOrderOutput==OUTPUT_IN_DSP)? pCodecInf->pRef[1] : pCodecInf->pCurFrm;
    }
    else
    {
        pOutput = pCodecInf->pCurFrm;
    }

	pImage = FSP_GetFsImagePtr(pCtx->ChanID, pOutput->FspID);
    AVS_ASSERT_RET((NULL != pImage), AVS_FALSE);

    if (pOutput != &(pCodecInf->ZeroFrm))
    {
        OutErrThr = pCtx->pstExtraData->s32OutErrThr;
        if ( pCodecInf->ErrRatio > OutErrThr )
        {
            dprint(PRN_ERROR, "ERROR: err_level(%d) over out_thr(%d)\n", pCodecInf->ErrRatio, OutErrThr );
			FSP_SetDisplay (pCtx->ChanID, pOutput->FspID, 0);
            if (NULL != pImage->p_usrdat[0])
            {
                FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[0]);
                pImage->p_usrdat[0] = NULL;
            }
            if (NULL != pImage->p_usrdat[1])
            {
                FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[1]);
                pImage->p_usrdat[1] = NULL;
            }
        }
        else if (AVS_OutputOneFrame(pOutput, pCtx) == AVS_FALSE)
        {
            if (NULL != pImage->p_usrdat[0])
            {
                FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[0]);
                pImage->p_usrdat[0] = NULL;
            }
            if (NULL != pImage->p_usrdat[1])
            {
                FreeUsdByDec(pCtx->ChanID, pImage->p_usrdat[1]);
                pImage->p_usrdat[1] = NULL;
            }
            return AVS_FALSE;
        }
    }

    return AVS_TRUE;
}

SINT32 AVSDEC_GetImageBuffer( AVS_CTX_S *pCtx )
{
    AVS_CODECINF *pCodecInf;    

	pCodecInf = &pCtx->CodecInfo;    


	/* 2. 否则，如果FSP中有新的帧存可以获取，返回TRUE */
    if (FSP_IsNewFsAvalible(pCtx->ChanID) == 1)
    {
        return 1;
	}
    else if (FSP_IsNewFsAvalible(pCtx->ChanID) == -1)
    {
        FSP_ClearNotInVoQueue(pCtx->ChanID,&(pCtx->ImageQue));
    }

    return 0;
}

SINT32 ClearSlice(SINT32 ChanID,AVS_SLCSTR_S *pSlcStr)
{
    SINT32 i = 0;
    for(i = 0; i < 2; i++)
    {
        if((pSlcStr->stream_lenInByte[i] > 0) && (pSlcStr->stream_phy_addr[i] > 0))
        {
            SM_ReleaseStreamSeg(ChanID, pSlcStr->steram_id[i]);   
        }
        pSlcStr->stream_lenInByte[i] = 0;
        pSlcStr->stream_phy_addr[i] = 0;
        pSlcStr->slice_start_mbn = 0;
    }
    return AVS_TRUE;
}

SINT32 AVS_ClearCurPic(AVS_CTX_S *pCtx)
{
    SINT32 i = 0;
    AVS_DEC_PARAM_S *pAvsDecParam = NULL;
    pAvsDecParam = &pCtx->AvsDecParam;
    for(i = 0; i < pAvsDecParam->SlcNum; i++)
    {
        ClearSlice(pCtx->ChanID,&(pAvsDecParam->SlcStr[i]));
    }
    pAvsDecParam->SlcNum = 0;

    return AVS_TRUE;
}

SINT32 ClearPacket(AVS_CTX_S *pCtx)
{
    SM_ReleaseStreamSeg(pCtx->ChanID, pCtx->LastPacket.StreamPack[0].StreamID);
    if((pCtx->LastPacket.StreamPack[0].IsLastSeg == 0) && (pCtx->LastPacket.StreamPack[1].IsLastSeg == 1) && 
        (pCtx->LastPacket.StreamPack[1].PhyAddr > 0))
    {
        SM_ReleaseStreamSeg(pCtx->ChanID, pCtx->LastPacket.StreamPack[1].StreamID);
    }
    
    return AVS_TRUE;
}

SINT32 WriteAvsSliceMsg(AVS_CTX_S *pCtx)
{
    SINT32 ret;
    SINT32 StartMb = 0;
    AVS_DEC_PARAM_S *pDecParam = NULL;
    AVS_SYNTAX *pSyntax = NULL;
    AVS_SYNTAX *pCurSyn = NULL;
//	UINT32 totalMbMin1 = 0;
	UINT32 totalMb = 0;
	//static int count =0;
    ret = AVS_TRUE;
    pDecParam = &(pCtx->AvsDecParam);
    pSyntax = &pCtx->SyntaxNew;
    pCurSyn = &pCtx->CodecInfo.Syntax;


    if(pDecParam->SlcNum >= MAX_AVS_SLICE_NUM)
    {
        dprint(PRN_ERROR,"SlcNum %d > %d Write slice msg failed\n",pDecParam->SlcNum, MAX_AVS_SLICE_NUM);
        return AVS_FALSE;
    }

	if (pDecParam->SlcNum > 0)
    {
        StartMb = (*(pCtx->LastPacket.StreamPack[0].VirAddr + 3)) * ((pSyntax->syn_seq.horizontal_size + 15) / 16);
        if (StartMb <= pDecParam->SlcStr[pDecParam->SlcNum-1].slice_start_mbn)
        {
            dprint(PRN_ERROR,"This slice's start mbn %d <= LastSliceFirstMb %d, Write slice msg failed\n", StartMb, pDecParam->SlcStr[pDecParam->SlcNum-1].slice_start_mbn);
			ClearPacket(pCtx);
            return AVS_TRUE;
        }
    }

    pDecParam->SlcStr[pDecParam->SlcNum].stream_phy_addr[0] = pCtx->LastPacket.StreamPack[0].PhyAddr;
    pDecParam->SlcStr[pDecParam->SlcNum].steram_id[0] = pCtx->LastPacket.StreamPack[0].StreamID;
    pDecParam->SlcStr[pDecParam->SlcNum].stream_lenInByte[0] = pCtx->LastPacket.StreamPack[0].LenInByte;
    if(pDecParam->SlcNum == 0)
    {
        pDecParam->SlcStr[pDecParam->SlcNum].slice_start_mbn = 0;
    }
    else
    {
        pDecParam->SlcStr[pDecParam->SlcNum].slice_start_mbn = (*(pCtx->LastPacket.StreamPack[0].VirAddr + 3)) * ((pSyntax->syn_seq.horizontal_size + 15) / 16);
    }

	//totalMbMin1 = pDecParam->PicHeightInMb*pDecParam->PicWidthInMb - 1;
	totalMb = (((pCurSyn->syn_seq.horizontal_size + 15)/16)*
	           ((pCurSyn->syn_seq.vertical_size + 15)/16));   

	if(pDecParam->SlcStr[pDecParam->SlcNum].slice_start_mbn > (totalMb - 1))
	{
		return AVS_FALSE;
	}

    if(pCtx->LastPacket.StreamPack[0].IsLastSeg == 1)
    {
        pDecParam->SlcStr[pDecParam->SlcNum].stream_phy_addr[1] = 0;
        pDecParam->SlcStr[pDecParam->SlcNum].steram_id[1] = 0;
        pDecParam->SlcStr[pDecParam->SlcNum].stream_lenInByte[1] = 0;

    }
    else
    {
        pDecParam->SlcStr[pDecParam->SlcNum].stream_phy_addr[1] = pCtx->LastPacket.StreamPack[1].PhyAddr;
        pDecParam->SlcStr[pDecParam->SlcNum].steram_id[1] = pCtx->LastPacket.StreamPack[1].StreamID;
        pDecParam->SlcStr[pDecParam->SlcNum].stream_lenInByte[1] = pCtx->LastPacket.StreamPack[1].LenInByte;
    }
    pDecParam->SlcNum++;

    return AVS_TRUE;

}

SINT32 AVS_GetPacketState(AVS_CTX_S *pCtx)
{
    SINT32 ret = AVS_DEC;
    if(1 == pCtx->IsPackWaitDec)
    {
        ret = AVS_NOTDEC;
    }

    return ret;
}
/*****************************************************************************
 函 数 名  : Avs_Vfmw_WQMatrix
 功能描述  : 生成 加权量化矩阵
 输入参数  : AVS_SEDINFO_S *pSedInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月20日
     作    者   :  y00226912
     修改内容   : 新生成函数

*****************************************************************************/
VOID  Avs_Vfmw_WQMatrix(AVS_SYNTAX *pSyntax)
{
    UINT32 i, j, k;
    SINT16 wq_param[2][6];
    SINT16 wq_matrix[2][64];
    SINT16 quant_param_undetail[6] = {0};             
    SINT16 quant_param_detail[6] = {0};       
  
    if((1 == pSyntax->syn_pic.weighting_quant_param_index)||((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable)&&(3 == pSyntax->syn_pic.weighting_quant_param_index)))
    {
            for(i=0; i<6; i++)
            {
                quant_param_undetail[i] = pSyntax->syn_pic.weighting_quant_param_delta1[i] + wq_param_default[0][i];
            } 
    }
    if((2 == pSyntax->syn_pic.weighting_quant_param_index)||((!pSyntax->syn_pic.mb_adapt_weighting_quant_disable)&&(3 == pSyntax->syn_pic.weighting_quant_param_index)))
    {
        for(i=0; i<6; i++)
            {
                quant_param_detail[i] = pSyntax->syn_pic.weighting_quant_param_delta2[i] + wq_param_default[1][i];
            }
    }
        
        
    // Patch the Weighting Parameters
    if(!pSyntax->syn_pic.mb_adapt_weighting_quant_disable)  
    {
        // Use default weighted parameters,    
        for(i=0; i<2; i++)
        {
		    for(j=0; j<6; j++)
	     	{
		    	wq_param[i][j] = wq_param_default[i][j];
		    }
        }
			
    	if(pSyntax->syn_pic.weighting_quant_param_index != 0)
    	{
    		if(1 == pSyntax->syn_pic.weighting_quant_param_index)
    		{
		    	for(i=0; i<6; i++)
		    	{
			    	wq_param[0][i] = quant_param_undetail[i];
		    	}
	    	}
	    	else if(2 == pSyntax->syn_pic.weighting_quant_param_index)
	    	{
		    	for(i=0; i<6; i++)
	    		{
	    			wq_param[1][i] = quant_param_detail[i];
			    }
	    	}
		    else if(3 == pSyntax->syn_pic.weighting_quant_param_index)
	    	{
		    	for(i=0; i<6; i++)
	    		{
	    			wq_param[0][i] = quant_param_undetail[i];
	    		}
	    		for(i=0; i<6; i++)
	    		{
	    			wq_param[1][i] = quant_param_detail[i];
	    		}
	    	}
    	}
    }
    else 
    {
        for(i=0; i<2; i++)
        {
                for(j=0; j<6; j++)
                {
                        wq_param[i][j] = 128;
                }
        }
                        
            if(0 == pSyntax->syn_pic.weighting_quant_param_index)
        {
                for(i=0; i<6; i++)
                {
                        wq_param[1][i] = wq_param_default[1][i];
                }
        }
        else if(1 == pSyntax->syn_pic.weighting_quant_param_index)
        {
                for(i=0; i<6; i++)
                {
                        wq_param[0][i] = quant_param_undetail[i];
                }
        }
        else if(2 == pSyntax->syn_pic.weighting_quant_param_index)
        {
                for(i=0; i<6; i++)
                {
                        wq_param[1][i] = quant_param_detail[i];
                }
        }       
    }


    for (i=0; i<64; i++)  
    {
        pSyntax->syn_pic.cur_wq_matrix[i] = 1<<7;
    }
        
        // Reconstruct the Weighting matrix
    if(!pSyntax->syn_pic.weighting_quant_flag)
    {  
        for(k=0; k<2; k++)        
        for(j=0; j<8; j++)
        for (i=0; i<8; i++)
        {
              wq_matrix[k][j*8+i] = 1<<7;
        }
    }
    else
    {                   
        for(k=0; k<2; k++) 
        for(j=0; j<8; j++)
        for(i=0; i<8; i++)
        {
              wq_matrix[k][j*8+i] = (wq_param[k][WeightQuantModel[pSyntax->syn_pic.weighting_quant_model][j*8+i]]); 
        }
    } 

    if(0 == pSyntax->syn_pic.weighting_quant_param_index)
    {
        for(i=0; i<64; i++) 
        {
            pSyntax->syn_pic.cur_wq_matrix[i] = wq_matrix[1][i];     // Detailed weighted matrix
        }
    }
    else if(1 == pSyntax->syn_pic.weighting_quant_param_index)
    {
        for(i=0; i<64; i++) 
        {
            pSyntax->syn_pic.cur_wq_matrix[i] = wq_matrix[0][i];     // unDetailed weighted matrix
        }

    }
    else if(2 == pSyntax->syn_pic.weighting_quant_param_index)
    {
        for(i=0; i<64; i++)
        { 
            pSyntax->syn_pic.cur_wq_matrix[i] = wq_matrix[1][i];     // Detailed weighted matrix
        }
    }
}
#endif //AVS_ENABLE

#endif //__AVS_C__
