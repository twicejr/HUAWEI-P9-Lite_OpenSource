


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_types.h"
#include "hmac_wapi_sms4.h"
#include "hmac_wapi_wpi.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_WAPI_WPI_C

#ifdef _PRE_WLAN_FEATURE_WAPI



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
3 函数实现
*****************************************************************************/

oal_uint32  hmac_wpi_encrypt(oal_uint8 *puc_iv, oal_uint8 *puc_bufin, oal_uint32 ul_buflen,
                       oal_uint8 *puc_key, oal_uint8* puc_bufout)
{
    oal_uint32       aul_iv_out[4];
    oal_uint32      *pul_in;
    oal_uint32      *pul_out;
    oal_uint8       *puc_out;
    oal_uint8       *puc_in;
    oal_uint32       ul_counter;
    oal_uint32       ul_comp;
    oal_uint32       ul_loop;
    oal_uint32       aul_pr_keyin[32];


    if (ul_buflen < 1)
    {
#ifdef WAPI_DEBUG_MODE
        g_stMacDriverStats.ulSms4OfbInParmInvalid++;
#endif
        return OAL_FAIL;
    }

    hmac_sms4_keyext(puc_key,  aul_pr_keyin);

    ul_counter = ul_buflen / 16;
    ul_comp    = ul_buflen % 16;

    /*get the iv*/
    hmac_sms4_crypt(puc_iv,(oal_uint8 *)aul_iv_out, aul_pr_keyin);
    pul_in  = (oal_uint32 *)puc_bufin;
    pul_out = (oal_uint32 *)puc_bufout;

    for (ul_loop=0; ul_loop < ul_counter; ul_loop++)
    {
        pul_out[0] = pul_in[0] ^ aul_iv_out[0];
        pul_out[1] = pul_in[1] ^ aul_iv_out[1];
        pul_out[2] = pul_in[2] ^ aul_iv_out[2];
        pul_out[3] = pul_in[3] ^ aul_iv_out[3];
        hmac_sms4_crypt((oal_uint8 *)aul_iv_out,(oal_uint8 *)aul_iv_out, aul_pr_keyin);
        pul_in  += 4;
        pul_out += 4;
    }

    puc_in  = (oal_uint8 *)pul_in;
    puc_out = (oal_uint8 *)pul_out;
    puc_iv = (oal_uint8 *)aul_iv_out;

    for (ul_loop=0; ul_loop < ul_comp; ul_loop++)
    {
        puc_out[ul_loop] = puc_in[ul_loop] ^ puc_iv[ul_loop];
    }

    return OAL_SUCC;
}




oal_uint32  hmac_wpi_decrypt(oal_uint8* puc_iv, oal_uint8* puc_bufin, oal_uint32 ul_buflen,
                        oal_uint8* puc_key, oal_uint8* puc_bufout)
{
   return hmac_wpi_encrypt(puc_iv, puc_bufin, ul_buflen, puc_key, puc_bufout);
}





void hmac_wpi_swap_pn(oal_uint8 *puc_pn, oal_uint8 uc_len)
{
    oal_uint8       uc_index;
    oal_uint8       uc_temp;
    oal_uint8       uc_len_tmp;

    uc_len_tmp = uc_len / 2;
    for (uc_index = 0; uc_index < uc_len_tmp; uc_index++)
    {
        uc_temp = puc_pn[uc_index];
        puc_pn[uc_index] = puc_pn[uc_len - 1 - uc_index];
        puc_pn[uc_len - 1 - uc_index] = uc_temp;
    }
}



oal_uint32  hmac_wpi_pmac(oal_uint8* puc_iv, oal_uint8* puc_buf, oal_uint32 ul_pamclen,
                    oal_uint8* puc_key, oal_uint8* puc_mic)
{
    oal_uint32  aul_mic_tmp[4];
    oal_uint32  ul_loop;
    oal_uint32 *pul_in;
    oal_uint32  aul_pr_macKeyin[32];

    if ((ul_pamclen < 1) || (ul_pamclen > 4096))
    {
        return OAL_FAIL;
    }

    hmac_sms4_keyext(puc_key, aul_pr_macKeyin);
    pul_in = (oal_uint32*)puc_buf;
    hmac_sms4_crypt(puc_iv, (oal_uint8*)aul_mic_tmp, aul_pr_macKeyin);

    for (ul_loop = 0; ul_loop < ul_pamclen; ul_loop++)
    {
        aul_mic_tmp[0] ^= pul_in[0];
        aul_mic_tmp[1] ^= pul_in[1];
        aul_mic_tmp[2] ^= pul_in[2];
        aul_mic_tmp[3] ^= pul_in[3];
        pul_in += 4;
        hmac_sms4_crypt((oal_uint8*)aul_mic_tmp, (oal_uint8*)aul_mic_tmp, aul_pr_macKeyin);
    }

    pul_in    = (oal_uint32*)puc_mic;
    pul_in[0] = aul_mic_tmp[0];
    pul_in[1] = aul_mic_tmp[1];
    pul_in[2] = aul_mic_tmp[2];
    pul_in[3] = aul_mic_tmp[3];

    return OAL_SUCC;
}



#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

