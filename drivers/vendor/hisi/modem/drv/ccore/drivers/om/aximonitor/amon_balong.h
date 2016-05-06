/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  amon_balong.h
*
*   作    者 :  z00212940
*
*   描    述 :  可维可测AXI Monitor
*
*   修改记录 :  2013年1月29日  v1.00  z00212940  创建
*
*************************************************************************/
#ifndef _AMON_BALONG_H_
#define _AMON_BALONG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "product_config.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "mdrv_public.h"
#include "hi_amon.h"
#include "soc_interrupts.h"
#include "bsp_softtimer.h"
#include "bsp_amon.h"
#include "drv_amon.h"
#include "bsp_memmap.h"
#include "bsp_clk.h"
#include "bsp_edma.h"
#include "bsp_version.h"
#define amon_log_print printf

#if 0
#define AXI_PHYS_TO_VIRT(phy)           phys_to_virt((unsigned long)phy)
#define AXI_VITR_TO_PHYS(virt)          virt_to_phys((void*)virt)
#else
#define AXI_PHYS_TO_VIRT(phy)           phy
#define AXI_VITR_TO_PHYS(virt)          virt
#endif

/**************************************************************************
                                   宏定义
**************************************************************************/
#define AXI_INT_VECTOR                  INT_LVL_AMON                /* 中断向量 */
#define AXI_WAIT_CNT                    1000                        /* 等待软复位或者启停操作完成尝试次数 */
#define AXI_MAX_PORT                    AXI_MAX_PORT_CNT            /* 最大监控端口个数 */
#define AXI_MAX_ID                      AXI_MAX_CONFIG_ID           /* 最大监控ID数目 */
#define AXI_CAPT_THRESHOLD              (50*1024)                   /* EDMA传输长度 */
#define AXI_EDMA_BINDEX                 128                         /* EDMA二维传输步长 */
#define SOC_EDMA_REQUEST                EDMA_AMON_SOC               /* SOC EDMA外设请求号 */
#define CPUFAST_EDMA_REQUEST            EDMA_AMON_CPUFAST           /* CPUFAST EDMA外设请求号 */
#define AXI_SOCP_CHAN_ID                SOCP_CODER_SRC_AXI_MONITOR  /* MONITOR使用的SOCP源通道ID */
#define SOCP_BD_PACKET_SIZE             8                           /* SOCP BD包大小 */
#define SOCP_BD_BUF_SIZE                (SOCP_BD_PACKET_SIZE*1024)  /* SOCP BD buffer大小 */
#define SOCP_RD_PACKET_SIZE             8                           /* SOCP RD包大小 */
#define SOCP_RD_BUF_SIZE                (SOCP_RD_PACKET_SIZE*1024)  /* SOCP RD buffer大小 */
#define AXI_SOCP_PACKET_SIZE            (2*1024)                    /* 每2k进行SOCP组包 */
#define AXI_SOCP_TRAN_WAIT_CNT          5                           /* 采集结束，等待SOCP传输完成最大次数 */
#define AXI_CAPT_TRAN_OVER_TIME         500                         /* 采集传输完成最大等待时间 */
#define AXI_CAPT_CNF_REG_CNT            17                          /* 采集配置命令回复需要上报寄存器的数目 */
#define AXI_MON_CNF_REG_CNT             35                          /* 监控配置命令回复需要上报寄存器的数目 */
#define AXI_CAPT_CYCLE_DEFAULT          2000                        /* 采集周期默认值 */
#define AXI_SOFT_RESET                  0x2                         /* AXI monitor软复位 */
#define AXI_RESET_TO_IDLE               0x1                         /* AXI monitor强制进入IDLE态 */
#define AXI_RUN_STATE_MASK              0xC                         /* AXI monitor运行状态 */
#define AXI_RESET_STATE_MASK            0x10                        /* AXI monitor软复位状态 */
#define AXI_FIFO_DEPTH                  32                          /* Monitor FIFO深度 */
#define AMON_MAIN_VERSION               1
#define AMON_MINOR_VERSION              1

/**************************************************************************
                                 寄存器定义
**************************************************************************/
/* 基地址类型 */
enum axi_base_addr_enum
{
    AXI_FAST_ADDR_ENUM,             /* cpu fast基地址*/
    AXI_SOC_ADDR_ENUM,             /* cpu slow 基地址 */
    AXI_CTRL_ADDR_BUTT                   /* 无效值 */
};

/* AXI monitor有两种配置方案: CPUFAST, SOC */
extern u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT];
#define AXI_MON_CPUFAST_BASE_ADDR       (g_amon_base_addr[AXI_FAST_ADDR_ENUM]) /* AXI monitor CPUFAST基地址 */
#define AXI_MON_SOC_BASE_ADDR           (g_amon_base_addr[AXI_SOC_ADDR_ENUM])     /* AXI monitor SOC基地址 */

/* AXI内部buffer起始地址 */
#define CPUFAST_BUFF_BASE_ADDR          (AXI_MON_CPUFAST_BASE_ADDR + 0xA00)
#define SOC_BUFF_BASE_ADDR              (AXI_MON_SOC_BASE_ADDR + 0xA00)

/* AXI monitor寄存器偏移地址定义 begin */
#define AXI_MON_CNT_RESET               HI_AMON_CNT_RESET_OFFSET                /* AXI monitor统计计数器软复位寄存器  */
#define AXI_MON_CNT_CTRL                HI_AMON_CNT_CTRL_OFFSET                 /* AXI monitor系统配置寄存器 */
#define AXI_MON_CNT_STATE_INT           HI_AMON_CNT_STATE_INT_OFFSET            /* AXI monitor系统状态寄存器 */
#define AXI_MON_WIN_COUNTER             HI_AMON_WIN_COUNTER_OFFSET              /* AXI monitor系统时间窗计数器 */
#define AXI_MON_IDLE_COUNTER            HI_AMON_IDLE_COUNTER_OFFSET             /* AXI monitor系统idle统计计数器 */
#define AXI_MON_PORT_SEL                HI_AMON_PORT_SEL_OFFSET                 /* AXI monitor监控ID的AXI port配置 */
#define AXI_MON_INT_CLR                 HI_AMON_INT_CLR_OFFSET                  /* AXI monitor中断清除寄存器 */
#define AXI_ID_INT_SRC                  HI_AMON_ID_INT_SRC_OFFSET               /* ID读写监控中断原始寄存器 */
#define AXI_ID_INT_MASK                 HI_AMON_ID_INT_MASK_OFFSET              /* ID读写监控中断屏蔽寄存器 */
#define AXI_ID_INT_STAT                 HI_AMON_ID_INT_STAT_OFFSET              /* ID读写监控中断状态寄存器 */

/* n为port，取值范围0-7 */
#define AXI_MON_RD_WAIT_CYCLE_PORTS(n)  (HI_AMON_RD_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* 监控PORTs为精确定位读等待计数而消耗的时间周期寄存器 */
#define AXI_MON_WR_WAIT_CYCLE_PORTS(n)  (HI_AMON_WR_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* 监控PORTs为精确定位写等待计数而消耗的时间周期寄存器 */
/* n为ID, 取值范围0-7 */
#define AXI_MON_CNT_TYPE(n)             (HI_AMON_CNT_TYPE_0_OFFSET + n*0x4)         /* 监控ID的监控类型选择 */
#define AXI_MON_CNT_ID(n)               (HI_AMON_CNT_ID_0_OFFSET + n*0x100)         /* AXI monitor系统ID信息寄存器 */
#define AXI_MON_ID_ADDR_DES(n)          (HI_AMON_ID_ADDR_DES_0_OFFSET + n*0x100)    /* 监控地址下边界 */
#define AXI_MON_ID_ADDR_DES_M(n)        (HI_AMON_ID_ADDR_DES_M_0_OFFSET + n*0x100)  /* 监控地址上边界 */

/* 统计计数器 begin */
#define AXI_MON_INCR1_ID(n)             (HI_AMON_INCR1_ID_0_OFFSET + n*0x100)               /* 监控ID n发起INCR1操作计数器 */
#define AXI_MON_INCR2_ID(n)             (HI_AMON_INCR2_ID_0_OFFSET + n*0x100)               /* 监控ID n发起INCR2操作计数器 */
#define AXI_MON_INCR4_ID(n)             (HI_AMON_INCR4_ID_0_OFFSET + n*0x100)               /* 监控ID n发起INCR4操作计数器 */
#define AXI_MON_INCR8_ID(n)             (HI_AMON_INCR8_ID_0_OFFSET + n*0x100)               /* 监控ID n发起INCR8操作计数器 */
#define AXI_MON_INCR16_ID(n)            (HI_AMON_INCR16_ID_0_OFFSET + n*0x100)              /* 监控ID n发起INCR16操作计数器 */
#define AXI_MON_WRAP_ID(n)              (HI_AMON_WRAP_ID_0_OFFSET + n*0x100)                /* 监控ID n发起WRAP操作计数器 */
#define AXI_MON_BURST_ID(n)             (HI_AMON_BURST_ID_0_OFFSET + n*0x100)               /* 监控ID n发起BURST操作计数器 */
#define AXI_MON_FINISH_ID(n)            (HI_AMON_FINISH_ID_0_OFFSET + n*0x100)              /* 监控ID n完成BURST操作计数器 */
#define AXI_MON_RD_WAIT_ID_LOW(n)       (HI_AMON_READ_WAIT_ID_0_OFFSET + n*0x100)           /* 监控ID n读等待周期计数器，低32位(64位寄存器，0~43有效) */
#define AXI_MON_RD_WAIT_ID_HIGH(n)      (HI_AMON_READ_WAIT_ID_0_OFFSET + 0x4 + n*0x100)     /* 监控ID n读等待周期计数器，高32位(64位寄存器，0~43有效) */
#define AXI_MON_WR_WAIT_ID_LOW(n)       (HI_AMON_WRITE_WAIT_ID_0_OFFSET + n*0x100)          /* 监控ID n写等待周期计数器，低32位(64位寄存器，0~43有效) */
#define AXI_MON_WR_WAIT_ID_HIGH(n)      (HI_AMON_WRITE_WAIT_ID_0_OFFSET + 0x4 + n*0x100)    /* 监控ID n写等待周期计数器，高32位(64位寄存器，0~43有效) */
#define AXI_MON_WR_WAIT_RESP_ID_LOW(n)  (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + n*0x100)     /* 监控ID n写响应等待周期计数器，低32位(64位寄存器，0~43有效) */
#define AXI_MON_WR_WAIT_RESP_ID_HIGH(n) (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + 0x4 + n*0x100)/* 监控ID n写响应等待周期计数器，高32位(64位寄存器，0~43有效) */
#define AXI_MON_RD_MAX_WAIT_ID(n)       (HI_AMON_READ_MAX_WAIT_ID_0_OFFSET + n*0x100)       /* 监控ID n读最大等待周期计数器 */
#define AXI_MON_WR_MAX_WAIT_ID(n)       (HI_AMON_WRITE_MAX_WAIT_ID_0_OFFSET + n*0x100)      /* 监控ID n写最大等待周期计数器 */
#define AXI_MON_WR_MAX_WAIT_RESP_ID(n)  (HI_AMON_WRITE_MAX_WAIT_RESP_ID_0_OFFSET + n*0x100) /* 监控ID n写响应最大等待周期计数器 */
#define AXI_MON_RD_BYTES_ID_LOW(n)      (HI_AMON_READ_BYTES_ID_0_OFFSET + n*0x100)          /* 监控ID n读数据总量，byte为单位，低32位(64位寄存器，0~39有效) */
#define AXI_MON_RD_BYTES_ID_HIGH(n)     (HI_AMON_READ_BYTES_ID_0_OFFSET + 0x4 + n*0x100)    /* 监控ID n读数据总量，byte为单位，高32位(64位寄存器，0~39有效) */
#define AXI_MON_WR_BYTES_ID_LOW(n)      (HI_AMON_WRITE_BYTES_ID_0_OFFSET + n*0x100)         /* 监控ID n写数据总量，byte为单位，低32位(64位寄存器，0~39有效) */
#define AXI_MON_WR_BYTES_ID_HIGH(n)     (HI_AMON_WRITE_BYTES_ID_0_OFFSET + 0x4 + n*0x100)   /* 监控ID n写数据总量，byte为单位，高32位(64位寄存器，0~39有效) */
/* 统计计数器 end */

/* 采集寄存器 begin */
#define AXI_CAPT_CTRL                   (HI_AMON_CAPT_CTRL_OFFSET)              /* 控制数据采集开始和结束 */
#define AXI_CAPT_ID_EN                  (HI_AMON_CAPT_ID_EN_OFFSET)             /* 采数使能寄存器 */
#define AXI_CAPT_TRAN_CONFIG            (HI_AMON_CAPT_CONFIG_OFFSET)            /* 采集传输配置寄存器 */
#define AXI_CAPT_ID(id)                 (HI_AMON_CAPT_ID_0_OFFSET + id*0x4)     /* ID信息寄存器 */
#define AXI_CAPT_INT_SRC                (HI_AMON_CAPT_INT_SRC_OFFSET)           /* 采集原始中断寄存器 */
#define AXI_CAPT_INT_MASK               (HI_AMON_CAPT_INT_MASK_OFFSET)          /* 采集中断屏蔽寄存器 */
#define AXI_CAPT_INT_STATE              (HI_AMON_CAPT_INT_STATE_OFFSET)         /* 采集中断状态寄存器 */
#define AXI_CAPT_INT_CLR                (HI_AMON_CAPT_INT_CLR_OFFSET)           /* 采集中断清除寄存器 */
#define AXI_CAPT_ERR_STATE              (HI_AMON_AXI_STATE_OFFSET)              /* 读写错误指示状态寄存器 */
#define AXI_CAPT_TRANS_WAIT_TIME        (HI_AMON_CAPT_TRANS_WAIT_TIME_OFFSET)   /* 数据搬移请求中断上报等待时长寄存器 */
#define AXI_CAPT_TRANS_DATA_CNT         (HI_AMON_TRANS_DATA_CNT_OFFSET)         /* 数据搬移量统计寄存器, 存放低11位以及进位标志 */
#define AXI_CAPT_TRANS_DATA_CNT_HIGH    (HI_AMON_TRANS_DATA_CNT_HIGH_OFFSET)    /* 数据搬移量统计寄存器, 存放高20位 */
#define AXI_CAPT_TRANS_DATA_LEVEL       (HI_AMON_TRANS_DATA_LEVEL_OFFSET)       /* 数据搬移阈值配置寄存器 */
#define AXI_CAPT_CMD_PKG_SIZE           (HI_AMON_CMD_PKG_SIZE_OFFSET)           /* 命令包长度寄存器 */
#define AXI_CAPT_DATA_PKG_SIZE          (HI_AMON_DATA1_PKG_SIZE_OFFSET)         /* 数据包长度寄存器 */
#define AXI_CAPT_EXT_PKG_SIZE           (HI_AMON_DATA2_PKG_SIZE_OFFSET)         /* 附加包长度寄存器 */
#define AXI_CAPT_DMA_REQ_TYPE           (HI_AMON_DMA_REQ_EN_OFFSET)             /* DMA外设请求寄存器 */
#define AXI_CAPT_HEAD_FLAG              (0x960)                                 /* 包头标志寄存器 */
#define AXI_CAPT_FIFO_ADDR              (0xa00)                                 /* Monitor FIFO地址 */
/* 采集寄存器 end */

/* AXI monitor寄存器偏移地址定义 end */

/**************************************************************************
                               数据结构定义
**************************************************************************/


/* 时间窗配置 */
enum axi_win_config_enum
{
    AXI_WIN_DISABLE,            /* 时间窗不使能 */
    AXI_WIN_ENABLE,             /* 时间窗使能 */
    AXI_WIN_BUTT
};
typedef unsigned char axi_win_config_enum_uint8;

/* 获取AXI monitor状态请求 */
enum axi_get_state_req_enum
{
    AXI_GET_RUN_STATE_REQ,      /* 获取运行状态 */
    AXI_GET_RESET_STATE_REQ,    /* 获取软复位状态 */
    AXI_GET_STATE_REQ_BUTT
};
typedef unsigned int axi_get_state_req_enum_uint32;

/* AXI monitor状态 */
enum axi_state_enum
{
    AXI_IDLE            = 0x0,  /* IDLE状态 */
    AXI_WIN_RUNNING     = 0x4,  /* 带时间窗的监控状态 */
    AXI_UNWIN_RUNNING   = 0x8,  /* 不带时间窗的监控状态 */
    AXI_STOP            = 0xC,  /* STOP状态 */
    AXI_RESET_FINISH    = 0x10, /* 软复位完成 */
    AXI_STATE_BUTT      = 0xFFFFFFFF
};
typedef unsigned int axi_state_enum_uint32;

/* 采集状态切换 */
enum axi_capt_full_state_enum
{
    AXI_CAPT_NORMAL             = 0x1,      /* 正常状态 */
    AXI_CAPT_FULL               = 0x2,      /* buffer满 */
    AXI_CAPT_FINISHING          = 0x4,      /* 等待传输完成 */
    AXI_CAPT_STOP_REQ           = 0x8,      /* stop请求 */
    AXI_CAPT_PERIOD_STOP_REQ    = 0x10,     /* 周期采集stop请求 */
    AXI_CAPT_BUTT                           /* 无效值 */
};
typedef unsigned int axi_capt_state_enum_uint32;

/* 采集ID配置 */
typedef struct
{
	u32 	id_en;				/* 使能 */
	u32 	id_value;			/* ID */
	u32 	mask;				/* 掩码 */
} axi_capt_id_config_t;

/* 采集配置请求， 正常模式 */
typedef struct
{
    u32 	mode;			    /* 区分Monitor工作模式，0:CPUFAST 1:SOC */
	u32 	port;	    		/* 监控端口 */
	u32 	op_type;			/* 操作类型，0:读操作 1:写操作 */
	u32 	dma_req_level;	    /* DMA请求发出级别 */
	u32 	cmd_pkg_len;		/* 命令包长度 */
	u32 	data_pkg_len;		/* 数据包长度 */
	u32 	ext_pkg_len;		/* 附加包长度 */
	u32 	data_trans_thr;		/* 数据传输阈值 */
	u32 	dma_req_type;		/* DMA请求类型 */
    u32 	capt_cycle;         /* 采集周期 */
	axi_capt_id_config_t id_cfg[AXI_MAX_ID];	/* 采集ID配置 */
} axi_capt_config_t;

/* 寄存器配置 */
typedef struct
{
	u32 	reg_offset;		    /* 寄存器偏移 */
	u32 	reg_value;			/* 寄存器值 */
} reg_config_t;

/* 采集、监控配置请求，寄存器配置模式 */
typedef struct
{
	u32 	        mode;	    /* 区分Monitor工作模式，0:CPUFAST 1:SOC */
    u32             capt_cycle; /* 采集周期 */
	u32 	        reg_cnt;	/* 寄存器配置数目 */
	reg_config_t    reg_cfg[];  /* 寄存器配置 */
} axi_reg_config_t;

/* 控制命令类型 */
enum axi_ctrl_type_enum
{
    AXI_CTRL_START,             /* 启动 */
    AXI_CTRL_STOP,              /* 停止 */
    AXI_CTRL_EXPORT,            /* 导出 */
    AXI_CTRL_BUTT               /* 无效值 */
};
typedef unsigned int   axi_ctrl_type_enum_uint32;



/* 控制命令请求：启动、停止、导出 */
typedef struct
{
	u32 	                    mode;		/* 区分Monitor工作模式，0:CPUFAST 1:SOC */
	axi_ctrl_type_enum_uint32 	ctrl_type;	/* 控制命令类型，0:启动 1:停止 2:导出 */
} axi_ctrl_t;

/* 监控操作类型配置 */
typedef struct
{
    u32    incr_1:1;   /* INCR操作统计类型: \
                          0 - INCR1读操作发出数量\
                          1 - INCR1写操作发出数量*/
    u32    incr_2:1;   /* INCR操作统计类型: \
                          0 - INCR2读操作发出数量\
                          1 - INCR2写操作发出数量*/
    u32    incr_4:1;   /* INCR操作统计类型: \
                          0 - INCR4读操作发出数量\
                          1 - INCR4写操作发出数量*/
    u32    incr_8:1;   /* INCR操作统计类型: \
                          0 - INCR8读操作发出数量\
                          1 - INCR8写操作发出数量*/
    u32    incr_16:1;  /* INCR操作统计类型: \
                          0 - INCR16读操作发出数量\
                          1 - INCR16写操作发出数量*/
    u32    wrap:2;     /* WRAP操作统计类型: \
                          00 - WRAP4读操作发出数量\
                          01 - WRAP4写操作发出数量\
                          10 - WRAP8读操作发出数量\
                          11 - WRAP8写操作发出数量*/
    u32    bur_send:1; /* burst发出统计类型: \
                          0 - 统计burst读操作发出数量\
                          1 - 统计burst写操作发出数量*/
    u32    but_fin:1;  /* burst完成统计类型: \
                          0 - 统计burst读操作完成数量\
                          1 - 统计burst写操作完成数量*/
    u32    wr_wait:1;  /* 写等待操作类型: \
                          0 - 统计写操作到写第一个数据的延迟\
                          1 - 统计写操作到写最后一个数据的延迟*/
    u32    reserved:22;
} axi_opt_type_t;

/* 监控ID配置 */
typedef struct
{
	u32             id_en;			/* ID使能 */
	u32 	        port;			/* 监控端口 */
    u32             id_mon_en;      /* 监控master ID使能 */
	u32 	        id_value;		/* ID */
	u32 	        mask;			/* 掩码 */
	u32 	        addr_en;		/* 地址监控使能 */
	u32 	        addr_start;	    /* 开始地址 */
	u32 	        addr_end;		/* 结束地址 */
	axi_opt_type_t	opt_type;		/* 操作类型 */
} axi_mon_id_config_t;

/* 监控配置请求， 正常模式 */
typedef struct
{
    u32 			    mode;			        /* 区分Monitor工作模式，0:CPUFAST 1:SOC */
	u32 			    win_en;			        /* 时间窗使能 0:不使能 1:使能 */
	axi_mon_id_config_t id_config[AXI_MAX_ID];  /* 采集ID配置 */
} axi_mon_config_t;

/* 中断统计 */
typedef struct
{
    u32     win_over;               /* 时间窗结束中断 */
    u32     tran_thresh;            /* 传输阈值中断 */
    u32     tran_req;               /* 传输请求中断 */
    u32     tran_over;              /* 传输结束中断 */
    u32     buff_over;              /* 缓存buffer满中断 */
    u32     edma_tran_over;         /* edma传输完成中断 */
} axi_int_stat_t;

/* 采集全局记录 */
typedef struct
{
    axi_int_stat_t          int_stat;       /* 中断统计 */
    axi_config_enum_uint32  capt_mode;      /* 采集模式 */
    axi_config_enum_uint32  mon_mode;       /* 监控模式 */
    struct softtimer_list   axi_timer;      /* timer, 用于周期采集 */
    osl_sem_id              capt_sem;       /* 采集信号量 */
    u32                     capt_cycle;     /* 采集周期 */
    u32                     tran_over_flag; /* 传输结束标志 */
    u32                     capt_edma_len;  /* edma传输长度 */
    u32                     edma_bindex;    /* 二维EDMA传输步长 */
    u32                     axi_buf_full;   /* 本地缓存满次数 */
    u32                     edma_tran_fail; /* edma传输失败次数 */
    u32                     socp_buf_full;  /* socp传输失败次数 */
    u32                     socp_tran_fail; /* socp传输失败次数 */
    u32                     mon_ind_cnt;    /* 监控上报次数统计 */
    u32                     mon_ind_fail_cnt; /* 监控上报失败次数 */
} axi_global_stat_t;

/* 时钟控制 */
typedef struct
{
    u32                     is_clk_enable[AXI_CONFIG_BUTT]; /* 时钟是否使能 */
    struct clk *            sc_clk[AXI_CONFIG_BUTT];        /* Monitor系统时钟 */
} axi_clk_ctrl_t;

/* 循环buffer */
typedef struct
{
    u8 *    start;     /* 循环buffer头指针 */
    u8 *    end;       /* 循环buffer尾指针 */
    u8 *    read;      /* 循环buffer读指针 */
    u8 *    write;     /* 循环buffer写指针 */
} ring_buf_info_t;

/* 循环buffer空闲区域信息 */
typedef struct
{
   u8 *     p_buf_1;    /* 空闲buffer指针 */
   u32      size_1;     /* 空闲buffer大小 */
   u8 *     p_buf_2;    /* 回卷空闲buffer指针 */
   u32      size_2;     /* 回卷空闲buffer大小 */
} ring_idle_buf_t;

/* 循环buffer数据区域信息 */
typedef ring_idle_buf_t ring_data_buf_t;

/******************amon_addr_balong.c********************************/



typedef struct
{
    u32 soc_rd_cnt[AXI_MAX_CONFIG_ID];
    u32 soc_wr_cnt[AXI_MAX_CONFIG_ID];
    u32 cpufast_rd_cnt[AXI_MAX_CONFIG_ID];
    u32 cpufast_wr_cnt[AXI_MAX_CONFIG_ID];
} amon_stat_t;

typedef struct
{
    char *  buff;           /* buffer地址 */
    u32     buff_size;      /* buffer大小 */
    u32     write_offset;   /* 写指针位置 */
} amon_buff_info_t;

/* 低功耗: 寄存器备份、恢复 */
typedef struct
{
    u32     ctrl_reg;                           /* 控制寄存器 begin */
    u32     port_reg;
    u32     int_mask;
    u32     id_reg[AXI_MAX_CONFIG_ID];
    u32     addr_start_reg[AXI_MAX_CONFIG_ID];
    u32     addr_end_reg[AXI_MAX_CONFIG_ID];   /* 控制寄存器 end */
    u32     incr1_reg[AXI_MAX_CONFIG_ID];      /* 统计寄存器 begin */
    u32     incr2_reg[AXI_MAX_CONFIG_ID];
    u32     incr4_reg[AXI_MAX_CONFIG_ID];
    u32     incr8_reg[AXI_MAX_CONFIG_ID];
    u32     incr16_reg[AXI_MAX_CONFIG_ID];
    u32     wrap_reg[AXI_MAX_CONFIG_ID];
    u32     burst_send_reg[AXI_MAX_CONFIG_ID];
    u32     burst_fin_reg[AXI_MAX_CONFIG_ID];
    u32     rd_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     rd_cnt_high_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_high_reg[AXI_MAX_CONFIG_ID];/* 统计寄存器 end */
} axi_reg_bak_t;

typedef enum{
    amon_cpufast_srst_en = 0,
    amon_cpufast_srst_dis = 1,
    amon_cpufast_monitor_start = 2,
    amon_cpufast_dts_butt
}AMON_CPUFAST_DTS_SYSCTRL;

typedef enum{
    amon_soc_srst_en = 0,
    amon_soc_srst_dis = 1,
    amon_soc_monitor_start = 2,
    amon_soc_dts_butt
}AMON_SOC_DTS_SYSCTRL;
typedef enum{
    AMON_BASE_ADDR = 0,
    AMON_START_BIT,
    AMON_END_BIT,
    AMON_ADDR_BUTT
}AMON_DTS_SYSCTRL_ADDR;

struct amon_sysctrl{
    u32 base_addr;
    u32 start_bit;
    u32 end_bit;
};

struct amon_sysctrl_struct
{
    struct amon_sysctrl amon_sysctrl_soc[amon_soc_dts_butt];
    struct amon_sysctrl amon_sysctrl_fast[amon_cpufast_dts_butt];
};

typedef enum{
    AMON_START_TIME = 0,
    AMON_END_TIME = 1,
    AMON_TIME_BUTT
}AMON_BUS_STRESS_TIME;

struct amon_ctrl_struct
{
    u32 busStressTime[AXI_CONFIG_BUTT][AMON_TIME_BUTT];
    struct clk * soc_clk;
    struct clk * cpufast_clk;
    u32          chip_version;
};
/*bus streess start*/
#define STRESS_TIME_FREQ     (1920000)/*1.92M时钟*/

#ifdef BSP_CONFIG_PHONE_TYPE
#define MODEM_BUS_FREQ      (50)/*总线频率,50MHZ*/
#define MODEM_PORT_WITH     (MODEM_BUS_FREQ * 8 * 1024 * 1024)/*每个port的总带宽，单位bytes/s*/
#else
/*每个port的总带宽*/
#define MODEM_BUS_FREQ      (50)/*总线频率,50MHZ*/
#define MODEM_PORT_WITH     (MODEM_BUS_FREQ * 8 * 1024 * 1024)/*bytes/s*/
#endif

/*bus streess end*/




#define AMON_IS_VALID_ADDR(addr) ((addr != 0x0) ? true:false)


#define amon_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_AMON, "[amon] %s:"fmt, __FUNCTION__, ##__VA_ARGS__))
#define amon_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL,   BSP_MODU_AMON, fmt, ##__VA_ARGS__))


/********************************************************************************/
/*    供电类、amon 系统控制器控制模块（sc_模块名_功能)   */
/********************************************************************************/
extern struct amon_sysctrl_struct g_amon_sysctrl;
extern struct amon_ctrl_struct g_amon_ctrl;
static inline void hi_amon_set_reg(unsigned int value,unsigned int base,unsigned int offset,unsigned int lowbit,unsigned highbit)
{
    unsigned int reg    = base + offset;
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    temp   = readl(reg);
    /*lint -save -e701*/
    mask   = ((1 << (highbit - lowbit + 1)) - 1) << lowbit;
    /*lint -restore*/
    value  = (temp & (~mask)) | ((value <<lowbit) & mask);
    writel(value  ,reg);

}
static inline u32 hi_amon_get_reg(unsigned int base,unsigned int offset,unsigned int lowbit,unsigned int highbit)
{
    unsigned int mask = 0;
    unsigned int temp = 0;
    unsigned int reg    = base + offset;
    u32 value = 0;

    temp   = readl(reg);
    /*lint -save -e701*/
    mask   = ((1 << (highbit - lowbit + 1)) -1) << lowbit;
    /*lint -restore*/
    value = temp & mask;
    value = (value) >> lowbit;

    return value;
}


/* AXI Monitor CPUFAST 软复位 */
static __inline__ void amon_cpufast_soft_reset(void)
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/********************************************************************************/
/*    复位、解复位类（sc_模块名_功能)   */
/********************************************************************************/

/* AXI Monitor SOC 软复位 */
static __inline__ void amon_soc_soft_reset(void)
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/* AXI Monitor CPUFAST 解复位 */
static __inline__ void amon_cpufast_rls_reset(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/* AXI Monitor SOC 解复位 */
static __inline__ void amon_soc_rls_reset(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}
/********************************************************************************/
/*    syssc 函数（AXI Monitor模块，启动、停止)                                  */
/********************************************************************************/
/* 启动CPUFAST, 如果该启动位为1，需要先写0，再写1 */
/*lint -save -e528*/
static __inline__ void amon_cpufast_start(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        if(hi_amon_get_reg(base_addr, 0, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}



/* 启动SOC, 如果该启动位为1，需要先写0，再写1 */
static __inline__ void amon_soc_start(void)/*lint !e528*/
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        if(hi_amon_get_reg(base_addr, 0, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}


/* 停止CPUFAST */
static __inline__ void amon_cpufast_stop(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
    }
}


/* 停止SOC */
static __inline__ void amon_soc_stop(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
    }
}
/* 获取CPUFAST 是否使能*/
static __inline__ u32 amon_cpufast_state(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        return hi_amon_get_reg(base_addr, 0, start_bit, end_bit);
    }
    else
    {
        return 0;
    }
}


/* 获取CPUFAST 是否使能*/
static __inline__ u32 amon_soc_state(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        return hi_amon_get_reg(base_addr, 0, start_bit, end_bit);
    }
    else
    {
        return 0;
    }

}

/* AXI Monitor CPUFAST 时钟使能 */
static __inline__ void amon_cpufast_clk_enable(void)/*lint !e528*/
{
    if(clk_enable(g_amon_ctrl.cpufast_clk))
    {
        amon_error("enable fast clk fail\n");
    }
}

/* AXI Monitor SOC 时钟使能 */
static __inline__ void amon_soc_clk_enable(void)/*lint !e528*/
{
    if(clk_enable(g_amon_ctrl.soc_clk))
    {
        amon_error("enable soc clk fail\n");
    }
}
/* AXI Monitor CPUFAST 时钟去使能 */
static __inline__ void amon_cpufast_clk_disable(void)/*lint !e528*/
{
    clk_disable(g_amon_ctrl.cpufast_clk);
}

/* AXI Monitor SOC 时钟去使能 */
static __inline__ void amon_soc_clk_disable(void)/*lint !e528*/
{
    clk_disable(g_amon_ctrl.soc_clk);
}

/*lint -restore*/


/**************************************************************************
                                函数声明
**************************************************************************/
/* AXI寄存器读操作 */
void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value);
#define AXI_REG_READ(config, reg, value)                axi_reg_read(config, reg, value)
/* AXI寄存器写操作 */

void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value);
#define AXI_REG_WRITE(config, reg, value)               axi_reg_write(config, reg, value)
/* AXI寄存器读位操作 */
void axi_reg_getbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 * value);
#define AXI_REG_GETBITS(config, reg, pos, bits, value)  axi_reg_getbits(config, reg, pos, bits, value)
/* AXI寄存器写位操作 */
void axi_reg_setbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 value);
#define AXI_REG_SETBITS(config, reg, pos, bits, value)  axi_reg_setbits(config, reg, pos, bits, value)
#ifdef ENABLE_BUILD_AMON
void axi_sc_clk_open(axi_config_enum_uint32 config);
void axi_sc_clk_close(axi_config_enum_uint32 config);
void axi_sc_mon_start(axi_config_enum_uint32 config);
void axi_sc_mon_stop(axi_config_enum_uint32 config);
void axi_sc_reset(void);
void axi_reset_pkg_buf(axi_config_enum_uint32 config);
void axi_get_data_buf(ring_data_buf_t * data_buf, ring_buf_info_t * ring_buf);
void axi_get_idle_buf(ring_idle_buf_t * idle_buf, ring_buf_info_t * ring_buf);
s32 axi_socp_src_chan_init(void);
s32 axi_gen_bd_packet(ring_data_buf_t * data_buf, u32 * tran_len);
s32 axi_data_buf_update(ring_buf_info_t * ring_buf);
s32 axi_edma_get_tran_len(ring_buf_info_t * ring_buf);
u32 axi_get_edma_cnt(u32 channel_id);
void axi_socp_timer_handler(u32 param);
s32 axi_socp_start_timer(u32 time_out);
void axi_edma_int_handler(u32 param, u32 int_status);
s32 axi_edma_config_init(axi_config_enum_uint32 config, u32 bindex);
s32 axi_edma_free(axi_config_enum_uint32 config);
axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req);
s32 axi_state_check(axi_config_enum_uint32 config);
void axi_win_over_int_handler(void);
void axi_tran_int_handler(void);
void axi_tran_int_handler_k3(void);
void axi_int_handler(void);
void axi_int_handler_k3(void);
s32 axi_reset(axi_config_enum_uint32 config);
s32 axi_init(void);
s32 axi_mon_start(axi_config_enum_uint32 config);
s32 axi_mon_stop(axi_config_enum_uint32 config);
void axi_capt_start(axi_config_enum_uint32 axi_mode);
void axi_capt_stop(axi_config_enum_uint32 config);
void axi_stop_timer(void);
void axi_timer_handler(u32 param);
s32 axi_start_timer(u32 time_out);
void axi_capt_config(axi_config_enum_uint32 axi_mode,  u32 port,u32 capt_id);
void axi_mon_config(axi_mon_config_t * mon_config);
AXI_DATA_CONFIG_CNF_STRU * axi_capt_set_cnf(axi_config_enum_uint32 mode, u32 * out_len);
AXI_MON_CONFIG_CNF_STRU * axi_mon_set_cnf(axi_config_enum_uint32 mode, u32 * out_len);
void axi_mon_get_reg_value(axi_config_enum_uint32 mode, AXI_MON_TERMINATE_CNF_STRU * ter_cnf);
AXI_MON_TERMINATE_CNF_STRU * axi_mon_set_statistic_data(axi_config_enum_uint32 mode, u32 * out_len);
s32 axi_mon_info_gen_packet(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_start(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_stop(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_export(axi_config_enum_uint32 mode);
void axi_print_debug_info(axi_config_enum_uint32 config);
void axi_print_int_cnt(void);
void axi_print_ring_buf_info(void);
s32 amon_addr_is_enable(void);
s32 axi_get_irq_and_iomap(void);
/* 采集配置接口 */
AXI_DATA_CONFIG_CNF_STRU * bsp_axi_capt_config(u8 * data, u32 * out_len);
/* 采集、监控寄存器配置接口 */
s32 bsp_axi_reg_config(u8 * data);
/* 采集控制命令接口 */
s32 bsp_axi_capt_ctrl(u8 * data);
/* 监控配置接口 */
AXI_MON_CONFIG_CNF_STRU * bsp_axi_mon_config(u8 * data, u32 * out_len);
/* 监控启动接口 */
s32 bsp_axi_mon_start(u8 * data);
/* 监控终止接口 */
AXI_MON_TERMINATE_CNF_STRU * bsp_axi_mon_terminate(u8 * data, u32 * out_len);
void axi_capt_test_config(u32 port, u32 mask, u32 value);
s32 amon_soft_enable(void);
void SRE_SetMonitor(void);
void amon_sc_reset(axi_config_enum_uint32 config);
/*lint -save -e830*/
s32 amon_reset(axi_config_enum_uint32 config);
void amon_debug_show(void);
void amon_save_log(axi_config_enum_uint32 mode, u32 id, u32 opt_type, amon_config_t * config);
void amon_int_handler(void);
/*lint -restore +e830*/
#else
static inline s32 bsp_axi_mon_start(u8 * data){return 0;}
static inline AXI_MON_TERMINATE_CNF_STRU * bsp_axi_mon_terminate(u8 * data, u32 * out_len){return NULL;}
static inline AXI_MON_CONFIG_CNF_STRU * bsp_axi_mon_config(u8 * data, u32 * out_len){return NULL;}
static inline AXI_DATA_CONFIG_CNF_STRU * bsp_axi_capt_config(u8 * data, u32 * out_len){return NULL;}
#endif
#ifdef __cplusplus
}
#endif

#endif /* _AMON_BALONG_H_ */
