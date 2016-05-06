/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  pdlock_balong.h
*
*   作    者 :  l00312158
*
*   描    述 :  本文件主要完成总线防挂死数据结构
*
*   修改记录 :  2015年5月11日  v1.00  l00312158  创建
*************************************************************************/
#ifndef __PDLOCK_BALONG_H__
#define __PDLOCK_BALONG_H__
    
#ifdef __cplusplus
    extern "C" {
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mdrv_errno.h"
#include "bsp_om.h"
#include "bsp_om_enum.h"

#include "osl_types.h"
#include "osl_malloc.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define pdlock_ok (0)
#define pdlock_error (-1)

#define MAX_RECORD (100)
#define FIRST_RECORD (20)

#define PDLOCK_DUMP_SAVE_MOD   DUMP_CP_PDLOCK

#define pdlock_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_PDLOCK, "[pdlock]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#define pdlock_malloc(size)     osl_malloc(size)
#define pdlock_free(ptr)        osl_free(ptr)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum pdlock_sysctrl_reg
{
    pd_glb = 0,
    modem_glb,
    pcie_glb,
    ao_glb,
    sysctrl_sum
};

enum
{
    magic = 0,      /*dump空间头信息中的魔术字*/
    max_log,        /*dump空间头信息中的最大能够保存异常信息的数目*/
    total,          /*dump空间头信息中的当前触发防挂死逻辑的总次数*/
    offset          /*dump空间头信息中的当前保存异常信息的位置*/
};

enum
{
    base_addr = 0,
    addr_offset,
    start_bit,
    end_bit
};

enum
{
    PDLOCK_DISABLE = 0,
    PDLOCK_ENABLE = 1
};

enum
{
    PDLOCK_RESET_DISABLE = 0,
    PDLOCK_RESET_ENABLE = 1
};
/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
struct pdlock_cfg
{
    u8  dump_mst_id;
    u8  dump_operation;
    u8  reserved[2];
    u32 mst_reg_addr[3];     /*错误状态寄存器偏移地址、起始位、终止位*/
    u32 mst_id_addr[3];      /*mstid 错误状态寄存器偏移地址、起始位、终止位(为V722预留)*/
    u32 mst_operation[3];    /*mst 操作类型寄存器偏移地址、起始位、终止位(V722 APB/AHB特有）*/
    char mst_name[32];               /*master名字及操作类型*/
    u32 error_address_offset;     /*访问错误地址寄存器的偏移地址*/
};                               

struct pdlock_bus
{
    u8   dump_bus_id;             /*bus_id*/
    u8   reserved[3];
    u32  base_addr;               /*寄存器虚拟基址*/
    char busname[16];             /*总线名字*/
    u32  reg_state_sum;           /*错误状态寄存器个数*/ 
    struct pdlock_cfg *cfg;       /*错误状态寄存器记录的信息*/
};                                /*总线数据结构*/

struct pdlock_sysctrl
{
    u32 reset_reg_addr[4];        /*复位错误状态寄存器基址、偏移、起始位、终止位*/
    u32 bus_sum;                  /*总线数目*/
    struct pdlock_bus *bus;       /*总线数据结构*/
};

struct pdlock_state
{
    u32 enable;                   /*从NV读取配置，判断是否使能防挂死逻辑，0代表不使能，1代表使能*/
    u32 reset_enable;             /*从NV读取配置，当触发防挂死逻辑时，判断是否复位系统，0代表不复位，1代表复位*/
};

struct pdlock_dump_record
{
    u8 bus_id;                    /*在dump中记录异常信息的bus_id*/
    u8 mst_id;                    /*在dump中记录异常信息的mst_id*/
    u8 operation;                 /*在dump中记录master发起的操作类型，1代表写操作，2代表读操作，0代表操作类型未知*/
    u8 reserved;
    u32 slave_addr;               /*在dump中记录异常信息的slave address*/
    u32 slice;                    /*在dump中记录异常信息的时间戳*/
};

/*****************************************************************************
  5 函数声明
*****************************************************************************/
s32 bsp_pdlock_init(void);



#ifdef __cplusplus
}
#endif

#endif






