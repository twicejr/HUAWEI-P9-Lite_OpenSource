#ifndef __MDRV_CCORE_EDMA_H__
#define __MDRV_CCORE_EDMA_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*物理通道    逻辑通道号	    软件通道宏定义名称	    用途	    使用场景	    使用组件/核	使用人
                 0	        EDMA_CH_GUDSP_MEMORY_1	GUDSP M2M	用于turbo译码	GUDSP	lianpeng 00167020
            	 1	        EDMA_CH_GUDSP_MEMORY_2	GUDSP M2M	用于viterb译码	GUDSP	lianpeng 00167020
            	 2复用 	    EDMA_CH_GUDSP_MEMORY_3	GUDSP M2M	用于CQI表搬移	GUDSP	lianpeng 00167020
                 2复用      EDMA_CH_LDSP_LCS_SDR    每次启用前检查通道是否空闲  BBE16   honghuiyong
            	 3	        EDMA_CH_GUDSP_MEMORY_4	GUDSP M2M	用于上行编码	GUDSP	lianpeng 00167020
            	 4	        EDMA_CH_GUDSP_MEMORY_6	GUDSP M2M	用于APT表搬移	GUDSP	lianpeng 00167020
            	 5复用	    EDMA_CH_GUDSP_MEMORY_7	GUDSP M2M   GUDSP加载 要求北京底软做封装虚拟通道，GUDSP代码不可见"	GUDSP	lianpeng 00167020
            	 5复用	    EDMA_CH_GUDSP_MEMORY_8	GUDSP M2M   AHB邮箱加载复用，要求北京底软做封装虚拟通道，GUDSP代码不可见"	GUDSP	lianpeng 00167020
            	 6  	    EDMA_CH_GUDSP_MEMORY_9	GUDSP 搬运使用	BBP_GRIF_PHY，实现BBP搬数，用于校准复用GU BBP DEBUG采数功能"	GUDSP	lianpeng 00167020

            	 7	        EDMA_CH_LDSP_NV_LOADING	分配给TLDSP动态加载NV使用	运行时候用于动态加载NV(包括装备场景)	BBE16	honghuiyong

            	 8	        EDMA_CH_HIFI_SIO_TX	    SIO接口发送	CPE等产品语音场景使用	HIFI	沈秀勇
            	 9  	    EDMA_CH_HIFI_SIO_RX	    SIO接口接收	CPE等产品语音场景使用	HIFI	沈秀勇

            	 10	        EDMA_CH_DRV_SIM_0	    SIM卡0收发数据使用	"SIM卡0接收和发送(由SIM卡驱动来解决接收和发送复用)"	C核	杨志
            	 11	        EDMA_CH_DRV_SIM_1	    SIM卡1收发数据使用	"SIM卡1接收和发送（用于双卡双待)(由SIM卡驱动来解决接收和发送复用)"	C核	杨志
            	 12	        EDMA_CH_HSUART_TX	    高速串口发送使用	用于蓝牙语音场景	A核?	吴择淳
            	 13	        EDMA_CH_HSUART_RX	    高速串口接收使用	用于蓝牙语音场景	A核?	吴择淳
            	 14	        EDMA_CH_DRV_LCD	        SPI1发送，刷LCD屏	SPI1发送，刷LCD屏	A核	徐文芳
            	 15	        EDMA_CH_DRV_AXIMON	    接收来自axi_monitor的采集数据	axi_monitor的采数	A核	朱洪飞

                0/1通道复用  两种作用复用：      1. TLDSP上下电(包括开机和低功耗)使用，上电512K, 下电256k2.在运行的时候搬移LDSP专有镜像"	LDRV/TLDSP
            	 0复用      EDMA_CH_LOAD_TLDSP_TCM  备份恢复TLDSP公共镜像或者动态加载LDSP专有镜像"	"	洪慧勇/付效伟
            	 0复用      EDMA_CH_LDSP_API_USED_0
            	 1复用      EDMA_CH_LOAD_TDSDSP_TCM	加载专有镜像	在运行的时候搬移TDSP专有镜像	LDRV or TLDSP	洪慧勇
            	 1复用      EDMA_CH_LDSP_API_USED_1

            	 2	        EDMA_CH_LDSP_CSU_SDR	LDSP小区搜索	运行时候用于小区搜索功能	TLDSP	洪慧勇
            	 3	        EDMA_CH_LDSP_EMU_SDR	LDSP能量测量	运行时候用于能量测量功能	TLDSP	洪慧勇
*/

#define BALONG_DMA_INT_DONE           1          /*DMA传输完成中断*/
#define BALONG_DMA_INT_LLT_DONE       2          /*链式DMA节点传输完成中断*/
#define BALONG_DMA_INT_CONFIG_ERR     4          /*DMA配置错误导致的中断*/
#define BALONG_DMA_INT_TRANSFER_ERR   8          /*DMA传输错误导致的中断*/
#define BALONG_DMA_INT_READ_ERR       16         /*DMA链表读错误导致的中断*/

/* EDMAC传输方向定义*/
#define BALONG_DMA_P2M      1
#define BALONG_DMA_M2P      2
#define BALONG_DMA_M2M      3

/* 通道状态 */

#define   EDMA_CHN_FREE          1   /* 通道空闲 */
#define   EDMA_CHN_BUSY          0   /* 通道忙 */


/* EDMA传输位宽，源、目的地址约束为一致的值 */
#define   EDMA_TRANS_WIDTH_8       0x0   /* 8bit位宽*/
#define   EDMA_TRANS_WIDTH_16      0x1   /* 16bit位宽*/
#define   EDMA_TRANS_WIDTH_32      0x2   /* 32bit位宽*/
#define   EDMA_TRANS_WIDTH_64      0x3   /* 64bit位宽*/

/*  EDMA burst length, 取值范围0~15，表示的burst长度为1~16*/
#define   EDMA_BUR_LEN_1    0x0    /* burst长度，即一次传输的个数为1个*/
#define   EDMA_BUR_LEN_2    0x1    /* burst长度，即一次传输的个数为2个*/
#define   EDMA_BUR_LEN_3    0x2   /* burst长度，即一次传输的个数为3个*/
#define   EDMA_BUR_LEN_4    0x3   /* burst长度，即一次传输的个数为4个*/
#define   EDMA_BUR_LEN_5    0x4   /* burst长度，即一次传输的个数为5个*/
#define   EDMA_BUR_LEN_6    0x5   /* burst长度，即一次传输的个数为6个*/
#define   EDMA_BUR_LEN_7    0x6   /* burst长度，即一次传输的个数为7个*/
#define   EDMA_BUR_LEN_8    0x7   /* burst长度，即一次传输的个数为8个*/
#define   EDMA_BUR_LEN_9    0x8   /* burst长度，即一次传输的个数为9个*/
#define   EDMA_BUR_LEN_10   0x9   /* burst长度，即一次传输的个数为10个*/
#define   EDMA_BUR_LEN_11   0xa   /* burst长度，即一次传输的个数为11个*/
#define   EDMA_BUR_LEN_12   0xb   /* burst长度，即一次传输的个数为12个*/
#define   EDMA_BUR_LEN_13   0xc   /* burst长度，即一次传输的个数为13个*/
#define   EDMA_BUR_LEN_14   0xd   /* burst长度，即一次传输的个数为14个*/
#define   EDMA_BUR_LEN_15   0xe   /* burst长度，即一次传输的个数为15个*/
#define   EDMA_BUR_LEN_16   0xf   /* burst长度，即一次传输的个数为16个*/


/* EDMA 对应的具体位，供EDMA  寄存器配置宏
       EDMAC_BASIC_CONFIG、BALONG_DMA_SET_LLI、BALONG_DMA_SET_CONFIG 使用*/
/*config------Bit 31*/
#define EDMAC_TRANSFER_CONFIG_SOUR_INC      (0X80000000)
/*Bit 30*/
#define EDMAC_TRANSFER_CONFIG_DEST_INC      (0X40000000)
#define EDMAC_TRANSFER_CONFIG_BOTH_INC      (0XC0000000)

/*Bit 27-24*/
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH_MASK     (0xF000000)
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH( _len )  ((unsigned int)((_len)<<24))
/*Bit 23-20*/
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH_MASK     (0xF00000)
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH( _len )  ((unsigned int)((_len)<<20))

/*Bit18-16*/
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH_MASK     (0x70000)
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH( _len )  ((unsigned int)((_len)<<16))
/*Bit14-12*/
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH_MASK     (0x7000)
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH( _len )  ((unsigned int)((_len)<<12))

/*Bit9-4*/
#define EDMAC_TRANSFER_CONFIG_REQUEST( _ulReg )    ( (_ulReg ) << 4)
/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )    ((unsigned int)((_len)<<2))

#define EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE            ( 0x2 )
#define EDMAC_TRANSFER_CONFIG_INT_TC_DISABLE           ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE           ( 0x1 )
#define EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE          ( 0x0 )
#define EDMAC_NEXT_LLI_ENABLE       0x2           /* Bit 1 */
/*Bit 15*/
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_A_SYNC     ( 0UL )
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_AB_SYNC    ( 0x00008000 )

#define P2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_DEST_INC)
#define M2P_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC)
#define M2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_MEM_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC | EDMAC_TRANSFER_CONFIG_DEST_INC)

#define EDMAC_MAKE_LLI_ADDR( _p )   (unsigned int)( (unsigned int)(_p) & 0xFFFFFFE0 )

/*edma 请求类型。*/
typedef enum _BALONG_DMA_REQ
{

    EDMA_SPI0_RX = 0,
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,
    EDMA_SPI1_TX,       /* Acore drv lcd 刷屏   实际分配通道 edma ch16 - 14 */
    EDMA_LTESIO_RX,     /* HIFI                  实际分配通道 edma ch16 - 8  */
    EDMA_LTESIO_TX,     /* HIFI                  实际分配通道 edma ch16 - 9  */
    RESERVE_0,
    RESERVE_1,
    EDMA_HSUART_RX = 8, /* Acore drv 蓝牙语音场景 实际分配通道 edma ch16-12 */
    EDMA_HSUART_TX,      /* Acore drv 蓝牙语音场景 实际分配通道 edma ch16-13 */
    EDMA_UART0_RX,
    EDMA_UART0_TX,
    EDMA_UART1_RX,
    EDMA_UART1_TX,
    EDMA_UART2_RX,
    EDMA_UART2_TX,
    EDMA_SCI0_RX = 0x10, /* Acore drv SIM卡1收  实际分配通道 edma ch16-10 */
    EDMA_SCI_RX  = 0x10,
    EDMA_SCI0_TX,          /* Acore drv SIM卡1发  实际分配通道 edma ch16-10 */
    EDMA_SCI1_RX,          /* Acore drv SIM卡2收  实际分配通道 edma ch16-11 */
    EDMA_SCI1_TX,          /* Acore drv SIM卡2发  实际分配通道 edma ch16-11 */
    EDMA_GBBP0_DBG = 0x14,
    EDMA_BBP_DBG   = 0x14, /* gudsp 的请求 bbp搬数 实际分配通道 edma ch16-6 */
    EDMA_GBBP1_GRIF = 0x15,
    EDMA_BBP_GRIF   = 0x15,/* gudsp 的请求 bbp采数 实际分配通道 edma ch16-6  */
    EDMA_AMON_SOC = 0x16,     /* Acore AXIMON 实际分配通道 edma ch16-15 */
    EDMA_AMON_CPUFAST = 0x17,/* Acore AXIMON 实际分配通道 edma ch16-15 */
    /* gudsp 的请求 M2M */
    /* EDMA_GBBP0_DBG 为gudsp使用 EDMA_BBP_DBG  实际分配通道 edma ch16 - 6  */
    EDMA_MEMORY_DSP_1,  /* 用于turbo译码  实际分配通道 edma ch4  - 0  */
    EDMA_MEMORY_DSP_2,          /* 用于viterb译码 实际分配通道 edma ch4  - 1  */
    /*TL与GU复用 ch16 - 2，为保险每次启用前检查当前通道是否空闲***/
    EDMA_MEMORY_DSP_3,          /* 用于CQI表搬移   实际分配通道 edma ch16 - 2 */
    EDMA_MEMORY_DSP_4,          /* 用于上行编码     实际分配通道 edma ch4  - 2 */
    EDMA_MEMORY_DSP_5,          /* 用于APT表搬移   实际分配通道 edma ch4  - 3 */
    EDMA_MEMORY_DSP_6 ,  /* GUDSP/AHB加载 实际分配通道 edma ch16 - 7 */

    EDMA_PWC_LDSP_TCM,        /* Mcore  drv   实际分配通道 edma ch16 - 0  */
    EDMA_PWC_TDSP_TCM,         /* Mcore  drv   实际分配通道 edma ch16 - 1  */
    EDMA_MEMORY_1 = 0x20,
    EDMA_MEMORY_2,
    EDMA_MEMORY_3,
    EDMA_MEMORY_4,
    EDMA_DSP_GRIF = 0x24,
    EDMA_PWC_CDSP_TCM = 0x25,         /* Mcore  drv   实际分配通道   */
    EDMA_CPS_L2_UP,
    EDMA_CPS_L2_DOWN,
    EDMA_G1_GTC,
    EDMA_G2_GTC,
    EDMA_REQ_MAX,               /*如果设备请求不小于此值，则为非法请求*/

    EDMA_BUTT
} BALONG_DMA_REQ_E;

/**** V8 提供给LPHY的 edma通道号    ---- start**/
/* V7 提供给LPHY的 edma通道号 在platform下drv_edma_enum.h中*/
#define     EDMA_LDSP_NV_LOADING         (2)           /* edma chanl 2 , for LDSP*/
#define     EDMA_LDSP_API_USED_0         (3)           /* edma chanl 3 , for LDSP*/
#define     EDMA_LDSP_API_USED_1         (4)           /* edma chanl 4 , for LDSP*/
#define     EDMA_LDSP_CSU_SDR            (5)           /* edma chanl 5 , for LDSP*/
#define     EDMA_LDSP_EMU_SDR            (6)           /* edma chanl 6, for LDSP*/
#define     EDMA_LDSP_LCS_SDR            (0xffff)      /* 没有实际用途 , stub for LDSP*/

/*EDMAC流控制与传输类型*/
typedef enum tagEDMA_TRANS_TYPE
{
    MEM_MEM_DMA = 0x00,    /* 内存到内存，DMA流控*/
    MEM_PRF_DMA = 0x01,    /* 内存与外设，DMA流控*/
    MEM_PRF_PRF = 0x10     /* 内存与外设，外设流控*/
} EDMA_TRANS_TYPE_E;

/*链式传输时的节点信息。*/
typedef struct _BALONG_DMA_CB
{
    volatile unsigned int lli;     /*指向下个LLI*/
    volatile unsigned int bindx;
    volatile unsigned int cindx;
    volatile unsigned int cnt1;
    volatile unsigned int cnt0;  /*块传输或者LLI传输的每个节点数据长度 <= 65535字节*/
    volatile unsigned int src_addr; /*物理地址*/
    volatile unsigned int des_addr; /*物理地址*/
    volatile unsigned int config;
} BALONG_DMA_CB_S __attribute__ ((aligned (32)));

typedef void (*channel_isr)(unsigned int channel_arg,unsigned int int_status);
/*****************************************************************************
	 *  函 数 名  : mdrv_edma_basic_config
	 *  功能描述  :  用于配置edma通道的源和目的的burst width和len。
	                                实现为宏，得到一个u32的值。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :
     	 *
	 ******************************************************************************/
    /*unsigned int mdrv_edma_basic_config (unsigned int burst_width, unsigned int burst_len);*/
	#define mdrv_edma_basic_config(burst_width,burst_len) \
		( EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len) | EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len) \
		| EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width) | EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width) )

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_set_lli
	 *  功能描述  :  用于链表传输时，配置节点信息BALONG_DMA_CB的lli项。
	 *                             配置lli寄存器的下一个链表节点地址和使能。
	 *                             用宏实现，得到配置值
	 *  输入参数  :addr 为物理地址
	 *
	 *  输出参数  : 无
	 *  返 回 值  : 0	最后一个节点的配置。
        *                        32位的值	"节点地址"和"使能"对应比特位的配置"
     	 *
	 ******************************************************************************/
/*unsigned int mdrv_edma_set_lli (unsigned int addr, unsigned int last);*/
 /*待确认是否用宏实现*/
#define mdrv_edma_set_lli(addr,last)  ((last)?0:(EDMAC_MAKE_LLI_ADDR(addr) | EDMAC_NEXT_LLI_ENABLE))



/*****************************************************************************
 函 数 名  : mdrv_edma_set_config
 功能描述  : 用于根据用户下发EDMA配置信息生成config寄存器信息并返回给用户
 输入参数  : req         逻辑请求号
             direction   传输方向
             burst_width burst传输位宽
             burst_len   burst传输长度
 输出参数  : 无
 返 回 值  : 0-失败，其他-生成的寄存器信息
 调用函数  : NA
 被调函数  : NA
*
******************************************************************************/
unsigned int mdrv_edma_set_config(BALONG_DMA_REQ_E req, unsigned int direction, unsigned int burst_width, unsigned int burst_len);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_get_curr_trans_addr
	 *  功能描述  :  获得某通道当前的传输地址。
	 *  输入参数  :  channel_id : 通道ID，调用 xx_channel_init函数的返回值
	 *
	 *  输出参数  : 无
	 *  返 回 值  : 	其他值:	读取获得的当前通道传输地址寄存器的值
        *                         -1	          :    失败（参数错误）
     	 *
	 ******************************************************************************/
int mdrv_edma_get_curr_trans_addr (unsigned int channel_id);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_stop
	 *  功能描述  :  停止某通道的传输。
	 *  输入参数  : channel_id 
	 *
	 *  输出参数  : 无
	 *  返 回 值  :其他	成功，返回当前传输地址
        *                        -1	   失败
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_stop (unsigned int channel_id);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_get_lli_addr
	 *  功能描述  :  获得指定DMA通道的lli控制块首地址。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  : 0	      失败，返回空指针
        *                        其他   成功，返回寄存器lli控制块的地址
     	 *
	 ******************************************************************************/
BALONG_DMA_CB_S * mdrv_edma_chan_get_lli_addr (unsigned int channel_id);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_init
	 *  功能描述  :  根据外设号分配通道，注册通道中断回调函数、初始化传输完成信号量、将外设号写入config寄存器。
	 *  输入参数  : req		     外设请求号
        *                            pFunc		     上层注册的DMA中断处理函数。为NULL时表示不需要注册。
        *                            channel_arg	     pFunc的参数1
        *                            int_flag	            pFunc的参数2，表示传输产生的中断类型
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_init (BALONG_DMA_REQ_E req, channel_isr pFunc, unsigned int channel_arg, unsigned int int_flag);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_config
	 *  功能描述  :  非链式EDMA传输时，调用本函数配置通道参数。链式EDMA传输时，不需要使用本函数。
	 *  输入参数  :  channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
               direction : DMA传输方向, 取值为BALONG_DMA_P2M、BALONG_DMA_M2P、
                           BALONG_DMA_M2M之一
               burst_width：取值为0、1、2、3，表示的burst位宽为8、16、32、64bit
               burst_len：取值范围0~15，表示的burst长度为1~16
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_config (unsigned int channel_id, unsigned int direction,unsigned int burst_width, unsigned int burst_len);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_dest_config
	 *  功能描述  :  BBP GRIF单独配置目的数据位宽和长度时调用。其他情形不使用。
                       使用时，该接口在balong_dma_channel_set_config之后调用。
	 *  输入参数  :  channel_id：通道ID，调用balong_dma_channel_init函数的返回值
               burst_width：取值为0、1、2、3，表示的burst位宽为8、16、32、64bit
               burst_len：取值范围0~15，表示的burst长度为1~16
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_dest_config(unsigned int channel_id, unsigned int dest_width, unsigned int dest_len);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_start
	 *  功能描述  :  启动一次同步DMA传输，DMA传输完成后才返回，不需要注册中断
	 *  输入参数  : channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；一次传输数据的最大长度是65535字节
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_async_start
	 *  功能描述  :  启动一次异步DMA传输，启动DMA后就返回，不等待。
	                   需要注册中断处理函数，处理DMA传输完成中断。
					   或者，不注册中断处理函数，使用balong_dma_channel_is_idle函数查询
               DMA传输是否完成
	 *  输入参数  :   channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；一次传输数据的最大长度是65535字节
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_async_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_lli_start
	 *  功能描述  :  启动链式传输，所有节点传输完成后返回。
	 			链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_lli_start(unsigned int channel_id);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_lli_async_start
	 *  功能描述  :  启动链式传输，启动后不等待传输完成，直接返回
               链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_lli_async_start(unsigned int channel_id);

/*****************************************************************************
	 *  函 数 名  : mdrv_edma_chan_is_idle
	 *  功能描述  :  查询DMA通道是否空闲。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  : 	0		通道空闲
	 *                         1		通道忙
	 *                        负数		查询失败
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_is_idle(unsigned int channel_id);

#ifdef __cplusplus
}
#endif
#endif

