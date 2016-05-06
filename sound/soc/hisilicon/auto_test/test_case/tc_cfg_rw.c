/****************************************************************************

                  °æÈ¨ËùÓĞ (C), 2001-2011, »ªÎª¼¼ÊõÓĞÏŞ¹«Ë¾

 ****************************************************************************
  ÎÄ ¼ş Ãû   : test_asp_cfg.c
  °æ ±¾ ºÅ   : ³õ¸å
  ×÷    Õß   : w00262566
  Éú³ÉÈÕÆÚ   : 2015Äê1ÔÂ27ÈÕ
  ×î½üĞŞ¸Ä   :
  ¹¦ÄÜÃèÊö   : ×Ô¶¯»¯²âÊÔ¹«¹²º¯ÊıÄ£¿é
  º¯ÊıÁĞ±í   :
                at_util_reg_read_u32
                at_util_reg_write_u32
                at_util_mem_remap_type
                at_util_reg_test
                at_util_log_file_open
                at_util_log_file_close
                at_util_log
  ĞŞ¸ÄÀúÊ·   :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ´´½¨ÎÄ¼ş
******************************************************************************/

/*****************************************************************************
  1 Í·ÎÄ¼ş°üº¬
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>

#include "util.h"
#include "core.h"
#include "asp_cfg.h"


/*****************************************************************************
  2 È«¾Ö±äÁ¿Óëºê¶¨Òå¶¨Òå
*****************************************************************************/
#define DRV_NAME              "tc_cfg_reg"

static int tc_cfg_probe (struct platform_device *pdev);
static int tc_cfg_remove(struct platform_device *pdev);

static struct at_case_type* tc_cfg_reg;

static const struct of_device_id tc_cfg_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver tc_cfg_driver = {
    .probe      = tc_cfg_probe,
    .remove     = tc_cfg_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = tc_cfg_of_match,
    },
};


struct at_util_reg_test_type asp_cfg_regs[] = {
  //  {0x0  , WO, 0x00000000, 0x0007FFFF, 0x00000000},                    //R_RST_CTRLEN,     å¤–è®¾è½¯å¤ä½ä½¿èƒ½å¯„å­˜å™¨
    {0x4  , WO, 0x00000000, 0x00000000, 0x00000000},                    //R_RST_CTRLDIS,    å¤–è®¾è½¯å¤ä½æ’¤ç¦»å¯„å­˜å™¨


    {0xC  , WO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_GATE_EN,        æ—¶é’Ÿä½¿èƒ½å¯„å­˜å™¨
    {0x10 , WO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_GATE_DIS,       æ—¶é’Ÿç¦æ­¢å¯„å­˜å™¨
    {0x14 , RO, 0x00000000, 0x00000000, 0x01000000},                    //R_GATE_CLKEN      æ—¶é’Ÿä½¿èƒ½çŠ¶æ€å¯„å­˜å™¨
    {0x18 , RO, 0x00000000, 0x00000000, 0x7fffbfff},                    //R_GATE_CLKSTAT    æ—¶é’Ÿæœ€ç»ˆçŠ¶æ€å¯„å­˜å™¨     ?


    {0x1C , RW, 0x000000FF, 0x0000007f, 0x0000007f},                    //R_GATE_CLKDIV_EN  æ—¶é’Ÿåˆ†é¢‘å™¨é—¨æ§ä½¿èƒ½å¯„å­˜å™¨
    {0x20 , RW, 0x0147AE14, 0x0147AE14, 0x0147AE14},                    //R_CLK1_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨1
    {0x24 , RW, 0x01179EC9, 0x01179EC9, 0x01179EC9},                    //R_CLK2_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨2
    {0x28 , RW, 0x00001707, 0xffff1707, 0x00001707},                    //R_CLK3_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨3
    {0x2C , RW, 0x00001717, 0xffff1717, 0x00001717},                    //R_CLK4_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨4
    {0x30 , RW, 0x00003F3F, 0xffff3f3f, 0x00003f3f},                    //R_CLK5_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨5
    {0x34 , RW, 0x00003F3F, 0xffff3f3f, 0x00003f3f},                    //R_CLK6_DIV        åˆ†é¢‘æ¯”æ§åˆ¶å¯„å­˜å™¨6

//    {0x38 , RW, 0x0000000F, 0xffffffff, 0x0000ffff},                    //R_CLK_SEL         æ—¶é’Ÿé€‰æ‹©å¯„å­˜å™¨
 //   {0x3C , RW, 0x00000000, 0x0000ffff, 0x0000ffff},                    //R_DSP_NMI         DSP NMIä¸­æ–­äº§ç”Ÿå¯„å­˜å™¨
    {0x40 , RW, 0x00000000, 0x0000ffff, 0x0000ffff},                    //R_DSP_PRID        DSP PRIDè®¾ç½®å¯„å­˜å™¨
    {0x44 , RW, 0x00000001, 0x00000001, 0x00000001},                    //R_DSP_RUNSTALL    DSP RUNSTALLè®¾ç½®å¯„å­˜å™¨

    {0x48 , RW, 0x00000000, 0x00000001, 0x00000001},                    //R_DSP_STATVECTORSEL   DSP STATVECTORSELè®¾ç½®å¯„å­˜å™¨
    {0x4C , RW, 0x00000000, 0x00000001, 0x00000001},                    //R_DSP_OCDHALTONRESET  DSP OCDHALTONRESETè®¾ç½®å¯„å­˜å™¨   ?

    {0x50 , RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_DSP_STATUS          DSP çŠ¶æ€å¯„å­˜å™¨

    {0x54 , RW, 0x00000000, 0xffffffff, 0x0000ffff},                    //R_DMAC_SEL            DMACé€šé“é€‰æ‹©å¯„å­˜å™¨
    {0x58 , RW, 0x853E4000, 0xffffffff, 0xffffffff},                    //R_BUS_PRIORITY        æ€»çº¿ä¼˜å…ˆçº§é…ç½®å¯„å­˜å™¨
    {0x5C , RW, 0x00000000, 0xffff0fff, 0x00000fff},                    //R_CG_EN               è‡ªåŠ¨é—¨æ§ä½¿èƒ½å¯„å­˜å™¨ ?
    {0x60 , RW, 0x00000000, 0xffff0fff, 0x00000fff},                    //R_OCRAM_RET           ocramä½åŠŸè€—é…ç½®å¯„å­˜å™¨
    {0x64 , RO, 0x00000000, 0xffffffff, 0x0000ffff},                    //R_INTR_NS_INI         éå®‰å…¨ä¸­æ–­åŸå§‹çŠ¶æ€å¯„å­˜å™¨
    {0x68 , RW, 0x00000000, 0x0000000d, 0x0000000d},                    //R_INTR_NS_EN          éå®‰å…¨ä¸­æ–­ä½¿èƒ½å¯„å­˜å™¨
    {0x6C , RO, 0x00000000, 0x0000000f, 0x00000000},                    //R_INTR_NS_MASK        éå®‰å…¨ä¸­æ–­å±è”½åçŠ¶æ€å¯„å­˜å™¨
    {0x70 , RO, 0x01011111, 0x00000000, 0x0000000f},                    //R_DBG_SET_AHB2AXI     ä»˜å¼ºæ¡¥DBGä¿¡å·è®¾ç½®å¯„å­˜å™¨   ?
    {0x74 , RO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_DBG_STATUS_AHB2AXI  ä»˜å¼ºæ¡¥DBGä¿¡å·çŠ¶æ€å¯„å­˜å™¨   ?
    {0x78 , RO, 0x00000000, 0x00000000, 0x00000000},                    //R_DLOCK_BP            æ€»çº¿é˜²æŒ‚æ­»bypasså¯„å­˜å™¨  ?


    {0x7C, RO,  0x00000000, 0xffffffff, 0x00000001},                    //R_DSP_BINTERRUPT      ä¸ŠæŠ¥åˆ°hifi dspçš„ä¸­æ–­ä¿¡å·åªè¯»å¯„å­˜å™¨
    {0x84, WO,  0x00000000, 0xffff0000, 0x00000000},                    //R_DSP_RAM_RET         ?
    {0x84, RW,  0x00000000, 0x0000ffff, 0x00000000},
    {0x100, WO, 0x0000FFFF, 0xffff0000, 0x0000FFFF},                    //R_TZ_SECURE_N         ?
    {0x100, WO, 0x0000FFFF, 0xffffffff, 0xffffffff},
  //  {0x104, RW, 0x000003FF, 0x000003ff, 0x000003ff},                    //R_OCRAM_R0SIZE        ?
    {0x108, RW, 0x00000000, 0x0000000f, 0x00000000},                    //R_SIO_LOOP_SECURE_N   ?

    {0x10C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_INTR_S_INI          å®‰å…¨ä¸­æ–­åŸå§‹çŠ¶æ€å¯„å­˜å™¨
    {0x110, RW, 0x00000000, 0x00000003, 0x00000000},                    //R_INTR_S_EN           å®‰å…¨ä¸­æ–­ä½¿èƒ½å¯„å­˜å™¨
    {0x114, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_INTR_S_MASK         å®‰å…¨ä¸­æ–­å±è”½åçŠ¶æ€å¯„å­˜å™¨
    {0x118, RW, 0x00000000, 0x000001fd, 0x00000000},                    //R_DSP_REMAPPING_EN    dspåœ°å€é‡æ˜ å°„ä½¿èƒ½å¯„å­˜å™¨

    {0x11C, RW, 0x00000000, 0xFFF00000, 0x00000000},                    //R_DSP_REMAPPING_SRC_BASE_ADDR DSP åœ°å€é‡æ˜ å°„å¯„å­˜å™¨
    {0x120, RW, 0x00000000, 0xFFF00000, 0x00000000},                    //R_DSP_REMAPPING_DES_BASE_ADDR DSP åœ°å€é‡æ˜ å°„å¯„å­˜å™¨

    {0x124, RW, 0x00000000, 0x000003ff, 0x000003ff},                    //R_DDR_HARQ_REMAP_EN               DDRä¸Harq Memory remapæ§åˆ¶å¯„å­˜å™¨
    {0x128, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_HARQ_REMAP_SRC_BASE_ADDR    DDRä¸Harq Memory remapæºåŸºåœ°å€å¯„å­˜å™¨
    {0x130, RW, 0x00000000, 0x000003FF, 0x000003FF},                    //R_DDR_MMBUF_REMAP_EN              DDRä¸MMBUF remapæ§åˆ¶å¯„å­˜å™¨
    {0x134, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_MMBUF_REMAP_SRC_BASE_ADDR   DDRä¸MMBUF remapæºåŸºåœ°å€å¯„å­˜å™¨
    {0x138, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_MMBUF_REMAP_DES_BASE_ADDR   DDRä¸MMBUF remapç›®æ ‡åŸºåœ°å€å¯„å­˜å™¨


    {0x13C, RW, 0x00000000, 0x000003ff, 0x000003ff},                    //R_DDR_OCRAM_REMAP_EN              DDRä¸OCRAM remapæ§åˆ¶å¯„å­˜å™¨
    {0x140, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_OCRAM_REMAP_SRC_BASE_ADDR   DDRä¸OCRAM remapæºåŸºåœ°å€å¯„å­˜å™¨
    {0x144, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_OCRAM_REMAP_DES_BASE_ADDR   DDRä¸OCRAM remapç›®æ ‡åŸºåœ°å€å¯„å­˜å™¨

    {0x148, WO, 0x000000FD, 0xffff0000, 0xffff0000},                    //R_MMBUF_CTRL                      MMBUF CTRLé…ç½®å¯„å­˜å™¨
    {0x148, WO, 0x000000FD, 0xffffffff, 0xffffffff},

    {0x14C, RW, 0x00000000, 0x000007FF, 0x000007FF},                    //R_HIFIDSP_CLK_DIV_AUTO                HIFIDSPæ—¶é’Ÿé¢‘ç‡è‡ªåŠ¨è°ƒé¢‘é…ç½®å¯„å­˜å™¨
    {0x150, RW, 0x00000110, 0x0000ffff, 0x0000ffff},                    //R_INTR_FREQ_OFFSET_CFG                é¢‘åè®°å½•æ¨¡å—é…ç½®å¯„å­˜å™¨
    {0x160, RW, 0x00000000, 0x0000000f, 0x0000000f},                    //R_ACCESS_ADDR_MONITOR_EN_ADDR         å†…å­˜ç›‘æ§æ¨¡å—ä½¿èƒ½é…ç½®å¯„å­˜å™¨
    {0x164, WO, 0x00000000, 0X00000001, 0x00000000},                    //R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR   å†…å­˜ç›‘æ§æ¨¡å—ä¸­æ–­æ¸…é›¶é…ç½®å¯„å­˜å™¨
    {0x168, RW, 0x00000000, 0x0000000f, 0x0000000f},                    //R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR    å†…å­˜ç›‘æ§æ¨¡å—ä¸­æ–­ä½¿èƒ½é…ç½®å¯„å­˜å™¨
    {0x16C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR  å†…å­˜ç›‘æ§æ¨¡å—ä¸­æ–­çŠ¶æ€å¯„å­˜å™¨
    {0x170, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR0_BASE_ADDR      å†…å­˜ç›‘æ§æ¨¡å—0åŸºåœ°å€é…ç½®å¯„å­˜å™¨
    {0x174, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR0_LEN_ADDR       å†…å­˜ç›‘æ§æ¨¡å—0åœ°å€é•¿åº¦é…ç½®å¯„å­˜å™¨
    {0x178, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR0_HIT_AWADDR     å†…å­˜ç›‘æ§æ¨¡å—0è¶Šç•Œçš„å†™åœ°å€è®°å½•å¯„å­˜å™¨
    {0x17C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR0_HIT_ARADDR     å†…å­˜ç›‘æ§æ¨¡å—0è¶Šç•Œçš„è¯»åœ°å€è®°å½•å¯„å­˜å™¨
    {0x180, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR1_BASE_ADDR      å†…å­˜ç›‘æ§æ¨¡å—1åŸºåœ°å€é…ç½®å¯„å­˜å™¨
    {0x184, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR1_LEN_ADDR       å†…å­˜ç›‘æ§æ¨¡å—1åœ°å€é•¿åº¦é…ç½®å¯„å­˜å™¨
    {0x188, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR1_HIT_AWADDR     å†…å­˜ç›‘æ§æ¨¡å—1è¶Šç•Œçš„å†™åœ°å€è®°å½•å¯„å­˜å™¨
    {0x18C, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR1_HIT_ARADDR     å†…å­˜ç›‘æ§æ¨¡å—1è¶Šç•Œçš„è¯»åœ°å€è®°å½•å¯„å­˜å™¨
    {0x190, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR2_BASE_ADDR      å†…å­˜ç›‘æ§æ¨¡å—2åŸºåœ°å€é…ç½®å¯„å­˜å™¨
    {0x194, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR2_LEN_ADDR       å†…å­˜ç›‘æ§æ¨¡å—2åœ°å€é•¿åº¦é…ç½®å¯„å­˜å™¨
    {0x198, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR2_HIT_AWADDR     å†…å­˜ç›‘æ§æ¨¡å—2è¶Šç•Œçš„å†™åœ°å€è®°å½•å¯„å­˜å™¨
    {0x19C, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR2_HIT_ARADDR     å†…å­˜ç›‘æ§æ¨¡å—2è¶Šç•Œçš„è¯»åœ°å€è®°å½•å¯„å­˜å™¨
    {0x1A0, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR3_BASE_ADDR      å†…å­˜ç›‘æ§æ¨¡å—3åŸºåœ°å€é…ç½®å¯„å­˜å™¨
    {0x1A4, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR3_BASE_ADDR      å†…å­˜ç›‘æ§æ¨¡å—3åœ°å€é•¿åº¦é…ç½®å¯„å­˜å™¨
    {0x1A8, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR3_HIT_AWADDR     å†…å­˜ç›‘æ§æ¨¡å—3è¶Šç•Œçš„å†™åœ°å€è®°å½•å¯„å­˜å™¨
    {0x1AC, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR3_HIT_ARADDR     å†…å­˜ç›‘æ§æ¨¡å—3è¶Šç•Œçš„è¯»åœ°å€è®°å½•å¯„å­˜å™¨
    {0x1B0, RW, 0x01A80090, 0xffffffff, 0xffffffff},                    //R_MEMORY_CTRL                         memoryæ§åˆ¶é…ç½®å¯„å­˜å™¨


    /*reserved
    {0x1B4, RW, 0x00000001, 0x00000001, 0x00000001},                    //R_SLIMBUS_PRIMARY_ADDR                slimbus primaryé…ç½®å¯„å­˜å™¨
    {0x1B8, RW, 0x00000000, 0x00000000, 0x00000001},                    //R_SLIMBUS_ID_ADDR                     slimbus idé…ç½®å¯„å­˜å™¨
    {0x200, RW, 0x00000000, 0x00000000, 0x00000001},                    //R_SECURE_AUTHORITY_EN                 å®‰å…¨è®¿é—®å±æ€§æ§åˆ¶å¯„å­˜å™¨
    */

};

/*****************************************************************************
  3 º¯ÊıÊµÏÖ
*****************************************************************************/


/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_read_write_test
 ¹¦ÄÜÃèÊö  : ²âÊÔcfgÖĞµÄ¼Ä´æÆ÷
 ÊäÈë²ÎÊı  : ÎŞ
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ÎŞ
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
void tc_cfg_read_write_test(void)
{
    char* tc_cfg_read_write_test_success = "tc_cfg_read_write_test result success\n";
    char* tc_cfg_read_write_test_failed  = "tc_cfg_read_write_test result faied\n";
    pr_info("Audio: test reg beg\n");

    if(AT_SUCCESS == asp_cfg_reg_rw_test(asp_cfg_regs, sizeof(asp_cfg_regs) / sizeof(asp_cfg_regs[0]))){
        at_util_log(tc_cfg_read_write_test_success,strlen(tc_cfg_read_write_test_success));
    }else {
        at_util_log(tc_cfg_read_write_test_failed,strlen(tc_cfg_read_write_test_failed));
    }

    pr_info("Audio: test reg end\n");
}
EXPORT_SYMBOL(tc_cfg_read_write_test);


/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_reg_prepare
 ¹¦ÄÜÃèÊö  : ²âÊÔÇ°´¦Àí
 ÊäÈë²ÎÊı  : int ²âÊÔ²ÎÊı
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ÎŞ
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
int tc_cfg_reg_prepare(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_prepare \n");
    asp_cfg_powerup();
    return AT_SUCCESS;
}

/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_reg_beg
 ¹¦ÄÜÃèÊö  : ²âÊÔ´¦Àí
 ÊäÈë²ÎÊı  : int ²âÊÔ²ÎÊı
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ÎŞ
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
int tc_cfg_reg_beg(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_beg \n");
    tc_cfg_read_write_test();
    return AT_SUCCESS;
}

/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_reg_stop
 ¹¦ÄÜÃèÊö  : ²âÊÔºó´¦Àí
 ÊäÈë²ÎÊı  : int ²âÊÔ²ÎÊı
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ÎŞ
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
int tc_cfg_reg_stop(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_stop \n");
    return AT_SUCCESS;
}


/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_read_write_test_individual
 ¹¦ÄÜÃèÊö  : ²âÊÔcfgÖĞµÄ¼Ä´æÆ÷
 ÊäÈë²ÎÊı  : ÎŞ
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ÎŞ
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
void tc_cfg_read_write_test_individual(void)
{
    pr_info("Audio: tc_cfg_read_write_test_individual beg\n");
    char* tc_cfg_read_log_beg = "tc_cfg_read_write_test_individual beg\n";
    char* tc_cfg_read_log_end = "tc_cfg_read_write_test_individual end\n";
    at_util_log(tc_cfg_read_log_beg,strlen(tc_cfg_read_log_beg));
    tc_cfg_reg_prepare(0);
    tc_cfg_reg_beg(0);
    tc_cfg_reg_stop(0);
    at_util_log(tc_cfg_read_log_end,strlen(tc_cfg_read_log_end));
    pr_info("Audio: tc_cfg_read_write_test_individual end\n");
}
EXPORT_SYMBOL(tc_cfg_read_write_test_individual);

/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_probe
 ¹¦ÄÜÃèÊö  : tc cfg Çı¶¯³õÊ¼»¯
 ÊäÈë²ÎÊı  : struct platform_device* Éè±¸Ö¸Õë
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : ³õÊ¼»¯½á¹û
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ27ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
static int tc_cfg_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_cfg_reg = devm_kmalloc(&pdev->dev,sizeof(struct at_case_type), GFP_ATOMIC);
    if(NULL == tc_cfg_reg){
         return -ENOMEM;
    }

    tc_cfg_reg->test_name   = "tc_cfg_reg";
    tc_cfg_reg->test_params = 0;
    tc_cfg_reg->test_pri    = AT_CASE_PRI_HIG;
    tc_cfg_reg->prepare     = tc_cfg_reg_prepare;
    tc_cfg_reg->begin       = tc_cfg_reg_beg;
    tc_cfg_reg->stop        = tc_cfg_reg_stop;

    //at_core_register_test_case(tc_cfg_reg);

    return 0;
}

/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_remove
 ¹¦ÄÜÃèÊö  : tc cfg Çı¶¯ÒÆ³ı
 ÊäÈë²ÎÊı  : struct platform_device* Éè±¸Ö¸Õë
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : Çı¶¯ÒÆ³ı½á¹û
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ26ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
static int tc_cfg_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    at_core_unregister_test_case(tc_cfg_reg);
    kfree(tc_cfg_reg);
    return 0;
}

/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_init
 ¹¦ÄÜÃèÊö  : tc cfg Ä£¿é³õÊ¼»¯
 ÊäÈë²ÎÊı  : ÎŞ
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : Ä£¿é³õÊ¼»¯½á¹û
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ26ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
static int __init tc_cfg_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_cfg_driver);
}
module_init(tc_cfg_init);


/*****************************************************************************
 º¯ Êı Ãû  : tc_cfg_exit
 ¹¦ÄÜÃèÊö  : tc cfg Ä£¿éÍË³ö
 ÊäÈë²ÎÊı  : ÎŞ
 Êä³ö²ÎÊı  : ÎŞ
 ·µ »Ø Öµ  : Ä£¿éÍË³ö½á¹û
 µ÷ÓÃº¯Êı  :
 ±»µ÷º¯Êı  :

 ĞŞ¸ÄÀúÊ·      :
  1.ÈÕ    ÆÚ   : 2015Äê1ÔÂ26ÈÕ
    ×÷    Õß   : w00262566
    ĞŞ¸ÄÄÚÈİ   : ĞÂÉú³Éº¯Êı

*****************************************************************************/
static void __exit tc_cfg_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_cfg_driver);
}
module_exit(tc_cfg_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
