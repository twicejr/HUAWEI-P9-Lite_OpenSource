/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bsp_tele_mntn.h
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年5月17日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月17日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifndef __BSP_TELE_MNTN_H__
#define __BSP_TELE_MNTN_H__

#include <linux/hisi/hisi_tele_mntn.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct tele_mntn_queue
{
    unsigned char* base;            /* 队列基地址       */
    unsigned int length;            /* 队列总长度，单位byte */
    unsigned char* front;           /* 队列写指针, 绝对地址，in   */
    unsigned char* rear;            /* 队列读指针, 绝对地址，out  */
}TELE_MNTN_QUEUE_STRU;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : tele_mntn_write_log
 功能描述  : 保存log接口
 输入参数  : TELE_MNTN_TYPE_ID type_id
             u32_t len
             void_t * data
 输出参数  : 无
 返 回 值  : s32_t
 调用函数  :
 被调函数  :
 说    明  : 该函数一次传输len最大值为64字节，建议len为8字节对齐。
             未避免多次调用影响性能，建议一个type_id一次流程的数据封装成结构体，一次性存入telemntn
 举    例  : hifi上电，该完整流程的log记录

             hifi上下电的typeid为 TELE_MNTN_PUPD_HIFI 表示上电和下电，可以分解为两个流程，上电和下电。
             对于上电流程，建议将PWC_TELE_MNTN_PU_STRU填充满后再调用执行tele_mntn_write_log接口，
             不建议一个流程调用执行多次tele_mntn_write_log接口。


             typedef struct PWC_TELE_MNTN_PU_STRU_S
             {
                 u32_t  wakeCount;
                 u32_t  wakeSrc0;
                 u32_t  wakeSrc1;
                 u32_t  wakeSrcIPC;
                 u8_t   wakeSrcGPIO[8];
             }PWC_TELE_MNTN_PU_STRU;

     	     typedef struct PWC_TELE_MNTN_PD_STRU_S
     	     {
     	         u32_t  sleepCount;
     	     }PWC_TELE_MNTN_PD_STRU;

             typedef struct PWC_TELE_MNTN_PUPD_STRU_S
             {
                 PWC_TELE_MNTN_PD_STRU pdStat;
                 PWC_TELE_MNTN_PU_STRU puStat; //该结构体数据log会记录到telemntn中
                 u32_t pdSliceTime;
                 u32_t puSliceTime;  //该时间为本地记录时间
             }PWC_TELE_MNTN_PUPD_STRU;

             g_hifi_log = (PWC_TELE_MNTN_PUPD_STRU *)0x25000; //全局变量，指向固定内存空间
             s32_t  pwc_power_up_hifi( void_t )
             {
                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeCount++;

                 上电处理……

                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeSrc0 = xxx;
                 g_hifi_log->puStat.wakeSrcIPC = xxx;
                 g_hifi_log->puStat.wakeSrcGPIO = xxx;
                 g_hifi_log->puSliceTime = get_slice_time();

                 //将该次完整流程记录到telemntn中，不带时间信息
                 (void)tele_mntn_write_log(TELE_MNTN_PUPD_HIFI,sizeof(g_hifi_log->puStat),&(g_hifi_log->puStat));

                 return RET_OK;
             }

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : 李彬彬 00186593
    修改内容   : 新生成函数

*****************************************************************************/
extern int tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, unsigned int len, const void *data);
extern int tele_mntn_init(void);
extern int tele_mntn_wake_up_acore(void);
extern int tele_mntn_get_head(struct tele_mntn_queue *queue);
extern int tele_mntn_set_head(const struct tele_mntn_queue *queue);
extern int tele_mntn_is_func_on (TELE_MNTN_TYPE_ID type_id);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_tele_mntn.h */
