/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  rf_mipi_cfg.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  通过mipi接口对射频器件进行控制
*
*   修改记录 :  2015年3月23日  v1.00  zuofenghua  创建
*
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <securec.h>
#include <osl_malloc.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <RfNvId.h>
#include <drv_nv_def.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <hi_anten.h>
#include <bsp_nvim.h>
#include <bsp_mipi.h>
#include <bsp_rf_balong.h>
#include <bsp_pinctrl.h>
#include <bsp_gpio.h>
#include <bsp_hardtimer.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_version.h>
#include <bsp_bbp.h>
#include <rf_anten_cfg.h>
#include <rf_mipi_cfg.h>


/*射频管脚与GPIO编号的对应关系*/
NV_FEMPIN_TO_GPIO_STRU     g_rfpin2gpio;

/*射频管脚开关机配置*/
RFFE_PIN_ALL_CFG g_anten_info;

/*todo:完善debug信息*/
FEMIO_CALLINFO_S g_femio_debug[16]; 

/*gpio、mipi通用接口控制信息*/
NV_FEM_GPIO_MIPI_CTRL_STRU g_femio_info; 

/*天线有线无线状态信息*/
RF_ANTEN_DETECT_GPIO_STRU g_anten_status;

/*天线插拔检测信息*/
ANTEN_DETECT_INFO g_detect;

/*内置天线、外置天线*/
RF_ANT_SHARE_STRU g_ant_share;

/*TDSL_GSM共存抗干扰使能变量*/
RF_NV_GSM_GPIO_ABBTX_FUNC_SEL g_tdsl_gsm_interference;

/*TDSL_GSM共存干扰配置变量*/
RF_NV_GSM_GPIO_ABBTX_CFG   g_tdsl_gsm_config;

/*射频通用gpio配置接口*/
RF_GPIO_COMM_STRU g_comm_gpio;

/*射频通用mipi配置*/
RF_MIPI_COMM_STRU g_comm_mipi;

/*VIA MODEM是否在位*/
#define VIA_MDM_LP_FLAG_ADDR (u32)((u32)SHM_BASE_ADDR + SHM_OFFSET_RFFE_VIA_LP_FLAG)

int balong_rf_pin_set_mux(struct pinctrl * pctrl, unsigned int gpio_num, unsigned int mux)
{
    if(CHIP_K3V5 == bsp_get_version_info()->chip_type){

        if(ANT_FUNCTION == mux){
        
            if((gpio_num >= 91) && (gpio_num <= 111)){
                mux = 2;
            }
            else mux = 1;
        }
    }
    if(NULL == pctrl){
        rf_print_error("pctrl is null ,gpio is %d,mux is %d\n",gpio_num, mux);
    }
    bsp_pinctrl_mux_set(pctrl, mux);

    return 0;
}
/*****************************************************************************
* 函 数    : rf_pin_to_gpio
* 功 能    : 射频管脚和gpio编号的转换
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，0xffff为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
unsigned int balong_rf_pin_to_gpio(unsigned int pin)
{

    if(pin >= FEM_PIN_MAX){        
        rf_print_error("para error, pin = %d.\n", pin);
        return GPIO_NUM_INVAILId;
    }

    return g_rfpin2gpio.cfg[pin];
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : 射频管脚输出电平配置，0为低电平，1为高电平
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_config_anten_pin(u32 pin_mask, u32 pin_value , u32 pin_func)
{
    u32 i;
    int ret          = 0;
    u32 level        = 0;
    u32 gpio_num     = 0;
    ANT_PIN_FUNC mux;
    struct pinctrl *pctrl = NULL;

    for(i = 0 ; i < FEM_PIN_MAX ; i++){
        if((pin_mask & ((u32)1<<i))){

            /*通过rfpin编号获取到gpio编号*/
            gpio_num = balong_rf_pin_to_gpio(i);            
            if(GPIO_NUM_INVAILId == gpio_num){
                rf_print_error("get gpio num is error %d!\n",gpio_num);
                return RFFE_ERROR;
            }

            /*只有管脚复用为gpio的，才配置电平*/
            if(~pin_func & ((u32)1<<i)){

                /*配置GPIO 输出电平值*/
                level = !!(pin_value &((u32)1<<i));
                bsp_gpio_direction_output(gpio_num, level);
            }

            /*配置管脚复用*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            mux   = (ANT_PIN_FUNC)!!(pin_func & ((u32)1<<i));
            ret   = balong_rf_pin_set_mux(pctrl, gpio_num, mux);
            if(ret){
                rf_print_error("set pin mux error! gpio num=%d,mux=%d\n", gpio_num, mux);
            }
        }
    }

    return ret;
}


/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_common(RFFE_PIN_STRU * pin_info)
{
    int ret        = RFFE_OK;
    u32 mask       = 0;
    u32 level      = 0;
    u32 mux        = 0;

    if(NULL == pin_info){
        rf_print_error("para is NULL !\n");
        return RFFE_ERROR;
    }

    mask = pin_info->mask;
    if (mask){        
        level = pin_info->level;        
        mux   = pin_info->mux;
        
        /*配置管脚电平和复用*/
        ret   = balong_rf_config_anten_pin(mask, level, mux);
        if(ret){
            rf_print_error("rf config anten pin output value error!,ret %d,mask %d\n",ret,mask);
        }
        
    }

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_poweron(u32 modem_id)
{
    int ret        = RFFE_OK;

    if (!g_anten_info.valid){
        return ret;
    }

    if (NV_BALONG_MODEM_NUM <= modem_id){
        rf_print_error("para error,modem id is %d ,nv surport max is %d\n",modem_id, NV_BALONG_MODEM_NUM);
        return RFFE_ERROR;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.modem_pwron[modem_id]);
    if(ret){
        rf_print_error("set ant pin config at modem [%d] power on fail!\n",modem_id);
    }

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem关机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_poweroff(u32 modem_id)
{
    int ret = RFFE_OK;

    if (!g_anten_info.valid){
        return ret;
    }

    if (NV_BALONG_MODEM_NUM <= modem_id){
        rf_print_error("para error,modem id is %d ,nv surport max is %d\n",modem_id, NV_BALONG_MODEM_NUM);
        return RFFE_ERROR;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.modem_pwroff[modem_id]);
    if(ret){
        rf_print_error("set ant pin config at modem [%d] power off fail!\n",modem_id);
    }

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : 两个modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_allpoweroff( void )
{
    int ret = RFFE_OK;
 
    if (!g_anten_info.valid){
        return ret;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.allmodem_pwroff);
    if(ret){
        rf_print_error("set ant pin config at all modem power off fail!ret is %d\n",ret);
    }

    return ret;
}
/*****************************************************************************
* 函 数    : balong_anten_event_report_oam
* 功 能    : 天线插拔时，上报到oam
* 输 入    : @para 上报消息参数

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
void balong_anten_event_report_oam(void *para)
{
    struct anten_msg_stru msg = {0, 0};
    /*lint -save -e716*/
    /* coverity[no_escape] */
    while(1)
    {
        osl_sem_down(&g_detect.sem_id);
        
        msg = *((struct anten_msg_stru*)para);

        rf_print_info("anten modem_id = %d,status = %d.\n", msg.modem_id, msg.status);

        if(msg.modem_id < PWC_COMM_MODEM_BUTT && (NULL != g_detect.routine[msg.modem_id]))
        {
            (void) (*(g_detect.routine[msg.modem_id]))();
        }
    }
    /*lint -restore */

}

/*****************************************************************************
* 函 数    : balong_anten_data_receive
* 功 能    : 天线插拔时，接收a核的消息
* 输 入    : @para 上报消息参数

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_anten_data_receive(void)
{    
    int len = 0;

    struct anten_msg_stru msg = {0};
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ANTEN;
      
    len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(struct anten_msg_stru));
    if(len != (int)sizeof(struct anten_msg_stru))
    {
        rf_print_error("read len(%x) != expected len(%x).\n", len, sizeof(struct anten_msg_stru));
        return RFFE_ERROR;
    }
    
    g_detect.msg.modem_id = msg.modem_id;
    g_detect.msg.status   = msg.status;

    osl_sem_up(&g_detect.sem_id);

    return RFFE_OK;
}

/*****************************************************************************
 * 函 数 : bsp_anten_init *
 * 功能  : 天线插拔核间通信，C核初始化函数
 *
 * 输入  : 无
 * 输出  : 无
 *
 * 返 回 : ANTAN_OK:    操作成功
 *                ANTAN_ERROR: 操作失败
 *****************************************************************************/
s32 balong_anten_detect_init(void)
{
    int ret = 0;
    u32 task_id = 0;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ANTEN;

    memset_s(&g_detect, sizeof(ANTEN_DETECT_INFO), 0, sizeof(ANTEN_DETECT_INFO));
    osl_sem_init(0, &g_detect.sem_id);
    
    ret = osl_task_init("anten_task", ANTEN_TASK_PRIORITY , ANTEN_TASK_STACK_SIZE, (OSL_TASK_FUNC)balong_anten_event_report_oam, &g_detect.msg, &task_id);

    ret |= bsp_icc_event_register(chan_id, (read_cb_func)balong_anten_data_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        rf_print_error("register is error.\n");
        return RFFE_ERROR;
    }    

    rf_print_info("anten init ok,task id is %d.\n", task_id);

    return RFFE_OK;
}


/*****************************************************************************
 * 函 数 : balong_tdsl_gsm_interference_init *
 * 功能  : 主、副卡天线互扰屏蔽，C核初始化函数
 *
 * 输入  : 无
 * 输出  : 无
 *
 * 返 回 : 0:    操作成功
 *                1:    操作失败
 *****************************************************************************/
s32 balong_tdsl_gsm_interference_init(void)
{
#ifdef HI_PHONE_ANTEN
    u32  abbid   = g_tdsl_gsm_interference.abb_tx_index;
    int   ret = 0;
    u32 ctu_base   = (u32)bsp_bbp_part_addr_get(BBP_CTU);

    if(0 == ctu_base){
        rf_print_error("ctu base get error!\n");
        return RFFE_ERROR;
    }

    /*nv 18000 get gpio and abb tx config by id*/
    ret = (int)bsp_nvm_read(en_NV_Item_GSM_GPIO_FUNC_SEL,(u8*)&g_tdsl_gsm_interference,sizeof(RF_NV_GSM_GPIO_ABBTX_FUNC_SEL));
    if (ret !=  0)
    {
        rf_print_error("rffe anten read NV=0x%x, ret = %d \n",en_NV_Item_GSM_GPIO_FUNC_SEL, ret);
    }

    /*nv 18020 get tdsl&gsm interfernce config*/
    ret = (int)bsp_nvm_read(en_NV_Item_GSM_GPIO_FUNC_CFG,(u8*)&g_tdsl_gsm_config,sizeof(RF_NV_GSM_GPIO_ABBTX_CFG));
    if (ret !=  0)
    {
        rf_print_error("rffe anten read NV=0x%x, ret = %d \n",en_NV_Item_GSM_GPIO_FUNC_CFG, ret);
     memset_s(&g_tdsl_gsm_interference, sizeof(RF_NV_GSM_GPIO_ABBTX_CFG), 0, sizeof(RF_NV_GSM_GPIO_ABBTX_CFG));
    }
    /*lint -save -e506 -e774*//* coverity[result_independent_of_operands] */
    if(g_tdsl_gsm_interference.gpio_and_or_en && (0xffff  != HI_BBPCOMMON_CPU_ANTPA_MODE_SEL)){
        writel(g_tdsl_gsm_config.gpio_and_or_cfg, ctu_base + HI_BBPCOMMON_CPU_ANTPA_MODE_SEL);
    }
    /*lint -restore*/
    if(abbid){/*index 为0时，不需要软件配置*/
        writel(g_tdsl_gsm_config.abb_tx_cfg[abbid -1].abb0_tx_reg, ctu_base + HI_BBPCOMMON_CPU_ABB0_CH_TX_MASK_SEL);
        writel(g_tdsl_gsm_config.abb_tx_cfg[abbid -1].abb1_tx_reg, ctu_base + HI_BBPCOMMON_CPU_ABB1_CH_TX_MASK_SEL);
    }
    return ret;
#else
    return 0;
#endif
}

/*****************************************************************************
* 函 数    : balong_fem_io_debuginfo_add
* 功 能    : 射频管脚接口调试信息
* 输 入    : @mipi_nv  nvid号为18002中，mipi配置方式的索引号

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部调试接口
*****************************************************************************/
void balong_fem_io_debuginfo_add(void* caller,u32 para1,u32 para2,u32 para3,int ret)
{
    u32 i = para1%FEM_IO_CFG_MAX;
    g_femio_debug[i].caller_addr = (u32) caller;
    g_femio_debug[i].para1       = para1;
    g_femio_debug[i].para2       = para2;
    g_femio_debug[i].para3       = para3;
    g_femio_debug[i].timestamp   = bsp_get_slice_value();
    g_femio_debug[i].ret         = ret;
}

/*****************************************************************************
* 函 数    : fem_iocfg_group_mipi
* 功 能    : 射频管脚本置--mipi配置方式
* 输 入    : @mipi_nv  nvid号为18002中，mipi配置方式的索引号

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static int balong_fem_iocfg_group_mipi(u32 nv_index)
{
    int ret      = 0;
    int max_bytes= 0;

    max_bytes = sizeof(g_femio_info.cfg[nv_index].mipi_ctrl) / sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_femio_info.cfg[nv_index].mipi_ctrl.MipiCmd,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_femio_info.cfg[nv_index].mipi_ctrl.MipiData, \
                               g_femio_info.cfg[nv_index].mipi_ctrl.CmdValidCnt, \
                               max_bytes);
    return ret;
}

/*****************************************************************************
* 函 数    : fem_iocfg_group_gpio
* 功 能    : 射频管脚本置--gpio配置方式
* 输 入    : @gpio_nv  nvid号为18002中，gpio配置方式的索引号

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static int balong_fem_iocfg_group_gpio(u32 nv_index, u32 mux)
{
    u32 i= 0;
    int ret = 0;
    u32 pin_mask  = 0;
    u32 pin_value = 0;
    u32 gpio_num  = 0;
    struct pinctrl* pctrl = NULL;

    if((nv_index >= FEM_IO_CFG_MAX) || (mux >= ANT_FUNC_BUTT)){
        rf_print_error("para error ! nv index is %d,mux is %d\n", nv_index, mux);
        return -1;
    }

    pin_mask  = g_femio_info.cfg[nv_index].gpio_ctrl.mask;
    pin_value = g_femio_info.cfg[nv_index].gpio_ctrl.level;

    for(i=0; i<FEM_PIN_MAX; i++){
        if(pin_mask & ((u32)1 << i)){
            gpio_num = balong_rf_pin_to_gpio(i);
            if(GPIO_NUM_INVAILId == gpio_num){
                rf_print_error("get gpio num is error %d!\n",gpio_num);
                return -1;
            }
            /*get pin mux*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);

            /*if pin is gpio function,set direction and pin level*/
            if(0 == mux){
                pin_value = (u32)!!(pin_value & ((u32)1<<i));
                bsp_pinctrl_gpio_modify(pctrl, GPIO_OUTPUT, pin_value);                
                bsp_gpio_direction_output(gpio_num, pin_value);
            }

            /*set pin mux*/
            ret  |= bsp_pinctrl_mux_modify(pctrl, mux);
            ret   = balong_rf_pin_set_mux(pctrl, gpio_num, mux);
            if(ret){
                rf_print_error("set pin mux error! gpio num=%d,mux=%d\n",gpio_num,mux);
                return ret;
            }

        }
    }

    return 0;
}

/*****************************************************************************
* 函 数    : balong_fem_iocfg_group_gpio_mipi_with_nv
* 功 能    : 射频管脚本置
* 输 入    : @type,0为gpio配置方式
                    @gpio_nv    nvid号为18002中，gpio配置方式的索引号
                    @mipi_nv     nvid号为18002中，gpio配置方式的索引号              

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static int balong_fem_iocfg_group_gpio_mipi_with_nv(u32 nv_index, u32 mux)
{
    FEMIO_CTRL_MODE type = FEMIO_CTRL_TOP;
    int ret = 0;

    if(nv_index >= FEM_IO_CFG_MAX){
        rf_print_error("para is error, nv_index = %d\n", nv_index);
        return -1;
    }

    if(mux > 1){
        rf_print_error("para is error, mux = %d\n", mux);
        return -1;
    }

    type = g_femio_info.cfg[nv_index].mode;
    switch (type){
        case FEMIO_CTRL_TOP:
            ret = 0;
            break;
        case GPIO_ONLY:/*配置GPIO*/
            ret =  balong_fem_iocfg_group_gpio(nv_index,mux);
            break;
        case MIPI_ONLY:/*配置MIPI*/
            ret = balong_fem_iocfg_group_mipi(nv_index);
            break;
        case GPIO_MIPI:
            ret =  balong_fem_iocfg_group_gpio(nv_index,mux);
            ret |= balong_fem_iocfg_group_mipi(nv_index);
            break;
        default:
            rf_print_error("para is error, type = %d\n", type);
            ret = -1;
            break;
    }
    return ret;
}
/*****************************************************************************
* 函 数    : balong_fem_iocfg_gpio_no_nv
* 功 能    : 射频管脚本置
* 输 入    : @gpio, 为gpio编号
                    @mux    管脚复用配置，0为GPIO，1为线控
                    @value  管脚输出电平值 ,0为输出低电平，1为输出低电平

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static int balong_fem_iocfg_gpio_no_nv(u32 gpio, u32 mux, u32 value)
{
    int ret = RFFE_OK;
    struct pinctrl *pctrl = NULL;

    if(mux >= MODEM_PIN_MUX_BUTT){
        rf_print_error("mux para error,mux is :%d\n",mux);
        return RFFE_ERROR;
    }

    if(MODEM_PIN_MUX_GPIO == mux){
        bsp_gpio_direction_output(gpio,value);
    }

    pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
    ret = balong_rf_pin_set_mux(pctrl, gpio, mux);
    if(ret){
        rf_print_error("set rf pin mux error!gpio = %d\n",gpio);
    }

    return ret;
}

/*****************************************************************************
* 函 数    : balong_fem_iocfg_gpio_with_resume
* 功 能    : 射频管脚本置
* 输 入    : @gpio, 为gpio编号
                    @mux    管脚复用配置，0为GPIO，1为线控
                    @value  管脚输出电平值 ,0为输出低电平，1为输出低电平

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static int balong_fem_iocfg_gpio_with_resume(u32 gpio, u32 mux, u32 value)
{
    int ret = RFFE_OK;
    struct pinctrl *pctrl = NULL;

    if(mux >= MODEM_PIN_MUX_BUTT){
        rf_print_error("mux para error,mux is :%d\n",mux);
        return RFFE_ERROR;
    }

    /*get pinctrl node*/
    pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);

    /*set gpio config*/
    if(MODEM_PIN_MUX_GPIO == mux){
        bsp_gpio_direction_output(gpio,value);
        ret = bsp_pinctrl_gpio_modify(pctrl, GPIO_OUTPUT, value);
        if(ret){
            rf_print_error("modify gpio error!\n");
            return RFFE_ERROR;
        }
    }

    /*set pin mux*/
    ret   = balong_rf_pin_set_mux(pctrl, gpio, mux);
    if(ret){
        rf_print_error("set rf pin mux error!gpio = %d\n",gpio);
        return RFFE_ERROR;
    }

    /*change pin mux dts*/
    ret = bsp_pinctrl_mux_modify(pctrl, mux);
    if(ret){
        rf_print_error("modify pin mux dts error!gpio = %d\n",gpio);
    }

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_gpio_comm_config
* 功 能    : 射频gpio通用配置函数(参照18022nv )
* 输 入    : @nv_index nv编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_gpio_comm_config(u32 nv_index)
{
    u32 gpio = g_comm_gpio.profile[nv_index].gpio_num;
    u32 value= g_comm_gpio.profile[nv_index].level;
    u32 mux  = g_comm_gpio.profile[nv_index].function;
    struct pinctrl* pctrl = NULL;

    pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
    if(NULL == pctrl)
    {
        rf_print_error("get pinctrl node error! gpio is %d\n", gpio);
        return RFFE_ERROR;
    }

    /*判断是否需要配置管脚电平*/
    if (GPIO_FUNCTION == g_comm_gpio.profile[nv_index].function)
    {
        bsp_gpio_direction_output(gpio, value);
    }

    return balong_rf_pin_set_mux(pctrl, gpio, mux);

}

/*****************************************************************************
* 函 数    : balong_rf_pin_dts_modify
* 功 能    : 射频gpio通用配置函数(参照18022nv )
* 输 入    : @nv_index nv编号
                     @dts_mode init/lowpower/normal

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_pin_dts_modify(u32 nv_index, u32 dts_mode)
{
    u32 gpio = g_comm_gpio.profile[nv_index].gpio_num;
    u32 value= g_comm_gpio.profile[nv_index].level;
    u32 mux  = g_comm_gpio.profile[nv_index].function;
    int ret  = 0;
    struct pinctrl* pctrl = NULL;

    if(!g_comm_gpio.profile[nv_index].enable)
    {
        return ret;/*nv 没使能，特性没打开*/
    }

    pctrl = bsp_pinctrl_get(dts_mode, gpio);
    if(NULL == pctrl)
    {
        rf_print_error("get pinctrl node error!dts mode is%d, gpio is %d\n",dts_mode, gpio);
        return RFFE_ERROR;
    }

    /*判断是否需要配置管脚电平*/
    if (GPIO_FUNCTION == g_comm_gpio.profile[nv_index].function)
    {
        ret = bsp_pinctrl_gpio_modify(pctrl, GPIO_OUTPUT, value);
    }

    ret |= bsp_pinctrl_mux_modify(pctrl, mux);
    return ret;

}

/*****************************************************************************
* 函 数    : balong_rf_mipi_comm_config
* 功 能    : 射频mipi通用配置函数(参照18022nv )
* 输 入    : @nv_index nv编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_mipi_comm_config(u32 nv_index)
{
    int ret      = 0;
    int max_bytes= 0;

    max_bytes = sizeof(g_comm_mipi.profile[nv_index]) / sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_comm_mipi.profile[nv_index].MipiCmd,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_comm_mipi.profile[nv_index].MipiData, \
                               g_comm_mipi.profile[nv_index].CmdValidCnt, \
                               max_bytes);
    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_anten_resume
* 功 能    : 天线相关低功耗唤醒
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_anten_resume(void)
{
    int ret      = 0;
#ifdef    VIA_MDM_TUNER_LP
    if (readl(VIA_MDM_LP_FLAG_ADDR))
    {
        /*如果VIA MODEM 允许tuner低功耗，resume时需要打开tuner ic和spdt*/
        ret |= balong_rf_mipi_comm_config(OUTER_MODEM_TUNER_RESUME);
    }
#endif
    return ret;
}

/*****************************************************************************
* 函 数    : balong_rf_anten_suspend
* 功 能    : 天线相关低功耗睡眠配置
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_anten_suspend(void)
{
    int ret      = 0;
#ifdef    VIA_MDM_TUNER_LP
    if (readl(VIA_MDM_LP_FLAG_ADDR))
    {
        /*如果VIA MODEM 允许tuner低功耗，需要关闭tuner ic和spdt*/
        ret = balong_rf_mipi_comm_config(OUTER_MODEM_TUNER_SUSPEND);
    }
#endif
    return ret;
}

/*****************************************************************************
* 函 数    : bsp_fem_ioctrl
* 功 能    : 射频管脚配置
* 输 入    : @ctrl_type  接口类型，1为gpio、mipi参照NV配置，2为直接传参配置

               ctrl_type = CFG_RFFE_GROUP_GPIO_MIPI
              @para1 is nvindex    nv  项索引，取值为0-15，此参数参见nv手册18002
              @para2 is mux         管脚复用配置，0为gpio功能，1为线控功能
              @para3 is reserved   保留

               ctrl_type = CFG_RFFFE_SET_PIN_NO_NV
              @para1 is gpio num    gpio编号
              @para2 is mux           管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value         若para2为gpio功能，则value为输出电平

               ctrl_type = CFG_RFFE_SET_PIN_WITH_RESUEM(在1的基础上，增加低功耗功能)
              @para1 is gpio num      gpio编号
              @para2 is mux          管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value           若para2为gpio功能，则value为输出电平

               ctrl_type = CFG_VIA_MODEM_IS_ACTIVE(外置modem是否在位)
              @para1 is active        0表示不在位，1表示在位
              @para2 is mux        保留
              @para3 is value            保留

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 此接口在手机平台使用，MBB不设及，打桩即可
*****************************************************************************/
int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    int ret = 0;
    switch(ctrl_type)
    {
        case CFG_RFFE_GROUP_GPIO_MIPI:
            ret = balong_fem_iocfg_group_gpio_mipi_with_nv(para1, para2);
            break;

        case CFG_RFFE_SET_PIN_NO_NV:
            ret = balong_fem_iocfg_gpio_no_nv(para1, para2,para3);
            break;

        case CFG_RFFE_SET_PIN_WITH_RESUEM:
            ret = balong_fem_iocfg_gpio_with_resume(para1, para2,para3);
            break;

        case CFG_RFFE_3RDMODEM_IS_ACTIVE:
            writel((unsigned)!para1, VIA_MDM_LP_FLAG_ADDR);

            /*if cdma modem isn't active ,set spdt lower when modem suspend*/
            #ifdef VIA_MDM_TUNER_LP
            if(0 == para1){
                ret|= balong_rf_pin_dts_modify(OUTER_MODEM_SPDT_SUSPEND, MODEM_PIN_POWERDOWN);
                if (ret !=      0)
                {
                    rf_print_error("balong rf pin dts modify fail, ret = %d \n",ret);
                }
            }
            #endif

            break;
        default:
            ret = -1;
            break;
    }

    
    /*lint -save -e718 -e746 -e628 -e64*/
    balong_fem_io_debuginfo_add(__builtin_return_address(0),para1,para2,para3,ret);    
    /*lint -save restore*/

    return ret;
}

/*****************************************************************************
* 函 数    : bsp_anten_get_lockstate
* 功 能    : 获取天线有线无线连接状态接口
* 输 入    : @modem_id,modem编号

* 输 出    : @status    有线为1,无线为0

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    int value = 0;
    u32 gpio = 0;

    if(NULL == status || (modem_id >= RF_ANTEN_NUM))
    {
        rf_print_error("para is error, modem id = %d, status = 0x%x.\n", modem_id, status);
        return RFFE_ERROR;
    }

    gpio  = g_anten_status.anten[modem_id];
    if(ANT_DETECT_STUB_GPIO == gpio){
        *status = 1;
        return RFFE_OK;
    }

    value = bsp_gpio_get_value(gpio);/* [false alarm]:屏蔽Fortify错误 */
    if(GPIO_ERROR == value)
    {
        rf_print_error("bsp_gpio_get_value is fail, value = %d.\n", value);
        return RFFE_ERROR;
    }

    *status = (unsigned int)value;

    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : bsp_anten_set_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择控制接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 输 出    : 无

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_set_outer_rfswitch(unsigned int status)
{   
    unsigned int i          = 0;
    unsigned int rf_pin     = 0;
    unsigned int gpio_num   = 0;
    unsigned int gpio_value = 0;
    unsigned int cnt        = 0;
    int          ret        = 0;
    struct pinctrl *pctrl   = NULL;

    cnt = g_ant_share.outside.num;
    if(OUTER_RFSWITCH_ON == status){

        for( i = 0 ; i < cnt ; i++ )
        {
            rf_pin     = g_ant_share.outside.gpio[i].rf_pin;
            gpio_value = g_ant_share.outside.gpio[i].gpio_level;
            gpio_num   = balong_rf_pin_to_gpio(rf_pin);
            pctrl      = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            ret = balong_rf_pin_set_mux(pctrl , gpio_num, GPIO_FUNCTION);
            bsp_gpio_direction_output(gpio_num, gpio_value);
        }
    }
    else if(OUTER_RFSWITCH_OFF == status){
        for( i = 0 ; i < cnt ; i++ )
        {
            rf_pin     = g_ant_share.outside.gpio[i].rf_pin;

            gpio_num   = balong_rf_pin_to_gpio(rf_pin);
            pctrl      = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            ret        = balong_rf_pin_set_mux(pctrl, gpio_num ,ANT_FUNCTION);
        }
    }
    else
    {
        rf_print_error("para error, status=%d.\n", status);            
        ret = RFFE_ERROR;
    }

    return ret;
}
/*****************************************************************************
* 函 数    : bsp_anten_get_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择查询接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : 无

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_get_outer_rfswitch(unsigned int *status)
{
    unsigned int i      = 0;
    unsigned int func   = 0;
    unsigned int gpio   = 0;
    unsigned int cnt    = 0;
    int          ret    = 0;
    struct pinctrl *pctrl = NULL;

    if(NULL == status)
    {
        rf_print_error("para error,status is NULL!\n");
        return RFFE_ERROR;
    }

  
    cnt = g_ant_share.outside.num;
    for( i = 0 ; i < cnt ; i++ )
    {
        gpio  = balong_rf_pin_to_gpio(g_ant_share.outside.gpio[i].rf_pin);
        pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
        ret   = bsp_pinctrl_mux_get(pctrl);

        if(-1 == ret)
        {
            rf_print_error("pinctrl get mux error!\n");
            return ret;

        }        

        func |= (u32)ret;
    }
    
    if(0 == func)
    {
        *status = OUTER_RFSWITCH_ON;
    }
    else
    {
        *status = OUTER_RFSWITCH_OFF;
    }

    return 0;
}

/*****************************************************************************
* 函 数    : bsp_anten_set_mode
* 功 能    : DSP专用接口,GPIO共天线设置
* 输 入    : @mode:天线模式
*                   ANT_LTE     =  0, lte分集天线
*                   ANT_GSM     =  1, GSM副卡天线

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0:正确，-1:错误
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    unsigned int i     = 0;
    unsigned int gpio  = 0;
    unsigned int value = 0;
    unsigned int cnt   = 0;
    int          ret   = RFFE_OK; 
    struct pinctrl * pctrl = NULL;

    cnt = g_ant_share.inside.num;

    if(ANT_LTE == mode)
    {
        for( i = 0 ; i < cnt ; i++ )
        {
            /*获取gpio编号*/
            gpio  = balong_rf_pin_to_gpio(g_ant_share.inside.gpio[i].rf_pin);
            value = g_ant_share.inside.gpio[i].gpio_level;

            /*管脚复用为gpio 功能*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
            ret   = balong_rf_pin_set_mux(pctrl , gpio, GPIO_FUNCTION);

            /*配置gpio输出电平值*/
            bsp_gpio_direction_output(gpio, value);    

            /*更新dts normal配置*/
            bsp_pinctrl_mux_modify(pctrl, GPIO_FUNCTION);
            bsp_pinctrl_gpio_modify(pctrl,GPIO_OUTPUT, value);

        }
    }
    else if(ANT_GSM == mode)
    {
        for( i = 0 ; i < cnt ; i++ )
        {
            
            /*获取gpio编号*/
            gpio  = balong_rf_pin_to_gpio(g_ant_share.inside.gpio[i].rf_pin);

            /*管脚复用为线控功能*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
            ret   = balong_rf_pin_set_mux(pctrl, gpio, ANT_FUNCTION);

            /*更新dts normal配置*/
            bsp_pinctrl_mux_modify(pctrl, ANT_FUNCTION);

        }
    }
    else
    {
        rf_print_error("para error, mode=%d.\n", mode);
        ret = RFFE_ERROR;
    }

    return ret;
}

/*****************************************************************************
* 函 数    : bsp_anten_int_install
* 功 能    : 注册oam的天线插拔回调函数
* 输 入    : @modem id
                     @routine 回调函数
                     @ para 参数

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para)
{
    if(NULL == routine || (modem_id >= PWC_COMM_MODEM_BUTT))
    {
        rf_print_error("para is error, modem_id = %d, routine = 0x%x, para = %d.\n", modem_id, routine, para);
        return ;
    }
    g_detect.routine[modem_id] = (ANTEN_FUNCPTR)routine;
}

/*****************************************************************************
* 函 数    : bsp_rf_gpio_comm_config
* 功 能    : 射频gpio通用配置函数(参照18022nv )
* 输 入    : @nv_index nv编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int bsp_rf_gpio_comm_config(u32 nv_index, u32 modify_dts, u32 dts_mode)
{
    int ret = 0 ;

    if(!g_comm_gpio.profile[nv_index].enable)
    {
        return ret;/*nv 没使能，特性没打开*/
    }

    ret = balong_rf_gpio_comm_config(nv_index);
    if(modify_dts)
    {
        ret |=balong_rf_pin_dts_modify(nv_index, dts_mode);
    }
    return ret;
}

/*****************************************************************************
* 函 数    : bsp_rf_mipi_comm_config
* 功 能    : 射频mipi通用配置函数(参照18022nv )
* 输 入    : @nv_index nv编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int bsp_rf_mipi_comm_config(u32 nv_index)
{
    return balong_rf_mipi_comm_config(nv_index);
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_init
* 功 能    : 天线配置初始化
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_config_anten_init(void)
{
    int ret = 0;
    
    (void)memset_s((void*)&g_rfpin2gpio, sizeof(NV_FEMPIN_TO_GPIO_STRU), 0, sizeof(NV_FEMPIN_TO_GPIO_STRU));
    (void)memset_s((void*)&g_anten_info, sizeof(RFFE_PIN_ALL_CFG), 0, sizeof(RFFE_PIN_ALL_CFG));
    (void)memset_s((void*)&g_comm_gpio, sizeof(RF_GPIO_COMM_STRU), 0, sizeof(RF_GPIO_COMM_STRU));
    (void)memset_s((void*)&g_comm_mipi, sizeof(RF_MIPI_COMM_STRU), 0, sizeof(RF_MIPI_COMM_STRU));

    /*nv 18002 femio 通用配置接口*/
    ret = (int)bsp_nvm_read(en_NV_Item_FEM_GPIO_MIPI_CTRL, (u8*)&g_femio_info, sizeof(NV_FEM_GPIO_MIPI_CTRL_STRU));
    if (ret !=  0){
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_FEM_GPIO_MIPI_CTRL, ret);
    }

    /*nv 18003 rfpin2gpio info init*/
    ret = (int)bsp_nvm_read(en_NV_Item_FEM_PIN_TO_GPIO,(u8*)&g_rfpin2gpio,sizeof(NV_FEMPIN_TO_GPIO_STRU));
    if (ret !=  0)
    {
        rf_print_error("rf_anten read NV=0x%x, ret = %d \n",en_NV_Item_FEM_PIN_TO_GPIO, ret);
    }

    /*nv 18009 anten pin config nv info init*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_GPIO_INIT,(u8*)&g_anten_info,sizeof(RFFE_PIN_ALL_CFG));
    if (ret !=  0)
    {
        rf_print_error("anten pin config read NV=0x%x, ret = %d \n",en_NV_Item_RF_GPIO_INIT, ret);
    }

    
    /*nv 18010 Get ANTEN NV data by id.*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_ANT_DETECT,(u8*)&g_anten_status,sizeof(RF_ANTEN_DETECT_GPIO_STRU));
    if (ret !=  0)
    {
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_RF_ANT_DETECT, ret);
    }

    
    /*nv 18011 Get SHARED ANTEN NV data by id.*/
    ret = (int)bsp_nvm_read(en_NV_Item_ANT_SHARE_CONFIG,(u8*)&g_ant_share,sizeof(RF_ANT_SHARE_STRU));
    if (ret !=  0)
    {
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_ANT_SHARE_CONFIG, ret);
    }

    /*nv 18022 get gpio comm config nv by id*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_GPIO_COMM_CFG, (u8*)&g_comm_gpio, sizeof(RF_GPIO_COMM_STRU));
    if (ret != 0)
    {
        rf_print_error("get gpio comm config nv by id fail,ret=%d\n", ret);
    }

    /*nv 18023 get mipi comm config nv by id*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_MIPI_COMM_CFG, (u8*)&g_comm_mipi, sizeof(RF_MIPI_COMM_STRU));
    if (ret != 0)
    {
        rf_print_error("get mipi comm config nv by id fail,ret=%d\n", ret);
    }

    /*天线互扰问题初始化*/
    ret|= balong_tdsl_gsm_interference_init();
    if (ret !=  0)
    {
        rf_print_error("rffe tdsl gsm interference init fail, ret = %d \n",ret);
    }
    
    /*天线插拔检测初始化*/
    ret|= balong_anten_detect_init();
    if(ret)
    {
        rf_print_error("balong_anten_detect_init fail \n");
    }

    /*内置天线初始化为LTE */
    ret|= bsp_anten_set_mode(ANT_LTE);
    if(ret){
        rf_print_error("bsp_anten_set_mode_init fail ,ret = %d\n",ret);
    }
    return ret;
}


