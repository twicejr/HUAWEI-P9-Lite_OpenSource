#ifndef __MDRV_CCORE_CIPHER_H__
#define __MDRV_CCORE_CIPHER_H__
#ifdef __cplusplus
extern "C"
{
#endif


/* 错误码 */
#define CIPHER_SUCCESS                  0

#define CHN_BUSY                    0
#define CHN_FREE                    1

typedef enum tagCIPHER_ALGORITHM_E
{
    CIPHER_ALG_NULL = 0,        /* 无算法 */
    CIPHER_ALG_SNOW3G  = 1,     /* SNOW3G算法 */
    CIPHER_ALG_AES_128 = 2,     /* AES128算法 */
    CIPHER_ALG_AES_192 = 3,     /* AES192算法 */
    CIPHER_ALG_AES_256 = 4,     /* AES256算法 */
    CIPHER_ALG_ZUC = 5,	        /* ZUC算法 */
    CIPHER_ALG_BUTTOM,
}CIPHER_ALGORITHM_E;


typedef enum tagKDF_SHA_KEY_SOURCE_E
{
    SHA_KEY_SOURCE_DDR,             /*sha_key来源于input point指定的地址空间 */
    SHA_KEY_SOURCE_KEYRAM,       /*  sha_key来源于内部KeyRam */
    SHA_KEY_SOURCE_FOLLOW,       /*  sha_key来源于上次KDF操作的sha_key */ 
    SHA_KEY_SOURCE_RESULT,        /*  sha_key来源于上一次KDF操作的结果*/
    SHA_KEY_SOURCE_MAX
}KDF_SHA_KEY_SOURCE_E;

typedef enum tagKDF_SHA_S_SOURCE_E
{
    SHA_S_SOURCE_DDR,              /*  sha_s来源于input point指定的地址空间*/
    SHA_S_SOURCE_KEYRAM,        /*  sha_s来源于内部KeyRam */
    SHA_S_SOURCE_MAX
}KDF_SHA_S_SOURCE_E;

enum CIPHER_SECURITY_CHANNEL_ENUM
{
    CIPHER_SECURITY_CHANNEL_0            = 0,                /*通道0*/
    CIPHER_SECURITY_CHANNEL_1            = 1,                /*通道1*/
    CIPHER_SECURITY_CHANNEL_2            = 2,                /*通道2*/
    CIPHER_SECURITY_CHANNEL_3            = 3,                /*通道3*/
    CIPHER_SECURITY_CHANNEL_4            = 4,                /*通道4*/
    CIPHER_SECURITY_CHANNEL_5            = 5,                /*通道5*/
    CIPHER_SECURITY_CHANNEL_6            = 6,                /*通道5*/

    CIPHER_SECURITY_CHANNEL_BUTT
};

/* 通道号*/
#define LTE_SECURITY_CHANNEL_NAS          CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_RRC          CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_UL_SRB       CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_SRB       CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_DRB_CCORE CIPHER_SECURITY_CHANNEL_3 /* 非直通 */
#define LTE_SECURITY_CHANNEL_DL_DRB_ACORE CIPHER_SECURITY_CHANNEL_5 /* 直通 */
#define LTE_SECURITY_CHANNEL_UL_ACC_0     CIPHER_SECURITY_CHANNEL_0
#define LTE_SECURITY_CHANNEL_UL_ACC_1     CIPHER_SECURITY_CHANNEL_6

typedef enum tagCIPHER_SINGLE_OPT_E
{
    CIPHER_OPT_ENCRYPT = 0x0,
    CIPHER_OPT_DECRYPT = 0x1,
    CIPHER_OPT_PROTECT_SMAC = 0x2,
    CIPHER_OPT_PROTECT_LMAC = 0x3,
    CIPHER_OPT_CHECK_PRE_SMAC  = 0x4,
    CIPHER_OPT_CHECK_POST_SMAC = 0x5,
    CIPHER_OPT_CHECK_PRE_LMAC  = 0x6,
    CIPHER_OPT_CHECK_POST_LMAC = 0x7,
    CIPHER_SINGLE_OPT_BUTTOM
}CIPHER_SINGLE_OPT_E;

typedef enum tagCIPHER_RELA_OPT_E
{
    CIPHER_PDCP_PRTCT_ENCY,
    CIPHER_PDCP_DECY_CHCK,
    CIPHER_NAS_ENCY_PRTCT,
    CIPHER_NAS_CHCK_DECY,
    CIPHER_RELA_OPT_BUTTOM

}CIPHER_RELA_OPT_E;


typedef enum tagCIPHER_KEY_LEN_E
{
    CIPHER_KEY_L128 = 0,        /* 密钥长度128 bit */
    CIPHER_KEY_L192 = 1,        /* 密钥长度192 bit */
    CIPHER_KEY_L256 = 2,        /* 密钥长度256 bit */
    CIPHER_KEY_LEN_BUTTOM
}CIPHER_KEY_LEN_E;

typedef enum tagCIPHER_SUBMIT_TYPE_E
{
    CIPHER_SUBM_NONE = 0,           /* 不作任何通知 */
    CIPHER_SUBM_BLK_HOLD = 1,       /* 循环查询等待完成 */
    CIPHER_SUBM_CALLBACK = 2,       /* 回调函数通知 */
    CIPHER_SUBM_BUTTOM
}CIPHER_SUBMIT_TYPE_E;

typedef enum tagCIPHER_NOTIFY_STAT_E
{
    CIPHER_STAT_OK = 0,           /* 成功完成 */
    CIPHER_STAT_CHECK_ERR = 1,    /* 完整性检查错误 */
    CIPHER_STAT_BUTTOM
}CIPHER_NOTIFY_STAT_E;


typedef enum tagCIPHER_HDR_E
{
    CIPHER_HDR_BIT_TYPE_0              = 0,     /*对应的头或附加头字节长度为0，即不启动此功能*/
    CIPHER_HDR_BIT_TYPE_5              = 1,     /*对应的头或附加头字节长度为1，即启动此功能，对应附加头的内容是Count值的低5位，参与保护*/
    CIPHER_HDR_BIT_TYPE_7              = 2,     /*对应的头或附加头字节长度为1，即启动此功能，对应附加头的内容是Count值的低7位，参与保护*/
    CIPHER_HDR_BIT_TYPE_12             = 3,     /*对应的头或附加头字节长度为2，即启动此功能，对应附加头的内容是Count值的低12位，参与保护*/
    CIPHER_APPEND_HDR_BIT_TYPE_5       = 4,     /*对应的头或附加头字节长度为1，即启动此功能，对应附加头的内容是Count值的低5位，不参与保护，只搬移*/
    CIPHER_APPEND_HDR_BIT_TYPE_7       = 5,     /*对应的头或附加头字节长度为1，即启动此功能，对应附加头的内容是Count值的低7位，不参与保护，只搬移*/
    CIPHER_APPEND_HDR_BIT_TYPE_12      = 6,     /*对应的头或附加头字节长度为2，即启动此功能，对应附加头的内容是Count值的低12位，不参与保护，只搬移*/
    CIPHER_HDR_BIT_TYPE_BUTT
}CIPHER_HDR_E;

typedef enum tagCIPHER_KEY_OUTPUT_E
{
    CIPHER_KEY_NOT_OUTPUT,    /*不输出密钥*/
    CIPHER_KEY_OUTPUT,        /*输出密钥*/
    CIPHER_KEY_OUTPUT_BUTTOM
}CIPHER_KEY_OUTPUT_E;

typedef unsigned int CIPHER_KEY_LEN_E_U32;
typedef unsigned int CIPHER_KEY_OUTPUT_E_U32;

typedef struct tagCIPHER_ALGKEY_INFO_S
{
    unsigned int u32KeyIndexSec;
    unsigned int u32KeyIndexInt;
    CIPHER_ALGORITHM_E enAlgSecurity;          /* 安全操作算法选择，AEC算法还是SNOW3G算法 */
    CIPHER_ALGORITHM_E enAlgIntegrity;         /* 完整性操作算法选择，AEC算法还是SNOW3G算法 */
}CIPHER_ALGKEY_INFO_S;

typedef struct tagACC_SINGLE_CFG_S
{
    unsigned int u32BearId;
    unsigned int u32AppdHeaderLen;
    unsigned int u32HeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* 是否是单内存块 */
    unsigned int u32BlockLen;                /* 如果是单块内存，需要知道长度*/
    unsigned int u32Offset;                  /* 使用数据距离数据包起始地址偏移*/
    unsigned int u32OutLen;                  /* 使用到的数据长度*/
    unsigned int u32Aph;                      /*附加包头域*/
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* 单独操作的算法密钥配置信息 */
    void* pInMemMgr;
    void* pOutMemMgr;
} ACC_SINGLE_CFG_S;


typedef struct tagCIPHER_RELA_CFG_S
{
    CIPHER_RELA_OPT_E enOpt;          /* 操作类型(纯DMA操作忽略下面的算法配置) */
    unsigned char u8BearId;
    unsigned char u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* 是否是单内存块，不是为０，是为其他数 */
    unsigned int u32BlockLen;                /* 如果是单块内存，需要知道长度*/
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* 单独操作的算法密钥配置信息 */
    void* pInMemMgr ;
    void* pOutMemMgr ;
    CIPHER_SUBMIT_TYPE_E enSubmAttr;
    unsigned int u32Private;
} CIPHER_RELA_CFG_S;

typedef struct tagCIPHER_SINGLE_CFG_S
{
    CIPHER_SINGLE_OPT_E enOpt;       /* 操作类型(纯DMA操作忽略下面的算法配置) */
    unsigned char u8BearId;
    unsigned char u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* 是否是单内存块，不是为０，是为其他数 */
    unsigned int u32BlockLen;                /* 如果是单块内存，需要知道长度*/ 
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* 单独操作的算法密钥配置信息 */
    void* pInMemMgr ;
    void* pOutMemMgr ;
    CIPHER_SUBMIT_TYPE_E enSubmAttr;
    unsigned int u32Private;
	unsigned int usr_field1;
	unsigned int usr_field2;
	unsigned int usr_field3;
} CIPHER_SINGLE_CFG_S;


typedef struct tagS_CONFIG_INFO_S
{
    KDF_SHA_S_SOURCE_E   enShaSSource;      /* sha_s来源*/
    unsigned int              u32ShaSIndex;                /* sha_s来源于KeyRam时，其在keyRam中的索引*/
    unsigned int              u32ShaSLength;              /* sha_s的长度*/
    void             *pSAddr;           
}S_CONFIG_INFO_S;


typedef struct
{
    CIPHER_KEY_LEN_E    enKeyLen; /* 要读取的Key的长度，由上层传入*/
    void                *pKeyAddr; /*Key值存放地址 */
    CIPHER_KEY_LEN_E    *penOutKeyLen;/*该地址用于存放实际返回的Key的长度*/
}KEY_GET_S;


typedef struct
{
    CIPHER_KEY_OUTPUT_E  enKeyOutput; /*指示是否输出Key到stKeyGet中*/
    KEY_GET_S stKeyGet;
}KEY_MAKE_S;


typedef struct tagKEY_CONFIG_INFO_S
{
    KDF_SHA_KEY_SOURCE_E enShaKeySource;    /* sha_key来源*/
    unsigned int              u32ShaKeyIndex;       /* sha_key来源于KeyRam时，其在keyRam中的索引 */
    void             *pKeySourceAddr;   /* */
}KEY_CONFIG_INFO_S;


typedef enum tagBD_TYPE_E
{
	BD_TYPE_FREE,
	BD_TYPE_CFG,	
	BD_TYPE_TOTAL
}BD_TYPE_E;



typedef struct tagCIPHER_RD_INFO_STRU
{
	CIPHER_NOTIFY_STAT_E enstat;
	unsigned int  usr_field1;
	unsigned int  usr_field2;
	unsigned int  usr_field3;
}CIPHER_RD_INFO_S;

/*****************************************************************************
* 函 数 名  : mdrv_acc_dma
*
* 功能描述  : 纯DMA方式组包加速
*
* 输入参数  : unsigned int u32BdFifoAddr  ACC工作FIFO首地址
*             		pstCfg   ACC配置信息
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_acc_dma (unsigned int u32BdFifoAddr, ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* 函 数 名  : mdrv_acc_cipher
*
* 功能描述  : 带有加解密功能的组包加速
*
* 输入参数  : unsigned int u32BdFifoAddr
*             const void* pInMemMgr
*             const void* pOutMemMgr
*             ACC_SINGLE_CFG_S *pstCfg
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_acc_cipher(unsigned int u32BdFifoAddr, ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* 函 数 名  : mdrv_acc_get_bdq_addr
*
* 功能描述  : 获取可用BDQ队列首地址
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 0，失败；其他，有效地址值；
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_acc_get_bdq_addr(void);

/*****************************************************************************
* 函 数 名  : mdrv_acc_get_status
*
* 功能描述  : 获取当前ACC通道状态
*
* 输入参数  : Chn  通道号
* 输出参数  :
*
* 返 回 值  : 0，通道忙；1，通道空闲
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_acc_get_status(unsigned int chn);

/*****************************************************************************
* 函 数 名  : mdrv_acc_enable
*
* 功能描述  : 设置BDQ首地址到寄存器，并使能ACC
*
* 输入参数  :chn   通道号
				unsigned int u32BdFifoAddr  FIFO工作队列首地址
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_acc_enable(unsigned int chn, unsigned int u32BdFifoAddr);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_register_memfree_cb
*
* 功能描述  : 注册上层内存释放函数
*
* 输入参数  : unsigned int u32Chn 通道号
*             int bSrc  0:输入Buffer / 1:输出Bufffer
*             CIPHER_FREEMEM_CB_T pFunFreeMemCb
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
/* Memory释放回调函数*/
typedef void (*CIPHER_FREEMEM_CB_T)(void* pMemAddr);
int mdrv_cipher_register_memfree_cb(unsigned int u32Chn, int bSrc, CIPHER_FREEMEM_CB_T pFunFreeMemCb);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_register_notify_cb
*
* 功能描述  : 注册上层通知回调函数
*
* 输入参数  : CIPHER_NOTIFY_CB_T pFunNotifyCb
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
/* 通知回调函数指针类型*/
typedef void (*CIPHER_NOTIFY_CB_T)(unsigned int u32ChNum, unsigned int u32SourAddr,unsigned int u32DestAddr, CIPHER_NOTIFY_STAT_E enStatus, unsigned int u32Private);

int mdrv_cipher_register_notify_cb(CIPHER_NOTIFY_CB_T pFunNotifyCb);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_purge_chan
*
* 功能描述  : 清空指定通道
*
* 输入参数  : unsigned int u32Chn
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*       1.该接口不能在中断上下文中调用。多任务安全，内部有互斥操作。【除3号通道】
*       2.该接口会循环等待指定通道空闲，然后复位通道。
*
*****************************************************************************/
int mdrv_cipher_purge_chan(unsigned int u32Chn);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_single_submit_task
*
* 功能描述  : 单独操作提交
*
* 输入参数  : unsigned int u32Chn               通道号
*                          	 CIPHER_SINGLE_CFG_S   pstCfg   单独操作配置信息
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_single_submit_task(unsigned int u32Chn, CIPHER_SINGLE_CFG_S *pstCfg);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_rela_submit_task
*
* 功能描述  : 关联操作提交
*
* 输入参数  : unsigned int u32Chn               通道号
*                          	 CIPHER_RELA_CFG_S   pstCfg    关联操作配置信息
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_rela_submit_task(unsigned int u32Chn, CIPHER_RELA_CFG_S * pstCfg);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_set_key
*
* 功能描述  : 设置key到指定的索引号位置
*
* 输入参数  : const void* pKeyAddr  源数据首地址
*             CIPHER_KEY_LEN_E enKeyLen Key长度
*             unsigned int u32KeyIndex       目的索引位置
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_set_key(const void* pKeyAddr,CIPHER_KEY_LEN_E enKeyLen,unsigned int u32KeyIndex);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_get_key
*
* 功能描述  : 获取指定索引位置的Key
*
* 输入参数  : unsigned int u32KeyIndex   索引号
*             KEY_GET_S *pstKeyGet  期望的key长度、接受key的内存地址
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_get_key(unsigned int u32KeyIndex, KEY_GET_S *pstKeyGet);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_set_dbuf_para
*
* 功能描述  : 设置源数据格式信息
*
* 输入参数  : unsigned int u32Chn      通道号
*             int bSrc       TRUE,源地址的属性配置;FALSE,目的地址属性配置
*             unsigned int u32BufOft   数据buffer指针偏移
*             unsigned int u32LenOft   Buffer长度偏移
*             unsigned int u32NextOft  下一节点偏移
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_set_dbuf_para(unsigned int u32Chn, int bSrc, unsigned int u32BufOft,unsigned int u32LenOft, unsigned int u32NextOft);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_get_cmplt_data
*
* 功能描述  : 获取已完成的数据
*
* 输入参数  : unsigned int u32Chn                   通道号
*             unsigned int *pu32SourAddr            源地址
*             unsigned int *pu32DestAddr            目的地址
*             CIPHER_NOTIFY_STAT_E *penStatus  状态
*             unsigned int *pu32Private             返回的私有数据
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_get_cmplt_data(unsigned int u32Chn, unsigned int *pu32SourAddr,unsigned int *pu32DestAddr, CIPHER_NOTIFY_STAT_E *penStatus, unsigned int *pu32Private);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_read_key
*
* 功能描述  : 读取key
*
* 输入参数  : pDestAddr    读取key后存放的地址
*             		 u32KeyIndex       要读取key的索引
*             		u32ReadLength     要读取key的长度

* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_read_key (void *pDestAddr, unsigned int u32KeyIndex ,unsigned int u32ReadLength);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_write_key
*
* 功能描述  : 将key写入keyram中
*
* 输入参数  : u32KeyIndex    Key写入keyram中的索引
*             		 pSourAddr        Key在内存中地址
*             		u32Length         key长度

* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_write_key(unsigned int u32KeyIndex, void *pSourAddr, unsigned int u32Length);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_gen_key
*
* 功能描述  : 生成新的key
*
* 输入参数  : KEY_CONFIG_INFO_S *pstKeyCfgInfo  KDF运算时参数sha_key属性配置信息
*             S_CONFIG_INFO_S *pstSCfgInfo      KDF运算时参数sha_s属性配置
*             unsigned int u32DestIndex              KDF运算产生的Key放置在KeyRam中的位置
*             KEY_MAKE_S *pstKeyMake            用于指示生成的KEY是否输出，输出时接受的地址
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*            1 u32DestIndex的取值范围在[0~15]
*            2 该接口不能在中断上下文中调用。多任务安全，内部有互斥操作
*
*****************************************************************************/
int mdrv_cipher_gen_key(KEY_CONFIG_INFO_S *pstKeyCfgInfo, S_CONFIG_INFO_S *pstSCfgInfo,unsigned int u32DestIndex, KEY_MAKE_S *pstKeyMake);



/*****************************************************************************
* 函 数 名  : mdrv_cipher_enable
*
* 功能描述  : Cipher开钟
*
* 输入参数  : 无

* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_enable(void);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_disable
*
* 功能描述  : Cipher关钟
*
* 输入参数  : unsigned int timeout  关闭Cipher时钟的超时时间，单位为ms，推荐10ms
*                                   数值范围:0 < timeout < 100                            
*
* 输出参数  : 无
*
* 返 回 值  : 0         成功关闭时钟
*             其他值    时钟关闭失败       
*
* 其它说明  :驱动检查硬件是否准备好被关闭，如果是，则关闭Cipher时钟;否则循环查询
*          Cipher状态。如果循环查询的时间超过超时时间，则放弃关闭时钟,返回错误值。
*
*****************************************************************************/
int  mdrv_cipher_disable(unsigned int timeout);

/*****************************************************************************
* 函 数 名  : mdrv_cipher_get_rdinfo
*
* 功能描述  : Cipher批量获取RD信息
*
* 输入参数  : u32Chn  通道号
				 pstRd RD信息结构体
				 pstRdNum   获取到的RD个数
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_get_rdinfo(unsigned int u32Chn, CIPHER_RD_INFO_S * pstRd, unsigned int* pstRdNum);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_set_bdinfo
*
* 功能描述  : Cipher批量设置BD信息
*
* 输入参数  : u32Chn  通道号
				 num  pstCfg数组长度
				 pstCfg  BD配置信息
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_set_bdinfo(unsigned int u32Chn, unsigned int num, CIPHER_SINGLE_CFG_S *pstCfg);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_get_bd_num
*
* 功能描述  : Cipher批量设置BD信息
*
* 输入参数  : u32Chn  通道号
				 bd_type  Bd类型
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_get_bd_num(unsigned int u32Chn, BD_TYPE_E  bd_type);


/*****************************************************************************
* 函 数 名  : mdrv_cipher_get_chn_status
*
* 功能描述  : 获取Cipher 特定通道状态
*
* 输入参数  : chn_id  通道号

* 输出参数  :
*
* 返 回 值  : CIPHER_CHN_STATUS_E枚举类型或者错误代码。
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_cipher_get_chn_status(unsigned int chn_id);


typedef enum tagCIPHER_CHN_STATUS_E
{
	CIPHER_CHN_BDEMPTY_RDEMPTY,	//BD queue and  RD queue are empty , the channel is idle.
	CIPHER_CHN_BDINUSE_RDEMPTY,	//BD queue in using, RD queue is empty, the channel in using.
	CIPHER_CHN_BDEMPTY_RDINUSE,	//BD queue is empty, RD queue in using , the channel in using.
	CIPHER_CHN_BDINUSE_RDINUSE	//Either BD queue and RD queue in using, the channel in using. 
} CIPHER_CHN_STATUS_E;

/* 注意CIPHER错误码要为负值 */
#define CIPHER_ERROR_BASE               0x80000800

typedef enum tagCIPHER_ERR_CODE_E
{
    CIPHER_ERR_CODE_NULL_PTR = 1,
    CIPHER_ERR_CODE_NO_MEM ,
    CIPHER_ERR_CODE_NOT_INIT ,
    CIPHER_ERR_CODE_FIFO_FULL ,
    CIPHER_ERR_CODE_INVALID_CHN ,
    CIPHER_ERR_CODE_INVALID_OPT ,
    CIPHER_ERR_CODE_ALIGN_ERROR ,
    CIPHER_ERR_CODE_PURGING ,
    CIPHER_ERR_CODE_TIME_OUT,
    CIPHER_ERR_CODE_INVALID_ENUM,
    CIPHER_ERR_CODE_INVALID_RD,
    CIPHER_ERR_CODE_RD_NULL,
    CIPHER_ERR_CODE_INVALID_KEY,
    CIPHER_ERR_CODE_CHECK_ERROR,
    CIPHER_ERR_CODE_BDLEN_ERROR,
    CIPHER_ERR_CODE_INVALID_NUM,
    CIPHER_ERR_CODE_NO_KEY,
    CIPHER_ERR_CODE_KEYLEN_ERROR,
    ACC_FIFOS_WORK,
    CIPHER_ENABLE_FAIL
}CIPHER_ERR_CODE_E;

#define CIPHER_NULL_PTR      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NULL_PTR))
#define CIPHER_NO_MEM        ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_MEM))
#define CIPHER_NOT_INIT      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NOT_INIT))
#define CIPHER_FIFO_FULL     ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_FIFO_FULL))
#define CIPHER_INVALID_CHN   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_CHN))
#define CIPHER_INVALID_OPT   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_OPT))
#define CIPHER_ALIGN_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_ALIGN_ERROR))
#define CIPHER_PURGING       ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_PURGING))
#define CIPHER_TIME_OUT      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_TIME_OUT))
#define CIPHER_INVALID_ENUM  ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_ENUM))
#define CIPHER_INVALID_RD    ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_RD))
#define CIPHER_RDQ_NULL      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_RD_NULL))
#define CIPHER_INVALID_KEY   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_KEY))
#define CIPHER_CHECK_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_CHECK_ERROR))
#define CIPHER_BDLEN_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_BDLEN_ERROR))
#define CIPHER_INVALID_NUM   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_NUM))
#define CIPHER_NO_KEY        ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_KEY))
#define CIPHER_KEYLEN_ERROR  ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_KEYLEN_ERROR))
#define ACC_ALL_FIFO_WORK    ((int)(CIPHER_ERROR_BASE|ACC_FIFOS_WORK))
#define CIPHER_ENABLE_FAILED ((int)(CIPHER_ERROR_BASE|CIPHER_ENABLE_FAIL))
#define CIPHER_UNKNOWN_ERROR ((int)(CIPHER_ERROR_BASE|0xff))


#ifdef __cplusplus
}
#endif
#endif
