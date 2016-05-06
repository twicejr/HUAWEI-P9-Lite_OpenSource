#ifndef _HISILICON_EFUSE_H_
#define _HISILICON_EFUSE_H_

#include <linux/mutex.h>
#include <linux/types.h>
#include <linux/string.h>


typedef enum tag_efuse_log_level {
    log_level_disable = 0,
    log_level_error = 1,
    log_level_warning,
    log_level_debug,
    log_level_info ,
    log_level_total = log_level_info
}EFUSE_LOG_LEVEL;

typedef enum tag_efuse_mem_attribution {
    efuse_mem_attr_none = -1,
    efuse_mem_attr_huk = 0,
    efuse_mem_attr_scp,
    efuse_mem_attr_authkey,
    efuse_mem_attr_chipid,
    efuse_mem_attr_tsensor_calibration,
    efuse_mem_attr_huk_rd_disable,
    efuse_mem_attr_authkey_rd_disable,
    efuse_mem_attr_dbg_class_ctrl,
    efuse_mem_attr_dieid,
#ifdef __SLT_FEATURE__
    efuse_mem_attr_sltfinishflag,
#endif
    efuse_mem_attr_max
}EFUSE_MEM_ATTRIBUTION;

typedef struct tag_efuse_attribution_info {
    unsigned int bits_width;
}EFUSE_ATTRIBUTION_INFO;

typedef struct tag_efusec_data{
	unsigned int efuse_group_max;
	phys_addr_t  buf_phy_addr;
	unsigned char *buf_virt_addr;
#ifdef CONFIG_ATFDRIVER
	int (*invoke_efuse_fn)(u64, u64, u64, u64);
#endif
    EFUSE_ATTRIBUTION_INFO efuse_attrs_parsed_from_dts[efuse_mem_attr_max];
	struct mutex efuse_mutex;
}EFUSEC_DATA;

#define OK                      (0)     /* 成功 */
#define ERROR                   (-1)    /* 包括参数错误和不支持 两种错误情况*/
#define ERROR_EXIT_PD           (-2)    /* 不能退出power down模式 */
#define ERROR_ENTER_PD          (-3)    /* 不能退出power down模式 */
#define ERROR_APB_PGM_DIS       (-4)    /* 当前eFusec不允许烧写 */
#define ERROR_EFUSEC_READ       (-5)    /* 不能完成一次eFuse读操作 */
#define ERROR_PRE_WRITE         (-6)    /* 未完成预烧写置位 */
#define ERROR_PG_OPERATION      (-7)    /* 不能完成一次eFuse写操作 */


#define HISI_EFUSE_READ_CHIPID             0x1000
#define HISI_EFUSE_READ_DIEID              0x2000
#define HISI_EFUSE_WRITE_CHIPID            0x3000
#define HISI_EFUSE_READ_AUTHKEY            0x4000
#define HISI_EFUSE_WRITE_AUTHKEY           0x5000
#define HISI_EFUSE_READ_CHIPIDLEN          0x6000
#define HISI_EFUSE_WRITE_DEBUGMODE         0x7000
#define HISI_EFUSE_READ_DEBUGMODE          0x8000

#define HISI_EFUSE_READ_THERMAL            0x9000
#define HISI_EFUSE_TEST_DISPLAY            0xa000

/* #define HISI_EFUSE_DEBUG */

#ifdef HISI_EFUSE_DEBUG
#define HISI_EFUSE_TEST_WR           0xa001
#define HISI_EFUSE_TEST_READ_CHIPID  0xa002
#define HISI_EFUSE_TEST_READ_DIEID   0xa003
#define HISI_EFUSE_TEST_READ_KCE     0xa004
#define HISI_EFUSE_TEST_WRITE_KCE    0xa005
#endif

#ifdef __SLT_FEATURE__
#define HISI_EFUSE_WRITE_SLTFINISHFLAG          0xb000
#define HISI_EFUSE_READ_SLTFINISHFLAG           0xb001
#endif
#define HISI_EFUSE_WRITE_DJTAGDEBUG             0xc000
#define HISI_EFUSE_READ_DJTAGDEBUG              0xd000

#define EFUSE_BUF_SIZE                     (256)
#define EFUSE_MAILBOX_TIMEOUT_1000MS       (1000)

extern int get_efuse_dieid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int timeout);
extern int get_efuse_thermal_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);
extern int get_efuse_carrierid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);
extern int set_efuse_djtagdebug_value(unsigned char *pu8Buffer, unsigned int timeout);
extern int get_efuse_djtagdebug_value(unsigned char *pu8Buffer, unsigned int timeout);

#ifdef CONFIG_HI3XXX_EFUSE
#define  EFUSE_DIEID_GROUP_START  32
#define  EFUSE_DIEID_GROUP_WIDTH  5
#define  EFUSE_CHIPID_GROUP_START  57
#define  EFUSE_CHIPID_GROUP_WIDTH  2
#define  EFUSE_KCE_GROUP_START  28
#define  EFUSE_KCE_GROUP_WIDTH  4
/*****************************************************************************
* 函 数 名  : bsp_efuse_read
*
* 功能描述  : 按组读取EFUSE中的数据
*
* 输入参数  : group  起始group
*                   num  数组长度(word数,不超过16)
* 输出参数  : pBuf ：EFUSE中的数据
*
* 返 回 值  : 
*
* 其它说明  : 
*
*****************************************************************************/
int bsp_efuse_read(unsigned int * pBuf, const unsigned int group, const unsigned int num);

/*****************************************************************************
* 函 数 名  : bsp_efuse_write
*
* 功能描述  : 烧写Efsue
*
* 输入参数  : pBuf:待烧写的EFUSE值
*                 group,Efuse地址偏移
*                 len,烧写长度
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_write(unsigned int *pBuf, const unsigned int group, const unsigned int num);
#endif

extern int test_efuse_display(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
#ifdef HISI_EFUSE_DEBUG
extern int test_efuse_wr(unsigned int timeout);
#endif
#endif
