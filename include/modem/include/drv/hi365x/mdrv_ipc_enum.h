/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __MDRV_IPC_ENUM_H__
#define __MDRV_IPC_ENUM_H__
#ifdef __cplusplus
extern "C"
{
#endif

/* 处理器类型*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_ARM11 = 0x0,   /* P500上的IPC */
    IPC_CORE_A9,
    IPC_CORE_CEVA,
    IPC_CORE_TENS0,
    IPC_CORE_TENS1,
    IPC_CORE_DSP,
    IPC_CORE_APPARM = 0x0,  /* V7R1/V3R2上的IPC */
    IPC_CORE_COMARM,
    IPC_CORE_LTEDSP,
    IPC_CORE_VDSP,
    IPC_CORE_ZSP,
    IPC_CORE_DSP_GU,
    IPC_CORE_ACPU = 0x0,    /* V9R1 SFT上的IPC */
    IPC_CORE_CCPU,
    IPC_CORE_MCU,
    IPC_CORE_HIFI,
    IPC_CORE_BBE16,
    IPC_CORE_ACORE = 0x0,   /*P531,V7R2*/
    IPC_CORE_CCORE,
    IPC_CORE_MCORE,
    IPC_CORE_LDSP,
    IPC_CORE_HiFi,
    IPC_CORE_BBE,           /*..5..P531\V7R2...........P531..*/
    IPC_CORE0_A15,
    IPC_CORE1_A15,
    /* !!!!新增元素请添加到最后  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

/*********************************************************
*  添加新IPC资源，枚举命名格式:
*  IPC_<目标处理器>_INT_SRC_<源处理器>_<功能/作用>
*  目标处理器:ACPU、CCPU、MCU、HIFI、BBE16
*  源处理器  :ACPU、CCPU、MCU、HIFI、BBE16
*  功能/作用 :
*********************************************************/
#if defined(CHIP_BB_HI6210)
typedef enum tagIPC_INT_LEV_E
{
   /* 定义CCPU IPC跨核消息中断源bit位置 */
    IPC_INT_DSP_MODEM                   = 0,
    IPC_CCPU_INT_SRC_HIFI_MSG           = 1,    /* bit1, HIFI跨核消息通知 */
    IPC_INT_DSP_MSP                     = 2,
    IPC_INT_DSP_PS 						= 3,
    IPC_CCPU_INT_SRC_MCU_MSG            = 5,    /* bit5, MCU跨核消息通知 */
    IPC_CCPU_INT_SRC_ACPU_MSG           = 6,    /* bit6, ACPU跨核消息通知 */
    IPC_CCPU_INT_SRC_ACPU_IFC           = 7,    /* bit7, ACPU跨核函数调用通知 */
    IPC_INT_DSP_HALT                    = 8,    /* bit8, DSP通知ARM睡眠*/
    IPC_INT_DSP_RESUME                  = 9,    /* bit9, DSP通知ARM完成唤醒后的恢复操作*/
    IPC_CCPU_INT_SRC_MCU_IFC            = 10,   /* bit10, MCU跨核函数调用通知*/
    IPC_INT_WAKE_GU                     = 11,   /* bit11, 主模唤醒从模中断*/
    IPC_INT_SLEEP_GU                    = 12,   /* bit12, 从模睡眠中断*/
    IPC_INT_DICC_USRDATA_ACPU           = 13,   /* bit13, 占位,该值必须与IPC_INT_DICC_USRDATA一致*/
    IPC_INT_DICC_RELDATA_ACPU           = 14,   /* bit14, 占位,该值必须与IPC_INT_DICC_USRDATA一致*/
    IPC_INT_ARM_SLEEP                   = 15,   /* bit15, 由8修改为15*/
    /* 定义TDS使用的邮箱IPC中断,begin */
    IPC_INT_WAKE_GSM                    = 16,   /* bit16, BBE16通知CCPU,唤醒GSM从模 */
    IPC_INT_WAKE_WCDMA                  = 17,   /* bit17, BBE16通知CCPU,唤醒WCDMA从模 */
    IPC_INT_DSP_PS_PUB_MBX              = 18,   /* bit18, 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_PS_MAC_MBX              = 19,   /* bit19, 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_MBX_RSD                 = 20,   /* bit20, 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_CCPU_INT_SRC_DSP_MNTN           = 21,   /* bit21，BBE16可维可测中断通知mailbox，崔军强 */
    IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX    = 22,   /* bit22*/
    /* 定义TDS使用的邮箱IPC中断,end */
    IPC_CCPU_INT_SRC_ACPU_ICC           = 30,   /* bit30, ACPU ICC跨核消息通知*/
    IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR = 31, /* BBE16通知C核发生了通道异常 */
    IPC_CCPU_INT_SRC_BUTT               = 32,

   /* 定义MCU IPC跨核消息中断源bit位置 */
    IPC_MCU_INT_SRC_ACPU_MSG            = 4,    /* bit4, ACPU跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_MSG            = 5,    /* bit5, CCPU跨核消息通知 */
    IPC_MCU_INT_SRC_HIFI_MSG            = 6,    /* bit6, HIFI跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_IFC            = 7,    /* bit7, HIFI跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_IPF            = 8,    /* bit8, IPF低功耗 */
    IPC_MCU_INT_SRC_ACPU_IFC            = 9,    /* bit9, ACPU跨核函数调用通知 */
    IPC_MCU_INT_SRC_ACPU0_PD            = 10,   /* bit10, acpu0 power down */
    IPC_MCU_INT_SRC_ACPU1_PD            = 11,   /* bit11, acpu1 power down */
    IPC_MCU_INT_SRC_ACPU2_PD            = 12,   /* bit12, acpu2 power down */
    IPC_MCU_INT_SRC_ACPU3_PD            = 13,   /* bit13, acpu3 power down */
    IPC_MCU_INT_SRC_ACPU_HOTPLUG        = 14,   /* bit14, acpu hotplug--no use */
    IPC_MCU_INT_SRC_ACPU_DFS            = 15,   /* bit15, ACPU DFS*/
    IPC_MCU_INT_SRC_ACPU_PD             = 16,   /* bit16, acpu power down */
    IPC_MCU_INT_SRC_CCPU_PD             = 17,   /* bit17, ccpu power down */
    IPC_MCU_INT_SRC_HIFI_PD             = 18,   /* bit18, hifi power down */
    IPC_MCU_INT_SRC_MCU_AGT             = 19,   /* bit19, mcu agent */
    IPC_MCU_INT_SRC_HIFI_DDR_VOTE       = 20,   /* bit20, HIFI DDR自刷新投票 */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    = 21,   /* bit21, ACPU 全系统SLOW态浅睡投票 */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   = 22,   /* bit22, ACPU 全系统TCXO和外设不下电浅睡投票 */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID = 23,   /* bit23, ACPU 全系统浅睡去投票 */
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_VOTE = 24,    /* bit24, MP3超低功耗播放使用HARQMEM,HIFI DDR自刷新投票*/
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_EXIT_VOTE = 25, /* bit25, MP3超低功耗播放使用HARQMEM,HIFI投票DDR退出自刷新*/
    IPC_MCU_INT_SRC_ACPU4_PD            = 26,   /* bit26, acpu4:cluster1 core0 power down */
    IPC_MCU_INT_SRC_ACPU5_PD            = 27,   /* bit27, acpu5:cluster1 core1 power down */
    IPC_MCU_INT_SRC_ACPU6_PD            = 28,   /* bit28, acpu6:cluster1 core2 power down */
    IPC_MCU_INT_SRC_ACPU7_PD            = 29,   /* bit29, acpu7:cluster1 core3 power down */
    IPC_MCU_INT_SRC_HIFI_IFC            = 31,   /* bit31, HIFI跨核函数调用通知*/
    IPC_MCU_INT_SRC_BUTT                = 32,

    /* 定义ACPU IPC跨核消息中断源bit位置 */
    IPC_ACPU_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU跨核消息通知 */
    IPC_ACPU_INT_SRC_HIFI_MSG           = 2,    /* bit2, HIFI跨核消息通知 */
    IPC_ACPU_INT_SRC_MCU_MSG            = 3,    /* bit3, ACPU跨核消息通知 */
    IPC_ACPU_INT_SRC_CCPU_NVIM          = 4,    /* bit4, 用于NVIM模块C核与A核之间的同步*/
    IPC_ACPU_INT_SRC_CCPU_IFC           = 5,    /* bit5, CCPU跨核函数调用通知  */
    IPC_ACPU_INT_SRC_MCU_IFC            = 6,    /* bit6, MCU跨核函数调用通知  */
    IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH   = 7,    /* bit7, MCU电池放电高温关机IPC中断通知ACPU*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_LOW    = 8,    /* bit8, MCU电池放电低温关机IPC中断通知ACPU*/
    IPC_INT_DSP_APP                     = 9,    /* bit9, LDSP跨核通知 */
    IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA = 10,  /* hifi->acore pc voice */
    IPC_INT_DICC_USRDATA                = 13,   /* bit13, TTF组件CCPU跨核通知，必须与IPC_INT_DICC_USRDATA_ACPU同时修改*/
    IPC_INT_DICC_RELDATA                = 14,   /* bit14, TTF组件CCPU跨核通知，必须与IPC_INT_DICC_RELDATA_ACPU同时修改*/
    IPC_ACPU_INT_SRC_CCPU_LOG = 25,   /* bit25,   CCPU发送给ACPU的LOG保存中断*/
    IPC_ACPU_INI_SRC_MCU_TELE_MNTN_NOTIFY    = 26,   /* bit26, TELE_MNTN唤醒ACPU通知 */
    IPC_ACPU_INI_SRC_MCU_EXC_REBOOT     = 27,   /* bit27, MCU异常复位跨核通知 */
    IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT    = 28,   /* bit28, CCPU异常复位跨核通知 */
    IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT = 29,   /* bit29, CCPU正常复位跨核通知 */
    IPC_ACPU_INT_SRC_MCU_DDR_EXC        = 30,   /* bit30, MCU DDR异常跨核通知 */
    IPC_ACPU_INT_SRC_CCPU_ICC           = 31,   /* bit31, CCPU ICC跨核消息通知 */
    IPC_ACPU_INT_SRC_BUTT               = 32,


    /* 定义HIFI IPC跨核消息中断源bit位置 */
    IPC_HIFI_INT_SRC_ACPU_MSG           = 0,    /* bit0, ACPU跨核消息通知 */
    IPC_HIFI_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU跨核消息通知 */
    IPC_HIFI_INT_SRC_BBE_MSG            = 4,    /* bit4, TDDSP跨核消息通知 */
    IPC_HIFI_INT_SRC_MCU_MSG            = 6,    /* bit6, MCU跨核消息通知 */
    IPC_HIFI_INT_SRC_MCU_WAKE_DDR       = 7,    /* bit7, MCU通知HIFI唤醒DDR */
    IPC_HIFI_INT_SRC_MCU_IFC            = 8,    /* bit8, MCU跨核函数调用通知 */
    IPC_HIFI_INT_SRC_BUTT               = 32,

    /* 定义BBE16 IPC跨核消息中断源bit位置 */
    IPC_INT_MSP_DSP_OM_MBX              = 0,   /* bit0, 下行ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX              = 1,   /* bit1, 下行ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX              = 2,   /* bit2, 下行ARM->DSP */
    IPC_INT_HIFI_DSP_MBX                = 3,   /* bit3, HIFI->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG          = 3,   /* bit3, 对上为解决v7r2与v9r1兼容问题，bit3同时定义两个宏 */
    IPC_BBE16_INT_SRC_BUTT              = 32,
    /* 仅解决编译问题 */
    IPC_INT_BUTTOM                      = 32
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_ICC = 0,
    IPC_SEM_NAND = 1,
    IPC_SEM_MEM = 2,
    IPC_SEM_DICC = 3,
    IPC_SEM_RFILE_LOG = 4,          /*用于flashless可维可测*/
    IPC_SEM_EMMC = 5,
    IPC_SEM_NVIM = 6,
    IPC_SEM_TELE_MNTN = 7,
    IPC_SEM_MEDPLL_STATE = 8,
	IPC_SEM_EFUSE = 9, 
    IPC_SEM_BBPMASTER_0 = 10,
    IPC_SEM_BBPMASTER_1 = 11,
    IPC_SEM_BBPMASTER_2 = 12,
    IPC_SEM_BBPMASTER_3 = 13,
    IPC_SEM_GU_SLEEP    = 14,
    IPC_SEM_BBPMASTER_5 = 15,
    IPC_SEM_BBPMASTER_6 = 16,
    IPC_SEM_BBPMASTER_7 = 17,
    IPC_SEM_DPDT_CTRL_ANT = 19, /*just for compile in portland*/
    IPC_SEM_SMP_CPU0 = 21,
    IPC_SEM_SMP_CPU1 = 22,
    IPC_SEM_SMP_CPU2 = 23,
    IPC_SEM_SMP_CPU3 = 24,
    IPC_SEM_SYNC = 25,
    IPC_SEM_BBP = 26,           /*该值与BBE16镜像绑定，修改需通知BBE16作相应修改*/
    IPC_SEM_CPUIDLE = 27,   /*CPUIDLE A/M核互斥资源锁*/
	IPC_SEM_BBPPS = 28,         /*BBP PS上下电投票*/
	IPC_SEM_HKADC = 29,     /*A、M核读取HKADC的互斥锁*/
    IPC_SEM_SYSCTRL = 30,
    IPC_SEM_ZSP_HALT = 31,
    IPC_SEM_BUTTOM
}IPC_SEM_ID_E;

#else
typedef enum tagIPC_INT_LEV_E
{
    IPC_CCPU_INT_SRC_HIFI_MSG              = 0, /* HIFI跨核消息通知 */
    IPC_CCPU_INT_SRC_MCU_MSG               = 1, /* MCU跨核消息通知 */
    IPC_INT_DSP_HALT                       = 2, /* DSP通知ARM睡眠*/
    IPC_INT_DSP_RESUME                     = 3, /* DSP通知ARM完成唤醒后的恢复操作*/
                                                /* 4, 占位不允许添加其他值,该值必须与IPC_INT_DICC_USRDATA一致*/
                                                /* 5, 占位不允许添加其他值,该值必须与IPC_INT_DICC_USRDATA一致*/
    IPC_INT_WAKE_GU                        = 6, /* 主模唤醒从模中断*/
    IPC_INT_SLEEP_GU                          , /* 从模睡眠中断*/
    /* 定义TDS使用的邮箱IPC中断,begin */
    IPC_INT_WAKE_GSM                       , /* BBE16通知CCPU,唤醒GSM从模 */
    IPC_INT_WAKE_WCDMA                     , /* BBE16通知CCPU,唤醒WCDMA从模 */
    IPC_INT_DSP_PS_PUB_MBX                 ,/* 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_PS_MAC_MBX                 ,/* 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_MBX_RSD                    ,/* 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_CCPU_INT_SRC_DSP_MNTN              ,/* BBE16可维可测中断通知mailbox，崔军强 */
    IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX       ,
    /* 定义TDS使用的邮箱IPC中断,end */
    IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR , /* BBE16通知C核发生了通道异常 */
    IPC_CCPU_INT_SRC_COMMON_END            , /* V7、V8共有的C核接收中断号结束 */

    /* C核接收，v7  特有的 ipc 中断 */
    IPC_CCPU_INT_SRC_ACPU_RESET            = IPC_CCPU_INT_SRC_COMMON_END,    /* A/C核在C核单独复位期间核间通信(唤醒C核), v8r2走的是核间消息 */
    IPC_CCPU_SRC_ACPU_DUMP                 ,   /* v7r2 可维可测，ACPU 发送给CCPU 的IPC中断 */
    IPC_CCPU_INT_SRC_ICC_PRIVATE           ,   /* v7r2 ICC通信，icc专用发送消息使用,ACPU发送给CCPU的IPC中断       */
    IPC_CCPU_INT_SRC_MCPU                  ,   /* ICC消息, MCU发送给CCPU的  IPC中断 */
    IPC_CCPU_INT_SRC_MCPU_WDT              ,   /* 运行trace时停wdt */
    IPC_CCPU_INT_SRC_XDSP_1X_HALT          ,   /* 1X Halt中断 */
    IPC_CCPU_INT_SRC_XDSP_HRPD_HALT        ,   /* HRPD Halt中断 */
    IPC_CCPU_INT_SRC_XDSP_1X_RESUME        ,   /* 1X Resume中断 */
	IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME      ,   /* HRPD Resume中断 */
	IPC_CCPU_INT_SRC_XDSP_MNTN             ,   /* XDSP邮箱异常维测中断 */
	IPC_CCPU_INT_SRC_XDSP_PS_MBX           ,   /* PS与X模邮箱通信使用的中断 */
    IPC_CCPU_INT_SRC_XDSP_RCM_MBX          ,   /* RCM与X模邮箱通信使用的中断 */

	/*  austin项目和 mcu 通信使用 icc 中断号, 不能变更 */
    IPC_CCPU_INT_SRC_ACPU_ICC			   = 31, /* acpu发给ccpu中断*/
    
	/* C核接收，v8 特有的ipc 中断 */
    IPC_CCPU_INT_SRC_ACPU_MSG              = IPC_CCPU_INT_SRC_COMMON_END,      /* 通用mailbox,底软内部使用*/
    IPC_CCPU_INT_SRC_ACPU_IFC              ,      /* 远程函数调用,底软内部使用*/
    IPC_CCPU_INT_SRC_MCU_IFC               ,      /* 远程函数调用,底软内部使用*/
    IPC_INT_ARM_SLEEP                      ,      /* 睡眠唤醒使用*/

    /* 定义MCU IPC跨核消息中断源bit位置 */
    IPC_MCU_INT_SRC_ACPU_MSG             = 0,    /* ACPU跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_MSG                ,    /* CCPU跨核消息通知 */
    IPC_MCU_INT_SRC_HIFI_MSG                ,    /* HIFI跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_IPF                ,    /* IPF低功耗 */
    IPC_MCU_INT_SRC_ACPU_PD                 ,    /* acpu power down */
    IPC_MCU_INT_SRC_HIFI_PD                 ,    /* hifi power down */
    IPC_MCU_INT_SRC_HIFI_DDR_VOTE           ,    /* HIFI DDR自刷新投票 */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID ,
    IPC_MCU_INT_SRC_COMMON_END              ,
    /* v7  特有的 ipc 中断 */
    /* ACPU给CCPU发送IPC中断时，需要同时告知给M3 */
    IPC_MCU_INT_SRC_ACPU_DRX                = IPC_MCU_INT_SRC_COMMON_END,
    IPC_MCU_INT_SRC_CCPU_DRX                ,   /* CCPU给ACPU发送IPC中断时，需要同时告知给M3 */
    IPC_MCU_INT_SRC_ICC_PRIVATE             ,   /* m3 icc私有的ipc中断，高性能通道，启独立任务用 */
    IPC_MCU_INT_SRC_DUMP                    ,   /* m3 dump中断，ACORE发送给MCU的IPC中断*/
    IPC_MCU_INT_SRC_HIFI_PU                 ,   /* POWERUP,  HIFI发送给MCU的IPC中断 */
    IPC_MCU_INT_SRC_HIFI_DDR_DFS_QOS        , /* HIFI对DDR调频投票 */
    IPC_MCU_INT_SRC_TEST                    ,   /* for test a\c interact with m3 */
    IPC_MCPU_INT_SRC_ACPU_USB_PME_EN        ,  /* acore向M3通报USB唤醒完成事件 */
    /* 以下3个austin修改，和AP对齐，不能修改 */
	IPC_MCU_INT_SRC_ICC 				= 29,	/* m3 icc公用的ipc中断 */
	IPC_MCU_INT_SRC_CCPU_PD 			= 30,	 /* ccpu power down */
	IPC_MCU_INT_SRC_CCPU_START			= 31,	/* 通知MCU启动CCPU */


    /* v8 特有的ipc 中断 */
    /* HIFI跨核消息通知,远程函数调用,底软内部使用 */
    IPC_MCU_INT_SRC_CCPU_IFC                    = IPC_MCU_INT_SRC_COMMON_END,
    IPC_MCU_INT_SRC_ACPU_IFC                    ,   /* ACPU跨核函数调用通知,底软内部使用 */
    IPC_MCU_INT_SRC_HIFI_IFC                    ,   /* HIFI跨核函数调用通知*/
    IPC_MCU_INT_SRC_ACPU0_PD                    ,   /* acpu0 power down, V8新增 */
    IPC_MCU_INT_SRC_ACPU1_PD                    ,   /* acpu1 power down, V8新增 */
    IPC_MCU_INT_SRC_ACPU2_PD                    ,   /* acpu2 power down, V8新增 */
    IPC_MCU_INT_SRC_ACPU3_PD                    ,   /* acpu3 power down , V8新增*/
    IPC_MCU_INT_SRC_ACPU4_PD                    ,   /* acpu4:cluster1 core0 power down */
    IPC_MCU_INT_SRC_ACPU5_PD                    ,   /* acpu5:cluster1 core1 power down */
    IPC_MCU_INT_SRC_ACPU6_PD                    ,   /* acpu6:cluster1 core2 power down */
    IPC_MCU_INT_SRC_ACPU7_PD                    ,   /* acpu7:cluster1 core3 power down */
    IPC_MCU_INT_SRC_ACPU_HOTPLUG                ,   /* acpu hotplug--no use, V8新增 */
    IPC_MCU_INT_SRC_MCU_AGT                     ,   /* mcu agent */
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_VOTE      ,   /* MP3超低功耗播放使用HARQMEM,HIFI DDR自刷新投票*/
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_EXIT_VOTE ,   /* MP3超低功耗播放使用HARQMEM,HIFI投票DDR退出自刷新*/
    IPC_MCU_INT_SRC_ACPU_DFS                    ,   /*ACPU DFS*/
    
    IPC_MCU_INT_SRC_END                         ,

    /* 定义ACPU IPC跨核消息中断源bit位置 */
    IPC_ACPU_INT_SRC_CCPU_MSG             = 0,   /* CCPU跨核消息通知 */
    IPC_ACPU_INT_SRC_HIFI_MSG             = 1,   /* HIFI跨核消息通知 */
    IPC_ACPU_INT_SRC_MCU_MSG              = 2,   /* ACPU跨核消息通知 */
    IPC_ACPU_INT_SRC_CCPU_NVIM            = 3,   /* 用于NVIM模块C核与A核之间的同步*/
    IPC_INT_DICC_USRDATA                  = 4,   /* 必须与CCPU接收中断号同时修改*/
    IPC_INT_DICC_RELDATA                  = 5,   /* 必须与CCPU接收中断号同时修改*/
    IPC_ACPU_INT_SRC_CCPU_ICC                ,
    IPC_ACPU_INT_SRC_COMMON_END              ,
    /* v7  特有的 ipc 中断 */
    IPC_ACPU_INT_SRC_ICC_PRIVATE          = IPC_ACPU_INT_SRC_COMMON_END,   /* v7r2 icc 私用，CCPU发送给ACPU的IPC中断 */
    IPC_ACPU_SRC_CCPU_DUMP                ,   /* v7r2 可维可测，CCPU 发送给ACPU 的IPC中断 */
    IPC_ACPU_INT_SRC_MCPU                 ,   /* ICC消息, MCU发送给ACPU的 IPC中断 */
    IPC_ACPU_INT_SRC_MCPU_WDT             ,  /* 运行trace时停wdt */
    IPC_ACPU_INT_MCU_SRC_DUMP             ,  /* dump中断?MCU发送给ACPU的IPC中断 */
    IPC_ACPU_INT_SRC_CCPU_RESET_IDLE      ,  /* A/C核在C核单独复位期间核间通信(master in idle)，姚国才 */
    IPC_ACPU_INT_SRC_CCPU_RESET_SUCC      ,  /* A/C核在C核单独复位期间核间通信(ccore reset ok)，姚国才 */

    IPC_ACPU_INT_SRC_CCPU_LOG             ,  /* CCPU发送给ACPU的LOG保存中断 */
    IPC_ACPU_INT_SRC_MCU_FOR_TEST         ,  /* test, m core to acore */
    IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE     ,  /* IPC自动化测试中断使能时使用，后续IPC中断不够使用时考虑删除 */
    IPC_ACPU_INT_SRC_MCPU_USB_PME         ,  /* M3向acore上报USB唤醒事件 */
    IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA,  /* hifi->acore pc voice */
    IPC_ACPU_INT_SRC_CCPU_PM_OM           ,  /* CCPU发给ACPU的PMOM中断,触发写文件, 姚国才 */

    /* v8 特有的ipc 中断 */
    IPC_ACPU_INT_SRC_CCPU_IFC             = IPC_ACPU_INT_SRC_COMMON_END,       /* 底软内部使用*/
    IPC_ACPU_INT_SRC_MCU_IFC              ,   /* 底软内部使用*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH     ,   /* MCU电池放电高温关机IPC中断通知ACPU, 手机内部使用*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_LOW      ,  /* MCU电池放电低温关机IPC中断通知ACPU*/
    IPC_ACPU_INI_SRC_MCU_TELE_MNTN_NOTIFY ,  /* 底软内部使用,可维护可测*/
    IPC_ACPU_INI_SRC_MCU_EXC_REBOOT       ,  /* 底软内部使用,可维护可测*/
    IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT      ,  /* 底软内部CCPU 异常发中断给ACPUfuwei*/
    IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT   ,  /* 底软内部;*RIL通知Cfuwei, C核通过该函数通知A核可以复位*/
    IPC_ACPU_INT_SRC_MCU_DDR_EXC          ,  /* 底软内部,MCU*/

    IPC_ACPU_INT_SRC_END              ,

    /* 定义HIFI IPC跨核消息中断源bit位置 */
    IPC_HIFI_INT_SRC_ACPU_MSG = 0 ,  /* ACPU跨核消息通知 */
    IPC_HIFI_INT_SRC_CCPU_MSG     ,  /* CCPU跨核消息通知 */
    IPC_HIFI_INT_SRC_BBE_MSG      ,  /* TDDSP跨核消息通知 */
    IPC_HIFI_INT_SRC_MCU_MSG      ,
    IPC_HIFI_INT_SRC_COMMON_END   ,
    
    /* v8 特有的ipc 中断 */
    IPC_HIFI_INT_SRC_MCU_WAKE_DDR = IPC_HIFI_INT_SRC_COMMON_END,  /* MCU通知HIFI唤醒DDR */
    IPC_HIFI_INT_SRC_MCU_IFC      ,
    
    IPC_HIFI_INT_SRC_END          ,

    /* 定义BBE16 IPC跨核消息中断源bit位置 */
    IPC_INT_MSP_DSP_OM_MBX = 0 ,   /* 下行ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX     ,   /* 下行ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX     ,   /* 下行ARM->DSP */
    IPC_INT_HIFI_DSP_MBX       ,   /* HIFI->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG ,   /* 邮箱消息，HIFI发送给BBE16的IPC中断 */

    IPC_BBE16_INT_SRC_END  ,


    /* 定义XDSP IPC跨核消息中断源bit位置 */
    IPC_XDSP_INT_SRC_CCPU_1X_WAKE = 0 ,   /* 1X Wake中断 */
    IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE   ,   /* HRPD Wake中断 */
    IPC_XDSP_INT_SRC_CCPU_OM_MBX      ,   /* C核->XDSP */
    IPC_XDSP_INT_SRC_CCPU_PUB_MBX     ,   /* C核->XDSP */

	IPC_XDSP_INT_SRC_END ,   


    /* 仅解决编译问题 */
    IPC_INT_BUTTOM             = 32,
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_MEM          ,
    IPC_SEM_DICC         ,
    IPC_SEM_EMMC         ,
    IPC_SEM_SYNC         , 
    IPC_SEM_SYSCTRL      ,
    IPC_SEM_BBP          ,  /*该值与BBE16镜像绑定，修改需通知BBE16作相应修改*/
    IPC_SEM_RFILE_LOG    ,  /*用于flashless可维可测*/
    IPC_SEM_NVIM         ,
    IPC_SEM_EFUSE        , 
    IPC_SEM_DPDT_CTRL_ANT,  /* 添加mdrv_ipc_spin_trylock时添加 */
    IPC_SEM_BBPMASTER_0  ,
    IPC_SEM_BBPMASTER_1  ,
    IPC_SEM_BBPMASTER_2  ,
    IPC_SEM_BBPMASTER_3  ,
    IPC_SEM_BBPMASTER_5  ,
    IPC_SEM_BBPMASTER_6  ,
    IPC_SEM_BBPMASTER_7  ,
    IPC_SEM_COMMON_END   ,

    /* v7 私有的IPC SEM */
    IPC_SEM_SPI0         = IPC_SEM_COMMON_END,
    IPC_SEM_NV           ,
    IPC_SEM_GPIO         ,
    IPC_SEM_CLK          ,
    IPC_SEM_PMU          ,
    IPC_SEM_MTCMOS       ,
    IPC_SEM_IPF_PWCTRL   ,
    IPC_SEM_PMU_FPGA     , /*调试pmu芯片时使用,回片后不使用*/
    IPC_SEM_NV_CRC       ,
    IPC_SEM_PM_OM_LOG    ,
    IPC_SEM_MDRV_LOCK    ,
    IPC_SEM_CDMA_DRX     , /* C核与XDSP使用 */
    IPC_SEM_GU_SLEEP     ,
    IPC_SEM2_IPC_TEST    , /*IPC自动化测试使用*/

    /* v8 私有的IPC SEM */
    IPC_SEM_ICC          = IPC_SEM_COMMON_END,
    IPC_SEM_NAND         ,
    IPC_SEM_TELE_MNTN    ,
    IPC_SEM_MEDPLL_STATE ,
    IPC_SEM_SMP_CPU0     ,
    IPC_SEM_SMP_CPU1     ,
    IPC_SEM_SMP_CPU2     ,
    IPC_SEM_SMP_CPU3     ,
    IPC_SEM_CPUIDLE      ,   /*CPUIDLE A/M核互斥资源锁*/
    IPC_SEM_BBPPS        ,   /*BBP PS上下电投票*/
    IPC_SEM_HKADC        ,   /*A、M核读取HKADC的互斥锁*/

    IPC_SEM_END          ,

    IPC_SEM_BUTTOM       = 32
} IPC_SEM_ID_E;

#endif


#ifdef __cplusplus
}
#endif

#endif
