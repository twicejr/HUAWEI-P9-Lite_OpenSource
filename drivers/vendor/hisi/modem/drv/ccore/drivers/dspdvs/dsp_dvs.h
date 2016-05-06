/*************************************************************************
*   版权所有(C) 2010-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  dsp_dvs.c
*
*   作    者 :  l00312158
*
*   描    述 :  本文件主要完成DSP的调压请求
*
*   修改记录 :  2015年11月10日  v1.00  l00312158  创建
*************************************************************************/
#ifndef __DSP_DVS_H__
#define __DSP_DVS_H__
    
#ifdef __cplusplus
    extern "C" {
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <bsp_regulator.h>
#include <osl_thread.h>
#include <bsp_ipc.h>

#include <mdrv.h>
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DSPDVS_OK (0)
#define DSPDVS_ERROR (-1)
#define HIGH_VOLTAGE_REQ (1)
#define LOW_VOLTAGE_REQ  (0)
#define BBE_HIGH_VOLTAGE (900000)
#define BBE_LOW_VOLTAGE  (800000)
#define BBP_HIGH_VOLTAGE (800000)
#define BBP_LOW_VOLTAGE  (725000)
#define SS_CHIP_TYPE_FLAG (0x5a5a5a5a)
#define DSPDVS_RESPOND_FLAG (0xaa)
#define DSPDVS_MNTN_NUMBER (30)
#define DSPDVS_WAIT_FOREVER (-1)
#define DSPDVS_HPM_VAL      (490)
#define DSP_PWRTYPE  "dsp_dvs"
#define BBP_PWRTYPE  "bbp_dvs"
    
#define dspdvs_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_DSPDVS, "[dspdvs]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
    
#define dspdvs_malloc(size)     osl_malloc(size)
#define dspdvs_free(ptr)        osl_free(ptr)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
struct dspdvs_ctrl
{
    u32 HPM_val;
    u32 ss_chip_flag;
    u32 dsp_dvs_TsensorTempFlag;
    osl_sem_id dspdvs_task_sem;
    spinlock_t spin_lock;
    BSP_BOOL dspdvs_DspReqFlag;
    BSP_BOOL dspdvs_TsensorReqFlag;
    char *dsp_pwrtype;
    char *bbp_pwrtype;
    struct regulator *dspdvs_pmu;
    struct regulator *bbpdvs_pmu;
};

struct dspdvs_req
{
    u8 dspdvs_req_flag;
    u8 dspdvs_req_id;
    u8 dsp_dvs_req;
    u8 bbp_dvs_req;
    u32 req_timestamp;
};

struct dspdvs_respond
{
    u8 dspdvs_respond_flag;
    u8 dspdvs_respond_id;
    u8 dsp_dvs_respond;
    u8 bbp_dvs_respond;
    u32 respond_timestamp;
};

struct dspdvs_mntn_tsensor_req
{
    u32 ulslice;
    u32 temperature;
};

struct dspdvs_mntn_reqslice
{
    u32 ulptr;              /* 循环指针,用于循环存储 */
    struct dspdvs_mntn_tsensor_req req_info[DSPDVS_MNTN_NUMBER];   /* slice 记录 */
};

struct dspdvs_mntn_intslice
{
    u32 ulptr;              /* 循环指针,用于循环存储 */
    u32 ulslice[DSPDVS_MNTN_NUMBER];   /* slice 记录 */
};

struct dspdvs_req_record
{
    u32 streq;                /* 记录dsp发起的调压请求，或者ARM的应答请求*/
    u32 streq_timestamp;
};

struct dspdvs_respond_record
{
    u32 strespond;                /* 记录dsp发起的调压请求，或者ARM的应答请求*/
    u32 strespond_timestamp;
    u32 stbbpvoltage;                /* 当处理完DSP调压请求之后，把当前电压值记录下来 */
    u32 stdspvoltage;                /* 当处理完DSP调压请求之后，把当前电压值记录下来 */
};

struct dspdvs_mntn_req_record
{
    u32 ulnxtptr;
    u32 ulcurrentptr;
    struct dspdvs_req_record streqrecord[DSPDVS_MNTN_NUMBER];
};

struct dspdvs_mntn_respond_record
{
    u32 ulnxtptr;
    u32 ulcurrentptr;
    struct dspdvs_respond_record strespondrecord[DSPDVS_MNTN_NUMBER];
};

struct dspdvs_mntn
{
    u32 dspdvs_intcount;
    u32 dspdvs_tsensorreqcount;
    struct dspdvs_mntn_intslice stintinfo;
    struct dspdvs_mntn_reqslice sttsensorreqinfo;
    struct dspdvs_mntn_req_record stdspreqinfo;
    struct dspdvs_mntn_respond_record stdspdvsrespondinfo; 
};

/*****************************************************************************
  5 函数声明
*****************************************************************************/


#ifdef __cplusplus
}
#endif

#endif





