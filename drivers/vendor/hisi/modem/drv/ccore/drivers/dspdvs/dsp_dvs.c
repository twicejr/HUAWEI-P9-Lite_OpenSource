/*************************************************************************
*   版权所有(C) 2010-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  dsp_dvs.c
*
*   作    者 :  l00312158
*
*   描    述 :  本文件主要完成DSP的调压请求
*
*   修改记录 :  2015年11月10日  v1.00  l00312158  创建
*************************************************************************/
#ifdef __cplusplus
    extern "C" {
#endif

#include <osl_bio.h>
#include <osl_spinlock.h>
#include "securec.h"
#include <osl_common.h>
#include <string.h>
#include <stdio.h>

#include <bsp_sysctrl.h>
#include <of.h>
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"
#include "bsp_dump.h"
#include "bsp_hardtimer.h"
#include <bsp_tsensor.h>
#include <bsp_efuse.h>

#include "dsp_dvs.h"

struct dspdvs_req g_dspdvs_req;
struct dspdvs_ctrl g_dspdvs_ctrl;
struct dspdvs_respond g_dspdvs_respond;
struct dspdvs_mntn g_dspdvs_mntn;
DRV_DSPDVS_CFG_STRU g_dspdvs_enable_flag;
SRAM_SOC_TLDSP_INTERACTION_STRU *g_dspdvs_SocTldspInteraction = NULL;
u32 g_dspdvs_stamp;

/*************************************************************************
 函 数 名	: dspdvs_get_chiptype
 功能描述	: 读取efuse中的HPM值，获取芯片类型
 输入参数	: 无
 返 回 值	: 成功返回0，失败返回-1
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
int dspdvs_get_chiptype(void)
{
    u32 efuse_hpm = 0, hpm_temp1 = 0, hpm_temp2 = 0;
    s32 ret = 0;

    ret = bsp_efuse_read(&efuse_hpm, 13, 1);
    if(ret)
    {
        dspdvs_print("get HPM_val failed.\n");
        return DSPDVS_ERROR;
    }

    hpm_temp1 = efuse_hpm & 0x3ff;
    hpm_temp2 = (efuse_hpm >> 10) & 0x3ff;
    dspdvs_print("hpm_temp1 val is %d.\n", hpm_temp1);
    dspdvs_print("hpm_temp2 val is %d.\n", hpm_temp2);

    if((hpm_temp1 <= DSPDVS_HPM_VAL) || (hpm_temp2 <= DSPDVS_HPM_VAL))
    {
        g_dspdvs_ctrl.ss_chip_flag = SS_CHIP_TYPE_FLAG;
        dspdvs_print("This chip is SS_chip.\n");
    }
    else
    {
        dspdvs_print("This chip is not SS_chip.\n");
    }

    return DSPDVS_OK;
}

/*************************************************************************
 函 数 名	: dspdvs_dvs_func
 功能描述	: 根据调压请求，对dsp或者bbp进行调压，如果请求发起者是dsp的话，还需要在
              调压之后设置应答状态
 输入参数	: struct regulator *pmu_type:调压结构
              u32 voltage_req:需要的电压
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_dvs_func(struct regulator *pmu_type, s32 voltage_req)
{
    s32 voltage = 0;
    s32 ret = 0;
    u32 temp = 0;

    voltage = regulator_get_voltage(pmu_type);
    if(voltage < 0)
    {
        dspdvs_print("Get voltage failed!\n");
        return;
    }

    if(voltage_req == voltage)
    {
        return;
    }
    else
    {
        if((pmu_type == g_dspdvs_ctrl.bbpdvs_pmu) && (BBP_LOW_VOLTAGE == voltage_req))
        {
            if(SS_CHIP_TYPE_FLAG != g_dspdvs_ctrl.ss_chip_flag)
            {
                temp = bsp_tsensor_temptype_get();
                if(temp == en_temp_high)
                {
                    ret = regulator_set_voltage(pmu_type, voltage_req, voltage_req);
                    if(ret)
                    {
                        dspdvs_print("Set voltage failed!\n");
                        return;
                    }
                }
            }
        }
        else
        {
            ret = regulator_set_voltage(pmu_type, voltage_req, voltage_req);
            if(ret)
            {
                dspdvs_print("DspDvs failed!\n");
                return;
            }
        }
    }
    return;
}

/*************************************************************************
 函 数 名	: dspdvs_bbp_dvs_tsensor
 功能描述	: 当收到tsensor上报的温度后，对BBP进行压。在任务中调用。
 输入参数	: 无
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_bbp_dvs_tsensor(void)
{
    if(en_temp_low == g_dspdvs_ctrl.dsp_dvs_TsensorTempFlag)
    {
        dspdvs_dvs_func(g_dspdvs_ctrl.bbpdvs_pmu, BBP_HIGH_VOLTAGE);
    }
    else if(en_temp_high == g_dspdvs_ctrl.dsp_dvs_TsensorTempFlag)
    {
        if(HIGH_VOLTAGE_REQ == (g_dspdvs_mntn.stdspreqinfo.streqrecord[g_dspdvs_mntn.stdspreqinfo.ulcurrentptr].streq & 0xff))
        {
            return;
        }
        else
        {
            dspdvs_dvs_func(g_dspdvs_ctrl.bbpdvs_pmu, BBP_LOW_VOLTAGE);
        }
    }
    else
    {
        dspdvs_print("g_dspdvs_ctrl.dsp_dvs_TsensorTempFlag is illegal!\n");
        return;
    }

    return;
}


/*************************************************************************
 函 数 名	: dspdvs_dvsproc
 功能描述	: 判断调压请求，对dsp或者bbp进行调压
 输入参数	: u8 dvs_req_flag:调压请求状态
              struct regulator *pmu_type:调压结构
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_dvsproc(u8 dvs_req_flag, struct regulator *pmu_type)
{
    s32 high_voltage = 0;
    s32 low_voltage = 0;

    if(pmu_type == g_dspdvs_ctrl.bbpdvs_pmu)
    {
        high_voltage = BBP_HIGH_VOLTAGE;
        low_voltage  = BBP_LOW_VOLTAGE;
    }
    else
    {
        high_voltage = BBE_HIGH_VOLTAGE;
        low_voltage  = BBE_LOW_VOLTAGE;
    }

    if(HIGH_VOLTAGE_REQ == dvs_req_flag)
    {
        dspdvs_dvs_func(pmu_type, high_voltage);
    }
    else if(LOW_VOLTAGE_REQ == dvs_req_flag)
    {
        dspdvs_dvs_func(pmu_type, low_voltage);
    }
    else
    {
        dspdvs_print("Dsp_dvs_req is illegal!\n");
        return;
    }

    return;
}

/*************************************************************************
 函 数 名	: dspdvs_get_dspreq
 功能描述	: 获取调压请求字
 输入参数	: 无
 返 回 值	: 成功返回0，失败返回-1
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
int dspdvs_get_dspreq(void)
{
    u32 req = 0;

    if(g_dspdvs_SocTldspInteraction)
    {
        req = g_dspdvs_SocTldspInteraction->DvsFlag.DspDvsReq;
        g_dspdvs_req.req_timestamp = g_dspdvs_SocTldspInteraction->DvsFlag.DspDvsReq_timestamp;

        g_dspdvs_req.dspdvs_req_flag = (u8)(req >> 24);
        g_dspdvs_req.dspdvs_req_id = (u8)((req >> 16) & 0xff);
        g_dspdvs_req.dsp_dvs_req = (u8)((req >> 8) & 0xff);
        g_dspdvs_req.bbp_dvs_req = (u8)(req & 0xff);

        g_dspdvs_mntn.stdspreqinfo.streqrecord[g_dspdvs_mntn.stdspreqinfo.ulnxtptr].streq = req;
        g_dspdvs_mntn.stdspreqinfo.streqrecord[g_dspdvs_mntn.stdspreqinfo.ulnxtptr].streq_timestamp= g_dspdvs_req.req_timestamp;
        g_dspdvs_mntn.stdspreqinfo.ulcurrentptr = g_dspdvs_mntn.stdspreqinfo.ulnxtptr;
        g_dspdvs_mntn.stdspreqinfo.ulnxtptr = (g_dspdvs_mntn.stdspreqinfo.ulnxtptr + 1)%DSPDVS_MNTN_NUMBER;
    }
    else
    {
        return DSPDVS_ERROR;
    }

    return DSPDVS_OK;
}

/*lint -save -e701*/
/*************************************************************************
 函 数 名	: dspdvs_set_dsprespond
 功能描述	: 设置调压应答字
 输入参数	: u32 bbp_vol:bbp电压
              u32 dsp_vol:dsp电压
 返 回 值	: 成功返回0，失败返回-1
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
int dspdvs_set_dsprespond(u32 bbp_vol, u32 dsp_vol)
{
    u32 respond;

    if(BBP_HIGH_VOLTAGE == bbp_vol)
    {
        g_dspdvs_respond.bbp_dvs_respond = HIGH_VOLTAGE_REQ;
    }
    else
    {
        g_dspdvs_respond.bbp_dvs_respond = LOW_VOLTAGE_REQ;
    }

    if(BBE_HIGH_VOLTAGE == dsp_vol)
    {
        g_dspdvs_respond.dsp_dvs_respond = HIGH_VOLTAGE_REQ;
    }
    else
    {
        g_dspdvs_respond.dsp_dvs_respond = LOW_VOLTAGE_REQ;
    }

    g_dspdvs_respond.dspdvs_respond_flag = DSPDVS_RESPOND_FLAG;
    g_dspdvs_respond.dspdvs_respond_id = g_dspdvs_req.dspdvs_req_id;

    if(g_dspdvs_SocTldspInteraction)
    {
        respond = (u32)((g_dspdvs_respond.dspdvs_respond_flag << 24) | (g_dspdvs_respond.dspdvs_respond_id << 16)
                   | (g_dspdvs_respond.dsp_dvs_respond << 8) | g_dspdvs_respond.bbp_dvs_respond);

        g_dspdvs_SocTldspInteraction->DvsFlag.DspDvsRespond = respond;
        g_dspdvs_SocTldspInteraction->DvsFlag.DspDvsRespond_timestamp = bsp_get_slice_value();

        g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr].strespond = respond;
        g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr].strespond_timestamp = bsp_get_slice_value();
        g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr].stbbpvoltage = bbp_vol;
        g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr].stdspvoltage = dsp_vol;
        g_dspdvs_mntn.stdspdvsrespondinfo.ulcurrentptr = g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr;
        g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr = (g_dspdvs_mntn.stdspdvsrespondinfo.ulnxtptr + 1)%DSPDVS_MNTN_NUMBER;
    }
    else
    {
        return DSPDVS_ERROR;
    }

    return DSPDVS_OK;
}
/*lint -restore*/

/*************************************************************************
 函 数 名	: dspdvs_intproc
 功能描述	: DSP发送调压请求的中断处理函数
 输入参数	: 无
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_intproc(void)
{
    g_dspdvs_mntn.dspdvs_intcount++;

    g_dspdvs_ctrl.dspdvs_DspReqFlag = BSP_TRUE;

    /* 记录时间，定位中断丢失 */
    g_dspdvs_mntn.stintinfo.ulslice[g_dspdvs_mntn.stintinfo.ulptr] = bsp_get_slice_value();
    g_dspdvs_mntn.stintinfo.ulptr = (g_dspdvs_mntn.stintinfo.ulptr+1)%DSPDVS_MNTN_NUMBER;

    osl_sem_up(&g_dspdvs_ctrl.dspdvs_task_sem);

    return;
}

/*************************************************************************
 函 数 名	: dspdvs_tsensorreq
 功能描述	: 注册给tsensor模块，当温度低于阈值，tsensor会在中断里调用。
              当C核从低功耗被唤醒时，tsensor也会调用。
              当tsensor定时器到时间后，也会调用。
 输入参数	: 无
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_tsensorcallback(enum temp_type temp)
{
    g_dspdvs_mntn.dspdvs_tsensorreqcount++;

    g_dspdvs_ctrl.dspdvs_TsensorReqFlag = BSP_TRUE;

    g_dspdvs_ctrl.dsp_dvs_TsensorTempFlag = temp;

    /* 记录时间，定位中断丢失 */
    g_dspdvs_mntn.sttsensorreqinfo.req_info[g_dspdvs_mntn.sttsensorreqinfo.ulptr].ulslice = bsp_get_slice_value();
    g_dspdvs_mntn.sttsensorreqinfo.req_info[g_dspdvs_mntn.sttsensorreqinfo.ulptr].temperature = temp;
    g_dspdvs_mntn.sttsensorreqinfo.ulptr = (g_dspdvs_mntn.sttsensorreqinfo.ulptr+1)%DSPDVS_MNTN_NUMBER;

    osl_sem_up(&g_dspdvs_ctrl.dspdvs_task_sem);

    return;
}

/*************************************************************************
 函 数 名	: dspdvs_taskProc
 功能描述	: dspbbp调压任务
 输入参数	: 无
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void dspdvs_taskproc(void* obj)
{
    s32 ret = 0;
    s32 bbp_voltage = 0, dsp_voltage = 0;
    BSP_BOOL DspReqFlag;
    BSP_BOOL TsensorReqFlag;
    unsigned long irq_flags;

    /* coverity[no_escape] *//* coverity[loop_top] */
    while(1)
    {
        (void)osl_sem_downtimeout(&g_dspdvs_ctrl.dspdvs_task_sem, DSPDVS_WAIT_FOREVER);

        spin_lock_irqsave(&g_dspdvs_ctrl.spin_lock, irq_flags);

        DspReqFlag = g_dspdvs_ctrl.dspdvs_DspReqFlag;
        TsensorReqFlag = g_dspdvs_ctrl.dspdvs_TsensorReqFlag;
        g_dspdvs_ctrl.dspdvs_DspReqFlag = BSP_FALSE;
        g_dspdvs_ctrl.dspdvs_TsensorReqFlag = BSP_FALSE;

        spin_unlock_irqrestore(&g_dspdvs_ctrl.spin_lock, irq_flags);

        if(BSP_TRUE == DspReqFlag)
        {
            (void)dspdvs_get_dspreq();

            dspdvs_dvsproc(g_dspdvs_req.bbp_dvs_req, g_dspdvs_ctrl.bbpdvs_pmu);

            bbp_voltage = regulator_get_voltage(g_dspdvs_ctrl.bbpdvs_pmu);

            dspdvs_dvsproc(g_dspdvs_req.dsp_dvs_req, g_dspdvs_ctrl.dspdvs_pmu);

            dsp_voltage = regulator_get_voltage(g_dspdvs_ctrl.dspdvs_pmu);

            ret = dspdvs_set_dsprespond(bbp_voltage, dsp_voltage);
            if(ret)
            {
                dspdvs_print("Set_Dspdvs_Respond is failed!\n");
            }
        }

        if(BSP_TRUE == TsensorReqFlag)
        {
            dspdvs_bbp_dvs_tsensor();
        }
        /* coverity[loop_bottom] */
    }
}


/*************************************************************************
 函 数 名	: bsp_dsp_dvs_init
 功能描述	: 初始化函数
 输入参数	: 无
 返 回 值	: 无
 修改历史	:
 日    期	: 2015年11月17日
 作    者	: l00312158
 修改内容	:

*************************************************************************/
void bsp_dsp_dvs_init(void)
{
    s32 ret = 0;
    u32 size = 0;
    OSL_TASK_ID task_id;

    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_DSPDVS, (u8 *)&g_dspdvs_enable_flag, sizeof(DRV_DSPDVS_CFG_STRU)))
    {
        dspdvs_print("dspdvs read nv 0x%x error\n", NV_ID_DRV_DSPDVS);
        return;
    }

    if(1 == g_dspdvs_enable_flag.enable)
    {
        g_dspdvs_ctrl.dsp_pwrtype = DSP_PWRTYPE;
        g_dspdvs_ctrl.bbp_pwrtype = BBP_PWRTYPE;

        g_dspdvs_ctrl.dspdvs_pmu = regulator_get(NULL, g_dspdvs_ctrl.dsp_pwrtype);
        g_dspdvs_ctrl.bbpdvs_pmu = regulator_get(NULL, g_dspdvs_ctrl.bbp_pwrtype);
        if(NULL == g_dspdvs_ctrl.dspdvs_pmu || NULL == g_dspdvs_ctrl.bbpdvs_pmu)
        {
            dspdvs_print("get pmu device failed.\n");
            return;
        }

        ret = dspdvs_get_chiptype();
        if(ret)
        {
            dspdvs_print("Dspdvs_Get_Chiptype failed!\n");
            return;
        }

        ret = mdrv_getmeminfo(BSP_DDR_TYPE_SRAM_TLDSP_SHARED, (u32 *)(&g_dspdvs_SocTldspInteraction), &size);
        if(ret)
        {
		    dspdvs_print("mdrv_getmeminfo BSP_DDR_TYPE_SRAM_TLDSP_SHARED fail!");
		    return;
        }

        memset_s((void *)g_dspdvs_SocTldspInteraction, size, 0, size);

        osl_sem_init(0, &g_dspdvs_ctrl.dspdvs_task_sem);

        spin_lock_init(&g_dspdvs_ctrl.spin_lock);

        ret = osl_task_init("dsp_dvs_task", 1, 4096, (OSL_TASK_FUNC)dspdvs_taskproc, NULL, &task_id);
        if(ret)
        {
            dspdvs_print("Creat dsp_dvs_task failed!\n");
            return;
        }

        g_dspdvs_stamp = bsp_get_slice_value();

        dspdvs_dvs_func(g_dspdvs_ctrl.bbpdvs_pmu, BBP_LOW_VOLTAGE);

        dspdvs_dvs_func(g_dspdvs_ctrl.dspdvs_pmu, BBE_LOW_VOLTAGE);

        ret = bsp_ipc_int_connect(IPC_CCPU_INT_SRC_DSP_DVS, (VOIDFUNCPTR)dspdvs_intproc, 0);
        if(BSP_OK != ret)
        {
            dspdvs_print("mdrv_ipc_int_connect failed.\n");
            return;
        }

        ret = bsp_ipc_int_enable(IPC_CCPU_INT_SRC_DSP_DVS);
        if(BSP_OK != ret)
        {
            dspdvs_print("mdrv_ipc_int_enable failed.\n");
            return;
        }

        ret = bsp_tsensor_callback_regist((pTFUNCPTR)dspdvs_tsensorcallback);
        if(ret)
        {
            dspdvs_print("bsp_tesensor_callback_regist failed!\n");
            return;
        }

        dspdvs_print("DSPDVS init success!\n");
    }
    else
    {
        dspdvs_print("DSPDVS feature is not available!\n");
        return;
    }

    return;
}

void dspdvs_print_debug(void)
{
    u32 i;

    dspdvs_print("DSP_Req_Int count is 0x%x.\n",g_dspdvs_mntn.dspdvs_intcount);
    dspdvs_print("Tsensor_Req count is 0x%x.\n",g_dspdvs_mntn.dspdvs_tsensorreqcount);
    dspdvs_print("The chip_type is 0x%x.\n",g_dspdvs_ctrl.ss_chip_flag);

    for(i = 0; i < DSPDVS_MNTN_NUMBER; i++)
    {
        if(g_dspdvs_mntn.stintinfo.ulslice[i] != 0)
        {
            dspdvs_print("DSP_Req_Int slice is 0x%x.\n",g_dspdvs_mntn.stintinfo.ulslice[i]);
        }
    }

    for(i = 0; i < DSPDVS_MNTN_NUMBER; i++)
    {
        if(g_dspdvs_mntn.sttsensorreqinfo.req_info[i].ulslice != 0)
        {
            dspdvs_print("Tsensor_req is %d, Tsensor_Req slice is 0x%x.\n",g_dspdvs_mntn.sttsensorreqinfo.req_info[i].temperature,
                g_dspdvs_mntn.sttsensorreqinfo.req_info[i].ulslice);
        }
    }

    for(i = 0; i < DSPDVS_MNTN_NUMBER; i++)
    {
        if(g_dspdvs_mntn.stdspreqinfo.streqrecord[i].streq != 0)
        {
            dspdvs_print("DSP_Req is 0x%x,   slice is 0x%x.\n", g_dspdvs_mntn.stdspreqinfo.streqrecord[i].streq,
                g_dspdvs_mntn.stdspreqinfo.streqrecord[i].streq_timestamp);
        }

        if(g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[i].strespond != 0)
        {
            dspdvs_print("DSP_respond is 0x%x,   slice is 0x%x.\n", g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[i].strespond,
                g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[i].strespond_timestamp);
            dspdvs_print("DSP voltage is 0x%x,   BBP voltage is 0x%x.\n", g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[i].stdspvoltage,
                g_dspdvs_mntn.stdspdvsrespondinfo.strespondrecord[i].stbbpvoltage);
        }
    }
    return;
}


#ifdef __cplusplus
}
#endif

