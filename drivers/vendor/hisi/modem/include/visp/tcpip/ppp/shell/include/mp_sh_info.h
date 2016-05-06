/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_info.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-28
 *        Author: yaochengliang
 *   Description: 信息字符串索引外部引用头文件
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-28      YaoChengLiang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/

#ifndef _MP_SH_INFO_H
#define _MP_SH_INFO_H

#ifdef __cplusplus
extern "C"{
#endif


enum enum_mp 
{
    MP_USER_PARAMETER, 
    MP_USER_NAME, 
    MP_BIND, 
    MP_VT, 
    MP_VT_NUMBER, 
    MP_PPP,
    MP_MP, 
    MP_MAX_BIND, 
    MP_MAX_BIND_NUMBER, 
    MP_MIN_FRAGMENT, 
    MP_REORDER_WINDOW,
    MP_SHOW_PPP, 
    MP_MP_INFO, 
    MP_SHOW_INTERFACE, 
    /*
    MP_INTERFACE_TYPE, 
    MP_INTERFACE_NUMBER, 
    MP_INTERFACE_NAME, 
    */
    MP_LFI_INTERLEAVE,
    MP_LFI_FRAGDELAY,
    MP_LFI_DELAYVALUE,
    /* VRP3R001M07，刘凯(L03198)，2002/11/04 */
    MP_BUNDLENAME,
    MP_BUNDLENAME_ENDP,
    MP_BUNDLENAME_AUTH,
    MP_BUNDLENAME_BOTH,
    /* VRP3R001M07，刘凯(L03198)，2002/11/04，结束 */
    MP_DISCRIMINATOR,   /* SWFD10247 2005.06.11  discriminator negotiation */
    MP_GROUP_INTERFACE_REMOVE,
    MP_GROUP_INTREFACE_ADD,
    MP_GROUP_INTERFACE_NAME,
    MP_GROUP_INTERFACE_TYPE,
    MP_GROUP_INTERFACE_NUMBER,
    MP_MAX 
};

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /*_MP_SH_INFO_H*/
