/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_i2c.h */
/* Version       : 2.0 */
/* Created       : 2013-04-16*/
/* Last Modified : */
/* Description   :  The C union definition file for the module i2c*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_I2C_H__
#define __HI_I2C_H__

/*
 * Project: hi
 * Module : i2c
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    i2c 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_I2C_CTRL_OFFSET                                (0x0) /* I2C控制寄存器。 */
#define    HI_I2C_COM_OFFSET                                 (0x4) /* I2C命令寄存器。 */
#define    HI_I2C_ICR_OFFSET                                 (0x8) /* I2C中断清除寄存器。 */
#define    HI_I2C_SR_OFFSET                                  (0xC) /* I2C状态寄存器。 */
#define    HI_I2C_SCL_H_OFFSET                               (0x10) /* I2C SCL高电平周期数寄存器。 */
#define    HI_I2C_SCL_L_OFFSET                               (0x14) /* I2C SCL低电平周期数寄存器。 */
#define    HI_I2C_TXR_OFFSET                                 (0x18) /* I2C发送数据寄存器。 */
#define    HI_I2C_RXR_OFFSET                                 (0x1C) /* I2C接收数据寄存器。 */

/********************************************************************************/
/*    i2c 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    int_done_mask              : 1; /* [0..0] 总线传输完成中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_arb_loss_mask          : 1; /* [1..1] 总线仲裁失败中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_ack_err_mask           : 1; /* [2..2] 从机ACK错误中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_rx_mask                : 1; /* [3..3] 主机接收中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_tx_mask                : 1; /* [4..4] 主机发送中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_stop_mask              : 1; /* [5..5] 主机停止条件发送结束中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_start_mask             : 1; /* [6..6] 主机开始条件发送结束中断屏蔽。0：屏蔽中断；1：不屏蔽中断。 */
        unsigned int    int_mask                   : 1; /* [7..7] I2C中断总屏蔽。0：屏蔽所有中断；1：不屏蔽所有中断。 */
        unsigned int    i2c_en                     : 1; /* [8..8] I2C使能。0：不使能；1：使能。 */
        unsigned int    reserved                   : 23; /* [31..9] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_CTRL_T;    /* I2C控制寄存器。 */

typedef union
{
    struct
    {
        unsigned int    op_stop                    : 1; /* [0..0] 产生停止条件操作。0：操作结束；1：操作有效。 */
        unsigned int    op_we                      : 1; /* [1..1] 产生写操作。0：操作结束；1：操作有效。 */
        unsigned int    op_rd                      : 1; /* [2..2] 产生读操作。0：操作结束；1：操作有效。 */
        unsigned int    op_start                   : 1; /* [3..3] 产生开始条件操作。0：操作结束；1：操作有效。 */
        unsigned int    op_ack                     : 1; /* [4..4] 主机作为接收器是否发送ACK。0：发送ACK；1：不发送ACK。 */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_COM_T;    /* I2C命令寄存器。 */

typedef union
{
    struct
    {
        unsigned int    clr_int_done               : 1; /* [0..0] 总线传输完成中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_arb_loss           : 1; /* [1..1] 总线仲裁失败中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_ack_err            : 1; /* [2..2] 从机ACK错误中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_rx                 : 1; /* [3..3] 主机接收中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_tx                 : 1; /* [4..4] 主机发送中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_stop               : 1; /* [5..5] 主机停止条件发送结束中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    clr_int_start              : 1; /* [6..6] 主机开始条件发送结束中断标志清除。0：不清除中断标志；1：清除中断标志。 */
        unsigned int    reserved                   : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_ICR_T;    /* I2C中断清除寄存器。 */

typedef union
{
    struct
    {
        unsigned int    int_done                   : 1; /* [0..0] 总线传输完成中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_arb_loss               : 1; /* [1..1] 总线仲裁失败中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_ack_err                : 1; /* [2..2] 从机ACK错误中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_rx                     : 1; /* [3..3] 主机接收中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_tx                     : 1; /* [4..4] 主机发送中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_stop                   : 1; /* [5..5] 主机停止条件发送结束中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    int_start                  : 1; /* [6..6] 主机开始条件发送结束中断标志。0：无中断标志产生；1：中断标志产生。 */
        unsigned int    bus_busy                   : 1; /* [7..7] 总线忙。0：空闲；1：忙。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_SR_T;    /* I2C状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    scl_h                      : 16; /* [15..0] scl_h*2是SCL高电平周期数。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_SCL_H_T;    /* I2C SCL高电平周期数寄存器。 */

typedef union
{
    struct
    {
        unsigned int    scl_l                      : 16; /* [15..0] scl_l*2是SCL低电平周期数。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_SCL_L_T;    /* I2C SCL低电平周期数寄存器。 */

typedef union
{
    struct
    {
        unsigned int    i2c_txr                    : 8; /* [7..0] 主机发送数据。发送结束后，I2C模块不会修改I2C_TXR内容。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_TXR_T;    /* I2C发送数据寄存器。 */

typedef union
{
    struct
    {
        unsigned int    i2c_rxr                    : 8; /* [7..0] 主机接收数据。I2C_RXR数据在I2C_SR bit[3]=1时，数据有效。同时数据将保持到下一个读操作之前。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2C_RXR_T;    /* I2C接收数据寄存器。 */


/********************************************************************************/
/*    i2c 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_i2c_ctrl_int_done_mask,int_done_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_arb_loss_mask,int_arb_loss_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_ack_err_mask,int_ack_err_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_rx_mask,int_rx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_tx_mask,int_tx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_stop_mask,int_stop_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_start_mask,int_start_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_mask,int_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_i2c_en,i2c_en,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_reserved,reserved,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_com_op_stop,op_stop,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_we,op_we,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_rd,op_rd,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_start,op_start,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_ack,op_ack,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_reserved,reserved,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_done,clr_int_done,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_arb_loss,clr_int_arb_loss,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_ack_err,clr_int_ack_err,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_rx,clr_int_rx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_tx,clr_int_tx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_stop,clr_int_stop,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_start,clr_int_start,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_reserved,reserved,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_done,int_done,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_arb_loss,int_arb_loss,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_ack_err,int_ack_err,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_rx,int_rx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_tx,int_tx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_stop,int_stop,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_start,int_start,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_bus_busy,bus_busy,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_reserved,reserved,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_scl_h_scl_h,scl_h,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_h_reserved,reserved,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_l_scl_l,scl_l,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_scl_l_reserved,reserved,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_txr_i2c_txr,i2c_txr,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_txr_reserved,reserved,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_i2c_rxr,i2c_rxr,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_reserved,reserved,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)

#endif // __HI_I2C_H__

