/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  acc_balong.h
*
*   作    者 :  w00228729
*
*   描    述 :  完成组包加速功能头文件
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 创建
*************************************************************************/
#ifndef	_ACC_BALONG_H_
#define	_ACC_BALONG_H_

#include <osl_types.h>
#include "cipher_balong.h"

#ifdef __cplusplus
extern "C" {
#endif


#define ACC_IV_NUM       0 /* max:2; min:0 */
#define ACC_USRFIELD_NUM 3 /* max:3; min:0 */
#define ACC_FIFO_NUM     4
/**********************************************************/

/*组包加速寄存器*/
#define CHN_ENBITS           0x1           /*使能ch_en位，通道使能寄存器的第0位 */
#define CHN_BDRESET          0x2           /*通道复位寄存器，清空BD队列，复位读指针*/
#define CHN_WPT              0xFFFFFC00    /*通道写指针复位*/
#define CHN_CFGUSR           0x60          /*将通道0的配置寄存器的userfiled域配成3*/

#define ACC_ERROR_PRINT(errno) \
do{\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ACC, "[ACC API ERROR]:\n\t\t <func>: %s;  <line>: %d;  <Errno>: %s (0x%08x)\n\n", \
               (int)__FUNCTION__, (int)__LINE__, (int)#errno, errno);\
    }\
}while(0)
#define ACC_INFOR_PRINT(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_ACC, "[ACC API INFOR]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

/* ACC_FIFO_DEEP should confirm to global variable fifo_elem_cnt in cipher_balong.c  */
#define ACC_CHN_NUM         2
#define CHN_STATBIT         (0x1U << 30)
#define CHN_PACK_ENBIT      0xBFFFFFFF
#define CHN_DENBIT          0xFFFFFFFE
#define CIPHER_INT0_MASK		(0x40C)
#define	CHN_PACK_DEN_EN	(CHN_PACK_ENBIT & CHN_DENBIT)

enum acc_fifo_sta
{
	ACC_STAT_WORK,
	ACC_STAT_CFG,
	ACC_STAT_IDLE
};

struct acc_bd
{
	u32 cfg;
	u32 ptr_attr_ilen;
	u32 offset_olen;
	u32 iptr_pad;
	u32 optr;
	u32 aph;
	u32 count;
#if (ACC_IV_NUM != 0)
	u128 iv[ACC_IV_NUM];
#endif
#if (ACC_USRFIELD_NUM != 0)
	u32 usr_field[ACC_USRFIELD_NUM];
#endif
};

struct acc_fifo_ctl
{
	enum acc_fifo_sta status;
	unsigned int      cfg_bd_idx;
	unsigned int      acc_chn_id;
	unsigned int      fifo_id;
	unsigned char     pad[16];   /* ensure this struct take up 32 bytes space */
};

struct acc_dbg_ctl
{
	unsigned int get_fifo_times;
	unsigned int cfg_dma_times;
	unsigned int cfg_cipher_times;
	unsigned int enable_times;
	unsigned int drop_pak_times;
	unsigned int dma_fifo_null;
	unsigned int cipher_fifo_null;
};

struct acc_chn_ctl
{
	void *          reg_base;
	unsigned int    acc_chn_num;
	unsigned int	fifo_depth;
	unsigned int    chn_enum[ACC_CHN_NUM];
	void *fifo_base[ACC_FIFO_NUM];
};

void acc_disable_aes_opt_bypass(void);
void acc_enable_aes_opt_bypass(void);
void acc_enable_bd_done_int(void);
#ifdef __cplusplus
}
#endif

#endif /* _ACC_BALONG_H_ */

