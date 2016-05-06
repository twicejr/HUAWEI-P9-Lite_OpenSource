/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_id.h
  Description     :   productNV ID枚举定义
  History         :

******************************************************************************/

#ifndef __PRODUCT_NV_ID_H__
#define __PRODUCT_NV_ID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*
 *  NV ID 的添加按从小到大排列
 */

typedef enum
{
    NV_ID_CRC_CHECK_RESULT = 0xc350,
    NV_ID_GU_CHECK_ITEM    = 0xc351,
    NV_ID_TL_CHECK_ITEM    = 0xc352,
    NV_ID_GU_M2_CHECK_ITEM = 0xc353,
    NV_ID_PRODUCT_END      = 0xcb1f
}NV_ID_PRODUCT_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


