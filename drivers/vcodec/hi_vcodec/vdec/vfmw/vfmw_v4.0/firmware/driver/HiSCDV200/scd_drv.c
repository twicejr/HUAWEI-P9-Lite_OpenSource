/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3xTDeWuhAOfofKROCEE150YZfDeEJejM53xK+RBEPLvUN0rFoH1R6Rw0Da4E4jfclGDI
O11TkffEXQzBps2DXCRt0H5wZIoBYgMZZQOm/lg9CXbIuo3T+4lRt6c2SIIcHg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

#include "public.h"
#include "scd_drv.h"
#include "vfmw_ctrl.h"
#include "dsp_vfmw_avsp.h"
#include "dsp_vfmw_h264.h"
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif

#define SM_DOWN_CLIP_ZERO(a) do{(a) = (((a) < 0)? 0: (a));}while(0)

static SINT32 s_SCDInISR = 0;
static SCDDRV_SLEEP_STAGE_E  s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_NONE;

#if defined(VFMW_AVSPLUS_SUPPORT) || (VFMW_SCD_LOWDLY_SUPPORT)
SINT32 *g_hex_base_vir_addr;
UADDR   g_hex_base_addr;
UINT32  g_hex_len;
#endif

SM_IIS_S  s_SmIIS;   //静态定义的SM信息集
SM_IIS_S *g_pSmIIS = &s_SmIIS;

extern OSAL_FILE  *vfmw_save_str_file;
extern UINT32      save_str_chan_num;


/*======================================================================*/
/*  函数实现                                                            */
/*======================================================================*/

#ifdef VFMW_SCD_LOWDLY_SUPPORT
//写码表函数
extern UINT32 g_CabacMN[160][8];
VOID WriteCabacTabDsp(UADDR mn_phy_addr)
{
    UINT32 *p;

    p = (UINT32 *)MEM_Phy2Vir(mn_phy_addr);

    if (NULL == p)
    {
        dprint(PRN_DBG, "line: %d, p = NULL is not expected value!\n", __LINE__);
        return;
    }

    memcpy(p, g_CabacMN, 160 * 8 * sizeof(UINT32));

    return;
}
#endif

#if defined(VFMW_AVSPLUS_SUPPORT) || (VFMW_SCD_LOWDLY_SUPPORT)
VOID WriteHexFile(SINT32 eVidStd)
{
    UINT32 i = 0;
    UINT32 data32 = 0;
    UINT8* pVirAddr = NULL;
    UINT32 u32VfmwBinLen = 0;
    UINT32 ReadyFlag = 0;

    pVirAddr = (UINT8*)MEM_Phy2Vir(g_hex_base_addr);
    if (NULL == pVirAddr)
    {
        dprint(PRN_FATAL,"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\n", g_hex_base_addr);
        return;
    }

    if (VFMW_AVS == eVidStd)
    {
        WR_SCDREG(REG_AVS_FLAG, 0x00000001);
        u32VfmwBinLen = sizeof(g_avsp_firmware);
        memcpy(pVirAddr, (UINT8*)g_avsp_firmware, sizeof(g_avsp_firmware));
        u32VfmwBinLen = u32VfmwBinLen/4;
    }
    else if (VFMW_H264 == eVidStd)
    {
        data32 = RD_SCDREG(REG_SCD_PROTOCOL);
        WR_SCDREG(REG_SCD_PROTOCOL, (data32|(1 << 8)));
        u32VfmwBinLen = sizeof(g_h264_firmware);
        memcpy(pVirAddr, (UINT8*)g_h264_firmware, sizeof(g_h264_firmware));
        u32VfmwBinLen = u32VfmwBinLen/4;
    }
    else
    {
        dprint(PRN_FATAL,"Warn: eVidStd = %d have no DSP vfmw bin file!!\n");
        return;
    }
	
    WR_SCDREG(REG_DSP_PROG_WLEN,     u32VfmwBinLen);
    WR_SCDREG(REG_DSP_PROG_STADDR, g_hex_base_addr);
    
    data32 = 0;
#ifdef HIVDEC_SMMU_SUPPORT
    // mmu enable, secure disable
    data32 = (1<<2) | (0<<1);
#endif

    WR_SCDREG(REG_DSP_PROG_ST, data32);
    WR_SCDREG(REG_DSP_PROG_ST, (data32|1));

    for (i=0; i<100; i++)
    {
        ReadyFlag = (RD_SCDREG(REG_DSP_PROG_OVER)) & 0x1;
        if(1 == ReadyFlag)
        {
            break;
        }
	 else
	 {
	     VFMW_OSAL_mSleep(5);
	 }
    }
    if (i >= 100)
    {
        dprint(PRN_FATAL, "eVidStd %d load dsp code failed!\n", eVidStd);
    }

    return;
}
#endif
    
/*********************************************************************************
  函数原型  SINT32 GetInstIDByRawArray( RAW_ARRAY_S *pRawArray)
  功能描述  根据RawArray查找Scd通道ID
  参数说明  无
  返回值    无
  算法描述  略
 *********************************************************************************/
SINT32 GetInstIDByRawArray( RAW_ARRAY_S *pRawArray)
{
    SINT32 i;

    for ( i=0; i<MAX_CHAN_NUM; i++ )
    {
        if (s_SmIIS.pSmInstArray[i] != NULL && pRawArray == &s_SmIIS.pSmInstArray[i]->RawPacketArray )
        {
            return i;
        }
    }

    return -1;
}


/*========================================================================
  part1.    raw stream management module
  ========================================================================*/

/*********************************************************************************
  函数原型
  SINT32 ResetSCD(VOID)
  功能描述
  复位SCD硬件
  参数说明
  无
  返回值
  无
  算法描述
  略
 *********************************************************************************/
SINT32 ResetSCD(VOID)
{
    UINT32 tmp;
    UINT32 i;
    UINT32 reg_rst_ok;
    UINT32 reg;
    UINT32 *pScdResetReg = NULL;
    UINT32 *pScdResetOkReg = NULL;
	
    pScdResetReg   = (UINT32*)MEM_Phy2Vir(gSOFTRST_REQ_Addr);
    pScdResetOkReg = (UINT32*)MEM_Phy2Vir(gSOFTRST_OK_ADDR);

    if( NULL == pScdResetReg || NULL == pScdResetOkReg)
    {
        dprint(PRN_FATAL,"scd reset register map fail!\n");
        return VF_ERR_SYS;
    }

    tmp = RD_SCDREG( REG_SCD_INT_MASK );

    /* require scd reset */
    reg= *(volatile UINT32 *)pScdResetReg;
    *(volatile UINT32 *)pScdResetReg = reg | (UINT32)(1<<SCD_RESET_CTRL_BIT);

    /*wait for rest ok */
    for(i=0; i<100; i++)
    {
        reg_rst_ok =*(volatile UINT32 *)pScdResetOkReg;
        if( reg_rst_ok & (1 <<SCD_RESET_OK_BIT))
        {
            break;
        }	
        VFMW_OSAL_uDelay(10);
    }
    
    if (i >= 100)
    {
        dprint(PRN_FATAL, "%s reset failed!\n", __func__);
    }
    else
    {
        //dprint(PRN_ALWS,  "%s reset success!\n", __func__);
    }

    /* clear reset require */
    *(volatile UINT32 *)pScdResetReg = reg & (UINT32)(~(1<<SCD_RESET_CTRL_BIT));

    WR_SCDREG(REG_SCD_INT_MASK, tmp);
	
    return(VF_OK);
}

/*********************************************************************************
  函数原型
  VOID SCDDRV_ResetSCD(SINT32 ChanID)
  功能描述
  复位为该通道工作的SCD硬件
  参数说明
  ChanID 通道号
  返回值
  无
  算法描述
  略
 *********************************************************************************/
VOID SCDDRV_ResetSCD(SINT32 ChanID)
{
    if (1 == s_SmIIS.SCDState && ChanID == s_SmIIS.ThisInstID)
    {
        ResetSCD();
        s_SmIIS.SCDState = 0;
    }
    
    return;
}

/*屏蔽SCD中断*/
VOID SCDDRV_MaskInt(VOID)
{
    WR_SCDREG(REG_SCD_INT_MASK, 1);

    return;
}

/*使能SCD中断*/
VOID SCDDRV_EnableInt(VOID)
{
#ifndef SCD_BUSY_WAITTING
    WR_SCDREG(REG_SCD_INT_MASK, 0);
#endif

    return;
}

/************************************************************************
  原型    VOID ResetRawStreamArray( RAW_ARRAY_S *pRawStreamArray )
  功能    将一组原始码流集合复位，清除其中所有记录
  参数    pRawStreamArray 指向原始码流集合
  返回值  无
 ************************************************************************/
VOID ResetRawStreamArray(RAW_ARRAY_S *pRawStreamArray)
{
    FMW_ASSERT( NULL != pRawStreamArray );

    memset( pRawStreamArray, 0, sizeof(RAW_ARRAY_S) );
    return;
}

/************************************************************************
  原型    SINT32 InsertRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  功能    将一个原始码流包插入到指定的码流集合
  参数    pRawStreamArray 指向原始码流集合
  pRawPacket  指向原始码流包
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 InsertRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket )
{
    SINT32 Index;

    /* 可以调GetRawState */
    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 != pRawPacket), FMW_ERR_PARAM );

    //# 锁定，防止竞争. 具体措施后续加上

    /* 判断是否已满 */
    if ( ((pRawStreamArray->Tail+1) % MAX_STREAM_RAW_NUM) == pRawStreamArray->History )
    {
        return FMW_ERR_BUSY;
    }

    /* 插入包 */
    Index = pRawStreamArray->Tail;
    memcpy( &(pRawStreamArray->RawPacket[Index]), pRawPacket, sizeof(STREAM_DATA_S) );
    pRawStreamArray->Tail = (pRawStreamArray->Tail+1) % MAX_STREAM_RAW_NUM;

    //# 解除锁定

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 GetRawIsFull(SINT32 SmID)
  功能    得到Raw Buffer能否插入的状态
  参数    SmID    码流管理模块的实例的标识
  返回值  可以插入Raw Packet就返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 GetRawState(SINT32 SmID)
{

    SINT32 Ret;
    RAW_ARRAY_S *pRawStreamArray;

    Ret = FMW_ERR_BUSY;
    FMW_ASSERT_RET((SmID >= 0) && (SmID < SM_MAX_SMID),Ret);
    FMW_ASSERT_RET(s_SmIIS.pSmInstArray[SmID]!=NULL,Ret);

    pRawStreamArray = &s_SmIIS.pSmInstArray[SmID]->RawPacketArray;    

    if( ((pRawStreamArray->Tail+1) % MAX_STREAM_RAW_NUM) == pRawStreamArray->History )
    {
        return Ret;
    }

    return FMW_OK;

}

/************************************************************************
  原型    SINT32 ShowFirstRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  功能    查看指定的码流集合中的第一个码流包信息。
  参数    pRawStreamArray 指向原始码流集合
  pRawPacket  指向原始码流包的结构，用于接收码流包信息
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 ShowFirstRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket )
{
    SINT32 Index;
    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 != pRawPacket), FMW_ERR_PARAM );

    if ( pRawStreamArray->Head == pRawStreamArray->Tail )
    {
        return FMW_ERR_NOTRDY;
    }
    else
    {
        Index = pRawStreamArray->Head;
        pRawStreamArray->CurShowIndex = Index;
        memcpy( pRawPacket, &pRawStreamArray->RawPacket[Index], sizeof(STREAM_DATA_S) );
    }

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 ShowNextRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  功能    "Next"是相对于上一次调用Show…函数而言的。本函数与ShowFirstRawPacket()结合可查看所有码流包的信息。
  参数    pRawStreamArray 指向原始码流集合
  pRawPacket  指向原始码流包的结构，用于接收码流包信息
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 ShowNextRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket )
{
    SINT32 Index;
    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 != pRawPacket), FMW_ERR_PARAM );

    /* 判断是否还有可show的码流包 */
    Index = (pRawStreamArray->CurShowIndex + 1) % MAX_STREAM_RAW_NUM;
    if( Index == pRawStreamArray->Tail )
    {
        return FMW_ERR_NOTRDY;
    }
    else
    {
        pRawStreamArray->CurShowIndex = Index;
        memcpy( pRawPacket, &pRawStreamArray->RawPacket[Index], sizeof(STREAM_DATA_S) );
    }

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 SetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 Offset )
  功能    设置第一个码流包的有效字节偏移
  参数    pRawStreamArray 指向原始码流集合
  Offset  第一个数据包的有效字节偏移量
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 SetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 Offset )
{
    SINT32 Index;
    SINT32 TargetOffset;
    FMW_ASSERT_RET( 0 != pRawStreamArray, FMW_ERR_PARAM );

    /* 如果原始码流集空，返回失败 */
    if( pRawStreamArray->Head == pRawStreamArray->Tail )
    {
        return FMW_ERR_NOTRDY;
    }

    TargetOffset = pRawStreamArray->FirstPacketOffset + Offset;
    Index = pRawStreamArray->Head;
    if( TargetOffset >= pRawStreamArray->RawPacket[Index].Length )  
    {
        return FMW_ERR_PARAM;
    }

    pRawStreamArray->FirstPacketOffset += Offset;

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 GetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset )
  功能    获取第一个码流包的有效字节偏移
  参数    pRawStreamArray 指向原始码流集合
  pOffset 第一个数据包的有效字节偏移量
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 GetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset )
{
    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 != pOffset), FMW_ERR_PARAM );

    /* 如果原始码流集空，返回失败 */
    if( pRawStreamArray->Head == pRawStreamArray->Tail )
    {
        return FMW_ERR_NOTRDY;
    }

    *pOffset = pRawStreamArray->FirstPacketOffset;

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 DeleteRawPacket( RAW_ARRAY_S *pRawStreamArray, UINT32 DelNum )
  功能    从第一码流包开始，连续删除DelNum个码流包。
  由于有码流片段缓冲区的存在，原始码流无需乱序释放，所以原始码流
  管理模块可以只支持按插入顺序释放。码流包从原始码流集中删除的同时，
  也会调用MPP的接口通知外部组建释放对应的码流空间。
  参数    pRawStreamArray 指向原始码流集合
  pRawPacket  指向原始码流包的结构，用于接收码流包信息
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 DeleteRawPacket( RAW_ARRAY_S *pRawStreamArray, UINT32 DelNum )
{
    UINT32 PacketNum = 0;
    UINT32 i = 0, j = 0;
    SINT32 SmID = 0;

    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 != DelNum), FMW_ERR_PARAM );
    SmID = GetInstIDByRawArray( pRawStreamArray );

    if( SmID < 0 )
    {
        dprint(PRN_FATAL,"line: %d Get SmID fail!", __LINE__);
        return FMW_ERR_PARAM;
    }

    /* 原始码流集中有多少包？*/
    PacketNum = (pRawStreamArray->Head <= pRawStreamArray->Tail)?
        (pRawStreamArray->Tail - pRawStreamArray->Head):
        (pRawStreamArray->Tail + MAX_STREAM_RAW_NUM - pRawStreamArray->Head);

    if( DelNum > PacketNum )
    {
        dprint(PRN_SCD_INFO, "DelRaw err PacketNum=%d,DelNum=%d\n",PacketNum,DelNum);
        return FMW_ERR_PARAM;
    }
    else
    {
        j = pRawStreamArray->Head;
        for( i=0; i < DelNum; i++ )
        {
            dprint(PRN_SCD_INFO, "Release RawPhyAddr=0x%x,Len=%d\n",pRawStreamArray->RawPacket[j].PhyAddr,pRawStreamArray->RawPacket[j].Length);
            //ReleaseRawStreamData(SmID, &pRawStreamArray->RawPacket[j]);
            s_SmIIS.pSmInstArray[SmID]->RawPacketArray.RawTotalSize -= pRawStreamArray->RawPacket[j].Length;
            SM_DOWN_CLIP_ZERO(s_SmIIS.pSmInstArray[SmID]->RawPacketArray.RawTotalSize);
            j = (j+1) % MAX_STREAM_RAW_NUM;
        }

        pRawStreamArray->Head += DelNum;
        if(pRawStreamArray->Head >= MAX_STREAM_RAW_NUM)
        {
            pRawStreamArray->Head -= MAX_STREAM_RAW_NUM;
        }
        if( DelNum > 0 )
        {
            pRawStreamArray->FirstPacketOffset = 0;
        }
    }

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag)
  功能    从history开始，连续删除到head
  参数    SmID 通道号
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag)
{
    UINT32 i, j;
    SINT32 RawHead;
    SINT32 DelNum;
    RAW_ARRAY_S *pRawStreamArray;
    SM_INSTANCE_S *pSmInstArray = NULL;

    if ((SmID < 0) || (SmID > (SM_MAX_SMID - 1)))
    {
        dprint(PRN_FATAL, "SmID = %d is not expected!\n", SmID);
        return FMW_ERR_PARAM;
    }

    pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    if (pSmInstArray == NULL)
    {
        return FMW_ERR_PARAM;
    }

    if (ResetFlag == 0)
    {
        FMW_ASSERT_RET( (SM_INST_MODE_IDLE != pSmInstArray->Mode), FMW_ERR_PARAM );
    }
    pRawStreamArray = &(pSmInstArray->RawPacketArray);
    FMW_ASSERT_RET( (0 != pRawStreamArray), FMW_ERR_PARAM );

    RawHead = pRawStreamArray->Head;
    /* 计算需要释放的原始码流有多少包 */
    DelNum = (pRawStreamArray->History <= RawHead)?
        (RawHead - pRawStreamArray->History):
        (RawHead + MAX_STREAM_RAW_NUM - pRawStreamArray->History);

    if(DelNum == 0)
    {
        return FMW_ERR_PARAM;
    }
    else
    {
        j = pRawStreamArray->History;
        for( i =0; i < DelNum; i++ )
        {
            dprint(PRN_SCD_INFO, "Release RawPhyAddr=0x%x,Len=%d\n",pRawStreamArray->RawPacket[j].PhyAddr,pRawStreamArray->RawPacket[j].Length);
            ReleaseRawStreamData(SmID, &pRawStreamArray->RawPacket[j]);
            j = (j+1) % MAX_STREAM_RAW_NUM;
        }

        pRawStreamArray->History += DelNum;
        if(pRawStreamArray->History >= MAX_STREAM_RAW_NUM)
        {
            pRawStreamArray->History -= MAX_STREAM_RAW_NUM;
        }
    }

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 GetRawNumOffsert( RAW_ARRAY_S *pRawStreamArray, SINT32 Len, SINT32 *pNum, SINT32 Offset )
  功能    从长度Len计算从第一码流包开始，共有需要有多个的码流包的大小等于Len，如果有半包则长度余数为Offset。 
  参数    pRawStreamArray 指向原始码流集合
  Len             长度
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 GetRawNumOffsert( RAW_ARRAY_S *pRawStreamArray, SINT32 Len, SINT32 *pNum, SINT32 *pOffset, UINT64 *pPts, UINT64 *pUsertag, UINT64 *pDisptime, UINT32 *pDispEnableFlag, UINT32 *pDispFrameDistance, UINT32 *pDistanceBeforeFirstFrame, UINT32 *pGopNum, UINT64 *pRawPts)
{
    SINT32 i, Index;
    SINT32 TotalLen;
    SINT32 RawNum = 0;

    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 <= Len), FMW_ERR_PARAM );
    FMW_ASSERT_RET( (0 != pNum) && (0 != pOffset), FMW_ERR_PARAM );

    TotalLen = pRawStreamArray->RawPacket[pRawStreamArray->Head].Length - pRawStreamArray->FirstPacketOffset;

    if(FMW_OK !=  GetRawStreamNum(pRawStreamArray, &RawNum))
    {
        dprint(PRN_DBG, "%s %d FMW_OK !=  GetRawStreamNum!!\n",__FUNCTION__,__LINE__);
    }
    RawNum = RawNum + pRawStreamArray->Head;

    Index = pRawStreamArray->Head;
    *pPts = pRawStreamArray->RawPacket[Index].Pts;
    *pUsertag = pRawStreamArray->RawPacket[Index].UserTag;
    *pRawPts = pRawStreamArray->RawPacket[Index].Pts;
    *pDisptime = pRawStreamArray->RawPacket[Index].DispTime;
    *pDispEnableFlag = pRawStreamArray->RawPacket[Index].DispEnableFlag;
    *pDispFrameDistance = pRawStreamArray->RawPacket[Index].DispFrameDistance;
    *pDistanceBeforeFirstFrame = pRawStreamArray->RawPacket[Index].DistanceBeforeFirstFrame;
    *pGopNum = pRawStreamArray->RawPacket[Index].GopNum;

    for( i = pRawStreamArray->Head; i < RawNum;)
    {
        if( Len < TotalLen )
        {            
            break;
        }        
        i++;
        Index = i % MAX_STREAM_RAW_NUM;
        TotalLen += pRawStreamArray->RawPacket[Index].Length;
        *pPts = (pRawStreamArray->RawPacket[Index].Pts == -1)? (*pPts) : pRawStreamArray->RawPacket[Index].Pts;
        *pUsertag = pRawStreamArray->RawPacket[Index].UserTag;
        *pRawPts = pRawStreamArray->RawPacket[Index].Pts;
        *pDisptime = pRawStreamArray->RawPacket[Index].DispTime;
        *pDispEnableFlag = pRawStreamArray->RawPacket[Index].DispEnableFlag;
        *pDispFrameDistance = pRawStreamArray->RawPacket[Index].DispFrameDistance;
        *pDistanceBeforeFirstFrame = pRawStreamArray->RawPacket[Index].DistanceBeforeFirstFrame;
        *pGopNum = pRawStreamArray->RawPacket[Index].GopNum;

    }

    if (pRawStreamArray->Head == i)
    {
        *pNum = 0;
        *pOffset = Len;
        return FMW_OK;
    }
    else
    {
        TotalLen = TotalLen - pRawStreamArray->RawPacket[Index].Length;
        *pNum = i - pRawStreamArray->Head;
        *pOffset = Len - TotalLen;
        return FMW_OK;
    }
}

/************************************************************************
  原型    SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen )
  功能    从第一码流包开始，连续删除DelLen的码流包如果删除的长度不够，则要置偏移。            
  参数    pRawStreamArray 指向原始码流集合
  DelLen  总共需要删除的长度
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen )
{
    SINT32 TotallLen;
    SINT32 Ret;
    SINT32 DelNum;
    SINT32 RawPacketOffSet;
    UINT64 Pts;
    UINT64 Usertag;
    UINT64 Disptime;
    UINT64 RawPts;
    UINT32 DispEnableFlag;
    UINT32 DispFrameDistance;
    UINT32 DistanceBeforeFirstFrame;
    UINT32 GopNum;

    FMW_ASSERT_RET( (0 != pRawStreamArray) && (0 <= DelLen), FMW_ERR_PARAM );

    DelNum = 0;
    RawPacketOffSet = 0;

    /*充许删除长度为0的输入*/
    if (0 == DelLen)
    {
        //return FMW_OK;  //lenth == 0时这样做会导致实际这包码流没有被del，出现在VP6 NVOP(此时该包码流长度为0)时出错。
    }
    RawPacketOffSet = 0;

    /* 原始码流集中有多少包？*/
    Ret = GetRawStreamSize( pRawStreamArray, &TotallLen);
    if (FMW_OK == Ret)
    {
        if( DelLen > TotallLen )
        {
            return FMW_ERR_PARAM;
        }
        else
        {
            /*得到Raw包的个数与多余的偏移*/
            GetRawNumOffsert(pRawStreamArray, DelLen, &DelNum, &RawPacketOffSet, &Pts, &Usertag, &Disptime, &DispEnableFlag, &DispFrameDistance, &DistanceBeforeFirstFrame, &GopNum, &RawPts);
            /*删除EatenRawNum包码流,因为前面有包数的限制,所以EatenRawNum不会越界,
              但EatenRawNum会为零,但这里可以不用管,因为不用删除包*/
            DeleteRawPacket(pRawStreamArray, DelNum);
            Ret = SetFirstOffset(pRawStreamArray, RawPacketOffSet);
            if (FMW_OK != Ret)
            { 
                return Ret;
            }
        } 
    }
    else
    {
        return Ret;
    }

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 DeleteLastSendRaw( UINT32 SmID  )
  功能    删除SmID所指向的通道，上次所送入SCD的码流
  参数    SmID通道号
  返回值  无
 ************************************************************************/
VOID DeleteLastSendRaw( UINT32 SmID )
{
    SINT32 LastPushRawNum;
    SM_INSTANCE_S *pSmInstArray = NULL;

    SM_CHECK_VALUE((SINT32)SmID, 0, SM_MAX_SMID-1, return);

    pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    if (pSmInstArray == NULL)
    {
        dprint(PRN_FATAL, "line: %d pSmInstArray is NULL!\n", __LINE__);
        return;
    }

    LastPushRawNum = pSmInstArray->SmPushRaw.PushRawNum;

    if (LastPushRawNum > 0)
    {
        DeleteRawPacket(&(pSmInstArray->RawPacketArray), (UINT32)LastPushRawNum);
        pSmInstArray->SmPushRaw.PushRawNum = 0;
    }

    return;

}



/************************************************************************
  原型    SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize)
  功能    将原始码流集合中所有包的长度累加起来即为码流总量，目的是获得目前的码流占用情况。
  参数    pRawStreamArray 指向原始码流集合
  pRawPacket  指向原始码流包的结构，用于接收码流包信息
  返回值  成功返回码流长度，否则返回错误码（负整数）
 ************************************************************************/
SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize)
{

    FMW_ASSERT_RET( 0 != pRawStreamArray, FMW_ERR_PARAM );

    *pStreamSize  = pRawStreamArray->RawTotalSize;
    *pStreamSize -= pRawStreamArray->FirstPacketOffset;
    FMW_ASSERT_RET( (*pStreamSize) >= 0, FMW_ERR_PARAM );
    return FMW_OK;
}


/************************************************************************
  原型    SINT32 GetRawStreamNum( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum )
  功能    将原始码流集合中已被推送但尚未被切割的码流包数，目的是获得目前的码流占用情况。
  参数    pRawStreamArray 指向原始码流集合
  返回值  成功返回pStreamNum码流包数，并返回FMW_OK,失败则返回错误码（负整数）
 ************************************************************************/
SINT32 GetRawStreamNum(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum)
{
    FMW_ASSERT_RET( 0 != pRawStreamArray, FMW_ERR_PARAM );
    
    *pStreamNum = pRawStreamArray->Tail - pRawStreamArray->Head;

    if (*pStreamNum < 0)
    {
        *pStreamNum += MAX_STREAM_RAW_NUM;
    }

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 GetRawStreamNumInBuffer( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum )
  功能    将原始码流集合中已被推送但尚未被切割的码流包数和已切割但未被从buffer中释放的码流包数，
  目的是获得目前的码流占用情况。
  参数    pRawStreamArray 指向原始码流集合
  返回值  成功返回pStreamNum码流包数，并返回FMW_OK,失败则返回错误码（负整数）
 ************************************************************************/
SINT32 GetRawStreamNumInBuffer(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum)
{
    FMW_ASSERT_RET( 0 != pRawStreamArray, FMW_ERR_PARAM );

    *pStreamNum = pRawStreamArray->Tail - pRawStreamArray->History;

    if (*pStreamNum < 0)
    {
        *pStreamNum += MAX_STREAM_RAW_NUM;
    }

    return FMW_OK;
}



/*========================================================================
  part2.    stream segment management module
  ========================================================================*/
/************************************************************************
  原型    SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UADDR  BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize )
  功能    为码流片段集合配置必要的信息，如码流片段缓冲区的首地址、长度等。
  参数    pStreamSegArray 指向切割码流片段集合
  BufPhyAddr  码流片段缓冲区物理地址
  BufSize 码流片段缓冲区大小，单位：字节
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UADDR  BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize )
{
    FMW_ASSERT_RET( (NULL!=pStreamSegArray && 0!=BufPhyAddr && NULL!=pBufVirAddr &&
                BufSize>=SM_MIN_SEG_BUF_SIZE), FMW_ERR_PARAM );

    memset( pStreamSegArray, 0, sizeof(SEG_ARRAY_S) );

    pStreamSegArray->SegBufPhyAddr   = BufPhyAddr;
    pStreamSegArray->pSegBufVirAddr  = pBufVirAddr;
    pStreamSegArray->SegBufReadAddr  = BufPhyAddr;
    pStreamSegArray->SegBufWriteAddr = BufPhyAddr;
    pStreamSegArray->SegBufSize      = BufSize;

    return FMW_OK;
}

/************************************************************************
  原型    VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray )
  功能    将一组切割码流片段集合复位，清除其中所有记录，释放全部切割码流缓冲空间。
  参数    pStreamSegArray 指向切割码流片段集合
  返回值  无
 ************************************************************************/
VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray )
{
    FMW_ASSERT( NULL!=pStreamSegArray );

    memset( pStreamSegArray->StreamSeg, 0, sizeof(pStreamSegArray->StreamSeg) );

    pStreamSegArray->Head            = 0;
    pStreamSegArray->Tail            = 0;
    pStreamSegArray->History         = 0;	
    pStreamSegArray->SegBufReadAddr  = pStreamSegArray->SegBufPhyAddr;
    pStreamSegArray->SegBufWriteAddr = pStreamSegArray->SegBufPhyAddr;

    return;
}

/************************************************************************
  原型    VOID GetSegBuf( SEG_ARRAY_S *pStreamSegArray, UINT32 *pBufAddr, UINT32 *pBufLength )
  功能    获取码流片段缓冲区的地址和长度。
  SCD切割码流时需要配置缓冲区的顶底地址。
  参数    pStreamSegArray 指向切割码流片段集合
  pAddr   接收码流片段缓冲区首地址（物理地址）变量的指针
  pLength 接收码流片段缓冲区长度变量的指针
  返回值  无
 ************************************************************************/
VOID GetSegBuf( SEG_ARRAY_S* pStreamSegArray, UADDR* pBufAddr, UINT32* pBufLength )
{
    FMW_ASSERT( NULL != pStreamSegArray && NULL != pBufAddr && NULL != pBufLength );

// *pBufAddr   = ((pStreamSegArray->SegBufPhyAddr + 0x3) & (~0x3));
    *pBufAddr   = pStreamSegArray->SegBufPhyAddr;
    *pBufLength = pStreamSegArray->SegBufSize;

    return;
}

/************************************************************************
  原型    VOID GetFreeSegBuf( SEG_ARRAY_S *pStreamSegArray, UINT32 *pAddr, UINT32 *pLength )
  功能    获取空闲的码流片段缓冲空间，所有介于写地址和读地址只见的空间都被视为空闲空间。
  由于码流片段缓冲区是一个循环buffer，所以空闲区域可能卷绕，从而使得地址不连续。
  判断地址是否卷绕的依据是pAddr+pLength>buffer底部。
  参数    pStreamSegArray 指向切割码流片段集合
  pAddr   接收空闲空间首地址（物理地址）变量的指针
  pLength 接收空闲空间长度变量的指针
  返回值  无
 ************************************************************************/
VOID GetFreeSegBuf( SEG_ARRAY_S *pStreamSegArray, SINT32 *pAddr, SINT32 *pLength )
{
    SINT32 Len;

    FMW_ASSERT( NULL != pStreamSegArray && NULL != pAddr && NULL != pLength );

    *pAddr   = pStreamSegArray->SegBufWriteAddr;
    *pLength = 0;

    if (pStreamSegArray->SegBufWriteAddr > pStreamSegArray->SegBufReadAddr)
    {
        Len = pStreamSegArray->SegBufSize - 1 - 
            (pStreamSegArray->SegBufWriteAddr - pStreamSegArray->SegBufReadAddr);
    }
    else if(pStreamSegArray->SegBufWriteAddr < pStreamSegArray->SegBufReadAddr)
    {
        Len = pStreamSegArray->SegBufReadAddr - pStreamSegArray->SegBufWriteAddr - 1;
    }
    else
    {
        Len = pStreamSegArray->SegBufSize - 1;
    }

    FMW_ASSERT(Len <= pStreamSegArray->SegBufSize);

    *pLength = Len;

    return;
}

/************************************************************************
  原型    SINT32 InsertStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  功能    向特定的码流片段集中插入一个码流片段。
  本函数的任务有两个，第一是将待插入码流片段的描述信息加入到队列中，第二是更新码流片段缓冲区的写地址。
  参数    pStreamSegArray 指向切割码流片段集合
  pStreamSeg  待插入码流片段的描述信息
  返回值  FMW_OK --- 成功
  FMW_ERR_PARAM  --- 参数错误
  FMW_ERR_BUSY   --- 信息块满，不能插入
 ************************************************************************/
SINT32 InsertStreamSeg(SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg)
{
    STREAM_SEG_S *pTail;
    SINT32  Ret = FMW_OK;

    FMW_ASSERT_RET( NULL!=pStreamSegArray && NULL!=pStreamSeg , FMW_ERR_PARAM );

    /* 待插入码流片段的地址和长度不检查，默认由本函数的调用者保证其合理性 */

    if( (pStreamSegArray->Tail+1) % MAX_STREAM_SEG_NUM != pStreamSegArray->Head )  /* 码流片信息块够，直接插入 */
    {        
        pTail = &pStreamSegArray->StreamSeg[pStreamSegArray->Tail];
        memcpy( pTail, pStreamSeg, sizeof(STREAM_SEG_S) );
        SMSEG_SET_ISFRESH(pStreamSegArray->StreamSeg[pStreamSegArray->Tail]);
        pTail->StreamID = pStreamSegArray->Tail;

        pStreamSegArray->Tail = (pStreamSegArray->Tail+1) % MAX_STREAM_SEG_NUM;
        pStreamSegArray->SegBufWriteAddr = pStreamSeg->PhyAddr + pStreamSeg->LenInByte;
        pStreamSegArray->SegTotalSize += pStreamSeg->LenInByte;
        pStreamSegArray->SegFreshSize += pStreamSeg->LenInByte;
        pStreamSegArray->SegFreshNum++;
    }
    else  /* 码流片信息块满，如果不是强制插入则返回错误码，否则强行释放一包再插入 */
    {
        Ret = FMW_ERR_BUSY;
    }

    return Ret;
}

/************************************************************************
  原型    SINT32 GetStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  功能    从特定的码流片段集中取出一个码流片段：将处于队列头的码流片段信息取出。
  参数    pStreamSegArray 指向流片段集合
  pStreamSeg  存储码流片段的描述信息的结构指针
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 GetStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
{
    SINT32 i, Ret = FMW_ERR_NOTRDY;
    STREAM_SEG_S *pSeg;

    FMW_ASSERT_RET( NULL!=pStreamSegArray && NULL!=pStreamSeg , FMW_ERR_PARAM );

    pSeg = NULL;
    for(i=pStreamSegArray->Head;;)
    {
        if(i==pStreamSegArray->Tail) /*到头了，无码流片段可取*/
        {
            break;
        }
        else if( SMSEG_IS_FRESH(pStreamSegArray->StreamSeg[i]) ) /* 找到一个还没有访问过的，就它了 */
        {
            pSeg = &pStreamSegArray->StreamSeg[i];
            break;
        }
        else    /* 这个已经被取过了，看下一个 */
        {
            i = (i+1) % MAX_STREAM_SEG_NUM;
        }
    }

    if(NULL != pSeg)
    {
        memcpy(pStreamSeg, pSeg, sizeof(STREAM_SEG_S));
        SMSEG_SET_ISREAD(*pSeg);    /* 标记这个码流已被读走 */

        pStreamSegArray->SegFreshSize -= pSeg->LenInByte;
        pStreamSegArray->SegFreshNum--;
        SM_DOWN_CLIP_ZERO(pStreamSegArray->SegFreshSize);
        SM_DOWN_CLIP_ZERO(pStreamSegArray->SegFreshNum);

        dprint(PRN_SCD_INFO, "Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLastSeg=%d\n", pSeg->PhyAddr, pSeg->LenInByte, pSeg->IsLastSeg);
        Ret = FMW_OK;
    }
    else
    {
        Ret = FMW_ERR_NOTRDY;
    }

    return Ret;
}

/************************************************************************
  原型    SINT32 ReleaseStreamSeg( SEG_ARRAY_S *pStreamSegArray, UINT32 StreamID)
  功能    将ID为StreamID的码流片段释放，如果这个码流片段是历史上已读取但未释放的第一段码流，则同步更新码流片段缓冲区的读地址。
  参数    pStreamSegArray 指向流片段集合
  StreamID    待释放码流片段的ID
  如果StreamID取值在0~ MAX_STREAM_SEG_NUM-1之间则表示要释放索引号为StreamID的码流片段；
  如果StreamID = 0xffffffff，则表示释放第一个码流片段。这个参数的使用场景是，如果码流
  解析模块长时间不释放码流包，出于容错考虑SM模块需要强制释放第一包，以腾出空间来继续切割码
  流，避免死锁。这种情况下，无论第一个码流片段是否被读走，都强制释放。
  返回值  成功返回FMW_OK，否则返回错误码
 ************************************************************************/
SINT32 ReleaseStreamSeg(SEG_ARRAY_S *pStreamSegArray, UINT32 StreamID)
{
    SINT32 Ret = FMW_ERR_NOTRDY;
    UINT32 i = 0;
    STREAM_SEG_S *pSeg = NULL;

    FMW_ASSERT_RET( (NULL!=pStreamSegArray) &&
            ((StreamID<MAX_STREAM_SEG_NUM) || (StreamID==0xffffffff)), FMW_ERR_PARAM  );

    if( 0xffffffff == StreamID )  /* 要强制释放队头包 */
    {
        if( pStreamSegArray->Head != pStreamSegArray->Tail ) /* 只要队列不空总能释放 */
        {
            pSeg     = &pStreamSegArray->StreamSeg[pStreamSegArray->Head];
            StreamID = pStreamSegArray->Head;
            dprint(PRN_FATAL, "-------- forece release seg[%d] -----------\n", StreamID);
            for (i = 0; i < pSeg->LenInByte && i < 16; i++)
            {
                dprint(PRN_FATAL,"0x%02x,", pSeg->VirAddr[i]);
            }
            dprint(PRN_FATAL,"\n");
        }
    }
    else
    {
        for( i=pStreamSegArray->Head;; )
        {
            if( i == pStreamSegArray->Tail ) /* 扫描结束，未找到指ID的码流 */
            {
                break;
            }
            else if( i == (SINT32)StreamID ) /* 找到指定ID的码流，不知它能释放否... */
            {
                if( 1 == SMSEG_IS_READ(pStreamSegArray->StreamSeg[i]))
                {
                    pSeg = &pStreamSegArray->StreamSeg[i];
                }
                break;
            }

            i = (i+1)%MAX_STREAM_SEG_NUM;
        }
    }

    /* 若找到可释放的码流，则释放之 */
    if( NULL != pSeg )
    {
        SMSEG_SET_ISRELEASED(*pSeg); /* 标志这个码流已经被释放了 */

        dprint(PRN_SCD_INFO, "Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d StreamID=%d\n", pSeg->PhyAddr, pSeg->LenInByte, pSeg->IsLastSeg, StreamID);
        if( StreamID == (UINT32)pStreamSegArray->Head )  /* 若释放的是第一个码流，要同步更新读指针，释放空间供新一轮使用 */
        {
            for( i=pStreamSegArray->Head;; )
            {
                if(i >= MAX_STREAM_SEG_NUM)
                {
                    dprint(PRN_ERROR, "Array out of bound in function %s\n",__FUNCTION__);
                    Ret = FMW_ERR_PARAM;

                }
                if( i == pStreamSegArray->Tail ) /* 看来所有码流都释放掉了 */
                {
                    pStreamSegArray->Head = pStreamSegArray->Tail;
                    pStreamSegArray->SegBufReadAddr = pStreamSegArray->SegBufWriteAddr;
                    break;
                }
                else if( (i<(MAX_STREAM_SEG_NUM)) && (0 == SMSEG_IS_RELEASED(pStreamSegArray->StreamSeg[i]))) /* 到此为止 */
                {
                    pStreamSegArray->Head = i;
                    pStreamSegArray->SegBufReadAddr = pStreamSegArray->StreamSeg[i].PhyAddr;
                    break;
                }
                else  /* 后面可能还有 */
                {
                    i = (i+1)%MAX_STREAM_SEG_NUM;
                }
            }
        }

        pStreamSegArray->SegTotalSize -= pSeg->LenInByte;
        SM_DOWN_CLIP_ZERO(pStreamSegArray->SegTotalSize);

        Ret = FMW_OK;
    }
    else
    {
        //dprint(PRN_ERROR, "Release Err StreamID %d in function %s\n", StreamID,__FUNCTION__);
        Ret = FMW_ERR_NOTRDY;
    }

    return Ret;
}


/************************************************************************
  原型    SINT32 GetSegStreamSize( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize)
  功能    将码流片断集合中所有包的长度累加起来即为码流总量，目的是获得目前的码流占用情况。
  参数    pSegStreamArray 指向码流片断集合
  返回值  成功返回码流长度，否则返回错误码（负整数）

 ************************************************************************/
SINT32 GetSegStreamSize( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize)
{

    FMW_ASSERT_RET( 0 != pSegStreamArray, FMW_ERR_PARAM );
    *pStreamSize = pSegStreamArray->SegTotalSize;
    //FMW_ASSERT_RET( pSegStreamArray->SegBufSize < *pStreamSize, FMW_ERR_PARAM );

    return FMW_OK;
}

/************************************************************************
  原型    SINT32 GetSegStreamNum( SEG_ ARRAY_S *pSegStreamArray, SINT32 *pStreamNum )
  功能    将码流片断集合中已被推送但尚未被释放的码流包数，目的是获得目前的码流占用情况。
  参数    pSegStreamArray 指向码流片断集合
  返回值  成功返回码流包数，否则返回错误码（负整数）
 ************************************************************************/
SINT32 GetSegStreamNum( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamNum)
{   
    //SINT32 i, idx;
    //SINT32 StreamCount;

    FMW_ASSERT_RET( 0 != pSegStreamArray, FMW_ERR_PARAM );
    
    *pStreamNum = pSegStreamArray->Tail - pSegStreamArray->Head;

    if (*pStreamNum < 0)
    {
        *pStreamNum += MAX_STREAM_SEG_NUM;
    }
#if 0

    idx = pSegStreamArray->Head;
    *pStreamNum = 0;

    for( i = 0; i < StreamCount; i++ )
    {  
        if ( 0 == SMSEG_IS_RELEASED(pSegStreamArray->StreamSeg[idx]))
        {
            (*pStreamNum)++;
        }

        idx++;
        if( idx >= MAX_STREAM_SEG_NUM )
        {
            idx -= MAX_STREAM_SEG_NUM;
        }
    }
#endif
    return FMW_OK;
}

/************************************************************************
  原型    SINT32 GetSegStreamNum( SEG_ ARRAY_S *pSegStreamArray, SINT32 *pStreamNum )
  功能    将码流片断集合中已被推送但尚未被释放的码流包数，目的是获得目前的码流占用情况。
  参数    pSegStreamArray 指向码流片断集合
  返回值  成功返回码流包数，否则返回错误码（负整数）
 ************************************************************************/
VOID GetFreshSegStream( SEG_ARRAY_S *pSegStreamArray, SINT32 *pFreshNum, SINT32 *pFreshSize)
{
    FMW_ASSERT( 0 != pSegStreamArray );

    *pFreshNum = pSegStreamArray->SegFreshNum;
    *pFreshSize = pSegStreamArray->SegFreshSize;

    return;
}

/* 准备休眠: 收到此命令后把当前工作完成，但不会寻找下一个解码通道 */
SINT32 SCDDRV_PrepareSleep(VOID)
{
    SINT32 ret = SCDDRV_OK;

    if (s_eScdDrvSleepStage == SCDDRV_SLEEP_STAGE_NONE)
    {
        if (0 == s_SmIIS.SCDState)
        {
            s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_SLEEP;
        }
        else
        {
            s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_PREPARE;
        }

        ret = SCDDRV_OK;
    }
    else
    {
        ret = SCDDRV_ERR;
    }

    return ret;
}

/* 查询休眠: 返回休眠进行到何种阶段 */
SCDDRV_SLEEP_STAGE_E SCDDRV_GetSleepStage(VOID)
{
    return s_eScdDrvSleepStage;
}

/* 强制休眠: 无法自然休眠，强制其进入sleep */
VOID SCDDRV_ForceSleep(VOID)
{
    if (s_eScdDrvSleepStage != SCDDRV_SLEEP_STAGE_SLEEP)
    {
        s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_SLEEP;
    }

    return;
}

/* 退出休眠: 恢复正常运行 */
VOID SCDDRV_ExitSleep(VOID)
{
    SCDDRV_OpenHardware();
    s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_NONE;
    return;
}


/************************************************************************
  原型    SINT32 SM_Reset ( SINT32 SmID )
  功能    本函数用以复位一个码流管理模块的实例， 
  本函数使得ID号为SmID的码流管理模块实例的所有状态都回到初始值。
  参数    SmID    标识码流管理模块的上下文信息。在多路解码中，每一路解码器都有一个码流管理模块的
  实例，SmID指向某个特定的实例。
  返回值  成功返回FMW_OK，否则返回特定的错误码
 ************************************************************************/
SINT32 SM_Reset (SINT32 SmID)
{   
    SINT32 RawNum = 0;
    SM_CFG_S TmpCfg;
    SINT32   TmpMode;
    UINT32   TmpHeaderLen;    
    UINT8    TmpHeaderBuf[HEADER_BUFFER_SIZE];
    SM_INSTANCE_S *pSmInstArray = NULL;

    SM_CHECK_VALUE(SmID, 0, SM_MAX_SMID-1, return FMW_ERR_PARAM);

    pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    if (pSmInstArray == NULL)
    {
        dprint(PRN_FATAL, "line: %d, pSmInstArray is NULL!\n", __LINE__);
        return FMW_ERR_PARAM;
    }

    /* 备份必要信息 */
    memcpy( &TmpCfg, &pSmInstArray->Config, sizeof(SM_CFG_S) );
    TmpMode = pSmInstArray->Mode;

    /* VC1 REAL8等协议在seek情况下，OMX通路不会重新送config数据，因此需要保留 */
    TmpHeaderLen = pSmInstArray->HeaderLen;
    memcpy(TmpHeaderBuf, pSmInstArray->HeaderBuf, sizeof(pSmInstArray->HeaderBuf));

    /* 停掉这个通道 */
    SM_Stop(SmID);

    /* 释放所持有的全部raw数据，从history开始 */
    if(FMW_OK != GetRawStreamNum(&pSmInstArray->RawPacketArray, &RawNum))
    {
        dprint(PRN_DBG, "%s %d FMW_OK !=  GetRawStreamNum !!\n",__FUNCTION__,__LINE__);
    }    
    DeleteRawPacket(&(pSmInstArray->RawPacketArray), (UINT32)RawNum);
    DeleteRawPacketInBuffer(SmID, 1);

    /* 完全清除实例内部信息 */
    memset(pSmInstArray, 0, sizeof(SM_INSTANCE_S) );
    pSmInstArray->LastPts = (UINT64)(-1);
    pSmInstArray->UpMsgStepNum = SM_SCD_UP_INFO_NUM;

    /* 恢复实例的配置，模式等信息 */
    SM_Config(SmID, &TmpCfg);
    if( SM_INST_MODE_WORK == TmpMode || SM_INST_MODE_WAIT == TmpMode )
    {
        pSmInstArray->Mode = SM_INST_MODE_WORK;  /* 使之处于运行状态 */
    }
    else
    {
        pSmInstArray->Mode = SM_INST_MODE_IDLE;  /* 使之处于非运行状态 */
    }
    
    pSmInstArray->HeaderLen = TmpHeaderLen;
    memcpy(pSmInstArray->HeaderBuf, TmpHeaderBuf, sizeof(pSmInstArray->HeaderBuf));
    
    return FMW_OK;
}


SINT32 SM_ClearInst (SINT32 SmID)
{
    SM_CHECK_VALUE(SmID, 0, SM_MAX_SMID-1, return FMW_ERR_PARAM);

    /* 完全清除实例内部信息 */
    memset( s_SmIIS.pSmInstArray[SmID], 0, sizeof(SM_INSTANCE_S) );
    s_SmIIS.pSmInstArray[SmID]->LastPts = (UINT64)(-1);

    return FMW_OK;
}

/* 
   给对应通道分配低延迟上下文空间
*/
SINT32 SM_AllocDSPCtxMem(SINT32 SmID)
{
    SINT32 Size    = 0;
    SINT32 Offset  = 0;
    UADDR  MemAddr = 0;
    MEM_RECORD_S stTempMem;
    MEM_RECORD_S  *pstMem    = NULL;
    DSP_CTX_MEM_S *pstDSPMem = NULL;

    Offset = 0;
    Size = DSP_SPS_MSG_SIZE + DSP_PPS_MSG_SIZE + 32;
    pstDSPMem = &s_SmIIS.DspCtxMem[SmID];
    pstMem = &stTempMem;

    memset(pstMem, 0, sizeof(MEM_RECORD_S));

    if( MEM_MAN_OK == MEM_AllocMemBlock("DSP_CTX", Size, pstMem, 0) )
    {
        MEM_AddMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);
    }
    else
    {
        dprint(PRN_FATAL,"%s Alloc mem for DSP (SPS PPS) failed!\n", __func__);
        return FMW_ERR_SCD;
    }

    memcpy(&(pstDSPMem->stBaseMemInfo), pstMem, sizeof(MEM_RECORD_S));
    MemAddr = pstMem->PhyAddr;
    Offset = ((MemAddr + 15) & (~15)) - MemAddr;

    pstDSPMem->DspSpsMsgMemAddr = MemAddr + Offset;
    pstDSPMem->pDspSpsMsgMemVirAddr = MEM_Phy2Vir(pstDSPMem->DspSpsMsgMemAddr);
    if (NULL == pstDSPMem->pDspSpsMsgMemVirAddr)
    {
        dprint(PRN_FATAL,"%s pDspSpsMsgMemVirAddr is NULL!\n", __func__);
        return FMW_ERR_SCD;
    }
    pstDSPMem->DspSpsMsgMemSize = DSP_SPS_MSG_SIZE;
    memset(pstDSPMem->pDspSpsMsgMemVirAddr, 0, DSP_SPS_MSG_SIZE);
    Offset += DSP_SPS_MSG_SIZE;

    pstDSPMem->DspPpsMsgMemAddr = MemAddr + Offset;
    pstDSPMem->pDspPpsMsgMemVirAddr = MEM_Phy2Vir(pstDSPMem->DspPpsMsgMemAddr);
    if (NULL == pstDSPMem->pDspPpsMsgMemVirAddr)
    {
        dprint(PRN_FATAL,"%s pDspPpsMsgMemVirAddr is NULL!\n", __func__);
        return FMW_ERR_SCD;
    }
    pstDSPMem->DspPpsMsgMemSize = DSP_PPS_MSG_SIZE;
    memset(pstDSPMem->pDspPpsMsgMemVirAddr, 0, DSP_PPS_MSG_SIZE);
    Offset += DSP_PPS_MSG_SIZE;

    return FMW_OK;

}


/*
   为对应通道释放低延迟上下文空间
   */
VOID SM_DeletDSPCtxMem(MEM_RECORD_S *pstDSPMem)
{
    /* 释放资源 ctx */
    if ( 0 != pstDSPMem->PhyAddr )
    {
        MEM_ReleaseMemBlock(pstDSPMem->PhyAddr, (UINT8 *)pstDSPMem->VirAddr);
    }
    else
    {
        dprint(PRN_FATAL, "pstDSPMem->PhyAddr = 0 is not right address\n");
    }

    MEM_DelMemRecord(pstDSPMem->PhyAddr, pstDSPMem->VirAddr, pstDSPMem->Length);

    return ;
}


/* SCD驱动全局打开 */
SINT32 SM_OpenSCDDrv(SCD_OPEN_PARAM_S *pOpenParam)
{
    SINT32 Offset;
    UADDR MemAddr;

    if(NULL == pOpenParam)
    {
        dprint(PRN_FATAL, "%s: pOpenParam = NULL\n",__func__);
        return FMW_ERR_SCD;
    }
    MemAddr = pOpenParam->MemAddr;
    
    SCDDRV_OpenHardware();

    if( 1 == s_SmIIS.IsScdDrvOpen )
    {
        dprint(PRN_FATAL, "s_SmIIS.IsScdDrvOpen %d is not opened.\n");
        return FMW_ERR_SCD;
    }

    /* 复位SCD硬件 */
    ResetSCD();

    memset( &s_SmIIS, 0, sizeof(SM_IIS_S) );
    s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_NONE;

    /* 尝试划分上／下行消息区 */
    Offset = ((MemAddr+15) & (~15)) - MemAddr;

    s_SmIIS.ScdDrvMem.HwMemAddr = MemAddr;
    s_SmIIS.ScdDrvMem.HwMemSize = pOpenParam->MemSize;

    s_SmIIS.ScdDrvMem.DownMsgMemAddr = MemAddr + Offset;
    s_SmIIS.ScdDrvMem.pDownMsgMemVirAddr = (UINT32 *)MEM_Phy2Vir(s_SmIIS.ScdDrvMem.DownMsgMemAddr);
    s_SmIIS.ScdDrvMem.DownMsgMemSize = SM_MAX_DOWNMSG_SIZE;
    Offset += (SM_MAX_DOWNMSG_SIZE+15) & (~15);

    s_SmIIS.ScdDrvMem.UpMsgMemAddr = MemAddr + Offset;
    s_SmIIS.ScdDrvMem.pUpMsgMemVirAddr = (SINT32 *)MEM_Phy2Vir(s_SmIIS.ScdDrvMem.UpMsgMemAddr);
    s_SmIIS.ScdDrvMem.UpMsgMemSize = SM_MAX_UPMSG_SIZE;
    Offset += (SM_MAX_UPMSG_SIZE+15) & (~15);
    
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    s_SmIIS.ScdDrvMem.DvmMemAddr = MemAddr + Offset;
    s_SmIIS.ScdDrvMem.pDvmMemVirAddr = MEM_Phy2Vir(s_SmIIS.ScdDrvMem.DvmMemAddr);
    if(NULL == s_SmIIS.ScdDrvMem.pDvmMemVirAddr)
    {
        dprint(PRN_FATAL, "%s: s_SmIIS.ScdDrvMem.pDvmMemVirAddr = NULL\n",__func__);
        return VDMHAL_ERR;
    }
    memset(s_SmIIS.ScdDrvMem.pDvmMemVirAddr,0,DVM_SIZE);
    s_SmIIS.ScdDrvMem.DvmMemSize = DVM_SIZE;
    Offset += (DVM_SIZE+15) & (~15);

    s_SmIIS.ScdDrvMem.DspSedTopMemAddr = MemAddr + Offset;  
    s_SmIIS.ScdDrvMem.pDspSedTopMemVirAddr = MEM_Phy2Vir(s_SmIIS.ScdDrvMem.DspSedTopMemAddr);
    if(NULL == s_SmIIS.ScdDrvMem.pDspSedTopMemVirAddr)
    {
        dprint(PRN_FATAL, "%s: s_SmIIS.ScdDrvMem.pDspSedTopMemVirAddr = NULL\n",__func__);
        return VDMHAL_ERR;
    }
    s_SmIIS.ScdDrvMem.DspSedTopMemSize = DSP_SED_TOP_SIZE;
    memset(s_SmIIS.ScdDrvMem.pDspSedTopMemVirAddr,0,DSP_SED_TOP_SIZE);
    Offset += (DSP_SED_TOP_SIZE+15) & (~15);

    s_SmIIS.ScdDrvMem.DspCaMnMemAddr = MemAddr + Offset;
    s_SmIIS.ScdDrvMem.pDspCaMnMemVirAddr = MEM_Phy2Vir(s_SmIIS.ScdDrvMem.DspCaMnMemAddr);
    if(NULL == s_SmIIS.ScdDrvMem.pDspCaMnMemVirAddr)
    {
        dprint(PRN_FATAL, "%s: s_SmIIS.ScdDrvMem.pDspCaMnMemVirAddr = NULL\n",__func__);
        return VDMHAL_ERR;
    }
    memset(s_SmIIS.ScdDrvMem.pDspCaMnMemVirAddr,0,CA_MN_SIZE);
    s_SmIIS.ScdDrvMem.DspCaMnMemSize = CA_MN_SIZE;
    Offset += (CA_MN_SIZE+15) & (~15);
    //写码表
    WriteCabacTabDsp(s_SmIIS.ScdDrvMem.DspCaMnMemAddr);
#endif

#if defined(VFMW_AVSPLUS_SUPPORT) || (VFMW_SCD_LOWDLY_SUPPORT)
    g_hex_base_addr= MemAddr + Offset;
    g_hex_base_addr = (g_hex_base_addr+127)/128*128;
    g_hex_base_vir_addr = MEM_Phy2Vir(g_hex_base_addr);
    if(NULL == g_hex_base_vir_addr)
    {
        dprint(PRN_FATAL, "%s: g_hex_base_vir_addr = NULL\n",__func__);
        return VDMHAL_ERR;
    }
    g_hex_len = 0x1180*4;
    Offset += g_hex_len;
#endif

    /* 检查MemSize是否够用，以及地址是否有效 */
    if( (Offset > pOpenParam->MemSize) || NULL == s_SmIIS.ScdDrvMem.pDownMsgMemVirAddr
            || NULL == s_SmIIS.ScdDrvMem.pUpMsgMemVirAddr )
    {
       dprint(PRN_FATAL, "Invalid: Offset %d > MemSize %d, pDownMsgMemVirAddr = %p, pUpMsgMemVirAddr = %p\n", Offset, pOpenParam->MemSize, s_SmIIS.ScdDrvMem.pDownMsgMemVirAddr, s_SmIIS.ScdDrvMem.pUpMsgMemVirAddr);
        return FMW_ERR_SCD;
    }
    else
    {
        s_SmIIS.IsScdDrvOpen = 1;  /* 宣告SCD打开成功 */
    }

    return FMW_OK;
}

/* SCD驱动全局关闭 */
SINT32 SM_CloseSCDDrv(VOID)
{
    SINT32 i;

    /* 所有实例逐个停掉 */
    for( i = 0; i < MAX_CHAN_NUM; i++ )
    {
        (VOID)SM_Stop(i);
    }

    /* 复位SCD硬件 */
    ResetSCD();

    /* 清除上下文 */
    memset( &s_SmIIS, 0, sizeof(SM_IIS_S) );

    SCDDRV_CloseHardware();
    
    return FMW_OK;
}


/************************************************************************
  原型    SINT32 SetMaxSegSize(SINT32 ChanID)
  功能    打印Seg队列的详细情况
  参数    通道ID
  返回值  对应通道SCD Buf 最大允许值
 ********************************** *************************************/
SINT32 SetMaxSegSize(SINT32 ChanID, SM_CFG_S *pSmCfg)
{
    SINT32 MaxSegSize;
    SINT32 ChanWidth, ChanHeight;
    VDEC_CHAN_CAP_LEVEL_E eCapLevel;

    eCapLevel = VCTRL_GetChanCapLevel(ChanID);

    if (CAP_LEVEL_BUTT <= eCapLevel)
    {
        dprint(PRN_FATAL, "SetMaxSegSize get eCapLevel failed!\n"); 
        return FMW_ERR_PARAM;
    }

    if (CAP_LEVEL_USER_DEFINE_WITH_OPTION == eCapLevel)
    {
        ChanWidth = VCTRL_GetChanWidth(ChanID);
        ChanHeight = VCTRL_GetChanHeight(ChanID);
        if(VCTRL_ERR == ChanWidth || VCTRL_ERR == ChanHeight )
        {
            dprint(PRN_FATAL, "SetMaxSegSize get ChanWidth/ChanHeight failed!\n"); 
            return FMW_ERR_PARAM;
        }
        else
        {
            if((ChanWidth*ChanHeight) <= (1920*1088)) 
            {
                MaxSegSize = 3*1024*1024;
            }
            else
            {
                MaxSegSize = 20*1024*1024;
            }
        }
   }
   else
   {
        if((VFMW_H264 != pSmCfg->VidStd) && (VFMW_HEVC != pSmCfg->VidStd))
        {
            eCapLevel = CAP_LEVEL_H264_FHD;
        }
        switch(eCapLevel)
        {
            case CAP_LEVEL_HEVC_UHD:
                MaxSegSize = 20*1024*1024;
                break;

            case CAP_LEVEL_1488x1280:
            case CAP_LEVEL_1280x1488:
            case CAP_LEVEL_2160x1280:
            case CAP_LEVEL_1280x2160:
            case CAP_LEVEL_2160x2160:
                MaxSegSize = 4*1024*1024;
                break;

            case CAP_LEVEL_4096x2160:
            case CAP_LEVEL_2160x4096:
                MaxSegSize = 20*1024*1024;
                break;

            case CAP_LEVEL_4096x4096:
            case CAP_LEVEL_8192x4096:
            case CAP_LEVEL_4096x8192:
                MaxSegSize = 20*1024*1024;
                break;

            case CAP_LEVEL_8192x8192:
                MaxSegSize = 20*1024*1024;
                break;

            default:
                MaxSegSize = 3*1024*1024;
                break;
        }
    }


    return MaxSegSize;
}


/************************************************************************
  原型    SINT32 SM_Config ( SINT32 SmID, SM_CFG_S *pSmCfg )
  功能    本函数用以配置一个码流管理模块的实例，在这个实例开始工作之前，必须调用此函数给它配置必要的信息。
  参数    SmID    标识码流管理模块的上下文信息。在多路解码中，每一路解码器都有一个码流管理模块的实例，
  SmID指向某个特定的实例。
  pSmCfg  SM实例的配置信息
  返回值  成功返回FMW_OK，否则返回特定的错误码
 ************************************************************************/
SINT32 SM_Config (SINT32 SmID, SM_CFG_S *pSmCfg)
{
    SINT32 Offset, ByteOffsetInWord;
    SM_BUFFERCFG_S *pBufAddrCfg = NULL;
    UADDR TmpPhyAddr;
    UINT8* pTmpVirAddr;
    SINT32 SmMaxSegBufSize;
    SM_INSTANCE_S *pSmInstArray = NULL;
	SINT32 s32ScdBlankSegLen=0;

    if ((SmID < 0) || (SmID >= SM_MAX_SMID) || (NULL == pSmCfg))
    {
        dprint(PRN_FATAL, "line: %d, SmID = %d, pSmCfg = %p is not expected!\n", __LINE__, SmID, pSmCfg);        
        return FMW_ERR_PARAM;
    }

    pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    if (NULL == pSmInstArray)
    {
        return FMW_ERR_PARAM;	
    }

    /* 只在第一次SM_Config()时，才重新初始化SegArray，此后的SM_Config()都只是修改配置，不重建SegArray */
    if( pSmInstArray->Config.BufPhyAddr != pSmCfg->BufPhyAddr )
    {
        FMW_ASSERT_RET((0 != pSmCfg->BufPhyAddr), FMW_ERR_PARAM);
        FMW_ASSERT_RET((0 != pSmCfg->pBufVirAddr), FMW_ERR_PARAM);
        //SM_CHECK_VALUE(pSmCfg->VidStd, VFMW_START_RESERVED, VFMW_END_RESERVED - 1, return FMW_ERR_PARAM);

        pBufAddrCfg = &pSmInstArray->BufAddrCfg;

        pBufAddrCfg->DownMsgPhyAddr = s_SmIIS.ScdDrvMem.DownMsgMemAddr;
        pBufAddrCfg->pDownMsgVirAddr = s_SmIIS.ScdDrvMem.pDownMsgMemVirAddr;
        pBufAddrCfg->DownMsgSize = s_SmIIS.ScdDrvMem.DownMsgMemSize;

        pBufAddrCfg->UpMsgPhyAddr = s_SmIIS.ScdDrvMem.UpMsgMemAddr;
        pBufAddrCfg->pUpMsgVirAddr = s_SmIIS.ScdDrvMem.pUpMsgMemVirAddr;
        pBufAddrCfg->UpMsgSize = s_SmIIS.ScdDrvMem.UpMsgMemSize;
        pBufAddrCfg->UpMsgNum = MAX_STREAM_SEG_NUM;
#ifdef VFMW_SCD_LOWDLY_SUPPORT
        pBufAddrCfg->DspSpsMsgMemAddr         = s_SmIIS.DspCtxMem[SmID].DspSpsMsgMemAddr;
        pBufAddrCfg->pDspSpsMsgMemVirAddr     = s_SmIIS.DspCtxMem[SmID].pDspSpsMsgMemVirAddr;
        pBufAddrCfg->DspSpsMsgMemSize         = s_SmIIS.DspCtxMem[SmID].DspSpsMsgMemSize;

        pBufAddrCfg->DspPpsMsgMemAddr         = s_SmIIS.DspCtxMem[SmID].DspPpsMsgMemAddr;
        pBufAddrCfg->pDspPpsMsgMemVirAddr     = s_SmIIS.DspCtxMem[SmID].pDspPpsMsgMemVirAddr;
        pBufAddrCfg->DspPpsMsgMemSize         = s_SmIIS.DspCtxMem[SmID].DspPpsMsgMemSize;

        pBufAddrCfg->DvmMemAddr               = s_SmIIS.ScdDrvMem.DvmMemAddr;
        pBufAddrCfg->pDvmMemVirAddr           = s_SmIIS.ScdDrvMem.pDvmMemVirAddr;
        pBufAddrCfg->DvmMemSize               = s_SmIIS.ScdDrvMem.DvmMemSize;

        pBufAddrCfg->DspSedTopMemAddr         = s_SmIIS.ScdDrvMem.DspSedTopMemAddr;
        pBufAddrCfg->pDspSedTopMemVirAddr     = s_SmIIS.ScdDrvMem.pDspSedTopMemVirAddr;
        pBufAddrCfg->DspSedTopMemSize         = s_SmIIS.ScdDrvMem.DspSedTopMemSize;

        pBufAddrCfg->DspCaMnMemAddr           = s_SmIIS.ScdDrvMem.DspCaMnMemAddr;
        pBufAddrCfg->pDspCaMnMemVirAddr       = s_SmIIS.ScdDrvMem.pDspCaMnMemVirAddr;
        pBufAddrCfg->DspCaMnMemSize           = s_SmIIS.ScdDrvMem.DspCaMnMemSize;
#endif
        if(VFMW_AVS == pSmCfg->VidStd)
        {
            s32ScdBlankSegLen = SCD_AVS_SEG_BLANK_LEN;
        }
		else
		{
		   s32ScdBlankSegLen = SCD_SEG_BLANK_LEN;
		}
        TmpPhyAddr = (pSmCfg->BufPhyAddr + 15) & 0xfffffff0;
        ByteOffsetInWord = TmpPhyAddr - pSmCfg->BufPhyAddr;
        pTmpVirAddr = pSmCfg->pBufVirAddr + ByteOffsetInWord;
        Offset = s32ScdBlankSegLen;

        pBufAddrCfg->SegBufPhyAddr = TmpPhyAddr + s32ScdBlankSegLen;
        pBufAddrCfg->pSegBufVirAddr = pTmpVirAddr + s32ScdBlankSegLen;

        /* 根据通道解码能力，设置 SmMaxSegBufSize 值*/   
        SmMaxSegBufSize = SetMaxSegSize(SmID, pSmCfg);
        if (FMW_ERR_PARAM == SmMaxSegBufSize)  // 获取失败时，设置默认值
        {
            SmMaxSegBufSize = 2*1024*1024;
        }

        if  ( (pSmCfg->BufSize - ByteOffsetInWord) > SmMaxSegBufSize)
        {
            pBufAddrCfg->SegBufSize =  (SmMaxSegBufSize - s32ScdBlankSegLen - 1024); // y00226912  (SM_MAX_SEG_BUF_SIZE - SCD_SEG_BLANK_LEN - 1024);    // 顶部留白xk,底部留白1K
        }
        else
        {
            pBufAddrCfg->SegBufSize = pSmCfg->BufSize - ByteOffsetInWord - s32ScdBlankSegLen - 1024;    // 顶部留白xk,底部留白1K
            if( pBufAddrCfg->SegBufSize < SM_MIN_SEG_BUF_SIZE )
            {
                return FMW_ERR_PARAM;
            }
        }

        ConfigStreamSegArray(&pSmInstArray->StreamSegArray, pBufAddrCfg->SegBufPhyAddr, pBufAddrCfg->pSegBufVirAddr, pBufAddrCfg->SegBufSize);        

        /*Check input pSmCfg param*/
        memcpy(&pSmInstArray->Config, pSmCfg, sizeof(SM_CFG_S));
    }

    /* 存储配置信息 */
    memcpy( &pSmInstArray->Config, pSmCfg, sizeof(SM_CFG_S) );

    pSmInstArray->UpMsgStepNum = SM_SCD_UP_INFO_NUM;
    if (VFMW_MPEG4 == pSmCfg->VidStd)
    { 
#ifdef SCD_MP4_SLICE_ENABLE
        pSmInstArray->UpMsgStepNum = MAX_SM_SCD_UP_INFO_NUM;
#endif
    }

    pSmInstArray->InstID = SmID;
    return FMW_OK;
}


SINT32 SM_Start (SINT32 SmID)
{
    SINT32 ret = FMW_OK;

    if(s_SmIIS.pSmInstArray[SmID] != NULL
            && s_SmIIS.pSmInstArray[SmID]->Config.BufSize != 0  
            && SM_INST_MODE_IDLE == s_SmIIS.pSmInstArray[SmID]->Mode  )
    {
        s_SmIIS.pSmInstArray[SmID]->Mode = SM_INST_MODE_WORK;
        ret = FMW_OK;
    }
    else
    {
        ret = FMW_ERR_SCD;
    }

    return FMW_ERR_SCD;
}

SINT32 SM_Stop (SINT32 SmID)
{
    SINT32 i;


    if( s_SmIIS.pSmInstArray[SmID] == NULL
        || SM_INST_MODE_IDLE == s_SmIIS.pSmInstArray[SmID]->Mode )
    {
        return FMW_OK;
    }

    s_SmIIS.pSmInstArray[SmID]->Mode = SM_INST_MODE_IDLE;

    /* 确保此实例此后真正不被调度 */
    for( i = 0; i < 50; i++ )
    {
        if( s_SmIIS.SCDState == 0 )
        {
            return FMW_OK;
        }
        else
        {
            //OSAL_MSLEEP(10);
        }
    }

    return FMW_ERR_SCD;
}




/************************************************************************
  原型    SINT32 SM_GetInfo( SINT32 SmID, SM_INST_INFO_S *pSmInstInfo )
  功能    本函数查询码流管理模块中原始码流已累计了多少包，已切割待解码的码流有多少段。在多路解码环境下，上层调度程序可能需要根据每一路的这些信息来决定将SCD分配给哪一路去切割码流。
  参数    SmID    码流管理模块的实例的标识
  pSmInstInfo  存放实例信息的结构
  返回值  FMW_ERR_PARAM or FMW_OK

 ************************************************************************/
//SINT32 SM_GetInfo(SINT32 SmID, SINT32 *pRawNum, SINT32 *pRawSize, SINT32 *pSegNum, SINT32 *pSegSize)
SINT32 SM_GetInfo( SINT32 SmID, SM_INST_INFO_S *pSmInstInfo )
{
    SINT32 Ret;
    SM_INSTANCE_S *pSmInstArray = NULL;

    SM_CHECK_VALUE(SmID, 0, SM_MAX_SMID-1, return FMW_ERR_PARAM);

    pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    if (NULL == pSmInstArray)
    {
        if (NULL != pSmInstInfo)
        {
            pSmInstInfo->InstMode = SM_INST_MODE_IDLE;
        }
        return FMW_ERR_PARAM;
    }

    pSmInstInfo->InstMode = pSmInstArray->Mode;

    pSmInstInfo->numReadSegFail = pSmInstArray->numReadSegFail;

    Ret = GetRawStreamNum(&pSmInstArray->RawPacketArray, &pSmInstInfo->RawNum);
    if (FMW_OK != Ret)
    {
        //return FMW_OK;
    }
    
    Ret = GetRawStreamSize(&pSmInstArray->RawPacketArray, &pSmInstInfo->TotalRawSize);
    if (FMW_OK != Ret)
    {
        //return FMW_OK;
    }
    
    Ret = GetSegStreamNum(&pSmInstArray->StreamSegArray, &pSmInstInfo->SegNum);
    if (FMW_OK != Ret)
    {
        //return FMW_OK;
    }
    
    Ret = GetSegStreamSize(&pSmInstArray->StreamSegArray, &pSmInstInfo->TotalSegSize);
    if (FMW_OK != Ret)
    {
        //return FMW_OK;
    }

    return FMW_OK;   
}

/************************************************************************
  原型    SINT32 SM_PushRaw(SINT32 SmID, RAW_PACKET_S *pRawPacket)
  功能    外部程序调用本函数向码流管理模块推送一段码流，推送过程只是将码流的相关信息记录到SM模块的内部结构中，并不一定立即执行码流的切分工作。
  参数    SmID    码流管理模块的实例的标识
  PhyAddr 原始码流的物理地址
  VirAddr 原始码流的虚拟地址
  Len 原始码流的长度，以字节为单位
  Pts 原始码流的节目时间戳(PTS)
  返回值  成功返回FMW_OK，否则返回特定的错误码
 ************************************************************************/
SINT32 SM_PushRaw(SINT32 SmID, STREAM_DATA_S *pRawPacket)
{    
    SINT32 Ret;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];

    FMW_ASSERT_RET( 0 != pRawPacket->PhyAddr, FMW_ERR_PARAM );
    FMW_ASSERT_RET( 0 != pRawPacket->VirAddr, FMW_ERR_PARAM );
    FMW_ASSERT_RET( 0 != pSmInstArray, FMW_ERR_PARAM );

    Ret = InsertRawPacket(&pSmInstArray->RawPacketArray, pRawPacket);

    return Ret;

}


SINT32 SM_CopyRawToSeg(SINT32 SmID, STREAM_SEG_S *pStreamSeg)
{
    STREAM_DATA_S *pRawPacket;
    RAW_ARRAY_S *pRawPacketArray;
    SEG_ARRAY_S *pStreamSegArray;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    //STREAM_SEG_S *pTail;
    UADDR TmpPhyAddr;
    UINT8 *TmpVirAddr;
    UINT8 *SrcVirAddr = 0;
    SINT32 SrcLength = 0, TotalSrcLength = 0, SegFreeBufLen=0;
    UINT32 index, rawnum, i, rawnum1;

    index = 0;
    rawnum = 0;
    FMW_ASSERT_RET( NULL!=pSmInstArray, FMW_ERR_PARAM );

    pRawPacketArray = &pSmInstArray->RawPacketArray;
    pStreamSegArray = &pSmInstArray->StreamSegArray;

    FMW_ASSERT_RET( NULL!=pRawPacketArray && NULL!=pStreamSegArray && NULL!=pStreamSeg, FMW_ERR_PARAM );


    //Find a filled raw packet
    if (pRawPacketArray->Tail != pRawPacketArray->Head)
    {
        pRawPacket = &pRawPacketArray->RawPacket[pRawPacketArray->Head];
    }
    else
    {
        return FMW_ERR_BUSY;
    }

    index = pRawPacketArray->Head;
    TotalSrcLength = pRawPacket->Length;
    rawnum = 1;
    rawnum1 = 1;
    while (pRawPacketArray->RawPacket[index].is_not_last_packet_flag)
    {
        rawnum++;
        index = (index+1) % MAX_STREAM_RAW_NUM;
        TotalSrcLength += pRawPacketArray->RawPacket[index].Length;
        if (index == pRawPacketArray->Tail)
        {
            return FMW_ERR_BUSY ;  
        }
        if (rawnum > MAX_STREAM_RAW_NUM)
        {
            return FMW_ERR_BUSY;  
        }
    }

    ResetStreamSegArray(pStreamSegArray);

    if (TotalSrcLength > pStreamSegArray->SegBufSize - SM_MIN_SEG_BUF_SIZE)
    {
        dprint(PRN_FATAL, "Raw packet TOO BIG! can't copy to seg! Len: %#x\n", TotalSrcLength); 
        if(FMW_OK != DeleteRawLen(pRawPacketArray, TotalSrcLength))
        {
            dprint(PRN_FATAL,"line: %d, delet raw failed!\n",__LINE__);            
        }

        return FMW_OK;
    }

    TmpPhyAddr = pStreamSegArray->SegBufPhyAddr;
    SMSEG_PHY2VIR(pStreamSegArray, TmpPhyAddr, TmpVirAddr);

    SegFreeBufLen = pStreamSegArray->SegBufSize;

    if (((VFMW_VP6 == pSmInstArray->Config.VidStd) || (VFMW_VP6A == pSmInstArray->Config.VidStd))  && (0 == (g_VdmCharacter & VDM_SUPPORT_VP6)))
    {
        *TmpVirAddr++ = 0;
    }

    SrcVirAddr = pRawPacket->VirAddr; 
    SrcLength = pRawPacket->Length;
    index = pRawPacketArray->Head;

    if ((VFMW_VP6A == pSmInstArray->Config.VidStd) && (0 != (g_VdmCharacter & VDM_SUPPORT_VP6)) && (SrcLength != 0))
    {
// *TmpVirAddr++ = 0;

        if (SrcLength >= 3)
        {
            SrcVirAddr += 3;
            SrcLength  -= 3;
        }
        else
        {
            index = (index+1) % MAX_STREAM_RAW_NUM;     
            rawnum1++;
            if (rawnum1 > rawnum)
            {
                return FMW_ERR_BUSY;
            }
            SrcLength += pRawPacketArray->RawPacket[index].Length;
            SrcVirAddr  = pRawPacketArray->RawPacket[index].VirAddr;
            if (SrcLength >= 3)
            {
                SrcVirAddr += (3 -pRawPacketArray->RawPacket[((index+MAX_STREAM_RAW_NUM)-1) % MAX_STREAM_RAW_NUM].Length) ;
                SrcLength -=3;
                rawnum --;
            }
            else
            {	          
                index = (index+1) % MAX_STREAM_RAW_NUM;
                rawnum1++;
                if (rawnum1 > rawnum)
                {
                    return FMW_ERR_BUSY;
                }
                SrcLength += pRawPacketArray->RawPacket[index].Length;
                SrcVirAddr  = pRawPacketArray->RawPacket[index].VirAddr;
                if (SrcLength >= 3)
                {
                    SrcVirAddr += (3 - pRawPacketArray->RawPacket[((index+MAX_STREAM_RAW_NUM)-1) % MAX_STREAM_RAW_NUM].Length 
                            - pRawPacketArray->RawPacket[((index+MAX_STREAM_RAW_NUM)-2) % MAX_STREAM_RAW_NUM].Length);
                    SrcLength -= 3;
                    rawnum -= 2;
                }
                else
                {
                    return FMW_ERR_BUSY;
                }
            }
        }

    }

    //set seg para
    pStreamSeg->PhyAddr = TmpPhyAddr;
    pStreamSeg->VirAddr = (UINT8 *)MEM_Phy2Vir(TmpPhyAddr);
    pStreamSeg->LenInByte = TmpVirAddr - pStreamSeg->VirAddr;
    pStreamSeg->Pts = pRawPacket->Pts; /* 一帧的所有raw包的pts应一样 */
    pStreamSeg->RawPts = pRawPacket->Pts;
    pStreamSeg->Usertag = pRawPacket->UserTag;
    pStreamSeg->IsLastSeg = 1;

    for (i=0; i<rawnum; i++)
    {
        if ( (0!=TmpVirAddr) && (0!=SrcVirAddr) )
        {
            memcpy(TmpVirAddr, SrcVirAddr, SrcLength);
        }
        else
        {
            return FMW_ERR_BUSY;
        }

        //set seg para 
        pStreamSeg->IsStreamEnd              = pRawPacketArray->RawPacket[index].is_stream_end_flag;
        pStreamSeg->LenInByte               += SrcLength;

        TmpVirAddr                           = TmpVirAddr + SrcLength;
        index                                = (index+1) % MAX_STREAM_RAW_NUM;
        SrcVirAddr                           = pRawPacketArray->RawPacket[index].VirAddr;
        SrcLength                            = pRawPacketArray->RawPacket[index].Length;

        pStreamSeg->DispTime                 = pRawPacket->DispTime;
        pStreamSeg->DispEnableFlag           = pRawPacket->DispEnableFlag;
        pStreamSeg->DispFrameDistance        = pRawPacket->DispFrameDistance;
        pStreamSeg->DistanceBeforeFirstFrame = pRawPacket->DistanceBeforeFirstFrame;  
        pStreamSeg->GopNum                   = pRawPacket->GopNum;

    } 

    if ( FMW_OK == InsertStreamSeg(&pSmInstArray->StreamSegArray, pStreamSeg) )
    {
        //pStreamSegArray->SegBufWriteAddr += LenOfNULL;
    }

    //Delete raw packet
    if (FMW_OK != DeleteRawLen(pRawPacketArray, TotalSrcLength) )
    {
        //return FMW_ERR_SCD;
    }

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 SM_ReadStreamSeg(SINT32 SmID, STREAM_SEG_S *pStreamSeg )
  功能    本函数从码流管理模块获取一段已分割完毕的码流
  参数    SmID    码流管理模块的实例的标识
  pStreamSeg  接收码流段信息的结构指针
  返回值  如果读取成功返回FMW_OK，否则返回相应的错误码
 ************************************************************************/
SINT32 SM_ReadStreamSeg(SINT32 SmID, STREAM_SEG_S *pStreamSeg)
{
    SINT32 ret = FMW_OK;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    FMW_ASSERT_RET( 0 != pStreamSeg, FMW_ERR_PARAM );
    FMW_ASSERT_RET( 0 != pSmInstArray, FMW_ERR_PARAM );

    if ( ( VFMW_REAL8    == pSmInstArray->Config.VidStd ) ||
         ( VFMW_REAL9    == pSmInstArray->Config.VidStd ) ||
         ( VFMW_DIVX3    == pSmInstArray->Config.VidStd ) ||
         ( VFMW_H263     == pSmInstArray->Config.VidStd ) ||
         ( VFMW_VP6      == pSmInstArray->Config.VidStd ) ||
         ( VFMW_SORENSON == pSmInstArray->Config.VidStd ) ||
         ( VFMW_VP6F     == pSmInstArray->Config.VidStd ) ||
         ( VFMW_VP6A     == pSmInstArray->Config.VidStd ) ||
         ( VFMW_VP8      == pSmInstArray->Config.VidStd ) ||
         ((VFMW_VC1      == pSmInstArray->Config.VidStd ) && (pSmInstArray->Config.StdExt.Vc1Ext.IsAdvProfile == 0)))
    {
        if ( FMW_OK != SM_CopyRawToSeg(SmID, pStreamSeg) )
        {
            dprint(PRN_SCD_INFO, "copy raw to seg fail\n");
            ret = FMW_ERR_SCD;
            goto SM_ReadStreamSeg_exit;
        }
    }

    ret = GetStreamSeg(&pSmInstArray->StreamSegArray, pStreamSeg);

#ifdef ENV_ARMLINUX_KERNEL
    if(ret == FMW_OK)
    {
        extern OSAL_FILE *vfmw_save_seg_file;
        extern UINT32 save_seg_chan_num;

        if( NULL != vfmw_save_seg_file && SmID == save_seg_chan_num)
        {
            VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
            OSAL_FileWrite(pStreamSeg->VirAddr, pStreamSeg->LenInByte, vfmw_save_seg_file);
            VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
        }
    }
#endif

SM_ReadStreamSeg_exit:
    if (FMW_OK != ret)
    {
        pSmInstArray->numReadSegFail++;
    }
    else
    {
        pSmInstArray->numReadSegFail = 0;
    }

    return ret;

}


/************************************************************************
  原型    SINT32 SM_ReleaseStreamSeg( SINT32 SmID, SINT32 StreamID )
  功能    本函数将协议层已经解码完毕的码流片归还给码流管理模块
  参数    SmID    码流管理模块的实例的标识
  StreamID    码流片的ID
  返回值  无
 ************************************************************************/
SINT32 SM_ReleaseStreamSeg(SINT32 SmID, SINT32 StreamID)
{
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    SINT32 ret;
    FMW_ASSERT_RET( 0 != pSmInstArray, FMW_ERR_PARAM );    

    ret =  ReleaseStreamSeg(&pSmInstArray->StreamSegArray, (UINT32)StreamID);

    return ret;
}


/***********************************************************************
  SM_GiveThreadEvent(): 
  SCD中断后需要根据当前码流情况和通道decparam情况来促使解码线程被激活
 ***********************************************************************/
VOID SM_GiveThreadEvent(SINT32 SmID)
{
    static UINT32 LastEventTime = 0;
    UINT32 CurTime = VFMW_OSAL_GetTimeInMs();
    UINT32  Period;
    SINT32 flag = 0;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];

    if (NULL == pSmInstArray)
    {
        return;
    }

    /*码流和decparam判断*/
    if ((pSmInstArray->InsertNewSegFlag == 1)&&
            (NULL == VCTRL_GetDecParam(SmID))&&(0 == VCTRL_IsChanSegEnough(SmID)))
    {
        flag = 1;
    }
    if (CurTime > LastEventTime)
    {
        Period = CurTime - LastEventTime;
    }
    else
    {
        Period = 2;
        LastEventTime = CurTime;
    }
    if ((Period >= 2)&&(flag == 1))
    {
        VFMW_OSAL_GiveEvent(G_INTEVENT);
        LastEventTime = CurTime;
    }

    return;
}

/************************************************************************
  原型    SINT32 CalcInstBlockTime( SINT32 SmID )
  功能    计算指定实例被阻塞的时间，将上次阻塞时间与当前时间之差累加到
  总阻塞时间上去，并且更新"上次阻塞时间"
  参数    SmID    码流管理模块的实例的标识
  FirstCalc  1: 第一次计算，仅记录"上次阻塞时间"
0: 累计计算，在上述工作之外还要累加阻塞时间
返回值  累计阻塞时间
 ************************************************************************/
SINT32 CalcInstBlockTime( SINT32 SmID, SINT32 FirstCalc )
{
    UINT32  CurTime = 0;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];

    if (NULL == pSmInstArray)
    {
        return 0;
    }

    CurTime = VFMW_OSAL_GetTimeInMs();     /* 读系统时间先空着，后续使用OSAL实现 */

    if( FirstCalc )
    {
        pSmInstArray->BlockTimeInMs = 0;
        pSmInstArray->LastBlockTime = CurTime;
    }
    else
    {
        if(CurTime > pSmInstArray->LastBlockTime)
        {
            pSmInstArray->BlockTimeInMs = CurTime - pSmInstArray->LastBlockTime;
        }
        else
        {
            pSmInstArray->BlockTimeInMs = 0;
            pSmInstArray->LastBlockTime = CurTime;
        }
    }

    return pSmInstArray->BlockTimeInMs;
}

/************************************************************************
  原型    SINT32 SetInstMode( SINT32 SmID, SINT32 Mode )
  功能    计算指定实例被阻塞的时间，将上次阻塞时间与当前时间之差累加到
  总阻塞时间上去，并且更新"上次阻塞时间"
  参数    SmID    码流管理模块的实例的标识
  Mode    SM_INST_MODE_WORK  工作模式
  SM_INST_MODE_WAIT  阻塞模式
  返回值  成功返回FMW_OK， 否则返回错误码
 ************************************************************************/
SINT32 SetInstMode( SINT32 SmID, SINT32 Mode )
{
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];
    FMW_ASSERT_RET( Mode==SM_INST_MODE_WORK || Mode==SM_INST_MODE_WAIT, FMW_ERR_PARAM );
    FMW_ASSERT_RET( NULL!=pSmInstArray, FMW_ERR_PARAM );

    pSmInstArray->Mode = Mode;
    return FMW_OK;
}



/*========================================================================
  part4.   SCD level 码流切割和控制子模块 
  ========================================================================*/

/************************************************************************
  原型    SINT32 CutStreamWithSCD(RAW_ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, UINT32 StdType, SINT32 *pCutRawNum)
  功能    驱动SCD切割码流。
  本函数从原始码流集中取出若干个码流包配置给SCD，然后启动SCD切割。一次切割的原始码流包个数取决于两个条件：
  1.  码流片段缓冲区的空闲空间
  2.  原始码流的PTS分布
  亦即，可切割的码流包总长度不得大于码流片段缓冲区的空闲空间总量，一次切割的码流包PTS不能变化（对于MPEG系列可能无须受此限制）。
  本函数调用原始码流管理子模块的ShowFirstRawPacket() / ShowNextRawPacket()函数组依次扫描原始码流，得到可切割的码流包数。
  参数    pRawStreamArray 原始码流集
  pStreamSegArray 切割码流片段集
  StdType 码流的协议类型。
  SCD同步头检测依赖于协议类型。
  pSmPushRaw 可切割的码流包的信息
  返回值  FMW_OK或错误码

 ************************************************************************/
SINT32 CutStreamWithSCD(SM_INSTANCE_S *pScdInstance)
{
    /*剩余的包数及长度*/
    SINT32 StreamNum, RawStreamSize;
    SINT32 SegStreamSize;

    /*一次送入SCD多少包raw packet*/
    SINT32 PushRawNum;
    SM_CTRLREG_S ScdCtrlReg;
    SINT32 Ret;
    UADDR FreeSegBufAddr = 0;
    UADDR SegBufPhyAddr = 0;
    SINT32 SegBufSize    = 0;
    SINT32 RawTotalLen;

    RAW_ARRAY_S *pRawStreamArray;
    SEG_ARRAY_S *pStreamSegArray;

    UINT32 StdType;
    UINT32 ScdLowdlyEnable;

    /*初始化部分*/    
    pRawStreamArray = &(pScdInstance->RawPacketArray);
    pStreamSegArray = &(pScdInstance->StreamSegArray);
    
    StdType = pScdInstance->Config.VidStd;
    ScdLowdlyEnable = pScdInstance->Config.ScdLowdlyEnable;

    FMW_ASSERT_RET( 0 != pRawStreamArray, FMW_ERR_PARAM );
    FMW_ASSERT_RET( 0 != pStreamSegArray, FMW_ERR_PARAM );

    PushRawNum     = 0;
    StreamNum      = 0;
    RawStreamSize  = 0;
    SegStreamSize  = 0;
    FreeSegBufAddr = 0;
    RawTotalLen    = 0;
    memset(&(pScdInstance->SmPushRaw), 0, sizeof(SM_PUSHRAW_S));

    /*得到包数及长度*/
    Ret = GetRawStreamNum(pRawStreamArray, &StreamNum);
    if (FMW_OK != Ret)
    {
        return Ret;
    }
    dprint(PRN_SCD_INFO, "RawStreamNum=%d\n", StreamNum);

    Ret = GetRawStreamSize(pRawStreamArray, &RawStreamSize);    
    if (FMW_OK != Ret)
    {
        return Ret;
    }
    dprint(PRN_SCD_INFO, "RawStreamSize=%d\n",RawStreamSize);

    /*对于RawStreamSize的判断条件以前是<=0，但是有种情况会出现即使切不出来可供解码的seg包却使其它通道码流得不到及时
      处理的问题，当RAW包是以帧为单位且加入了结束码的时候，切包的结果会是RAW中最后剩3个bytes(00 00 01)，此时该通道依然
      会被SCD处理，又因为SCD采用查询模式工作，每调度一次即是线程运行一次的时间，则下一个通道就会延时这么长时间才得到处理，
      因此，此处判断条件改为 (RawStreamSize <= 3)，可以避免上述情况的发生。*/
    if ((StreamNum <= 0) || (RawStreamSize <= 3))
    {
        return FMW_ERR_RAWNULL;
    }

    Ret = GetSegStreamNum(pStreamSegArray, &StreamNum);
    if (FMW_OK != Ret)
    {
        return Ret;
    }

    /* StreamNum表示空闲的SegStreamNum个数 */
    StreamNum = MAX_STREAM_SEG_NUM - StreamNum;
    dprint(PRN_SCD_INFO, "SegStreamNum=%d\n", StreamNum);
    FMW_ASSERT_RET((StreamNum > MAX_STREAM_SEG_NUM / 4), FMW_ERR_SEGFULL);

    /* SegStreamSize表示空闲的SegStreamSize大小 */
    GetFreeSegBuf(pStreamSegArray, &FreeSegBufAddr, &SegStreamSize);

    /* FreeSegBufAddr表示SegBuf的写指针，做16字节对齐 */
    FreeSegBufAddr = (FreeSegBufAddr + 15) & 0xfffffff0;
    SegStreamSize  = SegStreamSize - SM_SEGWASTE_BUF_SIZE - 15;
    dprint(PRN_SCD_INFO, "SegStreamSize=%d\n", SegStreamSize);

    /*没有空闲空间*/
    //FMW_ASSERT_RET((SegStreamSize > 1024), FMW_ERR_SEGFULL);
    FMW_ASSERT_RET((SegStreamSize > (pStreamSegArray->SegBufSize >> 3)), FMW_ERR_SEGFULL);
    
    GetSegBuf(pStreamSegArray, &SegBufPhyAddr, &SegBufSize);

    pScdInstance->BufAddrCfg.UpMsgNum  = StreamNum;
    pScdInstance->BufAddrCfg.UpMsgSize = (pScdInstance->UpMsgStepNum) * pScdInstance->BufAddrCfg.UpMsgNum * sizeof(SINT32); //TODO
    /*配置寄存器*/
    ScdCtrlReg.ScdStart = 1;
    ScdCtrlReg.DownMsgPhyAddr  = pScdInstance->BufAddrCfg.DownMsgPhyAddr;
    ScdCtrlReg.pDownMsgVirAddr = pScdInstance->BufAddrCfg.pDownMsgVirAddr;
    ScdCtrlReg.UpMsgPhyAddr    = pScdInstance->BufAddrCfg.UpMsgPhyAddr;
 
    // UpLen 以 word 为单位
    ScdCtrlReg.UpLen       = (pScdInstance->UpMsgStepNum) * pScdInstance->BufAddrCfg.UpMsgNum;//MAX_STREAM_SEG_NUM;//pScdInstance->BufAddrCfg.UpMsgSize/sizeof(SINT32);//pScdInstance->BufAddrCfg.UpMsgNum;
    ScdCtrlReg.BufferFirst = SegBufPhyAddr;
    ScdCtrlReg.BufferLast  = SegBufPhyAddr + SegBufSize;
    ScdCtrlReg.BufferIni   = FreeSegBufAddr;
    ScdCtrlReg.ScdIntMask  = 1;

    ScdCtrlReg.ScdLowdlyEnable = ScdLowdlyEnable;

    /* SCD 低延迟使能标志 */
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    ScdCtrlReg.DspSpsMsgMemAddr = pScdInstance->BufAddrCfg.DspSpsMsgMemAddr;
    ScdCtrlReg.DspPpsMsgMemAddr = pScdInstance->BufAddrCfg.DspPpsMsgMemAddr;
    ScdCtrlReg.DvmMemAddr       = pScdInstance->BufAddrCfg.DvmMemAddr;
    ScdCtrlReg.DspSedTopMemAddr = pScdInstance->BufAddrCfg.DspSedTopMemAddr;
    ScdCtrlReg.DspCaMnMemAddr   = pScdInstance->BufAddrCfg.DspCaMnMemAddr;
#endif
    ScdCtrlReg.reg_avs_flag = (VFMW_AVS == StdType)? 1: 0;

    /*1"表示也进行slice起始码检测。
      "0"表示不进行slice起始码检测。
      MPEG-4的时候不能打开进行slice起始码检测
      问题*/
    if (VFMW_VC1 == StdType || VFMW_MVC == StdType || VFMW_HEVC == StdType)
    {
        StdType = VFMW_H264;
    }

    if (StdType == VFMW_AVS)
    {
        ScdCtrlReg.SliceCheckFlag = 0x01;
    }
#ifdef SCD_MP4_SLICE_ENABLE
    else if (StdType == VFMW_MPEG2 || StdType == VFMW_MPEG4)
    {
        ScdCtrlReg.SliceCheckFlag = 0x01;
    }
#endif
    else
    {
        ScdCtrlReg.SliceCheckFlag = 0;
    }    
    ScdCtrlReg.ScdProtocol = StdType;
    ScdCtrlReg.ScdIniClr   = 0x01;
    
    Ret = ScdDriver(&ScdCtrlReg, &(pScdInstance->SmPushRaw),SegStreamSize, pRawStreamArray, pScdInstance->BufAddrCfg.pDownMsgVirAddr, pScdInstance->BufAddrCfg.DownMsgPhyAddr);
    if (Ret != FMW_OK)
    {
        return Ret;
    }
    pScdInstance->IsWaitSCD = 1;
    pScdInstance->PrevCfgRawSize = RawStreamSize;
    pScdInstance->PrevCfgSegSize = SegStreamSize;

    if (RawStreamSize <= SegStreamSize)
    {
        /*此次SCD处理将所有的RAW码流都进行了处理，如果后续没有新的RAW码流则不必急于继续处理此通道码流*/
        pScdInstance->LastCfgAllRawFlag = 1;
    }
    else
    {
        pScdInstance->LastCfgAllRawFlag = 0;
    }
    pScdInstance->FillNewRawFlag   = 0;
    pScdInstance->LastSCDStartTime = VFMW_OSAL_GetTimeInMs();
    pScdInstance->InsertNewSegFlag = 0;

    return FMW_OK;
}

/************************************************************************
  原型    VOID WriteScdVtrlReg()
  功能    配置Scd控制寄存器函数
  参数    
  返回值  

 ************************************************************************/
VOID WriteScdVtrlReg(SM_CTRLREG_S *pSmCtrlReg)
{
    // LIST_ADDRESS
    WR_SCDREG(REG_LIST_ADDRESS, (unsigned int)pSmCtrlReg->DownMsgPhyAddr);

    // UP_ADDRESS
    WR_SCDREG(REG_UP_ADDRESS, (UINT32)pSmCtrlReg->UpMsgPhyAddr);

    // UP_LEN
    WR_SCDREG(REG_UP_LEN,(UINT32) pSmCtrlReg->UpLen);

    // BUFFER_FIRST
    WR_SCDREG(REG_BUFFER_FIRST, (UINT32)pSmCtrlReg->BufferFirst);

    // BUFFER_LAST
    WR_SCDREG(REG_BUFFER_LAST, (UINT32)pSmCtrlReg->BufferLast);

    // BUFFER_INI
    WR_SCDREG(REG_BUFFER_INI, (UINT32)pSmCtrlReg->BufferIni); 

    // AVS_FLAG    
    WR_SCDREG(REG_AVS_FLAG, (UINT32)pSmCtrlReg->reg_avs_flag);

#ifdef VFMW_SCD_LOWDLY_SUPPORT
    // SCD LOW DELAY
    WR_SCDREG(REG_DSP_SPS_MSG_ADDRESS, (UINT32)pSmCtrlReg->DspSpsMsgMemAddr);
    WR_SCDREG(REG_DSP_PPS_MSG_ADDRESS, (UINT32)pSmCtrlReg->DspPpsMsgMemAddr);
    WR_SCDREG(REG_DVM_MSG_ADDRESS,     (UINT32)pSmCtrlReg->DvmMemAddr);
    WR_SCDREG(REG_SED_TOP_ADDRESS,     (UINT32)pSmCtrlReg->DspSedTopMemAddr);
    WR_SCDREG(REG_CA_MN_ADDRESS,       (UINT32)pSmCtrlReg->DspCaMnMemAddr);
#endif     

    // SCD_PROTOCOL   
#ifdef ENV_SOS_KERNEL
    WR_SCDREG(REG_SCD_PROTOCOL, (UINT32)((pSmCtrlReg->ScdLowdlyEnable << 8) 
                                      | (1<<7) /* sec mode */
                                      | ((pSmCtrlReg->SliceCheckFlag << 4) & 0x10)
                                      | (pSmCtrlReg->ScdProtocol& 0x0f)));
#ifdef HIVDEC_SMMU_SUPPORT
    SMMU_SetMasterReg(SCD, SECURE_ON,  SMMU_OFF);
#endif

#else
    WR_SCDREG(REG_SCD_PROTOCOL, (UINT32)((pSmCtrlReg->ScdLowdlyEnable << 8) 
                                      | ((pSmCtrlReg->SliceCheckFlag << 4) & 0x10)
                                      | (pSmCtrlReg->ScdProtocol& 0x0f)));
#ifdef HIVDEC_SMMU_SUPPORT
    SMMU_SetMasterReg(SCD, SECURE_OFF, SMMU_ON);
#endif

#endif 

    PrintScdVtrlReg();
	
    // SCD_START
    WR_SCDREG(REG_SCD_START, 0);   
    WR_SCDREG(REG_SCD_START, (UINT32)(pSmCtrlReg->ScdStart & 0x01));
    
}

/************************************************************************
  原型  VOID WriteScdMsg(SM_PUSHRAW_S *pSmPushRaw, SINT32 *pDownMsgVirAddr, UADDR DownMsgPhyAddr)
  功能  配置Scd下行消息池
  参数  
  返回值    

 ************************************************************************/
SINT32 WriteScdMsg(SM_PUSHRAW_S *pSmPushRaw, SINT32 SegStreamSize, RAW_ARRAY_S *pRawStreamArray,
        SINT32 *pDownMsgVirAddr, UADDR DownMsgPhyAddr, SINT32 LowdlyFlag)
{
    /*为剩余的包数及长度*/
    /*一次送入SCD多少包raw packet*/
    SINT32 PushRawNum;
    STREAM_DATA_S RawPacket = {0};
    SINT32 RawShowTotalLen;
    SINT32 FirstRawOffset = 0;
    SINT32 j;

    /*****组包送包的过程*******/
    GetFirstOffset(pRawStreamArray, &FirstRawOffset);
    ShowFirstRawPacket(pRawStreamArray, &RawPacket);

    RawPacket.PhyAddr += FirstRawOffset;
    RawPacket.VirAddr += FirstRawOffset;
    RawPacket.Length  -= FirstRawOffset;

    RawShowTotalLen = RawPacket.Length;

    pDownMsgVirAddr[0] = 0;
    pDownMsgVirAddr[1] = 0;
    pDownMsgVirAddr[2] = 0;
    pSmPushRaw->PushRawTotalLen = 0;

    for (PushRawNum = 0, j = 0; (SegStreamSize >= RawShowTotalLen) && (PushRawNum < MAX_STREAM_RAW_NUM);)
    {
        /*****组成一个Scd要的链表,虚拟送包的过程*******/
        if (RawPacket.Length > 0)
        {
#ifdef SM_RUN_ON_SOFTSCD
            pDownMsgVirAddr[j++] = RawPacket.VirAddr;
            pDownMsgVirAddr[j++] = RawPacket.VirAddr + RawPacket.Length - 1;
            pDownMsgVirAddr[j]   = &pDownMsgVirAddr[j + 1];
#else
            pDownMsgVirAddr[j++] = RawPacket.PhyAddr;
            pDownMsgVirAddr[j++] = RawPacket.PhyAddr + RawPacket.Length - 1;
            pDownMsgVirAddr[j]   = DownMsgPhyAddr + (j + 1) * (sizeof(SINT32));
#endif  
            j++;
            RawPacket.Length = 0;
        }
        
        pSmPushRaw->PushRawTotalLen = RawShowTotalLen;
        PushRawNum++;
        if ( FMW_OK != ShowNextRawPacket(pRawStreamArray, &RawPacket) )
        {
            break;
        }
        RawShowTotalLen += RawPacket.Length;
        /*问题：如果raw包为0包,可以考虑将PushRawNum++移下来,加在if里面,但Pts还要多考虑一下*/
    }

    // 送半包(第一包送不进去或第N包送不出去)
    // 新增一条件(0 == LowdlyFlag)，即是内部低延迟时，不能进入下面的分支
    // 原因是下面的代码分支会将一个RAW PACKET 分成两次送给SCD去切，这样会
    // 导致SCD检测不到一帧的结束，从而低延功能无法实现,
    // LowdlyFlag: 0 -- 低延迟未使能，1 -- 低延迟使能
    if ((0 == LowdlyFlag) && (RawPacket.Length != 0) &&
            (pSmPushRaw->PushRawTotalLen < (SegStreamSize - 16)) &&
            (SegStreamSize < RawShowTotalLen) && (PushRawNum < MAX_STREAM_RAW_NUM))
    {
        if (RawPacket.Length >= SegStreamSize - pSmPushRaw->PushRawTotalLen)
        {
            RawPacket.Length = SegStreamSize - pSmPushRaw->PushRawTotalLen;
#ifdef SM_RUN_ON_SOFTSCD
            pDownMsgVirAddr[j++] = RawPacket.VirAddr;
            pDownMsgVirAddr[j++] = RawPacket.VirAddr + RawPacket.Length - 1;
            pDownMsgVirAddr[j] = (&pDownMsgVirAddr[j + 1]);
#else
            pDownMsgVirAddr[j++] = RawPacket.PhyAddr;
            pDownMsgVirAddr[j++] = RawPacket.PhyAddr + RawPacket.Length - 1;
            pDownMsgVirAddr[j] = DownMsgPhyAddr + (j + 1) * (sizeof(SINT32));
#endif  
            j++;  

            pSmPushRaw->PushRawTotalLen += RawPacket.Length; 
            PushRawNum++;            
            RawPacket.Length = 0;


        } 
    }

    if (0 == PushRawNum)
    {
        return FMW_ERR_SEGFULL;
    }
    pDownMsgVirAddr[j-1] = 0;

    pSmPushRaw->PushRawNum  = PushRawNum;
    pSmPushRaw->PushRawOver = 1;
    PrintDownMsg(DownMsgPhyAddr, pDownMsgVirAddr, PushRawNum);

    return FMW_OK;
}


/************************************************************************
  原型  VOID ScdDriver(SM_CTRLREG_S *pSmCtrlReg, UINT32 *pRegUpAddress)
  功能  配置寄存器函数
  参数  
  返回值    

 ************************************************************************/
SINT32 ScdDriver(SM_CTRLREG_S *pSmCtrlReg, SM_PUSHRAW_S *pSmPushRaw, SINT32 SegStreamSize,RAW_ARRAY_S *pRawStreamArray,
        SINT32 *pDownMsgVirAddr, UADDR DownMsgPhyAddr)
{
    SINT32 Ret;
    ResetSCD();
    Ret = WriteScdMsg(pSmPushRaw, SegStreamSize, pRawStreamArray, pDownMsgVirAddr, 
            DownMsgPhyAddr, pSmCtrlReg->ScdLowdlyEnable);
    if (Ret != FMW_OK)
    {
        return Ret;
    }

    WriteScdVtrlReg(pSmCtrlReg);

    return FMW_OK;
}


/************************************************************************
  原型  VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg)
  功能  读取Scd状态寄存器函数
  参数  
  返回值    

 ************************************************************************/
VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg)
{
    /* state registers */
    pSmStateReg->Scdover     = RD_SCDREG(REG_SCD_OVER) & 0x01;
    pSmStateReg->ScdInt      = RD_SCDREG(REG_SCD_INT) & 0x01;
    pSmStateReg->ShortScdNum = (RD_SCDREG(REG_SCD_NUM) >> 22) & 0x3ff;
    pSmStateReg->ScdNum      = RD_SCDREG(REG_SCD_NUM) & 0x3fffff;
    pSmStateReg->ScdRollAddr = RD_SCDREG(REG_ROLL_ADDR);
    pSmStateReg->SrcEaten    = RD_SCDREG(REG_SRC_EATEN);

    PrintScdStateReg(pSmStateReg);
}

/************************************************************************
  原型  SINT32 CheckScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 StdType)
  功能  检查Scd状态寄存器函数
  参数  
  返回值    

 ************************************************************************/
SINT32 CheckScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 StdType)
{
    //SINT32 ScdSegNum;
#if 0 
    /* state registers */
    FMW_ASSERT_RET((0 != pSmStateReg->Scdover), FMW_ERR_SCD);
    //FMW_ASSERT_RET((1 != pSmStateReg->ScdNum) || (0 == RD_SCDREG(REG_SRC_EATEN)), FMW_ERR_SCD);
    FMW_ASSERT_RET((0 != pSmStateReg->ScdRollAddr), FMW_ERR_SCD);
    //FMW_ASSERT_RET((0 != pSmStateReg->SrcEaten), FMW_ERR_SCD);
#else
    FMW_ASSERT_RET((0 != pSmStateReg->ScdRollAddr), FMW_ERR_SCD);

#endif

    return FMW_OK;
}

SINT32 ScdParseUpMsgInfo(SM_SEGSTREAMFILTER_S *pSegFilter, STREAM_SEG_S *ParseUpMsgInfo, UINT32 SegNum, UINT32 UpMsgStepNum)
{
    if (NULL == ParseUpMsgInfo)
    {
        return FMW_ERR_PARAM;
    }

    if (SM_MPEG4_NOTH263 == pSegFilter->ModeFlag)
    {
        ParseUpMsgInfo->stMp4UpMsg.IsShStreamFlag = 0;
    }
    else
    {
        ParseUpMsgInfo->stMp4UpMsg.IsShStreamFlag = 1;
    }

#ifdef SCD_MP4_SLICE_ENABLE
    #ifndef REP_SCD_ADDR_BUG
    ParseUpMsgInfo->stMp4UpMsg.SliceFlag = (pSegFilter->pScdUpMsg[SegNum*UpMsgStepNum + 0]>> 31) & 0x1; 
    #else
    ParseUpMsgInfo->stMp4UpMsg.SliceFlag = (pSegFilter->pScdUpMsg[SegNum*UpMsgStepNum + 1]>> 30) & 0x1; 
    #endif
    ParseUpMsgInfo->stMp4UpMsg.IsShortHeader = (pSegFilter->pScdUpMsg[SegNum*UpMsgStepNum + 2] >> 16) & 0x1;
    ParseUpMsgInfo->stMp4UpMsg.StartCodeBitOffset = (pSegFilter->pScdUpMsg[SegNum*UpMsgStepNum + 2]>> 4) & 0x7;
    ParseUpMsgInfo->stMp4UpMsg.StartCodeLength = pSegFilter->pScdUpMsg[SegNum*UpMsgStepNum + 2]& 0x7;
#else
    ParseUpMsgInfo->stMp4UpMsg.SliceFlag = 0;
    ParseUpMsgInfo->stMp4UpMsg.IsShortHeader = 0;
    ParseUpMsgInfo->stMp4UpMsg.StartCodeBitOffset = 0;
    ParseUpMsgInfo->stMp4UpMsg.StartCodeLength = 0;
#endif


    return FMW_OK;
}

/************************************************************************
  原型  SINT32 ScdReturnSegFilter(SM_SEGSTREAMFILTER_S *pSegStreamFilter, SINT32 *pTransFormSeg, SINT32 *pSegNum, UINT32 UpMsgStepNum)
  功能  
  参数    pSegNum(输入/输出)
  返回值    FMW_OK或错误码

 ************************************************************************/
SINT32 ScdReturnSegFilter(SM_SEGSTREAMFILTER_S *pSegStreamFilter, SINT32 *pTransFormSeg, SINT32 *pExtraSrcBack, SINT32 *pSegNum, UINT32 UpMsgStepNum)
{
    SINT32 i;
    SINT32 j;
    SINT32 SegNum;
    UINT8 *pTmpVirAddr;
    UADDR TmpPhyAddr;
    UINT32 Data32;
    /*因为上行消息一共有SegNum + 1 个,所以有可能最后一个节点没有赋值 */
    SINT32 LastPacketOffset;
    //	  UINT32 BitOffset;

    SegNum = pSegStreamFilter->SegNum;
    LastPacketOffset = 0;
    *pExtraSrcBack = 0;    
    dprint(PRN_SCD_REGMSG,"***Print Up Msg Now\n");

    if (VFMW_MPEG4 != pSegStreamFilter->ProtocolType)
    {
        for (i = 0; i < SegNum ; i++)
        {
            #ifndef  REP_SCD_ADDR_BUG
            TmpPhyAddr = (pSegStreamFilter->pScdUpMsg[i * UpMsgStepNum] & 0x7fffffff);
            if (TmpPhyAddr < pSegStreamFilter->SegBufPhyAddr)
            {
                TmpPhyAddr |= 0x80000000;
            }
            pTransFormSeg[i * UpMsgStepNum]  = TmpPhyAddr;
            #else
            pTransFormSeg[i*UpMsgStepNum]  = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum];
            #endif
            pTransFormSeg[i*UpMsgStepNum + 1]  = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 1];
            //dprint(PRN_SCD_REGMSG,"ScdUpMsg[%d] = 0x%x\n",i,pSegStreamFilter->pScdUpMsg[i]);

        }
        pSegStreamFilter->ModeFlag = SM_NOT_MPEG4;
        pSegStreamFilter->LastH263Num = 0;
        *pSegNum = SegNum;
    }
    else
    {
        /*可能存在00 00 01回饶,所以需要拷贝一个word到Buffer底部*/
        TmpPhyAddr = pSegStreamFilter->SegBufPhyAddr;
        pTmpVirAddr = (UINT8 *)MEM_Phy2Vir(TmpPhyAddr);
        FMW_ASSERT_RET((pTmpVirAddr != 0), FMW_ERR_SCD);

        Data32 =    (((UINT32)pTmpVirAddr[0] & 0xff) << 24)
                    |  (((UINT32)pTmpVirAddr[1] & 0xff) << 16)
                    |  (((UINT32)pTmpVirAddr[2] & 0xff) << 8)
                    |  (((UINT32)pTmpVirAddr[3] & 0xff));

        TmpPhyAddr = pSegStreamFilter->SegBufRollAddr;// + 1;//这个地址本身已经是无效数据的地址
        pTmpVirAddr = (UINT8 *)MEM_Phy2Vir(TmpPhyAddr);
        FMW_ASSERT_RET((pTmpVirAddr != 0), FMW_ERR_SCD);

        pTmpVirAddr[0] = (Data32 >> 24) & 0xff;
        pTmpVirAddr[1] = (Data32 >> 16) & 0xff;
        pTmpVirAddr[2] = (Data32 >> 8) & 0xff;
        pTmpVirAddr[3] = Data32 & 0xff;
        for ( i = 0, j = 0; i < SegNum; i++)
        {
            #ifndef  REP_SCD_ADDR_BUG
            TmpPhyAddr = (pSegStreamFilter->pScdUpMsg[i * UpMsgStepNum] & 0x7fffffff);
            if (TmpPhyAddr < pSegStreamFilter->SegBufPhyAddr)
            {
                TmpPhyAddr |= 0x80000000;
            }
            #else
            TmpPhyAddr = (SINT32)( pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum] );
            #endif
            FMW_ASSERT_RET((TmpPhyAddr != 0), FMW_ERR_SCD);

            pTmpVirAddr = (UINT8 *)MEM_Phy2Vir(TmpPhyAddr);

            FMW_ASSERT_RET((pTmpVirAddr != 0), FMW_ERR_SCD);

            Data32 =    (((UINT32)pTmpVirAddr[0] & 0xff) << 24)
                        |  (((UINT32)pTmpVirAddr[1] & 0xff) << 16)
                        |  (((UINT32)pTmpVirAddr[2] & 0xff) << 8)
                        |  (((UINT32)pTmpVirAddr[3] & 0xff));

            if((SM_VOP_START_CODE == Data32)
                    ||(SM_VIDOBJLAY_START_CODE == Data32))
            {            
                /* 当前码流格式标记为"非短头模式" */
                pSegStreamFilter->ModeFlag = SM_MPEG4_NOTH263;
                /* 对ShortHeader Picture 计数清0 */
                pSegStreamFilter->LastH263Num = 0;
                pTransFormSeg[j*UpMsgStepNum]  = TmpPhyAddr;
                pTransFormSeg[j*UpMsgStepNum + 1] = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 1];
                j++;
                LastPacketOffset = 0;
            }
            else if (SM_SHORT_VIDEO_START_CODE == (Data32 & 0xfffffc00))
            {
                if (SM_MPEG4_NOTH263 != pSegStreamFilter->ModeFlag)
                {
                    /*当前码流尚未标记为非短头或短头模式,将当前码流格式标记为"短头"模式，即原来为非Mpeg4模式 */
                    pSegStreamFilter->ModeFlag = SM_MPEG4_H263;
                    pTransFormSeg[j*UpMsgStepNum]  = TmpPhyAddr;
                    pTransFormSeg[j*UpMsgStepNum + 1] = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 1];
                    j++;
                    LastPacketOffset= 0;
                }
                else 
                {
                    /* 码流已经标记为"非短头"模式,Picture 计数 */
                    pSegStreamFilter->LastH263Num++;
                    LastPacketOffset = 1;
                    if(pSegStreamFilter->LastH263Num > SM_H263_THRESHOLD_NUM)
                    {
                        REPORT_UNSUPPORT(s_SmIIS.ThisInstID);
                        /* 将当前码流格式标记为"短头"模式 */
                        pSegStreamFilter->ModeFlag = SM_MPEG4_H263;
                        pTransFormSeg[j*UpMsgStepNum]  = TmpPhyAddr;
                        pTransFormSeg[j*UpMsgStepNum + 1] = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 1];
                        j++;
                        LastPacketOffset = 0;
                    }
                    else
                    {
#ifdef SCD_MP4_SLICE_ENABLE  					  
                        //非短头码流中，收到byte对齐的短头，不能过滤掉，需要当做slice解析
                        pTransFormSeg[j*UpMsgStepNum]   = TmpPhyAddr;
                        pTransFormSeg[j*UpMsgStepNum+1] = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum+1];
                        j++;
#endif					
                    }
                }
            }
            else
            {
#if 0   /* 这样的过虑有问题 */
                BitOffset = (pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 2] >> 4) & 0x7;
                /*在非短头码流中，收到了非byte对齐的短头起始码，过滤掉*/
                if ((BitOffset != 0) && (pSegStreamFilter->ModeFlag == SM_MPEG4_NOTH263))
                {
                    continue;
                }
#endif                  
                /*mode不变，当前头有效*/
                pTransFormSeg[j*UpMsgStepNum]  = TmpPhyAddr;//pSegStreamFilter->pScdUpMsg[i*2];
                pTransFormSeg[j*UpMsgStepNum + 1] = pSegStreamFilter->pScdUpMsg[i*UpMsgStepNum + 1];
                j++;
                LastPacketOffset = 0;
            }
        }
        *pSegNum = j;  // zhl

        for (i = 0; i < j; i++)
        {
            //dprint(PRN_SCD_REGMSG,"ScdUpMsg[%d] = 0x%x\n",i,pTransFormSeg[i*UpMsgStepNum]);
        }
    }        

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 CheckSegValid(STREAM_SEG_S *pSegPacket, SINT32 SendSegTotalSize, SINT32 SegFreeBufLen)
  功能    
  参数    pPushRawPacket:本包的结构体
PreSegTotalSize:本包之前先送入的总长度
SegFreeBufLen:Seg Stream Buffer中还剩余多少长度
返回值  FMW_OK或错误码

 ************************************************************************/
SINT32 CheckSegValid(STREAM_SEG_S *pSegPacket,SINT32 SegFreeBufLen)
{
    FMW_ASSERT_RET((NULL != pSegPacket), FMW_ERR_PARAM);

    FMW_ASSERT_RET((0 != pSegPacket->PhyAddr), FMW_ERR_SCD);
    FMW_ASSERT_RET((NULL != pSegPacket->VirAddr), FMW_ERR_SCD);
    //FMW_ASSERT_RET((pSegPacket->LenInByte >= 4) && (pSegPacket->LenInByte <= SegFreeBufLen), FMW_ERR_SCD);
    FMW_ASSERT_RET((pSegPacket->LenInByte <= SegFreeBufLen), FMW_ERR_SCD);

    return FMW_OK;
}


/************************************************************************
  原型  SM_PUSHRAW_S *pPushRaw, SINT32 CurrSegTotalSize, SINT32 *pCurrRawId,SINT64 *pPts)
  功能  
  参数    
  返回值    Pts

 ************************************************************************/

/*输入一个长度，就可以得到这个长度所对应的Pts*/
VOID GetSegPts(RAW_ARRAY_S *pRawStreamArray, SINT32 Len, UINT64 *pLastPts, STREAM_SEG_S* pSegPacket)
{
    SINT32 Num;
    SINT32 Offset;
    UINT64*  pPts      = &(pSegPacket->Pts);
    UINT64*  pUsertag  = &(pSegPacket->Usertag);
    UINT64*  pRawPts   = &(pSegPacket->RawPts);
    UINT64*  pDisptime = &(pSegPacket->DispTime);
    UINT32*  pDispEnableFlag = &(pSegPacket->DispEnableFlag);     
    UINT32*  pDispFrameDistance = &(pSegPacket->DispFrameDistance);     
    UINT32*  pDistanceBeforeFirstFrame = &(pSegPacket->DistanceBeforeFirstFrame);     
    UINT32*  pGopNum = &(pSegPacket->GopNum);     

    Num = 0;
    Offset = 0;
    *pPts      = (UINT64)(-1);
    *pUsertag  = (UINT64)(-1);
    *pRawPts   = (UINT64)(-1); 
    *pDisptime = (UINT64)(-1);
    *pDispEnableFlag = (UINT32)(-1);
    *pDispFrameDistance = (UINT32)(-1);
    *pDistanceBeforeFirstFrame = (UINT32)(-1);
    *pGopNum = (UINT32)(-1);

    GetRawNumOffsert(pRawStreamArray, Len, &Num, &Offset, pPts, pUsertag, pDisptime, pDispEnableFlag, pDispFrameDistance, pDistanceBeforeFirstFrame, pGopNum, pRawPts);


    if (*pLastPts == *pPts)
    {
        *pPts = (UINT64)(-1);   
    }
    else
    {
        *pLastPts = *pPts;
    }

    return;   
}


SINT32 IsVopHeader(SINT32 ModeFlag, UINT32 StartCode)
{
    SINT32 flag = 0;
    
    /*非短头vop用0x000001B6标记，短头vop用0x000080xx ~ 0x000083xx标记*/
    /*由于大小端不一致问题，使用0xB6010000作为非短头判断起始码条件，0xxx800000~0xxx830000作为短头起始码判断条件，提高效率*/
    if (SM_MPEG4_NOTH263 == ModeFlag)
    {
        if (0xB6010000 == StartCode)
        {
            flag = 1;
        } 
    }
    else if (SM_MPEG4_H263 == ModeFlag)
    {
        if ((((StartCode & 0xFF0000) >> 16)  >= 0x80)
        && ((((StartCode & 0xFF0000) >> 16)) <= 0x83))
        {
            flag = 1;
        }
    }
	
    if (0xFE010000 == StartCode) // 最后一帧自定义头
    {
        flag = 1;
    }
	
    return flag;
}

SINT32 GetNextVop(SM_INSTANCE_S *pScdInstance, SINT32 *pUsedSeg, SEG_ARRAY_S *pStreamSegArray, SINT32 Seg_num)
{
    SM_STATEREG_S SmStateReg;
    SINT32 StdType;
    SINT32 ScdSegNum = 0;
    SINT32 Ret;
    SINT32 i;
    UADDR  CurrSegPhyAddr;
    UINT32 start_code;
    UINT8  *VirAddr = NULL;
    SINT32 count = 0;
    UINT32 SegNum = 0;

    StdType = (RD_SCDREG(REG_SCD_PROTOCOL)&0x0f);

    /*读取Scd状态寄存器函数*/
    ReadScdStateReg(&SmStateReg);
    Ret = CheckScdStateReg(&SmStateReg, StdType);
    if(FMW_OK !=  GetSegStreamNum(pStreamSegArray, &SegNum))
    {
        dprint(PRN_DBG, "%s %d FMW_OK !=  GetSegStreamNum!!\n",__FUNCTION__,__LINE__);
    }

    SegNum = MAX_STREAM_SEG_NUM - SegNum;

    if (FMW_OK != Ret)
    {
        return Ret;
    }
    ScdSegNum = Seg_num;

    for(i = ScdSegNum - 1; i >= 0; i--)
    {
        CurrSegPhyAddr  = pUsedSeg[i*(pScdInstance->UpMsgStepNum)];
        SMSEG_PHY2VIR(pStreamSegArray, CurrSegPhyAddr, VirAddr);
        /* 在安全测，不能直接读取一个word，只能读取一个字节 */
        start_code = *((UINT8 *)VirAddr) + (*(((UINT8 *)VirAddr)+1) << 8) + (*(((UINT8 *)VirAddr)+2) << 16) + (*(((UINT8 *)VirAddr)+3) << 24);

        if (1 == IsVopHeader(pScdInstance->SegFilter.ModeFlag, start_code))
        {
            count++;
            if(count >= 1)
            {
                ScdSegNum--;
                /* 可插入的seg个数应该大于实际要插入的个数 */
                if(SegNum < ScdSegNum)
                {
                    continue;
                }
                break;
            }
        }
        ScdSegNum--;
    }

    return ScdSegNum;
}

/************************************************************************
  原型  SINT32 ProcessSCDReturn(RAW_ ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, SINT32 *pCutRawNum)
  功能  处理SCD的返回信息。
  本函数从SCD的寄存器和上、下行消息池中读取上一次的码流切割信息，完成下列两种操作：
  1.    根据上行消息将各帧（或NAL）码流按STREAM_SEG_S格式组织并且插入到码流片段集pStreamSegArray中管理起来
  2.    分析此次切割消耗了多少原始码流包，并将这些码流包释放。
  参数
  pRawStreamArray   原始码流集
  pStreamSegArray   切割码流片段集
  pSmPushRaw   上一次送入Scd的原始码流
  pSmPushRaw 已切割的码流包的信息
  返回值    FMW_OK或错误码

 ************************************************************************/
SINT32 ProcessScdReturn(SM_INSTANCE_S *pScdInstance)
{
    SINT32 Ret;
    SINT32 i = 0;
    SM_STATEREG_S SmStateReg;
    STREAM_SEG_S SegPacket;
    SINT32 RawStreamSize;
    SINT32 SrcEaten = 0;
    SINT32 PushRawNum;
    SINT32 ScdSegNum;//Scd送出的Seg的实际包数;
    SINT32 StreamNum=0;
    UADDR  CurrSegPhyAddr;
    UADDR  NextSegPhyAddr;
    SINT32 SegPacketLen;
    UADDR  SegBufAddr = 0;
    SINT32 SegBufLength = 0;
#ifdef SCD_MP4_SLICE_ENABLE	  
    UINT32 Data32;
    UINT8 *pTmpVirAddr = NULL;
#endif
    RAW_ARRAY_S *pRawStreamArray;
    SEG_ARRAY_S *pStreamSegArray;
    SM_PUSHRAW_S  *pSmPushRaw;
    SINT32 *pUsedSeg = NULL;
    SINT32 StdType;
    /*打Pts时*/
    SINT32 CurrRawId;
    SINT32 SegFreeBufLen = 0;
    UADDR  TmpAddr = 0;
    SINT32 ScdErrFlag = 0;
    SINT32 ExtraSrcBack;
    SINT32 LastSegTail;
    UINT32 UpMsgStepNum;
    STREAM_SEG_S LastSegPacket;
    UINT32 UpNum = 0;
    UINT32 ReadScdSegNum;
    UINT32 FilterScdSegNum;

    if( 0 == pScdInstance->IsWaitSCD )
    {
        return FMW_ERR_SCD;
    }
    if(pScdInstance->SmPushRaw.PushRawOver == 3)
    {
        pScdInstance->SmPushRaw.PushRawOver = 2;
        return FMW_ERR_SCD;
    }
    /*初始化部分*/    
    pRawStreamArray = &(pScdInstance->RawPacketArray);
    pStreamSegArray = &(pScdInstance->StreamSegArray);
    StdType = (RD_SCDREG(REG_SCD_PROTOCOL)&0x0f);
    pSmPushRaw = &(pScdInstance->SmPushRaw);
    pSmPushRaw->PushRawOver = 2;

    memset(&SegPacket, 0, sizeof(STREAM_SEG_S));
    memset(&LastSegPacket, 0, sizeof(STREAM_SEG_S));      
    memset(&SmStateReg, 0 , sizeof(SmStateReg));
    RawStreamSize = 0;
    SegPacketLen = 0;
    PushRawNum = pSmPushRaw->PushRawNum;
    pUsedSeg = NULL;
    CurrRawId = 0;
    SegFreeBufLen = 0;
    TmpAddr = 0;
    ScdErrFlag = 0;
    SrcEaten = 0;
    UpMsgStepNum = pScdInstance->UpMsgStepNum;


    /*读取Scd状态寄存器函数*/
    ReadScdStateReg(&SmStateReg);
    Ret = CheckScdStateReg(&SmStateReg, StdType);    
    if (FMW_OK != Ret)
    {
        return Ret;
    }

    ScdSegNum = SmStateReg.ScdNum;  // zhl.
    ReadScdSegNum = ScdSegNum;
    /* l00232354: 如果 SCD 切出来的起始码超过了 MAX_STREAM_SEG_NUM*10 多个，则认为这是个错误码流，先强行丢
      一个RAW 包试试。修改背景，一条H264 4K码流，中间某些错帧有的码流全是（00 00 01 xx），多达百万个，如果
      放到后语法解析去丢的话，会卡住多达几分钟的时间，这是不可接受。          
     */
    if((ReadScdSegNum > MAX_STREAM_SEG_ALLOW) && (VFMW_H264 == pScdInstance->Config.VidStd))
    {
        dprint(PRN_FATAL,"line:%d ReadScdSegNum = %d, FilterScdSegNum = 0 release raw packet anyway!\n", __LINE__, ReadScdSegNum);
        DeleteRawPacket(pRawStreamArray, 1);
        return FMW_ERR_SCD;
    }

    GetSegBuf(pStreamSegArray, &SegBufAddr, &SegBufLength );
    UpNum = ScdSegNum;

    /*过滤包,主要用于Mpeg4*/
    pScdInstance->SegFilter.ProtocolType = (RD_SCDREG(REG_SCD_PROTOCOL)&0x0f);    
	pScdInstance->SegFilter.SegNum = MIN(MIN(ScdSegNum,MAX_STREAM_SEG_NUM),(((SINT32)RD_SCDREG(REG_UP_LEN))/UpMsgStepNum));

    /* 容错:  如果本次启动配置了全部码流，但因为空间不足，而无法完成所有seg信息上报，
       这时候需要将LastCfgAllRawFlag标志清除，否则会误判导致scd延迟启动，造成解码卡顿 */
    if (pScdInstance->SegFilter.SegNum < ScdSegNum && 1 == pScdInstance->LastCfgAllRawFlag)
    {
        pScdInstance->LastCfgAllRawFlag = 0;
    }

    pScdInstance->SegFilter.pScdUpMsg = pScdInstance->BufAddrCfg.pUpMsgVirAddr;
    pScdInstance->SegFilter.SegBufPhyAddr = SegBufAddr;
    SMSEG_PHY2VIR(pStreamSegArray, SegBufAddr, pScdInstance->SegFilter.pSegBufVirAddr);
    pScdInstance->SegFilter.SegBufSize = SegBufLength;
    pScdInstance->SegFilter.SegBufRollAddr = SmStateReg.ScdRollAddr;

    Ret = ScdReturnSegFilter(&(pScdInstance->SegFilter), pScdInstance->TransFormSeg, &ExtraSrcBack, &ScdSegNum, UpMsgStepNum);
    if (FMW_OK != Ret)
    {
        return FMW_ERR_SCD;
    }
    /*如果出来SegNum < 2，因为这时可能Filter之后SegNum不一样了，那么需要处理一下*/
    /*且只报上来0个或一个头*/
    if (ScdSegNum < 2)
    {
        /* 切不出有效的seg!
           如果raw是足够的(大于seg buf的可用空间)，则切不出的原因可能是seg buf的可用空间太小. 
           正常情况下，seg buf会随着解码器释放seg而逐渐延伸，虽然这次切不出来，下次可能就能切了，所以此
           时不能贸然丢码流。但是，万一码流太大(比如每个slice都大于1M)，或者码流错误，或者vfmw存在尚未发
           现的错误，seg buf可能并不会延伸，scd永远无法切出新的码流。这会造成解码器停止工作.
           应对方法: 上述情况可归并到seg buf full处理，所以此处把SegFullFlag标志置起来，DoNextInstance()
           检测到此标志后会启动延时，一旦时间足够长，会强行释放seg buf，使得切割可以继续. */
        if ( pScdInstance->PrevCfgRawSize > pScdInstance->PrevCfgSegSize )
        {
            pScdInstance->SegFullFlag = 1;
        }
        else
        {
            pScdInstance->SegFullFlag = 0;
        }

        if (ScdSegNum == 0)
        {
            /*最少要有4个空位才送，所以只报0或1个头是不会碰到边界条件的*/
            /*送入的包全部删除*/
            SrcEaten = pScdInstance->SmPushRaw.PushRawTotalLen;
            /*因为可能有00 00 01 xx跨包，所以需要少减3个字节*/
            SrcEaten = (SrcEaten >= 4)? (SrcEaten - 3) : 0;
        }
        else if (ScdSegNum == 1)
        {
            /*第一个头前面全部删除，因为送的总是以00 00 01 xx 开始送的
              其实只有第一次才会删除，其它都不会删除的*/
            //第一个必定是有效的头，所以用pScdInstance->BufAddrCfg.pUpMsgVirAddr[1]也是一样的
            SINT32 DiscardThr;
            DiscardThr = pScdInstance->StreamSegArray.SegBufSize * 3 / 4;
            #ifndef REP_SCD_ADDR_BUG
            SrcEaten = pScdInstance->TransFormSeg[1];//pScdInstance->BufAddrCfg.pUpMsgVirAddr[1];
            #else
            SrcEaten = pScdInstance->TransFormSeg[1] & 0x3FFFFFFF;
            #endif
            //剩下的长度仍然大于SM_RAW_DISCARD_SIZE,则将送入的包全部删除，除了最后的三个字节
            //if ((pScdInstance->SmPushRaw.PushRawTotalLen - SrcEaten) > SM_RAW_DISCARD_SIZE)
            if ((pScdInstance->SmPushRaw.PushRawTotalLen - SrcEaten) > DiscardThr)
            {
                dprint(PRN_FATAL, "Error! (PushRawTotalLen - SrcEaten) > SM_RAW_DISCARD_SIZE, packet discard...\n");
                SrcEaten = pScdInstance->SmPushRaw.PushRawTotalLen;
            }
        }
        Ret = DeleteRawLen( pRawStreamArray, SrcEaten );
        if (FMW_OK != Ret)
        {
            return FMW_ERR_SCD;
        }
        return FMW_OK;
    }
    else
    {
        pScdInstance->SegFullFlag = 0;
    }

    pUsedSeg = pScdInstance->TransFormSeg;
    /*上报头的个数必须小于上行消息池的个数*/
    if (ScdSegNum < (((SINT32)RD_SCDREG(REG_UP_LEN))/UpMsgStepNum))
    {
        ScdSegNum = ScdSegNum - 1;
        //SrcEaten = pUsedSeg[ScdSegNum*UpMsgStepNum + 1];   // zhl, 20081230        
        #ifndef REP_SCD_ADDR_BUG
        SrcEaten = pUsedSeg[ScdSegNum*UpMsgStepNum + 1] & 0x7FFFFFFF;
        #else
        SrcEaten = pUsedSeg[ScdSegNum*UpMsgStepNum + 1] & 0x3FFFFFFF;
        #endif
    }
    else
    {
        /*这是为了规避硬件的一个错误,当消息池满时,最后一个消息池不可用*/
        ScdSegNum = ((RD_SCDREG(REG_UP_LEN) - UpMsgStepNum)/UpMsgStepNum) - 1;
        if (ScdSegNum < 0)
        {
            ScdSegNum = 0;
        }
        //SrcEaten = pScdInstance->SegFilter.pScdUpMsg[ScdSegNum*UpMsgStepNum + 1];
        #ifndef REP_SCD_ADDR_BUG
        SrcEaten = (pScdInstance->SegFilter.pScdUpMsg[ScdSegNum*UpMsgStepNum + 1]) & 0x7FFFFFFF;
        #else
        SrcEaten = (pScdInstance->SegFilter.pScdUpMsg[ScdSegNum*UpMsgStepNum + 1]) & 0x3FFFFFFF;
        #endif
    }

    /* 只有收到两个vop，才会把前一帧的所有seg包插入队列里 */
#ifdef SCD_MP4_SLICE_ENABLE	  
    if(VFMW_MPEG4 == pScdInstance->Config.VidStd)
    {
        ScdSegNum = GetNextVop(pScdInstance, pUsedSeg, pStreamSegArray, ScdSegNum);
    }
#endif
    LastSegTail = pStreamSegArray->Tail;
    FilterScdSegNum = ScdSegNum;
      
    for (i = 0; i < ScdSegNum; i++)
    {
        CurrSegPhyAddr  = pUsedSeg[i*UpMsgStepNum];
        NextSegPhyAddr  = pUsedSeg[(i+1)*UpMsgStepNum];
        SegPacket.DspCheckPicOverFlag = ((pUsedSeg[i*UpMsgStepNum+1]) & 0x80000000)>>31; 
        if (SegBufAddr == NextSegPhyAddr)//后面改成偏移的话,这一行代码要改成if (0 == NextSegPhyAddr)
        {
            SegPacketLen = SmStateReg.ScdRollAddr - CurrSegPhyAddr;
        }
        else
        {
            SegPacketLen = NextSegPhyAddr - CurrSegPhyAddr;
        }

        /*大小大于3的包才插入*/
        if (SegPacketLen > 3 )
        {
            if(LastSegPacket.PhyAddr != 0)
            {
#ifdef SCD_MP4_SLICE_ENABLE                    	            
                LastSegPacket.LenInByte += SegPacketLen;
                GetFreeSegBuf(pStreamSegArray, &TmpAddr, &SegFreeBufLen);	
                if (FMW_OK == CheckSegValid(&LastSegPacket, SegFreeBufLen))
                {
                    Ret = InsertStreamSeg(pStreamSegArray, &LastSegPacket);
                    memset(&LastSegPacket, 0, sizeof(STREAM_SEG_S));

                    if (FMW_OK != Ret)
                    {
                        //如果不够空位插入，直接break是没有问题
                        dprint(PRN_SCD_INFO, "Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", LastSegPacket.PhyAddr, LastSegPacket.LenInByte, LastSegPacket.IsLastSeg);
                        break;
                    }
                    #ifndef REP_SCD_ADDR_BUG
                    dprint(PRN_SCD_INFO, "RawLen = %d, Pts = %ld, \n", pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF, LastSegPacket.Pts);
                    #else
                    dprint(PRN_SCD_INFO, "RawLen = %d, Pts = %ld, \n", pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF, LastSegPacket.Pts);
                    #endif
                    dprint(PRN_SCD_INFO, "Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", LastSegPacket.PhyAddr, LastSegPacket.LenInByte, LastSegPacket.IsLastSeg);
                }			  
                else
                {
                    dprint(PRN_ERROR, "line %d CheckSeg err\n",__LINE__);
                    dprint(PRN_ERROR, "line %d SegFreeBufLen=%d,SrcEaten=%d\n",__LINE__, SegFreeBufLen,SrcEaten);
                    dprint(PRN_ERROR, "line %d Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", __LINE__, LastSegPacket.PhyAddr, LastSegPacket.LenInByte, LastSegPacket.IsLastSeg);
                    ScdErrFlag = 1;
                    break;
                }
#endif			  

            }
            else
            {
                if(VFMW_MPEG4 == pScdInstance->Config.VidStd)
                {
                    ScdParseUpMsgInfo(&pScdInstance->SegFilter, &SegPacket, i,UpMsgStepNum);
                }
                SegPacket.IsLastSeg = 1;
                SegPacket.PhyAddr = CurrSegPhyAddr;//pStreamSegArray->SegBufPhyAddr + CurrSegPhyAddr;        
                SMSEG_PHY2VIR(pStreamSegArray, SegPacket.PhyAddr, SegPacket.VirAddr);
                SegPacket.LenInByte = SegPacketLen;             
                GetFreeSegBuf(pStreamSegArray, &TmpAddr, &SegFreeBufLen);            

                if (FMW_OK == CheckSegValid(&SegPacket, SegFreeBufLen))
                {
                    #ifndef REP_SCD_ADDR_BUG
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF,&pScdInstance->LastPts,&SegPacket);
                    #else
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF,&pScdInstance->LastPts,&SegPacket);
                    #endif
                    Ret =InsertStreamSeg(pStreamSegArray, &SegPacket);
                    if (FMW_OK != Ret)
                    {
                        //如果不够空位插入，直接break是没有问题
                        dprint(PRN_SCD_INFO, "Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                        break;
                    }
                    #ifndef REP_SCD_ADDR_BUG
                    dprint(PRN_SCD_INFO, "RawLen = %d, Pts =  %lld, \n",pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF, SegPacket.Pts);
                    #else
                    dprint(PRN_SCD_INFO, "RawLen = %d, Pts =  %lld, \n",pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF, SegPacket.Pts);
                    #endif
                    dprint(PRN_SCD_INFO, "Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                }            
                else
                {
                    dprint(PRN_FATAL, "CheckSeg err\n");
                    dprint(PRN_FATAL, "SegFreeBufLen=%d,SrcEaten=%d\n",SegFreeBufLen,SrcEaten);
                    dprint(PRN_FATAL, "Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                    ScdErrFlag = 1;
                    break;
                }
            }//回绕了    
        }
        else if ((0 < SegPacketLen) && (SegPacketLen <= 3))
        {	

#ifdef SCD_MP4_SLICE_ENABLE                    	            

            if(VFMW_MPEG4 == pScdInstance->Config.VidStd)
            {
                pTmpVirAddr = (UINT8 *)MEM_Phy2Vir(NextSegPhyAddr);
                FMW_ASSERT_RET((pTmpVirAddr != NULL), FMW_ERR_SCD);

                Data32 = (((SINT32)pTmpVirAddr[0] & 0xff) << 24)
                      |  (((SINT32)pTmpVirAddr[1] & 0xff) << 16)
                      |  (((SINT32)pTmpVirAddr[2] & 0xff) << 8)
                      |  (((SINT32)pTmpVirAddr[3] & 0xff));

                if ((Data32&0xffffff00) != 0x100)
                {
                    ScdParseUpMsgInfo(&pScdInstance->SegFilter, &LastSegPacket, i, UpMsgStepNum);
                    LastSegPacket.IsLastSeg = 1;
                    LastSegPacket.PhyAddr = CurrSegPhyAddr;//pStreamSegArray->SegBufPhyAddr + CurrSegPhyAddr;        
                    SMSEG_PHY2VIR(pStreamSegArray, LastSegPacket.PhyAddr, LastSegPacket.VirAddr);
                    LastSegPacket.LenInByte = SegPacketLen;
                    GetFreeSegBuf(pStreamSegArray, &TmpAddr, &SegFreeBufLen);
                    #ifndef REP_SCD_ADDR_BUG
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF,&pScdInstance->LastPts,&LastSegPacket);
                    #else
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF,&pScdInstance->LastPts,&LastSegPacket);
                    #endif
                }
            }
#endif			
        }
        else if (SegPacketLen < 0)
        {
            /*只要回绕，就要减去在Buffer底没有填入的地址*/ 
            if(VFMW_MPEG4 == pScdInstance->Config.VidStd)
            {
                ScdParseUpMsgInfo(&pScdInstance->SegFilter, &SegPacket, i, UpMsgStepNum);
            }
            SegPacket.IsLastSeg = 0;
            SegPacket.PhyAddr = CurrSegPhyAddr;//SegBufAddr + CurrSegPhyAddr;   
            SMSEG_PHY2VIR(pStreamSegArray, SegPacket.PhyAddr, SegPacket.VirAddr);
            SegPacket.LenInByte = SmStateReg.ScdRollAddr - SegPacket.PhyAddr;
            //本包的真正长度
            SegPacket.LenInByte = (NextSegPhyAddr - SegBufAddr) + SegPacket.LenInByte;
            GetFreeSegBuf(pStreamSegArray, &TmpAddr, &SegFreeBufLen);             
            /*检查这两包是否合格*/
            if (SegPacket.LenInByte > 3)
            {
                if(FMW_OK != GetSegStreamNum(pStreamSegArray, &StreamNum))
                {
                    dprint(PRN_DBG, "%s %d FMW_OK != GetSegStreamNum!!\n",__FUNCTION__,__LINE__);
                }
                StreamNum = MAX_STREAM_SEG_NUM - StreamNum;       
                if ((FMW_OK == CheckSegValid(&SegPacket, SegFreeBufLen))
                        && (StreamNum >= 2))
                {
                    /*插入第一包Seg,需要修正一下长度才能插入*/
                    SegPacket.LenInByte = SmStateReg.ScdRollAddr - SegPacket.PhyAddr;
                    #ifndef REP_SCD_ADDR_BUG
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF, &pScdInstance->LastPts, &SegPacket);
                    #else
                    GetSegPts(pRawStreamArray, pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF, &pScdInstance->LastPts, &SegPacket);
                    #endif
                    Ret = InsertStreamSeg(pStreamSegArray, &SegPacket);   
                    if (FMW_OK != Ret)
                    {
                        //如果不够空位插入，直接break是没有问题
                        dprint(PRN_SCD_INFO, "Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                        break;
                    }
                    #ifndef REP_SCD_ADDR_BUG
                    dprint(PRN_SCD_INFO,"RawLen = %d, Pts =  %lld, \n",pUsedSeg[i*UpMsgStepNum+1] & 0x7FFFFFFF, SegPacket.Pts);
                    #else
                    dprint(PRN_SCD_INFO,"RawLen = %d, Pts =  %lld, \n",pUsedSeg[i*UpMsgStepNum+1] & 0x3FFFFFFF, SegPacket.Pts);
                    #endif
                    dprint(PRN_SCD_INFO, "Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);

                    SegPacket.IsLastSeg = 1;
                    SegPacket.PhyAddr = SegBufAddr;
                    SMSEG_PHY2VIR(pStreamSegArray, SegPacket.PhyAddr, SegPacket.VirAddr);
                    SegPacket.LenInByte = NextSegPhyAddr - SegPacket.PhyAddr;//回绕肯定是从头到下一包的开始位置
                    //SegPacket.Pts 不用赋值，直接用上一包的Pts
                    Ret = InsertStreamSeg(pStreamSegArray, &SegPacket);
                    if (FMW_OK != Ret)
                    {
                        //如果不够空位插入，直接break是没有问题
                        dprint(PRN_SCD_INFO, "Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                        break;
                    }
                    dprint(PRN_SCD_INFO, "Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                }
                else
                {
                    //如果不够空位插入，直接break是没有问题
                    if (StreamNum < 2)
                    {                     
                        dprint(PRN_SCD_INFO, "Insert 2 err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", SegPacket.PhyAddr, SegPacket.LenInByte,SegPacket.IsLastSeg);
                    }
                    else
                    {
                        dprint(PRN_ERROR, "line %d CheckSeg err\n",__LINE__);
                        dprint(PRN_ERROR, "line %d SegFreeBufLen=%d,SrcEaten=%d",__LINE__, SegFreeBufLen,SrcEaten);
                        dprint(PRN_ERROR, "line %d Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\n", __LINE__, LastSegPacket.PhyAddr, LastSegPacket.LenInByte, LastSegPacket.IsLastSeg);
                        ScdErrFlag = 1;
                    }
                    break;
                }
            }
        }
    }

    if (pStreamSegArray->Tail != LastSegTail)
    {
        pScdInstance->InsertNewSegFlag = 1;
    }
    else
    {
        pScdInstance->InsertNewSegFlag = 0;
    }

    if (i > 0)
    {
        #ifndef REP_SCD_ADDR_BUG
        SrcEaten = pUsedSeg[i * UpMsgStepNum + 1] & 0x7FFFFFFF;
        #else
        SrcEaten = pUsedSeg[i * UpMsgStepNum + 1] & 0x3FFFFFFF;
        #endif
        Ret = DeleteRawLen( pRawStreamArray, SrcEaten );

        if (FMW_OK != Ret)
        {
            return FMW_ERR_SCD;
        }
    }     
    else
    {
#ifdef SCD_MP4_SLICE_ENABLE
          if((ReadScdSegNum > MAX_STREAM_SEG_NUM) 
		  && (FilterScdSegNum == 0) 
		  && (VFMW_MPEG4 == pScdInstance->Config.VidStd))
          {
              dprint(PRN_FATAL,"ReadScdSegNum = %d, FilterScdSegNum = 0 release raw packet anyway!\n",
                ReadScdSegNum);
              DeleteRawPacket(pRawStreamArray, 1);
          }

#endif

    }

    return ((1 == ScdErrFlag) ? FMW_ERR_SCD : FMW_OK); 
}

/************************************************************************
  原型    VOID FillRawData(SINT32 InstID)
  功能    读取码流，填充码流队列
  参数    InstID    通道实例ID
  返回值  无
 ************************************************************************/
VOID FillRawData(SINT32 InstID)
{
    STREAM_DATA_S  RawPacket;
    UINT32  ThisTime, TimePeriod;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    SINT32 rec_pos_print_flag = 0;
    UINT32 dat = 0;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[InstID];

    memset(&RawPacket, 0, sizeof(STREAM_DATA_S));
    if (NULL == pSmInstArray)
    {
        return;
    }

    while (1)
    {
        if (1 == pSmInstArray->Config.IsOmxPath) // For Omx Low Frequency Get Stream
        {
            /* OMX通路仅在seg报不足的情况下才取码流继续解 y00226912 */
            if (1 == VCTRL_IsChanSegEnough(InstID))
            {
                break;
            }
        }
        if ( FMW_OK == GetRawState(InstID) )
        {
            /* 可以接收新的raw数据 */
            if (FMW_OK != ReadRawStreamData( InstID, &RawPacket))
            {
                break;
            }

            /* 统计码率 */
            pSmInstArray->TotalRawSize    += RawPacket.Length;
            pSmInstArray->u32RawNumCount++;
            pSmInstArray->u32RawSizeCount += RawPacket.Length;
            ThisTime = VFMW_OSAL_GetTimeInMs();
            if (pSmInstArray->LastStatTime == 0)
            {
                pSmInstArray->LastStatTime = ThisTime;
            }
            else
            {
                TimePeriod = ThisTime - pSmInstArray->LastStatTime;
                if (TimePeriod > 2000)
                {
                    pSmInstArray->BitRate = pSmInstArray->TotalRawSize * 8 / TimePeriod * 1000 / 1024;
                    pSmInstArray->TotalRawSize = 0;
                    pSmInstArray->LastStatTime = ThisTime;
                }
            }

            /* 将此raw包插入到本地raw队列 */
            dprint(PRN_PTS,"raw_pts: %lld\n", RawPacket.Pts);
            dprint(PRN_SCD_INFO, "Get RawPhyAddr=0x%x,Len=%d\n", RawPacket.PhyAddr, RawPacket.Length);
            if (RawPacket.Pts == (UINT32)(-1))
            {
                RawPacket.Pts = (UINT64)(-1);
            }

            if (FMW_OK != SM_PushRaw(InstID, &RawPacket))
            {
                dprint(PRN_FATAL, "!!!push raw err!!!\n");
                break;
            }
            else
            {
                pSmInstArray->FillNewRawFlag = 1;
            #ifdef VFMW_SCD_LOWDLY_SUPPORT
                DBG_CountTimeInfo(InstID, STATE_RCV_RAW, 0);
            #endif
                if (CHECK_REC_POS_ENABLE(STATE_RCV_RAW))
                {
                    ThisTime = VFMW_OSAL_GetTimeInMs();	
                    if ((ThisTime - last_rec_pos_time[InstID]) > g_TraceBsPeriod)
                    {
                        rec_pos_print_flag = 1;
                        last_rec_pos_time[InstID] = ThisTime;
                    }
                    else
                    {
                        rec_pos_print_flag = 0;
                    }

                    if (rec_pos_print_flag == 1)
                    {
                        dat = (InstID<<24) + (STATE_RCV_RAW<<16);
                        REC_POS(dat);
                    }
                }
            }

        #ifdef ENV_ARMLINUX_KERNEL
            if (InstID == save_str_chan_num && NULL != vfmw_save_str_file)
            {
                VID_STD_E eStd = pSmInstArray->Config.VidStd;
                VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
                /* 某些协议码流成帧保存，帧前加长度 */
                if (eStd == VFMW_VP6 || eStd == VFMW_VP6F || eStd == VFMW_VP6A || eStd == VFMW_VP8 
                        || eStd == VFMW_H263 || eStd == VFMW_SORENSON || eStd == VFMW_RAW
                        || eStd == VFMW_REAL8 || eStd == VFMW_REAL9 || eStd == VFMW_DIVX3
                        || (eStd == VFMW_VC1 && 1 != pSmInstArray->Config.StdExt.Vc1Ext.IsAdvProfile) )
                {
                    OSAL_FileWrite((char *)&RawPacket.Length, 4, vfmw_save_str_file);
                }                
                OSAL_FileWrite((char *)RawPacket.VirAddr, RawPacket.Length, vfmw_save_str_file);
                VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
            }
        #endif

        }
        else
        {
            /* 此实例raw数据已满 */
            dprint(PRN_BLOCK, "Chan%d raw full\n", InstID);
            PrintScdRawState(s_SmIIS.ThisInstID, 0);
            break;
        }
    }

    return;
}

SINT32 FillEosRawStream(SINT32 InstID, STREAM_DATA_S *pRawPacket)
{
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[InstID];
    
    UINT8 au8EndFlag[5][20] = 
    {
        /* H264 */
        {
            0x00, 0x00, 0x01, 0x0b, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45,
            0x4e, 0x44, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        /* VC1ap,AVS */
        {
            0x00, 0x00, 0x01, 0xfe, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45,
            0x4e, 0x44, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        /* MPEG4 */
        {
            0x00, 0x00, 0x01, 0xfe, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45,
            0x4e, 0x44, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x01, 0x00
        },
        /* MPEG2 */
        {
            0x00, 0x00, 0x01, 0xb7, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45,
            0x4e, 0x44, 0x00, 0x00, 0x01, 0xb7, 0x00, 0x00, 0x00, 0x00
        },
        /* H265 */
        {
            0x00, 0x00, 0x01, 0x62, 0x00, 0x48, 0x53, 0x50, 0x49, 0x43,
            0x45, 0x4e, 0x44, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
        },
    };
    UINT8* pu8Flag = NULL;
    UINT32 u32FlagLen = 0;

    if (NULL == pRawPacket)
    {
        dprint(PRN_FATAL, "%s: pRawPacket = NULL!\n", __func__);
        return FMW_ERR_SCD;
    }

    /* CodecType Relative */
    switch (pSmInstArray->Config.VidStd)
    {
        case STD_HEVC:
            pu8Flag = au8EndFlag[4];
            u32FlagLen = 16;
            break;
            
        case STD_H264:
            pu8Flag = au8EndFlag[0];
            u32FlagLen = 15;
            break;
            
        case STD_MVC:
            pu8Flag = au8EndFlag[0];
            u32FlagLen = 15;
            break;

        case STD_AVS:
            pu8Flag = au8EndFlag[1];
            u32FlagLen = 15;
            break;

        case STD_MPEG4:
            pu8Flag = au8EndFlag[2];
            u32FlagLen = 19;
            break;

        case STD_MPEG2:
            pu8Flag = au8EndFlag[3];
            u32FlagLen = 16;
            break;

        case STD_VC1:
            if (1 == pSmInstArray->Config.StdExt.Vc1Ext.IsAdvProfile)
            {
                pu8Flag = au8EndFlag[1];
                u32FlagLen = 15;
            }
            break;

        case STD_H263:
        case STD_DIVX3:
        case STD_REAL8:
        case STD_REAL9:
        case STD_VP6:
        case STD_VP6F:
        case STD_VP6A:
        case STD_VP8:
        case STD_SORENSON:
            break;

        default:
            dprint(PRN_FATAL, "%s: unkown standard type = %d!\n", __func__, pSmInstArray->Config.VidStd);
            return FMW_ERR_SCD;
    }
    
    if (u32FlagLen > pRawPacket->Length)
    {
        dprint(PRN_FATAL, "%s: FlagLen(%d) > RawPacketLength(%d)\n", __func__, u32FlagLen, pRawPacket->Length);
        return FMW_ERR_SCD;
    }

    if (u32FlagLen != 0)
    {
        memcpy(pRawPacket->VirAddr, pu8Flag, u32FlagLen);
        pRawPacket->Length = u32FlagLen;
    }

    return FMW_OK;
}

SINT32 FillExtraData(SINT32 InstID, STREAM_DATA_S *pRawPacket)
{
    VID_STD_E     VidStd;
    SM_INSTANCE_S *pSmInstArray = NULL; 
    
    FMW_ASSERT_RET((InstID >= 0) && (InstID < SM_MAX_SMID), FMW_ERR_PARAM);
    FMW_ASSERT_RET(pRawPacket != NULL, FMW_ERR_PARAM);
    
    if (pRawPacket->Length <= 0)
    {
        dprint(PRN_ERROR, "%s: RawPacket Length %d <= 0\n", __func__, pRawPacket->Length);
        return FMW_ERR_PARAM;
    }
    
    pSmInstArray = s_SmIIS.pSmInstArray[InstID];
    VidStd = pSmInstArray->Config.VidStd;
    
    switch(VidStd)
    {
        case STD_VC1:
            if (1 == pSmInstArray->Config.StdExt.Vc1Ext.IsAdvProfile)
            {
                if (pRawPacket->RawExt.Flags & VDEC_BUFFERFLAG_CODECCONFIG)
                {
                    if (pRawPacket->Length > HEADER_BUFFER_SIZE)
                    {
                        dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, header_buf:%d)\n", 
                                          __func__, VidStd, pRawPacket->Length, HEADER_BUFFER_SIZE);
                        return FMW_ERR_NOMEM;
                    }
                    else
                    {
                        /*保存前置引导码*/
                        pSmInstArray->HeaderLen = pRawPacket->Length;
                        memcpy(pSmInstArray->HeaderBuf, pRawPacket->VirAddr, pRawPacket->Length);
                    }
                }
                else if (pRawPacket->RawExt.IsSeekPending)
                {
                    if (pRawPacket->Length+pSmInstArray->HeaderLen > pRawPacket->RawExt.BufLen)
                    {
                        dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, str_buf:%d)\n", 
                                          __func__, VidStd, pRawPacket->Length+pSmInstArray->HeaderLen, pRawPacket->RawExt.BufLen);
                        return FMW_ERR_NOMEM;
                    }
                    else
                    {
                        /*补上前置引导码*/
                        memmove((pRawPacket->VirAddr+pSmInstArray->HeaderLen), pRawPacket->VirAddr, pRawPacket->Length);
                        memcpy(pRawPacket->VirAddr, pSmInstArray->HeaderBuf, pSmInstArray->HeaderLen);
                        pRawPacket->Length += pSmInstArray->HeaderLen;
                    }
                }
            }
            else
            {
                if (pRawPacket->RawExt.Flags & VDEC_BUFFERFLAG_CODECCONFIG)
                {
                    if (pRawPacket->Length+12 > pRawPacket->RawExt.BufLen || pRawPacket->Length+12 > HEADER_BUFFER_SIZE)
                    {
                        dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, str_buf:%d, header_buf:%d)\n", 
                                          __func__, VidStd, pRawPacket->Length+12, pRawPacket->RawExt.BufLen, HEADER_BUFFER_SIZE);
                        return FMW_ERR_NOMEM;
                    }
                    else
                    {
                        /*补上宽高*/
                        memmove((pRawPacket->VirAddr+8), pRawPacket->VirAddr, pRawPacket->Length);
                        memcpy(pRawPacket->VirAddr, &pRawPacket->RawExt.CfgWidth, 4);
                        memcpy((pRawPacket->VirAddr+4), &pRawPacket->RawExt.CfgHeight, 4);
                        /*后缀补零*/
                        memset((pRawPacket->VirAddr+12), 0, 4);

                        pRawPacket->Length = 16;
                        /*保存前置引导码*/
                        pSmInstArray->HeaderLen = pRawPacket->Length;
                        memcpy(pSmInstArray->HeaderBuf, pRawPacket->VirAddr, pRawPacket->Length);
                    }
                }
                else
                {
                    if (pRawPacket->Length+pSmInstArray->HeaderLen > pRawPacket->RawExt.BufLen)
                    {
                        dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, str_buf:%d)\n", 
                                          __func__, VidStd, pRawPacket->Length+pSmInstArray->HeaderLen, pRawPacket->RawExt.BufLen);
                        return FMW_ERR_NOMEM;
                    }
                    else
                    {
                        /*补上前置引导码*/
                        memmove((pRawPacket->VirAddr+pSmInstArray->HeaderLen), pRawPacket->VirAddr, pRawPacket->Length);
                        memcpy(pRawPacket->VirAddr, pSmInstArray->HeaderBuf, pSmInstArray->HeaderLen);
                        pRawPacket->Length += pSmInstArray->HeaderLen;
                    }
                }
            }
            break;

        case STD_DIVX3: 
            if (pRawPacket->Length+8 > pRawPacket->RawExt.BufLen)
            {
                dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space, (act:%d, str_buf:%d)\n", 
                                  __func__, VidStd, pRawPacket->Length+8, pRawPacket->RawExt.BufLen);
                return FMW_ERR_NOMEM;
            }
            else
            {
                //补上宽高
                memmove((pRawPacket->VirAddr+8), pRawPacket->VirAddr, pRawPacket->Length);
                memcpy(pRawPacket->VirAddr, &pRawPacket->RawExt.CfgWidth, 4);
                memcpy((pRawPacket->VirAddr+4), &pRawPacket->RawExt.CfgHeight, 4);
                pRawPacket->Length += 8;
            }
            break;

        case STD_REAL8:
            if (pRawPacket->RawExt.Flags & VDEC_BUFFERFLAG_CODECCONFIG)
            {
                if (pRawPacket->Length > HEADER_BUFFER_SIZE)
                {
                    dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, header_buf:%d)\n", 
                                      __func__, VidStd, pRawPacket->Length, HEADER_BUFFER_SIZE);
                    return FMW_ERR_NOMEM;
                }
                else
                {
                    /*保存前置引导码*/
                    pSmInstArray->HeaderLen = pRawPacket->Length;
                    memcpy(pSmInstArray->HeaderBuf, pRawPacket->VirAddr, pRawPacket->Length);
                }
            }
            else
            {
                if (pRawPacket->Length+pSmInstArray->HeaderLen > pRawPacket->RawExt.BufLen)
                {
                    dprint(PRN_ERROR, "%s(): Std(%d) buffer has no enough space,(act:%d, str_buf:%d)\n", 
                                      __func__, VidStd, pRawPacket->Length+pSmInstArray->HeaderLen, pRawPacket->RawExt.BufLen);
                    return FMW_ERR_NOMEM;
                }
                else
                {
                    /*补上前置引导码*/
                    memmove((pRawPacket->VirAddr+pSmInstArray->HeaderLen), pRawPacket->VirAddr, pRawPacket->Length);
                    memcpy((pRawPacket->VirAddr), pSmInstArray->HeaderBuf, pSmInstArray->HeaderLen);
                    pRawPacket->Length += pSmInstArray->HeaderLen;
                }
            }
            break;

        default:
            break;
    }

    return FMW_OK;
}

SINT32 ReadRawStreamData(SINT32 InstID, STREAM_DATA_S * pRawPacket)
{
    STREAM_INTF_S *pStreamIntf;
    STREAM_INTF_S  StreamIntf;
    SINT32 ret = FMW_ERR_SCD;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[InstID];

    memset(&StreamIntf, 0, sizeof(STREAM_INTF_S));
    if (NULL == pSmInstArray)
    {
        return FMW_ERR_SCD;    
    }

    pStreamIntf = VCTRL_GetStreamInterface(InstID);
    if ((NULL == pStreamIntf))
    {
        dprint(PRN_FATAL, "Chan %d has been destroyed or the function pointer -- ReadRawStreamData pStreamIntf is NULL!", InstID);
        return ret;
    }

    memcpy(&StreamIntf, pStreamIntf, sizeof(STREAM_INTF_S));
    if (NULL != pStreamIntf->read_stream)
    {
        ret = StreamIntf.read_stream( StreamIntf.stream_provider_inst_id, pRawPacket);
        ret = (0==ret)? FMW_OK: FMW_ERR_SCD;
    }

    if (ret == FMW_OK)
    {
        if (1 == pRawPacket->is_stream_end_flag)
        {
            if (FillEosRawStream(InstID, pRawPacket) != FMW_OK)
            {
                dprint(PRN_FATAL, "Chan %d FillEosRawStream failed!\n", InstID);
                return FMW_ERR_SCD;    
            }
            VCTRL_SetLastFrameState(InstID, LAST_FRAME_RECEIVE);
        }
        else
        {
            /* Fill extra data in omx path & normal dec mode */
            if (1 == s_SmIIS.pSmInstArray[InstID]->Config.IsOmxPath && 1 != s_SmIIS.pSmInstArray[InstID]->Config.SpecMode)
            {
                /* OMX通路部分协议解码需要增加额外的信息 */
                if (FillExtraData(InstID, pRawPacket) != FMW_OK)
                {
                    dprint(PRN_FATAL, "Chan %d FillExtraData failed!\n", InstID);
                    ret = ReleaseRawStreamData( StreamIntf.stream_provider_inst_id, pRawPacket);
                    if (ret != FMW_OK)
                    {
                        dprint(PRN_FATAL, "Release this packet failed!\n");
                    }
                    return FMW_ERR_SCD;    
                }
            }
        }
        pSmInstArray->RawPacketArray.RawTotalSize += pRawPacket->Length;
    }

    return ret;
}

SINT32 ReleaseRawStreamData(SINT32 InstID, STREAM_DATA_S * pRawPacket)
{
    STREAM_INTF_S *pStreamIntf;
    STREAM_INTF_S StreamIntf;
    SINT32 ret = FMW_ERR_SCD;
    pStreamIntf = VCTRL_GetStreamInterface(InstID);

    memset(&StreamIntf, 0, sizeof(STREAM_INTF_S));
    if (pStreamIntf == NULL)
    {
        dprint(PRN_FATAL, "Chan %d has been destroyed or the function pointer -- ReleaseRawStreamData pStreamIntf is NULL!", InstID);
        return FMW_ERR_SCD;
    }

    memcpy(&StreamIntf, pStreamIntf, sizeof(STREAM_INTF_S));
    if( NULL != pStreamIntf->release_stream )
    {
        ret = StreamIntf.release_stream( StreamIntf.stream_provider_inst_id, pRawPacket);
        ret = (0==ret)? FMW_OK: FMW_ERR_SCD;
    }

    if (NULL == s_SmIIS.pSmInstArray[InstID])
    {
        dprint(PRN_FATAL, "line: %d s_SmIIS.pSmInstArray[%d] is NULL\n", __LINE__,InstID);
        return FMW_ERR_SCD;
    }

    return ret;
}

SINT32 SM_MoveRawData(SM_INSTANCE_S *pSmInstArray)
{
    SINT32 LastPos=-1, PrePos=-1;
    STREAM_DATA_S *pLastRawPacket=NULL, *pPreRawPacket=NULL;

    LastPos = pSmInstArray->RawPacketArray.Tail-1;
    LastPos = (LastPos < 0)? LastPos+MAX_STREAM_RAW_NUM: LastPos;
    PrePos  = pSmInstArray->RawPacketArray.Tail-2;
    PrePos  = (PrePos < 0)? PrePos+MAX_STREAM_RAW_NUM: PrePos;

    pLastRawPacket = &pSmInstArray->RawPacketArray.RawPacket[LastPos];
    pPreRawPacket  = &pSmInstArray->RawPacketArray.RawPacket[PrePos];

    if (pPreRawPacket->Length+pLastRawPacket->Length <= pSmInstArray->Config.MaxRawPacketSize)
    {
        memcpy(pPreRawPacket->VirAddr+pPreRawPacket->Length, pLastRawPacket->VirAddr, pLastRawPacket->Length);
        pPreRawPacket->Length += pLastRawPacket->Length;

        ReleaseRawStreamData(pSmInstArray->InstID, pLastRawPacket);
        pSmInstArray->RawPacketArray.Tail = LastPos;
    }
    else
    {
        dprint(PRN_ERROR,"No space for raw move, total:%d+%d > max:%d!\n", pPreRawPacket->Length,pLastRawPacket->Length,pSmInstArray->Config.MaxRawPacketSize);
        return FMW_ERR_SCD;
    }

    return FMW_OK;
}


/************************************************************************
  原型    SINT32 SM_DoNextInstance ( SINT32 *pNextInstId )
  功能    本函数遍历SM的所有实例，找一个可以服务的实例，并启动SCD为其切割码流
  参数    无  
  返回值  如果找到可以服务的实例，返回FMW_OK
  否则返回错误码
 ************************************************************************/
SINT32 SM_DoNextInstance( SINT32 *pNextInstId )
{
    /* 可以删除CurInstID变量 */
    SINT32 i, CurInstID, NextInstId;
    SINT32 Ret;
    SINT32 WaitSegTime;
    /* stInstInfo应该初始化 */
    SM_INST_INFO_S  stInstInfo;
    /* memset(&stInstInfo, 0, sizeof(SM_INST_INFO_S)); */
    SINT32 FreshNum=0, FreshSize=0, SegBufTotalSize = 0;
    UADDR SegBufAddr = 0 ;
    SINT32 CurTimeInMs, WaitTime;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    UINT32 dat = 0;
    SM_INSTANCE_S *pSmInstArray = NULL;

    /* 处理SCD休眠 */
    if (s_eScdDrvSleepStage != SCDDRV_SLEEP_STAGE_NONE)
    {
        if (s_eScdDrvSleepStage == SCDDRV_SLEEP_STAGE_PREPARE)
        {
            s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_SLEEP;
        }
        dprint(PRN_ERROR, "s_eScdDrvSleepStage = SCDDRV_SLEEP_STAGE_SLEEP!\n");
        return FMW_ERR_NOTRDY;
    }

    /* 选择一个通道，准备新一次切割 */
    CurInstID  = s_SmIIS.ThisInstID;
    NextInstId = CurInstID;
    for ( i = 0; i < MAX_CHAN_NUM; i++ )
    {
        NextInstId = (NextInstId+1) % MAX_CHAN_NUM;

        /* 如果此实例未被激活，找下一个 */
        pSmInstArray = s_SmIIS.pSmInstArray[NextInstId];

        (VOID)SM_GetInfo( NextInstId, &stInstInfo );
        if ( SM_INST_MODE_IDLE == stInstInfo.InstMode )
        {
            continue;
        }

        /* 如果此实例已激活 */
        if ( (VFMW_REAL8 == pSmInstArray->Config.VidStd)    ||
             (VFMW_REAL9 == pSmInstArray->Config.VidStd)    ||
             (VFMW_DIVX3 == pSmInstArray->Config.VidStd)    ||
             (VFMW_VC1   == pSmInstArray->Config.VidStd && pSmInstArray->Config.StdExt.Vc1Ext.IsAdvProfile == 0) ||
             (VFMW_VP6F  == pSmInstArray->Config.VidStd)    ||
             (VFMW_VP6A  == pSmInstArray->Config.VidStd)    ||
             (VFMW_VP6   == pSmInstArray->Config.VidStd)    ||
             (VFMW_VP8   == pSmInstArray->Config.VidStd))
        {
            continue;
        }

        PrintScdRawState(NextInstId, 0);
        PrintScdSegState(NextInstId, 0);

        CurTimeInMs = VFMW_OSAL_GetTimeInMs();
        WaitTime =  CurTimeInMs - pSmInstArray->LastSCDStartTime;		
        if (WaitTime < 0)
        {
            WaitTime = 200;
            pSmInstArray->LastSCDStartTime = CurTimeInMs;
        }

        if ((pSmInstArray->LastCfgAllRawFlag == 1)
		 && (pSmInstArray->FillNewRawFlag == 0)   
	     && (WaitTime < 500))
        {
            continue;
        }
        
        pSmInstArray->LastSCDStartTime = CurTimeInMs;

        if ( 1 == pSmInstArray->SegFullFlag )   // seg释放比较慢，要看等了多少时间
        {
            PrintScdRawState(NextInstId, 0);
            PrintScdSegState(NextInstId, 0);

            GetFreshSegStream(&pSmInstArray->StreamSegArray, &FreshNum, &FreshSize);
            GetSegBuf(&pSmInstArray->StreamSegArray, &SegBufAddr, &SegBufTotalSize);

            if ( 0 == pSmInstArray->IsCounting )
            {  
                if (FreshSize < (SegBufTotalSize / 2) && FreshNum < 128)
                {
                    // 之前还没有等待，刚刚阻塞的
                    pSmInstArray->IsCounting = 1;
                    CalcInstBlockTime( NextInstId, 1 );
                }
            }
            else
            {  
                // 以前就是阻塞状态，要看阻塞了多久，以及seg buf是否已经形成死锁
                WaitSegTime = CalcInstBlockTime( NextInstId, 0 );
                #ifdef RELEASE_LONG_TIME_SEG
                if ( (WAIT_SEG_REL_MAX_TIME < WaitSegTime) && (FreshSize < (SegBufTotalSize / 4)) && (FreshNum < 64))
                {
                    dprint(PRN_FATAL,"long time(%d ms) not release stream seg, release anyway!\n", WaitSegTime );
                    // 已经超时了,强制释放一包看看...
                    ReleaseStreamSeg( &pSmInstArray->StreamSegArray, 0xffffffff );
                    pSmInstArray->IsCounting  = 0;
                    pSmInstArray->SegFullFlag = 0;
                }
                #endif
            }
        }
        else
        {
            pSmInstArray->IsCounting = 0;
        }

        /* 尝试切割 */
        Ret = CutStreamWithSCD( pSmInstArray );
        if( FMW_ERR_SEGFULL == Ret )
        {
            pSmInstArray->SegFullFlag = 1;
        }
        else
        {
            pSmInstArray->SegFullFlag = 0;
        }

        if( FMW_OK == Ret )
        {    
            // 已经将SCD投入到一个实例了
            *pNextInstId = NextInstId;
            SetInstMode(NextInstId, SM_INST_MODE_WORK);
        #ifdef VFMW_SCD_LOWDLY_SUPPORT
            DBG_CountTimeInfo(NextInstId, STATE_SCD_START, pSmInstArray->Config.ScdLowdlyEnable);
        #endif
            if (CHECK_REC_POS_ENABLE(STATE_SCD_START))
            {
                CurTimeInMs = VFMW_OSAL_GetTimeInMs();	
                if ((CurTimeInMs - last_rec_pos_time[NextInstId]) > g_TraceBsPeriod)
                {
                    last_rec_pos_time[NextInstId] = CurTimeInMs;
                    dat = (NextInstId<<24) + (STATE_SCD_START<<16);
                    REC_POS(dat);
                }
            }

            return FMW_OK;
        }
    }

    return FMW_ERR_NOTRDY;
}

/************************************************************************
  原型    VOID SM_SCDIntServeProc ( VOID )
  功能    本函数为SCD的中断服务程序，响应SCD的中断信号并处理其返回的信息。
  参数    无  
  返回值  无
 ************************************************************************/
VOID SM_SCDIntServeProc ( VOID )
{
    SINT32 NextInstID;
    SINT32 SmID;
    SINT32 dat = 0;
    UINT32 CurTimeInMs = 0;
    SM_INSTANCE_S *pSmInstArray;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    SINT32 Ret;
    SINT32 CurRawNum = 0;

#ifndef SCD_BUSY_WAITTING   
    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD); 
    dat = RD_SCDREG(REG_SCD_OVER) & 0x01;
    if( (dat & 1) == 0 )
    {
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        return;
    }
#endif

    /* 清除SCD中断 */
    WR_SCDREG(REG_SCD_INI_CLR, 1);

    s_SCDInISR = 1;

    if (CHECK_REC_POS_ENABLE(STATE_SCD_INTERRUPT))
    {
        CurTimeInMs = VFMW_OSAL_GetTimeInMs();	
        if ((CurTimeInMs - last_rec_pos_time[s_SmIIS.ThisInstID]) > g_TraceBsPeriod)
        {
            last_rec_pos_time[s_SmIIS.ThisInstID] = CurTimeInMs;
            dat = (s_SmIIS.ThisInstID<<24) + (STATE_SCD_INTERRUPT<<16);
            REC_POS(dat);
        }
    }
    SmID = s_SmIIS.ThisInstID;
    pSmInstArray = s_SmIIS.pSmInstArray[SmID];

    /* 仅防万一 */
    if( 0 == s_SmIIS.IsScdDrvOpen || NULL == pSmInstArray)
    {
        s_SCDInISR = 0;
        s_SmIIS.SCDState = 0;
#ifndef SCD_BUSY_WAITTING 
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
#endif
        return;
    }

    /* 正常情况下当SCD中断时，s_SmIIS.SCDState一定等于1 */
    if( 1 == s_SmIIS.SCDState )
    {
        /* 如果这个通道被停掉，则不处理SCD的上行消息 */
        if( pSmInstArray->Mode == SM_INST_MODE_WORK )
        {
            PrintScdRawState(s_SmIIS.ThisInstID, 0);
            PrintScdSegState(s_SmIIS.ThisInstID, 0);
#ifdef VFMW_SCD_LOWDLY_SUPPORT
            DBG_CountTimeInfo(s_SmIIS.ThisInstID, STATE_SCD_INTERRUPT, 0);
#endif
            (VOID)ProcessScdReturn( pSmInstArray );

            /* 背景: 因为OMX通路码流包个数固定，如所有的包都不能切流，VFMW不释放，上层也不能继续送流，导致解码停止。
               判断: 该次切割已配置了所有码流包，但是切割完仍有同样包数码流未能释放。
               容错: 最后一包数据拷到倒数第二包中，释放最后一包，如无法拷贝，强制复位SCD */
            if (1 == pSmInstArray->Config.IsOmxPath && 0 == gIsFPGA)
            {
                Ret  = GetRawStreamNum(&pSmInstArray->RawPacketArray, &CurRawNum);
                if(Ret !=FMW_OK)
                {
                    dprint(PRN_ERROR,"SCD GetRawStreamNum Fail.\n");
                }
                if (1 == pSmInstArray->LastCfgAllRawFlag
                 && CurRawNum == pSmInstArray->Config.MaxRawPacketNum)
                {
                    if (SM_MoveRawData(pSmInstArray) != FMW_OK)
                    {
                        dprint(PRN_ERROR,"Move raw data failed, force to reset scd.\n");
                        SM_Reset(pSmInstArray->InstID);
                    }
                }
            }
            
            PrintScdRawState(s_SmIIS.ThisInstID, 0);
            PrintScdSegState(s_SmIIS.ThisInstID, 0);
        }
        s_SmIIS.SCDState = 0;  // 标志SCD返回值已经处理完毕
        if( FMW_OK == SM_DoNextInstance( &NextInstID ) )
        {
            s_SmIIS.ThisInstID = NextInstID;
            s_SmIIS.SCDState   = 1;  // 标记SCD正在处理
            s_SmIIS.LastProcessTime = VFMW_OSAL_GetTimeInMs();
        }
    }

    s_SCDInISR = 0;
    SM_GiveThreadEvent(SmID);
#ifndef SCD_BUSY_WAITTING 
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
#endif

    return;
}


SINT32 WaitSCDFinish(VOID)
{
    SINT32 i;

    if ( 1 == s_SmIIS.SCDState )
    {
        for ( i=0; i<SCD_TIME_OUT_COUNT; i++ )
        {
            if ( (RD_SCDREG( REG_SCD_OVER ) & 1) )
            {
                return FMW_OK;
            }
            else
            {
                //OSAL_MSLEEP(10);
            }
        }

        return FMW_ERR_SCD;
    }
    else
    {
        return FMW_OK;
    }
}


/************************************************************************
  原型    VOID SM_Wakeup ( VOID )
  功能    本函数用于唤醒SM模块，避免SM停工后无法恢复运行。
  如果采用线程监控SCD，则解码线程在每解完一帧调用此函数。
  如果采用定时中断监控SCD，则在定时中断中调用此函数。
  参数    无  
  返回值  无
 ************************************************************************/
VOID SM_Wakeup(VOID)
{
    SINT32 NextInstID;
    UINT32 CurTime, DelayTime;
    UINT32 MaxTimeOut = (0 == gIsFPGA)? SCD_TIMEOUT: SCD_FPGA_TIMEOUT; //FPGA wait longer
    
    /* 试图填充各通道的raw数据 */
    for ( NextInstID=0; NextInstID < MAX_CHAN_NUM; NextInstID++ )
    {
        if( NULL != s_SmIIS.pSmInstArray[NextInstID] 
                && SM_INST_MODE_WORK == s_SmIIS.pSmInstArray[NextInstID]->Mode )
        {
            /* 填充NextInstID的raw数据 */
            FillRawData(NextInstID);
        }
    }

    /* 如果s_SmIIS.SCDState等于1，表示SCD并未停工 */
    if ( 0 == s_SmIIS.SCDState )
    {
        if ( FMW_OK == SM_DoNextInstance( &NextInstID ) )
        {
            s_SmIIS.ThisInstID = NextInstID;
            s_SmIIS.SCDState   = 1;  // 标记SCD正在处理
            s_SmIIS.LastProcessTime = VFMW_OSAL_GetTimeInMs();
        }
    }
    else
    {
#ifdef SCD_BUSY_WAITTING
        if ( FMW_OK == WaitSCDFinish() )
        {
            SM_SCDIntServeProc();  // 硬件已经完成，调用中断服务程序处理其状态
            return;
        }
#endif
		
        /* 让等待SCD与其它调度并行起来，即, 如果SCD没有返回，不死等它，而是退出做其它工作 */
        CurTime = VFMW_OSAL_GetTimeInMs();
        DelayTime = CurTime - s_SmIIS.LastProcessTime;
        if (CurTime < s_SmIIS.LastProcessTime)
        {
            DelayTime = 0;
            s_SmIIS.LastProcessTime = CurTime;
        }

        if (DelayTime > MaxTimeOut)
        {
            dprint(PRN_ERROR, "SCD Time Out(%d/%d ms), Reset SCD!\n", DelayTime, MaxTimeOut);
			
            ResetSCD();
            s_SmIIS.SCDState = 0;  //硬件Scd可以工作
            DeleteLastSendRaw(s_SmIIS.ThisInstID);
            return;
        }
    }

    return;
}


/************************************************************************
  原型    VOID PrintScdVtrlReg()
  功能    打印Scd控制寄存器函数
  参数    
  返回值  无
 ************************************************************************/
VOID PrintScdVtrlReg()
{

    SM_CTRLREG_S SmCtrlReg = {0};

    SmCtrlReg.DownMsgPhyAddr = RD_SCDREG(REG_LIST_ADDRESS);
    // UP_ADDRESS
    SmCtrlReg.UpMsgPhyAddr = RD_SCDREG(REG_UP_ADDRESS);

    // UP_LEN
    SmCtrlReg.UpLen = RD_SCDREG(REG_UP_LEN);

    // BUFFER_FIRST
    SmCtrlReg.BufferFirst = RD_SCDREG(REG_BUFFER_FIRST);

    // BUFFER_LAST
    SmCtrlReg.BufferLast = RD_SCDREG(REG_BUFFER_LAST);

    // BUFFER_INI
    SmCtrlReg.BufferIni= RD_SCDREG(REG_BUFFER_INI); 

    // SCD_PROTOCOL    
    SmCtrlReg.ScdProtocol = RD_SCDREG(REG_SCD_PROTOCOL);

    // SCD_START
    SmCtrlReg.ScdStart = RD_SCDREG(REG_SCD_START); 

    dprint(PRN_SCD_REGMSG,"***Print Scd Vtrl Reg Now\n");
    dprint(PRN_SCD_REGMSG,"DownMsgPhyAddr = %x\n", SmCtrlReg.DownMsgPhyAddr);
    dprint(PRN_SCD_REGMSG,"UpMsgPhyAddr = %x\n", SmCtrlReg.UpMsgPhyAddr);
    dprint(PRN_SCD_REGMSG,"UpLen = %x\n", SmCtrlReg.UpLen);
    dprint(PRN_SCD_REGMSG,"BufferFirst = %x\n", SmCtrlReg.BufferFirst);
    dprint(PRN_SCD_REGMSG,"BufferLast = %x\n", SmCtrlReg.BufferLast);
    dprint(PRN_SCD_REGMSG,"BufferIni = %x\n", SmCtrlReg.BufferIni);
    dprint(PRN_SCD_REGMSG,"ScdProtocol = %x\n", SmCtrlReg.ScdProtocol);
    dprint(PRN_SCD_REGMSG,"ScdStart = %x\n", SmCtrlReg.ScdStart);

}

/************************************************************************
  原型    VOID PrintDownMsg()
  功能    打印下行消息池
  参数    
  返回值  无
 ************************************************************************/
VOID PrintDownMsg(UADDR DownMsgPhyAddr, SINT32 * pDownMsgVirAddr, SINT32 PushRawNum)
{
    SINT32 i, j;

    dprint(PRN_SCD_REGMSG,"***Print Down Msg Now\n");
    dprint(PRN_SCD_REGMSG,"DownMsgVirAddr = %p   \n",pDownMsgVirAddr);
    dprint(PRN_SCD_REGMSG,"DownMsgPhyAddr = %x   \n",DownMsgPhyAddr);
    for (i = 0, j = 0; i < PushRawNum; i++)
    {
        dprint(PRN_SCD_REGMSG,"DownMsg[%d] = %x   ",j,pDownMsgVirAddr[j]);
        j++;
        dprint(PRN_SCD_REGMSG,"DownMsg[%d] = %x   ",j,pDownMsgVirAddr[j]);
        j++;
        dprint(PRN_SCD_REGMSG,"DownMsg[%d] = %x   ",j,pDownMsgVirAddr[j]);
        j++;
        dprint(PRN_SCD_REGMSG,"\n");
    }

}

/************************************************************************
  原型    VOID PrintScdStateReg()
  功能    打印Scd状态寄存器函数
  参数    
  返回值  无
 ************************************************************************/
VOID PrintScdStateReg(SM_STATEREG_S *pSmStateReg)
{

    dprint(PRN_SCD_REGMSG, "***Print Scd State Reg\n");
    dprint(PRN_SCD_REGMSG, "Scdover = %d \n",pSmStateReg->Scdover);
    dprint(PRN_SCD_REGMSG, "ScdInt = %d \n",pSmStateReg->ScdInt);
    dprint(PRN_SCD_REGMSG, "ShortScdNum = %d \n",pSmStateReg->ShortScdNum);
    dprint(PRN_SCD_REGMSG, "ScdNum = %d \n",pSmStateReg->ScdNum);
    dprint(PRN_SCD_REGMSG, "ScdRollAddr = %0x \n",pSmStateReg->ScdRollAddr);
    dprint(PRN_SCD_REGMSG, "SrcEaten = %d \n",pSmStateReg->SrcEaten);

}

/************************************************************************
  原型    VOID PrintScdRawState()
  功能    打印Raw队列的详细情况
  参数    
  返回值  无
 ************************************************************************/
VOID PrintScdRawState(SINT32 SmID, SINT32 PrintDetail)
{
    SINT32 i,RawNum,RawIndex;
    RAW_ARRAY_S *pRawStreamArray = NULL;

    i = 0;
    RawNum = 0;
    RawIndex = 0;

    if (IsDprintTypeEnable(PRN_SCD_INFO))
    {
        pRawStreamArray = &s_SmIIS.pSmInstArray[SmID]->RawPacketArray;

        dprint(PRN_SCD_INFO, "RawHead=%d\n",pRawStreamArray->Head);
        dprint(PRN_SCD_INFO, "RawTail=%d\n",pRawStreamArray->Tail);
        dprint(PRN_SCD_INFO, "RawHistory=%d\n",pRawStreamArray->History);		
        dprint(PRN_SCD_INFO, "RawFirstPacketOffset=%d\n",pRawStreamArray->FirstPacketOffset);
        dprint(PRN_SCD_INFO, "CurShowIndex=%d\n",pRawStreamArray->CurShowIndex);

        if (1 == PrintDetail)
        {
            if(FMW_OK !=  GetRawStreamNum(pRawStreamArray,&RawNum))
            {
                dprint(PRN_DBG, "%s %d FMW_OK !=  GetRawStreamNum!!\n",__FUNCTION__,__LINE__);
            }
            RawIndex = pRawStreamArray->Head;
            for (i = 0; i < RawNum; i++, RawIndex++)
            {
                dprint(PRN_SCD_INFO, "RawPhyAddr=0x%x\n",pRawStreamArray->RawPacket[RawIndex].PhyAddr);
                dprint(PRN_SCD_INFO, "RawVirAddr=%p\n",pRawStreamArray->RawPacket[RawIndex].VirAddr);
                dprint(PRN_SCD_INFO, "RawLength=%d\n",pRawStreamArray->RawPacket[RawIndex].Length);
                dprint(PRN_SCD_INFO, "RawPts=%lld\n",pRawStreamArray->RawPacket[RawIndex].Pts);      
            }
        }
    }
}


/************************************************************************
  原型    VOID PrintScdRawState()
  功能    打印Raw队列的详细情况
  参数    
  返回值  无
 ************************************************************************/
VOID PrintSmInfo(SINT32 SmID)
{
    SINT32 i, idx;
    SM_INST_INFO_S SmInstInfo = {0};
    RAW_ARRAY_S *pstRaw;
    SM_INSTANCE_S *pSmInstArray = s_SmIIS.pSmInstArray[SmID];

    SM_GetInfo(SmID, &SmInstInfo);
    if (NULL == pSmInstArray)
    {
        return;
    }
    dprint(PRN_ALWS, "------------------ s_SmIIS.SmInstArray[%d] --------------------\n",SmID);

    dprint(PRN_ALWS, "%-25s :%d\n", "Mode",pSmInstArray->Mode);
    dprint(PRN_ALWS, "%-25s :%d\n", "Priority",pSmInstArray->Config.Priority);
    dprint(PRN_ALWS, "%-25s :%d\n", "VidStd",pSmInstArray->Config.VidStd);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "BufPhyAddr",pSmInstArray->Config.BufPhyAddr);
    dprint(PRN_ALWS, "%-25s :%p\n", "pBufVirAddr",pSmInstArray->Config.pBufVirAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "BufSize",pSmInstArray->Config.BufSize);

    dprint(PRN_ALWS, "%-25s :0x%x\n", "ScdRegBaseAddr",   gScdRegBaseAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "SmPushRaw.PushRawNum",pSmInstArray->SmPushRaw.PushRawNum);
    dprint(PRN_ALWS, "%-25s :%d\n", "SmPushRaw.PushRawTotalLen",pSmInstArray->SmPushRaw.PushRawTotalLen);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "DownMsgPhyAddr",pSmInstArray->BufAddrCfg.DownMsgPhyAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "DownMsgSize",pSmInstArray->BufAddrCfg.DownMsgSize);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "UpMsgPhyAddr",pSmInstArray->BufAddrCfg.UpMsgPhyAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "UpMsgNum",pSmInstArray->BufAddrCfg.UpMsgNum);
    dprint(PRN_ALWS, "%-25s :%d\n", "UpMsgSize",pSmInstArray->BufAddrCfg.UpMsgSize);

    dprint(PRN_ALWS, "%-25s :0x%x\n", "seg BufPhyAddr",pSmInstArray->BufAddrCfg.SegBufPhyAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "seg BufSize",pSmInstArray->BufAddrCfg.SegBufSize);
    dprint(PRN_ALWS, "%-25s :%d\n", "seg BufUsed", SmInstInfo.TotalSegSize );
    dprint(PRN_ALWS, "%-25s :%d\n", "seg BufItemNum", SmInstInfo.SegNum);

    dprint(PRN_ALWS, "%-25s :%d\n", "raw StreamHold", SmInstInfo.TotalRawSize);
    dprint(PRN_ALWS, "%-25s :%d\n", "raw StreamPacketNum", SmInstInfo.RawNum);

    dprint(PRN_ALWS, "%-25s :%d\n", "filter ProtocolType",pSmInstArray->SegFilter.ProtocolType);
    dprint(PRN_ALWS, "%-25s :%d\n", "filter ModeFlag",pSmInstArray->SegFilter.ModeFlag);
    dprint(PRN_ALWS, "%-25s :%d\n", "filter LastH263Num",pSmInstArray->SegFilter.LastH263Num);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "filter SegBufPhyAddr",pSmInstArray->SegFilter.SegBufPhyAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "filter SegBufSize",pSmInstArray->SegFilter.SegBufSize);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "filter SegBufRollAddr",pSmInstArray->SegFilter.SegBufRollAddr);
    dprint(PRN_ALWS, "%-25s :0x%x\n", "filter pScdUpMsg",pSmInstArray->SegFilter.pScdUpMsg);
    dprint(PRN_ALWS, "%-25s :%d\n", "filter SegNum",pSmInstArray->SegFilter.SegNum);
    dprint(PRN_ALWS, "%-25s :%d\n", "BlockTimeInMs",pSmInstArray->BlockTimeInMs);
    dprint(PRN_ALWS, "%-25s :%d\n", "LastBlockTime",pSmInstArray->LastBlockTime);
    dprint(PRN_ALWS, "%-25s :%lld\n", "LastPts",pSmInstArray->LastPts);
    dprint(PRN_ALWS, "%-25s :%d\n", "ThisInstID",s_SmIIS.ThisInstID);
    dprint(PRN_ALWS, "%-25s :%d\n", "SCDState",s_SmIIS.SCDState);

    pstRaw = &pSmInstArray->RawPacketArray;

    dprint(PRN_ALWS, "\nraw packets Head : %d, Histroy : %d\n", "SCDState", pstRaw->Head, pstRaw->History);
    dprint(PRN_ALWS, "\nraw packets length is(first packet %d bytes used):\n", pstRaw->FirstPacketOffset);
    idx = pstRaw->History;
    for( i = 0; i < MAX_STREAM_RAW_NUM; i++ )
    {
        if ((i!=0) && ((i%10)==0) )
        {
            dprint(PRN_ALWS,"\n");
        }
        if( idx == pstRaw->Tail )
        {
            break;
        }
        else
        {
            dprint(PRN_ALWS,"%5d ", pstRaw->RawPacket[idx].Length);
        }

        idx++;
        if( idx >= MAX_STREAM_RAW_NUM )
        {
            idx -= MAX_STREAM_RAW_NUM;
        }
    }
    dprint(PRN_ALWS, "\n");

}


/************************************************************************
  原型    VOID PrintScdSegState()
  功能    打印Seg队列的详细情况
  参数    
  返回值  无
 ************************************************************************/
VOID PrintScdSegState(SINT32 SmID, SINT32 PrintDetail)
{
    SINT32 i,SegNum,SegIndex;
    SEG_ARRAY_S *pSegStreamArray = NULL;

    i = 0;
    SegNum = 0;
    SegIndex = 0;

    if (IsDprintTypeEnable(PRN_SCD_INFO))
    {
        pSegStreamArray = &s_SmIIS.pSmInstArray[SmID]->StreamSegArray;

        dprint(PRN_SCD_INFO, "SegHead=%d\n",pSegStreamArray->Head);
        dprint(PRN_SCD_INFO, "SegTail=%d\n",pSegStreamArray->Tail);
        dprint(PRN_SCD_INFO, "SegCurrent=%d\n",pSegStreamArray->Current);
        dprint(PRN_SCD_INFO, "SegBufPhyAddr=%x\n",pSegStreamArray->SegBufPhyAddr);
        dprint(PRN_SCD_INFO, "SegBufVirAddr=%p\n",pSegStreamArray->pSegBufVirAddr);
        dprint(PRN_SCD_INFO, "SegBufSize=%d\n",pSegStreamArray->SegBufSize);
        dprint(PRN_SCD_INFO, "SegBufReadAddr=%x\n",pSegStreamArray->SegBufReadAddr);
        dprint(PRN_SCD_INFO, "SegBufWriteAddr=%x\n",pSegStreamArray->SegBufWriteAddr);

        if (1 == PrintDetail)
        {
            if(FMW_OK !=  GetSegStreamNum(pSegStreamArray,&SegNum))
            {
                dprint(PRN_DBG, "%s %d FMW_OK !=  GetSegStreamNum\n",__FUNCTION__,__LINE__);
            }            
            SegIndex = pSegStreamArray->Head;
            for (i = 0; i < SegNum; i++, SegIndex++)
            {
                dprint(PRN_SCD_INFO, "SegPhyAddr=0x%x\n",pSegStreamArray->StreamSeg[SegIndex].PhyAddr);
                dprint(PRN_SCD_INFO, "SegVirAddr=%p\n",pSegStreamArray->StreamSeg[SegIndex].VirAddr);
                dprint(PRN_SCD_INFO, "SegLength=%d\n",pSegStreamArray->StreamSeg[SegIndex].LenInByte);
                dprint(PRN_SCD_INFO, "SegStreamID=%d\n",pSegStreamArray->StreamSeg[SegIndex].StreamID);
                dprint(PRN_SCD_INFO, "SegState=%d\n",pSegStreamArray->StreamSeg[SegIndex].SegState);
                dprint(PRN_SCD_INFO, "SegIsLastSeg=%d\n",pSegStreamArray->StreamSeg[SegIndex].IsLastSeg);
                dprint(PRN_SCD_INFO, "SegPts=%lld\n",pSegStreamArray->StreamSeg[SegIndex].Pts);              
            }
        }   
    }
}

