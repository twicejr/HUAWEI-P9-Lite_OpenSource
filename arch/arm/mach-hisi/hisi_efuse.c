/*
  * hisilicon efuse driver, hisi_efuse.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/smp.h>
#include "hisi_efuse.h"
#include <linux/regulator/consumer.h>

#ifdef CONFIG_TZDRIVER
#include <teek_client_api.h>
#include <teek_client_id.h>
#endif

#define EFUSE_DEV_NAME "efuse"

struct efuse_data{
	struct regulator_bulk_data regu_burning;
};

static struct efuse_data g_efuse_data;

static void __iomem *SCTRL_BASE = NULL;
static void __iomem *PMURTC_BASE = NULL;
static void __iomem *EFC_BASE = NULL;

#ifndef CONFIG_TZDRIVER

#define EFUSEC_CFG(r)			(r+0x0)
#define EFUSEC_PG_EN_MASK		(1<<0)
#define EFUSEC_PRE_PG_MASK		(1<<1)
#define EFUSEC_RD_EN_MASK		(1<<2)
#define EFUSEC_AIB_SIG_SELN_MASK	(1<<3)
#define EFUSEC_RREN_MASK		(1<<4)
#define EFUSEC_PD_EN_MASK		(1<<5)
#define EFUSEC_MR_EN_MASK		(1<<6)

#define EFUSEC_STATUS(r)		(r+0x04)
#define EFUSEC_PG_STATUS_MASK		(1<<0)
#define EFUSEC_RD_STATUS_MASK		(1<<1)
#define EFUSEC_PGENAB_STATUS_MASK	(1<<2)
#define EFUSEC_RD_ERROR_MASK		(1<<3)
#define EFUSEC_PD_STATUS_MASK		(1<<4)

#define EFUSEC_GROUP(r)		(r+0x08)
#define EFUSEC_GROUP_MASK		((1<<6)-1)

#define EFUSEC_PG_VALUE(r)		(r+0x0C)
#define EFUSEC_COUNT(r)		(r+0x10)
#define EFUSE_COUNT_MASK		((1<<8)-1)

#define EFUSEC_PGM_COUNT(r)		(r+0x14)
#define EFUSE_PGM_COUNT_MASK		((1<<16)-1)

#define EFUSEC_DATA(r)			(r+0x18)
#define EFUSEC_HW_CFG(r)		(r+0x1C)

#define EFUSEC_PG_EN			(1<<0)
#define EFUSEC_PRE_PG			(1<<1)
#define EFUSEC_RD_EN			(1<<2)
#define EFUSEC_APB_SIG_SEL		(1<<3)
#define EFUSEC_RR_EN			(1<<4)
#define EFUSEC_PD_EN			(1<<5)
#define EFUSEC_MR_EN			(1<<6)

#define EFUSEC_APB_PGM_DISABLE_MASK	(1<<0)

#define EFUSE_OP_TIMEOUT_COUNT	0x10
#define EFUSE_OP_TIMEOUT		50

#define SCPERCTRL0(r)			(r+0x200)
#define SCPERCTRL0_REMAP_DIS		0x0C9B
#define SCPERCTRL0_REMAP_EN		0x10C9B
#define SCEFUSECTRL(r)			(r+0x83C)
#define SYS_EFUSE_PAD_SEL		0x0
#define SYS_EFUSE_SOFT_SEL		0x1

#define SCPEREN1(r)			(r+0x030)
#define SCPERDIS1(r)			(r+0x034)
#define GT_PCLK_EFUSEC			(0x01UL<<30)


/* 烧写时序要求, hi3630 asic版本不能用默认值
*  (EFUSEC_COUNT<<2)*Trefclk>120ns,11us<PGM_COUNT*Trefclk+EFUSEC_COUNT*Trefclk<13us,
*  其中EFUSEC_COUNT>=3
*/
#define EFUSE_COUNT_CFG     20
#define PGM_COUNT_CFG       0x500

static inline void efusec_enable_clk(void)
{
	writel(GT_PCLK_EFUSEC, SCPEREN1(SCTRL_BASE));
}

static inline void efusec_disable_clk(void)
{
	/* disenable system efusec clock */
	writel(GT_PCLK_EFUSEC, SCPERDIS1(SCTRL_BASE));
}

static void efuse_power_on(void)
{
	/* 配置VOUT6输出1.8V, 给eFuse控制器上电 */
	int ret = 0;
	ret = regulator_bulk_enable(1, &g_efuse_data.regu_burning);
	if (ret)
		pr_err("failed to enable efuse regulators %d\n", ret);
	else
		pr_info("enable efuse regulators.\n");
}

static void efuse_power_down(void)
{
	/* 配置VOUT6输出0V, 给eFuse控制器下电 */
	int ret = 0;
	ret = regulator_bulk_disable(1, &g_efuse_data.regu_burning);
	if (ret)
		pr_err("failed to disable efuse regulators %d\n", ret);
	else
		pr_info("disable efuse regulators.\n");
}

static inline int exit_power_down_mode(void)
{
	unsigned int loop_count = EFUSE_OP_TIMEOUT_COUNT;
	int pd_status = readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PD_STATUS_MASK;

	if (pd_status == 0) {
		pr_debug("Current pd status is nomal.\n");
		return OK;
	}

	writel(readl(EFUSEC_CFG(EFC_BASE)) & (~EFUSEC_PD_EN), EFUSEC_CFG(EFC_BASE));

	while ((readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PD_STATUS_MASK) > 0) {
		pr_warning("Current pd status is power down.\n");
		if (0 == loop_count) {
			pr_err("Loop is overrun, current pd status is power down.\n");
			return ERROR;
		}
		loop_count--;
		udelay(EFUSE_OP_TIMEOUT);
	}
	pr_info("Exit power down mode OK.\n");
	return OK;
}

static inline int enter_power_down_mode(void)
{
	unsigned int loop_count = EFUSE_OP_TIMEOUT_COUNT;

	int pd_status = readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PD_STATUS_MASK;
	if (pd_status > 0) {
		pr_debug("Current pd status is power down.\n");
		return OK;
	}

	writel(readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_PD_EN, EFUSEC_CFG(EFC_BASE));
	while (0 == (readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PD_STATUS_MASK)) {
		pr_warning("Current pd status is nomal.\n");
		if (0 == loop_count) {
			pr_err("Loop is over, current pd status is nomal.\n");
			return ERROR;
		}
		loop_count--;
		udelay(EFUSE_OP_TIMEOUT);
	}
	pr_info("Enter the power down mode OK.\n");
	return OK;
}

static void display_regtable(void)
{
	pr_info("EFUSEC_CFG: 0x%X.\n", readl(EFUSEC_CFG(EFC_BASE)));
	pr_info("EFUSEC_STATUS: 0x%X.\n", readl(EFUSEC_STATUS(EFC_BASE)));
	pr_info("EFUSEC_GROUP: 0x%X.\n", readl(EFUSEC_GROUP(EFC_BASE)));
	pr_info("EFUSEC_PG_VALUE: 0x%X.\n", readl(EFUSEC_PG_VALUE(EFC_BASE)));
	pr_info("EFUSEC_COUNT: 0x%X.\n", readl(EFUSEC_COUNT(EFC_BASE)));
	pr_info("EFUSEC_PGM_COUNT: 0x%X.\n", readl(EFUSEC_PGM_COUNT(EFC_BASE)));
	pr_info("EFUSEC_DATA: 0x%X.\n", readl(EFUSEC_DATA(EFC_BASE)));
	pr_info("EFUSEC_HW_CFG: 0x%X.\n", readl(EFUSEC_HW_CFG(EFC_BASE)));
}



/******************************************************************************
Function:	    bsp_efuse_write
Description:	    从指定Words偏移开始写入指定Words个数的eFuse值
Input:		    buf			- 输入参数，存放要写入到eFuse中的值
		    size		- 输入参数，要写入的Words个数
		    group		- 输入参数，从指定的Words偏移处开始写入，
					  文中表示eFuse分组序号group
Output:		    none
Return:		    0: OK  其他: ERROR码
******************************************************************************/
int bsp_efuse_write(const unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)
{
	int result = OK;
	unsigned int *curr_value = (unsigned int *)buf;
	unsigned int count = 0;
	unsigned int group_index = group;
	unsigned int loop_count = EFUSE_OP_TIMEOUT_COUNT;
	unsigned int read_buf[64] = {0};

	pr_info("%s enter.(NO TZDRIVER)\n", __func__);

	/* 入参判断 */
	if (NULL == curr_value) {
		pr_err("bsp_efuse_write: puiValues is NULL!\n" );
		return ERROR;
	}

	if ((size == 0) ||
	    (group_index > EFUSEC_GROUP_MAX_COUNT) ||
	    (group_index + size > EFUSEC_GROUP_MAX_COUNT)) {
		pr_err("lineno:%d\n", __LINE__);
		pr_err("bsp_efuse_write: input para is overrun!"
		"size: %d, group: %d\n", size, group_index);
		return ERROR;
	}

	/* 使能软件通路 */
	writel(SYS_EFUSE_SOFT_SEL, SCEFUSECTRL(SCTRL_BASE));

	/* 配置remap为0，控制器会写入eFuse器件和eFuse镜像中 */
	writel(SCPERCTRL0_REMAP_DIS, SCPERCTRL0(SCTRL_BASE));

	/* 给eFuse控制器上电 */
	efuse_power_on();

	/* 使能efusec时钟 */
	efusec_enable_clk();

	/* 退出power_down状态 */
	if (ERROR == exit_power_down_mode()) {
		pr_err("Can't exit power down mode!\n" );
		result = ERROR_EXIT_PD;
		goto end1;
	}

	/* 判断是否允许烧写 */
	if ((readl(EFUSEC_HW_CFG(EFC_BASE)) & EFUSEC_APB_PGM_DISABLE_MASK) > 0) {
		pr_err("APB program is disnable!\n" );
		result = ERROR_APB_PGM_DIS;
		goto end1;
	}

	/* 选择efuse信号为apb操作efuse */
	writel(readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_APB_SIG_SEL, EFUSEC_CFG(EFC_BASE));

	/* 配置时序要求,hi3630 asic版本不能使用默认值 */
	writel(EFUSE_COUNT_CFG, EFUSEC_COUNT(EFC_BASE));
	writel(PGM_COUNT_CFG, EFUSEC_PGM_COUNT(EFC_BASE));

	/* 使能预烧写 */
	writel((readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_PRE_PG),  EFUSEC_CFG(EFC_BASE));
	loop_count = EFUSE_OP_TIMEOUT_COUNT;
	while (0 == (readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PGENAB_STATUS_MASK)) {
		pr_warning("Current pgenab status is not finished.\n");
		if (0 == loop_count--) {
			pr_err("time out, current pgenab status is not finished.\n");
			result = ERROR_PRE_WRITE;
			goto end2;
		}
		udelay(EFUSE_OP_TIMEOUT);
	}

	for (count = 0; count < size; count++) {
		if (0 == *curr_value) {
			/* 烧写下一组 */
			group_index++;
			curr_value++;
			continue;
		}

		/* 设置group */
		writel(group_index, EFUSEC_GROUP(EFC_BASE));

		/* 设置value */
		writel(*curr_value, EFUSEC_PG_VALUE(EFC_BASE));

		/* 使能烧写 */
		writel((readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_PG_EN),  EFUSEC_CFG(EFC_BASE));

		udelay(500);

		/* 查询烧写完成 */
		loop_count = EFUSE_OP_TIMEOUT_COUNT;
		while (0 == (readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_PG_STATUS_MASK)) {
			pr_debug("Current pg status is not finished.\n");
			if (0 == loop_count--) {
				pr_err("time out, current pg status is not finished.\n");
				result = ERROR_PG_OPERATION;
				goto end2;
			}
			udelay(EFUSE_OP_TIMEOUT);
		}

		pr_debug("Current pg status is finished, then write next group.\n");

		/* 烧写下一组 */
		group_index++;
		curr_value++;
	}
end2:
	/* 不使能预烧写 */
	writel((readl(EFUSEC_CFG(EFC_BASE)) & (~EFUSEC_PRE_PG)), EFUSEC_CFG(EFC_BASE));

	/* 修改efuse默认的仲裁为AIB */
	writel(readl(EFUSEC_CFG(EFC_BASE)) & (~EFUSEC_APB_SIG_SEL), EFUSEC_CFG(EFC_BASE));
end1:

	if (OK != result) {
		display_regtable();
	}

	result = bsp_efuse_read(read_buf, group, size);

	if (OK != result) {
		pr_err("bsp_efuse_read failed!\n" );
	}

	/* 配置remap为1, 读数据是从eFuse镜像中获得 */
	writel(SCPERCTRL0_REMAP_EN, SCPERCTRL0((SCTRL_BASE)));

	/* 给eFuse控制器下电 */
	efuse_power_down();

	return result;
}
EXPORT_SYMBOL_GPL(bsp_efuse_write);


/******************************************************************************
Function:	    bsp_efuse_read
Description:	    从指定Words偏移开始读取指定Words个数的eFuse值
Input:		    buf			- 输入&输出参数，存放读取到的eFuse值，
					  由调用方负责分配内存
		    group		- 输入参数，从指定的Words偏移处开始读取，
					  文中表示eFuse分组序号group
		    size		- 输入参数，要读取的Words个数
Output:		    buf			- 输出参数，存放读取到的eFuse值，
					  由调用方负责分配内存
Return:		    0: OK  其他: ERROR码
******************************************************************************/
int bsp_efuse_read(unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)
{
	int result = OK;
	unsigned int *curr_value = buf;
	unsigned int count = 0;
	unsigned int loop_count = EFUSE_OP_TIMEOUT_COUNT;

	pr_info("%s Enter.((NO TZDRIVER))", __func__);

	/* 入参判断 */
	if (NULL == buf) {
		pr_err("bsp_efuse_read: puiValues is NULL!\n" );
		return ERROR;
	}

	if ((size == 0) ||
	    (group > EFUSEC_GROUP_MAX_COUNT) ||
	    (group + size > EFUSEC_GROUP_MAX_COUNT)) {
		pr_err("bsp_efuse_read: input para is overrun!"
		"size: %d, group: %d\n", size, group);
		return ERROR;
	}

	/* 使能软件通路 */
	writel(SYS_EFUSE_SOFT_SEL, SCEFUSECTRL(SCTRL_BASE));

	/* 使能efusec时钟 */
	efusec_enable_clk();

	/* 退出power_down状态 */
	if (ERROR == exit_power_down_mode()) {
		pr_err("Can't exit power down mode!\n" );
		result = ERROR_EXIT_PD;
		goto end1;
	}


	/* 选择efuse信号为apb操作efuse */
	writel(readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_APB_SIG_SEL, EFUSEC_CFG(EFC_BASE));

	/* 循环读取Efuse值 */
	for (count = 0; count < size; count++) {
		/* 设置读取地址 */
		writel(group + count, EFUSEC_GROUP(EFC_BASE));

		/* 使能读efuse流程 */
		writel((readl(EFUSEC_CFG(EFC_BASE)) | EFUSEC_RD_EN),  EFUSEC_CFG(EFC_BASE));

		udelay(10);

		/* 等待读完成 */
		loop_count = EFUSE_OP_TIMEOUT_COUNT;

		while (0 == (readl(EFUSEC_STATUS(EFC_BASE)) & EFUSEC_RD_STATUS_MASK)) {
			pr_debug("Current efc read status is not finished.\n");
			if (0 == loop_count--) {
				pr_err("Current efc read timeout!\n");
				result = ERROR_EFUSEC_READ;
				goto end2;
			}
			udelay(EFUSE_OP_TIMEOUT);
		}
		pr_debug("Current efc read operation is finished, then read next group.\n");

		/* 读取数据 */
		*curr_value = readl(EFUSEC_DATA(EFC_BASE));
		curr_value++;
	}
end2:
	/* 修改efuse默认的仲裁为AIB */
	writel(readl(EFUSEC_CFG(EFC_BASE)) & (~EFUSEC_APB_SIG_SEL), EFUSEC_CFG(EFC_BASE));
end1:

	if (OK != result) {
		display_regtable();
	}
	return result;
}
EXPORT_SYMBOL_GPL(bsp_efuse_read);
#else
/******************************************************************************
Function:	    bsp_efuse_write
Description:	    从指定Words偏移开始写入指定Words个数的eFuse值
Input:		    buf			- 输入参数，存放要写入到eFuse中的值
		    size		- 输入参数，要写入的Words个数
		    group		- 输入参数，从指定的Words偏移处开始写入，
					  文中表示eFuse分组序号group
Output:		    none
Return:		    0: OK  其他: ERROR码
******************************************************************************/
int bsp_efuse_write(const unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)

{
	TEEC_Context context;
	TEEC_Session session;
	TEEC_Result result;
	TEEC_UUID svc_uuid = TEE_SERVICE_EFUSE;
	TEEC_Operation operation;
	uint32_t cmd_id;
	uint32_t origin;

	/* 入参判断 */
	if (NULL == buf) {
		pr_err("bsp_efuse_write: puiValues is NULL!\n" );
		return ERROR;
	}

	if ((size == 0) ||
	    (group > EFUSEC_GROUP_MAX_COUNT) ||
	    (group + size > EFUSEC_GROUP_MAX_COUNT)) {
		pr_err("lineno:%d\n", __LINE__);
		pr_err("bsp_efuse_write: input para is overrun!"
		"size: %d, group: %d\n", size, group);
		return ERROR;
	}

	result = TEEK_InitializeContext(
			               NULL,
			               &context);

	if(result != TEEC_SUCCESS) {
		TEEC_Error("TEEK_InitializeContext failed, result=0x%x\n", result);
		result = ERROR;
		goto error1;
	}
	TEEC_Info("succeed to initialize context.\n");

	result = TEEK_OpenSession(
	                    &context,
	                    &session,
	                    &svc_uuid,
	                    TEEC_LOGIN_PUBLIC,
	                    NULL,
	                    NULL,
	                    NULL);

	if (result != TEEC_SUCCESS) {
		TEEC_Error("TEEK_OpenSession failed, result=0x%x\n", result);
		result = ERROR_SECURE_OS;
		goto error2;
	}
	TEEC_Info("succeed to open session.\n");

	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_MEMREF_TEMP_INPUT,
						TEEC_NONE,
						TEEC_NONE);
	operation.params[0].value.a = size;
	operation.params[0].value.b = group;
	operation.params[1].tmpref.buffer = (void *)buf;
	operation.params[1].tmpref.size = size*sizeof(unsigned int);

	TEEC_Info("puiValues=0x%x, size=%d\n", virt_to_phys((void *)buf), size);

	cmd_id = ECHO_CMD_ID_EFUSE_WRITE;
	result = TEEK_InvokeCommand(
				&session,
				cmd_id,
				&operation,
				&origin);
	if (result != TEEC_SUCCESS) {
		TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
		result = ERROR_SECURE_OS;
	}
	TEEC_Info("succeed to invoke command.\n");

	TEEK_CloseSession(&session);
error2:
	TEEK_FinalizeContext(&context);
error1:
	return result;
}
EXPORT_SYMBOL_GPL(bsp_efuse_write);


/******************************************************************************
Function:	    bsp_efuse_read
Description:	    从指定Words偏移开始读取指定Words个数的eFuse值
Input:		    buf			- 输入&输出参数，存放读取到的eFuse值，
					  由调用方负责分配内存
		    group		- 输入参数，从指定的Words偏移处开始读取，
					  文中表示eFuse分组序号group
		    size		- 输入参数，要读取的Words个数
Output:		    buf			- 输出参数，存放读取到的eFuse值，
					  由调用方负责分配内存
Return:		    0: OK  其他: ERROR码
******************************************************************************/
int bsp_efuse_read(unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)
{
	TEEC_Context context;
	TEEC_Session session;
	TEEC_Result result;
	TEEC_UUID svc_uuid = TEE_SERVICE_EFUSE;
	TEEC_Operation operation;
	uint32_t cmd_id;
	uint32_t origin;

	/* 入参判断 */
	if (NULL == buf) {
		TEEC_Error("bsp_efuse_read: puiValues is NULL!\n" );
		return ERROR;
	}

	if ((size == 0) ||
	    (group > EFUSEC_GROUP_MAX_COUNT) ||
	    (group + size > EFUSEC_GROUP_MAX_COUNT))
	{
		TEEC_Error("bsp_efuse_read: input para is overrun!"
		"size: %d, group: %d\n", size, group);
		return ERROR;
	}

	result = TEEK_InitializeContext(
					NULL,
					&context);

	if(result != TEEC_SUCCESS) {
		TEEC_Error("TEEK_InitializeContext failed, result=0x%x\n", result);
		result = ERROR;
		goto error1;
	}
	TEEC_Info("succeed to initialize context.\n");

	result = TEEK_OpenSession(
				&context,
				&session,
				&svc_uuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				NULL);

	if (result != TEEC_SUCCESS) {
		TEEC_Error("TEEK_OpenSession failed, result=0x%x\n", result);
		result = ERROR_SECURE_OS;
		goto error2;
	}
	TEEC_Info("succeed to open session.\n");

	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_MEMREF_TEMP_OUTPUT,
						TEEC_NONE,
						TEEC_NONE);
	operation.params[0].value.a = size;
	operation.params[0].value.b = group;
	operation.params[1].tmpref.buffer = (void *)buf;
	operation.params[1].tmpref.size = size*sizeof(unsigned int);

	TEEC_Info("puiValues=0x%x, size=%d\n", virt_to_phys((void *)buf), size);

	cmd_id = ECHO_CMD_ID_EFUSE_READ;
	result = TEEK_InvokeCommand(
				&session,
				cmd_id,
				&operation,
				&origin);
	if (result != TEEC_SUCCESS) {
		TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n",
								result, origin);
		result = ERROR_SECURE_OS;
	}
	TEEC_Info("succeed to invoke command.\n");

	TEEK_CloseSession(&session);
error2:
	TEEK_FinalizeContext(&context);
error1:
	return result;
}
EXPORT_SYMBOL_GPL(bsp_efuse_read);
#endif

int efuse_test(void)
{
	u32 efuse_buf[64] = {0};
	u32 efuse_write[64] = {0};
	u32 i;
	uint8_t *p_efuse_write = (uint8_t *)(efuse_write);

	memset((void *)p_efuse_write, 0x5a, 2*4);

	if (OK == bsp_efuse_read(efuse_buf, 36, 2)) {
		pr_info("read efuse before write!\n");
		for(i = 0; i < 2; i++) {
			pr_info("efuse_buf[%d]=%x\n", i, efuse_buf[i]);
		}
	}
	else {
		pr_err("Failed to read efuse.\n");
	}


	if (OK == bsp_efuse_write(efuse_write, 36, 2)) {
		pr_info("efuse write : efuse_write[0]=%x,efuse_write[1]=%x\n",
						efuse_write[0], efuse_write[1]);
	}
	else {
		pr_err("Failed to write efuse.\n");
	}

	if (OK == bsp_efuse_read(efuse_buf, 36, 2)) {
		pr_info("read efuse after write!\n");
		for(i = 0; i < 2; i++) {
			pr_info("efuse_buf[%d]=%x\n", i, efuse_buf[i]);
		}
	}
	else {
		pr_err("Failed to read efuse.\n");
	}

	pr_debug("efuse_buf[1]=%x,efuse_buf[2]=%x\n", efuse_buf[1], efuse_buf[2]);
	if (memcmp((void *)(efuse_write), (void *)(efuse_buf), 4)) {
		pr_err("efuse_test failed.\n");
		return ERROR;
	}
	pr_info("efuse_test ok.\n");
	return OK;
}

/*
 * Function name:efusec_ioctl.
 * Discription:complement read efuse by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long efusec_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = OK;
	void __user *argp = (void __user *)arg;
	unsigned char efuse_read_buf[256] = {0};

	switch (cmd) {
	case HISI_EFUSE_READ_CHIPID:
		ret = bsp_efuse_read((unsigned int*)efuse_read_buf, 57, 2);
		if (ret) {
			pr_err("efusec_ioctl: bsp_efuse_read failed.\n");
			break;
		}

		/*send back to user*/
		if (copy_to_user(argp, efuse_read_buf, 8))
			ret = -EFAULT;

		break;
	case HISI_EFUSE_READ_DIEID:
		ret = bsp_efuse_read((unsigned int*)efuse_read_buf, 32, 5);
		if (ret) {
			pr_err("efusec_ioctl: bsp_efuse_read failed.\n");
			break;
		}

		/*send back to user*/
		if (copy_to_user(argp, efuse_read_buf, 20))
			ret = -EFAULT;

		break;
	default:
		pr_err("[EFUSE][%s] Unknow command!\n", __func__);
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct file_operations efusec_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = efusec_ioctl,
};

static int __init hisi_efusec_init(void)
{
	int ret = 0;
	int major = 0;
	struct class *efuse_class;
	struct device *pdevice;
	struct device_node *np = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_err("hisi efuse: No sysctrl compatible node found.\n");
		return -ENODEV;
	}
	SCTRL_BASE = of_iomap(np, 0);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hi6421-pmurtc");
	if (!np) {
		pr_err("hisi efuse: No pmurtc compatible node found.\n");
		return -ENODEV;
	}
	PMURTC_BASE = of_iomap(np, 0);

	np = of_find_compatible_node(NULL, NULL, "hisilicon, efuse");
	if (!np) {
		pr_err("hisi efuse: No efusec compatible node found.\n");
		return -ENODEV;
	}
	EFC_BASE = of_iomap(np, 0);

	pr_info("efuse SCTRL_BASE=%x, PMURTC_BASE=%x, EFC_BASE=%x",
		(unsigned int)SCTRL_BASE, (unsigned int)PMURTC_BASE,
		(unsigned int)EFC_BASE);

	major = register_chrdev(0, EFUSE_DEV_NAME, &efusec_fops);
	if (major <= 0) {
		ret = -EFAULT;
		pr_err("hisi efuse: unable to get major for memory devs.\n");
	}

	efuse_class = class_create(THIS_MODULE, EFUSE_DEV_NAME);
	if (IS_ERR(efuse_class)) {
		ret = -EFAULT;
		pr_err("hisi efuse: class_create error.\n");
		goto error1;
	}

	pdevice = device_create(efuse_class,NULL,MKDEV(major,0),NULL,EFUSE_DEV_NAME);
	if (IS_ERR(pdevice)){
		ret = -EFAULT;
		pr_err("hisi efuse: device_create error.\n");
		goto error2;
	}
	pr_info("efuse init");

	pdevice->of_node = np;
	g_efuse_data.regu_burning.supply = "efuse-burning";

	ret = regulator_bulk_get(pdevice , 1, &g_efuse_data.regu_burning);
	if (ret) {
		dev_err(pdevice, "couldn't get efuse-burning regulator %d\n\r",ret);
		goto error3;
	}
	else {
		pr_info("get efuse-burning regulator success!\n");
	}

	return ret;
error3:
	device_destroy(efuse_class, MKDEV(major,0));
	pdevice = NULL;
error2:
	class_destroy(efuse_class);
	efuse_class = NULL;
error1:
	unregister_chrdev(major, EFUSE_DEV_NAME);
	return ret;
}

late_initcall(hisi_efusec_init);

MODULE_DESCRIPTION("Hisilicon efusec driver");
MODULE_AUTHOR("chenya99@huawei.com");
MODULE_LICENSE("GPL");
