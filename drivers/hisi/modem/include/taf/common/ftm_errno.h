/*****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

*****************************************************************************
  文 件 名   : ftm_errno.h
  版 本 号   : V1.0
  作    者   : 沈汉坤/00130424
  生成日期   : 2008年07月07日
  功能描述   : FTM中的错误码值定义，适用于FTM和其它子系统.
  函数列表   : 无
  修改历史   :
  1.日    期 : 2008年07月07日
    作    者 : 沈汉坤/00130424
    修改内容 : 创建文件

*****************************************************************************/

#ifndef __FTM_ERRNO_H__
#define __FTM_ERRNO_H__

#define  ERR_FTM_SUCCESS                (0)
#define  ERR_FTM_WAIT_ASYNC             (1)
#define  ERR_FTM_INVALID_ID             (2)
#define  ERR_FTM_NO_INITILIZATION       (3)
#define  ERR_FTM_NOT_FOUND              (4)
#define  ERR_FTM_FULL                   (7)
#define  ERR_FTM_INSUFFICIENT_BUFFER    (8)
#define  ERR_FTM_CONSUMED               (9)
#define  ERR_FTM_CONTINUE               (10)
#define  ERR_FTM_TOO_SMALL_BUFFER       (11)
#define  ERR_FTM_NOT_FREEE_SPACE        (12)
#define  ERR_FTM_NO_MORE_DATA           (13)
#define  ERR_FTM_MALLOC_FAILUE          (15)
#define  ERR_FTM_NOT_ENOUGH_MEMORY      (16)
#define  ERR_FTM_INVALID_HEAP_ADDR      (17)
#define  ERR_FTM_SHUTDOWN               (18) /* 未能关机*/
#define  ERR_FTM_NOT_CONNECT            (19) /* 未正确连接UE*/
#define  ERR_FTM_BUSY                   (20) /* 系统忙或者使用冲突*/


#define  ERR_FTM_UNAVAILABLE            (50)
#define  ERR_FTM_TIMEOUT                (51)
#define  ERR_FTM_INIT_FAILURE           (52)
#define  ERR_FTM_IO_REGISTER_FAILURE    (53)
#define  ERR_FTM_NO_REGISTER            (54)

#define  ERR_FTM_FLASH_ERASE_ERROR      (100)
#define  ERR_FTM_FLASH_WRITE_ERROR      (101)
#define  ERR_FTM_FLASH_ALIGN_ERROR      (102)             /* sector aligned addresses*/
#define  ERR_FTM_FLASH_PROTECT_ERROR    (103)
#define  ERR_FTM_FLASH_BIN_LOAD_NEED_FIRST_BLOCK    (104) /* while bin file load,req need first block*/
#define  ERR_FTM_DIAG_CMD_SIZE_INVALID              (106)


#define  ERR_FTM_CFG_RAM_SUCCESS         (201)
#define  ERR_FTM_CFG_PART_SUCCESS        (202)
#define  ERR_FTM_CFG_LOG_NOT_ALLOW       (203)
#define  ERR_FTM_DIAG_CYC_CMD_NOT_START  (204)
#define  ERR_FTM_DIAG_MSG_CFG_NOT_SET    (205)
#define  ERR_FTM_QUEUE_FULL              (300)
#define  ERR_FTM_QUEUE_NOT_EXIST         (301)
#define  ERR_FTM_INVALID_TASK_ID         (302)
#define  ERR_FTM_INVALID_TASK_QUEUE      (303)

#define  ERR_FTM_VCOM_WRITE_ERROR        (401)

/* AT错误码，可以和字符串对应*/
/* 该错误码和FTM内部错误码统一定义*/
#define  ERR_FTM_NOT_EXIST               (500) /* 字符串："未实现"   “Undone”*/
#define  ERR_FTM_UNKNOWN                 (501) /* 字符串："未知错误" “unknown error”*/
#define  ERR_FTM_INVALID_PARAMETER       (502) /* 字符串："输入参数非法，包括不在合法范围等错误" "invalid parameters"*/
#define  ERR_FTM_NV_NOT_SUPPORT_ID       (520) /* 字符串："NV不存在""NVIM Not Exist"*/
#define  ERR_FTM_NV_ERROR_READ           (521) /* 字符串："NV读取失败" "Read NVIM Failure"*/
#define  ERR_FTM_NV_NOT_SUPPORT_LENTH    (522) /* 字符串："NV写失败，长度过长""Write Error for Length Overflow"*/
#define  ERR_FTM_NV_BAD_BLOCK            (523) /* 字符串："NV写失败，Flash坏块" "Write Error for Flash Bad Block"*/
#define  ERR_FTM_NV_ERROR_WRITE          (524) /* 字符串："NV写失败，其它错误" "Write Error for Unknown Reason"*/
#define  ERR_FTM_VCTCXO_OVER_HIGH        (525) /* 字符串："设置VCTCXO电压过高" "Higher Voltage"	*/
#define  ERR_FTM_UE_MODE_ERR             (526) /* 字符串："单板模式错误(比如信令模式)"	"UE Mode Error"	*/
#define  ERR_FTM_NOT_SET_CHAN            (527) /* 字符串："没有设置相关信道""Not Set Appointed Channel"	*/
#define  ERR_FTM_OPEN_RFTX_ERROR         (528) /* 字符串："打开发射机失败""Open TX Transmitter Failure"	*/
#define  ERR_FTM_OPEN_RFRX_ERROR         (529) /* 字符串："打开接收机失败""Open RX Transmitter Failure"	*/
#define  ERR_FTM_OPEN_CHAN_ERROR         (530) /* 字符串："通道打开失败""Open Channel Failure"	*/
#define  ERR_FTM_CLOSE_CHAN_ERROR        (531) /* 字符串："通道关闭失败""Close Channel Failure"	*/
#define  ERR_FTM_NOT_SUPPORT             (532) /* 字符串："不支持（如打开通道2的发送通道，DD800项目采用1T2R模式）"	"Not Support"*/
#define  ERR_FTM_INVALID_OP              (533) /* 字符串："非法操作（比如读取特殊NV）""Invalid Operation"	*/
#define  ERR_FTM_ENTER_BAND_ERROR        (534) /* 字符串："输入频段信息无法对应" "Band No Match"	*/
#define  ERR_FTM_SET_CHAN_INFOR_ERROR    (535) /* 字符串："设置信道信息失败" "Set Channel Information Failure"	*/
#define  ERR_FTM_FRE_CHANI_NOTMATCH      (536) /* 字符串："输入频段和信道信息无法组合""Band And Channel Not Combinated"	*/
#define  ERR_FTM_SET_TX_POWER_FAILUE     (537) /* 字符串："设置TX的发射功率失败""Set TX Transmitter Power Error"	*/
#define  ERR_FTM_SET_PA_LEVEL_FAILUE     (538) /* 字符串："设置PA级失败""Set PA Level Failure"	*/
#define  ERR_FTM_NOT_SET_CURRENT_CHAN    (539) /* 字符串："未设置当前信道"	"Not Set Current Channel"*/
#define  ERR_FTM_NOT_ABLETO_RD_APC       (540) /* 字符串："无法读取当前设置的APC值"	"APC Value Can't Be Read"*/
#define  ERR_FTM_SET_APC_ERROR           (541) /* 字符串："设置APC操作失败"	"Write APC Failure"*/
#define  ERR_FTM_RD_APC_ERROR            (542) /* 字符串："读取APC操作失败"	"Read APC Failure"*/
#define  ERR_FTM_SET_LINA_ERROR          (543) /* 字符串："设置LNA失败"	"Set AAGC Failure"*/
#define  ERR_FTM_NOT_OPEN_RXRX           (544) /* 字符串："没有打开接收机"	"RX Transmitter Not Open"*/
#define  ERR_FTM_NOT_OPEN_RXTX           (545) /* 字符串："没有打开发射机"	"TX Transmitter Not Open"*/
#define  ERR_FTM_NO_SIGNAL               (546) /* 字符串："无信号输入或检测不到信号" "No Signal"	*/
#define  ERR_FTM_PHYNUM_LENGTH_ERROR     (547) /* 字符串："物理号长度错误"	"PHY Number Length Error"*/
#define  ERR_FTM_PHYNUM_INVALID          (548) /* 字符串："物理号不合法" "Invalid PHY Number"	*/
#define  ERR_FTM_PHYNUM_TYPE_ERROR       (549) /* 字符串："物理号类型错误""Invalid PHY Type"*/
#define  ERR_FTM_PLATINFOR_NOTABLE_TORD  (550) /* 字符串："无法读取平台信息""Platform Information Can't Be Read"	*/
#define  ERR_FTM_WRT_NOT_UNLOCK          (551) /* 字符串："表示写数据时，数据保护未解锁, 无法操作保护数据"	"Not unlock, write error"*/
#define  ERR_FTM_CALLNUM_OVER20          (552) /* 字符串："输入的号段多于20段"	"Card Number Morethan 20"*/
#define  ERR_FTM_MNC_ENTER_OVERFLOW      (553) /* 字符串："<mnc-digital-num>输入超出范围" "<mnc-digital-num> Enter Error"	*/
#define  ERR_FTM_RD_VER_FAILUE           (554) /* 字符串："版本信息读取失败""Read VERSION Failure"	*//* [false alarm]:alarm */
#define  ERR_FTM_OPERTION_ERROR          (555) /* 字符串："操作失败""Operation Failure"*//* [false alarm]:alarm */
#define  ERR_FTM_PWD_ERR                 (556) /* 字符串: "输入密码错误""Password Error"*//* [false alarm]:alarm */
#define  ERR_FTM_TIME_OUT                (557) /* 字符串: "超时错误" "Overtime"*//* [false alarm]:alarm */
#define  ERR_FTM_NO_MORE_MEMORY	         (558) /* 内存不足 "No Memory"*/
#define  ERR_FTM_SIMM_LOCK               (559) /* 启用了SIMLOCK功能"Sim Lock Active"*/
#define  ERR_FTM_CLOSE_RFTX_ERROR        (560) /* 字符串："关闭发射机失败""Close TX Transmitter Failure"	*/
#define  ERR_FTM_CLOSE_RFRX_ERROR        (561) /* 字符串："关闭接收机失败""Close RX Transmitter Failure"*/
#define  ERR_FTM_NV_DATA_INVALID         (562) /* 字符串："读取的NV项内容非法""NV DATA INVALID"*/
#define  ERR_FTM_AT_CHANNEL_CLOSE        (563) /* DIAG/MUX的AT通道关闭*/
#define  ERR_FTM_AT_CHANNEL_BUSY         (564) /* DIAG/MUX的AT通道BUSY*/
#define  ERR_FTM_OS_MSG_BODY_NULL        (565) /* 接收到的消息体为NULL(本应不为NULL)*/
#define  ERR_FTM_AT_ACK_URC_INVALID      (566) /* AT ACK or URC invalid, such as size is zero*/
#define  ERR_FTM_PS_START_FAILURE        (567) /* START PS FAILURE*/
#define  ERR_FTM_PS_STOP_FAILURE         (568) /* STOP PS FAILURE*/
#define  ERR_FTM_PS_SET_APN_FAILURE      (569) /* SET APN FAILURE*/
#define  ERR_FTM_PS_SET_AUTH_FAILURE     (570) /* SET AUTH FAILURE*/
#define  ERR_FTM_PS_SET_BEARER_TYPE_FAILURE      (571) /* SET BEARER TYPE*/


#define  ERR_FTM_BNADSW_ERROR            (572) /* 字符串: "BAND切换错误"*/
#define	 ERR_FTM_TXWAVE_ERROR	         (573) /* 字符串: "发射波形类型错误"*/
#define  ERR_FTM_AT_FW_TABLEID_EXIST     (574) /* client id 已存在*/
#define  ERR_FTM_START_TIMER_FAIL           (575)

/* add simm error number (周罗俊/67193/2009-08-14)*/
/* 600 ~ 699 should be used by simm*/
#define  ERR_FTM_SIMM_NOT_INIT             (601)          /*SIMM未初始化*/
#define  ERR_FTM_SIMM_WRONG_PARA           (602)          /*因为参数错误，函数执行失败*/
#define  ERR_FTM_SIMM_NOAPP                (603)          /*因为没有可用应用，函数执行失败*/
#define  ERR_FTM_SIMM_NO_MEM               (604)          /*因为初始化没有完成，函数执行失败*/
#define  ERR_FTM_SIMM_ALLOCMEM_FAILED      (605)          /*因为内存分配失败，函数执行失败*/
#define  ERR_FTM_SIMM_SENDMSG_FAILED       (606)          /*因为消息发送失败，函数执行失败*/
#define  ERR_FTM_SIMM_TIMEOUT              (607)          /*超时,函数执行失败*/
#define  ERR_FTM_SIMM_NO_CARD              (608)          /*卡不在位失败*/
#define  ERR_FTM_SIMM_SEM                  (609)          /*任务队列信号量错误*/

#define  ERR_FTM_SIMM_QUEUE_FULL           (621)          /*队列已满*/
#define  ERR_FTM_SIMM_QUEUE_EMPTY          (622)          /*队列为空*/
#define  ERR_FTM_SIMM_CMD_EXCEPTION        (623)          /*命令处理失败*/
#define  ERR_FTM_SIMM_CMD_TIMEOUT          (624)          /*命令处理超时*/

#define  ERR_FTM_SIMM_DF_FCP_FAILED        (630)          /*DF文件解析失败*/
#define  ERR_FTM_SIMM_PIDO_FAILED          (631)          /*PIDO解析失败*/
#define  ERR_FTM_SIMM_FCP_FAILED           (632)          /*EF文件解析失败*/
#define  ERR_FTM_SIMM_EFDIR_FAILED         (632)          /*EF文件解析失败*/

#define  ERR_FTM_SIMM_NEED_PIN             (640)          /*需要PIN码*/
#define  ERR_FTM_SIMM_NEED_PIN2            (641)          /*需要PIN2码*/
#define  ERR_FTM_SIMM_NEED_PUK             (642)          /*需要PUK码*/
#define  ERR_FTM_SIMM_NEED_PUK2            (643)          /*需要PUK2码*/

#define  ERR_FTM_SIMM_AUTH_MAC_FAILURE     (645)          /*鉴权MAC错误*/
#define  ERR_FTM_SIMM_AUTH_SYNC_FAILURE    (646)          /*鉴权SYNC错误*/
#define  ERR_FTM_SIMM_AUTH_OTHER_FAILURE   (647)          /*其他鉴权错误*/
#define  ERR_FTM_SIMM_OTHER_FAILURE        (648)          /*其他鉴权错误*/


#define  ERR_FTM_QUEUE_NOT_OPEN          (1000)
#define  ERR_FTM_QUEUE_UNAVAILABLE       (1001)
#define  ERR_FTM_QUEUE_SHUTDOWN          (1002)

#define  ERR_FTM_NV_ITEM_IS_EMPTY        (1100)
#define  ERR_FTM_NV_FLASH_FULL           (1103)

/* 对应BSP错误码*/
#define  ERR_FTM_NV_GOOD_BLOCK           (1105)
#define  ERR_FTM_NV_ERROR_INIT           (1106)
#define  ERR_FTM_NV_ERROR_ARGS           (1107)
#define  ERR_FTM_NV_ERROR_MALLOC         (1108)
#define  ERR_FTM_NV_ERROR_ERASE          (1111)

/* 升级错误码*/
#define  ERR_FTM_SUM_ONLY_NVCOPY_OK      (1200)
#define  ERR_FTM_SUM_BACK_OK             (1201) /* 回退成功 */
#define  ERR_FTM_SUM_BACK_FAIL           (1202) /* 回退失败 */
#define  ERR_FTM_SUM_BACK_NO_VERSION     (1203) /* 没有版本可回退 */
#define  ERR_FTM_SUM_UPDATE_RESET_FAILUE (1204)

#define  ERR_FTM_NVIM_BACKUP_FILE_FAIL    (2001)
#define  ERR_FTM_NVIM_BACKUP_DATA_FAIL    (2002)
#define  ERR_FTM_NVIM_WRITE_FILE_FAIL     (2003)
#define  ERR_FTM_NVIM_UPDATA_DATA_FAIL    (2004)
#define  ERR_FTM_NVIM_UPDATA_FILE_FAIL    (2005)
#define  ERR_FTM_NVIM_SECTION_NOT_SUPPORT_UPDATA    2006
#define  ERR_FTM_NVIM_NOT_SUPPORT_WRITE    2007
#define  ERR_FTM_NVIM_NEED_BACK_ERR             2008

#define LNVM_OPEN_FILE_ERROR      (2010)
#define	LNVM_READ_FILE_ERROR      (2011)
#define	LNVM_FTELL_FILE_ERROR     (2012)
#define	LNVM_WRITE_FILE_ERROR     (2013)
#define	LNVM_SEEK_FILE_ERROR      (2014)
#define	LNVM_REMOVE_FILE_ERROR    (2015)
#define	LNVM_CLOSE_FILE_ERROR     (2016)

#define FTM_SD_OPEN_FILE_ERROR      (2200)
#define	FTM_SD_WRITE_FILE_ERROR     (2201)
#define	FTM_SD_SEEK_FILE_ERROR      (2202)
#define	FTM_SD_GET_STATE_ERROR      (2203)
#define FTM_SD_CREAT_DIR_ERROR      (2204)


/*CDM ERR NO. START*/

#define ERR_FTM_CDM_BEGIN               (0x3000)

#define ERR_FTM_CDM_ACPU_CODER_SRC_FAIL (ERR_FTM_CDM_BEGIN + 1)

#define ERR_FTM_CDM_END                 (0x3100)
/*CDM ERR NO. END*/

/* DIAG给工具软件回复的错误码 0x4000-0x4fff */

#define  ERR_FTM_DIAG_ERROR_BEGIN               (0x4000)
#define  ERR_FTM_DIAG_ACORE_ERROR               (ERR_FTM_DIAG_ERROR_BEGIN + 1)  /* A核处理失败 */
#define  ERR_FTM_DIAG_CCORE_ERROR               (ERR_FTM_DIAG_ERROR_BEGIN + 2)  /* C核处理失败 */
#define  ERR_FTM_DIAG_INVALID_CMD               (ERR_FTM_DIAG_ERROR_BEGIN + 3)  /* 不能识别的诊断命令 */


#define  ERR_FTM_FAILURE                (0XFFFFFFFFU)
#define  ERR_FTM_SYSTEM                 (0XFFFFFFFFU)

/* The definition of error number which result in reboot */
enum
{
    FTM_REBOOT_FTM_ERR  = 0xb0000000,
    FTM_REBOOT_ID_BUTT  = 0xbfffffff
};



#endif /* __FTM_ERRNO_H__ */
