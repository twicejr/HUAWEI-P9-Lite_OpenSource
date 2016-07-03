
#ifndef __DSP_TEST_INTERFACE_H__
#define __DSP_TEST_INTERFACE_H__

/************************************************************
                     包含其它模块的头文件
************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "TLPhyInterface.h"

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

#define LPHY_MAILBOX_BASE_ADDR_DSP          (LPHY_MAILBOX_BASE_ADDR)                          /*邮箱共享基地定义*/
#define TL_PHY_MAILBOX_SOC_TEST_ADDR        (LPHY_MAILBOX_BASE_ADDR_DSP + 0x4000)   /*DSP压力测试与底软的邮箱基址*/

typedef union
{
    struct
    {
        unsigned int ulPPTR :8;
        unsigned int ulCPTR :8;
        unsigned int ulMsgID:16;
    }bits;
    unsigned int ulReg32;
}DSP_DRV_MAIL_HEAD;

typedef union
{
    struct
    {
        unsigned int ulAddr;
        unsigned int ulLen;
        unsigned int ulResult;
        unsigned int ulNum;
    }writeReadTest;
    struct
    {
        unsigned int ulSrcAddr;
        unsigned int ulDestinAddr;
        unsigned int ulLen;
        unsigned int ulNum;
    }readWriteTest;
    struct
    {
        unsigned int ulFuncID;
        unsigned int ulCycle;
        unsigned int ulNum;
        unsigned int ulRsvd;
    }funcCycleCalc;
}DSP_DRV_MAIL_BODY;


typedef struct _DSP_DRV_MAIL_
{
	DSP_DRV_MAIL_HEAD strMailHead;
    DSP_DRV_MAIL_BODY strMailBody;
    unsigned int      ulRunCount;
}DSP_DRV_MAIL;

typedef enum
{
	WRITE_READ_TEST = 0,
	READ_WRITE_TEST,
	FUNC_CYCLE_CALC,
}MSG_TYPE_ENUM;

typedef enum
{
	FUNC_DHRYSTONE = 0,
	FUNC_WAITI,
	FUNC_NULL,
}FUNC_TYPE_ENUM;



/************************************************************
                             接口函数声明
 ************************************************************/
#if (defined(TENSILICA_PLATFORM) && defined(CONFIG_MODULE_BUSSTRESS))
void BBE_OnBoardTest(void);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DSPTEST_H__ */
