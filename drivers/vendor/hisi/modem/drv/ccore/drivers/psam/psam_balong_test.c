#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include "osl_malloc.h"
#include <bsp_hardtimer.h>
#include <bsp_softtimer.h>
#include <osl_sem.h>
#include "securec.h"
#include <mdrv_cipher.h>
#include <bsp_cipher.h>

#include <bsp_ipf.h>
#include <bsp_psam.h>
#include "psam_balong.h"

#ifdef CONFIG_MODULE_BUSSTRESS
#include <bsp_busstress.h>
static struct softtimer_list stress_tsk_timer_id;
static osl_sem_id    bus_stress_tsk_sem;
#endif

#define C_NON_STRAIGHT_P_V 0x00
//-psam test file needs ttf struct
#define TTF_OFFSET_OF_T(s, m) ((unsigned int)&(((s *)0)->m))
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*本内存属于哪一个内存池 */
    unsigned char                   ucClusterId;    /*本内存是属于哪一个级别*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* 该数据的下一段 */
    unsigned short                  usType;         /* 内存类型，DYN、BLK、EXT类型 */
    unsigned short                  usLen;          /* 申请数据的总长度，但不一定全部被使用 */
    unsigned short                  usUsed;         /* 已经使用的数据长度   */
    unsigned short                  usApp;          /* 使用者可以使用的区域 */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* 记录数据的原始指针 */
    unsigned char                  *pData;          /* 存放数据的指针，物理上指向结构体的连续内存 */
    void                           *pExtBuffAddr;   /* 保存extern类型的内存地址用于释放 */
    unsigned long                   ulForCds[1];    /*预留给CDS使用，GU模不用初始化*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned long                   ulForLte[6];    /*预留给LTE使用，GU模不用初始化*/
#endif
} TTF_MEM_ST;
//+psam test file needs ttf struct

unsigned int g_psamUlTaskId = 0;
int psam_st_all_init = 0;

void stmmac_EthTestBuildIpHdr(ETH_TEST_IP_PACKET_FORMAT_T *pstPkt, unsigned int ulLen)
{
	pstPkt->stSCTPHdr.Vers = 4;
    pstPkt->stSCTPHdr.HeaderLen = 5;
    pstPkt->stSCTPHdr.TOS = 3;
    pstPkt->stSCTPHdr.TOL = ulLen;
    pstPkt->stSCTPHdr.ID = 1;
    pstPkt->stSCTPHdr.ReservFlag = 0;
    pstPkt->stSCTPHdr.DF = 0;
    pstPkt->stSCTPHdr.MF = 0;
    pstPkt->stSCTPHdr.offset = 0;
    pstPkt->stSCTPHdr.TTL = 128;
    pstPkt->stSCTPHdr.Prot = 17; /* UDP */
    pstPkt->stSCTPHdr.Checksum = 0xEC3A;
    pstPkt->stSCTPHdr.SourceAddr = 0xACA84649;
    pstPkt->stSCTPHdr.DestAddr = 0x0202014E;

    pstPkt->SrcPort = 5088;
    pstPkt->DstPort = 2923;
    pstPkt->Checksum = 0;
    pstPkt->Length = pstPkt->stSCTPHdr.TOL;
}

void psam_dl_rpt1_switch(int value)
{
	return bsp_ipf_dl_rpt1_switch(value);
}

int psam_srest(void)
{
	return psam_srset();
}

int psam_limit_disable(void)
{
	return psam_disable_limit_func();
}

int psam_st_init(void)
{
    IPF_COMMON_PARA_S stCommPara;
    int s32Ret = 0;

    /*初始化时IP过滤的参数配置*/
    stCommPara.bEspSpiDisable = 1;      /* ESP SPI是否参与匹配控制信号 */
    stCommPara.bAhSpiDisable = 1;       /* AH SPI是否参与匹配控制信号 */
    stCommPara.bEspAhSel= 0;           /* 0选ESP，1选AH */
    stCommPara.bIpv6NextHdSel = 0;
    stCommPara.eMaxBurst = IPF_BURST_16;       /* BURST最大长度 */
    stCommPara.bSpWrrModeSel = 0;
    stCommPara.bSpPriSel = 0;          /* SP优先级选择 */
    stCommPara.bFltAddrReverse = 1;        /* 配置为0,地址为大端 */
    stCommPara.bFilterSeq = 0;         /* 过滤器配置顺序指示 */
    stCommPara.bAdReport = 0; /*上报AD第二个字指针*/
#ifdef IPF_NO_FILTER_TEST
    stCommPara.bMultiFilterChainEn = 0;/*单寄存器链模式*/
    stCommPara.bMultiModeEn = 0;/*静态业务模式*/
#endif
    stCommPara.bMultiFilterChainEn = 1;/*多寄存器链模式*/
    stCommPara.bMultiModeEn = 1;/*动态业务模式*/
	
    s32Ret = mdrv_ipf_init(&stCommPara) ;
    if (s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT(" TESTERROR    mdrv_ipf_init :%d   s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

	s32Ret = psam_reinit_regs();
	if (s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT(" TESTERROR    psam_reinit_regs :%d   s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }
	
    psam_st_all_init = 1;
    
    return OK;
}

int psam_st_dl_init(void)
{
    IPF_CHL_CTRL_S stCtrl;
    static IPF_FILTER_CONFIG_S stDlFilterInfo[50];
    int s32Ret = 0;
    unsigned int i = 0;
	
    memset_s(stDlFilterInfo, 50*sizeof(IPF_FILTER_CONFIG_S), 0x0, 50*sizeof(IPF_FILTER_CONFIG_S));
    for(i=0;i<49;i++)
    {
        stDlFilterInfo[i].u32FilterID = i;
        stDlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0xffffffff;
    }
    
    stDlFilterInfo[49].u32FilterID = 172;
    stDlFilterInfo[49].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x23C01;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8SrcAddr) = 0xACA84649;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8DstAddr) = 0x0202014E;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stDlFilterInfo[49].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 1;
    stDlFilterInfo[49].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 5100;
    stDlFilterInfo[49].stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stDlFilterInfo[49].stMatchInfo.unDstPort.Bits.u16DstPortHi = 5100;
    stDlFilterInfo[49].stMatchInfo.unTrafficClass.u32TrafficClass  = 3|(0xFF<<8);
    stDlFilterInfo[49].stMatchInfo.u32LocalAddressMsk = 0x00;
    stDlFilterInfo[49].stMatchInfo.unNextHeader.u32Protocol = 1;
    stDlFilterInfo[49].stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stDlFilterInfo[49].stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stDlFilterInfo[49].stMatchInfo.u32FltSpi = 4;

    if(psam_st_all_init != 1)
    {
        s32Ret = psam_st_init();
        if(s32Ret != OK)
        {
            IPF_PRINT(" TESTERROR    psam_st_INIT :%d\n",__LINE__);
            return ERROR;
        }
    }

    stCtrl.bDataChain = 1;
    stCtrl.bEndian = 1; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY; //tran or filter by bd descriptor
    stCtrl.u32WrrValue = 0;
    s32Ret = mdrv_ipf_config_dlchan(&stCtrl);/////Dose psam need do something else??
    if(s32Ret)
    {
        IPF_PRINT(" TESTERROR    mdrv_ipf_config_dlchan :%d s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, 50);
    if(s32Ret)    
    {
        IPF_PRINT(" TESTERROR    mdrv_ipf_set_filter :%d s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }
    
    s32Ret = mdrv_ipf_enable_chan(IPF_CHANNEL_DOWN, 1);
    if(s32Ret)
    {
        IPF_PRINT(" TESTERROR    mdrv_ipf_enable_chan :%d s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

	bsp_cipher_set_channel_dma(CIPHER_SECURITY_CHANNEL_5, 1);
    return OK;
}

int bsp_psam_dl_send_n2(unsigned int SendTimes,unsigned int SendNum)
{
    IPF_CONFIG_DLPARAM_S stDlPara[PSAM_DLBD_DESC_SIZE];
    int s32Ret = 0;
    unsigned int i = 0;
    unsigned int j = SendTimes;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    unsigned int u32Len = 100;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int DlSendBDNum = 0;
	
    pu8IPData = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData2 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData3 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData4 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }

	stSrcTtf[0].usUsed = u32Len;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[0].pData), u32Len*5);
	memset_s(stSrcTtf[0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[0].pData, u32Len);

    stSrcTtf[1].usUsed = u32Len;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];
	memset_s(stSrcTtf[1].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[1].pData, u32Len);

    stSrcTtf[2].usUsed = u32Len;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];
	memset_s(stSrcTtf[2].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[2].pData, u32Len);

    stSrcTtf[3].usUsed = u32Len;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];
	memset_s(stSrcTtf[3].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[3].pData, u32Len);

    stSrcTtf[4].usUsed = u32Len;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	memset_s(stSrcTtf[4].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[4].pData, u32Len);

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));

    while(j > 0)
    {
		u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
		if(u32BDNum > SendNum)
		{
			for(i=0;i < PSAM_DLBD_DESC_SIZE;i++)
			{
			    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
			    stDlPara[i].u16UsrField1= 200;
			    stDlPara[i].u16Len= u32Len*5;
			    stDlPara[i].u16Attribute= 0x28;/*设中断，仅搬移*/ 
			}	
			stDlPara[SendNum-1].u16Attribute= 0x29; 

			s32Ret = mdrv_ipf_config_dlbd(SendNum, stDlPara);
			if(s32Ret != IPF_SUCCESS)    
			{
				IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
				goto error0;
			} 
			j--;
			DlSendBDNum += (u32BDNum-1);
		}
		osl_task_delay(10);
    }
	IPF_PRINT("DlSendBDNum(BDs) =%u",DlSendBDNum);
	return OK;
	
error0:
    osl_free(pu8IPData4);
error1:
    osl_free(pu8IPData3);
error2:
    osl_free(pu8IPData2);
error3:
    osl_free(pu8IPData1);
error4:
    osl_free(pu8IPData);

    return ERROR;

}


int bsp_psam_dl_send(void)
{
	return bsp_psam_dl_send_n2(90000,20);
}

/* 2个TTF结点，配2个BD 一长一短，用于验证AD回退的有效性*/
int bsp_psam_st_001(void)
{
    psam_config_dlparam_s stDlPara[2];
    TTF_MEM_ST stSrcTtf;
    TTF_MEM_ST stSrcTtfShort;
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 2;
    int s32Ret = 0;
   
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }
	
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 
	
    stSrcTtf.usUsed = 1000;
    stSrcTtf.pData = osl_malloc(stSrcTtf.usUsed);
    stSrcTtf.pNext = NULL;
    if(stSrcTtf.pData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf.pData), stSrcTtf.usUsed);
	memset_s(stSrcTtf.pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	
    stDlPara[0].u32Data = (unsigned int)&stSrcTtf;
    stDlPara[0].u16UsrField1= 1200;
    stDlPara[0].u16Len= 1000;
    stDlPara[0].u16Attribute= 0x29;/*设中断，仅搬移*/
	
    osl_cache_flush(OSL_DATA_CACHE,stSrcTtf.pData,1000);
	
    stSrcTtfShort.usUsed = 200;
    stSrcTtfShort.pData = osl_malloc(stSrcTtfShort.usUsed);
    stSrcTtfShort.pNext = NULL;
    if(stSrcTtfShort.pData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtfShort.pData), stSrcTtfShort.usUsed);
	memset_s(stSrcTtfShort.pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtfShort.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtfShort.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

    stDlPara[1].u32Data = (unsigned int)(&stSrcTtfShort);
    stDlPara[1].u16UsrField1= 200;
    stDlPara[1].u16Len= 200;
    stDlPara[1].u16Attribute= 0x29; /*设中断，仅搬移*/
	
    osl_cache_flush(OSL_DATA_CACHE,stSrcTtfShort.pData,200);

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, (IPF_CONFIG_DLPARAM_S*)&stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error1;
    } 
    
error1:
    osl_free((unsigned int *)stSrcTtfShort.pData);
	osl_free((unsigned int *)stSrcTtf.pData);
	
    return s32Ret;
}

/* 1个TTF结点，配1个BD */
int bsp_psam_st_002(void)
{
    psam_config_dlparam_s stDlPara;
    TTF_MEM_ST stSrcTtf;
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 1;
    int s32Ret = 0;
   
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 
	
    stSrcTtf.usUsed = 1000;
    stSrcTtf.pData = osl_malloc(stSrcTtf.usUsed);
    stSrcTtf.pNext = NULL;
    if(stSrcTtf.pData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf.pData), stSrcTtf.usUsed);
	memset_s(stSrcTtf.pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf.usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
    
    stDlPara.u32Data = (unsigned int)(&stSrcTtf);
    stDlPara.u16UsrField1= 200;
    stDlPara.u16Len= 1000;
    stDlPara.u16Attribute= 0x29; /*设中断，仅搬移，cd 使能*/
	
    osl_cache_flush(OSL_DATA_CACHE, stSrcTtf.pData, 1000);
	
	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));

    s32Ret = mdrv_ipf_config_dlbd(u32Num, &stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error1;
    } 
    IPF_PRINT("stSrcTtf.pData = %x \n stDlPara.u32Data = %x \n &stSrcTtf = %x \n",stSrcTtf.pData,stDlPara.u32Data,&stSrcTtf);

	osl_task_delay(10); 
error1:
    osl_free((void *)(stSrcTtf.pData));
	
    return s32Ret;
}

/* 5个TTF结点，配1个BD */
int bsp_psam_st_003(void)
{
	int ret = OK;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    psam_config_dlparam_s stDlPara;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int u32Num = 1;
	
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }
    
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 

    pu8IPData = (unsigned char*)osl_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_malloc(100);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_malloc(300);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    }

	stSrcTtf[0].usUsed = 200;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[0].pData), 1000);
	memset_s(stSrcTtf[0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[0].pData, 200);
	
    stSrcTtf[1].usUsed = 200;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];
	memset_s(stSrcTtf[1].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[1].pData, 200);

    stSrcTtf[2].usUsed = 100;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];
	memset_s(stSrcTtf[2].pData, 100, 0x0, 100);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[2].pData, 100);

    stSrcTtf[3].usUsed = 200;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];
	memset_s(stSrcTtf[3].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[3].pData, 200);

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	memset_s(stSrcTtf[4].pData, 300, 0x0, 300);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[4].pData, 300);
	
    stDlPara.u32Data = (unsigned int)stSrcTtf;
    stDlPara.u16UsrField1= 200;
    stDlPara.u16Len= 1000;
    stDlPara.u16Attribute= 0x29; /*设中断，仅搬移*/

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, &stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    } 
    osl_task_delay(50);
	
    osl_free((void *)pu8IPData4);
error1:
    osl_free((void *)pu8IPData3);
error2:
    osl_free((void *)pu8IPData2);
error3:
    osl_free((void *)pu8IPData1);
error4:
    osl_free((void *)pu8IPData);

    return ret;
}

/* 5个TTF结点，配61个BD 仅搬移，每个bd有一个链5个ttf*/
int bsp_psam_st_004(void)
{
	int ret = OK;
    unsigned int BDNUM = 60;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    psam_config_dlparam_s stDlPara[BDNUM];
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int i = 0;
	
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }

    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 
	
    pu8IPData = (unsigned char*)osl_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_malloc(100);
    if(pu8IPData2 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_malloc(200);
    if(pu8IPData3 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_malloc(300);
    if(pu8IPData4 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    }

    stSrcTtf[0].usUsed = 200;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[0].pData), 1000);
	memset_s(stSrcTtf[0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[0].pData, 200);

    stSrcTtf[1].usUsed = 200;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];
	memset_s(stSrcTtf[1].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[1].pData, 200);

    stSrcTtf[2].usUsed = 100;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];
	memset_s(stSrcTtf[2].pData, 100, 0x0, 100);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[2].pData, 100);

    stSrcTtf[3].usUsed = 200;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];
	memset_s(stSrcTtf[3].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[3].pData, 200);

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	memset_s(stSrcTtf[4].pData, 300, 0x0, 300);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[4].pData, 300);
	
	for(i=0;i < BDNUM;i++)
	{
	    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
	    stDlPara[i].u16UsrField1= 200+i;
	    stDlPara[i].u16Len= 1000;
	    stDlPara[i].u16Attribute= 0x28; /*不设中断，仅搬移*/
	}	
	stDlPara[59].u16Attribute= 0x29;/*最后一个设置中断*/

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(BDNUM, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    } 
    osl_task_delay(50);

	osl_free((void *)pu8IPData4);
error1:
    osl_free((void *)pu8IPData3);
error2:
    osl_free((void *)pu8IPData2);
error3:
    osl_free((void *)pu8IPData1);
error4:
    osl_free((void *)pu8IPData);

    return ret;

}

/* 5个TTF结点，配30个BD 过滤搬移，每个bd带有个练5个ttf*/
int bsp_psam_st_005(void)
{
	int ret = OK;
    unsigned int BDNUM =  30;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    psam_config_dlparam_s stDlPara[BDNUM];
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int i = 0;
	
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }
    
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 

    pu8IPData = (unsigned char*)osl_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_malloc(100);
    if(pu8IPData2 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_malloc(200);
    if(pu8IPData3 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_malloc(300);
    if(pu8IPData4 == NULL)
    {
        IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    }
	
    stSrcTtf[0].usUsed = 200;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[0].pData), 1000);
	memset_s(stSrcTtf[0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[0].pData, 200);
	
    stSrcTtf[1].usUsed = 200;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];
	memset_s(stSrcTtf[1].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[1].pData, 200);

    stSrcTtf[2].usUsed = 100;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];
	memset_s(stSrcTtf[2].pData, 100, 0x0, 100);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[2].pData, 100);

    stSrcTtf[3].usUsed = 200;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];
	memset_s(stSrcTtf[3].pData, 200, 0x0, 200);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[3].pData, 200);

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	memset_s(stSrcTtf[4].pData, 300,0x0, 300);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[4].pData, 300);
	
	for(i=0;i < BDNUM;i++)
	{
	
	    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
	    stDlPara[i].u16UsrField1= 200+i;
	    stDlPara[i].u16Len= 1000;
	    stDlPara[i].u16Attribute= 0x28; /*不设中断，仅搬移*/
	}	
	    stDlPara[29].u16Attribute= 0x29; /*设中断*/

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(BDNUM, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
		ret = ERROR;
        goto error1;
    } 
    osl_task_delay(50);

	osl_free((void *)pu8IPData4);
error1:
    osl_free((void *)pu8IPData3);
error2:
    osl_free((void *)pu8IPData2);
error3:
    osl_free((void *)pu8IPData1);
error4:
    osl_free((void *)pu8IPData);

    return ret;

}


/* 5个TTF结点，配60个BD ，只过滤 */
int bsp_psam_st_006(void)
{
    unsigned char* pu8IPData[60];
    unsigned int u32Len = 1000;
    static psam_config_dlparam_s stDlPara[60];
    static TTF_MEM_ST stSrcTtf[60][5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 60;
    int s32Ret = 0;
    unsigned int i = 0;
	
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }
	
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    if(u32BDNum != PSAM_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
    } 

    for(i = 0; i < 60; i++)
    {
        pu8IPData[i] = (unsigned char*)osl_malloc(u32Len);
        if(pu8IPData[i] == NULL)
        {
            IPF_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        }

        stSrcTtf[i][0].usUsed = 200;
        stSrcTtf[i][0].pData = pu8IPData[i];
        stSrcTtf[i][0].pNext = &stSrcTtf[i][1];
		stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[i][0].pData), 1000);
		memset_s(stSrcTtf[i][0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[i][0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[i][0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

        stSrcTtf[i][1].usUsed = 200;
        stSrcTtf[i][1].pData = pu8IPData[i] + stSrcTtf[i][0].usUsed;
        stSrcTtf[i][1].pNext = &stSrcTtf[i][2];

        stSrcTtf[i][2].usUsed = 100;
        stSrcTtf[i][2].pData = pu8IPData[i] + stSrcTtf[i][1].usUsed;
        stSrcTtf[i][2].pNext = &stSrcTtf[i][3];

        stSrcTtf[i][3].usUsed = 200;
        stSrcTtf[i][3].pData = pu8IPData[i] + stSrcTtf[i][2].usUsed;
        stSrcTtf[i][3].pNext = &stSrcTtf[i][4];

        stSrcTtf[i][4].usUsed = 300;
        stSrcTtf[i][4].pData = pu8IPData[i] + stSrcTtf[i][3].usUsed;
        stSrcTtf[i][4].pNext = NULL;

		osl_cache_flush(OSL_DATA_CACHE, pu8IPData[i], 1000);
	
        stDlPara[i].u32Data= (unsigned int)stSrcTtf[i];
        stDlPara[i].u16Attribute= 0x3b;		//只过滤
        stDlPara[i].u16UsrField1 = 200; 
        stDlPara[i].u16Len= 1000; 

    }
	
    mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error1;
    } 

    osl_task_delay(50);
    
error1:
    for(i = 0; i < 60; i++)
    {
        if(pu8IPData[i] != NULL)
        {
            osl_free((void *)pu8IPData[i]);
        }
    }
	
    return s32Ret;
}

int bsp_psam_st_007(void)
{
    unsigned int s32Ret;
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }
	/*起一个进程，不停地发东西*/
	osl_task_init("IpfDlTask1", 33, 0x1000, (OSL_TASK_FUNC) bsp_psam_dl_send, 0, &g_psamUlTaskId);
	return OK;
}
int bsp_psam_st_008(unsigned int sendtimes,unsigned int sendnum)
{
    unsigned int s32Ret;
    s32Ret = psam_st_dl_init();
    if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    psam_st_dl_init :%d\n",__LINE__);
        return ERROR;
    }
	/*起一个进程，不停地发东西*/
	osl_task_init("IpfDlTask1", 33, 0x1000, (OSL_TASK_FUNC) bsp_psam_dl_send_n2, 0, &g_psamUlTaskId);
	return OK;
}

#ifdef CONFIG_MODULE_BUSSTRESS
/*ipf dl stress test*/

#ifndef CONFIG_MODULE_BUSSTRESS
typedef enum tagTestModule
{
	GMAC = 0,
	ACC = 1,
	CIPHER = 2,
	KDF =3,
	DMA_DSP =4,
	EDMAC = 5,
	IPF_UL = 6,
	IPF_DL = 7,
	LCD = 8
}TestModule;
typedef enum tagTestSwitch
{
	TEST_STOP = 0,
	TEST_RUN =1
}TestSwitch;

static int get_test_switch_stat(int module_id)
{
	return 1;
}

static int set_test_switch_stat(int module_id, int run_or_stop)
{
	return 0;
}
#endif

static void timer_event(unsigned int parm)
{
	osl_sem_up(&bus_stress_tsk_sem);
	bsp_softtimer_add(&stress_tsk_timer_id);
}


unsigned int psam_dl_stress_test_task_id = 0;

int psam_dl_stress_test_routine(void)
{
	int ret = OK;
	IPF_CONFIG_DLPARAM_S stDlPara[PSAM_DLBD_DESC_SIZE];
    int s32Ret = 0;
    unsigned int i = 0;
    unsigned int SendNum = 20;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    unsigned int u32Len = 100;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
	
    pu8IPData = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData == NULL)
    {
        IPF_PRINT("malloc failed!\n");
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT("malloc failed!");
		ret = ERROR;
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData2 == NULL)
    {
        IPF_PRINT("malloc failed!\n");
		ret = ERROR;
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData3 == NULL)
    {
        IPF_PRINT("malloc failed!\n");
		ret = ERROR;
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_malloc(u32Len);
    if(pu8IPData4 == NULL)
    {
        IPF_PRINT("malloc failed!\n");
		ret = ERROR;
        goto error1;
    }

	stSrcTtf[0].usUsed = u32Len;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)(stSrcTtf[0].pData), u32Len*5);
	memset_s(stSrcTtf[0].pData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), C_NON_STRAIGHT_P_V, stSrcTtf[0].usUsed - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[0].pData, u32Len);

    stSrcTtf[1].usUsed = u32Len;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];
	memset_s(stSrcTtf[1].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[1].pData, u32Len);

    stSrcTtf[2].usUsed = u32Len;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];
	memset_s(stSrcTtf[2].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[2].pData, u32Len);

    stSrcTtf[3].usUsed = u32Len;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];
	memset_s(stSrcTtf[3].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[3].pData, u32Len);

    stSrcTtf[4].usUsed = u32Len;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	memset_s(stSrcTtf[4].pData, u32Len, 0x0, u32Len);
	osl_cache_flush(OSL_DATA_CACHE, stSrcTtf[4].pData, u32Len);

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));

    while(get_test_switch_stat(IPF_DL))
    {
    	osl_sem_down(&bus_stress_tsk_sem);
		u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
		if(u32BDNum > SendNum)
		{
			for(i=0;i < PSAM_DLBD_DESC_SIZE;i++)
			{
			    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
			    stDlPara[i].u16UsrField1= 200;
			    stDlPara[i].u16Len= u32Len*5;
			    stDlPara[i].u16Attribute= 0x28;/*设中断，仅搬移*/ 
			}	
			stDlPara[SendNum-1].u16Attribute= 0x29; 

			s32Ret = mdrv_ipf_config_dlbd(SendNum, stDlPara);
			if(s32Ret != IPF_SUCCESS)    
			{
				IPF_PRINT(" TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
				ret = ERROR;
				goto error0;
			} 
		}
		osl_task_delay(10);
    }
	
error0:
    osl_free((void *)pu8IPData4);
error1:
    osl_free((void *)pu8IPData3);
error2:
    osl_free((void *)pu8IPData2);
error3:
    osl_free((void *)pu8IPData1);
error4:
    osl_free((void *)pu8IPData);

    return ret;
}

int psam_dl_stress_test_start(int task_priority,unsigned int dtime)
{
	int s32Ret = 0;

	stress_tsk_timer_id.func      = timer_event;
	stress_tsk_timer_id.para      = 0;
	stress_tsk_timer_id.timeout   = dtime;
	stress_tsk_timer_id.wake_type = SOFTTIMER_WAKE;

	set_test_switch_stat(IPF_DL,TEST_RUN);

	osl_sem_init(SEM_EMPTY, &bus_stress_tsk_sem);
	
	s32Ret = psam_st_dl_init();
	
	if(s32Ret != OK)
    {
        IPF_PRINT(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&stress_tsk_timer_id))
	{
		IPF_PRINT("bus test soft timer create fail.\n");
		return -1;
	}

	osl_task_init("psam_dl_stress", task_priority, 0x1000, (OSL_TASK_FUNC)psam_dl_stress_test_routine, NULL, &psam_dl_stress_test_task_id);
	if(psam_dl_stress_test_task_id == IPF_ERROR)
	{
		IPF_PRINT("task psam dl stress create task fail.\n");
		return -1;
	} 

	bsp_softtimer_add(&stress_tsk_timer_id);
    return OK;
}
int psam_dl_stress_test_stop()
{
	set_test_switch_stat(IPF_DL,TEST_STOP);
	while(BSP_OK == osl_task_check(psam_dl_stress_test_task_id))
	{
	    osl_task_delay(10);
	}	

	osl_sema_delete(&bus_stress_tsk_sem);
	if(stress_tsk_timer_id.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&stress_tsk_timer_id);
		bsp_softtimer_free(&stress_tsk_timer_id);
	}
	
	return OK;
}
#endif

#ifdef __cplusplus
}
#endif
