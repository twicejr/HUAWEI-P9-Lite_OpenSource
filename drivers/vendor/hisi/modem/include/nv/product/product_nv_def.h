/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_def.h
  Description     :   产线NV 结构体定义
  History         :
******************************************************************************/

#ifndef __PRODUCT_NV_DEF_H__
#define __PRODUCT_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_CHECK_NUM       1000

/*请参考结构体样例*/
typedef struct
{
    int reserved;  /*note */
}PRODUCT_MODULE_STRU;

typedef struct
{
    u32 uwGuCrcResult;                      /* GU主卡NV的校验结果 */
    u32 uwTlCrcResult;                      /* TL主卡NV的校验结果 */
    u32 uwGuM2CrcResult;                    /* GU副卡NV的校验结果 */
}NV_CRC_CHECK_RESULT_STRU;

typedef struct
{
    u16 uhwValidCount;                       /* 指示有效数据的个数 */
    u16 uhwRsv;                              /* 保留位 */
    u16 auhwNeedCheckID[MAX_CHECK_NUM];      /* 保存需要检查的NV_ID值 */
}NV_CHECK_ITEM_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


