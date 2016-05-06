
/*lint --e{944,506,525,64,119,101,132,537,958,438,830,752,762,713,732,729,539,830} */

#include "stdlib.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "securec.h"
#include "osl_malloc.h"
#include "product_config.h"
#include "osl_types.h"
#include "bsp_dump.h"
#include "bsp_om.h"
#include "bsp_rfile.h"
#include "bsp_rtc.h"
#include "bsp_sci.h"
#include "sci_debug.h"
#include "sci_appl131.h"
#include "sci_pl131.h"
#include "sci_apbitops.h"




/*lint -save -e525 -e40 -e409 -e19 -e63 -e18 -e826 -e419 -e831 -e539 -e830 -e774*/

#ifdef __cplusplus
extern "C"
{
#endif

u8* g_sciRegGblAddr = BSP_NULL;

u8* g_sciExcGblAddr = BSP_NULL;

u8* g_sciDirGblAddr = BSP_NULL;

u8* g_sciDataGblAddr= BSP_NULL;

u8* g_sciDataLastNotRing = BSP_NULL;

SCI_EVENT_HISTORY_STRUCT  * usim_event_history_ptr ;


BSP_BOOL g_SciEventRingFull = BSP_FALSE;

extern SCI_STATE_STRU g_strSciState;

/* recv buffer */
extern SCI_REC_DATA g_strRecBuf;

/* set sim0 or sim1 */

extern ATR_sBuffer g_strATRData; 
sci_debug_str  g_sci_debug_base = {0,NULL};

extern SCI_CFG_STRU g_stSciHwCfg;

//extern SCI_Class_Of_Type sciClassKind;

extern ATR_sBuffer g_strATRData;

extern SCI_VOLTAGE_STATE g_sci_voltage_state;
extern SCI_HW_ABNORMAL_E g_sci_hw_abnormal ;

#define MAX_TMP_BUF_LEN 4096
#define LPM3_SIM_LOG_RDR_ID  0x4000008
#define ACORE_SIM_LOG_RDR_ID 0x1010032
#define MAX_LOG_FILE_NUM     10
#define TIME_LENGTH       19
#define SCI_LOG_FILE_NAME_LEN  (strlen(SCI0_RECORD_LOG_PATH_LOST_CARD) + strlen("index0_") + strlen("sci0_") + strlen(g_sci_log_name[0])  + strlen("2013_03_02_12_02_03") + strlen(".txt"))




u32* sci_global_print(s32 fd,char*tmp_buf_start,u32* exc_global,char* content_buf);
u32* sci_register_print(s32 fd,char*tmp_buf_start,u32* reg_global,char* content_buf);


char* g_SciRecordEvent[]=
{
    "SCI_EVENT_SCI_INIT_SUCCESS",  /*SCI 模块初始化结束*/
    "SCI_EVENT_API_RESET_START",
    "SCI_EVENT_API_RESET_FAILED",
    "SCI_EVENT_API_RESET_FINISH",
    "SCI_EVENT_API_DATA_SEND",
    "SCI_EVENT_API_DATA_REC_START",
    "SCI_EVENT_API_DATA_REC_DONE",
    "SCI_EVENT_API_DECATIVE",
    "SCI_EVENT_API_CLASS_SWITCH",
    "SCI_EVENT_API_CLOCK_STOP",
    "SCI_EVENT_API_GET_STATUS",
    "SCI_EVENT_API_GET_ATR",
    "SCI_EVENT_API_REV_BLK",
    "SCI_EVENT_API_PROTOCOL_SWITCH",
    "SCI_EVENT_API_SET_BWT",
    "SCI_EVENT_API_SLOT_SWITCH",
    "SCI_EVENT_CARD_ACTIVE_START",
    "SCI_EVENT_CARD_ACTIVE_SUCCESS",
    "SCI_EVENT_ATR_REC_START",
    "SCI_EVENT_ATR_REC_GLOBAL",
    "SCI_EVENT_ATR_REC_OVER",
    "SCI_EVENT_ATR_DECODE_ERR",
    "SCI_EVENT_ATR_WWT_RESET",
    "SCI_EVENT_DATA_TRANS",
    "SCI_EVENT_PPS_REQ",
    "SCI_EVENT_PPS_PPS0",
    "SCI_EVENT_PPS_PPS1",
    "SCI_EVENT_PPS_DONE",
    "SCI_EVENT_CLK_START",
    "SCI_EVENT_CLK_STOP",
    "SCI_EVENT_CLK_ERROR",
    "SCI_EVENT_REGISTER_COLD_RESET",
    "SCI_EVENT_REGISTER_WARM_RESET",
    "SCI_EVENT_REGISTER_FINISH",
    "SCI_EVENT_REGISTER_CLOCK_STOP",
    "SCI_EVENT_REGISTER_CLOCK_START",
    "SCI_EVENT_REGULATOR_ERR",
    "SCI_EVENT_REGULATOR_UP",
    "SCI_EVENT_REGULATOR_DOWN",
    "SCI_EVENT_VOLTAGE_SWITCH",
    "SCI_EVENT_VOLTAGE_CLASS_C2B",
    "SCI_EVENT_VOLTAGE_CLASS_C2C",
    "SCI_EVENT_VOLTAGE_CLASS_B2B",
    "SCI_EVENT_VOLTAGE_ERROR",
    "SCI_EVENT_INTR_CARD_UP",
    "SCI_EVENT_INTR_CARD_DOWN",
    "SCI_EVENT_INTR_TX_ERR",
    "SCI_EVENT_INTR_ATRSTOUT",
    "SCI_EVENT_INTR_ATRDTOUT",
    "SCI_EVENT_INTR_BLKOUT",
    "SCI_EVENT_INTR_CHOUT",
    "SCI_EVENT_INTR_RTOUT",
    "SCI_EVENT_INTR_RORI",
    "SCI_EVENT_INTR_CLK_STOP",
    "SCI_EVENT_INTR_CLK_ACTIVE",
    "SCI_EVENT_DETECT_CARD_IN",
    "SCI_EVENT_DETECT_CARD_OUT",
    "SCI_EVENT_DETECT_CARD_LEAVE",
    "SCI_EVENT_DETECT_IND_USIM",
    "SCI_EVENT_IND_PLUS_IN",          
    "SCI_EVENT_IND_PLUS_OUT",         
    "SCI_EVENT_DETECT_IND_M3",        
    "SCI_EVENT_ERROR_NODATA",         
    "SCI_EVENT_ERROR_NOCARD",         
    "SCI_EVENT_ERROR_DATA_REC_BUF_OVR",
    "SCI_EVENT_ERROR_PROTOCOL_SWITCH",
    "SCI_EVENT_ERROR_REV_BLK_PLOUGE", 
    "SCI_EVENT_ERROR_REV_BLK_DATA",   
    "SCI_EVENT_LOW_POWER_ENTER",      
    "SCI_EVENT_LOW_POWER_EXIT",      
    "SCI_EVENT_DMA_START",           
    "SCI_EVENT_DMA_ERROR",            
    "SCI_EVENT_BEYOND_LOG",           
};

char* g_ControlRecordEvent[]=
{
    "SIM_OUT            ",
    "SIM_IN_POSITION    ",
    "SIM_IN             ", 
    "SIM_LEAVE_POSITION ",
    "SIM_STATUS_NONE    ",
};

/*后面有特殊处理，请增加文件名称时保持和已经定义的文件名长度一致，
    否则将导致控制文件个数时出错*/
char* g_sci_log_name[] =
{
    "normal_reset_fail_",                    /*复位失败*/
    "protect_reset_suc_",                    /*保护性复位成功*/
    "protect_reset_fal_",                    /*保护性复位失败*/
    "receive__no__data_",                    /*没有数据返回*/
    "receive_buff_over_",                    /*数据接收溢出*/
    "voltg_switch_fail_",                    /*USIM电压切换失败*/
    "defalut_file_name_",                    /*默认保存文件名*/
};

/*记录异常文件路径的全局变量*/
char * g_pcCardRecordControlFile[] = {SCI0_RECORD_LOG_PATH_CONTROL,
                                         SCI1_RECORD_LOG_PATH_CONTROL};

#ifdef ENABLE_BUILD_OM
extern void QueueInit(Queue *Q, u32 elementNum);

extern s32 QueueLoopIn(Queue *Q, u32 element);
#else
void QueueInit(Queue *Q, u32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;
    (void)memset_s((void *)Q->data, (elementNum*sizeof(u32)),0, (size_t )(elementNum*sizeof(u32)));
}

__inline__ s32 QueueIn(Queue *Q, u32 element)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear] = element;
    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

__inline__ s32 QueueLoopIn(Queue *Q, u32 element)
{
    if (Q->num < Q->maxNum)
    {
        return QueueIn(Q, element);
    }
    else
    {
        Q->data[Q->rear] = element;
        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}
#endif

/******************************************************************************
 * Function:      sci_record_init
 * Description:
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
void sci_record_init(void )
{
    if(CARD0_EXCP_RECORD_ADDR_NUM == g_stSciHwCfg.record_enum)
    {
        g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr = (char *)bsp_dump_register_field(g_stSciHwCfg.record_enum, "SIM0", 0, 0, 0x4000, 0);
        if(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr == NULL)
        {
            sci_print_error("get sim0 debug buffer failed! \n");
            return ;            
        }
        g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr_legth = 0x4000;
    }
    
    if(CARD1_EXCP_RECORD_ADDR_NUM == g_stSciHwCfg.record_enum)
    {
        g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr = (char *)bsp_dump_register_field(g_stSciHwCfg.record_enum, "SIM1", 0, 0, 0x4000, 0);
        if(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr == NULL)
        {
            sci_print_error("get sim1 debug buffer failed! \n");
            return ;            
        }
        g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr_legth = 0x4000;
    }

    (void)memset_s((void *)(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr),(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr_legth ),0,(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr_legth));
    
    usim_event_history_ptr=(SCI_EVENT_HISTORY_STRUCT  *)SCI_EVENT_BASE_ADDR;
    usim_event_history_ptr->event_ring=(SCI_EVENT_RING_STRUCT *)(SCI_EVENT_BASE_ADDR+0x20);

    /*memset_s((void *)usim_event_history_ptr,0,(int)sizeof(SCI_EVENT_HISTORY_STRUCT));*/
    /* save ring size and others.  */

    usim_event_history_ptr->init_flag     = SCI_EVENT_RING_INIT_FLAG;

    /* so, event_pos + 1 = 0 = first osl_free position.  */
    usim_event_history_ptr->event_pos = 0xFFFFFFFF;

    usim_event_history_ptr->version    = 0;

    usim_event_history_ptr->reserved   = SCI_EVENT_RECORD_MAGIC;

    g_sciRegGblAddr = (u8*)(SCI_RECORD_BASE_ADDR + SCI_RECORD_ATR_SIZE);
    /* exc and dir init*/
    g_sciExcGblAddr = (u8 *)SCI_EXC_GBL_ADDR;

    g_sciDirGblAddr = (u8 *)SCI_DIR_BASE_ADDR;

    g_sciDataGblAddr = (u8 *)SCI_DATA_BASE_ADDR;

    QueueInit((Queue *)(SCI_DIR_BASE_ADDR), (SCI_DIR_BASE_SIZE-0x10)/sizeof(BSP_U32));    

}

/******************************************************************************
 * Function:      sci_record_init_para
 * Description:  save atr and register
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
void sci_record_init_para(void)
{
    SCI_CHECK_RECORD_BASE(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr);

    BSP_U8*sciRecordAddr=(BSP_U8 *)SCI_RECORD_BASE_ADDR;

    SCI_CHECK_RECORD_BASE(sciRecordAddr);

    *(sciRecordAddr)=g_strATRData.ulATRLen;
    sciRecordAddr++;
    (void)memcpy_s((void *)sciRecordAddr,g_strATRData.ulATRLen,(void *)g_strATRData.ATRData,(unsigned int)g_strATRData.ulATRLen);
    sciRecordAddr=(BSP_U8 *)(SCI_RECORD_BASE_ADDR+SCI_RECORD_ATR_SIZE);
    (void)memcpy_s((void *)sciRecordAddr,SCI_RECORD_REG_SIZE,(void *)SCI_BASE_ADDR,(int)SCI_RECORD_REG_SIZE); 
    sciRecordAddr+=SCI_RECORD_REG_SIZE;
    
    return;
}

/******************************************************************************
 * Function:      sci_event_record_stop
 * Description:
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
void sci_event_record_stop(void)
{
    SCI_CHECK_RECORD_BASE(SCI_RECORD_BASE_ADDR);
    
    usim_event_history_ptr=(SCI_EVENT_HISTORY_STRUCT  *)SCI_EVENT_BASE_ADDR;
    usim_event_history_ptr->init_flag = SCI_EVENT_RING_STOP_FLAG;
}

/******************************************************************************
 * Function:      sciEventRecordStart
 * Description:
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
void sci_event_record_start(void)
{
    SCI_CHECK_RECORD_BASE(SCI_RECORD_BASE_ADDR);
    
    usim_event_history_ptr=(SCI_EVENT_HISTORY_STRUCT  *)SCI_EVENT_BASE_ADDR;
    usim_event_history_ptr->init_flag = SCI_EVENT_RING_INIT_FLAG;
}

/******************************************************************************
 * Function:      sci_event_record_add
 * Description:
 * Input:
        event_ptr:  event list;
        event:      event  to be record;
        param1:     param1;
        param2:     param2; 
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
void sci_event_record_add(SCI_EVENT_HISTORY_STRUCT * event_ptr,
                       u32 event,
                       u32 param1,
                       u32 param2 )
{
    u32     pos;

    SCI_CHECK_RECORD_BASE(SCI_RECORD_BASE_ADDR);

    if(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr == NULL || event_ptr == NULL)
    {
        return;
    }
    if( SCI_EVENT_RING_INIT_FLAG == event_ptr->init_flag )
    {
        /*ê1ó?NV ????*/
        if(event != SCI_EVENT_BEYOND_LOG)
        {
            /* increase and update the pos.  */
            pos  = event_ptr->event_pos + 1;
            
            /* record attach to the ring tail,restart the ring form SCI_RECORD_RING_HEAD*/
            if (pos>=SCI_EVENT_RING_SIZE)
            {
                g_SciEventRingFull = BSP_TRUE;
                pos =SCI_RECORD_RING_HEAD;
            }
            event_ptr->event_pos = pos;
            ADD_TO_RING( event_ptr, event, param1, param2, pos );

        }
    }
}
/******************************************************************************
 * Function:      sci_record_cmd_data
 * Description:
 * Input:
        tfrFlag:    event list;
        dataLen:    data length;
        dataAddr:   data buffer; 
 * Output:
 * Return:
 * Others:
 *****************************************************************************/

void sci_record_cmd_data(u8 tfrFlag, u8 dataLen, u8 *dataAddr)
{   
    u32 timestamp = 0;
    SCI_CHECK_RECORD_BASE(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr);

    /* judge record base */
    SCI_CHECK_RECORD_BASE(g_sciDataGblAddr);
    timestamp = bsp_get_slice_value();
    /* judge the range */
    if((g_sciDataGblAddr+dataLen+SCI_DATA_HALF_MAX_LGTH)>=(u8 *)(SCI_DATA_BASE_ADDR+SCI_DATA_BASE_SIZE))
    {
        g_sciDataLastNotRing = g_sciDataGblAddr;
        g_sciDataGblAddr = (u8 *)(SCI_DATA_BASE_ADDR + SCI_DATA_RING_SIZE);
    }

    /* write to memory */
    *(g_sciDataGblAddr) = tfrFlag;
    g_sciDataGblAddr += sizeof(u8);
    (void)memcpy_s(g_sciDataGblAddr, (sizeof(u32)) ,&timestamp, sizeof(u32));
    g_sciDataGblAddr += sizeof(u32);   
    *(g_sciDataGblAddr) = dataLen;
    g_sciDataGblAddr += sizeof(u8);
    /*if the data number is more than 8,just record the first and the last two bytes*/
    if(dataLen >= SCI_DATA_PER_MAX_LGTH)
    {
        (void)memcpy_s(g_sciDataGblAddr,(SCI_DATA_HALF_MAX_LGTH ),dataAddr,SCI_DATA_HALF_MAX_LGTH);
        (void)memcpy_s((g_sciDataGblAddr+SCI_DATA_HALF_MAX_LGTH),(SCI_DATA_HALF_MAX_LGTH ),(dataAddr+dataLen-SCI_DATA_HALF_MAX_LGTH),SCI_DATA_HALF_MAX_LGTH);
    }
    else
    {
        (void)memcpy_s(g_sciDataGblAddr,dataLen ,dataAddr,(int)dataLen);
        (void)memset_s((g_sciDataGblAddr + dataLen), (SCI_DATA_PER_MAX_LGTH - dataLen ),0, (SCI_DATA_PER_MAX_LGTH - dataLen));
    }
    g_sciDataGblAddr += SCI_DATA_PER_MAX_LGTH;

}
/******************************************************************************
 * Function:      sciRecordExcGbl
 * Description:
 * Input:
        tfrFlag:    event flag
 * Output:        void
 * Return:
 * Others:
 *****************************************************************************/
void sci_record_exc_gbl(u32 excEvent, u32 u32RecvLen,  u32 u32TimeSamp)
{
    SCI_STATE_STRU *pstrState = (SCI_STATE_STRU *)&g_strSciState;
    volatile u32* pRegData;

    /* judge record base */
    SCI_CHECK_RECORD_BASE(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr);
    SCI_CHECK_RECORD_BASE(g_sciExcGblAddr);
    
    /* write to memory */
    if((g_sciExcGblAddr+sizeof(SCI_STATE_STRU)+(sizeof(u32)*SCI_EXC_LOG_TYPE_NUM)+SCI_REGS_NUM+u32RecvLen)<(u8 *)(SCI_EXC_GBL_ADDR+SCI_EXC_GBL_SIZE))
    {       
        *((u32*)(g_sciExcGblAddr)) = excEvent;
        g_sciExcGblAddr+=sizeof(u32);
        
        /* save global variables */
        *((u32*)(g_sciExcGblAddr)) = sizeof(SCI_STATE_STRU);
        g_sciExcGblAddr+=sizeof(u32);
        (void)memcpy_s(g_sciExcGblAddr, (sizeof(SCI_STATE_STRU) ),(u8 *)pstrState, sizeof(SCI_STATE_STRU));
        g_sciExcGblAddr+=sizeof(SCI_STATE_STRU);
        
        pRegData = (volatile u32 *)(SCI_BASE_ADDR); 
        *((u32*)(g_sciExcGblAddr)) = SCI_REGS_NUM;
        g_sciExcGblAddr+=sizeof(u32);
        (void)memcpy_s(g_sciExcGblAddr, (SCI_REGS_NUM*sizeof(u32) ),(u8 *)pRegData, (SCI_REGS_NUM*sizeof(u32)));/* [false alarm]:*/
        g_sciExcGblAddr+=SCI_REGS_NUM*sizeof(u32);

        *((u32*)(g_sciExcGblAddr)) = u32TimeSamp;
        g_sciExcGblAddr+=sizeof(u32);
    
    }
    else
    {
        g_sciExcGblAddr = (u8 *)SCI_EXC_GBL_ADDR;
    }

    return;

}

/******************************************************************************
 * Function:      sci_record_format
 * Description: 将内存中内容以格式化的形式存储
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/

void sci_record_format(char*buf_start,char** tmp_buf, char *fmt,...)
{
    u32 len = 0;
    char buf[256];
    va_list arglist;/*lint !e40 !e522*/

    va_start(arglist, fmt);/*lint !e586 !e530*/
    /*lint -save -e119*/
    (void)vsnprintf_s(buf,256 ,256, fmt, arglist); /* [false alarm]:屏蔽Fority错误 */
    /*lint -restore*/
    va_end(arglist);/*lint !e586*/

    len = strlen(buf);
    /* coverity[deref_parm_in_call] */
    if((strlen(buf_start)  + len) < MAX_TMP_BUF_LEN)
    {
        (void)memcpy_s(*tmp_buf,(len),buf,len);
    
        *tmp_buf += len;
    }

}

/******************************************************************************
 * Function:      sci_record_flush2file
 * Description: 将缓存中的内容写入文件中，并复位缓存指针
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/

void sci_record_flush2file(s32 fd,char* tmp_buf_start,char** tmp_buf)
{
    (void)bsp_write(fd, (s8*)tmp_buf_start, strlen(tmp_buf_start));
    (void)memset_s(tmp_buf_start,(MAX_TMP_BUF_LEN ),'\0',MAX_TMP_BUF_LEN);
    *tmp_buf = tmp_buf_start;

}

/******************************************************************************
 * Function:      sci_acore_record_save
 * Description: 将A核或lpm3 的log写入sci的日志文件
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/

void sci_gpio_record_save(u32 id,s32 fd,char* tmp_buf_start,char** tmp_buf)
{
#if 0
   
    u32 i = 1;/* [false alarm]:fortify */
    dump_save_modid_t mod_id = (dump_save_modid_t)id;

    CONTROL_LOG* log = (CONTROL_LOG*)bsp_dump_get_buffer_addr(mod_id);

    if(log == NULL)
    {
        return;
    }
    if(id == ACORE_SIM_LOG_RDR_ID)
    {
        sci_record_format(tmp_buf_start,tmp_buf,"\nBegin to save ACORE SIM Log\n");
        sci_record_format(tmp_buf_start,tmp_buf,"The Acore rdr ID is 0x%.8x%, rdr address is 0x%.8x%\n",id, log);
    }
    else if(id == LPM3_SIM_LOG_RDR_ID)
    {
        sci_record_format(tmp_buf_start,tmp_buf,"\nBegin to save LPM3 SIM Log\n");
        sci_record_format(tmp_buf_start,tmp_buf,"The LPM3 rdr ID is 0x%.8x%, rdr address is 0x%.8x%\n",id, log);
    }
    else
    {
        sci_print("ERROR RDR ID\n");
        return;
    }
    
    for(;i <= 50;i++)
    {
        if(log->sim_no < 2 && log->sim_status < 4)
        {
            /*对应的卡只保存对应的拔插事件*/
            if(g_stSciHwCfg.sci_id == log->sim_no)
            {
                sci_record_format(tmp_buf_start,tmp_buf,"time : 0x%.8x  ",log->time);
                sci_record_format(tmp_buf_start,tmp_buf,"sim_no : %3d  ",log->sim_no);
                sci_record_format(tmp_buf_start,tmp_buf,"sim_status : %s  ",g_ControlRecordEvent[log->sim_status]);
                sci_record_format(tmp_buf_start,tmp_buf,"hpd_level : %3d  ",log->hpd_level);
                sci_record_format(tmp_buf_start,tmp_buf,"det_level : %3d  ",log->det_level);
                sci_record_format(tmp_buf_start,tmp_buf,"trace : %3d  ",log->trace);
                sci_record_format(tmp_buf_start,tmp_buf,"sim_mux : %3d ",log->sim_mux[0]);
                sci_record_format(tmp_buf_start,tmp_buf,"%3d ",log->sim_mux[1]);
                sci_record_format(tmp_buf_start,tmp_buf,"%3d \n",log->sim_mux[2]);
            }
            
        }

        if(i % 5 == 0)
        {
            sci_record_flush2file(fd,tmp_buf_start,tmp_buf);
        }
        
        log++;
    }
#endif
    
}
void sci_combine_log_name(char *log_name,char *fmt, ...)
{
    char buf[256] = {'\0',};
    va_list arglist ;/*lint !e40 !e522 !e830*/
    
    va_start(arglist, fmt);/*lint !e586 !e530*/
    /*lint -save -e119*/    
    (void)vsnprintf_s(buf,256 ,256, fmt, arglist); /* [false alarm]:屏蔽Fority错误 */
    /*lint -restore*/
    va_end(arglist);/*lint !e586*/
    (void)memcpy_s(log_name ,(strlen(buf)),buf,strlen(buf));

}
/*lint -save -e550*/

void sci_get_log_name(SCI_LOG_MODE log_mode,char* dir_path,char* control_path, char** logname)
{
    char* logpath = NULL;
    char* log_name_head = NULL;
    s32 ret = -1;
    s32 fd = -1;
    u32 file_length = 0;
    u32 i = 0;
    char oldname[128] = {'\0',};
    char newname[128] = {'\0',};
    struct rtc_time tm = {0};
    char index_pos = -1;
    char* all_name_buf= NULL;
    
    if(logname == NULL || control_path == NULL  || dir_path == NULL)
    {   
        return;
    }
    if(log_mode > SCI_LOG_BUTT)
    {
        log_mode = SCI_LOG_BUTT;/* [false alarm]:fortify */
    }
    logpath = g_sci_log_name[log_mode]; 
    log_name_head = (g_stSciHwCfg.sci_id== 0) ? "sci0_" : "sci1_";/*lint !e158*/
    (void)mdrv_rtc_read_time(&tm);
    /* [false alarm]:fortify */
    fd = bsp_access((s8*)dir_path, 0); //F_OK, 检查文件是否存在
    /* [false alarm]:fortify */
    if(0 != fd)
    {
        fd  = bsp_mkdir((s8*)dir_path, 0660);
        if(fd < 0)/* [false alarm]:fortify */
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OM, "create om dir failed! ret = %d\n", fd);
            return ;
        }
    }

    ret = bsp_access((s8*)control_path, 0);
    if(ret != BSP_OK)
    {
         fd = bsp_open((const s8*)control_path, (s32)(RFILE_CREAT|RFILE_RDWR), (s32)0755);/* [false alarm]:fortify */
    }
    else
    {
         fd = bsp_open((const s8*)control_path, (s32)(RFILE_APPEND|RFILE_RDWR), (s32)0755);/* [false alarm]:fortify */
    }
    
    ret = bsp_access((s8*)control_path, 0);

    if(fd != BSP_ERROR)/* [false alarm]:fortify */
    {
         ret = bsp_lseek(fd,0,SEEK_SET);/* [false alarm]:fortify */
         file_length = bsp_lseek(fd, 0, SEEK_END);           
         ret = bsp_lseek(fd,0,SEEK_SET);
        
         /*当前控制文件已经写满，需要进行重新命名，
                 保证index0开头的文件永远是最旧的*/
         if(file_length == SCI_LOG_FILE_NAME_LEN * MAX_LOG_FILE_NUM)/* [false alarm]:fortify */
         {
             (void)bsp_read(fd, (s8*)oldname, SCI_LOG_FILE_NAME_LEN);/* [false alarm]:fortify */
             (void)bsp_remove((s8*)oldname);
             all_name_buf = osl_malloc((MAX_LOG_FILE_NUM - 1 ) * SCI_LOG_FILE_NAME_LEN + 1);
             if(all_name_buf == NULL)
             {
                (void)bsp_close(fd);
                return;
             }
             (void)memset_s(all_name_buf,((MAX_LOG_FILE_NUM - 1 ) * SCI_LOG_FILE_NAME_LEN + 1 ),'\0',((MAX_LOG_FILE_NUM - 1 ) * SCI_LOG_FILE_NAME_LEN + 1));
             for(i = 1; i < MAX_LOG_FILE_NUM;i++)
             {                 
                (void) bsp_read(fd, (s8*)oldname, SCI_LOG_FILE_NAME_LEN);
                 (void)memcpy_s(newname, (sizeof(oldname) ),oldname, sizeof(oldname));
                 newname[strlen(dir_path) + strlen("sci0_") + strlen("index")] = oldname[strlen(dir_path) + strlen("sci0_") + strlen("index")] - 1;
                 (void)bsp_rename(oldname, newname);
                 (void)memcpy_s((all_name_buf + (i - 1) * SCI_LOG_FILE_NAME_LEN),(strlen(newname)),newname,strlen(newname));
             }
             
             (void)bsp_close(fd);
             (void)bsp_remove((s8*)control_path);
             fd = bsp_open((const s8*)control_path, (s32)(RFILE_CREAT|RFILE_RDWR), (s32)0755);/* [false alarm]:fortify */
             ret = bsp_lseek(fd,0,SEEK_SET);/* [false alarm]:fortify */
             (void)bsp_write(fd, (s8*) all_name_buf, strlen(all_name_buf));
             osl_free(all_name_buf);
             /*控制文件修改完成，返回最终的文件名，并将其写入控制文件*/
             /* [false alarm]:fortify */
             sci_combine_log_name(*logname,"%s%s%s%d%s%s%04d_%02d_%02d_%02d_%02d_%02d.txt",dir_path,log_name_head,"index",9,"_",logpath,(tm.tm_year ), (tm.tm_mon ), tm.tm_mday, (tm.tm_hour ), tm.tm_min, tm.tm_sec);
             
         }
         else if(file_length == 0) /*当前文件为空，则直接返回index0的文件*/
         {
            /* [false alarm]:fortify */
            sci_combine_log_name(*logname,"%s%s%s%d%s%s%04d_%02d_%02d_%02d_%02d_%02d.txt",dir_path,log_name_head,"index",0,"_",logpath,(tm.tm_year ), (tm.tm_mon), tm.tm_mday, (tm.tm_hour ), tm.tm_min, tm.tm_sec);
         }
         else /*文件中已有数据，则直接读取最后一条，将index+1*/
         {
            ret = bsp_lseek(fd, (file_length - SCI_LOG_FILE_NAME_LEN) ,SEEK_SET);   /* [false alarm]:fortify */      
            (void)bsp_read(fd, (s8*)oldname, SCI_LOG_FILE_NAME_LEN);
           
            index_pos = oldname[strlen(dir_path) + strlen("sci0_") + strlen("index")] -= '0';
            index_pos += 1;
            sci_combine_log_name(*logname,"%s%s%s%d%s%s%04d_%02d_%02d_%02d_%02d_%02d.txt",dir_path,log_name_head,"index",index_pos,"_",logpath,(tm.tm_year ), (tm.tm_mon), tm.tm_mday, (tm.tm_hour ), tm.tm_min, tm.tm_sec);
         }
         ret = bsp_write(fd, (s8*)(*logname),SCI_LOG_FILE_NAME_LEN);
         (void)bsp_close((u32)(fd));
    }

}


/******************************************************************************
 * Function:      sciRecordDataSave
 * Description:
 * Input:
 * Output:
 * Return: fail or ok
 * Others:
 *****************************************************************************/
 
u32 sci_record_data_save(SCI_LOG_MODE log_mode)
{
    u8 dataLen,i;/* [false alarm]:fortify */
    u8 * pucData;/* [false alarm]:fortify */
    volatile u32* pMemData;/* [false alarm]:fortify */
    u32 currentEventPos;/* [false alarm]:fortify */
    u32 count = 0;/* [false alarm]:fortify */
    u32 eventId;  /* [false alarm]:fortify */
    u32 u32ArraySize = 0;/* [false alarm]:fortify */
    u32 u32ExcLen =0;/* [false alarm]:fortify */
    u32 * pExcData = NULL;/* [false alarm]:fortify */
    int ret = BSP_OK;/* [false alarm]:fortify */
    char * logpath = NULL;/* [false alarm]:fortify */
    char * logpath_start = NULL;/* [false alarm]:fortify */
    char* tmp_buf = NULL;
    char* tmp_buf_start = NULL;/* [false alarm]:fortify */
    char* control_path = g_pcCardRecordControlFile[g_stSciHwCfg.sci_id];
    char* dir_path = SCI0_RECORD_LOG_PATH_LOST_CARD;    
    s32 fd = -1;
    /* judge record base */
    sci_print("save log reason is %s \n",g_sci_log_name[log_mode]);
    if(BSP_NULL == SCI_RECORD_BASE_ADDR)
    {
        sci_print_error("base addr is NULL!\n");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    /* record sci event */
    sci_event_record_stop();
    tmp_buf = osl_malloc(sizeof(char) * MAX_TMP_BUF_LEN);
    if(tmp_buf == NULL)
    {
        return BSP_ERR_SCI_INVALIDPARA;
    }
    tmp_buf_start = tmp_buf;
    (void)memset_s(tmp_buf,MAX_TMP_BUF_LEN,'\0',MAX_TMP_BUF_LEN);

    logpath = (char*)osl_malloc(128 * sizeof(char));
    if(logpath == NULL)
    {
        osl_free(tmp_buf_start);
        return BSP_ERR_SCI_INVALIDPARA;
    }    
    logpath_start = logpath;
    (void)memset_s(logpath,128,'\0',128);

    sci_get_log_name(log_mode,dir_path,control_path,&logpath);

    if(strlen(logpath) != SCI_LOG_FILE_NAME_LEN)
    {
        if(logpath_start != NULL)
        {            
            osl_free(logpath_start);
        }
        if(tmp_buf_start != NULL)
        {
            osl_free(tmp_buf_start);
        }
        return (u32)BSP_ERROR;
    }
    ret = bsp_access((s8*)logpath, 0);
    if(BSP_OK == ret)/* [false alarm]:fortify */
    {
       (void)bsp_remove((s8*)logpath);/* [false alarm]:fortify */
    }
    
    fd = bsp_open((const s8*)logpath, (s32)(RFILE_CREAT|RFILE_RDWR), (s32)0755);/* [false alarm]:fortify */
    if(fd == BSP_ERROR)
    {
        if(logpath_start != NULL)
        {            
            osl_free(logpath_start);
        }
        if(tmp_buf_start != NULL)
        {
            osl_free(tmp_buf_start);
        }

        return (u32)BSP_ERROR;
    }
    /* save ATR */
    sci_print("sci record save Begin:\n");/* [false alarm]:fortify */


    sci_record_format(tmp_buf_start,&tmp_buf,"SCI ATR RECORD: \n");
    dataLen=*(u8 *)(SCI_RECORD_BASE_ADDR);
    sci_record_format(tmp_buf_start,&tmp_buf,"ATR Len: %d\n",dataLen);
    sci_record_format(tmp_buf_start,&tmp_buf,"DATA RECORD: \n");

    pucData=(u8 *)(SCI_RECORD_BASE_ADDR+1);
    dataLen = (dataLen>SCI_RECORD_ATR_SIZE) ? SCI_RECORD_ATR_SIZE : dataLen;
    for(i=0;i<dataLen;i++)
    {
        sci_record_format(tmp_buf_start,&tmp_buf,"  0x%.2x",*(pucData+i));
    }
    sci_record_format(tmp_buf_start,&tmp_buf,"\n");
    sci_record_format(tmp_buf_start,&tmp_buf,"\n");
    sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

    /* save exc event */
    pExcData=(u32 *)SCI_EXC_GBL_ADDR;
    sci_print("sci record exc global variables, addr is 0x%x\n",(u32)pExcData);
    while(((*pExcData)<(u32)SCI_EVENT_MAX) && (0 !=(*pExcData)))
    {

        /* print exc events */
        eventId = *pExcData;
        sci_record_format(tmp_buf_start,&tmp_buf,"EVENT: %s \n",(g_SciRecordEvent[eventId]));
        pExcData += 1;

        /* print global variables */
        u32ExcLen = *pExcData;
        sci_record_format(tmp_buf_start,&tmp_buf,"global vars Length:  %d\n",(u32ExcLen /4 ));        
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);
        pExcData +=1;
        pExcData = sci_global_print(fd,tmp_buf_start,pExcData,tmp_buf);
        
        /* print current regs */
        /* coverity[dereferencing] */
        u32ExcLen = *pExcData;
        sci_record_format(tmp_buf_start,&tmp_buf,"current reg Length:  %d\n", u32ExcLen);
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);
        pExcData +=1;
        /* coverity[returned_null] */
        pExcData = sci_register_print(fd,tmp_buf_start,pExcData, tmp_buf);

        /* coverity[dereferencing] */      
        sci_record_format(tmp_buf_start,&tmp_buf,"current time stampe:  0x%x\n", *pExcData);      
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);
        pExcData +=1;

        
    }

    /*save cmd data */
    sci_record_format(tmp_buf_start,&tmp_buf,"\nSCI CMD DATA:  \n");
    sci_print("sci record data, addr is 0x%x\n",(u32)SCI_DATA_BASE_ADDR);
    pucData=(u8 *)SCI_DATA_BASE_ADDR;
    dataLen=*(++pucData);
    pucData--;
    while(((*pucData)==(u8)SCI_DATA_SEND_EVENT) || ((*pucData)==(u8)SCI_DATA_RCV_EVENT))
    {
        /*预留100字节余量*/
        if(((tmp_buf - tmp_buf_start) + 100) > MAX_TMP_BUF_LEN)
        {
            sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);
 
        }
        if((*pucData)==(u8)SCI_DATA_SEND_EVENT)/*send data*/
        {
            sci_record_format(tmp_buf_start,&tmp_buf,"SEND:  timestamp:   ");
        }
        else/*receive data*/
        {
            sci_record_format(tmp_buf_start,&tmp_buf,"RCVE:  timestamp:   ");
        }
        sci_record_format(tmp_buf_start,&tmp_buf,"0x%.4x     ",(u32*)pucData);
        pucData += 4;
        if(dataLen<SCI_DATA_PER_MAX_LGTH)/*if data len less than 8,record the whole data*/
        {
            for(i=0;i<dataLen;i++)
            {
                sci_record_format(tmp_buf_start,&tmp_buf," 0x%.2x",*(pucData+2+i));
            }
            if(0 == dataLen)
            {
                sci_record_format(tmp_buf_start,&tmp_buf," len:0x%.2x",dataLen);
            }
        }
        else/*if data len more than 8,record the first two bytes and the last two bytes*/
        {
           sci_record_format(tmp_buf_start,&tmp_buf," 0x%.2x 0x%.2x...len:0x%.2x... 0x%.2x 0x%.2x",*(pucData+2),*(pucData+3),\
                   dataLen, *(pucData+8),*(pucData+9));
        }

        pucData += (SCI_DATA_PER_MAX_LGTH + 2);
        
        sci_record_format(tmp_buf_start,&tmp_buf,"\n");
        sci_record_format(tmp_buf_start,&tmp_buf,"\n");
        dataLen=*(pucData+1);

    }
    sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);


    /* dir record */
    pExcData=(u32 *)SCI_DIR_BASE_ADDR;
    sci_print("sci record dir, addr is 0x%x\n",(u32)pExcData);
    u32ExcLen = *pExcData;/* [false alarm]:*/
    while(0!=(*(pExcData+1)))
    {
        //(void)print2file(logpath,"tick is  0x%.8x, timestampe is 0x%.8x\n", *(pExcData), *(pExcData+1));
        sci_record_format(tmp_buf_start,&tmp_buf,"tick is  0x%.8x, timestampe is 0x%.8x\n", *(pExcData), *(pExcData+1));
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);
        pExcData +=2;
        
    }

    /*save the event record*/
    sci_record_format(tmp_buf_start,&tmp_buf,"\n");
    sci_record_format(tmp_buf_start,&tmp_buf,"\nSCI EVENT RECORD:  \n");
    currentEventPos=*(u32 *)(SCI_EVENT_BASE_ADDR+4);
    pMemData=(u32 *)(SCI_EVENT_BASE_ADDR+SCI_EVENT_HAED_SIZE);

    sci_print("sci record event , addr is 0x%x: \n",(u32)pMemData);

    if(currentEventPos>SCI_EVENT_RING_SIZE)
    {
        sci_print_error("SCI:event record invalid!currentEventPos=0x%x\n",(int)currentEventPos,0,0,0,0,0);
        if(logpath_start != NULL)
        {            
            osl_free(logpath_start);
        }
        if(tmp_buf_start != NULL)
        {
            osl_free(tmp_buf_start);
        }
        (void)bsp_close(fd);
        /* coverity[leaked_storage] */
        return BSP_ERR_SCI_INVALIDPARA;
    }

    if( SCI_EVENT_RECORD_MAGIC != usim_event_history_ptr->reserved)
    {
        sci_print_error("SCI:event record magic invalid!\n",0,0,0,0,0,0);
        if(logpath_start != NULL)
        {            
            osl_free(logpath_start);
        }
        if(tmp_buf_start != NULL)
        {
            osl_free(tmp_buf_start);
        }
        
        (void)bsp_close(fd);
        /* coverity[leaked_storage] */
        return BSP_ERR_SCI_INVALIDPARA;
    }
    
    u32ArraySize = sizeof(g_SciRecordEvent)/sizeof((g_SciRecordEvent[0]));
    /*the event record pointer is in the beginning liner part ,has not reach to the ring area*/
    if(currentEventPos<SCI_RECORD_RING_HEAD)
    {
        for(count =0;count<=currentEventPos;count++)
        {
            /*预留100字节余量*/
            if(((tmp_buf - tmp_buf_start) + 100) > MAX_TMP_BUF_LEN)
            {
                sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

            }
            eventId=*(pMemData);
            if(eventId<u32ArraySize)
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"0x%04x    %-35s\tpara1:0x%04x  para2:0x%08x   time:0x%x\n",count,(g_SciRecordEvent[eventId]), \
                *(pMemData+1),*(pMemData+2),*(pMemData+3));
                pMemData+=4;
                sci_record_format(tmp_buf_start,&tmp_buf,"\n");
            }
            else
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"there is a invalid eventId %d\n", eventId);
            }
         }
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

    }
    else/*the record pointer reach to the ring area*/
    {
        for(count=0;count<SCI_RECORD_RING_HEAD;count++)
        {
            if(((tmp_buf - tmp_buf_start) + 100) > MAX_TMP_BUF_LEN)
            {
                sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

            }
            eventId=*(pMemData);
            if(eventId<u32ArraySize)
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"0x%04x    %-35s\tpara1:0x%04x  para2:0x%08x   time:0x%x\n",count,(g_SciRecordEvent[eventId]), \
                        *(pMemData+1),*(pMemData+2),*(pMemData+3));

                pMemData+=4;
                sci_record_format(tmp_buf_start,&tmp_buf,"\n");
            }
            else
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"there is a invalid eventId %d\n", eventId);
            }
        }

        sci_record_format(tmp_buf_start,&tmp_buf,"MORE, 0--HEAD,POS: 0x%x\n", currentEventPos);
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);


        if(g_SciEventRingFull)/*the ring is full and restart from the ring head*/
        {
            pMemData=(u32 *)(SCI_EVENT_BASE_ADDR+SCI_EVENT_HAED_SIZE+
                                ((currentEventPos+1)*sizeof(SCI_EVENT_RING_STRUCT)));
            /*save the record from the next of current pointer to ring tail*/
            for(count =(currentEventPos+1);count<SCI_EVENT_RING_SIZE;count++)
            {
                if(((tmp_buf - tmp_buf_start) + 100) > MAX_TMP_BUF_LEN)
                {
                    sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

                }
                eventId=*(pMemData);
                if(eventId<u32ArraySize)
                {
                    sci_record_format(tmp_buf_start,&tmp_buf,"0x%04x    %-35s\tpara1:0x%04x  para2:0x%08x   time:0x%x\n",count,(g_SciRecordEvent[eventId]), \
                            *(pMemData+1),*(pMemData+2),*(pMemData+3));
                    pMemData+=4;
                    sci_record_format(tmp_buf_start,&tmp_buf,"\n");
                }
                else
                {
                    sci_record_format(tmp_buf_start,&tmp_buf,"there is a invalid eventId %d\n", eventId);
                }
            }

        }
        sci_record_format(tmp_buf_start,&tmp_buf,"MORE, POS--END,POS: 0x%x\n", currentEventPos);
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

        
        pMemData=(u32 *)(SCI_EVENT_BASE_ADDR+SCI_EVENT_HAED_SIZE+
                            (SCI_RECORD_RING_HEAD*sizeof(SCI_EVENT_RING_STRUCT)));
        /*save the record from the headd to the current pointer*/
        for(count =SCI_RECORD_RING_HEAD;count<=currentEventPos;count++)
        {
            if(((tmp_buf - tmp_buf_start) + 100) > MAX_TMP_BUF_LEN)
            {
                sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

            }
            eventId=*(pMemData);
            if(eventId<u32ArraySize)
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"0x%04x    %-35s\tpara1:0x%04x  para2:0x%08x   time:0x%x\n",count,(g_SciRecordEvent[eventId]), \
                        *(pMemData+1),*(pMemData+2),*(pMemData+3));
                pMemData+=4;
                sci_record_format(tmp_buf_start,&tmp_buf,"\n");
            }
            else
            {
                sci_record_format(tmp_buf_start,&tmp_buf,"there is a invalid eventId %d\n", eventId);
            }
        }
        sci_record_format(tmp_buf_start,&tmp_buf,"MORE, HEAD--POS,POS: 0x%x\n", currentEventPos);
        sci_record_flush2file(fd,tmp_buf_start,&tmp_buf);

        
    }

    sci_print("lpm3 record save begin! \n");
    sci_gpio_record_save(LPM3_SIM_LOG_RDR_ID, fd, tmp_buf_start,&tmp_buf);

    sci_print("acore record save begin! \n");
    sci_gpio_record_save(ACORE_SIM_LOG_RDR_ID, fd, tmp_buf_start,&tmp_buf);


    sci_print("sci record save OK! \n");

    if(logpath_start != NULL)
    {            
        osl_free(logpath_start);
    }
    if(tmp_buf_start != NULL)
    {
        osl_free(tmp_buf_start);
    }

    (void)bsp_close((u32) fd);
    sci_event_record_start();

    return BSP_OK;

}

/******************************************************************************
 * Function:      ci_record_log_read
 * Description:
 * Input:
 * Output:
 * Return: fail or ok
 * Others:
 *****************************************************************************/
s32 sci_record_log_read(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength)
{
    u32     ulDataShiftCnt  = 0;
    u32     ulDataShiftCntNotRing  = 0;
    u32     ulEventShiftCnt = 0;
    u32     ulEventBaseCnt  = 0;
    u32     ulLogLength = 0;
    SCI_RECORD_INFO_S *pStrRecordInfo = BSP_NULL;
    u8*     pSciDataShift = BSP_NULL;
    
    /* judge para */
    if((BSP_NULL == pucDataBuff)||(BSP_NULL == pulLength))
    {
        sci_print_error("ptr is null: pucDataBuff is 0x%x, pulLength is %x!\n",pucDataBuff, pulLength);
        return BSP_ERROR;
    }

    if(ulMaxLength < sizeof(SCI_RECORD_INFO_S))
    {
        sci_print_error("ulMaxLength is too short: %d!\n",ulMaxLength);
        
        return BSP_ERROR;
    }

    pStrRecordInfo = (SCI_RECORD_INFO_S*)pucDataBuff;
    
    /* card voltage class */
    pStrRecordInfo->cardClass = (unsigned short)g_sci_voltage_state.sciClassKind;
    ulLogLength += sizeof(unsigned short);

    /* atr */
    if(g_strATRData.ulATRLen!=0 )
    {
        pStrRecordInfo->ATRlen = (unsigned short)((g_strATRData.ulATRLen > SCI_RECORD_ATR_LEN?SCI_RECORD_ATR_LEN:g_strATRData.ulATRLen)); 
        /* coverity[overrun-buffer-arg] */
        (void)memcpy_s((void *)pStrRecordInfo->ATRData, (pStrRecordInfo->ATRlen ),(const void *)(g_strATRData.ATRData), pStrRecordInfo->ATRlen);
    }

    ulLogLength += sizeof(unsigned short);
    ulLogLength += pStrRecordInfo->ATRlen;

    pStrRecordInfo->enSciHwStatus = g_sci_hw_abnormal;
    if(g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr == NULL)
    {
        return BSP_ERROR;
    }
    /* regs */
    if((g_stSciHwCfg.g_sci_debug_base.sci_debug_base_addr == NULL)||(BSP_NULL==g_sciRegGblAddr) || (BSP_NULL==g_sciDataGblAddr) || (BSP_NULL==usim_event_history_ptr))
    {
        sci_print_error("g_sciRegGblAddr:0x%x, g_sciDataGblAddr:0x%x, usim_event_history_ptr:0x%x!\n",g_sciRegGblAddr, g_sciDataGblAddr, usim_event_history_ptr);
        
        return BSP_ERROR;
    }
    
    /* coverity[overrun-buffer-arg] */
    (void)memcpy_s((void *)pStrRecordInfo->SciRegData, (SCI_RECORD_REG_SIZE ),(const void *)g_sciRegGblAddr, SCI_RECORD_REG_SIZE);
    ulLogLength += SCI_RECORD_REG_SIZE;
    
    /* data */
    if(g_sciDataGblAddr <= (u8*)(SCI_DATA_BASE_ADDR + SCI_DATA_RING_SIZE))
    {
        ulDataShiftCnt = g_sciDataGblAddr - (u8 *)SCI_DATA_BASE_ADDR;
        ulDataShiftCnt = (ulDataShiftCnt>SCI_RECORD_DATA_REAL_LEN)?SCI_RECORD_DATA_REAL_LEN:ulDataShiftCnt;
        /*保证拷贝的是最新的指令数据*/
        pSciDataShift = (u8*)(g_sciDataGblAddr - ulDataShiftCnt);
        /* coverity[overrun-buffer-arg] */
        (void)memcpy_s(pStrRecordInfo->SimRecordData,(ulDataShiftCnt ),pSciDataShift,ulDataShiftCnt);
        ulLogLength += (ulDataShiftCnt);
    
    }
    else
    {
        /*最后一段空间*/
        ulDataShiftCntNotRing = (u32)((u32)g_sciDataGblAddr - (u32)(SCI_DATA_BASE_ADDR + SCI_DATA_RING_SIZE));
        ulDataShiftCntNotRing =  ulDataShiftCntNotRing / SCI_DATA_TOTAL_MAX_LGTH;
        if(ulDataShiftCntNotRing < SCI_RECORD_DATA_CNT)
        {
            if(g_sciDataLastNotRing != NULL)
            {
                ulDataShiftCnt = (SCI_RECORD_DATA_CNT - ulDataShiftCntNotRing);
                pSciDataShift = (u8*)(g_sciDataLastNotRing - (ulDataShiftCnt * SCI_RECORD_PER_DATA_LEN));
            
                (void)memcpy_s(pStrRecordInfo->SimRecordData,(SCI_RECORD_PER_DATA_LEN * ulDataShiftCnt ),pSciDataShift,SCI_RECORD_PER_DATA_LEN * ulDataShiftCnt);/*循环以前的buf*/
                ulDataShiftCntNotRing *= SCI_DATA_TOTAL_MAX_LGTH;
                (void)memcpy_s((pStrRecordInfo->SimRecordData + SCI_RECORD_PER_DATA_LEN * ulDataShiftCnt),(ulDataShiftCntNotRing ),(SCI_DATA_BASE_ADDR + SCI_DATA_RING_SIZE),ulDataShiftCntNotRing );
        
            } 
        }
        else
        {
            (void)memcpy_s(pStrRecordInfo->SimRecordData,(SCI_RECORD_DATA_LEN ), (SCI_DATA_BASE_ADDR + SCI_DATA_RING_SIZE), SCI_RECORD_DATA_LEN);
        }
        ulLogLength += SCI_RECORD_DATA_LEN;
        
    }
 
    /* event */
    ulEventBaseCnt  = *(u32 *)(SCI_EVENT_BASE_ADDR+4);
    ulEventShiftCnt = (ulEventBaseCnt>SCI_RECORD_EVENT_CNT)?SCI_RECORD_EVENT_CNT:ulEventBaseCnt;
    ulEventBaseCnt  = ulEventBaseCnt - ulEventShiftCnt;

    ulEventBaseCnt += 1;
  
    /* coverity[overrun-buffer-arg] */
    (void)memcpy_s(pStrRecordInfo->SciEvent,(ulEventShiftCnt * 16 ),(usim_event_history_ptr->event_ring + ulEventBaseCnt),(ulEventShiftCnt * 16));
    
    ulLogLength += ulEventShiftCnt*(sizeof(u32)*4);
    * pulLength = ulLogLength;
    
    return BSP_OK;
    
}

u32* sci_global_print(s32 fd,char*tmp_buf_start,u32* exc_global,char* content_buf)
{
    if(exc_global == NULL || content_buf == NULL)
    {
        return NULL;
    }

    sci_record_format(tmp_buf_start,&content_buf,"The global variable SCI_STATE_STRU g_strSciState is\n"); 
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->eCurrentState is   :  0x%.8x\n", *(exc_global++));    
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->eProtocol is       :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->eConvention is     :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->Padding is         :  0x%.8x\n", *(exc_global++));    
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->pBase              :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->pDataBuffer is     :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The g_strSciState->DataLength is      :  0x%.8x\n", *(exc_global++));   
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);


    /*apPL131_sSetupParams   sSetupParams*/   
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ClockFreq is        :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->DebounceTime is     :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ActEventTime is     :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->DeactEventTime is   :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ATRStartTime is     :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ATRDuration is      :  0x%.8x\n", *(exc_global++));    
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->CharacterTime is    :  0x%.8x\n", *(exc_global++));
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->BlockTime is        :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->BlockGuard is       :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->CardFreq is         :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ClockIsOpenDrain is :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->ReceiveTime is      :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->StopTime is         :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->StartTime is        :  0x%.8x\n", *(exc_global++));    
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->RxRetries is        :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->TxRetries is        :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->eRxHandshake is     :  0x%.8x\n", *(exc_global++));
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->eTxHandshake is     :  0x%.8x\n", *(exc_global++));
    sci_record_format(tmp_buf_start,&content_buf,"The sSetupParams->Padding is          :  0x%.8x\n", *(exc_global++));
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);

    /*apPL131_sATRParams   sATRParams*/
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->eBitRateAdj is        :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->eClkRateConv is       :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->eClkStopInd is        :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->Padding is            :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->ClassInd is           :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->ProtocolType is       :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->AltProtocolType is    :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->ChGuard is            :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->pATRBuffer is         :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->BufferAt is           :  0x%.8x\n", *(exc_global++));   
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->InterfaceByteQual is  :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->HasChecksum is        :  0x%.8x\n", *(exc_global++)); 
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->Checksum is           :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->CharPresent is        :  0x%.8x\n", *(exc_global++));
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->Grouping is           :  0x%.8x\n", *(exc_global++));
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->Current is            :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->NumHist is            :  0x%.8x\n", *(exc_global++));  
    sci_record_format(tmp_buf_start,&content_buf,"The sATRParams->WI is                 :  0x%.8x\n", *(exc_global++));
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);

    return exc_global;
    
}

u32* sci_register_print(s32 fd,char*tmp_buf_start,u32* reg_global,char* content_buf)
{
    u32 i = 0;

    if(content_buf == NULL || reg_global == NULL)
    {
        return NULL;
    }
    sci_record_format(tmp_buf_start,&content_buf,"The current register variable are\n");
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegData           :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegCtrl0          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegCtrl1          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegCtrl2          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegClkICC         :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegBaudValue      :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegBaud           :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegTide           :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegDMACtrl        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegStable         :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegATime          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);
    
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegDTime          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegATRSTime       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegATRDTime       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegStopTime       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegStartTime      :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegRetry          :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegChTimeLS       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegChTimeMS       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegBlkTimeLS      :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegBlkTimeMS      :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);

    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegChGuard        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegBlkGuard       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegRxTime         :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegFlag           :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegTxCount        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegRxCount        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegIntMask        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegIntRaw         :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegIntStatus      :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegIntClear       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegSyncAct        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegSyncData       :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG->RegSyncRaw        :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG PADDING            :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_format(tmp_buf_start,&content_buf,"0x%.2x:  SCI_REG PADDING            :  0x%.8x \n", (SCI_BASE_ADDR+ (i++)*0x10),*((u32*)(reg_global++)));
    sci_record_flush2file(fd,tmp_buf_start,&content_buf);

    return reg_global;
    
    
}


#ifdef __cplusplus
}
#endif
/*lint -restore */

