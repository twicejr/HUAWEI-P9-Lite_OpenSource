

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/delay.h>
#include <linux/rtc.h>
#include <linux/tty.h>

#include "plat_type.h"
#include "plat_debug.h"
#include "hw_bfg_ps.h"
#include "plat_pm.h"
#include "plat_pm_wlan.h"
#include "bfgx_exception_rst.h"
#include "plat_firmware.h"
#include "plat_uart.h"

#include "oal_sdio.h"
#include "oal_sdio_host_if.h"
#include "oal_hcc_host_if.h"

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
struct st_exception_info *g_pst_exception_info = NULL;
struct sdio_dump_bcpu_buff st_bcpu_dump_buff = {0};
oal_netbuf_stru*       st_bcpu_dump_netbuf = NULL;


uint8 *g_bfgx_mem_file_name[BFGX_MEM_DUMP_BLOCK_COUNT] =
                            {
                                "plat_nfc_stack",
                                "fgb_stack",
                                "bt_extra_mem",
                            };

struct st_exception_mem_info g_pst_bfgx_mem_dump[BFGX_MEM_DUMP_BLOCK_COUNT] = {{0},{0},{0}};
uint32 g_recvd_block_count = 0;

#define WIFI_PUB_REG_BLOCKS      (12)
#define WIFI_PRIV_REG_BLOCKS     (9)
#define WIFI_MEM_BLOCKS          (3)

#define WIFI_PUB_GLB_CTL_LEN              (4*1024)
#define WIFI_PUB_PMU_CMU_CTL_LEN          (4*1024)
#define WIFI_PUB_RF_WB_CTL_LEN            (2*1024)
#define WIFI_PUB_RF_WB_TRX_REG_LEN        (2*1024)
#define WIFI_PUB_RF_WB_PLL_REG_LEN        (2*1024)
#define WIFI_PUB_RF_FG_CTL_LEN            (2*1024)
#define WIFI_PUB_RF_FG_TRX_REG_LEN        (2*1024)
#define WIFI_PUB_RF_FG_PLL_REG_LEN        (2*1024)
#define WIFI_PUB_COEX_CTL_LEN             (1*1024)
#define WIFI_PUB_DIAG_CTL_LEN             (1*1024)
#define WIFI_PUB_COM_CTL_LEN              (2*1024)
#define WIFI_PUB_AON_GPIO_RTC_LEN         (16*1024)

#define WIFI_PUB_REG_TOTAL_LEN            (WIFI_PUB_GLB_CTL_LEN \
                                           + WIFI_PUB_PMU_CMU_CTL_LEN \
                                           + WIFI_PUB_RF_WB_CTL_LEN \
                                           + WIFI_PUB_RF_WB_TRX_REG_LEN \
                                           + WIFI_PUB_RF_WB_PLL_REG_LEN \
                                           + WIFI_PUB_RF_FG_CTL_LEN \
                                           + WIFI_PUB_RF_FG_TRX_REG_LEN \
                                           + WIFI_PUB_RF_FG_PLL_REG_LEN \
                                           + WIFI_PUB_COEX_CTL_LEN \
                                           + WIFI_PUB_DIAG_CTL_LEN \
                                           + WIFI_PUB_COM_CTL_LEN \
                                           + WIFI_PUB_AON_GPIO_RTC_LEN)

#define WIFI_PRIV_W_CTL_LEN               (1*1024)
#define WIFI_PRIV_W_WDT_LEN               (1*1024)
#define WIFI_PRIV_W_TIMER_LEN             (1*1024)
#define WIFI_PRIV_W_CPU_CTL_LEN           (1*1024)
#define WIFI_PRIV_W_PHY_BANK1_LEN         (1*1024)
#define WIFI_PRIV_W_PHY_BANK2_LEN         (1*1024)
#define WIFI_PRIV_W_PHY_BANK3_LEN         (1*1024)
#define WIFI_PRIV_W_PHY_BANK4_LEN         (1*1024)
#define WIFI_PRIV_W_MAC_BANK_LEN          (2*1024 + 512)
#define WIFI_PRIV_W_DMA_LEN               (1*1024)

#define WIFI_PRIV_REG_TOTAL_LEN           (WIFI_PRIV_W_CTL_LEN \
                                           + WIFI_PRIV_W_WDT_LEN \
                                           + WIFI_PRIV_W_TIMER_LEN \
                                           + WIFI_PRIV_W_CPU_CTL_LEN \
                                           + WIFI_PRIV_W_PHY_BANK1_LEN \
                                           + WIFI_PRIV_W_PHY_BANK2_LEN \
                                           + WIFI_PRIV_W_PHY_BANK3_LEN \
                                           + WIFI_PRIV_W_PHY_BANK4_LEN \
                                           + WIFI_PRIV_W_MAC_BANK_LEN \
                                           + WIFI_PRIV_W_DMA_LEN)

#define WIFI_MEM_W_TCM_WRAM_LEN           (512*1024)
#define WIFI_MEM_W_PKT_SHARE_RAM_LEN      (256*1024)
#define WIFI_MEM_B_SHARE_RAM_LEN          (64*1024)

#define WIFI_MEM_TOTAL_LEN                (WIFI_MEM_W_TCM_WRAM_LEN \
                                           + WIFI_MEM_W_PKT_SHARE_RAM_LEN \
                                           + WIFI_MEM_B_SHARE_RAM_LEN)

#define BFGX_PUB_REG_NUM                  (5)
#define BFGX_PRIV_REG_NUM                 (2)
#define BFGX_SHARE_RAM_NUM                (2)

#define BFGX_GLB_PMU_CMU_CTL_ADDR                       (0x50000000)
#define BFGX_RF_WB_CTL_ADDR                             (0x5000C000)
#define BFGX_RF_FG_CTL_ADDR                             (0x5000E000)
#define BFGX_COEX_DIAG_COM_CTL_ADDR                     (0x50010000)
#define BFGX_AON_WB_GPIO_RTC_ADDR                       (0x50006000)
#define BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_ADDR        (0x300E4000)
#define BFGX_W_SHARE_RAM_ADDR                           (0x30178000)
#define BFGX_GNSS_SUB_ADDR                              (0x38000000)
#define BFGX_B_CTL_WDT_TIMER_UART_ADDR                  (0x40000000)
#define BFGX_IR_SUB_ADDR                                (0x40007000)
#define BFGX_B_DMA_CFG_ADDR                             (0x40010000)
#define BFGX_BT_FM_SUB_ADDR                             (0x41040000)
#define BFGX_NFC_APB_ADDR                               (0x60000000)

#define BFGX_GLB_PMU_CMU_CTL_LEN                        (1024*12)
#define BFGX_RF_WB_CTL_LEN                              (1024*8)
#define BFGX_RF_FG_CTL_LEN                              (1024*8)
#define BFGX_COEX_DIAG_COM_CTL_LEN                      (1024*20)
#define BFGX_AON_WB_GPIO_RTC_LEN                        (1024*16)
#define BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_LEN         (1024*592)
#define BFGX_W_SHARE_RAM_LEN                            (1024*32)
#define BFGX_GNSS_SUB_LEN                               (1024*128)
#define BFGX_B_CTL_WDT_TIMER_UART_LEN                   (1024*20)
#define BFGX_IR_SUB_LEN                                 (1024*4)
#define BFGX_B_DMA_CFG_LEN                              (1024*4)
#define BFGX_BT_FM_SUB_LEN                              (1024*140)
#define BFGX_NFC_APB_LEN                                (1024*20)

#define GLB_PMU_CMU_CTL_FILE_NAME                       "glb_pmu_cmu_ctl"
#define RF_WB_CTL_FILE_NAME                             "rf_wb_ctl"
#define RF_FG_CTL_FILE_NAME                             "rf_fg_ctl"
#define COEX_DIAG_COM_CTL_FILE_NAME                     "coex_diag_com_ctl"
#define AON_WB_GPIO_RTC_FILE_NAME                       "aon_wb_gpio_rtc"
#define PATCH_PLAT_NFC_BFGNI_SHARE_RAM_FILE_NAME        "patch_plat_nfc_bfgni_share_ram"
#define W_SHARE_RAM_FILE_NAME                           "w_share_ram"
#define GNSS_SUB_FILE_NAME                              "gnss_sub"
#define B_CTL_WDT_TIMER_UART_FILE_NAME                  "b_ctl_wdt_timer_uart"
#define IR_SUB_FILE_NAME                                "ir_sub"
#define B_DMA_CFG_FILE_NAME                             "b_dma_cfg"
#define BT_FM_SUB_FILE_NAME                             "bt_fm_sub"
#define NFC_APB_FILE_NAME                               "nfc_apb"

struct st_uart_dump_wifi_mem_info g_ast_wifi_pub_reg_info[WIFI_PUB_REG_BLOCKS] =
{
    {"glb_ctl",       WIFI_PUB_GLB_CTL_LEN},
    {"pmu_cmu_ctl",   WIFI_PUB_PMU_CMU_CTL_LEN},
    {"rf_wb_ctl",     WIFI_PUB_RF_WB_CTL_LEN},
    {"rf_wb_trx_reg", WIFI_PUB_RF_WB_TRX_REG_LEN},
    {"rf_wb_pll_reg", WIFI_PUB_RF_WB_PLL_REG_LEN},
    {"rf_fg_ctl",     WIFI_PUB_RF_FG_CTL_LEN},
    {"rf_fg_trx_reg", WIFI_PUB_RF_FG_TRX_REG_LEN},
    {"rf_fg_pll_reg", WIFI_PUB_RF_FG_PLL_REG_LEN},
    {"coex_ctl",      WIFI_PUB_COEX_CTL_LEN},
    {"diag_ctl",      WIFI_PUB_DIAG_CTL_LEN},
    {"com_ctl",       WIFI_PUB_COM_CTL_LEN},
    {"aon_gpio_rtc",  WIFI_PUB_AON_GPIO_RTC_LEN},
};

struct st_uart_dump_wifi_mem_info g_ast_wifi_priv_reg_info[WIFI_PRIV_REG_BLOCKS] =
{
    {"w_ctl",         WIFI_PRIV_W_CTL_LEN},
    {"w_wdt",         WIFI_PRIV_W_WDT_LEN},
    {"w_timer",       WIFI_PRIV_W_TIMER_LEN},
    {"w_cpu_ctl",     WIFI_PRIV_W_CPU_CTL_LEN},
    {"w_phy_bank1",   WIFI_PRIV_W_PHY_BANK1_LEN},
    {"w_phy_bank2",   WIFI_PRIV_W_PHY_BANK2_LEN},
    {"w_phy_bank3",   WIFI_PRIV_W_PHY_BANK3_LEN},
    {"w_phy_bank4",   WIFI_PRIV_W_PHY_BANK4_LEN},
    {"w_mac_bank",    WIFI_PRIV_W_MAC_BANK_LEN},
    /*{"w_dma",         WIFI_PRIV_W_DMA_LEN},*/
};

struct st_uart_dump_wifi_mem_info g_ast_wifi_mem_info[WIFI_MEM_BLOCKS] =
{
    {"w_tcm_wram",      WIFI_MEM_W_TCM_WRAM_LEN},
    {"w_pkt_share_ram", WIFI_MEM_W_PKT_SHARE_RAM_LEN},
    {"b_share_ram",     WIFI_MEM_B_SHARE_RAM_LEN},
};

struct st_uart_dump_wifi_info g_uart_read_wifi_mem_info[UART_WIFI_MEM_DUMP_BOTTOM] =
{
    {SYS_CFG_READ_WLAN_PUB_REG,  WIFI_PUB_REG_TOTAL_LEN,  WIFI_PUB_REG_BLOCKS,  g_ast_wifi_pub_reg_info},
    {SYS_CFG_READ_WLAN_PRIV_REG, WIFI_PRIV_REG_TOTAL_LEN, WIFI_PRIV_REG_BLOCKS, g_ast_wifi_priv_reg_info},
    {SYS_CFG_READ_WLAN_MEM,      WIFI_MEM_TOTAL_LEN,      WIFI_MEM_BLOCKS,      g_ast_wifi_mem_info},
};

struct st_exception_mem_info g_pst_uart_wifi_mem_dump[UART_WIFI_MEM_DUMP_BOTTOM] = {{0},{0},{0}};
uint32 g_recvd_wifi_block_index = UART_WIFI_MEM_DUMP_BOTTOM;

struct st_bfgx_reset_cmd g_ast_bfgx_reset_msg[BFGX_BUTT] =
{
    {BT_RESET_CMD_LEN,   {0x04,0xff,0x01,0xc7}},
    {FM_RESET_CMD_LEN,   {0xfb}},
    {GNSS_RESET_CMD_LEN, {0xa1, 0xb4, 0xc7, 0x51, GNSS_SEPER_TAG_LAST}},/*seperate_tag = GNSS_SEPER_TAG_LAST，DTS2016011204428*/
    {IR_RESET_CMD_LEN,   {0}},
    {NFC_RESET_CMD_LEN,  {0}},
};

exception_bcpu_dump_msg g_sdio_read_bcpu_pub_reg_info[BFGX_PUB_REG_NUM] =
{
    {GLB_PMU_CMU_CTL_FILE_NAME,  BFGX_GLB_PMU_CMU_CTL_ADDR,   ALIGN_2_BYTE, BFGX_GLB_PMU_CMU_CTL_LEN},
    {RF_WB_CTL_FILE_NAME,        BFGX_RF_WB_CTL_ADDR,         ALIGN_2_BYTE, BFGX_RF_WB_CTL_LEN},
    {RF_FG_CTL_FILE_NAME,        BFGX_RF_FG_CTL_ADDR,         ALIGN_2_BYTE, BFGX_RF_FG_CTL_LEN},
    {COEX_DIAG_COM_CTL_FILE_NAME,BFGX_COEX_DIAG_COM_CTL_ADDR, ALIGN_2_BYTE, BFGX_COEX_DIAG_COM_CTL_LEN},
    {AON_WB_GPIO_RTC_FILE_NAME  ,BFGX_AON_WB_GPIO_RTC_ADDR,   ALIGN_2_BYTE, BFGX_AON_WB_GPIO_RTC_LEN},
};
exception_bcpu_dump_msg g_sdio_read_bcpu_mem_info[BFGX_SHARE_RAM_NUM] =
{
    {PATCH_PLAT_NFC_BFGNI_SHARE_RAM_FILE_NAME, BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_ADDR,
                                                                        ALIGN_1_BYTE, BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_LEN},
    {W_SHARE_RAM_FILE_NAME,                    BFGX_W_SHARE_RAM_ADDR,   ALIGN_1_BYTE, BFGX_W_SHARE_RAM_LEN},
};
exception_bcpu_dump_msg g_sdio_read_bcpu_priv_reg_info[BFGX_PRIV_REG_NUM] =
{
	/*私有寄存器只能拷贝2个*/
    //{GNSS_SUB_FILE_NAME,             BFGX_GNSS_SUB_ADDR,             ALIGN_2_BYTE, BFGX_GNSS_SUB_LEN},
    {B_CTL_WDT_TIMER_UART_FILE_NAME, BFGX_B_CTL_WDT_TIMER_UART_ADDR, ALIGN_2_BYTE, BFGX_B_CTL_WDT_TIMER_UART_LEN},
    {IR_SUB_FILE_NAME,               BFGX_IR_SUB_ADDR,               ALIGN_2_BYTE, BFGX_IR_SUB_LEN},
    //{B_DMA_CFG_FILE_NAME,            BFGX_B_DMA_CFG_ADDR,            ALIGN_2_BYTE, BFGX_B_DMA_CFG_LEN},
    //{BT_FM_SUB_FILE_NAME,            BFGX_BT_FM_SUB_ADDR,            ALIGN_2_BYTE, BFGX_BT_FM_SUB_LEN},
    //{NFC_APB_FILE_NAME,              BFGX_NFC_APB_ADDR,              ALIGN_2_BYTE, BFGX_NFC_APB_LEN},
};

exception_bcpu_dump_msg g_sdio_read_all[BFGX_PUB_REG_NUM + BFGX_SHARE_RAM_NUM + BFGX_PRIV_REG_NUM] =
{
    {GLB_PMU_CMU_CTL_FILE_NAME,  BFGX_GLB_PMU_CMU_CTL_ADDR,   ALIGN_2_BYTE, BFGX_GLB_PMU_CMU_CTL_LEN},
    {RF_WB_CTL_FILE_NAME,        BFGX_RF_WB_CTL_ADDR,         ALIGN_2_BYTE, BFGX_RF_WB_CTL_LEN},
    {RF_FG_CTL_FILE_NAME,        BFGX_RF_FG_CTL_ADDR,         ALIGN_2_BYTE, BFGX_RF_FG_CTL_LEN},
    {COEX_DIAG_COM_CTL_FILE_NAME,BFGX_COEX_DIAG_COM_CTL_ADDR, ALIGN_2_BYTE, BFGX_COEX_DIAG_COM_CTL_LEN},
    {AON_WB_GPIO_RTC_FILE_NAME  ,BFGX_AON_WB_GPIO_RTC_ADDR,   ALIGN_2_BYTE, BFGX_AON_WB_GPIO_RTC_LEN},
    {PATCH_PLAT_NFC_BFGNI_SHARE_RAM_FILE_NAME, BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_ADDR,
                                                                        ALIGN_1_BYTE, BFGX_PATCH_PLAT_NFC_BFGNI_SHARE_RAM_LEN},
    {W_SHARE_RAM_FILE_NAME,                    BFGX_W_SHARE_RAM_ADDR,   ALIGN_1_BYTE, BFGX_W_SHARE_RAM_LEN},
    //{GNSS_SUB_FILE_NAME,             BFGX_GNSS_SUB_ADDR,             ALIGN_2_BYTE, BFGX_GNSS_SUB_LEN},
    {B_CTL_WDT_TIMER_UART_FILE_NAME, BFGX_B_CTL_WDT_TIMER_UART_ADDR, ALIGN_2_BYTE, BFGX_B_CTL_WDT_TIMER_UART_LEN},
    {IR_SUB_FILE_NAME,               BFGX_IR_SUB_ADDR,               ALIGN_2_BYTE, BFGX_IR_SUB_LEN},
    //{BT_FM_SUB_FILE_NAME,            BFGX_BT_FM_SUB_ADDR,            ALIGN_2_BYTE, BFGX_BT_FM_SUB_LEN},
    //{NFC_APB_FILE_NAME,              BFGX_NFC_APB_ADDR,              ALIGN_2_BYTE, BFGX_NFC_APB_LEN},
    //{B_DMA_CFG_FILE_NAME,            BFGX_B_DMA_CFG_ADDR,            ALIGN_2_BYTE, BFGX_B_DMA_CFG_LEN},
};

uint8  g_plat_beatTimer_timeOut_reset_cfg = 0;
extern struct oal_sdio* oal_alloc_sdio_stru(oal_void);

/*****************************************************************************
  2 函数实现
*****************************************************************************/
void  bfgx_beat_timer_expire(uint64 data);
int32 get_exception_info_reference(struct st_exception_info **exception_data);
int32 plat_exception_handler(uint32 subsys_type, uint32 thread_type, uint32 exception_type);
void  plat_exception_reset_work(struct work_struct *work);
int32 wifi_exception_handler(void);
int32 wifi_subsystem_reset(void);
int32 wifi_system_reset(void);
int32 wifi_status_recovery(void);
int32 wifi_exception_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count, oal_int32 excep_type);
int32 bfgx_exception_handler(void);
int32 bfgx_subthread_reset(void);
int32 bfgx_subsystem_reset(void);
int32 bfgx_system_reset(void);
int32 bfgx_recv_dev_mem(uint8 *buf_ptr, uint16 count);
int32 bfgx_store_stack_mem_to_file(void);
void  bfgx_dump_stack(void);
int32 bfgx_status_recovery(void);
int32 plat_bfgx_exception_rst_register(struct ps_plat_s *data);
int32 plat_exception_reset_init(void);
int32 plat_exception_reset_exit(void);

/*****************************************************************************
 函 数 名  : plat_dfr_cfg_set
 功能描述  : dfr全局配置
 输入参数  : uint64 arg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
void plat_dfr_cfg_set(uint64 arg)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    pst_exception_data->exception_reset_enable = arg ? (PLAT_EXCEPTION_ENABLE) : (PLAT_EXCEPTION_DISABLE);

    PS_PRINT_INFO("plat dfr cfg set value = %ld\n", arg);
}

/*****************************************************************************
 函 数 名  : plat_beatTimer_timeOut_reset_cfg_set
 功能描述  : beat_timer全局配置
 输入参数  : uint64 arg，没有使用。
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
void plat_beatTimer_timeOut_reset_cfg_set(uint64 arg)
{
    g_plat_beatTimer_timeOut_reset_cfg = arg ? (PLAT_EXCEPTION_ENABLE) : (PLAT_EXCEPTION_DISABLE);
    PS_PRINT_INFO("plat beat timer timeOut reset cfg set value = %ld\n", arg);
}

/*****************************************************************************
 * Prototype    : mod_beat_timer
 * Description  :
 * input        : uint8
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/05/09
 *     Author       : wx145522
 *     Modification : Created function
*****************************************************************************/
int32 mod_beat_timer(uint8 on)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (on)
    {
        PS_PRINT_INFO("reset beat timer\n");
        mod_timer(&pst_exception_data->bfgx_beat_timer, jiffies + BFGX_BEAT_TIME * HZ);
        atomic_set(&pst_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);
    }
    else
    {
        PS_PRINT_INFO("delete beat timer\n");
        del_timer_sync(&pst_exception_data->bfgx_beat_timer);
    }

    return 0;
}

/***********************************************************************************
 函 数 名  : bfgx_beat_timer_expire
 功能描述  : bfgx心跳超时处理函数，该函数运行在软中断上下文中，不能有引起睡眠的操作
 输入参数  : uint64 data，不需要。加上是为了遵守内核的函数声明
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

***********************************************************************************/
void bfgx_beat_timer_expire(uint64 data)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;
    struct tty_buffer *thead;
    struct tty_bufhead *buf = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return;
    }

    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    /*bfgx睡眠时，没有心跳消息上报*/
    if (BFGX_SLEEP == ps_core_d->ps_pm->bfgx_dev_state_get())
    {
        PS_PRINT_INFO("bfgx has sleep!\n");
        return;
    }

    if (BFGX_NOT_RECV_BEAT_INFO == atomic_read(&pst_exception_data->bfgx_beat_flag))
    {
        if (IS_ERR_OR_NULL(ps_core_d->tty))
        {
            PS_PRINT_ERR("tty is NULL\n");
            return;
        }

        PS_PRINT_ERR("###########host can not recvive bfgx beat info@@@@@@@@@@@@@@!\n");
        ps_uart_state_pre(ps_core_d->tty);
        ps_uart_state_dump(ps_core_d->tty);

        if(NULL == ps_core_d->tty->port)
        {
            PS_PRINT_ERR("tty->port is null, bfgx download patch maybe failed!\n");
            return;
        }

        buf = &(ps_core_d->tty->port->buf);
        thead = buf->head;
        while (thead != NULL)
        {
            PS_PRINT_INFO("head is not null, memused=0x%x, size= 0x%x\n", buf->memory_used, thead->size);
            if (thead->used)
            {
                PS_PRINT_INFO("tty rx buf is not free\n");
            }
            thead = thead->next;
        }

        DECLARE_DFT_TRACE_KEY_INFO("bfgx beat timeout", OAL_DFT_TRACE_EXCEP);

        if (PLAT_EXCEPTION_ENABLE == g_plat_beatTimer_timeOut_reset_cfg)
        {
            PS_PRINT_ERR("bfgx beat timer bring to reset work!\n");
            //del_timer_sync(&ps_core_d->ps_pm->pm_priv_data->bfg_timer);
            plat_exception_handler(SUBSYS_BFGX, BFGX_THREAD_BOTTOM, BEAT_HEART_TIMEOUT);
            return;
        }
    }

    atomic_set(&pst_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);

    PS_PRINT_INFO("reset beat timer\n");
    mod_timer(&pst_exception_data->bfgx_beat_timer, jiffies + BFGX_BEAT_TIME * HZ);

    return;
}

/*****************************************************************************
 函 数 名  : get_exception_info_reference
 功能描述  : 获得保存异常信息的全局变量
 输入参数  : st_exception_info **exception结构体指针，保存全局变量地址的指针
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 get_exception_info_reference(struct st_exception_info **exception_data)
{
    if (NULL == exception_data)
    {
        PS_PRINT_ERR("%s parm exception_data is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    if (NULL == g_pst_exception_info)
    {
        *exception_data = NULL;
        PS_PRINT_ERR("%s g_pst_exception_info is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    *exception_data = g_pst_exception_info;

    return EXCEPTION_SUCCESS;
}

int32 uart_reset_wcpu(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EXCEPTION_FAIL;
    }

    if (pst_exception_data->subsys_type >= SUBSYS_BOTTOM)
    {
        PS_PRINT_ERR("subsys [%d] is error!\n", pst_exception_data->subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (EXCEPTION_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return -EXCEPTION_FAIL;
    }

    INIT_COMPLETION(ps_core_d->wait_wifi_opened);
    ps_uart_state_pre(ps_core_d->tty);

    if (SUBSYS_WIFI == pst_exception_data->subsys_type)
    {
        PS_PRINT_INFO("uart reset WCPU\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_EXCEP_RESET_WCPU);
    }
    else
    {
        PS_PRINT_INFO("uart open WCPU\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_WIFI);
    }

    timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_opened, msecs_to_jiffies(WAIT_WIFI_OPEN_TIME));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait wifi open ack timeout\n");
        post_to_visit_node(ps_core_d);
        return -EXCEPTION_FAIL;
    }

    post_to_visit_node(ps_core_d);

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : plat_power_fail_exception_info_set
 功能描述  : bfgx open失败时，调用该函数设置exception info
 输入参数  : subsys_type:调用异常处理的子系统，WIFI或者BFGX
             thread_type:子系统中的子线程
             exception_type:异常的类型
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_power_fail_exception_info_set(uint32 subsys_type, uint32 thread_type, uint32 exception_type)
{
    struct st_exception_info *pst_exception_data = NULL;
    uint64 flag;

    if (subsys_type >= SUBSYS_BOTTOM)
    {
        PS_PRINT_ERR("para subsys_type %u is error!\n", subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (((subsys_type == SUBSYS_WIFI) && (thread_type > WIFI_THREAD_BOTTOM))
     || ((subsys_type == SUBSYS_BFGX) && (thread_type > BFGX_THREAD_BOTTOM)))
    {
        PS_PRINT_ERR("para thread_type %u is error! subsys_type is %u\n", thread_type, subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (exception_type >= EXCEPTION_TYPE_BOTTOM)
    {
        PS_PRINT_ERR("para exception_type %u is error!\n", exception_type);
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_WARNING("palt exception reset not enable!");
        return -EXCEPTION_FAIL;
    }

    spin_lock_irqsave(&pst_exception_data->exception_spin_lock, flag);

    if (PLAT_EXCEPTION_RESET_IDLE == atomic_read(&pst_exception_data->is_reseting_device))
    {
        pst_exception_data->subsys_type   = subsys_type;
        pst_exception_data->thread_type   = thread_type;
        pst_exception_data->excetion_type = exception_type;

        /*当前异常没有处理完成之前，不允许处理新的异常*/
        atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_BUSY);
    }
    else
    {
        PS_PRINT_INFO("plat is processing exception! subsys=%d, exception type=%d\n",
                               pst_exception_data->subsys_type, pst_exception_data->excetion_type);
        spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);
        return -EXCEPTION_FAIL;
    }

    /*增加统计信息*/
    if (SUBSYS_WIFI == subsys_type)
    {
        pst_exception_data->wifi_exception_cnt += 1;
    }
    else
    {
        pst_exception_data->bfgx_exception_cnt += 1;
    }

    spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : plat_power_fail_process_done
 功能描述  : bfgx open失败时，异常处理完成
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
void plat_power_fail_process_done(void)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_IDLE);

    PS_PRINT_SUC("bfgx open fail process done\n");

    return;
}

/*****************************************************************************
 函 数 名  : plat_exception_handler
 功能描述  : 平台host异常处理总入口函数，填充异常信息，并触发异常处理work
 输入参数  : subsys_type:调用异常处理的子系统，WIFI或者BFGX
             thread_type:子系统中的子线程
             exception_type:异常的类型
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_handler(uint32 subsys_type, uint32 thread_type, uint32 exception_type)
{
    struct st_exception_info *pst_exception_data = NULL;
    uint64 flag;

    if (subsys_type >= SUBSYS_BOTTOM)
    {
        PS_PRINT_ERR("para subsys_type %u is error!\n", subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (((subsys_type == SUBSYS_WIFI) && (thread_type > WIFI_THREAD_BOTTOM))
     || ((subsys_type == SUBSYS_BFGX) && (thread_type > BFGX_THREAD_BOTTOM)))
    {
        PS_PRINT_ERR("para thread_type %u is error! subsys_type is %u\n", thread_type, subsys_type);
        return -EXCEPTION_FAIL;
    }

    if (exception_type >= EXCEPTION_TYPE_BOTTOM)
    {
        PS_PRINT_ERR("para exception_type %u is error!\n", exception_type);
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_INFO("plat exception reset not enable!");
        return EXCEPTION_SUCCESS;
    }

    /*这里只能用spin lock，因为该函数会被心跳超时函数调用，心跳超时函数属于软中断，不允许睡眠*/
    spin_lock_irqsave(&pst_exception_data->exception_spin_lock, flag);
    if (PLAT_EXCEPTION_RESET_IDLE == atomic_read(&pst_exception_data->is_reseting_device))
    {
        pst_exception_data->subsys_type   = subsys_type;
        pst_exception_data->thread_type   = thread_type;
        pst_exception_data->excetion_type = exception_type;

        /*当前异常没有处理完成之前，不允许处理新的异常*/
        atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_BUSY);
    }
    else
    {
        PS_PRINT_INFO("plat is processing exception! subsys=%d, exception type=%d\n",
                               pst_exception_data->subsys_type, pst_exception_data->excetion_type);
        spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);
        return EXCEPTION_SUCCESS;
    }
    spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);

    /*触发异常处理worker*/
    queue_work(pst_exception_data->plat_exception_rst_workqueue, &pst_exception_data->plat_exception_rst_work);

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL(plat_exception_handler);

/*****************************************************************************
 函 数 名  : plat_exception_reset_work
 功能描述  : 平台host异常处理work，判断产生异常的系统，调用相应的处理函数。
             这个函数会获取mutex，以避免并发处理。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
void plat_exception_reset_work(struct work_struct *work)
{
	int32  ret = -EXCEPTION_FAIL;
	struct st_exception_info *pst_exception_data = NULL;
	struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    mutex_lock(&pm_data->host_mutex);

	if (SUBSYS_WIFI == pst_exception_data->subsys_type)
	{
	    pst_exception_data->wifi_exception_cnt += 1;
		ret = wifi_exception_handler();
	}
	else
	{
	    pst_exception_data->bfgx_exception_cnt += 1;
		ret = bfgx_exception_handler();
	}

	if (ret != EXCEPTION_SUCCESS)
	{
		PS_PRINT_ERR("plat execption recovery fail! subsys_type = [%u], exception_type = [%u]\n",
		                               pst_exception_data->subsys_type, pst_exception_data->excetion_type);
	}
	else
	{
        PS_PRINT_SUC("plat execption recovery success!\n");
	}

    atomic_set(&pst_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_IDLE);

	mutex_unlock(&pm_data->host_mutex);

	return;
}

/*****************************************************************************
 函 数 名  : wifi_exception_handler
 功能描述  : wifi异常处理入口函数，判断BFGN是否打开，如果打开则调用单系统复位流程，
             BFGN没开则调用全系统复位流程(单系统复位需要用到uart)。如果单系统复位
             失败，则会进行全系统复位。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_exception_handler(void)
{
	int32 ret = -EXCEPTION_FAIL;
	uint32 exception_type;
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

	exception_type = pst_exception_data->excetion_type;

	/*如果bfgx已经打开，执行wifi子系统复位流程，否则执行wifi全系统复位流程*/
	if (!bfgx_is_shutdown())
	{
	    PS_PRINT_INFO("bfgx is opened, start wifi subsystem reset!\n");
		ret = wifi_subsystem_reset();
		if (EXCEPTION_SUCCESS != ret)
		{
            PS_PRINT_ERR("wifi subsystem reset failed, start wifi system reset!\n");
            ret = wifi_system_reset();
		}
	}
	else
	{
	    PS_PRINT_INFO("bfgx is not opened, start wifi system reset!\n");
		ret = wifi_system_reset();
	}

	if (ret != EXCEPTION_SUCCESS)
	{
		PS_PRINT_ERR("wifi execption recovery fail!\n");
		return ret;
	}

	if (NULL == pst_exception_data->wifi_callback->wifi_recovery_complete)
	{
        PS_PRINT_ERR("wifi recovery complete callback not regist\n");
        return -EXCEPTION_FAIL;
	}

	pst_exception_data->wifi_callback->wifi_recovery_complete();

    PS_PRINT_INFO("wifi recovery complete\n");

	return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : wifi_subsystem_reset
 功能描述  : wifi子系统复位，通过uart复位解复位WCPU,重新加载wifi firmware
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_subsystem_reset(void)
{
	struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    if (EXCEPTION_SUCCESS != uart_reset_wcpu())
    {
        PS_PRINT_ERR("uart reset wcpu failed\n");
        return -EXCEPTION_FAIL;
    }

    hcc_disable(hcc_get_default_handler(), OAL_TRUE);
    wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    if (EXCEPTION_SUCCESS != firmware_download_function(WIFI_CFG))
    {
        PS_PRINT_ERR("wifi firmware download failed\n");
        return -EXCEPTION_FAIL;
    }

    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);

    if (0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
    {
        PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
        return -EXCEPTION_FAIL;
    }

    hcc_enable(hcc_get_default_handler(), OAL_TRUE);

	return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : wifi_system_reset
 功能描述  : wifi全系统复位，对device重新上电，bfgn和wifi firmware重新加载，
 			 恢复全系统复位前bfgn的业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_system_reset(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return BFGX_POWER_FAILED;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    /*重新上电，firmware重新加载*/
    hcc_disable(hcc_get_default_handler(), OAL_TRUE);
    wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    if (!bfgx_is_shutdown())
    {
        del_timer_sync(&ps_core_d->ps_pm->pm_priv_data->bfg_timer);
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);    
        release_tty_drv(ps_core_d->pm_data);
    }

    PS_PRINT_INFO("wifi system reset, board power on\n");
    board_power_on();

    if (EXCEPTION_SUCCESS != firmware_download_function(BFGX_AND_WIFI_CFG))
    {
        PS_PRINT_ERR("hi110x system power reset failed!\n");
        return -EXCEPTION_FAIL;
    }

    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);

    if (0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
    {
        PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
        return -EXCEPTION_FAIL;
    }

    hcc_enable(hcc_get_default_handler(), OAL_TRUE);

    if (!bfgx_is_shutdown())
    {
        INIT_COMPLETION(pm_data->dev_bootok_ack_comp);
        atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

        if (0 !=open_tty_drv(ps_core_d->pm_data))
        {
            PS_PRINT_ERR("open_tty_drv failed\n");
            return -EXCEPTION_FAIL;
        }

        if (EXCEPTION_SUCCESS != wlan_pm_open_bcpu())
        {
            PS_PRINT_ERR("wifi reset bcpu fail\n");
            release_tty_drv(ps_core_d->pm_data);
            atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);
            return -EXCEPTION_FAIL;
        }

        timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
        if (!timeleft)
        {
            PS_PRINT_ERR("wait bfgx boot ok timeout\n");
            atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);
            return  -FAILURE;
        }

        atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);

        bfgx_pm_feature_set();

        /*恢复bfgx业务状态*/
        if (EXCEPTION_SUCCESS != bfgx_status_recovery())
        {
            PS_PRINT_ERR("bfgx status revocery failed!\n");
            return -EXCEPTION_FAIL;
        }
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : wifi_status_recovery
 功能描述  : 全系统复位以后，恢复wifi业务函数
 输入参数  : st_exception_info *exception结构体指针，保存了异常产生的系统wifi
             还是BFGN，对于BFGN还保存了产生异常的子业务，以及异常的类型
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_status_recovery(void)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

	if (EXCEPTION_SUCCESS != wifi_subsystem_reset())
	{
        PS_PRINT_ERR("wifi subsystem reset failed\n");
        return -EXCEPTION_FAIL;
	}

	if (NULL == pst_exception_data->wifi_callback->wifi_recovery_complete)
	{
        PS_PRINT_ERR("wifi recovery complete callback not regist\n");
        return -EXCEPTION_FAIL;
	}

	pst_exception_data->wifi_callback->wifi_recovery_complete();

    PS_PRINT_INFO("wifi recovery complete\n");

	return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : wifi_open_bcpu_set
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_open_bcpu_set(uint8 enable)
{
    struct st_exception_info *pst_exception_data = NULL;
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (!enable)
    {
        PS_PRINT_INFO("wifi_open_bcpu_enable flag disable\n");
        pst_exception_data->wifi_open_bcpu_enable = false;
        return EXCEPTION_SUCCESS;
    }

    PS_PRINT_INFO("wifi_open_bcpu_enable flag enable\n");
    pst_exception_data->wifi_open_bcpu_enable = true;

    mutex_lock(&pm_data->host_mutex);

    if (SUCCESS != release_tty_drv(ps_core_d->pm_data))
    {
        PS_PRINT_ERR("close tty is err!");
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }

    if (SUCCESS != open_tty_drv(ps_core_d->pm_data))
    {
        PS_PRINT_ERR("open tty is err!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }

    if(OAL_SUCC != wlan_pm_open_bcpu())
    {
        mutex_unlock(&pm_data->host_mutex);
        return  -EXCEPTION_FAIL;
    }

    timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait BFGX boot ok timeout\n");
        mutex_unlock(&pm_data->host_mutex);
        return  -EXCEPTION_FAIL;
    }

    mutex_unlock(&pm_data->host_mutex);

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL(wifi_open_bcpu_set);

/*****************************************************************************
 函 数 名  : wifi_exception_mem_dump
 功能描述  : 全系统复位，firmware重新加载的时候，导出device指定地址的内存
 输入参数  : pst_mem_dump_info  : 需要读取的内存信息
             count              : 需要读取的内存块个数
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_exception_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count, oal_int32 excep_type)
{
    int32 ret;
    uint64 timeleft;
    struct st_exception_info *pst_exception_data = NULL;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EXCEPTION_FAIL;
    }

    if(WIFI_DEVICE_PANIC != excep_type && SDIO_TRANS_FAIL != excep_type)
    {
        PS_PRINT_ERR("unsupport exception type :%d\n", excep_type);
        return -EXCEPTION_FAIL;
    }

    mutex_lock(&pm_data->host_mutex);

    if(WIFI_DEVICE_PANIC != excep_type)
    {
        /*If sdio transfer failed, reset wcpu first*/
        if (!bfgx_is_shutdown())
        {
            if (prepare_to_visit_node(ps_core_d) < 0)
            {
                PS_PRINT_ERR("prepare work FAIL\n");
                mutex_unlock(&pm_data->host_mutex);
                return -EXCEPTION_FAIL;
            }

            /*bcpu is power on, reset wcpu by bcpu*/
            INIT_COMPLETION(ps_core_d->wait_wifi_opened);
            ps_uart_state_pre(ps_core_d->tty);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DUMP_RESET_WCPU);
            timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_opened, msecs_to_jiffies(WAIT_WIFI_OPEN_TIME));
            if (!timeleft)
            {
                ps_uart_state_dump(ps_core_d->tty);
                PS_PRINT_ERR("wait wifi open ack timeout\n");
                post_to_visit_node(ps_core_d);
                mutex_unlock(&pm_data->host_mutex);
                return -EXCEPTION_FAIL;
            }
            else
            {
                PS_PRINT_INFO("reset wifi by uart sucuess\n");
                post_to_visit_node(ps_core_d);
            }
        }
        else
        {
            PS_PRINT_INFO("bfgx did't opened, repower wifi directly\n");
            mutex_unlock(&pm_data->host_mutex);
            return -EXCEPTION_FAIL;
        }
    }

    oal_sdio_claim_host(oal_get_sdio_default_handler());
    ret = sdio_reinit();
    if (ret < 0)
    {
        oal_sdio_release_host(oal_get_sdio_default_handler());
        PS_PRINT_ERR("wifi mem dump:sdio reinit failed, ret=[%d]\n", ret);
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }

    ret = sdio_device_mem_dump(pst_mem_dump_info, count);
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);
    oal_sdio_release_host(oal_get_sdio_default_handler());
    if (ret < 0)
    {
        PS_PRINT_ERR("sdio_device_mem_dump failed, ret=[%d]\n", ret);
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }

    mutex_unlock(&pm_data->host_mutex);

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL(wifi_exception_mem_dump);

/*****************************************************************************
 函 数 名  : wifi_exception_work_submit
 功能描述  : 异常恢复动作触发接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_exception_work_submit(uint32 wifi_excp_type)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_INFO("palt exception reset not enable!");
        return EXCEPTION_SUCCESS;
    }

#ifdef _PRE_WLAN_FEATURE_DFR
    if(work_busy(&g_pst_exception_info->wifi_excp_worker))
    {
        PS_PRINT_WARNING("WIFI DFR %pF Worker is Processing...need't submit\n",(void*)g_pst_exception_info->wifi_excp_worker.func);
        return -OAL_EBUSY;
    }
    else if (work_busy(&g_pst_exception_info->wifi_excp_recovery_worker))
    {
        PS_PRINT_WARNING("WIFI DFR %pF Recovery_Worker is Processing...need't submit\n",(void*)g_pst_exception_info->wifi_excp_worker.func);
        return -OAL_EBUSY;
    }
    else
    {
        PS_PRINT_ERR("WiFi DFR %pF Worker Submit, excp_type[%d]\n",(void*)g_pst_exception_info->wifi_excp_worker.func, wifi_excp_type);
        g_pst_exception_info->wifi_excp_type = wifi_excp_type;
        queue_work(g_pst_exception_info->wifi_exception_workqueue, &g_pst_exception_info->wifi_excp_worker);
    }
#else
    PS_PRINT_WARNING("Geting WIFI DFR, but _PRE_WLAN_FEATURE_DFR not open!");
#endif //_PRE_WLAN_FEATURE_DFR
    return OAL_SUCC;

}
EXPORT_SYMBOL(g_pst_exception_info);
EXPORT_SYMBOL(wifi_exception_work_submit);

oal_workqueue_stru* wifi_get_exception_workqueue(oal_void)
{
    if(NULL == g_pst_exception_info)
    {
        return NULL;
    }
    return g_pst_exception_info->wifi_exception_workqueue;
}
EXPORT_SYMBOL(wifi_get_exception_workqueue);

/*****************************************************************************
 函 数 名  : wifi_exception_mem_dump
 功能描述  : 全系统复位，firmware重新加载的时候，导出device指定地址的内存
 输入参数  : pst_mem_dump_info  : 需要读取的内存信息
             count              : 需要读取的内存块个数
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 prepare_to_recv_bfgx_stack(uint32 len)
{
    if (g_recvd_block_count > BFGX_MEM_DUMP_BLOCK_COUNT - 1)
    {
        PS_PRINT_ERR("bfgx mem dump have recvd [%d] blocks\n", g_recvd_block_count);
        return -EXCEPTION_FAIL;
    }

    if (NULL == g_pst_bfgx_mem_dump[g_recvd_block_count].exception_mem_addr)
    {
        g_pst_bfgx_mem_dump[g_recvd_block_count].exception_mem_addr = (uint8 *)OS_KMALLOC_GFP(len);
        if (NULL == g_pst_bfgx_mem_dump[g_recvd_block_count].exception_mem_addr)
        {
            PS_PRINT_ERR("prepare mem to recv bfgx stack failed\n");
            return -EXCEPTION_FAIL;
        }
        else
        {
            g_pst_bfgx_mem_dump[g_recvd_block_count].recved_size = 0;
            g_pst_bfgx_mem_dump[g_recvd_block_count].total_size  = len;
            g_pst_bfgx_mem_dump[g_recvd_block_count].file_name   = g_bfgx_mem_file_name[g_recvd_block_count];
            PS_PRINT_INFO("prepare mem [%d] to recv bfgx stack\n", len);
        }
    }

    return EXCEPTION_SUCCESS;
}

int32 free_bfgx_stack_dump_mem(void)
{
    uint32 i = 0;

    for (i = 0; i < BFGX_MEM_DUMP_BLOCK_COUNT; i++)
    {
        if (NULL != g_pst_bfgx_mem_dump[i].exception_mem_addr)
        {
            OS_MEM_KFREE(g_pst_bfgx_mem_dump[i].exception_mem_addr);
            g_pst_bfgx_mem_dump[i].recved_size = 0;
            g_pst_bfgx_mem_dump[i].total_size  = 0;
            g_pst_bfgx_mem_dump[i].file_name   = NULL;
            g_pst_bfgx_mem_dump[i].exception_mem_addr = NULL;
        }
    }

    g_recvd_block_count = 0;

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_exception_handler
 功能描述  : bfgx异常处理入口函数，根据异常类型，调用不同的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_exception_handler(void)
{
	int32  ret = -EXCEPTION_FAIL;
	uint32 exception_type;
    struct st_exception_info *pst_exception_data = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

	exception_type = pst_exception_data->excetion_type;

    /* we do NOT need bfg timer anymore */
    del_timer_sync(&pm_data->bfg_timer);

	/*ioctl下来的异常执行线程复位流程*/
	if (exception_type == TIMER_TIMEOUT || exception_type == ARP_TIMEOUT)
	{
		ret = bfgx_subthread_reset();
	}
	else
	{
        /*异常恢复之前，尝试用平台命令读栈，不能保证一定成功，因为此时uart可能不通*/
        bfgx_dump_stack();
		ret = bfgx_subsystem_reset();
	}

	if (EXCEPTION_SUCCESS != ret)
	{
		PS_PRINT_ERR("bfgx exception recovery fail!, exception_type = [%u]\n", exception_type);
		del_timer_sync(&pm_data->bfg_timer);
		return ret;
	}

	return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_subthread_reset
 功能描述  : bfgx子线程复位函数，通过uart下发复位子线程命令，并等待复位
             成功ACK，收到ACK，异常处理完成，否则进入BFGX子系统复位流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_subthread_reset(void)
{
	int32  ret = -EXCEPTION_FAIL;
	uint32 subsys, subthread;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    subsys    = pst_exception_data->subsys_type;
    subthread = pst_exception_data->thread_type;

	/*uart 发送复位子业务命令*/

	/*等待子业务复位成功ACK*/

	if (EXCEPTION_SUCCESS != ret)
	{
		PS_PRINT_INFO("bfgx subthread reset fail! start subsystem reset!\n");
		ret = bfgx_subsystem_reset();

		if (EXCEPTION_SUCCESS != ret)
		{
			PS_PRINT_ERR("bfgx subsystem reset fail!\n");
			return -EXCEPTION_FAIL;
		}
	}

	return EXCEPTION_SUCCESS;
}

int32 wifi_reset_bfgx(void)
{
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (EXCEPTION_SUCCESS != wlan_pm_shutdown_bcpu_cmd())
    {
        PS_PRINT_ERR("wifi shutdown bcpu fail\n");
        return -EXCEPTION_FAIL;
    }

    INIT_COMPLETION(pm_data->dev_bootok_ack_comp);

    if (EXCEPTION_SUCCESS != wlan_pm_open_bcpu())
    {
        PS_PRINT_ERR("wifi reset bcpu fail\n");
        return -EXCEPTION_FAIL;
    }

    timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait bfgx boot ok timeout\n");
        return  -EXCEPTION_FAIL;
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : __bfgx_subsystem_reset
 功能描述  : bfgx子系统复位函数，进入该函数，说明wifi已开，通过sdio下发复位
             解复位BCPU命令，进行bfgx子系统复位。子系统复位完成以后需要恢复
             复位前bfgin的业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 __bfgx_subsystem_reset(void)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EXCEPTION_FAIL;
    }

    if (false == ps_chk_bfg_active(ps_core_d))
    {
        PS_PRINT_ERR("bfgx no subsys is opened\n");
        return EXCEPTION_SUCCESS;
    }

    if (EXCEPTION_SUCCESS != release_tty_drv(ps_core_d->pm_data))
    {
        PS_PRINT_ERR("close tty is err!\n");
        return -EXCEPTION_FAIL;
    }

    if (EXCEPTION_SUCCESS != open_tty_drv(ps_core_d->pm_data))
    {
        PS_PRINT_ERR("open tty is err!\n");
        return -EXCEPTION_FAIL;
    }

    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    if (EXCEPTION_SUCCESS != wifi_reset_bfgx())
    {
        PS_PRINT_ERR("wifi reset bfgx fail\n");
        atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);
        return -EXCEPTION_FAIL;
    }

    atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);

    bfgx_pm_feature_set();

    if (EXCEPTION_SUCCESS != bfgx_status_recovery())
    {
        PS_PRINT_ERR("bfgx recovery status failed\n");
        return -EXCEPTION_FAIL;
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_subsystem_reset
 功能描述  : bfgx子系统复位函数，如果wifi打开，则通过sdio下发复位解复位BCPU命令，
             进行bfgx子系统复位，wifi没开，进入bfgx全系统复位流程。如果子系统
             复位不能将异常恢复也会进入全系统复位流程。子系统复位完成以后需要
             恢复复位前bfgin的业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_subsystem_reset(void)
{
	if (!wlan_is_shutdown())
	{
	    PS_PRINT_INFO("wifi is opened, start bfgx subsystem reset!\n");
        if (EXCEPTION_SUCCESS != __bfgx_subsystem_reset())
        {
            PS_PRINT_ERR("bfgx subsystem reset failed, start bfgx system reset!\n");
            return bfgx_system_reset();
        }

        return EXCEPTION_SUCCESS;
	}
	else
	{
	    PS_PRINT_INFO("wifi is not opened, start bfgx system reset!\n");
		return bfgx_system_reset();
	}
}

int32 bfgx_power_reset(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    release_tty_drv(ps_core_d->pm_data);

    PS_PRINT_INFO("bfgx system reset, board power on\n");
    board_power_on();

    open_tty_drv(ps_core_d->pm_data);

    INIT_COMPLETION(pm_data->dev_bootok_ack_comp);
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    if (EXCEPTION_SUCCESS != firmware_download_function(BFGX_CFG))
    {
        oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
        PS_PRINT_ERR("bfgx power reset failed!\n");
        atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);
        return -EXCEPTION_FAIL;
    }
    oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);

    timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait bfgx boot ok timeout\n");
        atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);
        return  -EXCEPTION_FAIL;
    }

    atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);

    bfgx_pm_feature_set();

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_system_reset
 功能描述  : bfgin全系统复位函数，对device重新上电，wifi和bfgin firmware重新
             加载，恢复wifi，恢复bfgin业务。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_system_reset(void)
{
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (!wlan_is_shutdown())
    {
        if (NULL != pst_exception_data->wifi_callback->notify_wifi_to_recovery)
        {
            PS_PRINT_INFO("notify wifi bfgx start to power reset\n");
            pst_exception_data->wifi_callback->notify_wifi_to_recovery();
        }
    }

    /*重新上电，firmware重新加载*/
    if (EXCEPTION_SUCCESS != bfgx_power_reset())
    {
        PS_PRINT_ERR("bfgx power reset failed!\n");
        return -EXCEPTION_FAIL;
    }

    if (EXCEPTION_SUCCESS != bfgx_status_recovery())
    {
        PS_PRINT_ERR("bfgx status revocery failed!\n");
        return -EXCEPTION_FAIL;
    }

    if (!wlan_is_shutdown())
    {
        if (EXCEPTION_SUCCESS != wifi_status_recovery())
        {
            PS_PRINT_ERR("wifi status revocery failed!\n");
            return -EXCEPTION_FAIL;
        }
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_recv_dev_mem
 功能描述  : 接收bfgx异常时，device上报的栈内存
 输入参数  : buf_ptr :uart接收到的占内存bufer首地址
             count   :buffer长度
 输出参数  : 0表示成功，-1表示失败
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_recv_dev_mem(uint8 *buf_ptr, uint16 count)
{
    struct st_exception_mem_info *pst_mem_info = NULL;
    uint32 offset = 0;

    if (NULL == buf_ptr)
    {
        PS_PRINT_ERR("buf_ptr is NULL\n");
        return -EFAIL;
    }

    pst_mem_info = &(g_pst_bfgx_mem_dump[g_recvd_block_count]);

    if (NULL == pst_mem_info->exception_mem_addr)
    {
        PS_PRINT_ERR("mem addr is null, g_recvd_block_count=[%d]\n", g_recvd_block_count);
        return -EXCEPTION_FAIL;
    }

    offset = pst_mem_info->recved_size;
    if (offset + count > pst_mem_info->total_size)
    {
        PS_PRINT_ERR("outof buf total size, recved size is [%d], curr recved size is [%d], total size is [%d]\n", offset, count, pst_mem_info->total_size);
        return -EXCEPTION_FAIL;
    }
    else
    {
        PS_PRINT_INFO("cpy stack size [%d] to exception mem\n", count);
        OS_MEM_CPY(pst_mem_info->exception_mem_addr + offset, buf_ptr, count);
        pst_mem_info->recved_size += count;
    }

    if (pst_mem_info->recved_size == pst_mem_info->total_size)
    {
        g_recvd_block_count++;
        PS_PRINT_INFO("mem block [%d] recvd done\n", g_recvd_block_count);
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_store_stack_mem_to_file
 功能描述  : 将接收到的bfgx内存保存到文件中
 输入参数  : 无
 输出参数  : 0表示成功，-1表示失败
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_store_stack_mem_to_file(void)
{
    OS_KERNEL_FILE_STRU *fp;
    char filename[100] = {0};
    struct timeval tv;
    struct rtc_time tm;
    int32 l_ret;
    uint32 i;
    mm_segment_t fs;
    struct st_exception_mem_info *pst_mem_info = NULL;

    do_gettimeofday(&tv);
    rtc_time_to_tm(tv.tv_sec, &tm);
    PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
               tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    for (i = 0; i < BFGX_MEM_DUMP_BLOCK_COUNT; i++)
    {
        pst_mem_info = &(g_pst_bfgx_mem_dump[i]);
        if (NULL == pst_mem_info->exception_mem_addr)
        {
            PS_PRINT_ERR("mem addr is null, i=[%d]\n", i);
            continue;
        }

        OS_MEM_SET(filename, 0, sizeof(filename));
        snprintf(filename, sizeof(filename),"/data/memdump/%04d%02d%02d%02d%02d%02d_%s.bin",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, pst_mem_info->file_name);

        /*打开文件，准备保存接收到的内存*/
        fp = filp_open(filename, O_RDWR | O_CREAT, 0777);
        if (IS_ERR_OR_NULL(fp))
        {
            PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
            continue;
        }

        /*将接收到的内存写入到文件中*/
        fs = get_fs();
        set_fs(KERNEL_DS);
        l_ret = vfs_llseek(fp, 0, SEEK_END);
        PS_PRINT_INFO("pos = %d\n", (int)fp->f_pos);
        vfs_write(fp, pst_mem_info->exception_mem_addr, pst_mem_info->recved_size, &fp->f_pos);
        set_fs(fs);

        filp_close(fp, NULL);
    }

    free_bfgx_stack_dump_mem();

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_dump_stack
 功能描述  : 心跳超时时，尝试通过uart读栈，不保证一定能成功，因为此时uart可能不通
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
void bfgx_dump_stack(void)
{
    uint64 timeleft;
    uint32 exception_type;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    exception_type = pst_exception_data->excetion_type;

    if ((exception_type != BEAT_HEART_TIMEOUT) && (exception_type != LAST_WORD))
	{
	    return;
	}

    if (unlikely(NULL == pst_exception_data->ps_plat_d))
    {
        PS_PRINT_ERR("pst_exception_data->ps_plat_d is NULL\n");
        return;
    }
    ps_core_d = pst_exception_data->ps_plat_d->core_data;

    INIT_COMPLETION(pst_exception_data->wait_read_bfgx_stack);

    /*心跳超时需要host主动发命令去读内存，临终遗言只需要等待device将内存上报上来*/
    if (exception_type == BEAT_HEART_TIMEOUT)
    {
        ps_uart_state_pre(ps_core_d->tty);
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_READ_STACK);
    }

    /*等待读栈操作完成*/
    timeleft = wait_for_completion_timeout(&pst_exception_data->wait_read_bfgx_stack, msecs_to_jiffies(WAIT_BFGX_READ_STACK_TIME));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("read bfgx stack failed!\n");
    }
    else
    {
        PS_PRINT_INFO("read bfgx stack success!\n");
    }

    bfgx_store_stack_mem_to_file();

    return;
}

int32 prepare_to_recv_wifi_mem(void)
{
    uint32 malloc_mem_len;
    uint32 index;

    PS_PRINT_INFO("%s\n", __func__);

    index = g_recvd_wifi_block_index;
    if (index >= UART_WIFI_MEM_DUMP_BOTTOM)
    {
        PS_PRINT_ERR("g_recvd_wifi_block_index is error [%d]\n", index);
        return -EXCEPTION_FAIL;
    }

    if (NULL == g_pst_uart_wifi_mem_dump[index].exception_mem_addr)
    {
        malloc_mem_len = g_uart_read_wifi_mem_info[index].total_size;
        g_pst_uart_wifi_mem_dump[index].exception_mem_addr = (uint8 *)OS_VMALLOC_GFP(malloc_mem_len);
        if (NULL == g_pst_uart_wifi_mem_dump[index].exception_mem_addr)
        {
            PS_PRINT_ERR("prepare mem to recv wifi mem failed\n");
            return -EXCEPTION_FAIL;
        }
        else
        {
            g_pst_uart_wifi_mem_dump[index].recved_size = 0;
            g_pst_uart_wifi_mem_dump[index].total_size  = malloc_mem_len;
            g_pst_uart_wifi_mem_dump[index].file_name   = NULL;
            PS_PRINT_INFO("prepare mem [%d] to recv wifi mem, index = [%d]\n", malloc_mem_len, index);
        }
    }

    return EXCEPTION_SUCCESS;
}

int32 free_uart_read_wifi_mem(void)
{
    uint32 index;

    PS_PRINT_INFO("%s\n", __func__);

    index = g_recvd_wifi_block_index;
    if (index >= UART_WIFI_MEM_DUMP_BOTTOM)
    {
        PS_PRINT_ERR("g_recvd_wifi_block_index is error [%d]\n", index);
        return -EXCEPTION_FAIL;
    }

    if (NULL != g_pst_uart_wifi_mem_dump[index].exception_mem_addr)
    {
        OS_MEM_VFREE(g_pst_uart_wifi_mem_dump[index].exception_mem_addr);
        g_pst_uart_wifi_mem_dump[index].recved_size        = 0;
        g_pst_uart_wifi_mem_dump[index].total_size         = 0;
        g_pst_uart_wifi_mem_dump[index].exception_mem_addr = NULL;
        PS_PRINT_INFO("vfree uart read wifi mem [%d] success\n", index);
    }

    g_recvd_wifi_block_index = UART_WIFI_MEM_DUMP_BOTTOM;

    return EXCEPTION_SUCCESS;
}

int32 uart_recv_wifi_mem(uint8 *buf_ptr, uint16 count)
{
    struct st_exception_mem_info *pst_mem_info = NULL;
    uint32 offset = 0;
    uint32 index;

    if (NULL == buf_ptr)
    {
        PS_PRINT_ERR("buf_ptr is NULL\n");
        return -EFAIL;
    }

    index = g_recvd_wifi_block_index;
    if (index >= UART_WIFI_MEM_DUMP_BOTTOM)
    {
        PS_PRINT_ERR("g_recvd_wifi_block_index [%d] is error\n", index);
        return -EXCEPTION_FAIL;
    }

    pst_mem_info = &(g_pst_uart_wifi_mem_dump[index]);

    if (NULL == pst_mem_info->exception_mem_addr)
    {
        PS_PRINT_ERR("mem addr is null, g_recvd_block_count=[%d]\n", index);
        return -EXCEPTION_FAIL;
    }

    offset = pst_mem_info->recved_size;
    if (offset + count > pst_mem_info->total_size)
    {
        PS_PRINT_ERR("outof buf total size, index=[%d], recved size is [%d], curr recved size is [%d], total size is [%d]\n", index, offset, count, pst_mem_info->total_size);
        return -EXCEPTION_FAIL;
    }
    else
    {
        PS_PRINT_INFO("cpy wifi mem size [%d] to recv buffer\n", count);
        OS_MEM_CPY(pst_mem_info->exception_mem_addr + offset, buf_ptr, count);
        pst_mem_info->recved_size += count;
        PS_PRINT_INFO("index [%d] have recved size is [%d], total size is [%d]\n", index, pst_mem_info->recved_size, pst_mem_info->total_size);
    }

    return EXCEPTION_SUCCESS;
}

int32 __store_wifi_mem_to_file(void)
{
    OS_KERNEL_FILE_STRU *fp;
    char filename[100] = {0};
    struct timeval tv;
    struct rtc_time tm;
    int32 l_ret;
    mm_segment_t fs;
    uint32 index;
    uint32 i;
    uint32 block_count;
    uint8 *block_file_name;
    uint32 block_size;
    uint32 offset = 0;
    struct st_exception_mem_info *pst_mem_info = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    do_gettimeofday(&tv);
    rtc_time_to_tm(tv.tv_sec, &tm);
    PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
               tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    index = g_recvd_wifi_block_index;
    if (index >= UART_WIFI_MEM_DUMP_BOTTOM)
    {
        PS_PRINT_ERR("g_recvd_wifi_block_index [%d] is error\n", index);
        return -EXCEPTION_FAIL;
    }

    pst_mem_info = &(g_pst_uart_wifi_mem_dump[index]);
    if (NULL == pst_mem_info->exception_mem_addr)
    {
        PS_PRINT_ERR("mem addr is null, g_recvd_wifi_block_index=[%d]", index);
        return -EXCEPTION_FAIL;
    }

    block_count = g_uart_read_wifi_mem_info[index].block_count;

    for (i = 0; i < block_count; i++)
    {
        block_size      = g_uart_read_wifi_mem_info[index].block_info[i].size;
        block_file_name = g_uart_read_wifi_mem_info[index].block_info[i].file_name;

        snprintf(filename, sizeof(filename),"/data/memdump/%04d%02d%02d%02d%02d%02d_%s.bin",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, block_file_name);

        /*打开文件，准备保存接收到的内存*/
        fp = filp_open(filename, O_RDWR | O_CREAT, 0777);
        if (IS_ERR_OR_NULL(fp))
        {
            PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
            return -EXCEPTION_FAIL;
        }

        /*将接收到的内存写入到文件中*/
        fs = get_fs();
        set_fs(KERNEL_DS);
        l_ret = vfs_llseek(fp, 0, SEEK_END);
        PS_PRINT_INFO("pos = %d\n", (int)fp->f_pos);
        vfs_write(fp, pst_mem_info->exception_mem_addr + offset, block_size, &fp->f_pos);
        set_fs(fs);

        filp_close(fp, NULL);

        offset += block_size;
    }

    return EXCEPTION_SUCCESS;
}

void store_wifi_mem_to_file_work(struct work_struct *work)
{
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    __store_wifi_mem_to_file();

    free_uart_read_wifi_mem();

    complete(&pst_exception_data->wait_uart_read_wifi_mem);

    return;
}

void store_wifi_mem_to_file(void)
{
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    queue_work(pst_exception_data->plat_exception_rst_workqueue, &pst_exception_data->uart_store_wifi_mem_to_file_work);
    return;
}

int32 uart_halt_wcpu(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);
    
    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    INIT_COMPLETION(pst_exception_data->wait_uart_halt_wcpu);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_HALT_WCPU);
    timeleft = wait_for_completion_timeout(&pst_exception_data->wait_uart_halt_wcpu, msecs_to_jiffies(UART_HALT_WCPU_TIMEOUT));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait uart halt wcpu ack timeout\n");
        return -ETIMEDOUT;
    }

    oal_sdio_wakeup_dev(oal_get_sdio_default_handler());

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : exception_bcpu_dump_recv
 功能描述  : 回调数据处理函数

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 exception_bcpu_dump_recv(uint8* str, oal_netbuf_stru* netbuf)
{
    exception_bcpu_dump_header*      cmd_header={0};
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    cmd_header = (exception_bcpu_dump_header*)(str);
    oal_memcopy(st_bcpu_dump_buff.mem_addr+st_bcpu_dump_buff.data_len,
                str+sizeof(exception_bcpu_dump_header),cmd_header->men_len);
    st_bcpu_dump_buff.data_len += cmd_header->men_len;

    complete(&pst_exception_data->wait_sdio_d2h_dump_ack);

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  :  free_buffer_and_netbuf()
 功能描述  : 释放数据空间

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32  free_buffer_and_netbuf(void)
{
    if (NULL != st_bcpu_dump_buff.mem_addr)
    {
        OS_MEM_VFREE(st_bcpu_dump_buff.mem_addr);
        st_bcpu_dump_buff.data_limit = 0;
        st_bcpu_dump_buff.data_len = 0;
        st_bcpu_dump_buff.mem_addr = NULL;
    }

    if (NULL != st_bcpu_dump_netbuf)
    {
        st_bcpu_dump_netbuf = NULL;
    }
    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : sdio_halt_bcpu
 功能描述  : sdio send halt bcpu cmd

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 sdio_halt_bcpu(void)
{
    int32  ret;
    uint64 timeleft;
    int i;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    hcc_tx_transfer_lock(hcc_get_default_handler());

    //wake up wifi
    for (i = 0; i < WAKEUP_RETRY_TIMES; i++)
    {
        ret = wlan_pm_wakeup_dev();
        if (OAL_SUCC == ret)
        {
            break;
        }
    }

    if (EXCEPTION_SUCCESS != ret)
    {
        PS_PRINT_ERR("wlan wake up fail!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return -OAL_FAIL;
    }

    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_HALT_BCPU);
    if(0 == ret)
    {
        /*等待device执行命令*/
        timeleft = wait_for_completion_timeout(&pst_wlan_pm->st_halt_bcpu_done,msecs_to_jiffies(WLAN_HALT_BCPU_TIMEOUT));
        if(0 == timeleft)
        {
            PS_PRINT_ERR("sdio halt bcpu failed!\n");
            hcc_tx_transfer_unlock(hcc_get_default_handler());
            return -OAL_FAIL;
        }
    }
    PS_PRINT_INFO("halt bcpu sucess!");
    hcc_tx_transfer_unlock(hcc_get_default_handler());
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : allocate_data_save_buffer
 功能描述  : 分配存储数据buffer

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 allocate_data_save_buffer(uint32 len)
{
    //临时buff配置,用于传送数据
    st_bcpu_dump_buff.mem_addr = OS_VMALLOC_GFP(len);
    if (NULL == st_bcpu_dump_buff.mem_addr)
    {
        PS_PRINT_ERR("st_bcpu_dump_buff allocate fail!\n");
        return -EXCEPTION_FAIL;
    }
    st_bcpu_dump_buff.data_limit = len;
    st_bcpu_dump_buff.data_len  = 0;
    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : allocate_send_netbuf
 功能描述  : 分配netbuf

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 allocate_send_netbuf(uint32 len)
{
    st_bcpu_dump_netbuf  = hcc_netbuf_alloc(len);
    if (NULL == st_bcpu_dump_netbuf)
    {
        PS_PRINT_ERR("st_bcpu_dump_netbuf allocate fail !\n");
        return -EXCEPTION_FAIL;
    }

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : dump_header_init
 功能描述  : 初始化命令CMD

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 dump_header_init(exception_bcpu_dump_header* header, uint32 align_type, uint32 addr, uint32 send_len)
{
    /*cmd 初始化*/
    header->align_type = align_type;
    header->start_addr = addr;
    header->men_len    = send_len;
    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : init_hcc_head_and_send
 功能描述  : 初始化hcc发送header

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 init_hcc_head_and_send(struct hcc_transfer_param st_hcc_transfer_param,
                                         struct st_exception_info* pst_exception_data, uint32 wait_time)
{
    uint64 timeleft;
    //发送
    INIT_COMPLETION(pst_exception_data->wait_sdio_d2h_dump_ack);
    hcc_tx(hcc_get_default_handler(), st_bcpu_dump_netbuf, &st_hcc_transfer_param);
    /*等待SDIO读数据完成*/
    timeleft = wait_for_completion_timeout(&pst_exception_data->wait_sdio_d2h_dump_ack, msecs_to_jiffies(wait_time));
    if (!timeleft)
    {
        PS_PRINT_ERR("sdio read  failed!\n");

        //oal_netbuf_free(st_bcpu_dump_netbuf);
        st_bcpu_dump_netbuf = NULL;
        return -EXCEPTION_FAIL;
    }
     return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : sdio_get_and_save_data
 功能描述  : sdio send cmd save data

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 sdio_get_and_save_data(exception_bcpu_dump_msg* sdio_read_info, uint32 count)
{
    uint32 header_len;
    uint32 netbuf_len;
    uint32 send_len;
    uint32 index;
    uint32 i = 0;
    uint32 buffer_len;
    uint32 send_total_len;
    uint32 align_type;
    int32  error = EXCEPTION_SUCCESS;
    int8 filename[100] = {0};

    mm_segment_t fs = {0};
    OS_KERNEL_FILE_STRU *fp = {0};
    struct timeval tv;
    struct rtc_time tm;
    struct hcc_transfer_param st_hcc_transfer_param = {0};
    struct st_exception_info *pst_exception_data = NULL;
    exception_bcpu_dump_header      dump_header = {0};

    PS_PRINT_INFO("%s\n", __func__);

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    //获取文件时间
    do_gettimeofday(&tv);
    rtc_time_to_tm(tv.tv_sec, &tm);
    //tm.tm_hour = (tm.tm_hour + 8) >= 24 ? (tm.tm_hour + 8 - 24) : (tm.tm_hour + 8); //时区转换
    PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
               tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    if (OAL_SUCC != sdio_halt_bcpu())
    {
        PS_PRINT_ERR("halt bcpu error!\n");
        return -EXCEPTION_FAIL;
    }

    header_len = sizeof(exception_bcpu_dump_header);
    for (i = 0; i < count; i++)
    {
        index = 0;

        snprintf(filename, sizeof(filename),"/data/memdump/%04d%02d%02d%02d%02d%02d_%s.bin",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, sdio_read_info[i].file_name);

        /*准备文件空间*/
        fp = filp_open(filename, O_RDWR | O_CREAT, 0777);
        if (IS_ERR_OR_NULL(fp))
        {
            PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
            return -EXCEPTION_FAIL;
        }
        fs = get_fs();
        set_fs(KERNEL_DS);
        vfs_llseek(fp, 0, SEEK_END);
        PS_PRINT_INFO("%s is dumping...,pos = %d\n", sdio_read_info[i].file_name, (int)fp->f_pos);

        //prepare data buffer
        send_total_len = sdio_read_info[i].men_len;
        align_type = sdio_read_info[i].align_type;
        if (ALIGN_1_BYTE == align_type)
        {
            buffer_len = (send_total_len > DUMP_BCPU_MEM_BUFF_LEN) ? DUMP_BCPU_MEM_BUFF_LEN : sdio_read_info[i].men_len;
        }
        else
        {
            buffer_len = (send_total_len > DUMP_BCPU_REG_BUFF_LEN) ? DUMP_BCPU_REG_BUFF_LEN : sdio_read_info[i].men_len;
        }

        if(EXCEPTION_SUCCESS != allocate_data_save_buffer(buffer_len))
        {
            error = -EXCEPTION_FAIL;
            goto exit;
        }

        //send cmd and save data
        while (index < send_total_len)
        {
            send_len = send_total_len - index;

            if (ALIGN_1_BYTE == align_type)
            {
                // dump mem set
                if (send_len > DUMP_BCPU_MEM_BUFF_LEN)
                {
                    send_len = DUMP_BCPU_MEM_BUFF_LEN;
                }
                hcc_hdr_param_init(&st_hcc_transfer_param, HCC_ACTION_TYPE_OAM, DUMP_MEM, 0, 0, DATA_HI_QUEUE);
            }
            else
            {   //dump reg set
                if (send_len > DUMP_BCPU_REG_BUFF_LEN)
                {
                    send_len = DUMP_BCPU_REG_BUFF_LEN;
                }
                hcc_hdr_param_init(&st_hcc_transfer_param, HCC_ACTION_TYPE_OAM, DUMP_REG, 0, 0, DATA_HI_QUEUE);
            }

            netbuf_len = header_len + send_len;
            if(EXCEPTION_SUCCESS != allocate_send_netbuf(netbuf_len))
            {
                error = -EXCEPTION_FAIL;
                goto exit;
            }

            dump_header_init(&dump_header, sdio_read_info[i].align_type,
                                            sdio_read_info[i].start_addr+index, send_len);
            oal_memcopy(oal_netbuf_put(st_bcpu_dump_netbuf, netbuf_len), &dump_header, sizeof(exception_bcpu_dump_header));

            //发送
            if (EXCEPTION_SUCCESS != init_hcc_head_and_send(st_hcc_transfer_param, pst_exception_data, WIFI_DUMP_BCPU_TIMEOUT))
            {
                error = -EXCEPTION_FAIL;
                goto exit;
            }

            vfs_write(fp, st_bcpu_dump_buff.mem_addr, st_bcpu_dump_buff.data_len, &fp->f_pos);

            index += send_len;

            //prepare for next data
            st_bcpu_dump_buff.data_len  = 0;
            st_bcpu_dump_netbuf = NULL;
        }
    }
exit:
    set_fs(fs);
    filp_close(fp, NULL);
    free_buffer_and_netbuf();
    complete(&pst_exception_data->wait_sdio_d2h_dump_ack);

    return error;
}

/*****************************************************************************
 函 数 名  : debug_sdio_read_bfgx_reg_and_mem
 功能描述  : sdio read bfgx reg and mem

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
int32 debug_sdio_read_bfgx_reg_and_mem(uint32 which_mem)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);

    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error!\n");
        return -EXCEPTION_FAIL;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_ERR("plat dfr is not enable ,can not dump info");
        return -EXCEPTION_FAIL;
    }

    if (bfgx_is_shutdown())
    {
        PS_PRINT_WARNING("bfgx is off can not dump bfgx msg !\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EXCEPTION_FAIL;
    }

    PS_PRINT_INFO("sdio dump bfgx msg begin\n");

    //prepare the wlan state
    if (wlan_is_shutdown())
    {
        PS_PRINT_WARNING("wifi is closed, can not dump bcpu info!");
        return -EXCEPTION_FAIL;
    }
    else
    {
        PS_PRINT_INFO("wifi is open!\n");
    }

    //去能exception设置,halt bcpu不引发DFR
    pst_exception_data->exception_reset_enable = PLAT_EXCEPTION_DISABLE;

    //dump data
    switch (which_mem)
    {
        case BFGX_PUB_REG:
            sdio_get_and_save_data(g_sdio_read_bcpu_pub_reg_info, BFGX_PUB_REG_NUM);
            break;
        case BFGX_PRIV_REG:
            sdio_get_and_save_data(g_sdio_read_bcpu_priv_reg_info, BFGX_PRIV_REG_NUM);
            break;
        case BFGX_MEM:
            sdio_get_and_save_data(g_sdio_read_bcpu_mem_info, BFGX_SHARE_RAM_NUM);
            break;
        case SDIO_BFGX_MEM_DUMP_BOTTOM:
            sdio_get_and_save_data(g_sdio_read_all, sizeof(g_sdio_read_all)/sizeof(exception_bcpu_dump_msg));
            break;
        default:
            PS_PRINT_WARNING("input param error , which_mem is %d\n", which_mem);
            pst_exception_data->exception_reset_enable = PLAT_EXCEPTION_ENABLE;
            return -EXCEPTION_FAIL;
    }
    PS_PRINT_INFO("dump complete, recovery begin\n");

    //使能DFR, recovery
    pst_exception_data->exception_reset_enable = PLAT_EXCEPTION_ENABLE;
    plat_exception_handler(SUBSYS_BFGX, BFGX_THREAD_BOTTOM, SDIO_DUMP_BCPU);

    return EXCEPTION_SUCCESS;
}


int32 uart_read_wifi_mem(uint32 which_mem)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    if (which_mem >= UART_WIFI_MEM_DUMP_BOTTOM)
    {
        PS_PRINT_ERR("param which_mem [%d] is err\n", which_mem);
        return -EINVAL;
    }

    g_recvd_wifi_block_index = which_mem;

    if (0 > prepare_to_recv_wifi_mem())
    {
        PS_PRINT_ERR("prepare mem to recv wifi mem fail, which_mem = [%d]\n", which_mem);
        g_recvd_wifi_block_index = UART_WIFI_MEM_DUMP_BOTTOM;
        return -EINVAL;
    }

    INIT_COMPLETION(pst_exception_data->wait_uart_read_wifi_mem);
    ps_uart_state_pre(ps_core_d->tty);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, g_uart_read_wifi_mem_info[which_mem].cmd);
    timeleft = wait_for_completion_timeout(&pst_exception_data->wait_uart_read_wifi_mem, msecs_to_jiffies(UART_READ_WIFI_MEM_TIMEOUT));
    if (!timeleft)
    {
        ps_uart_state_dump(ps_core_d->tty);
        PS_PRINT_ERR("wait uart read wifi mem [%d] timeout\n", which_mem);
        free_uart_read_wifi_mem();
        return -ETIMEDOUT;
    }

    return EXCEPTION_SUCCESS;
}

int32 debug_uart_read_wifi_mem(uint32 ul_lock)
{
    uint32 i;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    if(ul_lock)
    {
        mutex_lock(&pm_data->host_mutex);
    }

    if (EXCEPTION_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        goto fail_return;
    }

    if (EXCEPTION_SUCCESS != uart_halt_wcpu())
    {
        PS_PRINT_ERR("uart halt wcpu fail!\n");
        post_to_visit_node(ps_core_d);
        goto fail_return;
    }

    for (i = 0; i < UART_WIFI_MEM_DUMP_BOTTOM; i++)
    {
        if (EXCEPTION_SUCCESS != uart_read_wifi_mem(i))
        {
            PS_PRINT_ERR("uart read wifi mem [%d] fail!", i);
            break;
        }
    }

    post_to_visit_node(ps_core_d);

    if(ul_lock)
    {
        mutex_unlock(&pm_data->host_mutex);
    }

    return EXCEPTION_SUCCESS;

 fail_return:
    if(ul_lock)
    {
        mutex_unlock(&pm_data->host_mutex);
    }
    
    return -EXCEPTION_FAIL;
    
}

int32 bfgx_reset_cmd_send(uint32 subsys)
{
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bfgx_data = NULL;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -EINVAL;
    }

    if (NULL == g_ast_bfgx_reset_msg)
    {
        PS_PRINT_ERR("g_ast_bfgx_reset_msg is null\n");
        return -EINVAL;
    }

    pst_bfgx_data = &ps_core_d->bfgx_info[subsys];

    ret = ps_push_skb_queue(ps_core_d, g_ast_bfgx_reset_msg[subsys].cmd, g_ast_bfgx_reset_msg[subsys].len, g_bfgx_rx_queue[subsys]);
    if (EXCEPTION_SUCCESS != ret)
    {
        PS_PRINT_ERR("push %s reset cmd to skb fail\n", g_bfgx_subsys_name[subsys]);
        return -EXCEPTION_FAIL;
    }

    wake_up_interruptible(&pst_bfgx_data->rx_wait);

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : bfgx_status_recovery
 功能描述  : 全系统复位以后，恢复bfgin业务函数
 输入参数  : st_exception_info *exception结构体指针，保存了异常产生的系统wifi
             还是BFGN，对于BFGN还保存了产生异常的子业务，以及异常的类型
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 bfgx_status_recovery(void)
{
    uint32 i;
    struct st_exception_info *pst_exception_data = NULL;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bfgx_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -EXCEPTION_FAIL;
    }

    if (EXCEPTION_SUCCESS != prepare_to_visit_node(ps_core_d))
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return -EXCEPTION_FAIL;
    }

    for (i = 0; i < BFGX_BUTT; i++)
    {
        pst_bfgx_data = &ps_core_d->bfgx_info[i];
        if (POWER_STATE_SHUTDOWN == atomic_read(&pst_bfgx_data->subsys_state))
        {
            continue;
        }

        ps_kfree_skb(ps_core_d, g_bfgx_rx_queue[i]);

        if (EXCEPTION_SUCCESS != bfgx_open_cmd_send(i))
        {
            PS_PRINT_ERR("bfgx open cmd fail\n");
            post_to_visit_node(ps_core_d);
            return -EXCEPTION_FAIL;
        }

        if (EXCEPTION_SUCCESS != bfgx_reset_cmd_send(i))
        {
            PS_PRINT_ERR("bfgx reset cmd send fail\n");
            post_to_visit_node(ps_core_d);
            return -EXCEPTION_FAIL;
        }
    }

    post_to_visit_node(ps_core_d);

    /*仅调试使用*/
    PS_PRINT_INFO("exception: set debug beat flag to 1\n");
    pst_exception_data->debug_beat_flag = 1;

    return EXCEPTION_SUCCESS;
}

/*****************************************************************************
 函 数 名  : is_bfgx_exception
 功能描述  : 判断bfgx是否发生了ecxception
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0没有异常，1发生异常
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 is_bfgx_exception(void)
{
    struct st_exception_info *pst_exception_data = NULL;
    int32 is_exception;
    uint64 flag;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    spin_lock_irqsave(&pst_exception_data->exception_spin_lock, flag);
    if (PLAT_EXCEPTION_RESET_BUSY == atomic_read(&pst_exception_data->is_reseting_device))
    {
        is_exception = PLAT_EXCEPTION_RESET_BUSY;
    }
    else
    {
        is_exception = PLAT_EXCEPTION_RESET_IDLE;
    }
    spin_unlock_irqrestore(&pst_exception_data->exception_spin_lock, flag);

    return is_exception;
}

/*****************************************************************************
 函 数 名  : plat_bfgx_exception_rst_register
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_bfgx_exception_rst_register(struct ps_plat_s *data)
{
	struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (NULL == data)
    {
        PS_PRINT_ERR("para data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    pst_exception_data->ps_plat_d = data;

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_bfgx_exception_rst_register);

/*****************************************************************************
 函 数 名  : plat_wifi_exception_rst_register
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_wifi_exception_rst_register(void *data)
{
	struct st_exception_info *pst_exception_data = NULL;
	struct st_wifi_dfr_callback *pst_wifi_callback = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (NULL == data)
    {
        PS_PRINT_ERR("param data is null\n");
        return -EXCEPTION_FAIL;
    }

    /*wifi异常回调函数注册*/
    pst_wifi_callback = (struct st_wifi_dfr_callback *)data;
    pst_exception_data->wifi_callback = pst_wifi_callback;

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_wifi_exception_rst_register);

/*****************************************************************************
 函 数 名  : plat_exception_reset_init
 功能描述  : 平台异常处理模块初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_reset_init(void)
{
    struct st_exception_info *p_exception_data = NULL;
    struct st_wifi_dfr_callback *pst_wifi_callback = NULL;

    p_exception_data = (struct st_exception_info *)kzalloc(sizeof(struct st_exception_info), GFP_KERNEL);
    if (NULL == p_exception_data)
    {
        PS_PRINT_ERR("kzalloc p_exception_data is failed!\n");
        return -EXCEPTION_FAIL;
    }

    pst_wifi_callback = kzalloc(sizeof(struct st_wifi_dfr_callback), GFP_KERNEL);
    if (NULL == pst_wifi_callback)
    {
        PS_PRINT_ERR("no mem to allocate\n");
        kfree(p_exception_data);
        return -ENOMEM;
    }
    p_exception_data->wifi_callback = pst_wifi_callback;

    p_exception_data->subsys_type   = SUBSYS_BOTTOM;
    p_exception_data->thread_type   = BFGX_THREAD_BOTTOM;
    p_exception_data->excetion_type = EXCEPTION_TYPE_BOTTOM;

    p_exception_data->exception_reset_enable   = PLAT_EXCEPTION_DISABLE;
    p_exception_data->wifi_exception_cnt       = 0;
    p_exception_data->bfgx_exception_cnt       = 0;
    p_exception_data->ps_plat_d                = NULL;

    atomic_set(&p_exception_data->bfgx_beat_flag, BFGX_NOT_RECV_BEAT_INFO);
    atomic_set(&p_exception_data->is_reseting_device, PLAT_EXCEPTION_RESET_IDLE);

    /*初始化异常处理workqueue和work*/
    p_exception_data->plat_exception_rst_workqueue = create_singlethread_workqueue("plat_exception_reset_queue");
    INIT_WORK(&p_exception_data->plat_exception_rst_work, plat_exception_reset_work);
    INIT_WORK(&p_exception_data->uart_store_wifi_mem_to_file_work, store_wifi_mem_to_file_work);

    /*初始化心跳timer*/
    init_timer(&p_exception_data->bfgx_beat_timer);
    p_exception_data->bfgx_beat_timer.function = bfgx_beat_timer_expire;
    p_exception_data->bfgx_beat_timer.expires  = jiffies + BFGX_BEAT_TIME*HZ;
    p_exception_data->bfgx_beat_timer.data     = 0;

    /*初始化异常处理自旋锁*/
    spin_lock_init(&p_exception_data->exception_spin_lock);

    /*初始化bfgx读栈完成量*/
    init_completion(&p_exception_data->wait_read_bfgx_stack);
    /*初始化sdio读取bcpu完成量*/
    init_completion(&p_exception_data->wait_sdio_d2h_dump_ack);

    /*调试使用的变量初始化*/
    p_exception_data->debug_beat_flag          = 1;
    p_exception_data->wifi_open_bcpu_enable    = false;

    init_completion(&p_exception_data->wait_uart_read_wifi_mem);
    init_completion(&p_exception_data->wait_uart_halt_wcpu);

    g_pst_exception_info = p_exception_data;

    PS_PRINT_SUC("plat exception reset init success\n");

	return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_init);

/*****************************************************************************
 函 数 名  : plat_exception_reset_exit
 功能描述  : 平台异常处理模块退出清理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : z00299054
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_reset_exit(void)
{
    struct st_exception_info *p_exception_data = NULL;

    p_exception_data = g_pst_exception_info;
    if (p_exception_data == NULL)
    {
        PS_PRINT_ERR("g_pst_exception_info is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    destroy_workqueue(p_exception_data->plat_exception_rst_workqueue);
    del_timer_sync(&p_exception_data->bfgx_beat_timer);

    kfree(p_exception_data->wifi_callback);
    p_exception_data->wifi_callback = NULL;
    kfree(p_exception_data);
    g_pst_exception_info = NULL;

    PS_PRINT_SUC("plat exception reset exit success\n");

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_exit);


