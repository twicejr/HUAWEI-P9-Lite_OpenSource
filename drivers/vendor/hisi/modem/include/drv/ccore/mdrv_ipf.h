#ifndef __MDRV_CCORE_IPF_H__
#define __MDRV_CCORE_IPF_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_ipf_comm.h"


typedef int (*BSP_IPF_WakeupUlCb)(void);
typedef int (*BSP_IPF_AdqEmptyUlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);

/* BURST最大长度 */
typedef enum tagIPF_BURST_E
{
    IPF_BURST_16,           /* BURST16 */
    IPF_BURST_8,            /* BURST8 */
    IPF_BURST_4,            /* BURST4 */
    IPF_BURST_MAX,          /* BURST4 跟寄存器一致 */
}IPF_BURST_E;

typedef struct tagIPF_COMMON_PARA_S
{
    int bAdReport;
    int bMultiModeEn;
    int bMultiFilterChainEn;
	int bEspSpiDisable;
	int bAhSpiDisable;
	int bEspAhSel;
    int bIpv6NextHdSel;
    IPF_BURST_E eMaxBurst;
    int bSpWrrModeSel;
    int bSpPriSel;
    int bFltAddrReverse;
    int bFilterSeq;
} IPF_COMMON_PARA_S;

/* 通道控制结构体 */
typedef struct tagIPF_CHL_CTRL_S
{
	int bDataChain;
	int bEndian;
	IPF_MODE_E eIpfMode;
    unsigned int u32WrrValue;
} IPF_CHL_CTRL_S;

typedef struct tagIPF_MATCH_INFO_S{
    unsigned char u8SrcAddr[16];
    unsigned char u8DstAddr[16];
    unsigned char u8DstMsk[16];
    union{
        struct{
        	unsigned int u16SrcPortLo:16;
        	unsigned int u16SrcPortHi:16;
        }Bits;
	    unsigned int u32SrcPort;
    } unSrcPort;
    union{
        struct
        {
            unsigned int u16DstPortLo:16;
        	unsigned int u16DstPortHi:16;
        }Bits;
    	unsigned int u32DstPort;
    } unDstPort;
    union{
        struct
        {
            unsigned int u8TrafficClass:8;
        	unsigned int u8TrafficClassMask:8;
        	unsigned int u16Reserve:16;
        }Bits;
    	unsigned int u32TrafficClass;
    }unTrafficClass;
    unsigned int u32LocalAddressMsk;
    union{
    	unsigned int u32NextHeader;
    	unsigned int u32Protocol;
    }unNextHeader;
    unsigned int u32FlowLable;
    union{
        struct{
            unsigned int u16Type:16;
        	unsigned int u16Code:16;
        }Bits;
    	unsigned int u32CodeType;
    } unFltCodeType;
    union{
        struct{
            unsigned int u16NextIndex:16;
        	unsigned int u16FltPri:16;
        }Bits;
    	unsigned int u32FltChain;
    } unFltChain;
    unsigned int u32FltSpi;
    union{
    	struct{
    		unsigned int FltEn:1;
    		unsigned int FltType:1;
    		unsigned int Resv1:2;
            unsigned int FltSpiEn:1;
            unsigned int FltCodeEn:1;
            unsigned int FltTypeEn:1;
            unsigned int FltFlEn:1;
            unsigned int FltNhEn:1;
            unsigned int FltTosEn:1;
            unsigned int FltRPortEn:1;
            unsigned int FltLPortEn:1;
            unsigned int FltRAddrEn:1;
            unsigned int FltLAddrEn:1;
            unsigned int Resv2:2;
            unsigned int FltBid:6;
            unsigned int Resv3:10;
    	}Bits;
    	unsigned int u32FltRuleCtrl;
    }unFltRuleCtrl;
}IPF_MATCH_INFO_S;

typedef struct tagIPF_FILTER_CONFIG_S
{
    unsigned int u32FilterID;
    IPF_MATCH_INFO_S stMatchInfo;
} IPF_FILTER_CONFIG_S;


/*****************************************************************************
* 函 数 名  : mdrv_ipf_init
*
* 功能描述  : 配置IPF硬件公共参数
*
* 输入参数  : IPF_COMMON_PARA_S *pstCommPara  公共参数结构体指针
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*             IPF_NOT_INITIALIZED IPF模块未初始化
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_init(IPF_COMMON_PARA_S *pstCommPara);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_ulchan
*
* 功能描述  : 配置IPF上行通道控制寄存器参数
*
* 输入参数  : IPF_CHL_CTRL_S *pstCtrl 通道控制寄存器配置参数
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_ulchan(IPF_CHL_CTRL_S *pstCtrl);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_dlchan
*
* 功能描述  : 配置IPF下行通道控制寄存器参数
*
* 输入参数  : IPF_CHL_CTRL_S *pstCtrl 通道控制寄存器配置参数
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_dlchan (IPF_CHL_CTRL_S *pstCtrl);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_set_filter
*
* 功能描述  : 配置IP过滤器
*
* 输入参数  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead 被配置的寄存器链首地址
*             IPF_FILTER_CONFIG_S *pstFilterInfo       Filter配置结构体指针
*             unsigned int u32FilterNum                     Filter个数
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*             IPF_NOT_INITIALIZED IPF模块未初始化
*             IPF_FILTER_NOT_ENOUGH IPF过滤器数目不够
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_set_filter (IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, IPF_FILTER_CONFIG_S *pstFilterInfo, unsigned int u32FilterNum);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_filter
*
* 功能描述  : 查询Filter配置
*
* 输入参数  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead  寄存器链首地址
*             unsigned int u32FilterID                       Filter ID号
*             IPF_FILTER_CONFIG_S *pstFilterInfo        Filter信息结构体指针
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*             IPF_NOT_INITIALIZED IPF模块未初始化
*             IPF_ERROR 没有查到Filter ID对应的过滤规则
* 其它说明  : 此接口只支持查询单个Filter配置值。u32FilterID指PS设置过滤规则时使用的ID号，与硬件寄存器的ID号一一对应，但是不一定相等，由软件维护其对应关系
*
*****************************************************************************/
int mdrv_ipf_get_filter (IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_timeout
*
* 功能描述  : 配置IPF通道超时处理
*
* 输入参数  : unsigned int u32Timeout  待配置的中断超时时间，单位是256个时钟周期，填65约为0.1ms，填648约为1ms
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
* 其它说明  : 输入参数的范围是1~ 0xffff，该设置对上下行通道同时生效
*
*****************************************************************************/
int mdrv_ipf_config_timeout(unsigned int u32Timeout);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_dlbd
*
* 功能描述  : 配置下行数据包
*
* 输入参数  : unsigned int u32Num  需要配置的BD数目
*             IPF_CONFIG_DLPARA_S* pstDlPara 配置参数结构体数组指针
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_ERROR 配置失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_enable_chan
*
* 功能描述  : 使能或复位IP过滤器上下行通道
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChanType 上下行通道标识
*             int bFlag 使能复位标识。BSP_TRUE：使能；BSP_FALSE：复位
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_ERROR 配置失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_enable_chan (IPF_CHANNEL_TYPE_E eChanType, int bFlag);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlbd_num
*
* 功能描述  : 获取下行可以配置的BD和CD的数目
*
* 输入参数  : unsigned int* pu32CDNum  返回的可以配置的CD的数目
* 输出参数  :
*
* 返 回 值  : 下行空闲的BD数目范围为0 ~ BD_DESC_SIZE，空闲CD数目范围为0~1023
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_dlbd_num (unsigned int* pu32CDNum);
/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlbd_max_num
*
* 功能描述  : 获取下行可以配置的bd的最大个数
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 下行可以配置的bd的最大个数,ipf N, psam N-1
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_dlbd_max_num(void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_ulrd
*
* 功能描述  : 获取上行RD
*
* 输入参数  : unsigned int* pu32Num  输入可以返回的最多的RD数目/输出实际返回的RD数目
*             IPF_RD_DESC_S *pstRd  RD描述符结构体首地址
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_ipf_get_ulrd (unsigned int* pu32Num, IPF_RD_DESC_S *pstRd);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_adthred
*
* 功能描述  : 提供区分长短包的分界阀值
*
* 输入参数  : unsigned int u32UlADThr 上行通道长短包的分界阀值
              unsigned int u32DlADThr 下行通道长短包的分界阀值
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*             IPF_NOT_INITIALIZED IPF模块未初始化
*
* 其它说明  : 如果不调用该接口，AD队列的使用404、448为上下行通道的长短包阀值的默认值。
*
*****************************************************************************/
int mdrv_ipf_config_adthred (unsigned int u32UlADThr, unsigned int u32DlADThr);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_ulad
*
* 功能描述  : 给空闲的AD分配新的内存缓冲区
*
* 输入参数  : IPF_AD_TYPE_E eAdType   AD队列号，0（短包队列）或1（长包对列）
*             unsigned int u32AdNum    需要配置的的AD数目
*             IPF_AD_DESC_S *pstAdDesc 缓存空间对应的数据结构首地址
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_ulad(IPF_AD_TYPE_E eAdType, unsigned int u32AdNum, IPF_AD_DESC_S *pstAdDesc);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_ulad_num
*
* 功能描述  : 获取上行（C核）空闲（指向的缓冲区已经被使用）AD数目
*
* 输入参数  : unsigned int* pu32AD0Num  返回空闲的AD0的数目
*             unsigned int* pu32AD1Num  返回空闲的AD1的数目
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_get_ulad_num (unsigned int* pu32AD0Num,unsigned int* pu32AD1Num);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_set_pktlen
*
* 功能描述  : 设定过滤器包长的最大最小值
*
* 输入参数  : unsigned int u32MaxLen  数据包最大长度
*             unsigned int u32MinLen  数据包最小长度
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_set_pktlen (unsigned int u32MaxLen, unsigned int u32MinLen);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlstateidle
*
* 功能描述  : 下行通道是否为空闲
*
* 输入参数  :
* 输出参数  :
*
* 返 回 值  :IPF_SUCCESS 空闲
*            IPF_ERROR   非空闲
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_get_dlstateidle(void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_set_dbuf_para
*
* 功能描述  : 设置源数据格式信息
*
* 输入参数  : bufoffset pData成员偏移
*             lenoffset usUsed成员偏移
*             nextoffset pNext成员偏移
* 输出参数  :
*
* 返 回 值  : 0 正确
*             -1 错误
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_set_dbuf_para(unsigned int bufoffset,unsigned int lenoffset, unsigned int nextoffset);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_set_limit_addr
*
* 功能描述  : 设置数传时GU在ccore允许访问的地址
*
* 输入参数  : start GU在ccore允许访问的开始地址
			  end 	GU在ccore允许访问的开始地址
* 输出参数  :
*
* 返 回 值  : 0 正确
*             -1 错误
* 其它说明  : 
*
*****************************************************************************/
int mdrv_ipf_set_limited_addr(unsigned int start, unsigned int end);


#ifdef __cplusplus
}
#endif
#endif
