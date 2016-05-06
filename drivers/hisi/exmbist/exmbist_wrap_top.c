/********************************************************************************
 File name  : exmbist_wrap_top.c
 Version    : 1.00
 Author     :
 Description: top level of the exmbist api
              a suite of api interface functions, such as api initialization,
              mbist test run/stop, commands set, blocks config...
********************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include <linux/types.h>
#include <linux/io.h>

#include "soc_exmbist_interface.h"
#include "soc_ddrc_qosb_interface.h"
#include "soc_dmss_interface.h"
#include "soc_ddrc_dmc_interface.h"

#include "exmbist_api.h"
#include "exmbist_wrap_top.h"
#include "exmbist_test.h"

extern struct exm_fsm_state g_exm_cur_fsm_state;

#define MAX_CMD_PARAM_LENGTH  12

extern DDR_TYPE_EMUM get_ddr_version(void);
extern exmbist_uint32 exmbist_init(ExmCtx *ctx);
extern exmbist_uint32 exmbist_algo_run(ExmCtx *ctx, exmbist_uint32 algo_id, exmbist_uint32 loop_cnt);
extern exmbist_uint32 exmbist_set_cmd(ExmCtx *ctx, exmbist_uint32 cmd_id, void *cmd_para);
extern exmbist_uint32 exmbist_stop(ExmCtx * ctx);

unsigned int ap_addr_to_exm_addr(unsigned int addr);
int exmbist_init_flag = 0;

/*exmbist实例，代表austin exmbist的所有配置*/
ExmCtx g_austin_exmbist;
/*命令参数记录全局数组*/
static unsigned int g_cmd_param[MAX_CMD_PARAM_LENGTH];
//static unsigned int g_dmss_limiter_temp;
/*
mem_row	6:4	RW	0x2	"单片SDRAM行地址位宽配置。
	000：11 bit；
	001：12 bit；
	010：13 bit；
	011：14 bit；
	100：15 bit；
	101：16 bit；
	110: 17 bit；
	111: 18 bit；"
mem_col	2:0	RW	0x2	"单片SDRAM列地址位宽配置。
	000：8 bit；
	001：9 bit；
	010：10 bit；
	011：11 bit；
	100：12 bit；
	其它保留。注意：DDRC不支持col地址小于8的器件（即32bit位宽，总容量64Mbit的LPDDR2器件）。"
*/
#if 0
ddr_density_rbc_str ddr_desity_rbc[DDR_TYPE_LPDDR4+1][MAX_DDR_DENSITY]= {
	/*lpddr3*/
	{{0x6, 512,  8, 3, 2},	/*4Gb, 512MB*/
	 {0xe, 768,  8, 4, 2},	/*6Gb*/
	 {0x7, 1024, 8, 4, 2},	/*8Gb*/
	 {0xD, 1536, 8, 4, 3},	/*12Gb*/
	 {0x8, 2048, 8, 4, 3},	/*16Gb*/
	},
	/*lpddr4*/
	{{0x0, 256, 8, 3, 2}, /*2Gb*/
	 {0x1, 384, 8, 4, 2}, /*3Gb*/
	 {0x2, 512, 8, 4, 2}, /*4Gb*/
	 {0x3, 768, 8, 5, 2}, /*6Gb*/
	 {0x4, 1024, 8, 5, 2},/*8Gb*/
	}
};
#endif

/*default config, [sub_sys][dmc_num]*/
ddr_rank_info_str ddr_rank_cfg[DDRC_NUM_MAX][DMC_NUM_MAX]={{{1,{{0,0,0,0,0},{0,0,0,0,0}}},{0,{{0,0,0,0,0},{0,0,0,0,0}}}},
                                                           {{1,{{0,0,0,0,0},{0,0,0,0,0}}},{0,{{0,0,0,0,0},{0,0,0,0,0}}}}
                                                          };

DDR_TYPE_EMUM get_ddr_version()
{
	unsigned int reg_val;
	static unsigned int ddr_type = 0xffffffff;
	
	if (ddr_type == 0xffffffff) 
	{
		reg_val = readl(SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR(DDR_REG_DMC(exm_get_reg_base(), 0, 0)));
		ddr_type = reg_val & 0xf;
	}
	return ddr_type;
}

/*
控制器Rank配置。
00：1个rank；
01：2个rank；
10：3个rank；
11：4个rank。
*/
void exm_ddr_fill_rank_info(unsigned int subsys_max, unsigned int dmc_max)
{
	unsigned int rank_max_num;
	unsigned int subsy_num;
	unsigned int dmc_num;
	unsigned int rank_num;

	for (subsy_num = 0; subsy_num < subsys_max; subsy_num++)
	{
		for(dmc_num = 0; dmc_num < dmc_max; dmc_num++)   //LPDDR3 一个DDRC对接一个DMC
		{
			rank_max_num = (readl(SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num)))>> 20) & 0x3;	
			printk("there is %d rank in one dmc\n", rank_max_num+1);
			ddr_rank_cfg[subsy_num][dmc_num].rank_num = rank_max_num+1;
			for (rank_num = 0; rank_num < rank_max_num+1; rank_num++)
			{
				printk("subsy_num %d  dmc_num %d  rank_num %d\n", subsy_num, dmc_num, rank_num);
				
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].bank = 8;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].row     
					= readl((SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num), rank_num)))>> 4 & 0x7;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].col    
					= readl(SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num), rank_num))& 0x7;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].density = exm_ddr_density_get();
				printk("row %d  col %d  density 0x%x\n", ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].row, ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].col,
											ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].density);
			}
		}
	}
}

void exm_ddr_self_adapter(void)
{
	unsigned int ddr_type = get_ddr_version();
	unsigned int dmc_max = (ddr_type == DRAM_TYPE_LPDDR3) ? 1:2;
	unsigned int rank_max_num;
	unsigned int subsy_num;
	unsigned int dmc_num;
	unsigned int rank_num;
	
	printk("ddr type is %s dmc_max %d\n",(ddr_type == DRAM_TYPE_LPDDR3) ? "lpddr3" :"lpddr4", dmc_max);

	for (subsy_num = 0; subsy_num < DDRC_NUM_MAX; subsy_num++)
	{
		for(dmc_num = 0; dmc_num < dmc_max; dmc_num++)   //LPDDR3 一个DDRC对接一个DMC
		{
			rank_max_num = (readl(SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num)))>> 20) & 0x3;	
			ddr_rank_cfg[subsy_num][dmc_num].rank_num = rank_max_num+1;
			printk("there is %d rank in one dmc_num %d\n", rank_max_num+1, dmc_num);
			for (rank_num = 0; rank_num < rank_max_num+1; rank_num++)
			{
				printk("subsy_num %d  dmc_num %d  rank_num %d\n", subsy_num, dmc_num, rank_num);
				//ddr_rank_cfg[subsy_num][dmc_num].rank_num = rank_num;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].bank = 8;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].row     
					= readl((SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num), rank_num)))>> 4 & 0x7;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].col    
					= readl(SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(DDR_REG_DMC(exm_get_reg_base(), subsy_num, dmc_num), rank_num))& 0x7;
				ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].density = exm_ddr_density_get();
				printk("row %d  col %d  density 0x%x\n", ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].row, ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].col,
											ddr_rank_cfg[subsy_num][dmc_num].rank_info[rank_num].density);
			}
		}
	}
}

#if 0
unsigned int exm_exmbist_is_done()
{
	exm_drv_get_status(&g_austin_exmbist);

	return g_austin_exmbist.bist_done;
}
#endif	

/*****************************************************************************
 函 数 名  : exmbsit_io_wr_cmd
 功能描述  : exmbist API IO层 写命令接口实现
 输入参数  : ExmCtx * ctx
             exmbist_uint32 cmd
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_wr_cmd (exmbist_uint32 cmd)
{
    volatile SOC_EXMBIST_CMD_ADDR_UNION * cmd_addr_ptr;
    cmd_addr_ptr  = (volatile SOC_EXMBIST_CMD_ADDR_UNION * )SOC_EXMBIST_CMD_ADDR_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    cmd_addr_ptr->value = cmd;
    return 0;
}

/*****************************************************************************
 函 数 名  : exmbsit_io_wr_din
 功能描述  : exmbist API IO层 写数据接口实现
 输入参数  : ExmCtx * ctx
             exmbist_uint32 data
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_wr_din (exmbist_uint32 data)
{
    volatile SOC_EXMBIST_DAT_ADDR_UNION * dat_addr_ptr;
    dat_addr_ptr = (volatile SOC_EXMBIST_DAT_ADDR_UNION *)SOC_EXMBIST_DAT_ADDR_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    dat_addr_ptr->value = data;

    /*no use,to delete warning*/
    dat_addr_ptr = dat_addr_ptr;
    return 0;
}

/*****************************************************************************
 函 数 名  : exmbsit_io_rd_dout
 功能描述  : exmbist API IO层 读数据接口实现
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_rd_dout (void)
{
    volatile SOC_EXMBIST_CMD_ADDR_UNION * cmd_addr_ptr;
    cmd_addr_ptr  = (volatile SOC_EXMBIST_CMD_ADDR_UNION * )SOC_EXMBIST_CMD_ADDR_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    return cmd_addr_ptr->value;
}

/*****************************************************************************
 函 数 名  : exmbsit_io_rd_status
 功能描述  : exmbist API IO层 读状态接口实现
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_rd_status (void)
{
    volatile SOC_EXMBIST_STATUS_UNION * status_ptr;
    status_ptr  = (volatile SOC_EXMBIST_STATUS_UNION * )SOC_EXMBIST_STATUS_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    return status_ptr->value;

}


/*****************************************************************************
 函 数 名  : exm_wrap_fix_init
 功能描述  : 自研wrap IP 初始化固定部分
 输入参数  : ExmCtx *ctx
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
static void  exm_wrap_fix_init(ExmCtx *ctx)
{
    volatile SOC_EXMBIST_PCLK_GATE_UNION *pclk_gate_ptr = NULL;
    volatile SOC_EXMBIST_EN_UNION *en_ptr = NULL;
    volatile SOC_EXMBIST_MUX_SEL_UNION *mux_sel_ptr = NULL;
    volatile SOC_EXMBIST_DRAM_WIDTH_UNION *dram_width_ptr = NULL;
#if 0
    /*close qos_by_pass and rate_adapter*/
    volatile SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION *qosbuf_byp_ptr = NULL;
    volatile SOC_DMSS_ASI_RATE_ADPT_UNION *rate_adpt_ptr = NULL;
    volatile SOC_DMSS_ASI_QOS_LMTR0_UNION *qos_lmtr0_ptr = NULL;
    int i;

    /*2 QoS_buf_bypass*/
    for(i=0;i<2;i++)
    {
        qosbuf_byp_ptr =(volatile SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION *)SOC_DDRC_QOSB_QOSB_BUF_BYP_ADDR(DDR_REG_QOSBUF(exm_get_reg_base(), i));
        qosbuf_byp_ptr->reg.qos_buf_byp = 0x3;
    }
    /*axis5 ra_en ==0*/

    rate_adpt_ptr =(volatile SOC_DMSS_ASI_RATE_ADPT_UNION *)SOC_DMSS_ASI_RATE_ADPT_ADDR(DDR_REG_DMSS(exm_get_reg_base(), 0), 5);
    rate_adpt_ptr->reg.ra_en = 0x0;
    /*close axi 5 dmss limiter*/
    qos_lmtr0_ptr = (volatile SOC_DMSS_ASI_QOS_LMTR0_UNION *)SOC_DMSS_ASI_QOS_LMTR0_ADDR(DDR_REG_DMSS(exm_get_reg_base(), 0),5);
    g_dmss_limiter_temp = qos_lmtr0_ptr->value;
    qos_lmtr0_ptr->value = 0;
#endif
    ctx->ddr_type = get_ddr_version();
    ctx->dmc_num_max = (ctx->ddr_type == DRAM_TYPE_LPDDR4)? 2:1;
    ctx->subsys_num_max =2;

    /*update in exm_wrap_adapt_init latter */
    ctx->density = ddr_rank_cfg[0][0].rank_info[0].density;/*density of all rank is always same*/
    ctx->rank_num_max = (ctx->ddr_type == DRAM_TYPE_LPDDR4)? 1 : 2;

    pclk_gate_ptr = (volatile SOC_EXMBIST_PCLK_GATE_UNION *)SOC_EXMBIST_PCLK_GATE_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    en_ptr = (volatile SOC_EXMBIST_EN_UNION *)SOC_EXMBIST_EN_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    mux_sel_ptr = (volatile SOC_EXMBIST_MUX_SEL_UNION *)SOC_EXMBIST_MUX_SEL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    dram_width_ptr = (volatile SOC_EXMBIST_DRAM_WIDTH_UNION *)SOC_EXMBIST_DRAM_WIDTH_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));

    pclk_gate_ptr->reg.apb_gt_en = 0x1;
    en_ptr->reg.cfg_exmbist_en= 0x1;
    mux_sel_ptr->reg.mux_sel = 0x0;
    dram_width_ptr->reg.cfg_dram_width =(ctx->ddr_type == DRAM_TYPE_LPDDR4)?0:1;// lpddr3 32bit 1; lpddr4 16bit 0

    return;
}

/*****************************************************************************
 函 数 名  : exm_wrap_adapt_init
 功能描述  : 自研wrap IP 初始化变化部分
 输入参数  : ExmCtx *ctx
             int subsys_num
             int dmc_num
             int rank_num
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
void  exm_wrap_adapt_init(ExmCtx *ctx,int subsys_num,int dmc_num,int rank_num)
{
    volatile SOC_EXMBIST_RANK_VOL_UNION *rank_vol_ptr = NULL;
    volatile SOC_EXMBIST_TEST_RANK_UNION *test_rank_ptr = NULL;
    volatile SOC_EXMBIST_CHAN_INFO_UNION *chan_info_ptr = NULL;
    unsigned int row,col;
		
    rank_vol_ptr = (volatile SOC_EXMBIST_RANK_VOL_UNION *)SOC_EXMBIST_RANK_VOL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()),rank_num);
    test_rank_ptr = (volatile SOC_EXMBIST_TEST_RANK_UNION *)SOC_EXMBIST_TEST_RANK_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    chan_info_ptr = (volatile SOC_EXMBIST_CHAN_INFO_UNION *)SOC_EXMBIST_CHAN_INFO_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));

    /*update*/
    ctx->density = ddr_rank_cfg[subsys_num][dmc_num].rank_info[rank_num].density;
    ctx->rank_num_max = ddr_rank_cfg[subsys_num][dmc_num].rank_num;

    row = ddr_rank_cfg[subsys_num][dmc_num].rank_info[rank_num].row;
    col = ddr_rank_cfg[subsys_num][dmc_num].rank_info[rank_num].col;

    /*bank row col adapt by rank*/
    ctx->cfg_bank_bits = 3;
    ctx->cfg_row_bits =row + 11;
    ctx->cfg_col_bits =col + 8 - ((ctx->ddr_type == DRAM_TYPE_LPDDR4) ? 4:3);
    //EXMBIST_info("ctx->cfg_row_bits =0x%x,ctx->cfg_col_bits=0x%x,ctx->cfg_bank_bits=0x%x \n",ctx->cfg_row_bits,ctx->cfg_col_bits,ctx->cfg_bank_bits);

    /*容量adapt配置*/
    rank_vol_ptr->reg.cfg_col_bit = col;
    rank_vol_ptr->reg.cfg_row_bit = row;
    rank_vol_ptr->reg.cfg_bank_bit = 1;

    test_rank_ptr->reg.cfg_test_rank = rank_num;

    if(ctx->ddr_type == DRAM_TYPE_LPDDR4)
    {
        //lpddr4
        chan_info_ptr->reg.cfg_chan_type = 0x1;
        chan_info_ptr->reg.cfg_test_chan = (subsys_num << 1) | dmc_num;

    }
    else
    {
        //lpddr3
        chan_info_ptr->reg.cfg_chan_type = 0x0;//4
        chan_info_ptr->reg.cfg_test_chan = subsys_num;
    }

    /*自适应扫描地址*/
	//phy_min_addr = exm_get_exmbist_addr_min();
	//phy_max_addr = exm_get_exmbist_addr_max();
    ctx->cfg_min_addr = exm_get_exmbist_addr_min();
	//ctx->cfg_max_addr = exm_get_exmbist_addr_min()+ 0x2000;
	ctx->cfg_max_addr = exm_get_exmbist_addr_max() - 1;  //512M/4/256=

	//exmbist_max_addr_hole = (1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits))-(1<<(ctx->cfg_row_bits-2+ctx->cfg_col_bits+ctx->cfg_bank_bits))-1;
	//exmbist_max_addr1 = (1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits)) - 1;
    //printk(KERN_ERR "exmbist_max_addr_hole=0x%x exmbist_max_addr10x%x \n",exmbist_max_addr_hole, exmbist_max_addr1);

#if 0	
    if(ctx->density == 0xe){
        /*rank扫描，地址空洞问题*/
        ctx->cfg_max_addr = (1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits))-(1<<(ctx->cfg_row_bits-2+ctx->cfg_col_bits+ctx->cfg_bank_bits))-1;
    }
    else{
        ctx->cfg_max_addr = (1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits)) - 1;
    }
#endif

    //printk(KERN_ERR "ctx->density=0x%x ctx->cfg_min_addr =0x%x  ctx->cfg_max_addr =0x%x \n",ctx->density, ctx->cfg_min_addr, ctx->cfg_max_addr);

    return;
}

/*****************************************************************************
 函 数 名  : exm_addr_to_ap_addr
 功能描述  : exmbist 地址转化为ap看到的地址
 输入参数  : unsigned int addr
 输出参数  : 无
 返 回 值  : unsigned int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_addr_to_ap_addr(unsigned int addr)
{
	/*获取当前测试的rank,bank,col,dmc,subsys,然后重组地址*/
	unsigned int col, row, bank, rank,channel,width, intlv;
	unsigned int ap_addr;
	volatile SOC_EXMBIST_RANK_VOL_UNION* embist_rank_vol;
	volatile SOC_EXMBIST_CHAN_INFO_UNION* exmbist_chan_info;
	unsigned int bank_addr,col_addr,row_addr;
	
	rank = readl(SOC_EXMBIST_TEST_RANK_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7;
	embist_rank_vol = \
		(SOC_EXMBIST_RANK_VOL_UNION*)SOC_EXMBIST_RANK_VOL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()), rank);
	col = embist_rank_vol->reg.cfg_col_bit + 8;
	row = embist_rank_vol->reg.cfg_row_bit + 11;
	bank = embist_rank_vol->reg.cfg_bank_bit + 2;
	width = 1<<(readl(SOC_EXMBIST_DRAM_WIDTH_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x1);

	exmbist_chan_info = \
		(SOC_EXMBIST_CHAN_INFO_UNION*)SOC_EXMBIST_CHAN_INFO_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
	channel = 1<<(exmbist_chan_info->reg.cfg_chan_type);

	intlv = (readl(SOC_EXMBIST_ADDR_INTLV_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7) + 8 -1;

	//printk("[addr]row 0x%x; col 0x%x; bank 0x%x; intlv 0x%x; width 0x%x;", row, col, bank, intlv, width);
      
	bank_addr = addr&((1<<bank) - 1);
	col_addr = (addr>>bank) & ((1<<(col- (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3))) -1);
	row_addr = (addr>>(bank+col- (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3))) & ((1<<row)-1);

	ap_addr = ((rank << (row+bank+col)) | \
	          (row_addr << (bank+col)) | \
	          (bank_addr << col) | \
	          (col_addr << (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3)) \
	          )<<(width);
	/*低位不变，中间插入channel,高位左移*/
	ap_addr = (ap_addr&((1<<intlv)-1)) |  \
	          (exmbist_chan_info->reg.cfg_test_chan << intlv) |\
	          ((ap_addr & ~((1<<intlv)-1))<<channel);
	return ap_addr;
}

#if 0
unsigned int ap_addr_to_exm_addr(unsigned int ap_addr)
{
	unsigned int ap_addr_low, ap_addr_high;
	unsigned int intlv, channel_bit, width, col, row, bank, rank;
	unsigned int exmbist_addr;
	unsigned int row_addr, bank_addr, col_addr;

	printk("[addr]ap_addr 0x%x;\n", ap_addr);
	intlv = (readl(SOC_EXMBIST_ADDR_INTLV_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7) + 8 -1;

	ap_addr_low = ap_addr&((1<<intlv)-1);
	volatile SOC_EXMBIST_CHAN_INFO_UNION* exmbist_chan_info = \
		(SOC_EXMBIST_CHAN_INFO_UNION*)SOC_EXMBIST_CHAN_INFO_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
	channel_bit = 1<<(exmbist_chan_info->reg.cfg_chan_type);
	ap_addr_high = (ap_addr & ~((1<<intlv)-1))>> channel_bit;
	exmbist_addr = ap_addr_low | ap_addr_high;

	printk("[addr]channel_bit 0x%x; ap_addr_high 0x%x; ap_addr_low 0x%x; exmbist_addr 0x%x\n", channel_bit, ap_addr_high, ap_addr_low, exmbist_addr);

	width = 1<<(readl(SOC_EXMBIST_DRAM_WIDTH_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x1);
	exmbist_addr = exmbist_addr>>(width);

	/*col row bank 为器件概念 */	
	rank = readl(SOC_EXMBIST_TEST_RANK_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7;
	volatile SOC_EXMBIST_RANK_VOL_UNION* embist_rank_vol = \
		(SOC_EXMBIST_RANK_VOL_UNION*)SOC_EXMBIST_RANK_VOL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()), rank);
	col  = embist_rank_vol->reg.cfg_col_bit + 8;
	row  = embist_rank_vol->reg.cfg_row_bit + 11;
	bank = embist_rank_vol->reg.cfg_bank_bit + 2;
	
	printk("[addr]row 0x%x; col 0x%x; bank 0x%x; intlv 0x%x; width 0x%x;\n", row, col, bank, intlv, width);

	rank      = (exmbist_addr >> (row+bank+col))& 0x1;
	row_addr  = exmbist_addr >> (bank+col)& ((1<<row) - 1);
	bank_addr = exmbist_addr >> col &((1<<bank) - 1);
	col_addr  = exmbist_addr & ((1<<col) - 1);
	col_addr  = col_addr >> (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3) & ((1<<(col- (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3))) -1);

	printk("[addr]row_addr 0x%x; col_addr 0x%x; bank_addr 0x%x\n", row_addr, col_addr, bank_addr);

	exmbist_addr = col_addr | bank_addr | row_addr;

	return exmbist_addr;	
}
#endif

unsigned int ap_addr_to_exm_addr(unsigned int ap_addr)
{
	unsigned int ap_addr_low, ap_addr_high;
	unsigned int intlv, channel_bit, width, col, row, bank, rank;
	unsigned int exmbist_addr;
	unsigned int row_addr, bank_addr, col_addr;

	volatile SOC_EXMBIST_CHAN_INFO_UNION* exmbist_chan_info;
	volatile SOC_EXMBIST_RANK_VOL_UNION* embist_rank_vol;
	
	//printk("[addr]ap_addr 0x%x;\n", ap_addr);
	intlv = (readl(SOC_EXMBIST_ADDR_INTLV_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7) + 8 -1;

	ap_addr_low = ap_addr&((1<<intlv)-1);
	exmbist_chan_info = \
		(SOC_EXMBIST_CHAN_INFO_UNION*)SOC_EXMBIST_CHAN_INFO_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
	channel_bit = 1<<(exmbist_chan_info->reg.cfg_chan_type);
	//ap_addr_high = (ap_addr & ~((1<<intlv)-1))>> channel_bit;
	ap_addr_high = (ap_addr>>channel_bit) & (~((1<<intlv)-1));
	exmbist_addr = ap_addr_low | ap_addr_high;

	//printk("[addr]channel_bit 0x%x; ap_addr_high 0x%x; ap_addr_low 0x%x; exmbist_addr 0x%x\n", channel_bit, ap_addr_high, ap_addr_low, exmbist_addr);

	width = 1<<(readl(SOC_EXMBIST_DRAM_WIDTH_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x1);
	exmbist_addr = exmbist_addr>>(width);

	/*col row bank 为器件概念 */	
	rank = readl(SOC_EXMBIST_TEST_RANK_ADDR(DDR_REG_EXMBIST(exm_get_reg_base())))&0x7;
	embist_rank_vol = \
		(SOC_EXMBIST_RANK_VOL_UNION*)SOC_EXMBIST_RANK_VOL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()), rank);
	col  = embist_rank_vol->reg.cfg_col_bit + 8;
	row  = embist_rank_vol->reg.cfg_row_bit + 11;
	bank = embist_rank_vol->reg.cfg_bank_bit + 2;
	
	//printk("[addr]row 0x%x; col 0x%x; bank 0x%x; intlv 0x%x; width 0x%x;\n", row, col, bank, intlv, width);

	rank      = (exmbist_addr >> (row+bank+col))& 0x1;
	row_addr  = exmbist_addr >> (bank+col)& ((1<<row) - 1);
	bank_addr = exmbist_addr >> col &((1<<bank) - 1);
	col_addr  = exmbist_addr >> (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3) & ((1<<(col- (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3))) -1);

	bank_addr = bank_addr;
	col_addr  = col_addr << bank;
	row_addr  = row_addr << (bank+col- (get_ddr_version()==DRAM_TYPE_LPDDR4 ? 4:3));
 
	//printk("[addr]row_addr 0x%x; col_addr 0x%x; bank_addr 0x%x\n", row_addr, col_addr, bank_addr);

	exmbist_addr = row_addr | bank_addr | col_addr;

	printk("exmbist_addr 0x%x\n", exmbist_addr);
	return exmbist_addr;	
}


unsigned int exm_wait_bist_pass(void)
{
	unsigned int ret;
	
	ret = exm_util_wait_bist_pass(&g_austin_exmbist);

	return ret;	
}

/*****************************************************************************
 函 数 名  : exm_api_pra_num_max
 功能描述  : 查找cmd需要的配置参数个数
 输入参数  : unsigned int  cmd_id
 输出参数  : 无
 返 回 值  : unsigned int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
static unsigned int exm_cmd_pra_num_max(unsigned int  cmd_id)
{

    unsigned int num;
    switch(cmd_id){
        case EXMBIST_CMD_SET_REPEAT_CNT:
        case EXMBIST_CMD_SET_DIAG_CNT:
        case EXMBIST_CMD_SET_LOOP_EN:
        case EXMBIST_CMD_SET_ADDR_PRBS_SEED:
        case EXMBIST_CMD_SET_GLOBAL_INORDER:
        case EXMBIST_CMD_SET_ALT_FIX_ADDR:
        case EXMBIST_CMD_SET_ADDR_PRBS_BIT_INV:
        case EXMBIST_CMD_SET_SAME_BASE_PAT:
        case EXMBIST_CMD_SET_TEST_SUBSYS_DMC_RANK:
            num = 1;
            break;
        case EXMBIST_CMD_SET_ADDR_RANGE:
        case EXMBIST_CMD_LOAD_INST:
        case EXMBIST_CMD_SET_BANK_MAP:
        case EXMBIST_CMD_SEL_PRBS:
            num = 2;
            break;
        case EXMBIST_CMD_SET_ROW_COL_BANK_BITS:
        case EXMBIST_CMD_SET_ITL:
            num = 3;
            break;
        case EXMBIST_CMD_SET_BASE_PAT:
        case EXMBIST_CMD_SET_ALT_PAT:
        case EXMBIST_CMD_SET_COMP_MSK:
            num = 8;
            break;
        case EXMBIST_CMD_SET_ADDR_CNT:
            num =12;
            break;
        default:
            num =0;
            break;
    }
    return num;
}

/*****************************************************************************
 函 数 名  : exm_api_set_cmd
 功能描述  : 配置命令接口
 输入参数  : unsigned int  cmd_id       配置命令编码
             unsigned int  param_value  配置参数i，重复该函数调用时i递增
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_set_cmd(unsigned int  cmd_id,unsigned int  param_value)
{
    static unsigned int cmd_param_cnt = 0;/*cmd 参数计数器*/
    unsigned int uiret = EXMBIST_OK;
    unsigned int pra_num_max = exm_cmd_pra_num_max(cmd_id);

    /*无需参数的cmd,直接下发*/
    if(0 == pra_num_max)
    {
        uiret = exmbist_set_cmd(&g_austin_exmbist,cmd_id,&g_cmd_param);
        EXMBIST_info("cmd without cfg have finished \n");
        return uiret;
    }

    cmd_param_cnt++;
    g_cmd_param[cmd_param_cnt-1] = param_value;

    /*带参cmd,参数准备就绪,可以下发*/
    if(cmd_param_cnt == pra_num_max)
    {
        /*用户自定义命令集*/
        /*SET_SAME_BASE_PAT 需要转定义cmd*/
        if(cmd_id == EXMBIST_CMD_SET_SAME_BASE_PAT)
        {
            /*带1个参数*/
            exm_util_init_array(g_cmd_param,MAX_CMD_PARAM_LENGTH,g_cmd_param[0]);
            uiret = exmbist_set_cmd(&g_austin_exmbist,EXMBIST_CMD_SET_BASE_PAT,&g_cmd_param);
        }
        /*SET_TEST_SUBSYS_DMC_RANK,切换sybsys/dmc/rank*/
        else if(cmd_id == EXMBIST_CMD_SET_TEST_SUBSYS_DMC_RANK)
        {
            /*带1个参数*/
            exm_wrap_adapt_init(&g_austin_exmbist,(g_cmd_param[0]&0xf00)>>8,(g_cmd_param[0]&0xf0)>>4,g_cmd_param[0]&0xf);
        }
        else
        {
            /*exmbist IP 命令集*/
            uiret = exmbist_set_cmd(&g_austin_exmbist,cmd_id,&g_cmd_param);
        }
        EXMBIST_info("cmd with %d params cfg have finished \n",pra_num_max);
        cmd_param_cnt =0;
        exm_util_init_array(g_cmd_param,MAX_CMD_PARAM_LENGTH,0x0);
        return uiret;
    }
    else
    {
        EXMBIST_info("you need to cfg %d params more\n",pra_num_max-cmd_param_cnt);
    }

    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_api_init
 功能描述  : 初始化函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_init(void)
{
    unsigned int uiret = EXMBIST_OK;

	if (exmbist_init_flag)
	{
		printk("exmbist already init\n");
		return EXMBIST_OK;
	}

	exmbist_init_flag = 1;
	
    exm_wrap_fix_init(&g_austin_exmbist);
    uiret = exmbist_init(&g_austin_exmbist);

    /*默认初始化通道0,DMC0,rank0*/
    exm_wrap_adapt_init(&g_austin_exmbist,0,0,0);

    return uiret;
}
/*****************************************************************************
 函 数 名  : exm_algo_run
 功能描述  : 算法运行接口
 输入参数  : unsigned int algo_id   
             unsigned int loop_cnt  
 输出参数  : 无
 返 回 值  : unsigned int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_algo_run(unsigned int algo_id, unsigned int loop_cnt)
{
    unsigned int uiret = EXMBIST_OK;
    uiret = exmbist_algo_run(&g_austin_exmbist,algo_id,loop_cnt);
    return uiret;
}
/*****************************************************************************
 函 数 名  : exm_rank_algo_run
 功能描述  :  单rank算法运行函数
 输入参数  : unsigned int algo_id   定义指定运行了哪种算法
             unsigned int loop_cnt  算法运行的次数
             sub_dmc_rank           当前算法在哪个subsys/dmc/rank执行
                                    bit[3:0]rank标号，bit[7:4]dmc标号，bit[13:8]subsys标号
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_rank_algo_run(unsigned int algo_id, unsigned int loop_cnt,unsigned int sub_dmc_rank)
{
    unsigned int uiret = EXMBIST_OK;
    unsigned int subsys_num,dmc_num,rank_num,loop_counter;

    rank_num = sub_dmc_rank &0xf;
    dmc_num  = (sub_dmc_rank &0xf0)>>4;
    subsys_num  = (sub_dmc_rank &0xf00)>>8;

    loop_counter =(loop_cnt == 0)?1:loop_cnt;/*循环次数保证大于或等于1*/
    printk(KERN_ERR "algo_id:0x%x loop:%d subsys:%d dmc:%d rank:%d\n",algo_id,loop_counter,subsys_num,dmc_num,rank_num);

    exm_wrap_adapt_init(&g_austin_exmbist,subsys_num,dmc_num,rank_num);

    uiret = exmbist_algo_run(&g_austin_exmbist,algo_id,loop_counter);
    
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_all_space_algo_run
 功能描述  : 全空间算法运行函数
 输入参数  : unsigned int algo_id
             unsigned int loop_cnt
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_all_space_algo_run(unsigned int algo_id, unsigned int loop_cnt)
{
    unsigned int uiret = EXMBIST_OK;
    unsigned int subsys_num,dmc_num,rank_num;
    unsigned int sub_dmc_rank;
    ExmCtx *ctx=&g_austin_exmbist;

    for (subsys_num = 0; subsys_num < ctx->subsys_num_max; subsys_num++) 
    {
        for (dmc_num=0; dmc_num < ctx->dmc_num_max; dmc_num++)
        {
		    for(rank_num=0; rank_num<ddr_rank_cfg[subsys_num][dmc_num].rank_num ; rank_num++) 
		    {
		    	if (rank_num > 0)
		    	{
					break;
				}
				sub_dmc_rank = rank_num | (dmc_num<<4)|(subsys_num<<8);
				uiret = exm_rank_algo_run(algo_id,loop_cnt,sub_dmc_rank);
				if(uiret != EXMBIST_OK)
				{
					return uiret;
				}
			}
        }
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_close
 功能描述  : exmbist关闭函数
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int exm_close(void)
{
    volatile SOC_EXMBIST_EN_UNION *en_ptr = NULL;
    volatile SOC_EXMBIST_MUX_SEL_UNION *mux_sel_ptr = NULL;
    unsigned int uiret = EXMBIST_OK;

	if (!exmbist_init_flag)
	{
		printk("exmbist not init\n");
		return EXMBIST_OK;
	}
		
    uiret = exmbist_stop(&g_austin_exmbist);

    en_ptr = (volatile SOC_EXMBIST_EN_UNION *)SOC_EXMBIST_EN_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));
    mux_sel_ptr = (volatile SOC_EXMBIST_MUX_SEL_UNION *)SOC_EXMBIST_MUX_SEL_ADDR(DDR_REG_EXMBIST(exm_get_reg_base()));

    en_ptr->reg.cfg_exmbist_en= 0x0;
    mux_sel_ptr->reg.mux_sel = 0x1;

	exmbist_init_flag = 0;
	
    return uiret;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
