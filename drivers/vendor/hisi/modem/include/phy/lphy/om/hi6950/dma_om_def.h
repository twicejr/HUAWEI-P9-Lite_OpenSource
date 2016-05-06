/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dma_om_define.h
  版 本 号   : 初稿
  作    者   : honghuiyong;
  生成日期   : 2011年1月14日
  最近修改   :
  功能描述   : DMA OM相关定义的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年1月14日
    作    者   : honghuiyong;
    修改内容   : 创建文件

******************************************************************************/


#ifndef __DMA_OM_DEFINE_H__
#define __DMA_OM_DEFINE_H__



/************************************************************
                             宏定义
************************************************************/

#define DMA_OM_MAX_PAYLOAD_LENGTH	10
#define DMA_OM_MSG_HEADER_LENGTH	12
#define DMA_OM_EXTRA_MSG_HEADER_LEN 4

#define DMA_REPORT_OM_TRACE_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_TRACE)        
#define DMA_REPORT_OM_DEBUG_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_DEBUG)        
#define DMA_REPORT_OM_ERROR_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_ERROR)        



/************************************************************
                             数据结构定义
************************************************************/
//---------------------------------------------------------
//  1.  DMA error info 结构体定义和申明[共用上报结构体]
//---------------------------------------------------------

/* Error Message Report Format */
typedef enum __LPHY_ERR_MSGID_DMA_ERROR_ENUM__
{
    LPHY_ERR_DMA_RESERVED = OM_CMD_ID(LPHY_DMA_MID,OM_TYPE_ERROR,0),
    LPHY_ERR_DMA_ILLEGAL_CHANNEL_INDEX,
    LPHY_ERR_DMA_ILLEGAL_DATA_LENGTH,
    LPHY_ERR_DMA_BUFFER_OVERFLOW,
    LPHY_ERR_DMA_NULL_DESCRIPTOR,        
    LPHY_ERR_DMA_TIMEOUT,        
}LPHY_ERR_MSGID_DMA_ERROR_ENUM;
typedef UINT32 LPHY_ERR_MSGID_DMA_ERROR_ENUM_UINT32;


typedef struct __LPHY_DMA_ERROR_REPORT_OM_IND__
{
    UINT16      usSysFN;        /*上报系统帧号*/
    UINT16      usSubFN;        /*上报子帧号*/    
    UINT32      ulPaylod[DMA_OM_MAX_PAYLOAD_LENGTH];
}LPHY_DMA_ERROR_REPORT_OM_IND;


/************************************************************
                             接口函数声明
 ************************************************************/

UINT32 DMA_OM_ErrMsgReport(LPHY_ERR_MSGID_DMA_ERROR_ENUM_UINT32 enErrorType,UINT32 ulPayloadLen ,UINT32* pulPayload);

#endif
