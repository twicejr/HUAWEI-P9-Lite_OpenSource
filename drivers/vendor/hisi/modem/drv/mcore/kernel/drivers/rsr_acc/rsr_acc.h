#ifndef __RSR_ACC__
#define __RSR_ACC__
struct rsr_acc_bd_s
{
    struct
    {
    	unsigned int bd_flow     :2;/*[0]:save_en:1表示在save流程中执行该bd，
    													0表示save流程中跳过该bd
    										[1]:restore_en:1表示在restore流程中执行该bd，
    													0表示restore流程中跳过该bd*/
    	unsigned int reserved_1	 :2;/*[2-3]*/
    	unsigned int bd_oper     :3;/*[4-6]:   0:save ；从reg_baddr-->ddr_baddr
    										1:restore ；从ddr_baddr--->reg_baddr
    										2:save&restore:save flow 从reg_baddr-->ddr_baddr;restore flow 从ddr_baddr--->reg_baddr
    										3:~restore
    										4:wait*/
    	unsigned int reserved_2  :9;/*[7-15]*/
    	unsigned int bd_type     :2;/*[16-17]: 
									1:连续多个寄存器操作
									2:单个寄存器操作
									other:reserved
									*/
		unsigned int reserved_3  :14;/*[18-31]*/
																	
    }cfg;
	u32* ddr_baddr;/*要保存寄存器内容到目的地址的基地址*/
	u32* reg_baddr;/*要保存的寄存器基地址*/
	unsigned int bd_flow_operation;/*bd_type=1,表示连续操作的寄存器长度
									bd_type=2,表示在取反restore时起作用，表示bit_mask*/
	
}__attribute__((aligned(8)));

#define CTRL_OFFSET(i)          ((i)*0x80+0x80) /*通道控制寄存器                       */
#define BD_BASE_OFFSET(i)       ((i)*0x80+0x84) /*bd基地址配置寄存器              */ 
#define BD_LEN_OFFSET(i)        ((i)*0x80+0x88) /*bd长度置寄存器                          */ 
#define SR_STATUS_OFFSET(i)     ((i)*0x80+0x8C) /*bd保存恢复状态寄存器         */ 
#define DMA_CTRL_OFFSET          0x0             /*DMA 状态控制寄存器               */
#define INT_STATUS_OFFSET        0x8             /*通道状态存器                            */
#define INT_MASK_OFFSET          0xC             /*通道状态取反寄存器           */
#define INT_MSTATUS_OFFSET       0x10            /*取反后的通道状态寄存器*/
#define DEBUG_STATE_OFFSET       0x14            /*bd及数据处理状态寄存器  */
enum{
	RSR_ACC_CHANNEL_0,
	RSR_ACC_CHANNEL_1,
	RSR_ACC_CHANNEL_2,
	RSR_ACC_CHANNEL_3,
	RSR_ACC_CHANNEL_MAX,
};

enum rsracc_flow_e{
	suspend_flow=0x1,
	resume_flow =0x2,
};
/*RSRACC模块维护的最大bd个数*/
#define MAX_RSR_ACC_BD_CNT 250


#endif
