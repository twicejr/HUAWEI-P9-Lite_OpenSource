#ifndef _HISILICON_EFUSE_H_
#define _HISILICON_EFUSE_H_

#define EFUSE_MAX_SIZE			2048
#define EFUSEC_GROUP_MAX_COUNT		(EFUSE_MAX_SIZE/32)

#define OK      			(0)
#define ERROR  				(-1)
#define ERROR_EXIT_PD			(-2)	/* 不能退出power down模式 */
#define ERROR_ENTER_PD			(-3)	/* 不能退出power down模式 */
#define ERROR_APB_PGM_DIS		(-4)	/* 当前eFusec不允许烧写 */
#define ERROR_EFUSEC_READ		(-5)	/* 不能完成一次eFuse读操作 */
#define ERROR_PRE_WRITE			(-6)	/* 未完成预烧写置位 */
#define ERROR_PG_OPERATION		(-7)	/* 不能完成一次eFuse写操作 */
#define ERROR_SECURE_OS                 (-8)	/* 安全OS执行错误 */

#define	HISI_EFUSE_READ_CHIPID		0x1000
#define	HISI_EFUSE_READ_DIEID		0x2000

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
extern int bsp_efuse_write(const unsigned int* buf,
			  const unsigned int group,
			  const unsigned int size);

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
extern int bsp_efuse_read(unsigned int* buf,
			  const unsigned int group,
			  const unsigned int size);

#endif
