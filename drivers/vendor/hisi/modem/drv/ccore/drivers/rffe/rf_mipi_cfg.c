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
#include <RfNvId.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_mipi.h>
#include <rf_power.h>
#include <rf_mipi_cfg.h>

RF_NV_MIPI_ALL_CFG g_mipi_info;

/*****************************************************************************
* 函 数    : balong_rf_mipi_write
* 功 能    : 射频MIPI配置接口
* 输 入    : @cmd: mipi cmd指针，@data: mipi数据指针
* 输 出    : 无
* 返 回    :
* 作 者    :z00228752
* 说 明    : 该接口支持1～4byte的写操作
*****************************************************************************/
int balong_rf_mipi_write(RF_NV_MIPI_CMD_STRU *cmd, RF_NV_MIPI_BYTE_DATA_STRU *data, int cnt, int max)
{
    int c_index    = 0;
    int d_index    = 0;
    int byte_cnt   = 0;
    u32 mipi_id    = 0;
    u32 slave_id   = 0;
    u32 reg_addr   = 0;
    u32 value      = 0;

    if(0 == cnt){
        return RFFE_OK;
    }
    if((NULL == cmd) || (NULL == data)){
        rf_print_error("para invalid !cmd 0x%x,data 0x%x\n",cmd,data);
        return RFFE_ERROR;
    }

    for( ; c_index < cnt ; )
    {
        byte_cnt = cmd[c_index].ByteCnt;
        slave_id = cmd[c_index].SlaveAddr;
        reg_addr = cmd[c_index].RegAddr;
        switch(byte_cnt){
            case MIPI_ONE_BYTE:
                mipi_id = data[d_index].MasterSel;
                value   = data[d_index].ByteData;
                if(0x20 > reg_addr){
                    bsp_mipi_write(mipi_id, slave_id, reg_addr, (u8)value);
                }
                else
                    bsp_mipi_ex_write_byte(mipi_id, slave_id, reg_addr, (u8)value);
                break;

            case MIPI_TWO_BYTE:
                mipi_id = data[d_index].MasterSel;
                value   = data[d_index].ByteData + (data[d_index + 1].ByteData << 8);
                bsp_mipi_ex_write_word(mipi_id, slave_id, reg_addr, (u16)value);
                break;

            case MIPI_THREE_BYTE:
                mipi_id = data[d_index].MasterSel;
                value   = data[d_index].ByteData + (data[d_index + 1].ByteData << 8);
                bsp_mipi_ex_write_word(mipi_id, slave_id, reg_addr, (u16)value);

                value   = data[d_index + 2].ByteData;
                reg_addr= reg_addr + 2;
                bsp_mipi_ex_write_byte(mipi_id, slave_id, reg_addr, (u8)value);
                break;

            case MIPI_FOUR_BYTE:
                mipi_id = data[d_index].MasterSel;
                value    = data[d_index].ByteData + \
                         (data[d_index + 1].ByteData << 8) + \
                         (data[d_index + 2].ByteData << 16) + \
                         (data[d_index + 3].ByteData << 24);
                bsp_mipi_ex_write_dword(mipi_id, slave_id, reg_addr, value);
                break;

            default:
                mipi_id = data[d_index].MasterSel;
                value    = data[d_index].ByteData + \
                         (data[d_index + 1].ByteData << 8) + \
                         (data[d_index + 2].ByteData << 16) + \
                         (data[d_index + 3].ByteData << 24);
                bsp_mipi_ex_write_dword(mipi_id, slave_id, reg_addr, value);
                rf_print_error("mipi data byte cnt surport 1,2,3,4bytes,but prara is 0x%x\n",byte_cnt);
        }

        c_index++;
        d_index += byte_cnt;
        if(d_index >= max){
            rf_print_error("mipi data byte cnt over max,data index is %d,max is %d\n",d_index,max);
        }
    }

    return RFFE_OK;
}

/*resume*/
static int balong_rf_config_by_mipi_init_cfg(void)
{
    int ret = 0;
    int max_bytes = 0;

    max_bytes = sizeof(g_mipi_info.init.usrid)/sizeof(u32);
    ret |= balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.init.usrid.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.init.usrid.MipiData, \
                               g_mipi_info.init.usrid.CmdValidCnt, \
                               max_bytes);

    max_bytes = sizeof(g_mipi_info.init.pa)/sizeof(u32);
    ret  = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.init.pa.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.init.pa.MipiData, \
                               g_mipi_info.init.pa.CmdValidCnt, \
                               max_bytes);

    max_bytes = sizeof(g_mipi_info.init.rfswitch)/sizeof(u32);
    ret |= balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.init.rfswitch.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.init.rfswitch.MipiData, \
                               g_mipi_info.init.rfswitch.CmdValidCnt, \
                               max_bytes);

    max_bytes = sizeof(g_mipi_info.init.tunner)/sizeof(u32);
    ret |= balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.init.tunner.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.init.tunner.MipiData, \
                               g_mipi_info.init.tunner.CmdValidCnt, \
                               max_bytes);

    max_bytes = sizeof(g_mipi_info.init.reserved)/sizeof(u32);
    ret |= balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.init.reserved.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.init.reserved.MipiData, \
                               g_mipi_info.init.reserved.CmdValidCnt, \
                               max_bytes);
    return ret;
}

/*resume*/
int balong_rf_config_by_mipi_resume(void)
{
    return balong_rf_config_by_mipi_init_cfg();
}

/*modem poweron*/
int balong_rf_config_by_mipi_modem_on(u32 chn_id)
{
    int ret       = 0;
    int max_bytes = 0;

    if(chn_id >= CHANNEL_NUM){
        rf_print_error("rffe mipi cfg para error,chn id is %d\n",chn_id);
        return RFFE_ERROR;
    }
    max_bytes = sizeof(g_mipi_info.pwron[chn_id])/sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.pwron[chn_id].MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.pwron[chn_id].MipiData, \
                               g_mipi_info.pwron[chn_id].CmdValidCnt,\
                               max_bytes);

    return ret;
}

/*one modem poweroff*/
int balong_rf_config_by_mipi_modem_off(u32 chn_id)
{
    int ret = 0;
    int max_bytes = 0;

    if(chn_id >= CHANNEL_NUM){
        rf_print_error("rffe mipi cfg para error,chn id is %d\n",chn_id);
        return RFFE_ERROR;
    }

    max_bytes = sizeof(g_mipi_info.pwroff[chn_id])/sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.pwroff[chn_id].MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.pwroff[chn_id].MipiData, \
                               g_mipi_info.pwroff[chn_id].CmdValidCnt, \
                               max_bytes);
    return ret;
}

/*all modem poweroff*/
int balong_rf_config_by_mipi_allmodem_off(void)
{
    int ret = 0;
    int max_bytes = 0;

    max_bytes = sizeof(g_mipi_info.all_pwroff)/sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_mipi_info.all_pwroff.MipiCmd ,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_mipi_info.all_pwroff.MipiData, \
                               g_mipi_info.all_pwroff.CmdValidCnt, \
                               max_bytes);
    return ret;
}

/*init*/
int balong_rf_config_by_mipi_init(void)
{
    int ret = 0;

    (void)memset_s((void*)&g_mipi_info, (unsigned int)sizeof(RF_NV_MIPI_ALL_CFG), 0, (unsigned int)sizeof(RF_NV_MIPI_ALL_CFG));

    /* mipi nv info init*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_MIPI_INIT,(u8*)&g_mipi_info,sizeof(RF_NV_MIPI_ALL_CFG));
    if (ret !=  0)
    {
        rf_print_error("rf_mipi read NV=0x%x, ret = %d \n",en_NV_Item_RF_MIPI_INIT, ret);
        return RFFE_ERROR;
    }

    ret = balong_rf_config_by_mipi_init_cfg();

    return ret;
}
