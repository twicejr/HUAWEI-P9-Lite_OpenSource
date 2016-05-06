/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  rf_power.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  用于管理射频器件供电
*
*   修改记录 :  2015年3月23日  v1.00  zuofenghua  创建
*
*************************************************************************/
#include <product_config.h>
#include <osl_sem.h>
#include <bsp_rf_balong.h>
#include <bsp_dpm.h>
#include <bsp_hardtimer.h>
#include <bsp_pmu.h>
#include <bsp_rsracc.h>
#include <rf_power.h>
#include <rf_anten_cfg.h>
#include <rf_mipi_cfg.h>

#define SEM_RFIC 0
#define SEM_FEM  1
#define SEM_PA   2
#define SEM_NUM  3

typedef struct{
    u64   vote[RF_PWR_CHN_NUM];
    u32   pwron_cnt[RF_PWR_CHN_NUM];
    u32   pwroff_cnt[RF_PWR_CHN_NUM];
    u32   true_pwron_cnt[RF_PWR_CHN_NUM];
    u32   true_pwroff_cnt[RF_PWR_CHN_NUM];
    u32   true_alloff_cnt;
    u32   pwron_time_stamp[RF_PWR_CHN_NUM];
    u32   pwroff_time_stamp[RF_PWR_CHN_NUM];
    u32   true_pwron_time_stamp[RF_PWR_CHN_NUM];
    u32   true_pwroff_time_stamp[RF_PWR_CHN_NUM];
    u32   true_alloff_time_stamp;
    u32   resume_time_stamp;
    u32   complete_timestamp;
    u32   suspend_late_timestamp;
    u32   reserved;
}RFFE_MIPI_ANTEN_CFG_S;

RFFE_MIPI_ANTEN_CFG_S rffe_cfg;

osl_sem_id rf_pwr_sem[SEM_NUM];

/*****************************************************************************
* 函 数    : mdrv_pmu_check_pastar
* 功 能    : 通信模块检查PASTAR是否有异常接口
* 输 入    : modem_id       卡号
* 输 出    : 无
* 返 回    : 0   没有异常，其它存在异常
* 作 者    : z00228752
* 说 明    : pa的编号根所chn号确定
*****************************************************************************/
s32 mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id)
{
    return 0;
}

/*****************************************************************************
* 函 数    : mdrv_pmu_set_voltage
* 功 能    : 通信模块设置电压接口
* 输 入    : consumer_id     电源id
* 输 出    : 无
* 返 回    : 0     设置成功，其它设置失败
* 作 者    : z00228752
* 说 明    :
*****************************************************************************/
s32 mdrv_pmu_set_voltage( EX_RFFE_POWER_ID_E consumer_id, u32 voltage_mv , PWC_COMM_CHANNEL_E chn)
{
    return balong_rfpower_set_voltage(consumer_id, voltage_mv, chn);
}

/*****************************************************************************
* 函 数    : mdrv_pmu_set_voltage
*
* 功 能    : 通信模块获取电压接口
* 输 入    : consumer_id     电源id
* 输 出    : 获得的电压值毫伏
* 返 回    : 0     获取成功，其它设置失败
* 作 者    : z00228752
* 说 明    :
*****************************************************************************/
s32 mdrv_pmu_get_voltage( EX_RFFE_POWER_ID_E consumer_id, u32 *voltage_mv, PWC_COMM_CHANNEL_E chn )
{
    int ret =  balong_rfpower_get_voltage(consumer_id, chn);

    if(RFFE_ERROR == ret){
       rf_print_error("rf ger voltage fail!consumer id is %d,ret is %d\n",consumer_id, ret);
       return ret;
    }

    *voltage_mv = (u32)ret / 1000;

    return RFFE_OK;
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_list_voltage
 功能描述  : 通信模块获取电压设置范围接口打桩
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : 0          获取成功
             else       获取失败
*****************************************************************************/
s32 mdrv_pmu_list_voltage(EX_RFFE_POWER_ID_E consumer_id,u16 **list, u32 *size)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_enable_apt
 功能描述  : 通信模块使能APT接口打桩
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : 0         设置成功
             else      设置失败
*****************************************************************************/
s32 mdrv_pmu_enable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return balong_rfpower_apt_enable(chn,  mode_id);
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_disable_apt
 功能描述  : 通信模块去使能APT接口打桩
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : 0         设置成功
             else      设置失败
*****************************************************************************/
s32 mdrv_pmu_disable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{

    return balong_rfpower_apt_disable(chn,  mode_id);
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_get_aptstatus
 功能描述  : 通信模块获取当前APT状态接口打桩
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : 1     APT使能
                        0    APT未使能
                       -1    获取失败
*****************************************************************************/
s32 mdrv_pmu_get_aptstatus(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return balong_rfpower_get_apt_status(chn);
}

/*****************************************************************************
 函 数 名  : mdrv_pmu_set_modem_mode
 功能描述  : 通信模块配置G模或W模接口打桩
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : 0         配置成功
             else      配置失败
*****************************************************************************/
s32 mdrv_pmu_set_modem_mode(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

/*****************************************************************************
* 函 数    : bsp_pa_power_up
* 功 能    : PA 上电接口
* 输 入    : 无
* 输 出    :
* 返 回    : 无
* 作 者    : pa电源开关状态
* 说 明    :
*****************************************************************************/
int bsp_pa_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_pa_power_on(mode, modem, chn);
}

/*****************************************************************************
* 函 数    : bsp_pa_power_down
* 功 能    : PA 下电打桩
* 输 入    : 无
* 输 出    :
* 返 回    : 无
* 作 者    : pa 电源开关状态
* 说 明    :
****************************************************************/
int bsp_pa_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_pa_power_off(mode, modem, chn);
}

/*****************************************************************************
* 函 数    : bsp_rfic_power_down
* 功 能    : RF 下电打桩
* 输 入    : 无
* 输 出    :
* 返 回    : 无
* 作 者    : rf电源开关状态
* 说 明    :
*****************************************************************************/
int bsp_rfic_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfic_power_off(mode, modem, chn);
}

/*****************************************************************************
 函数    : bsp_rfic_power_up
 功能    : RFIC 上电
 输入    : 无
 输出    : 无
 返回     : rf上电是否成功，0为成功,1为失败
*****************************************************************************/
int bsp_rfic_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfic_power_on(mode, modem, chn);
}

/*****************************************************************************
 函数    : bsp_rfclk_enable
 功能    : 打开RFIC 时钟buffer
 输入    : 无
 输出    : 无
 返回     : rf上电是否成功，0为成功,1为失败
*****************************************************************************/
int bsp_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfclk_enable(mode, modem, chn);
}

/*****************************************************************************
 函数    : bsp_rfic_power_up
 功能    : 关闭RFIC 时钟buffer
 输入    : 无
 输出    : 无
 返回    : rf上电是否成功，0为成功,1为失败
*****************************************************************************/
int bsp_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfclk_disable(mode, modem, chn);
}

/*****************************************************************************
* 函 数    : bsp_fem_power_down
* 功 能    : fem 下电打桩
* 输 入    : 无
* 输 出    :
* 返 回    : rf电源开关状态
* 作 者    : z00228752
* 说 明    :
*****************************************************************************/
int bsp_fem_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret        = 0;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    ret = balong_fem_power_off(mode, modem, chn);
    if(ret){
        rf_print_error("rfic power down faild\n");
        ret = RFFE_ERROR;
    }

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 函数    : bsp_fem_power_up
 功能    : RF 上电打桩
 输入    : 无
 输出    : 无
 返回    : rf电源开关状态
*****************************************************************************/
int bsp_fem_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = 0;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    ret = balong_fem_power_on(mode, modem, chn);

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 函 数 名  : bsp_rfic_power_status
 功能描述  : RF电源状态查询
 输入参数  :
 输出参数  :
 返 回 值  : rf电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_rfic_power_hw_status(mode,modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;

}

/*****************************************************************************
 函 数 名  :bsp_pa_power_status
 功能描述  :RF电源状态查询
 输入参数  :
 输出参数  :
 返 回 值  : pa电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_pa_power_hw_status(mode, modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;
}

/*****************************************************************************
 函数    : bsp_rfclk_is_enabled
 功能    : 查询RF clk是否打开
 输入    : 无
 输出    : 无
 返回    : rf电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_rfclk_is_enabled(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_rfclk_hw_status(mode, modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;
}

/*****************************************************************************
 函 数 名  :bsp_pa_power_status
 功能描述  :RF电源状态查询
 输入参数  :
 输出参数  :
 返 回 值  : pa电源开关状态
*****************************************************************************/
PWC_COMM_STATUS_E bsp_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_fem_power_hw_status(mode, modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;
}

/*****************************************************************************
 函数    : bsp_rffe_cfg_in_power_on
 功能    : 开机时mipi和线控配置
 输入    : 无
 输出    : 无
 返回     : mipi配置是否成功，0为成功,1为失败
*****************************************************************************/
int bsp_rffe_cfg_on_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    /*依赖fem的供电，所以使用其信号量*/
    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    first_on = !rffe_cfg.vote[chn];
    rffe_cfg.vote[chn] |= (u64)1 << vote_bit;
    if(first_on){
        ret  = balong_rf_config_by_mipi_modem_on((u32)chn);
        ret |= balong_rf_config_anten_poweron((u32)chn);

        rffe_cfg.true_pwron_cnt[chn]++;
        rffe_cfg.true_pwron_time_stamp[chn] = bsp_get_slice_value();
    }
    rffe_cfg.pwron_cnt[chn]++;
    rffe_cfg.pwron_time_stamp[chn] = bsp_get_slice_value();

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 函数    : bsp_rffe_cfg_on_power_down
 功能    : 开机时mipi和线控配置
 输入    : 无
 输出    : 无
 返回     : mipi配置是否成功，0为成功,1为失败
*****************************************************************************/
int bsp_rffe_cfg_on_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u64  cur_state  = 0;
    u32  vote_bit   = 0;
    int  ret        = 0;
    int  power_flag = 0;

    vote_bit = RF_PWR_MODE_NUM * modem + mode;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    cur_state      = rffe_cfg.vote[chn];
    rffe_cfg.vote[chn] &= ~((u64)1 << vote_bit);

    if((0 == rffe_cfg.vote[chn]) && cur_state){
        ret = balong_rf_config_by_mipi_modem_off(chn);
        ret |= balong_rf_config_anten_poweroff(chn);

        rffe_cfg.true_pwroff_cnt[chn]++;
        rffe_cfg.true_pwroff_time_stamp[chn] = bsp_get_slice_value();
    }

    power_flag = balong_fem_power_status(mode,modem, chn);
    if(!power_flag){
        ret  = balong_rf_config_by_mipi_allmodem_off();
        ret |= balong_rf_config_anten_allpoweroff();
        rffe_cfg.true_alloff_cnt++;
        rffe_cfg.true_alloff_time_stamp = bsp_get_slice_value();
    }
    rffe_cfg.pwroff_cnt[chn]++;
    rffe_cfg.pwroff_time_stamp[chn] = bsp_get_slice_value();

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;

}

int mdrv_rffe_cfg_on_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return bsp_rffe_cfg_on_power_up(mode, modem, chn);
}

int mdrv_rffe_cfg_on_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return bsp_rffe_cfg_on_power_down(mode, modem, chn);
}

#ifdef CONFIG_CCORE_PM
extern int bsp_rf_resume_early(struct dpm_device *dev);
extern int bsp_rf_complete(struct dpm_device *dev);
extern int bsp_rf_suspend_late(struct dpm_device *dev);
extern int bsp_rf_prepare(struct dpm_device *dev);
static struct dpm_device g_rf_dpm_device={
    .device_name = "rf_dpm",
    .prepare = bsp_rf_prepare,
    .suspend_early= NULL,
    .suspend = NULL,
    .suspend_late = bsp_rf_suspend_late,
    .resume_early = bsp_rf_resume_early,
    .resume = NULL,
    .resume_late = NULL,
    .complete = bsp_rf_complete,
};

/*resume*/
int bsp_rf_resume_early(struct dpm_device *dev)
{
    int ret = 0;

    ret  = balong_rf_power_resume();
    if(ret){
        rf_print_error("rffe power resume error!ret %d\n",ret);
    }

    rffe_cfg.resume_time_stamp = bsp_get_slice_value();
    return ret;
}

/*complete*/
int bsp_rf_complete(struct dpm_device *dev)
{
    int ret = 0;
    u32 time_stamp = 0;

    do{
        time_stamp = bsp_get_slice_value();
        udelay(5);
    }while(get_timer_slice_delta(rffe_cfg.resume_time_stamp , time_stamp) < 5);

    ret = balong_rf_config_by_mipi_resume();
    if(ret){
        rf_print_error("rffe resume mipi config error!ret %d\n",ret);
    }


    ret |= balong_rf_anten_resume();
    if(ret){
        rf_print_error("balong_rf_anten_resume fail!ret %d\n",ret);
    }

    rffe_cfg.complete_timestamp = bsp_get_slice_value();
    return ret;
}

int bsp_rf_prepare(struct dpm_device *dev)
{
    int ret = 0;

    ret = balong_rf_anten_suspend();
    if(ret){
        rf_print_error("rf anten error!ret is %d\n",ret);
    }

    return ret;
}

/*suspend*/
int bsp_rf_suspend_late(struct dpm_device *dev)
{
    int ret = 0;

    ret = balong_rf_power_suspend();
    if(ret){
        rf_print_error("rffe power suspend error!ret is %d\n",ret);
    }

    rffe_cfg.suspend_late_timestamp = bsp_get_slice_value();
    return ret;
}
s32 rf_suspend_begin(struct bd_desc_s *bd_descri)
{
    return bsp_rf_prepare(&g_rf_dpm_device);
}

void rf_suspend_end(struct bd_desc_s *bd_descri)
{
    (void)bsp_rf_suspend_late(&g_rf_dpm_device);
    return ;
}

void rf_resume_begin(struct bd_desc_s *bd_descri)
{
    (void)bsp_rf_resume_early(&g_rf_dpm_device);
    return ;
}

void rf_resume_end(struct bd_desc_s *bd_descri)
{
    (void)bsp_rf_complete(&g_rf_dpm_device);
    return ;
}

struct rsracc_cb_s g_rf_rsracc_ops = {
    .suspend_begin = rf_suspend_begin,
    .suspend_end     = rf_suspend_end,
    .resume_begin   = rf_resume_begin,
    .resume_end       = rf_resume_end,
 };
struct bd_desc_s rf_rsracc_device =
{
    .level = rsracc_bd_level_1,
    .name = "rf rsracc",
    .ops = &g_rf_rsracc_ops,
    .only_ops_in_bd = true,
};



#endif

/*todo :改名字*/
int bsp_rffe_init(void)
{
    int ret = 0;
    int i   = 0;

    for(i = 0; i < SEM_NUM; i++){
        osl_sem_init(1, &rf_pwr_sem[i]);
    }

    /*供电初始化*/
    ret  = balong_rf_power_init();
    if(ret){
        rf_print_error("rf power init fail,ret = %d\n",ret);
    }

    udelay(200);

    /*MIPI配置初始化*/
    ret = balong_rf_config_by_mipi_init();
    if(ret){
        rf_print_error("rf power init fail,ret = %d\n",ret);
    }

    /*射频线控配置初始化*/
    ret = balong_rf_config_anten_init();
    if(ret){
        rf_print_error("rf ant(gpio) init fail,ret = %d\n",ret);
    }
#ifdef CONFIG_CCORE_PM

    /*注册dpm 回调*/
    if(bsp_rsracc_support())
    {
        ret = bsp_rsracc_register((rsr_acc_description *)&rf_rsracc_device,1);
    }
    else
    {
        ret = bsp_device_pm_add(&g_rf_dpm_device);
        if(ret){
            rf_print_error("rffe add dpm device fail,ret = %d\n",ret);
        }
    }
#endif

    rf_print_error("bsp rf init end,ret is %d\n",ret);
    return ret;
}

/*help信息*/

/*供电投票查询*/

/*当前电源状态查询(开关、电压)*/

/*dts配置查询*/
