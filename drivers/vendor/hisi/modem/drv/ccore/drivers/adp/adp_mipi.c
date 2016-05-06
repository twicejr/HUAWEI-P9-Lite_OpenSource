#include <osl_bio.h>
#include <osl_types.h>
#include <mdrv_mipi.h>
#include <bsp_om.h>
#include <bsp_mipi.h>
#include <bsp_hardtimer.h>

u32 g_mipi_debug = 0;

int mdrv_mipi_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    int ret       = 0;
    u8 read_value = 0;

    ret = bsp_mipi_write(mipi_id, slave_id, reg_addr, value);
    if(g_mipi_debug){
        ret =  bsp_mipi_read(mipi_id, slave_id, reg_addr, 0, &read_value);
        bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi id :%x, slave id :0x%x, reg_addr:0x%x, value:0x%x", mipi_id, slave_id, reg_addr, value);
        if(value != read_value){
            bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi write fail,write value is :0x%x, read back is:0x%x",value, read_value);
        }
    }
    return ret;
}

int mdrv_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value, u32 byte_cnt)
{
    int ret = 0;
    u32 read_value = 0;

    switch(byte_cnt){
        case MIPI_ONE_BYTE:
			ret = bsp_mipi_ex_write_byte(mipi_id, slave_id, reg_addr, (u8)value);
			break;
		case MIPI_TWO_BYTE:
			ret = bsp_mipi_ex_write_word(mipi_id, slave_id, reg_addr, (u16)value);
			break;
		case MIPI_THREE_BYTE:
			ret  = bsp_mipi_ex_write_byte(mipi_id, slave_id, reg_addr, (u8)value);
			ret |= bsp_mipi_ex_write_word(mipi_id, slave_id, reg_addr + 1, (u16)(value >> 8));
			break;
		case MIPI_FOUR_BYTE:
			ret = bsp_mipi_ex_write_dword(mipi_id, slave_id, reg_addr, value);
			break;
		default:
			bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi write can't surport over four bytes !byte count is %d\n",byte_cnt);
			return -1;
	}
    
    if(g_mipi_debug) {
        bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi id :%x, slave id :0x%x, reg_addr:0x%x, value:0x%x", mipi_id, slave_id, reg_addr, value);
        ret =  bsp_mipi_ex_read_dword(mipi_id, slave_id, reg_addr, 0, &read_value);
		read_value = read_value & (((u32)1 << (byte_cnt*8)) -1);
        if(value != read_value){
            bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi ex write fail,write value is :0x%x, read back is:0x%x\n",value, read_value);
        }
    }
    return ret;

}

int mdrv_mipi_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8* value)
{
    int ret  = 0;

    ret = bsp_mipi_read(mipi_id, slave_id, reg_addr, 0, value);
    if(g_mipi_debug) {
        bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi id 0x%x,slave id 0x%x, reg :0x%x, value:0x%x%\n",mipi_id, slave_id, reg_addr, *value);
	}
    return ret;
}

int mdrv_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32* value, u32 byte_cnt)
{
    u32 temp = 0;
    int ret  = 0;

    if(byte_cnt > MIPI_FOUR_BYTE) {
		bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi write can't surport over four bytes !byte count is %d\n",byte_cnt);
    }

    ret = bsp_mipi_ex_read_dword( mipi_id, slave_id, reg_addr, 0, &temp);
    *value = temp & (((u32)1 << (byte_cnt*8)) - 1);
    if(g_mipi_debug) {
        bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI,"mipi id 0x%x,slave id 0x%x, reg :0x%x, value:0x%x%\n",mipi_id, slave_id, reg_addr, *value);
	}
    return ret;

}
