//#include <vxWorks.h>
#include <stdio.h>
#include <string.h>
#include "baseaddr.h"
#include "BasicFunc.h"
#include "common.h"
#include "mem_fun.h"

#define MAC_ENCAP_START    0x00
#define LOCH_NUM           0x004
#define DDI0_EN            0x008
#define SI_EN              0x00C
#define SI_DATA            0x010
#define PADDING_LENGTH     0x014
#define ENCAP_TRANS_ADDR   0x018
#define TRANS_NUM          0x01C
#define BBP_DEST_ADDR      0x020
#define INT_EN             0x024
#define INT_RAW            0x028
#define INT_MASK           0x02C
#define INT_CLR            0x030
#define BUS_ERROR_ADDR     0x034
#define LOCH1_PARAM        0x038
#define LOCH2_PARAM        0x03C
#define LOCH3_PARAM        0x040
#define LOCH4_PARAM        0x044
#define LOCH5_PARAM        0x048
#define LOCH6_PARAM        0x04C
#define LOCH7_PARAM        0x050
#define LOCH8_PARAM        0x054
#define LOCH1_START_ADDR   0x058
#define LOCH2_START_ADDR   0x05C
#define LOCH3_START_ADDR   0x060
#define LOCH4_START_ADDR   0x064
#define LOCH5_START_ADDR   0x068
#define LOCH6_START_ADDR   0x06C
#define LOCH7_START_ADDR   0x070
#define LOCH8_START_ADDR   0x074
#define LOCH1_END_ADDR     0x078
#define LOCH2_END_ADDR     0x07C
#define LOCH3_END_ADDR     0x080
#define LOCH4_END_ADDR     0x084
#define LOCH5_END_ADDR     0x088
#define LOCH6_END_ADDR     0x08C
#define LOCH7_END_ADDR     0x090
#define LOCH8_END_ADDR     0x094
#define LOCH1_READ_ADDR    0x098
#define LOCH2_READ_ADDR    0x09C
#define LOCH3_READ_ADDR    0x0A0
#define LOCH4_READ_ADDR    0x0A4
#define LOCH5_READ_ADDR    0x0A8
#define LOCH6_READ_ADDR    0x0AC
#define LOCH7_READ_ADDR    0x0B0
#define LOCH8_READ_ADDR    0x0B4
#define LOCH1_NUM_CFG      0x0B8
#define LOCH2_NUM_CFG      0x0BC
#define LOCH3_NUM_CFG      0x0C0
#define LOCH4_NUM_CFG      0x0C4
#define LOCH5_NUM_CFG      0x0C8
#define LOCH6_NUM_CFG      0x0CC
#define LOCH7_NUM_CFG      0x0D0
#define LOCH8_NUM_CFG      0x0D4
#define UPACC_EN           0x0D8
#define PDUARY_EN_E        0x0DC
#define LOCH1_PDUARY_ADDR  0x0E0
#define LOCH2_PDUARY_ADDR  0x0E4
#define LOCH3_PDUARY_ADDR  0x0E8
#define LOCH4_PDUARY_ADDR  0x0EC
#define LOCH5_PDUARY_ADDR  0x0F0
#define LOCH6_PDUARY_ADDR  0x0F4
#define LOCH7_PDUARY_ADDR  0x0F8
#define LOCH8_PDUARY_ADDR  0x0FC


#define MAC_ENCAP_START_I1   0x100
#define LOCH_NUM_I1          0x104
#define HEAD0_EN_I1          0x108
#define E_RNTI_I1            0x10C
#define SI_EN_I1             0x110
#define SI_DATA_I1           0x114
#define PADDING_LEN_I1       0x118
#define TSN_LEN_I1           0x11C
#define PARAM_ADDR_I1        0x120
#define HARQ_BUF_ADDR_I1     0x124
#define BBP_DEST_ADDR_I1     0x128
#define TRANS_NUM_I1         0x12C
#define INT_EN_I1            0x130
#define INT_RAW_I1           0x134
#define INT_MASK_I1          0x138
#define INT_CLR_I1           0x13C
#define BUS_ERROR_ADDR_I1    0x140
#define UPACC_EN_I1          0x144
#define HARQ_WRITE_ADDR_I1   0x148
#define BBP_WRITE_ADDR_I1    0x14C
#define PDUARY_EN_I1         0x150

#define MAC_ENCAP_START_I2   0x200
#define LOCH_NUM_I2          0x204
#define HEAD0_EN_I2          0x208
#define E_RNTI_I2            0x20C
#define SI_EN_I2             0x210
#define SI_DATA_I2           0x214
#define PADDING_LEN_I2       0x218
#define TSN_LEN_I2           0x21C
#define PARAM_ADDR_I2        0x220
#define HARQ_BUF_ADDR_I2     0x224
#define BBP_DEST_ADDR_I2     0x228
#define TRANS_NUM_I2         0x22C
#define INT_EN_I2            0x230
#define INT_RAW_I2           0x234
#define INT_MASK_I2          0x238
#define INT_CLR_I2           0x23C
#define BUS_ERROR_ADDR_I2    0x240
#define UPACC_EN_I2          0x244
#define HARQ_WRITE_ADDR_I2   0x248
#define BBP_WRITE_ADDR_I2    0x24C
#define PDUARY_EN_I2         0x250


int upacc_rd(UINT32 pAddr,UINT32 comp_Data);
void upacc_dly(UINT32 num);

void upacc_intr_clr();

void upacc_reg_test();

int upacc_test01();
int upacc_test02();
int upacc_test03();
int upacc_test04();
int upacc_test05();
int upacc_test06();
int upacc_test07();
int upacc_test08();
int upacc_test09();
int upacc_test10();
int upacc_test11();
int upacc_test12();
int upacc_test13();
int upacc_test14();
int upacc_test15();
int upacc_test16();
int upacc_test17();
int upacc_test18();
int upacc_test19();	
int upacc_test20();
int upacc_test21();
int upacc_test22();
int upacc_test23();
int upacc_test24();
int upacc_test25();	
int upacc_test26();	
int upacc_test27();	
int upacc_test28();	
int upacc_test29();
int upacc_test30();
int upacc_test31();
int upacc_test32();
int upacc_test33();
int upacc_test34();
int upacc_test35();
int upacc_test36();
int upacc_test37();
int upacc_test38();
int upacc_test39();
int upacc_test40();


int upacc_trans_config(UINT32 src_addr, UINT32 des_addr, UINT32 num_8);
//int upacc_trans_en(UINT32 upacc_baseaddr);
int upacc_trans_en();
int upacc_trans_check(UINT32 src_addr, UINT32 des_addr, UINT32 num_8);






