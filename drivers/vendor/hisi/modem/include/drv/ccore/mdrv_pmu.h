#ifndef __MDRV_CCORE_PMU_H__
#define __MDRV_CCORE_PMU_H__
#ifdef __cplusplus
extern "C"
{
#endif


#include <mdrv_pm_common.h>
#include <mdrv_pm.h>

    /*
       int DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id);
       int DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, unsigned int voltage_mv );
       int DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, unsigned int *voltage_mv );
       int DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,unsigned short **list, unsigned int *size);
       int DRV_MODEM_APT_ENABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_APT_DISABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_APT_STATUS_GET(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_MODE_CONFIG(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       */

    typedef enum
    {
        TULPA_VCC,
        TULPA_VBIAS,
        GPA_VCC,
        GPA_VBIAS,
        RFIC_ANALOG0,
        RFIC_ANALOG1,
        FEM,

        CONSUMER_ID_BUTT
    }EX_RFFE_POWER_ID_E;

    typedef enum
    {
        DCXO_CFIX1,
        DCXO_CFIX2,
        DCXO_COMPENSATE_BUTT
    }DCXO_COMPENSATE_ID_E;

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_check_pastar
     *  功能描述  : 通信模块检查PASTAR是否有异常接口
     *  输入参数  : modem_id       卡号
     *  输出参数  : 无
     *  返 回 值  : 0          没有异常
     *             -1       存在异常
     ******************************************************************************/
    int mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id);

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_set_voltage
     *  功能描述  : 通信模块设置电压接口
     *  输入参数  : consumer_id     用户id
     *              voltage_mv      设置的电压值毫伏
     *  输出参数  : 无
     *  返 回 值  : 0       设置成功
     *             -1       设置失败
     ******************************************************************************/
    int mdrv_pmu_set_voltage( EX_RFFE_POWER_ID_E consumer_id, unsigned int voltage_mv , PWC_COMM_CHANNEL_E chn);


    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_get_voltage
     *  功能描述  : 通信模块获取电压接口
     *  输入参数  : consumer_id     用户id
     *              voltage_mv      获得的电压值毫伏
     *  输出参数  : 无
     *  返 回 值  : 0       获取成功
     *             -1       获取失败
     ******************************************************************************/
    int mdrv_pmu_get_voltage( EX_RFFE_POWER_ID_E consumer_id, unsigned int *voltage_mv, PWC_COMM_CHANNEL_E chn );

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_list_voltage
     *  功能描述  : 通信模块获取电压设置范围接口
     *  输入参数  : consumer_id     用户id
     *              list            电压范围数组
     *              size            数组大小
     *  输出参数  : 无
     *  返 回 值  : 0       获取成功
     *             -1       获取失败
     * *****************************************************************************/
    int mdrv_pmu_list_voltage(EX_RFFE_POWER_ID_E consumer_id, unsigned short **list, unsigned int *size);

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_enable_apt
     *  功能描述  : 通信模块使能APT接口
     *  输入参数  : modem_id       卡号
     *              mode_id        通信模式
     *  输出参数  : 无
     *  返 回 值  : 0      设置成功
     *             -1      设置失败
     ******************************************************************************/
    int mdrv_pmu_enable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_disable_apt
     *  功能描述  : 通信模块去使能APT接口
     *  输入参数  : modem_id       卡号
     *              mode_id        通信模式
     *  输出参数  : 无
     *  返 回 值  : 0         设置成功
     *             -1      设置失败
     ******************************************************************************/
    int mdrv_pmu_disable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_get_aptstatus
     *  功能描述  : 通信模块获取当前APT状态接口
     *  输入参数  : modem_id       卡号
     *              mode_id        通信模式
     *  输出参数  : 无
     *  返 回 值  : PWRCTRL_COMM_ON     APT使能
     *              PWRCTRL_COMM_OFF    APT未使能
     *                     -1           获取失败
     ******************************************************************************/
    int mdrv_pmu_get_aptstatus(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

     /*****************************************************************************
     *  函 数 名  : mdrv_pmu_dcxo_fre_compensate
     *  功能描述  : 为dcxo获取频率补偿
     *  输入参数  : value:需要调节的值
     *              
     *  输出参数  : 无
     *  返 回 值  : null
     *             
     ******************************************************************************/   
     void mdrv_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
    
    /*****************************************************************************
     *  函 数 名  : mdrv_pmu_set_lod27_ao
     *  功能描述  : 设置ldo27是否为常开状态
     					只在austin和v7r5中使用，其他产品形态不提供也不打桩
     *  输入参数  : ao:true时，常开ldo27，false时，ldo27正常上下电
     *              
     *  输出参数  : 无
     *  返 回 值  : 0      配置成功
     *             -1      配置失败
     ******************************************************************************/ 
    int mdrv_pmu_set_ldo27_ao(int ao);

#ifdef __cplusplus
}
#endif
#endif
