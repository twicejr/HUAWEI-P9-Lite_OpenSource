/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_platform_kirin.h
 版 本 号   : 初稿
 作    者   : 蒋孝伟 00207786
 生成日期   : 2015年1月12日
 最近修改   :
 功能描述   : AP侧适配RDR框架，相关数据结构及函数定义
 修改历史   :
 1.日    期 : 2015年1月12日
 作    者   : 蒋孝伟 00207786
 修改内容   : 创建文件

 *******************************************************************************/
#include <linux/thread_info.h>
#include <linux/hisi/rdr_types.h>
#include <linux/hisi/rdr_pub.h>

#include <linux/hisi/rdr_hisi_ap_hook.h>
#include <soc_acpu_baseaddr_interface.h>
#include <pmic_interface.h>
#include <global_ddr_map.h>

/* 轨迹记录区 */
#define AP_TRACE_IRQ_SIZE			0x80000	/*512k */
#define AP_TRACE_TASK_SIZE			0x80000	/*512k */
#define AP_TRACE_CPU_IDLE_SIZE		0x40000	/*256K */
#define AP_TRACE_CPU_ON_OFF_SIZE	0x400	/*1k */
#define AP_TRACE_SYSCALL_SIZE		0x2000	/*8k */
#define AP_TRACE_HUNG_TASK_SIZE		0x1000	/*4k */
#define AP_TRACE_BUDD_FAIL_SIZE		0x1000	/*4k */
#define AP_TRACE_TASKLET_SIZE		0x2000	/*8k */
#define AP_TRACE_WORKER_SIZE		0x4000	/*16k */

/* 任务记录区 */
#define AP_LAST_TASK_STRUCT_SIZE    (NR_CPUS*0xAC0+0x200)	/*0x5800 //22k== 8 * 0xAC0 + 0.5k */
#define AP_LAST_TASK_STACK_SIZE     (NR_CPUS * THREAD_SIZE)	/*0x20000 //128k */

/* AP模块dump内存区 */
#define AP_DUMP_MEM_MODU_NOC_SIZE   0x1000
#define AP_DUMP_MEM_MODU_DDR_SIZE   0x2000
#define AP_DUMP_MEM_MODU_TMC_SIZE   0x20000	/* 128k for TMC */
#define AP_DUMP_MEM_MODU_GAP_SIZE   0x100	/*256byte空间作为gap，添加模块需要在此之前 */

#define REG_NAME_LEN 12
#define PRODUCT_VERSION_LEN 32
#define PRODUCT_DEVICE_LEN 32
#define REGS_DUMP_MAX_NUM   10
#define LOG_PATH_LEN    96
#define DEST_LOG_PATH_LEN    (LOG_PATH_LEN+10)
#define NEXT_LOG_PATH_LEN    (LOG_PATH_LEN+30)
#define AP_DUMP_MAGIC   0x19283746
#define BBOX_VERSION    0x10002	/*v1.0.2 */
#define AP_DUMP_END_MAGIC   0x1F2E3D4C
#define SIZE_1K         0x400
#define SYSTEM_BUILD_POP    "/system/build.prop"
#define AMNTN_MODULE_NAME_LEN 12
#define PMU_RESET_REG_MASK 0xFFFFFF00
#define RST_FLAG_MASK 0xFF
#define NMI_NOTIFY_LPM3_ADDR 0xFFF0A510
#define WDT_KICK_SLICE_TIMES    (3)

/*
PMU_RESET_REG_ADDR / FPGA_RESET_REG_ADDR 如下文件需要保持一致:
bootable\bootloader\legacy\include\reboot_reason.h
vendor\hisi\confidential\lpmcu\driver\psci\psci_task.c
kernel\drivers\hisi\mntn\blackbox\platform_ap\rdr_hisi_platform.h
*/
#define PMU_RESET_REG_ADDR (SOC_ACPU_PMU_SSI0_BASE_ADDR+(PMIC_HRST_REG0_ADDR(0)<<2))
#define FPGA_RESET_REG_ADDR ((HISI_RESERVED_MNTN_PHYMEM_BASE_UNIQUE)+0x288)	/* CAUSTIN: Confirm this definition is same as in fastboot */

/*记录panic时的pc指针和fpga上记录复位原因，前80个字节记录pc相关，后面20用作复位原因和冷启动判断*/
/* From 0x80--0x100, it records tmc trace data information */
#define PMU_RESET_RECORD_DDR_AREA_SIZE  0x100
#define ETR_TRACE_OFFSET_BBOX				0x80

#define RECORD_PC_STR_MAX_LENGTH 72
#define PSTORE_PATH            "/sys/fs/pstore/"
#define FASTBOOT_LOG_FILE      "/proc/balong/log/fastboot_log"
#define LAST_FASTBOOT_LOG_FILE "/proc/balong/log/last_fastboot_log"
#define MNTN_FILESYS_MAX_CYCLE    32	/*avoid loop forever! */
#define MNTN_FILESYS_PURE_DIR_NAME_LEN    64	/*the max length of pure name of a file or dir, that is, exclusive path */

typedef enum {
	MODID_AP_START            = HISI_BB_MOD_AP_START,
	MODID_AP_S_PANIC          = 0x80000001,
	MODID_AP_S_NOC            = 0x80000002,
	MODID_AP_S_PMU            = 0x80000003,
	MODID_AP_S_DDRC_SEC       = 0x80000004,
	MODID_AP_S_SMPL           = 0x80000005,
	MODID_AP_S_COMBINATIONKEY = 0x80000006,
	MODID_FASTBOOT_S_PANIC    = 0x80000007,
	MODID_AP_S_MAILBOX        = 0x80000008,
	MODID_AP_S_SCHARGER       = 0x80000009,
	MODID_AP_END              = HISI_BB_MOD_AP_END
} modid_ap;

/* 修改请与kernel/drivers/hisi/modem/drv/om/dump/rdr_adp.h保持一致*/
#define RDR_MODEM_NOC_MOD_ID 0x82000030
#define RDR_MODEM_DMSS_MOD_ID 0x82000031

typedef int (*rdr_hisiap_dump_func_ptr) (void *dump_addr, unsigned int size);

typedef struct {
	rdr_hisiap_dump_func_ptr dump_funcptr;
	unsigned char *dump_addr;
	unsigned int dump_size;
	char module_name[AMNTN_MODULE_NAME_LEN];
} module_dump_mem_info;

typedef enum {
	MODU_NOC,
	MODU_DDR,
	MODU_TMC,
	MODU_GAP,		/*256byte空间作为gap，添加模块需要在此之前 */
	MODU_MAX
} dump_mem_module;

typedef struct {
	char reg_name[12];
	u32 reg_size;
	u64 reg_base;
	void __iomem *reg_map_addr;
	unsigned char *reg_dump_addr;
} regs_info;

typedef struct {
	unsigned int dump_magic;
	unsigned char version[PRODUCT_VERSION_LEN];
	u32 modid;
	u32 e_exce_type;
	u64 coreid;
	u64 slice;
	struct rdr_register_module_result ap_rdr_info;
	unsigned int enter_times;	/* 重入计数，初始化为0，每次进入++； */

	unsigned int num_reg_regions;
	regs_info dump_regs_info[REGS_DUMP_MAX_NUM];

	unsigned char *hook_buffer_addr[HK_MAX];

	percpu_buffer_info hook_percpu_buffer[HK_PERCPU_TAG];

	unsigned char *last_task_struct_dump_addr[NR_CPUS];
	unsigned char *last_task_stack_dump_addr[NR_CPUS];

	char log_path[LOG_PATH_LEN];
	unsigned char *rdr_ap_area_map_addr;	/* rdr非配给ap内存的映射地址 */
	module_dump_mem_info module_dump_info[MODU_MAX];
	u64 wdt_kick_slice[WDT_KICK_SLICE_TIMES];
	unsigned char device_id[PRODUCT_DEVICE_LEN];
	u64 bbox_version;	/* 表示BBox版本信息 */
	unsigned int end_magic;	/* 标记结构体末尾，用于判断结构体范围 */
	char reserved[1];	/*sizeof(AP_EH_ROOT)=1024byte*/
} AP_EH_ROOT;			/*AP_EH_ROOT占用2K空间，通过get_rdr_hisiap_dump_addr函数预留 */

/*记录panic时的pc指针，传入fastboot，显示在屏幕上，此结构体修改需要和fastboot同步*/
typedef struct {
	char exception_info[RECORD_PC_STR_MAX_LENGTH];
	unsigned long exception_info_len;
} AP_RECORD_PC;

#ifdef CONFIG_HISI_CORESIGHT_TRACE
/* record ETR trace information */
#define		ETR_MAGIC_START		"ETRTRACE"
#define		ETR_MAGIC_SIZE		(sizeof(ETR_MAGIC_START))
#define		ETR_DUMP_NAME		"etr_dump.ad"
typedef struct {
	char magic[ETR_MAGIC_SIZE];
	u64 paddr;
	u32 size;
	u32 rd_offset;
} AP_RECORD_ETR;
void set_etr_trace_info(u64 paddr, u32 size, u32 offset);
#endif

/*外部可以使用的变量声明*/
extern int g_bbox_fpga_flag;
void get_product_version(char *version, size_t count);
void print_debug_info(void);
int rdr_hisiap_dump_init(struct rdr_register_module_result *retinfo);
void rdr_hisiap_dump(u32 modid, u32 etype, u64 coreid,
		     char *log_path, pfn_cb_dump_done pfn_cb);
int register_module_dump_mem_func(rdr_hisiap_dump_func_ptr func,
				  char *module_name, dump_mem_module modu);
bool rdr_get_ap_init_done(void);
unsigned long long get_pmu_reset_reg(void);
void hisiap_nmi_notify_lpm3(void);

/* 测试函数声明 */
void ap_exch_task_stack_dump(int taskPid);
void ap_exch_buf_show(unsigned int offset, unsigned int size);
void ap_exch_hex_dump(unsigned char *buf, unsigned int size,
		      unsigned char per_row);
int ap_exchUNDEF(void *arg);
int ap_exchSWI(void *arg);
int ap_exchPABT(void *arg);
int ap_exchDABT(void *arg);
