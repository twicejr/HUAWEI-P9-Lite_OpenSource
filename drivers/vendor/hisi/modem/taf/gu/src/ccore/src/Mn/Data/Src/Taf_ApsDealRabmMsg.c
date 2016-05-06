/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealRabmMsg.c
  Author       : 韩鲁峰
  Version      : V200R001
  Date         : 2005-0
  Description  :
  Function List:
        ---Aps_DealAllFromRabm
        ---Aps_RabmMsgMod2To3Cur3Succ
        ---Aps_RabmMsgMod3To2Cur2Succ
        ---Aps_RabmMsgModStateCheck
        ---Aps_Nop

        ---Aps_RabmMsgDeAct
        ---Aps_RabmMsgDeActSndcp
        ---Aps_RabmMsgActSndcp
        ---Aps_GetAllNegoRate
        ---Aps_GetOneNegoRate

        ---
  History      :
  1. Date:2005-0
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-03-03 MODIFY BY H41410 FOR A32D02344
  4. 2006-08-15 modify by L47619 for A32D05709
  4. 2007-04-10 modify by L47619 for A32D10258
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALRABMMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/




/*****************************************************************************/
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
