


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_cali_dpd.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CALI_DPD_C

/*****************************************************************************
  2 函数声明
*****************************************************************************/
//#define HI1102_DPD_CALI_LUT_LENGTH 128
#define DPD_CALI_GAIN_REF_IDX 49
#define DPD_CALI_AMP_REF_RMS 16
#define LUT_End_Point 10

#define GET2COMP(a) (a >= 1024)?(a-2048):(a)
#define SET2COMP(a) (a>=0)?(a):(2048+a)
#define absd(a) (a>=0)?(a):(-a)


/*****************************************************************************
  3 函数实现
*****************************************************************************/




// do_div(temp, 1024)
OAL_STATIC  oal_int32 hi1102_cali_div_round_closest(oal_int32 l_a, oal_int32 l_b)
{
    oal_int32 l_result = 0;
    if ((0 == l_b) || (0 == (l_b << 1)))
    {
        l_result = (oal_int32)l_a;
    }
    else
    {
        if (((l_a >= 0) && (l_b > 0)) || ((l_a <=0) && (l_b < 0)))
        {
            l_result = (oal_int32)(((l_a << 1) + l_b) / (l_b << 1));
        }
        else
        {
            l_result = (oal_int32)(((l_a << 1) - l_b) / (l_b << 1));
        }
    }

    return l_result;
}


OAL_STATIC oal_void dpd_cordic(oal_int32 l_real, oal_int32 l_image, oal_uint32* pl_amp, oal_int32* pl_theta1, oal_int32* pl_theta2)
{
   oal_uint8  us_idx = 0;
   oal_int32  l_x[13] = {0}, l_y[13] = {0};
   oal_int32  flag =0;

   oal_int32  l_real_table[13] = {1447, 1891, 2008, 2037, 2045, 2046, 2047, 2047, 2047, 2047, 2047, 2047, 2047},
              l_imag_table[13] = {1447, 783, 399, 201, 100, 50, 25, 13, 6, 3, 2, 1, 0};

   oal_int32  l_theta1 = 2047, l_theta2 = 0;
   oal_int32  l_temp1 = 0, l_temp2 = 0; /* real and image*/
   oal_int32  l_thetatmp1 = 0, l_thetatmp2 = 0;/* real and image*/
   oal_int32  l_divider = 2048;


   l_x[0] = absd(l_real);
   l_y[0] = absd(l_image);
   flag = absd(l_image);

   for (us_idx = 0; us_idx < 10; us_idx++)
   {
     if (flag > 0)
     {
        l_temp1 = l_real_table[us_idx] ;
        l_temp2 = - l_imag_table[us_idx];
     }
     else if (flag < 0)
     {
        l_temp1 = l_real_table[us_idx];
        l_temp2 = l_imag_table[us_idx];
     }
     else/*y=0*/
     {
        break;
     }

     l_x[us_idx + 1] = hi1102_cali_div_round_closest((l_x[us_idx] * l_temp1 -  l_y[us_idx] * l_temp2), l_divider);
     l_y[us_idx + 1] = hi1102_cali_div_round_closest((l_y[us_idx] * l_temp1 + l_x[us_idx] * l_temp2), l_divider);

     l_thetatmp1 = hi1102_cali_div_round_closest((l_theta1 * l_temp1  -  l_theta2 * l_temp2), l_divider);;
     l_thetatmp2 = hi1102_cali_div_round_closest(( l_theta2 * l_temp1 + l_theta1 * l_temp2), l_divider);
     l_theta1 = l_thetatmp1;
     l_theta2 = l_thetatmp2;

     flag =  l_y[us_idx + 1];
   }

   if (l_real < 0) { l_theta1 = - l_theta1; }
   if (l_image < 0) { l_theta2 = - l_theta2; }

   *pl_amp = (oal_uint32)l_x[us_idx];
   *pl_theta1 = (oal_int32)l_theta1;
   *pl_theta2 = (oal_int32)l_theta2;

   /* OAM_ERROR_LOG3(0, OAM_SF_CALIBRATE, "dpd_cordic: Amp=0x%08x, Theta1=%d, Thet2=%d\n\r",
                      *pl_amp, *pl_theta1, *pl_theta2);*/
}


oal_uint16  LUT_Gain[DPD_CALI_LUT_LENGTH], DPD_Gain[DPD_CALI_LUT_LENGTH];
hi1102_complex_stru  LUT_Theta[DPD_CALI_LUT_LENGTH], DPD_Theta[DPD_CALI_LUT_LENGTH];

// oal_memalloc(oal_uint32 ul_size)
oal_uint32 hi1102_rf_cali_dpd_corr_calc(oal_uint32* hi1102_dpd_cali_data_read, oal_uint32* hi1102_dpd_cali_data_calc)
{
   oal_uint8 idx = 0,  jdx =0;
   oal_uint32  l_amp = 0,  vrms =0;
   oal_int32 l_real = 0,l_imag =0;

  // oal_uint32  LUT_Gain[DPD_CALI_LUT_LENGTH] = {0};
  // oal_uint32  DPD_Gain[DPD_CALI_LUT_LENGTH] = {0};
   //hi1102_complex_stru  LUT_Theta[DPD_CALI_LUT_LENGTH] = {0};
  // hi1102_complex_stru  DPD_Theta[DPD_CALI_LUT_LENGTH] = {0};

   //oal_uint32  LUT_Gain[DPD_CALI_LUT_LENGTH], DPD_Gain[DPD_CALI_LUT_LENGTH];
   //hi1102_complex_stru  LUT_Theta[DPD_CALI_LUT_LENGTH], DPD_Theta[DPD_CALI_LUT_LENGTH];
   oal_uint32 pa_gain_target = 0;
   oal_int32  l_divider = 2048;
   oal_int32 l_dpd_real = 0, l_dpd_imag = 0;

   for(idx = 0; idx <DPD_CALI_LUT_LENGTH ; idx++)
   {
     l_real =  GET2COMP((((oal_uint32)(*(hi1102_dpd_cali_data_read + idx))) & 0x7ff));
     l_imag =  GET2COMP(((((oal_uint32)(*(hi1102_dpd_cali_data_read + idx))) >> 11) & 0x7ff));

     dpd_cordic(l_real, l_imag, &l_amp, &LUT_Theta[idx].l_real, &LUT_Theta[idx].l_imag);

     LUT_Gain[idx] = (oal_uint16)hi1102_cali_div_round_closest((oal_int64)(l_amp << 10) ,(oal_int64)(DPD_CALI_AMP_REF_RMS * (idx+ 1)));
   }

   pa_gain_target = LUT_Gain[DPD_CALI_GAIN_REF_IDX];

   for(idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++ )
   {
     if (LUT_Gain[idx] == 0)
     {
        return OAL_FAIL;
     }

     LUT_Gain[idx] = (oal_uint16)hi1102_cali_div_round_closest((oal_int64)pa_gain_target<<9, (oal_int64)LUT_Gain[idx]);
   }

   for(idx=0; idx < LUT_End_Point; idx++)
   {
     LUT_Gain[idx] = LUT_Gain[LUT_End_Point -1];
     LUT_Theta[idx] = LUT_Theta[LUT_End_Point - 1];
   }
   for (idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++)
   {
     DPD_Gain[idx] = LUT_Gain[idx];
   }

  // gain
   for(idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++)
   {
     vrms= ((DPD_CALI_AMP_REF_RMS *(idx + 1)) * LUT_Gain[idx])>>9;
     for(jdx= 0; jdx < (DPD_CALI_LUT_LENGTH - 1); jdx++)
     {
        if((vrms < ((DPD_CALI_AMP_REF_RMS *(jdx+2))))&&(vrms >=(DPD_CALI_AMP_REF_RMS *(jdx+1))))
        {
          DPD_Gain[idx]= LUT_Gain[jdx];
          break;
        }
        if(vrms < (DPD_CALI_AMP_REF_RMS))
        {
          DPD_Gain[idx] = LUT_Gain[0];
          break;
        }
        if(vrms>=(DPD_CALI_AMP_REF_RMS * DPD_CALI_LUT_LENGTH))
        {

          DPD_Gain[idx] = LUT_Gain[DPD_CALI_LUT_LENGTH-1];/* +
                        hi1102_cali_div_round_closest(((vrms- DPD_CALI_AMP_REF_RMS * DPD_CALI_LUT_LENGTH) *
                         (LUT_Gain[DPD_CALI_LUT_LENGTH-1]-LUT_Gain[DPD_CALI_LUT_LENGTH-2])),20);//16 */
           break;
        }
     }

    if(DPD_Gain[idx] > 1023)
    {
       DPD_Gain[idx] = 1023;
    }
   }

   // phase
   for(idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++)
   {
     vrms = (oal_uint32)(((DPD_CALI_AMP_REF_RMS *(idx + 1)) * DPD_Gain[idx]) >> 9);
     for(jdx = 0; jdx < (DPD_CALI_LUT_LENGTH - 1); jdx++)
     {
        if((vrms < ((DPD_CALI_AMP_REF_RMS *(jdx+2))))&&(vrms >=(DPD_CALI_AMP_REF_RMS *(jdx+1))))
        {
          DPD_Theta[idx] = LUT_Theta[jdx];
          break;
        }
        if(vrms < (DPD_CALI_AMP_REF_RMS))
        {
          DPD_Theta[idx] = LUT_Theta[0];
          break;
        }
        if(vrms>=(DPD_CALI_AMP_REF_RMS * DPD_CALI_LUT_LENGTH))
        {
          DPD_Theta[idx] = LUT_Theta[DPD_CALI_LUT_LENGTH - 1];
          break;
        }
     }
   }


   for(idx= 0; idx < DPD_CALI_LUT_LENGTH; idx++)
   {
/*
     OAM_ERROR_LOG4(0, OAM_SF_CALIBRATE,"DPD_Gain[%d]=%d, DPD_theta1=%d, DPD_theta2=%d\n\r", idx,DPD_Gain[idx], DPD_Theta[idx].l_real, DPD_Theta[idx].l_imag);
*/
     l_dpd_real = hi1102_cali_div_round_closest(DPD_Gain[idx] * DPD_Theta[idx].l_real, l_divider);
     l_dpd_imag = hi1102_cali_div_round_closest(DPD_Gain[idx] * DPD_Theta[idx].l_imag, l_divider);
     *(hi1102_dpd_cali_data_calc + idx) = (SET2COMP(l_dpd_real))| ((SET2COMP(l_dpd_imag))<<11);
/*
     OAM_ERROR_LOG4(0, OAM_SF_CALIBRATE,  "dpd_gain[%d] real=%d, image=%d, DPD_CAL=0x%06x\n\r", idx,
                     hi1102_cali_div_round_closest (DPD_Gain[idx] * DPD_Theta[idx].l_real, 2048),
                     hi1102_cali_div_round_closest(DPD_Gain[idx] * DPD_Theta[idx].l_imag, 2048),
                     (oal_uint32)(*(hi1102_dpd_cali_data_calc + idx)));*/
     //OAM_WARNING_LOG1(0, OAM_SF_CALIBRATE, "{hmac_dpd_cali_data_recv::[%x]!}\r\n",
     //(oal_uint32)(*(hi1102_dpd_cali_data_calc + idx)));
   }

   return OAL_SUCC;
}
#endif /* _PRE_WLAN_RF_1102CALI_DPD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

