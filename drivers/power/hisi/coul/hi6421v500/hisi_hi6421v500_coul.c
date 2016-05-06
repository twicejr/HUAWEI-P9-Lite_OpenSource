

#include "hisi_hi6421v500_coul.h"
#include <../hisi_coul_core.h>


extern struct atomic_notifier_head coul_fault_notifier_list;


static unsigned int last_eco_in  = 0;
static unsigned int last_eco_out = 0;
static int hisi_saved_abs_cc_mah = 0;

/*******************************************************
  Function:        hi6421v500_coul_set_nv_save_flag
  Description:     set coul nv save success flag
  Input:           nv_flag: success 1, fail 0
  Output:          NA
  Return:          NA
  Remark:          the flag is read by fastboot
*******************************************************/
void hi6421v500_coul_set_nv_save_flag(int nv_flag)
{
    unsigned char val = 0;
    
    val = HI6421V500_REG_READ(HI6421V500_NV_SAVE_SUCCESS);
    if (NV_SAVE_SUCCESS == nv_flag){
        HI6421V500_REG_WRITE(HI6421V500_NV_SAVE_SUCCESS, (val | NV_SAVE_BITMASK));
    } else {
        HI6421V500_REG_WRITE(HI6421V500_NV_SAVE_SUCCESS, (val & (~NV_SAVE_BITMASK)));
    }
}
/*******************************************************
  Function:        hi6421v500_coul_get_nv_read_flag
  Description:     get coul nv read success flag
  Input:           NA
  Output:          NA
  Return:          success:1 fail:0
  Remark:         the flag is written by fastboot
*******************************************************/
int hi6421v500_coul_get_nv_read_flag(void)
{
    unsigned char val = 0;
    
    val = HI6421V500_REG_READ(HI6421V500_NV_READ_SUCCESS); 
    if (val & NV_READ_BITMASK) 
    {
        return NV_READ_SUCCESS;
    } else {
        return NV_READ_FAIL;
    }
}
/*******************************************************
  Function:        hi6421v500_coul_get_use_saved_ocv_flag
  Description:     get the flag that use saved ocv
  Input:           NA
  Output:          NA
  Return:          1:saved ocv
                   0:not saved ocv
  Remark:          the flag is written by fastboot
*******************************************************/
int hi6421v500_coul_get_use_saved_ocv_flag(void)
{
    unsigned char val = 0;
    val = HI6421V500_REG_READ(HI6421V500_OCV_CHOOSE);
    if (val & USE_SAVED_OCV_FLAG){
        return 1;
    }else {
        return 0;
    }
}

/*******************************************************
  Function:        hi6421v500_coul_get_delta_rc_ignore_flag
  Description:     get delta rc ignore flag
  Input:           NA
  Output:          NA
  Return:          1:not calculate delta rc
                   0:calculate delta rc
  Remark:          the flag is written by fastboot
*******************************************************/

int hi6421v500_coul_get_delta_rc_ignore_flag(void)
{
    unsigned char use_delta_rc_flag = 0;
    use_delta_rc_flag = HI6421V500_REG_READ(HI6421V500_DELTA_RC_SCENE);
    if(use_delta_rc_flag & DELTA_RC_SCENE_BITMASK)
    {
        use_delta_rc_flag &= ~DELTA_RC_SCENE_BITMASK;//clear the flag after read
        HI6421V500_REG_WRITE(HI6421V500_DELTA_RC_SCENE,use_delta_rc_flag);
        return 1;        
    }
    return 0;
}

/*******************************************************
  Function:        hi6421v500_coul_is_battery_moved
  Description:     whether battery is moved
  Input:           NULL
  Output:          NULL
  Return:          0:not moved, 1: moved
********************************************************/
int hi6421v500_coul_is_battery_moved(void)
{
    unsigned char val;
    val = HI6421V500_REG_READ(HI6421V500_BATTERY_MOVE_ADDR);

    if (val == BATTERY_MOVE_MAGIC_NUM){
	    HI6421V500_COUL_INF("Battey not moved \n");
        return 0;
    }
    else {
	    HI6421V500_COUL_INF("Battey  moved \n");
        HI6421V500_REG_WRITE(HI6421V500_BATTERY_MOVE_ADDR, BATTERY_MOVE_MAGIC_NUM);
        return 1;
    }
}

/*******************************************************
  Function:        hi6421v500_coul_set_battery_move_magic
  Description:     set battery move magic num
  Input:           move flag 1:plug out 0:plug in
  Output:          NULL
  Return:          NULL
********************************************************/
void hi6421v500_coul_set_battery_move_magic(int move_flag)
{
    unsigned char val;
    if (move_flag){
        val = BATTERY_PLUGOUT_SHUTDOWN_MAGIC_NUM;
    } else {
        val = BATTERY_MOVE_MAGIC_NUM;
    }
    HI6421V500_REG_WRITE(HI6421V500_BATTERY_MOVE_ADDR, val);    
}

/*******************************************************
  Function:      hi6421v500_coul_get_fifo_depth
  Description:   get coul fifo depth
  Input:         NULL
  Output:        NULL
  Return:        depth of fifo
********************************************************/
static int hi6421v500_coul_get_fifo_depth(void)
{
    return FIFO_DEPTH;
}
/*******************************************************
  Function:      hi6421v500_coul_get_coul_time
  Description:   get coulomb total(in and out) time
  Input:         NULL
  Output:        NULL
  Return:        sum of total time
********************************************************/
static unsigned int hi6421v500_coul_get_coul_time(void)
{
    unsigned int cl_in_time = 0;
    unsigned int cl_out_time = 0;

    HI6421V500_REGS_READ(HI6421V500_CHG_TIMER_BASE,&cl_in_time,4);
    HI6421V500_REGS_READ(HI6421V500_LOAD_TIMER_BASE,&cl_out_time,4);

    return (cl_in_time + cl_out_time);
}

/*******************************************************
  Function:      hi6421v500_coul_get_coul_time
  Description:   clear coulomb total(in and out) time
  Input:         NULL
  Output:        NULL
  Return:        sum of total time
********************************************************/

static void hi6421v500_coul_clear_coul_time(void)
{
    unsigned int cl_time = 0;
    udelay(110); 
    HI6421V500_REGS_WRITE(HI6421V500_CHG_TIMER_BASE,&cl_time,4);
    HI6421V500_REGS_WRITE(HI6421V500_LOAD_TIMER_BASE,&cl_time,4);
}
/*******************************************************
  Function:      hi6421v500_coul_convert_regval2uv
  Description:   convert register value to uv
  Input:         reg_val:voltage reg value 
  Output:        NULL
  Return:        value of register in uV
  Remark:        1 bit = 225.1196 uv = 4.8/21322 V = 4.8/21322 * 1000 * 1000 uV = 24 * 1000 * 100/ 10661 uV
********************************************************/
static  int hi6421v500_coul_convert_regval2uv(short reg_val)
{
    s64 temp;

    if (reg_val & INVALID_TO_UPDATE_FCC) {
        reg_val &= (~INVALID_TO_UPDATE_FCC);
        //return -1;
    }

    temp = (s64)((s64)(reg_val)  * (s64)(24 * 1000 * 100));

    temp = div_s64(temp, 10661);

    temp = (s64) v_offset_a *temp;
    temp = div_s64(temp, 1000000);
    temp += v_offset_b;

    return (int)temp;
}

/*******************************************************
  Function:      hi6421v500_coul_convert_uv2regval
  Description:   convert uv value to Bit for register
  Input:         reg_val: uv
  Output:        NULL
  Return:        value of register in uV
  Remark:       1 bit = 225.1196 uv = 4.8/21322 V = 4.8/21322 * 1000 * 1000 uV =10661 /  24 * 1000 * 100 uV                   
********************************************************/
static  short hi6421v500_coul_convert_uv2regval(int uv_val)
{
    short ret;
    s64 temp;

    temp = (s64)(uv_val - v_offset_b);
    temp = temp * 1000000;
    temp = div_s64(temp, v_offset_a);

    temp = (s64)(temp * (s64)10661);
    temp = div_s64(temp,2400000);

    ret = (short)temp;

    return ret;
}

/*******************************************************
  Function:      hi6421v500_coul_convert_regval2ua
  Description:   convert register value to current(uA)
  Input:         reg_val:current reg value 
  Output:        NULL
  Return:        value of register in uA
  Remark:        10 mohm resistance: 1 bit = 5/10661 A = 5*1000*1000 / 10661 uA
                      20 mohm resistance: 1 bit = 10 mohm / 2
                      30 mohm resistance: 1 bit = 10 mohm / 3
  						high bit = 1 is in, 0 is out
********************************************************/
static  int hi6421v500_coul_convert_regval2ua(short reg_val)
{
    int ret;
    s64 temp;

    ret = reg_val;
    temp = (s64)(ret) * (s64)(1000 * 1000 * 5);
    temp = div_s64(temp, 10661);

    ret = temp / (R_COUL_MOHM/10);
    temp = (s64) c_offset_a *ret;
    ret = div_s64(temp, 1000000);
    ret += c_offset_b;
    return ret;
}

/*******************************************************
  Function:      hi6421v500_coul_convert_regval2uah
  Description:   hi6421v500 convert register value to uah
  Input:         reg_val:cc reg val 
  Output:        NULL
  Return:        uah value of reg
********************************************************/
static int hi6421v500_coul_convert_regval2uah(unsigned int reg_val)
{
    int ret;
    s64 temp;  
    u8 coul_clk_mode = 0;
    
    temp = reg_val;
    coul_clk_mode = HI6421V500_REG_READ(COUL_CLK_MODE_ADDR);
    if((coul_clk_mode & XO32K_MODE_MSK) == COUL_32K_CLK_MODE){
        temp = temp * BIT_FOR_UAH_32K;
    } else {
		temp = temp * BIT_FOR_UAH_DCXO_586;
    }
    temp = (s64)div_s64(temp, 10000000);

    temp = (s64) c_offset_a * temp;
    ret = div_s64(temp, 1000000);

    return ret;
}

/*******************************************************
  Function:      hi6421v500_coul_convert_uah2regval
  Description:   hi6421v500 convert uah value to reg
  Input:         reg_val:uah 
  Output:        NULL
  Return:        uah value in register
  Remark:       1bit = 1bit current * 0.11 c = 5/10661 * 11/100 c = 5/10661 * 11/100 * 1000/3600 mAh
                     = 11 / (10661*2*36) mAh = 11 * 1000/ (10661 *2 *36) uAh
                     = 11 * 125/ (10661* 9) uAh
********************************************************/
static int hi6421v500_coul_convert_uah2regval(unsigned int reg_val)
{
    int ret = 0;
    s64 temp;
    u8 coul_clk_mode = 0;
    
    temp = reg_val;
    temp = temp * 1000000;
    temp = div_s64(temp, c_offset_a);

    temp = temp * 10000000;
    coul_clk_mode = HI6421V500_REG_READ(COUL_CLK_MODE_ADDR);
    if( (coul_clk_mode & XO32K_MODE_MSK) == COUL_32K_CLK_MODE){
        temp =div_s64( temp, BIT_FOR_UAH_32K);
    } else {
		temp = div_s64(temp, BIT_FOR_UAH_DCXO_586);
    }

    ret = (int)temp;
    return ret;
}

/*******************************************************
  Function:      hi6421v500_coul_calculate_cc_uah
  Description:   value of out_uah - in_uah recorded by  coulomb
  Input:         NULL                  
  Output:        NULL
  Return:        value of  uah through coulomb
  Remark:        adjusted by offset integrated on time
********************************************************/
static int hi6421v500_coul_calculate_cc_uah(void)
{
    unsigned int cc_in = 0;
    unsigned int cc_out = 0;
    unsigned int cl_in_time, cl_out_time;
    int cc_uah_in = 0;
    int cc_uah_out = 0;
    int cc_uah = 0;
    HI6421V500_REGS_READ(HI6421V500_CL_IN_BASE, &cc_in, 4);
    HI6421V500_REGS_READ(HI6421V500_CL_OUT_BASE, &cc_out, 4);
    cc_uah_out = hi6421v500_coul_convert_regval2uah(cc_out);
    cc_uah_in  = hi6421v500_coul_convert_regval2uah(cc_in);

    HI6421V500_REGS_READ(HI6421V500_CHG_TIMER_BASE,&cl_in_time,4);
    HI6421V500_REGS_READ(HI6421V500_LOAD_TIMER_BASE,&cl_out_time,4);
    /* uah = uas/3600 = ua*s/3600 */
    cc_uah_in  -= div_s64((s64) cl_in_time * c_offset_b, 3600);
    cc_uah_out += div_s64((s64) cl_out_time * c_offset_b, 3600);
    cc_uah = cc_uah_out - cc_uah_in;

    HI6421V500_COUL_INF("ccout_reg=0x%x,ccin_reg = 0x%x, cl_out_time=%d, cl_in_time=%d, cc_adjust=%d uah\n",
           (unsigned int) cc_out, (unsigned int)cc_in, cl_out_time, cl_in_time, cc_uah);

    return cc_uah;
}

/*******************************************************
  Function:      hi6421v500_coul_save_cc_uah
  Description:   get coulomb total(in and out) time
  Input:         cc_uah:save cc uah                 
  Output:        NULL
  Return:        sum of total time
********************************************************/
static void hi6421v500_coul_save_cc_uah(int cc_uah)
{
    unsigned int reg;
	if (cc_uah > 0){
        reg = hi6421v500_coul_convert_uah2regval(cc_uah);
        udelay(110); 
        HI6421V500_REGS_WRITE(HI6421V500_CL_OUT_BASE, &reg, 4);
        reg = 0;
        HI6421V500_REGS_WRITE(HI6421V500_CL_IN_BASE, &reg, 4);
    } else {
        reg = hi6421v500_coul_convert_uah2regval(-cc_uah);
        udelay(110); 
        HI6421V500_REGS_WRITE(HI6421V500_CL_IN_BASE, &reg, 4);
        reg = 0;
        HI6421V500_REGS_WRITE(HI6421V500_CL_OUT_BASE, &reg, 4);
    }
	hi6421v500_coul_clear_coul_time();
}

/*******************************************************
  Function:        hi6421v500_coul_save_ocv
  Description:     coul save ocv
  Input:           ocv:ocv vol uv
                   invalid_fcc_up_flag: no update fcc 1,update 0
  Output:          NA
  Return:          NA
*******************************************************/
void hi6421v500_coul_save_ocv(int ocv, int invalid_fcc_up_flag)
{
    short ocvreg = hi6421v500_coul_convert_uv2regval(ocv);

    if (invalid_fcc_up_flag){
        ocvreg |= INVALID_TO_UPDATE_FCC;
    }
    HI6421V500_REGS_WRITE(HI6421V500_SAVE_OCV_ADDR,&ocvreg,2);
    HI6421V500_COUL_INF("save ocv, ocv=%d,reg=%d", ocv, ocvreg);
}

/*******************************************************
  Function:        hi6421v500_coul_clear_ocv
  Description:     clear ocv 
  Input:           NA
  Output:          NA
  Return:          NA
*******************************************************/
void hi6421v500_coul_clear_ocv(void)
{
    short ocvreg = 0;
    HI6421V500_REGS_WRITE(HI6421V500_SAVE_OCV_ADDR,&ocvreg,2);
}

/*******************************************************
  Function:        hi6421v500_coul_get_ocv
  Description:     get saved ocv 
  Input:           NA
  Output:          NA
  Return:          OCV(reg value)
*******************************************************/
short hi6421v500_coul_get_ocv(void)
{
    short ocvreg = 0;
    HI6421V500_REGS_READ(HI6421V500_SAVE_OCV_ADDR,&ocvreg,2);
    return ocvreg;
}

/*******************************************************
  Function:        hi6421v500_coul_save_ocv_temp
  Description:     coul save ocv temp
  Input:           ocv_temp: temp*10                   
  Output:          NA
  Return:          NA
*******************************************************/
void hi6421v500_coul_save_ocv_temp(short ocv_temp)
{
    HI6421V500_REGS_WRITE(HI6421V500_SAVE_OCV_TEMP_ADDR, &ocv_temp, 2);
    HI6421V500_COUL_INF("save ocv temp, ocv_temp=%d\n",ocv_temp);
}

/*******************************************************
  Function:        hi6421v500_coul_clear_ocv_temp
  Description:     clear ocv temp
  Input:           NA
  Output:          NA
  Return:          NA
*******************************************************/
void hi6421v500_coul_clear_ocv_temp(void)
{
    short ocv_temp = 0;
    HI6421V500_REGS_WRITE(HI6421V500_SAVE_OCV_TEMP_ADDR,&ocv_temp,2);
}

/*******************************************************
  Function:        hi6421v500_coul_get_ocv_temp
  Description:     get saved ocv temp
  Input:           NA
  Output:          NA
  Return:          OCV temp(temp*10)
*******************************************************/
short hi6421v500_coul_get_ocv_temp(void)
{
    short ocv_temp = 0;
    HI6421V500_REGS_READ(HI6421V500_SAVE_OCV_TEMP_ADDR,&ocv_temp,2);
    return ocv_temp;
}
/*******************************************************
  Function:        hi6421v500_coul_get_fcc_valid_up_flag
  Description:     get fcc update flag
  Input:           NA
  Output:          NA
  Return:          no up:1 is up:1
*******************************************************/
int  hi6421v500_coul_get_fcc_invalid_up_flag(void)
{
    short ocvreg = 0;    
    ocvreg = hi6421v500_coul_get_ocv();
    if (ocvreg & INVALID_TO_UPDATE_FCC){
        return 1;
    }
    return 0;
}
/*******************************************************
  Function:      hi6421v500_coul_get_battery_voltage_uv
  Description:   get battery voltage in uV
  Input:         NULL
  Output:        NULL
  Return:        battery voltage in uV
********************************************************/
int hi6421v500_coul_get_battery_voltage_uv(void)
{
    short regval;
    HI6421V500_REGS_READ(HI6421V500_V_OUT,&regval,2);
    return(hi6421v500_coul_convert_regval2uv(regval));
}

/*******************************************************
  Function:      hi6421v500_coul_get_battery_current_ua
  Description:   get battery current in uA
  Intput:        NULL
  Output:        NULL
  Return:        battery current in uA
********************************************************/
int hi6421v500_coul_get_battery_current_ua(void)
{
    short regval;
    HI6421V500_REGS_READ(HI6421V500_CURRENT,&regval,2);
    return hi6421v500_coul_convert_regval2ua(regval);
}
 /*******************************************************
  Function:      hi6421v500_coul_get_battery_vol_uv_from_fifo
  Description:   get battery vol in uv from fifo
  Intput:        fifo_order:fifo serial number 0-9
  Output:        NULL
  Return:        battery voltage in uv
********************************************************/
int hi6421v500_coul_get_battery_vol_uv_from_fifo(unsigned int fifo_order)
{
    short regval;
    if (fifo_order > 9){
        fifo_order = 0;        
    }
    HI6421V500_REGS_READ((HI6421V500_VOL_FIFO_BASE + 2*fifo_order),&regval,2);
	return (hi6421v500_coul_convert_regval2uv(regval));
}

/*******************************************************
  Function:      hi6421v500_coul_get_battery_cur_ua_from_fifo
  Description:   get battery cur in ua from fifo
  Intput:        fifo_order:fifo serial number 0-9
  Output:        NULL
  Return:        battery current in ua
********************************************************/
int hi6421v500_coul_get_battery_cur_ua_from_fifo(unsigned int fifo_order)
{
    short regval;
    if (fifo_order > 9){
        fifo_order = 0;        
    }
    HI6421V500_REGS_READ((HI6421V500_CUR_FIFO_BASE + 2*fifo_order),&regval,2);
	return (hi6421v500_coul_convert_regval2ua(regval));
}

/*******************************************************
  Function:      hi6421v500_coul_get_offset_current_mod
  Description:   get current offset mod
  Intput:        NULL
  Output:        NULL
  Return:        current offset mod value
********************************************************/
short hi6421v500_coul_get_offset_current_mod(void)
{
    short regval;
    HI6421V500_REGS_READ(HI6421V500_OFFSET_CUR_MODIFY_BASE, &regval, 2);
	return regval;
} 

/*******************************************************
  Function:        hi6421v500_coul_get_fifo_avg_data
  Description:     get coul fifo average vol/current value(uv/ua)
  Input:           NULL
  Output:          struct vcdata:avg , max and min cur, vol
  Return:          NULL
********************************************************/
static void hi6421v500_coul_get_fifo_avg_data(struct vcdata *vc)
{
    int i;
    short vol_reset_value = 0xffff;
    int abnormal_value_cnt = 0;
    static short vol_fifo[FIFO_DEPTH];
    static short cur_fifo[FIFO_DEPTH];
    int vol,cur;
    int max_cur, min_cur;
    int vols, curs;
    if( NULL == vc )
    {
        HI6421V500_COUL_INF("NULL point in [%s]\n", __func__);
   	    return;
    }
    for (i=0; i<FIFO_DEPTH; i++) {
        HI6421V500_REGS_READ(HI6421V500_VOL_FIFO_BASE+i*2, &vol_fifo[i], 2);
        HI6421V500_REGS_READ(HI6421V500_CUR_FIFO_BASE+i*2, &cur_fifo[i], 2);
    }


    if(vol_fifo[0] != vol_reset_value) {
        vol=hi6421v500_coul_convert_regval2uv(vol_fifo[0])/1000;
        cur=hi6421v500_coul_convert_regval2ua(cur_fifo[0])/1000;
    } else {
        vol = 0;
        cur = 0;
    }

    vols=vol;
    curs=cur;

    max_cur = min_cur = cur;

    for (i=1; i<FIFO_DEPTH; i++){
        if(vol_fifo[i] != vol_reset_value)
        {
            vol = hi6421v500_coul_convert_regval2uv(vol_fifo[i])/1000;
            cur = hi6421v500_coul_convert_regval2ua(cur_fifo[i])/1000;

            vols += vol;
            curs += cur;

            if (cur > max_cur){
                max_cur = cur;
            } else if (cur < min_cur){
                min_cur = cur;
            }
        } else {
            abnormal_value_cnt++;
        }
    }

    vol = vols/(FIFO_DEPTH - abnormal_value_cnt);
    cur = curs/(FIFO_DEPTH - abnormal_value_cnt);

    vc->avg_v = vol;
    vc->avg_c = cur;
    vc->max_c = max_cur;
    vc->min_c = min_cur;

    HI6421V500_COUL_INF("avg_v = %d, avg_c = %d, max_c = %d, min_c = %d \n", vc->avg_v,
		                             vc->avg_c, vc->max_c, vc->min_c);
}
 
/*******************************************************
  Function:      hi6421v500_coul_clear_cc_register
  Description:    clear coulomb uah record
  Input:          NULL
  Output:         NULL
  Return:         NULL
********************************************************/
static int hi6421v500_coul_get_abs_cc(void)
{
    return hisi_saved_abs_cc_mah;
}

/*******************************************************
  Function:      hi6421v500_coul_get_ate_a
  Description:   get v_offset a value 
  Input:         NULL
  Output:        NULL
  Return:        v_offset a value
********************************************************/
static int  hi6421v500_coul_get_ate_a(void)
{    
    unsigned short regval = 0;
    unsigned char  a_low  = 0;
    unsigned char  a_high = 0;
    a_low  = HI6421V500_REG_READ(HI6421V500_VOL_OFFSET_A_ADDR_1);
    a_high = HI6421V500_REG_READ(HI6421V500_VOL_OFFSET_A_ADDR_0);
    regval = (a_low | ((a_high & VOL_OFFSET_A_HIGH_VALID_MASK) << 1)) & VOL_OFFSET_A_VALID_MASK;
    return (VOL_OFFSET_A_BASE + regval*VOL_OFFSET_A_STEP);
}
/*******************************************************
  Function:      hi6421v500_coul_get_ate_b
  Description:   get v_offset b value
  Input:         NULL
  Output:        NULL
  Return:        v_offset b value
********************************************************/
static int hi6421v500_coul_get_ate_b(void)
{
    unsigned char regval = 0;   
    regval = HI6421V500_REG_READ(HI6421V500_VOL_OFFSET_B_ADDR);
    regval &= VOL_OFFSET_B_VALID_MASK;/*bit[2-6]*/
    return (VOL_OFFSET_B_BASE + regval*VOL_OFFSET_B_STEP);
}

/*******************************************************
  Function:      hi6421v500_coul_clear_cc_register
  Description:    clear coulomb uah record
  Input:          NULL
  Output:         NULL
  Return:         NULL
********************************************************/
static void hi6421v500_coul_clear_cc_register(void)
{
    int ccregval = 0;

    hisi_saved_abs_cc_mah += (hi6421v500_coul_calculate_cc_uah() / 1000);
    udelay(110);
    HI6421V500_REGS_WRITE(HI6421V500_CL_IN_BASE,&ccregval,4);
    HI6421V500_REGS_WRITE(HI6421V500_CL_OUT_BASE,&ccregval,4);
}

/*******************************************************
  Function:        hi6421v500_coul_set_low_vol_val
  Description:     set low int vol val
  Input:           vol_value:low int vol val(mV)
  Output:          NA
  Return:          NA.
********************************************************/
static void hi6421v500_coul_set_low_vol_val(int vol_mv)
{
    short regval = 0;
    regval = hi6421v500_coul_convert_uv2regval(vol_mv*1000);
    udelay(110);
    HI6421V500_REGS_WRITE(HI6421V500_VOL_INT_BASE, &regval, 2);
}
/*******************************************************
  Function:        hi6421v500_coul_check_version
  Description:     check coul version
  Input:           NA
  Output:          NA
  Return:          0:success -1:fail.
********************************************************/
static int hi6421v500_coul_check_version(void)
{
    int tryloop = 0;
    short version_reg = 0;
    do {
        HI6421V500_REGS_READ(HI6421V500_COUL_VERSION_ADDR, &version_reg, 1);
        HI6421V500_COUL_INF("do a dummy read, version is 0x%x\n", version_reg);
        udelay(500);
        if ((tryloop++) > 5){
            HI6421V500_COUL_ERR("version is not correct!\n");
            return -1;
        }
    } while(COUL_HI6421V5XX != version_reg);
    return 0;
}

/*******************************************************
  Function:        hi6421v500_coul_check_debug
  Description:     check coul debug reg
  Input:           NA
  Output:          NA
  Return:          0:success -1:fail.
********************************************************/
static int hi6421v500_coul_check_debug(void)
{
    u8    val    = 0;
    short ocvreg = 0;
    val = HI6421V500_REG_READ(HI6421V500_DEBUG_REG2);
    if (val & (~COUL_FIFO_CLEAR)){
        HI6421V500_COUL_ERR("debug reg2 is 0x%x\n",val);
    }
    val = HI6421V500_REG_READ(HI6421V500_DEBUG_REG);
    if(val){
        HI6421V500_COUL_ERR("debug reg is not 0x0\n");
        HI6421V500_REG_WRITE(HI6421V500_DEBUG_REG, 0x0);
        udelay(500);
        HI6421V500_REGS_WRITE(HI6421V500_SAVE_OCV_ADDR, &ocvreg, 2);
        udelay(500);
        return -1;
    }
    return 0;
}

/*******************************************************
  Function:        hi6421v500_coul_cali_adc
  Description:     coul calibration
  Input:           NA
  Output:          NA
  Return:          NA.
********************************************************/
static void hi6421v500_coul_cali_adc(void)
{
	unsigned char reg_val = 0;
    reg_val = HI6421V500_REG_READ(HI6421V500_COUL_STATE_REG);

    if (COUL_CALI_ING == reg_val){
    	HI6421V500_COUL_INF("cali ing, don't do it again!\n");
        return;
    }
	HI6421V500_COUL_INF("calibrate!\n");
	reg_val = HI6421V500_REG_READ(HI6421V500_COUL_CTRL_REG);
	/* Mode */
	reg_val = reg_val | COUL_CALI_ENABLE;
    udelay(110);
	HI6421V500_REG_WRITE(HI6421V500_COUL_CTRL_REG, reg_val);
}
/*******************************************************
  Function:        hi6421v500_coul_clear_irq
  Description:     clear coul interrupt
  Input:           NULL
  Output:          NULL
  Remark:          clear low vol/capacity INT before coul
                   self_adjust when start up
********************************************************/
static void hi6421v500_coul_clear_irq(void)
{   
    char val = 0x0F;
    HI6421V500_REG_WRITE(HI6421V500_COUL_IRQ_REG, val);
}
/*******************************************************
  Function:        hi6421v500_coul_enable_irq
  Description:     enable coul irq
  Input:           NULL
  Output:          NULL
  Return:          NULL
********************************************************/
 static void hi6421v500_coul_enable_irq(void)
 {
	unsigned char irq_enable_flag = ~((unsigned char)(COUL_VBAT_INT_MASK | COUL_CL_IN_MASK | COUL_CL_OUT_MASK));/*disable cl_int interrupt*/
	HI6421V500_REG_WRITE(HI6421V500_COUL_IRQ_MASK_REG, irq_enable_flag);
	HI6421V500_COUL_INF("Enable coul irq!\n");
 }
/*******************************************************
  Function:        hi6421v500_coul_disable_irq
  Description:     disable coul irq 
  Input:           NULL  
  Output:          NULL
  Return:          NULL
********************************************************/
 static void hi6421v500_coul_disable_irq(void)
 {
     char irq_disable_flag = (COUL_VBAT_INT_MASK | COUL_CL_IN_MASK | COUL_CL_OUT_MASK | COUL_CL_INT_MASK);
     HI6421V500_REG_WRITE(HI6421V500_COUL_IRQ_MASK_REG, irq_disable_flag);
     HI6421V500_COUL_INF("Mask coul irq!\n");
 }

/*******************************************************
  Function:        hi6421v500_coul_config_init
  Description:     hi6421v500 config init
  Input:           NULL
  Output:          NULL
  Return:          NULL
********************************************************/
static void hi6421v500_coul_chip_init(void)
{
    hi6421v500_coul_clear_irq();
    hi6421v500_coul_disable_irq();
    /*unmask coul eco*/
    udelay(110);
    HI6421V500_REG_WRITE(HI6421V500_COUL_ECO_MASK, 0);
    /* config coul Mode */
    udelay(110);
    HI6421V500_REG_WRITE(HI6421V500_COUL_CTRL_REG,DEFAULT_COUL_CTRL_VAL);
}

/*******************************************************
  Function:        hi6421v500_coul_show_key_reg
  Description:     show key register info for bug
  Input:           NULL
  Output:          NULL
  Return:          NULL
********************************************************/

void hi6421v500_coul_show_key_reg(void)
{
    int reg0=0;
    int reg1=0;
    int reg2=0;
    int reg3=0;
    int reg4=0;
    int reg5=0;
    int reg6=0;
    int reg7=0;

    udelay(50);
    HI6421V500_REGS_READ(0x1af,&reg0,1);
    HI6421V500_REGS_READ(0x179,&reg1,2);
    HI6421V500_REGS_READ(0x17b,&reg2,2);
    HI6421V500_REGS_READ(0x16b,&reg3,2);
    HI6421V500_REGS_READ(0x151,&reg4,1);
    HI6421V500_REGS_READ(0x152,&reg5,1);
    HI6421V500_REGS_READ(0x14f,&reg6,2);
    HI6421V500_REGS_READ(0x1a3,&reg7,2);

    HI6421V500_COUL_INF("\n"
              "0x1af(state)        = 0x%x, 0x179-0x17a(fifo0) = 0x%x,  0x17b-0x17c(fifo1) = 0x%x\n"
              "0x16b-0x16c(offset) = 0x%x, 0x151(ctrl)        = 0x%x,  0x152(reflash)     = 0x%x\n"
              "0x14f(cur vol)      = 0x%x, 0x1a3-0x1a4(offvol)= 0x%x\n",
               reg0,reg1,reg2,reg3,reg4,reg5,reg6,reg7);

}

/*******************************************************
  Function:        interrupt_notifier_work
  Description:     interrupt_notifier_work - send a notifier event to battery monitor.
  Input:           struct work_struct *work           ---- work queue
  Output:          NULL
  Return:          NULL
  Remark:          capacity INT : low level and shutdown level.
                   need to check by Test
********************************************************/
 static void hi6421v500_coul_interrupt_notifier_work(struct work_struct *work)
{
    struct hi6421v500_coul_device_info *di = container_of(work,
				struct hi6421v500_coul_device_info,
				irq_work.work);
	unsigned char intstat = 0;

    if( NULL == di || NULL == work)
    {
	  	HI6421V500_COUL_ERR(" [%s] NULL point in \n", __func__);
     	return;
    }
    intstat = di->irq_mask;
    di->irq_mask = 0;
    
	hi6421v500_coul_show_key_reg();
    
    if (intstat & COUL_VBAT_INT_MASK){
        HI6421V500_COUL_INF("IRQ: COUL_CCOUT_LOW_VOL_INT\n");
        atomic_notifier_call_chain(&coul_fault_notifier_list,COUL_FAULT_LOW_VOL, NULL);
    }
	if (intstat & COUL_CL_INT_MASK)
	{
	      HI6421V500_COUL_INF("IRQ: COUL_CCOUT_BIG_INT\n");
          atomic_notifier_call_chain(&coul_fault_notifier_list,COUL_FAULT_CL_INT, NULL);
	}
	if (intstat & COUL_CL_IN_MASK)
	{
		HI6421V500_COUL_INF("IRQ: COUL_CCIN_CNT_INT\n");
        atomic_notifier_call_chain(&coul_fault_notifier_list,COUL_FAULT_CL_IN, NULL);        
	}
	if (intstat & COUL_CL_OUT_MASK)
	{
		HI6421V500_COUL_INF("IRQ: COUL_CCOUT_CNT_INT\n");
        atomic_notifier_call_chain(&coul_fault_notifier_list,COUL_FAULT_CL_OUT, NULL);        
	}

}

/*******************************************************
  Function:        hi6421v500_coul_irq_cb
  Description:     hi6421v500 coul irq handler
  Input:            int irq                 ---- irq number
                       void *_di            ---- coul device
  Output:          NULL
  Return:          IRQ_NONE: irq not exist,  IRQ_HANDLED: be handled
********************************************************/
static irqreturn_t hi6421v500_coul_irq_cb(int irq,  void *_di)
{
    struct hi6421v500_coul_device_info *di = _di;
    unsigned char val = 0;

    HI6421V500_COUL_INF("coul_irq_cb irq=%d\n", irq);

    val = HI6421V500_REG_READ(HI6421V500_COUL_IRQ_REG);
    HI6421V500_COUL_INF("HI6421V500_IRQ_ADDR reg=%d\n", val);
    
    HI6421V500_REG_WRITE(HI6421V500_COUL_IRQ_REG,val);    

    di->irq_mask |= val;

    schedule_delayed_work(&di->irq_work, msecs_to_jiffies(0));

    return IRQ_HANDLED;
}
/*******************************************************
  Function:        hi6421v500_coul_calculate_eco_leak_uah
  Description:     calculate capacity leak from existing ECO MODE to calc soc first time
  Input:           NULL
  Output:          NULL
  Return:          leak capacity
  Remark:          ECO uah register keep the same value after exist from ECO
********************************************************/
static int hi6421v500_coul_calculate_eco_leak_uah(void)
{
    int rst_uah          = 0;
    int eco_uah          = 0;
    int cur_uah          = 0;
    int eco_in_uah       = 0;
    int eco_out_uah      = 0;
    int present_in_uah   = 0;
    int present_out_uah  = 0;
    unsigned int in_val  = 0;
    unsigned int out_val = 0;

    HI6421V500_REGS_READ(HI6421V500_ECO_OUT_CLIN_REG_BASE, &in_val, 4);
    HI6421V500_REGS_READ(HI6421V500_ECO_OUT_CLOUT_REG_BASE, &out_val, 4);
    /*if: first time to calc soc after exiting from ECO Mode */
    if ((last_eco_in != in_val) || (last_eco_out != out_val)) {
		eco_out_uah     = hi6421v500_coul_convert_regval2uah(out_val);
		eco_in_uah      = hi6421v500_coul_convert_regval2uah(in_val);
		eco_uah         = eco_out_uah - eco_in_uah;
        /* current cc  */
		HI6421V500_REGS_READ(HI6421V500_CL_OUT_BASE, &out_val, 4);
		HI6421V500_REGS_READ(HI6421V500_CL_IN_BASE, &in_val, 4);
		present_in_uah  = hi6421v500_coul_convert_regval2uah(in_val);
		present_out_uah = hi6421v500_coul_convert_regval2uah(out_val);
		cur_uah         = present_out_uah - present_in_uah;
		/* leak cc from exisingt eco mode to first calc soc */
	    rst_uah         = cur_uah - eco_uah;

	    HI6421V500_COUL_ERR("eco_in=%d,eco_out=%d,present_in=%d,present_out=%d,leak cc=%d .\n",
                                       eco_in_uah, eco_out_uah,present_in_uah, present_out_uah, rst_uah);
    } else {
        rst_uah = 0;
	    HI6421V500_COUL_INF("Not the FIRST time to calc soc after exiting from ECO Model, leak cc=0 .\n");
    }
    return rst_uah;
}

/*******************************************************
  Function:        hi6421v500_coul_clear_fifo
  Description:     clear coul vol/current fifo value
  Input:           NULL
  Output:          NULL
  Return:          NULL
  Remark:          NA
********************************************************/
static void hi6421v500_coul_clear_fifo(void)
{
	unsigned char reg_value = 0;
	reg_value = HI6421V500_REG_READ(HI6421V500_FIFO_CLEAR);
	HI6421V500_REG_WRITE(HI6421V500_FIFO_CLEAR, (reg_value | COUL_FIFO_CLEAR));
}
/*******************************************************
  Function:        hi6421v500_coul_enter_eco
  Description:     coul enter eco
  Input:           NULL
  Output:          NULL
  Return:          NULL
  Remark:          coul eco follow pmu eco
********************************************************/
static void hi6421v500_coul_enter_eco(void)
{
    unsigned char reg_val = 0;

    HI6421V500_REGS_READ(HI6421V500_ECO_OUT_CLIN_REG_BASE, &last_eco_in, 4);
    HI6421V500_REGS_READ(HI6421V500_ECO_OUT_CLOUT_REG_BASE, &last_eco_out, 4);

    reg_val = HI6421V500_REG_READ(HI6421V500_COUL_STATE_REG);
    if (COUL_CALI_ING == reg_val) {
    	HI6421V500_COUL_INF("cali ing, don't do it again!\n");

        reg_val= ECO_COUL_CTRL_VAL;
    } else {
        HI6421V500_COUL_INF("calibrate!\n");
        reg_val= (ECO_COUL_CTRL_VAL | COUL_CALI_ENABLE);
    }
    udelay(110);
	HI6421V500_REG_WRITE(HI6421V500_COUL_CTRL_REG,reg_val);
	hi6421v500_coul_clear_fifo();
}

/*******************************************************
  Function:        hi6421v500_coul_exit_eco
  Description:     coul exit eco
  Input:           NULL
  Output:          NULL
  Return:          NULL
  Remark:          coul eco follow pmu eco
********************************************************/
static void hi6421v500_coul_exit_eco(void)
{
	hi6421v500_coul_clear_fifo();
    udelay(110);
	HI6421V500_REG_WRITE(HI6421V500_COUL_CTRL_REG,DEFAULT_COUL_CTRL_VAL);
}

/*******************************************************
  Function:        hi6421v500_coul_set_hltherm_flag
  Description:     set coul hltherm flag for high and low temperature test
  Input:           temp_protect_flag: protect 1, no protect 0
  Output:          NA
  Return:          0:success
                   other :fail
*******************************************************/
int hi6421v500_coul_set_hltherm_flag(int temp_protect_flag)
{
    unsigned char val = 0;    
    val = HI6421V500_REG_READ(HI6421V500_COUL_TEMP_PROTECT);
    if (1 == temp_protect_flag){
        HI6421V500_REG_WRITE(HI6421V500_COUL_TEMP_PROTECT, (val | TEMP_PROTECT_BITMASK));
    } else {
        HI6421V500_REG_WRITE(HI6421V500_COUL_TEMP_PROTECT, (val & (~TEMP_PROTECT_BITMASK)));
    }
    return 0;
}
/*******************************************************
  Function:        hi6421v500_coul_get_hltherm_flag
  Description:     get hltherm flag
  Input:           NA
  Output:          NA
  Return:          1: tmep protect  0:no protect
*******************************************************/
int hi6421v500_coul_get_hltherm_flag(void)
{
    unsigned char val = 0;
    
    val = HI6421V500_REG_READ(HI6421V500_COUL_TEMP_PROTECT); 
    if (val & TEMP_PROTECT_BITMASK) 
    {
        return 1;
    } else {
        return 0;
    }
}

#ifdef CONFIG_SYSFS

static long g_reg_addr = 0;
ssize_t hi6421v500_coul_set_reg_sel(struct device *dev,
                  struct device_attribute *attr,
                  const char *buf, size_t count)
{
    int status = count;
	g_reg_addr = 0;
    if (strict_strtol(buf, 0, &g_reg_addr) < 0)
        return -EINVAL;
	return status;
}

ssize_t hi6421v500_coul_set_reg_value(struct device *dev,
                  struct device_attribute *attr,
                  const char *buf, size_t count)
{
    long val = 0;
	size_t status = count;
    if (strict_strtol(buf, 0, &val) < 0)
        return -EINVAL;
    HI6421V500_REG_WRITE(g_reg_addr,(char)val);
	return status;

}

ssize_t hi6421v500_coul_show_reg_info(struct device *dev,
                  struct device_attribute *attr,
                  char *buf)
{
    u8 val = 0;
    val = HI6421V500_REG_READ(g_reg_addr);
	return sprintf(buf,"reg[0x%x]=0x%x\n",(u32)g_reg_addr,val);
}

static DEVICE_ATTR(sel_reg, (S_IWUSR | S_IRUGO),
                NULL,
                hi6421v500_coul_set_reg_sel);
static DEVICE_ATTR(set_reg, (S_IWUSR | S_IRUGO),
                hi6421v500_coul_show_reg_info,
                hi6421v500_coul_set_reg_value);

static struct attribute *hi6421v500_coul_attributes[] = {
    &dev_attr_sel_reg.attr,
    &dev_attr_set_reg.attr,
    NULL,
};

static const struct attribute_group hi6421v500_coul_attr_group = {
    .attrs = hi6421v500_coul_attributes,
};
#endif

struct coul_device_ops hi6421v500_coul_ops =
{  
    .calculate_cc_uah             = hi6421v500_coul_calculate_cc_uah,
    .save_cc_uah                  = hi6421v500_coul_save_cc_uah,
    .convert_regval2ua            = hi6421v500_coul_convert_regval2ua,
    .convert_regval2uv            = hi6421v500_coul_convert_regval2uv,
    .convert_uv2regval            = hi6421v500_coul_convert_uv2regval,
    .is_battery_moved             = hi6421v500_coul_is_battery_moved,
    .set_battery_moved_magic_num  = hi6421v500_coul_set_battery_move_magic,
    .get_fifo_depth               = hi6421v500_coul_get_fifo_depth,
    .get_fifo_avg_data            = hi6421v500_coul_get_fifo_avg_data,
    .get_delta_rc_ignore_flag     = hi6421v500_coul_get_delta_rc_ignore_flag,
    .get_nv_read_flag             = hi6421v500_coul_get_nv_read_flag,
    .set_nv_save_flag             = hi6421v500_coul_set_nv_save_flag,
    .set_hltherm_flag             = hi6421v500_coul_set_hltherm_flag,
    .get_hltherm_flag             = hi6421v500_coul_get_hltherm_flag,
    .get_use_saved_ocv_flag       = hi6421v500_coul_get_use_saved_ocv_flag,
    .get_fcc_invalid_up_flag      = hi6421v500_coul_get_fcc_invalid_up_flag,
    .save_ocv                     = hi6421v500_coul_save_ocv,
    .get_ocv                      = hi6421v500_coul_get_ocv,
    .clear_ocv                    = hi6421v500_coul_clear_ocv,
    .save_ocv_temp                = hi6421v500_coul_save_ocv_temp,
    .get_ocv_temp                 = hi6421v500_coul_get_ocv_temp,
    .clear_ocv_temp               = hi6421v500_coul_clear_ocv_temp,    
    .set_low_low_int_val          = hi6421v500_coul_set_low_vol_val,
    .get_abs_cc                   = hi6421v500_coul_get_abs_cc,
    .get_coul_time                = hi6421v500_coul_get_coul_time,
    .clear_coul_time              = hi6421v500_coul_clear_coul_time,
    .clear_cc_register            = hi6421v500_coul_clear_cc_register,
    .cali_adc                     = hi6421v500_coul_cali_adc,
    .get_battery_voltage_uv       = hi6421v500_coul_get_battery_voltage_uv,
    .get_battery_current_ua       = hi6421v500_coul_get_battery_current_ua,
    .get_battery_vol_uv_from_fifo = hi6421v500_coul_get_battery_vol_uv_from_fifo,
    .get_battery_cur_ua_from_fifo = hi6421v500_coul_get_battery_cur_ua_from_fifo,
    .get_offset_current_mod       = hi6421v500_coul_get_offset_current_mod,
    .get_ate_a                    = hi6421v500_coul_get_ate_a,
    .get_ate_b                    = hi6421v500_coul_get_ate_b,
    .irq_enable                   = hi6421v500_coul_enable_irq,
    .show_key_reg                 = hi6421v500_coul_show_key_reg,
    .enter_eco                    = hi6421v500_coul_enter_eco,
    .exit_eco                     = hi6421v500_coul_exit_eco,
    .calculate_eco_leak_uah       = hi6421v500_coul_calculate_eco_leak_uah,
};


/*******************************************************
  Function:        hi6421v500_coul_probe
  Description:     hi6421v500 probe function
  Input:           struct platform_device *pdev  ---- platform device
  Output:          NULL
  Return:          NULL
********************************************************/
static int  hi6421v500_coul_probe(struct platform_device *pdev)
{
    struct coul_device_ops *coul_core_ops = NULL;
    struct hi6421v500_coul_device_info *di = NULL;
    struct device_node* np;
    int retval = 0;
    struct class *power_class = NULL;

    di = (struct hi6421v500_coul_device_info *)devm_kzalloc(&pdev->dev, sizeof(*di), GFP_KERNEL);
    if (!di) {
		HI6421V500_COUL_ERR("%s failed to alloc di struct\n",__FUNCTION__);
        return -1;
    }
    di->dev =&pdev->dev; 
    np = di->dev->of_node;
    if(NULL == np){
        HI6421V500_COUL_ERR("%s np is null!\n",__FUNCTION__);
        return -1;
    }
    di->irq = platform_get_irq_byname(pdev,"coulirq");
    if(di->irq < 0) {
        HI6421V500_COUL_ERR("failed to get irq resource!\n");
        return -1;
    }    

    platform_set_drvdata(pdev, di);
    
    if (hi6421v500_coul_check_version()){
        retval = -EINVAL;
        goto hi6521v500_failed_0;
    }

    if (hi6421v500_coul_check_debug()){
        retval = -EINVAL;
        goto hi6521v500_failed_0;
    } 
    
    /*config coul ctrl and irq */
    hi6421v500_coul_chip_init();
    
    /* Init interrupt notifier work */
    INIT_DELAYED_WORK(&di->irq_work, hi6421v500_coul_interrupt_notifier_work);    
	retval = request_irq(di->irq, hi6421v500_coul_irq_cb, IRQF_NO_SUSPEND, pdev->name, di);
    if (retval){
        HI6421V500_COUL_ERR("Failed to request coul irq\n");
        goto hi6421v500_failed_1;
    }
    /* set shutdown vol level */
    hi6421v500_coul_set_low_vol_val(DEFAULT_BATTERY_VOL_0_PERCENT);
   
    //set_low_capacity_int_reg(di);
	hi6421v500_coul_enable_irq();

    coul_core_ops = &hi6421v500_coul_ops;   
 	retval = coul_core_ops_register(coul_core_ops);
    if (retval) {
        HI6421V500_COUL_ERR("failed to register coul ops\n");
        goto hi6421v500_failed_2;
    }

    retval = sysfs_create_group(&di->dev->kobj, &hi6421v500_coul_attr_group);
    if (retval) {
        HI6421V500_COUL_ERR("%s failed to create sysfs group!!!\n", __FUNCTION__);
        goto hi6421v500_failed_3;
    }
    power_class = hw_power_get_class();
    if (power_class)
    {
        if (NULL == coul_dev){
            coul_dev = device_create(power_class, NULL, 0, "%s", "coul");
            if(IS_ERR(coul_dev)){
                coul_dev = NULL;
            }
        }        
        if (coul_dev) {
            retval = sysfs_create_link(&coul_dev->kobj, &di->dev->kobj, "hi6421v500_coul");
            if(0 != retval)
                HI6421V500_COUL_ERR("%s failed to create sysfs link!!!\n", __FUNCTION__);
        } else {
            HI6421V500_COUL_ERR("%s failed to create new_dev!!!\n", __FUNCTION__);
        }
    }    
    HI6421V500_COUL_INF("hi6421v500 coul probe ok!\n");
    return 0;
    
hi6421v500_failed_3:
    sysfs_remove_group(&di->dev->kobj, &hi6421v500_coul_attr_group);    
hi6421v500_failed_2:
    hi6421v500_coul_disable_irq();
	free_irq(di->irq, di);
hi6421v500_failed_1: 
    cancel_delayed_work(&di->irq_work);
hi6521v500_failed_0:
    platform_set_drvdata(pdev,NULL);
    HI6421V500_COUL_ERR("hi6421v500 coul probe failed!\n");
    return retval;
}

/*******************************************************
  Function:        hi6421v500_coul_remove
  Description:     remove function
  Input:           struct platform_device *pdev        ---- platform device
  Output:          NULL
  Return:          NULL
********************************************************/
static int  hi6421v500_coul_remove(struct platform_device *pdev)
{
    struct hi6421v500_coul_device_info *di = platform_get_drvdata(pdev);

    if(NULL == di)
    {
        HI6421V500_COUL_ERR("[%s]di is null\n",__FUNCTION__);
        return -ENODEV;
    }
    //cancel_delayed_work(&di->irq_work);
    kfree(di);
    di = NULL;
    return 0;
}


static struct of_device_id hi6421v500_coul_match_table[] =
{
    {
          .compatible = "hisilicon,hi6421v500_coul",
    },
    {},
};


static struct platform_driver hi6421v500_coul_driver = {
	.probe		= hi6421v500_coul_probe,
	.remove		= hi6421v500_coul_remove,
	.driver		= {
	   .name		   = "hi6421v500_coul",
       .owner          = THIS_MODULE,
       .of_match_table = hi6421v500_coul_match_table,
	},
};

int __init hi6421v500_coul_init(void)
{
    return platform_driver_register(&hi6421v500_coul_driver);
}

void __exit hi6421v500_coul_exit(void)
{
    platform_driver_unregister(&hi6421v500_coul_driver);
}

arch_initcall_sync(hi6421v500_coul_init);
module_exit(hi6421v500_coul_exit);


MODULE_AUTHOR("HISILICON");
MODULE_DESCRIPTION("hisi hi6421v500 coul driver");
MODULE_LICENSE("GPL");
