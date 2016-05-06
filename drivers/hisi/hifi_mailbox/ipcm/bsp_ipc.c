
#include <linux/module.h>
#include <asm/io.h>
#include <asm/string.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <linux/delay.h>

#include <linux/slab.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_rproc.h>


#include "bsp_drv_ipc.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define USE_HIFI_IPC
/*lint -e750*/
BSP_IPC_ENTRY   stIpcIntTable[INTSRC_NUM];
static IPC_DEV_S    g_stIpcDev = {0};
BSP_U32         g_CoreNum;

struct semaphore    g_semIpcTask[INTSRC_NUM];
IPC_DEBUG_E     g_stIpc_debug = {0};

/* base address of ipc registers */
void __iomem *ipc_base = NULL;
spinlock_t g_ipc_int_lock = __SPIN_LOCK_UNLOCKED("ipc");

#define USE_HISI_MAILBOX

/*************************************k3 ipc******************************************/
#define BIT_ENABLE(n)                           (1 << (n))
#define BYTE_REF(address) (* ((unsigned char volatile *) (address)))
#define HALFWORD_REF(address) (* ((unsigned short volatile *) (address)))
#define WORD_REF(address) (* ((unsigned int volatile *) (address)))
#define WORD_PTR(address) (* ((unsigned int volatile **) (address)))
#define BYTE(address)   volatile unsigned char __attribute__((section(".ARM.__at_"address)))
#define HALFWORD(address)   volatile unsigned short __attribute__((section(".ARM.__at_"address)))
#define WORD(address)   volatile unsigned int __attribute__((section(".ARM.__at_"address)))

#define K3_IPC_MODE_ACK                         (7)
#define K3_IPC_MODE_IDLE                        (4)
#define K3_IPC_MODE_AUTOACK                 (0)

/*************************************hifi系统ipc******************************************/
#if  defined(CONFIG_HIFI_IPC_3650) || defined(CONFIG_HIFI_IPC_6250) || defined(CONFIG_HIFI_IPC_3660)
#define K3_SYS_IPC_BASE_ADDR_S      (unsigned long)(0xe896a000)
#define K3_SYS_IPC_BASE_ADDR_NS    (unsigned long)(0xe896b000)
#endif
#define K3_SYS_IPC_REG_SIZE     (0xA00)

#define K3_IPC_LOCK(base)                          WORD_REF(base + 0xA00)
#define K3_IPC_SOURCE(base, box)           WORD_REF(base + ((box) * 64))
#define K3_IPC_DEST(base, box)             WORD_REF(base + ((box) * 64) + 0x04)
#define K3_IPC_DCLR(base, box)             WORD_REF(base + ((box) * 64) + 0x08)
#define K3_IPC_DSTATUS(base, box)          WORD_REF(base + ((box) * 64) + 0x0c)
#define K3_IPC_MODE(base, box)          WORD_REF(base + ((box) * 64) + 0x10)
#define K3_IPC_IMASK(base, box)        WORD_REF(base + ((box) * 64) + 0x14)
#define K3_IPC_ICLR(base, box)             WORD_REF(base + ((box) * 64) + 0x18)
#define K3_IPC_SEND(base, box)                WORD_REF(base + ((box) * 64) + 0x1c)
#define K3_IPC_DATA(base, box, num)       WORD_REF(base + ((box) * 64) + 0x20 + ((num) *4))
#define K3_IPC_CPUIMST(base, core)         WORD_REF(base + 0x800 + ((core) * 8))
#define K3_IPC_CPUIRST(base, core)         WORD_REF(base + 0x804 + ((core) * 8))

#define K3_SYS_IPC_CORE_LIT                        (0)
#define K3_SYS_IPC_CORE_BIG                          (1)
#define K3_SYS_IPC_CORE_IOM3                      (2)
#define K3_SYS_IPC_CORE_LPM3                      (3)
#define K3_SYS_IPC_CORE_HIFI                        (4)

	/*************************************hifi内部ipc******************************************/
#define K3_HIFI_IPC_BASE_ADDR      (unsigned long)(0xE804C000)
#define K3_HIFI_IPC_REG_SIZE        (0x1000)

#define K3_ASP_CFG_CTRLDIS(base)                       WORD_REF(base + 0x04)
#define K3_ASP_CFG_GATE_EN(base)                       WORD_REF(base + 0x0c)

enum {
    /*hifi内部的ipc目的核ap、lpm3、iom3都是对应的第0比特*/
    K3_HIFI_IPC_CORE_AP_LPM3_IOM3 = 0,
    K3_HIFI_IPC_CORE_MODEM_A9 = 1,
    K3_HIFI_IPC_CORE_MODEM_BBE = 2,
    K3_HIFI_IPC_CORE_HIFI = 3,
    K3_HIFI_IPC_CORE_IOM3 = 5,
    K3_HIFI_IPC_CORE_AP = 6,
    K3_HIFI_IPC_CORE_LPM3 = 8,
};

typedef enum {
    K3_SEC_SYS_IPC = 0,
    K3_UNSEC_SYS_IPC,
    K3_HIFI_IPC,
} K3_IPC;

typedef struct {
	/*使用系统ipc还是audio ipc*/
	K3_IPC ipcMode;
	/*映射后的ipc基址*/
	void __iomem *ipcBase;
	/*邮箱号*/
	int mailBoxNum;
	/*中断号*/
	int intNum;
	/*源核编号*/
	int sourceCore;
	/*目标核编号*/
	int destCore;
} K3_IPC_CONFIG;

enum {
    K3_IPC_CORE_IS_SEND = 0,
    K3_IPC_CORE_IS_RECEIVE,
    K3_IPC_CORE_IS_UNKNOEN,
};

/*每个核应该有两个结构体，收发各一个*/
static K3_IPC_CONFIG k3IpcConfig[K3_IPC_CORE_IS_UNKNOEN] = {
	/*本核作为send ipc方*/
	{
		K3_UNSEC_SYS_IPC,
		NULL,
		18,
		220,
		K3_SYS_IPC_CORE_LIT,
		K3_SYS_IPC_CORE_HIFI
	},

/*本核作为rec ipc方*/
#ifdef USE_HIFI_IPC
	{
		K3_HIFI_IPC,
		NULL,
		0,
		239,
		K3_HIFI_IPC_CORE_HIFI,
		K3_HIFI_IPC_CORE_AP_LPM3_IOM3
	}
#else
	/*本核作为rec ipc方*/
	{
		K3_UNSEC_SYS_IPC,
		NULL,
		2,
		227,
		K3_SYS_IPC_CORE_HIFI,
		K3_SYS_IPC_CORE_BIG
	}
#endif
};


#ifdef USE_HIFI_IPC
static irqreturn_t DRV_k3IpcIntHandler_ipc(int irq, void *dev_id);
struct hisi_mbox *hifi_tx_mbox;

#else
static int DRV_k3IpcIntHandler_ipc(struct notifier_block *nb, unsigned long len, void *msg);
struct hisi_mbox *hifi_tx_mbox;
struct notifier_block rx_nb;
#endif

#ifdef USE_HISI_MAILBOX
#define MAX_SEND_IPC_TRY    3


static int hisi_hifi_mbox_init(void)
{
	int ret = 0, rproc_id = 0;

#ifdef USE_HIFI_IPC
#else
	rx_nb.next = NULL;
	rx_nb.notifier_call = DRV_k3IpcIntHandler_ipc;
#if  defined(CONFIG_HIFI_IPC_3650) || defined(CONFIG_HIFI_IPC_6250) || defined(CONFIG_HIFI_IPC_3660)
	rproc_id = HISI_RPROC_HIFI_MBX2;
#endif	
    	/* register the rx notify callback */
	ret = RPROC_MONITOR_REGISTER(rproc_id, &rx_nb);
	if (ret)
		pr_info("%s:RPROC_MONITOR_REGISTER failed", __func__);
#endif

	return ret;
}

/*
static void hisi_hifi_mbox_exit(void)
{
    if (hifi_mbox)
        hisi_mbox_put(&hifi_mbox);
}
*/
#else
static irqreturn_t DRV_k3IpcIntHandler_ack(int irq, void *dev_id)
{
	BSP_S32 retval = IRQ_HANDLED;
	BSP_U32 u32IntStat = 0;

	int myRole = K3_IPC_CORE_IS_SEND;
	BSP_U32 mailBoxNum = k3IpcConfig[myRole].mailBoxNum;
	BSP_U32 source = k3IpcConfig[myRole].sourceCore;
	void __iomem *ipcBase = k3IpcConfig[myRole].ipcBase;

	/*读取A15的中断状态*/
	u32IntStat = K3_IPC_CPUIMST(ipcBase, source);

	/*应答中断只关心A15发给hifi通信的18号邮箱*/
	if (u32IntStat & BIT_ENABLE(mailBoxNum)) {
		/*如果此邮箱收到应答中断，释放邮箱*/
		if (K3_IPC_MODE(ipcBase, mailBoxNum) & BIT_ENABLE(K3_IPC_MODE_ACK)) {
			printk("func:%s: Receive ack int\n", __func__);

			K3_IPC_SOURCE(ipcBase, mailBoxNum) = BIT_ENABLE(source);
		}
		/*清中断*/
		K3_IPC_DCLR(ipcBase, mailBoxNum) = BIT_ENABLE(mailBoxNum);
	}

	return (irqreturn_t)IRQ_RETVAL(retval);
}

#endif


/*****************************************************************************
* 函 数 名  : DRV_IPCIntInit
*
* 功能描述  : IPC模块初始化
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  : 2009年3月5日   wangjing  creat
*****************************************************************************/
BSP_S32 DRV_IPCIntInit(void)
{
#ifdef USE_HIFI_IPC
	BSP_S32 ret = 0;
#endif

	int myRole = 0;

	printk(KERN_ERR "DRV_IPCIntInit begin.\n");

	if (BSP_TRUE == g_stIpcDev.bInit) {
		return BSP_OK;
	}

	printk(KERN_ERR "DRV_IPCIntInit line = %d\n", __LINE__);

	g_CoreNum = IPC_CORE_ACPU;

	memset((void*)stIpcIntTable, 0x0, (INTSRC_NUM * sizeof(BSP_IPC_ENTRY) ));

	/************************************发送方****************************************/
	myRole = K3_IPC_CORE_IS_SEND;
	if (K3_UNSEC_SYS_IPC == k3IpcConfig[myRole].ipcMode) {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_SYS_IPC_BASE_ADDR_NS, K3_SYS_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 unsec sys ipc ioremap error.\n", __LINE__);
			return -1;
		}
	} else if (K3_SEC_SYS_IPC == k3IpcConfig[myRole].ipcMode) {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_SYS_IPC_BASE_ADDR_S, K3_SYS_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 sec sys ipc ioremap error.\n", __LINE__);
			return -1;
		}
	} else {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_HIFI_IPC_BASE_ADDR, K3_HIFI_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 hifi ipc ioremap error.\n", __LINE__);
			return -1;
		}
	}

	/*寄存器解锁*/
	K3_IPC_LOCK(k3IpcConfig[myRole].ipcBase) = 0x1ACCE551;
	/************************************end****************************************/

	/************************************接收方****************************************/
	myRole = K3_IPC_CORE_IS_RECEIVE;
	if (K3_UNSEC_SYS_IPC == k3IpcConfig[myRole].ipcMode) {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_SYS_IPC_BASE_ADDR_NS, K3_SYS_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 unsec sys ipc ioremap error.\n", __LINE__);
			return -1;
		}
	} else if(K3_SEC_SYS_IPC == k3IpcConfig[myRole].ipcMode) {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_SYS_IPC_BASE_ADDR_S, K3_SYS_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 sec sys ipc ioremap error.\n", __LINE__);
			return -1;
		}
	} else {
		k3IpcConfig[myRole].ipcBase = ioremap(K3_HIFI_IPC_BASE_ADDR, K3_HIFI_IPC_REG_SIZE);
		if (!k3IpcConfig[myRole].ipcBase) {
			printk(KERN_ERR "line %d :k3 hifi ipc ioremap error.\n", __LINE__);
			return -1;
		}
	}
	/*寄存器解锁*/
	K3_IPC_LOCK(k3IpcConfig[myRole].ipcBase) = 0x1ACCE551;
	/************************************end****************************************/
#ifdef USE_HIFI_IPC
	/*挂接安全模式中断处理程序*/
	ret = request_irq(k3IpcConfig[K3_IPC_CORE_IS_RECEIVE].intNum,
	                  DRV_k3IpcIntHandler_ipc, 0, "k3IpcIntHandler_ipc", NULL);
	if (ret ) {
		printk(KERN_ERR "BSP_DRV_IPCIntInit: Unable to register ipc irq ret=%d.\n", ret);
		return BSP_ERROR;
	}
#endif
#ifdef USE_HISI_MAILBOX
	hisi_hifi_mbox_init();
#else
	ret = request_irq(k3IpcConfig[K3_IPC_CORE_IS_SEND].intNum,
	                  DRV_k3IpcIntHandler_ack, 0, "k3IpcIntHandler_ack", NULL);
	if (ret ) {
		printk(KERN_ERR "BSP_DRV_IPCIntInit: Unable to register ipc irq ret=%d.\n", ret);
		return BSP_ERROR;
	}
	printk(KERN_ERR "BSP_DRV_IPCIntInit line = %d\n", __LINE__);
#endif

	/*挂接非安全模式中断处理程序*/
	g_stIpcDev.bInit = BSP_TRUE;

	printk(KERN_ERR "BSP_DRV_IPCIntInit end.\n");


	return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : IPC_IntEnable
*
* 功能描述  : 使能某个中断
*
* 输入参数  :   IPC_INT_CORE_E enCoreNum 要使能中断的core
                BSP_U32 ulLvl 要使能的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  : 2011年4月11日 wangjing creat
*****************************************************************************/
BSP_S32 IPC_IntEnable (IPC_INT_LEV_E ulLvl)
{
	/*参数检查*/
	IPC_CHECK_PARA(ulLvl);

	return BSP_OK;
}


/*****************************************************************************
 * 函 数 名  : BSP_INT_Disable
 *
 * 功能描述  : 去使能某个中断
 *
 * 输入参数  : IPC_INT_CORE_E enCoreNum 要使能中断的core
                BSP_U32 ulLvl 要使能的中断号，取值范围0～31
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 * 修改记录  : 2011年4月11日 wangjing creat
 *****************************************************************************/
BSP_S32 IPC_IntDisable (IPC_INT_LEV_E ulLvl)
{
	/*参数检查*/
	IPC_CHECK_PARA(ulLvl);

	return BSP_OK;
}

/*****************************************************************************
 * 函 数 名  : IPC_IntConnect
 *
 * 功能描述  : 注册某个中断
 *
 * 输入参数  : IPC_INT_CORE_E enCoreNum 要使能中断的core
               BSP_U32 ulLvl 要使能的中断号，取值范围0～31
               VOIDFUNCPTR routine 中断服务程序
 *             BSP_U32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 * 修改记录  : 2011年4月11日 wangjing creat
 *****************************************************************************/
BSP_S32 IPC_IntConnect  (IPC_INT_LEV_E ulLvl, VOIDFUNCPTR routine, BSP_U32 parameter)
{

	unsigned long flag = 0;

	/*参数检查*/
	IPC_CHECK_PARA(ulLvl);

	spin_lock_irqsave(&g_ipc_int_lock, flag);
	stIpcIntTable[ulLvl].routine = routine;
	stIpcIntTable[ulLvl].arg = parameter;
	spin_unlock_irqrestore(&g_ipc_int_lock, flag);

	return BSP_OK;
}

/*****************************************************************************
 * 函 数 名  : IPC_IntDisonnect
 *
 * 功能描述  : 取消注册某个中断
 *
 * 输入参数  :
 *              BSP_U32 ulLvl 要使能的中断号，取值范围0～31
 *              VOIDFUNCPTR routine 中断服务程序
 *             BSP_U32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 * 修改记录  : 2011年4月11日 wangjing creat
 *****************************************************************************/
 BSP_S32 IPC_IntDisonnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter)
 {
	unsigned long flag = 0;

	/*参数检查*/
	IPC_CHECK_PARA(ulLvl);

	spin_lock_irqsave(&g_ipc_int_lock, flag);
	stIpcIntTable[ulLvl].routine = NULL;
	stIpcIntTable[ulLvl].arg = 0;
	spin_unlock_irqrestore(&g_ipc_int_lock, flag);

	return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : BSP_DRV_k3IpcIntHandler_S
*
* 功能描述  : k3的IPC安全模式下中断处理函数
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  : 2011年4月11日 wangjing creat
*****************************************************************************/
#ifdef USE_HIFI_IPC
static irqreturn_t DRV_k3IpcIntHandler_ipc(int irq, void *dev_id)
{
	BSP_S32 retval = IRQ_HANDLED;
	BSP_U32 newLevel = 0;
	BSP_U32 u32IntStat = 0;

	int myRole = K3_IPC_CORE_IS_RECEIVE;
	BSP_U32 mailBoxNum = k3IpcConfig[myRole].mailBoxNum;
	BSP_U32 dest = k3IpcConfig[myRole].destCore;
	void __iomem *ipcBase = k3IpcConfig[myRole].ipcBase;

	/*读取AP的中断状态*/
	u32IntStat = K3_IPC_CPUIRST(ipcBase, dest);

	printk("func:%s: destCore = %d intStatus = %d BIT_ENABLE = %d\n", __func__, dest, u32IntStat, BIT_ENABLE(mailBoxNum));

	/*IPC只关心hifi发给AP的0号邮箱*/
	if (u32IntStat & BIT_ENABLE(mailBoxNum)) {
		/*读取0号邮箱的数据寄存器，获取目标核和usage*/
		newLevel = K3_IPC_DATA(ipcBase, mailBoxNum, 0);

		printk("func:%s: newLevel = %d\n", __func__,  newLevel);

		/*清中断同时hifi侧产生应答中断*/
		K3_IPC_ICLR(ipcBase, mailBoxNum) = BIT_ENABLE(dest);

		/*调用注册的中断处理函数*/
		if (newLevel < INTSRC_NUM) {
			g_stIpc_debug.u32IntHandleTimes[newLevel]++;

			if (NULL != stIpcIntTable[newLevel].routine) {
				stIpcIntTable[newLevel].routine(stIpcIntTable[newLevel].arg);
			}
		}
	}

	return (irqreturn_t)IRQ_RETVAL(retval);
}
#else
static int DRV_k3IpcIntHandler_ipc(struct notifier_block *nb, unsigned long len, void *msg)
{
	BSP_U32 newLevel = 0;
	mbox_msg_t *_msg = (mbox_msg_t *)msg;

	newLevel = _msg[0];

	/*调用注册的中断处理函数*/
	if (newLevel < INTSRC_NUM) {
		g_stIpc_debug.u32IntHandleTimes[newLevel]++;

		if (NULL != stIpcIntTable[newLevel].routine) {
			stIpcIntTable[newLevel].routine(stIpcIntTable[newLevel].arg);
		}
	}

	return 0;
}
#endif

/*****************************************************************************
* 函 数 名  : IPC_IntSend
*
* 功能描述  : 发送中断
*
* 输入参数  :
                IPC_INT_CORE_E enDstore 要接收中断的core
                BSP_U32 ulLvl 要发送的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  : 2011年4月11日 wangjing creat
*****************************************************************************/
BSP_S32 IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	int myRole = K3_IPC_CORE_IS_SEND;
	BSP_U32 source = k3IpcConfig[myRole].sourceCore;

#ifdef USE_HISI_MAILBOX
	BSP_U32 ipcMsg[2];
    int ret = 0, rproc_id = 0;
#else
	BSP_U32 mailBoxNum = k3IpcConfig[myRole].mailBoxNum;
	BSP_U32 dest = k3IpcConfig[myRole].destCore;
	void __iomem *ipcBase = k3IpcConfig[myRole].ipcBase;
#endif

	/*参数检查*/
	IPC_CHECK_PARA(ulLvl);

	/*如果是跟hifi通信，使用k3自己的sys ipc，ulLvl使用数据寄存器实现*/
	if (IPC_CORE_HiFi == enDstCore) {
#ifdef USE_HISI_MAILBOX
		ipcMsg[0] = (source << 24) | (ulLvl << 8);
#if 0	//k3 delete  ipc消息格式变化，仅使用第一个数据寄存器
		ipcMsg[1] = ulLvl;
#endif

#if defined(CONFIG_HIFI_IPC_3650) || defined(CONFIG_HIFI_IPC_6250) || defined(CONFIG_HIFI_IPC_3660)
	rproc_id = HISI_RPROC_HIFI_MBX18;
#endif
		ret = RPROC_ASYNC_SEND(rproc_id, (mbox_msg_t *)ipcMsg, 2);
		if(ret)
		  {
		        printk(" %s , line %d, send error\n", __func__, __LINE__);
		  }
#else
		/*判断邮箱是否空闲*/
		while(0 == (K3_IPC_MODE(ipcBase, mailBoxNum) & BIT_ENABLE(K3_IPC_MODE_IDLE))) {
			printk("func:%s: mailbox is busy mode = 0x%x\n", __func__, K3_IPC_MODE(ipcBase, mailBoxNum));
		}

		K3_IPC_SOURCE(ipcBase, mailBoxNum) = BIT_ENABLE(source);
		K3_IPC_DEST(ipcBase, mailBoxNum) = BIT_ENABLE(dest);

		/*快速邮箱目的为hifi，无需配置*/

		/*屏蔽其他*/
		K3_IPC_IMASK(ipcBase, mailBoxNum) = ~(BIT_ENABLE(source)|BIT_ENABLE(dest));

		/*自动应答*/
		K3_IPC_MODE(ipcBase, mailBoxNum) = BIT_ENABLE(K3_IPC_MODE_AUTOACK);

		/*设置数据寄存器*/
		K3_IPC_DATA(ipcBase, mailBoxNum, 0) = source;
		K3_IPC_DATA(ipcBase, mailBoxNum, 1) = ulLvl;

		/*配置发送寄存器*/
		K3_IPC_SEND(ipcBase, mailBoxNum) = BIT_ENABLE(source);

#endif
	} else {
		/*写原始中断寄存器,产生中断*/
		BSP_RegWr(BSP_IPC_CPU_RAW_INT(enDstCore), 1 << ulLvl);
	}

	g_stIpc_debug.u32RecvIntCore = enDstCore;
	g_stIpc_debug.u32IntSendTimes[ulLvl]++;

	return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : BSP_IPC_SpinLock
*
* 功能描述  : 查询等待获取信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  : 2011年4月11日 wangjing creat
*****************************************************************************/
void BSP_IPC_SpinLock (unsigned int u32SignalNum)
{
	unsigned int u32HsCtrl;

	if(u32SignalNum >= INTSRC_NUM)
	{
		printk("BSP_IPC_SpinLock  Parameter error, line:%d\n", __LINE__);
		return;
	}
	for(;;)
	{
		u32HsCtrl = BSP_RegRd(BSP_IPC_HS_CTRL(g_CoreNum, u32SignalNum));
		if (0 == u32HsCtrl)
		{
			break;
		}
	}
}

/*****************************************************************************
* 函 数 名  : BSP_IPC_SpinUnLock
*
* 功能描述  : 释放信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  : 2011年4月11日 wangjing creat
*****************************************************************************/
void BSP_IPC_SpinUnLock (unsigned int u32SignalNum)
{
	if(u32SignalNum >= INTSRC_NUM)
	{
		printk("BSP_IPC_SpinUnLock  Parameter error, line:%d\n", __LINE__);
		return;
	}
	/*将信号量请求寄存器清0*/
	BSP_RegWr(BSP_IPC_HS_CTRL(g_CoreNum, u32SignalNum), 0);
}

EXPORT_SYMBOL(IPC_IntEnable);
EXPORT_SYMBOL(IPC_IntDisable);
EXPORT_SYMBOL(IPC_IntConnect);
EXPORT_SYMBOL(IPC_IntSend);

#ifdef __cplusplus
}
#endif

