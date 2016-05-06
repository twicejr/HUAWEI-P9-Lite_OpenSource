//#include "hdlcv200_frm_def_test_bbit.h"
#include "sre_typedef.h"
#include "hdlc.h"
//#define _UNIT_DEBUG
//********************************************************
//    define for framer
//********************************************************
#define IP_OR_PPP 0 //0:IP mode; 1:PPP mode
#define FRM_INFO_LEN_MAX_VALUE 1500
#define FRM_IN_LLI_1DOR2D_VALUE 0//0
#define FRM_IN_MAINLLI_NUM 3//2//1//3
#define FRM_IN_SUBLLI_NUM 1//3//1
#define FRM_OUT_SEGMENT_NUM 1//9//1
//********************************************************
//    define for deframer
//********************************************************
#define DEF_IN_LLI_NUM 3
#define DEF_IN_PKT_LEN_MAX_VALUE 1536
#define	DEF_OUT_SPC_DEP_VALUE 3000
#define DEF_RPT_DEP_VALUE 64//40


int hdlcv200_frm_def_test_bbit(UINT32 SRC_ADDR_HDLC,UINT32 DES_ADDR_HDLC)
{	
#define  E_FRM_RAW_DATA_ADDR				(SRC_ADDR_HDLC + 0x00000)
#define  E_FRM_CHECK_DATA_ADDR			(DES_ADDR_HDLC + 0x00000)
#define  E_FRM_OUT_SPC_ADDR				(DES_ADDR_HDLC + 0x00100)
#define  E_FRM_IN_MAIN_LLI_ADDR			(SRC_ADDR_HDLC + 0x00100)
#define  E_FRM_IN_SUB_LLI_ADDR			(SRC_ADDR_HDLC + 0x00130)
#define  E_FRM_OUT_LLI_ADDR				(SRC_ADDR_HDLC + 0x00180)
#define  E_FRM_RPT_ADDR					(SRC_ADDR_HDLC + 0x001D0)

#define  E_DEF_RAW_DATA_ADDR				(SRC_ADDR_HDLC + 0x00200)
#define  E_DEF_CHECK_DATA_ADDR			(DES_ADDR_HDLC + 0x00400)
#define  E_DEF_OUT_SPC_ADDR				(DES_ADDR_HDLC + 0x00500)
#define  E_DEF_IN_LLI_ADDR				(SRC_ADDR_HDLC + 0x00300)
#define  E_DEF_RPT_ADDR					(SRC_ADDR_HDLC + 0x00380)



	UINT32 def_over_first=0x0;
	UINT32 i, j, n;
	UINT8 k, m;
	UINT32 hdlc_prior_ctrl=0x0;
	UINT32 axireq_timeout_en;
	UINT32 axireq_timeout_value;
	UINT32 prior_timeout_ctrl_value;
//********************************************************
//    variable for framer
//********************************************************	
//	UINT32 frm_inputdata;
//	UINT32 frm_checkdata;
	UINT32 frm_e_num=0;
	UINT32 frm_raw_data_addr = E_FRM_RAW_DATA_ADDR+8;
	UINT32 frm_check_data_addr = E_FRM_CHECK_DATA_ADDR+4;
	UINT32 frm_protocol;
	UINT32 frm_raw_data_total_len;
	UINT32 frm_residue0;
	UINT32 frm_in_mainlli_num_min;
	UINT32 frm_in_mainlli_num;
	UINT32 frm_in_pkt_len_array[FRM_IN_MAINLLI_NUM]={0x1c,0x1c,0x1c};
	UINT32 frm_in_pkt_len;
	UINT32 frm_in_pkt_len_last;
	UINT32	frm_pkt_addr;
	UINT32 frm_sublli_addr;
	UINT32 frm_pkt_or_sublli_addr;
	UINT32	frm_blk_addr;
	UINT32 frm_in_blk_len;
	UINT32 frm_in_blk_len_last;
	UINT32	frm_out_addr;
	UINT32	frm_out_segment_dep;
	UINT32	frm_out_segment_dep_last;
	
	
	UINT32 frm_acfc, frm_pfc;
	UINT32 frm_cfg_value;
	UINT32 frm_accm;
	
	UINT32 frm_stat;
	UINT32 hdlc_frm_raw_int;
    UINT32 hdlc_frm_int_status;	
	UINT32 frm_vld_num;
	UINT32 frm_out_seg_num;	
	UINT32 frm_report_addr;
	UINT32 frm_report_value;
	UINT32 frm_output_addr;
	UINT32 frm_outlli_addr;
	UINT32 frm_vld_frm_length[40];
	UINT32 frm_out_one_len;
	UINT32 frm_check_data_one_len;
	
//********************************************************
//    variable for deframer
//********************************************************	
	
//	UINT32 def_inputdata;
//	UINT32 def_checkdata;
	UINT32 def_e_num = 0;
	UINT32 def_raw_data_addr = E_DEF_RAW_DATA_ADDR+4;
	UINT32 def_check_data_addr = E_DEF_CHECK_DATA_ADDR+8;
	UINT32 def_raw_data_total_len;
	UINT32 def_residue0;
	UINT32 def_in_lli_num_min;
	UINT32 def_in_lli_num;
	UINT32 def_in_pkt_len;
	UINT32 def_in_pkt_len_last;
	
	UINT32 def_uncompleted_ago;
	UINT32 def_acfc;
	UINT32 def_pfc;
	UINT32 def_cfg_value;
	
	UINT32 def_stat;
	
	UINT32 def_vld_num;
	UINT32 def_report_addr;
	UINT32 def_report_value;
	UINT32 def_output_addr;
	UINT32 def_vld_frm_length[40];
	UINT32 def_out_one_len;
	UINT32 def_protocol[40];
	UINT32 def_check_data_one_len;
	UINT32 hdlc_def_raw_int;
    UINT32 hdlc_def_int_status;
	UINT32 def_in_lli_addr;
	UINT32 def_in_pkt_addr;
    UINT32 def_uncompleted_now;
    UINT32 def_err_ind[7];
	UINT32 def_err_num[7];
	UINT32 def_err_info_0;
	UINT32 def_err_info_1;
	UINT32 def_err_info_2;
	UINT32 def_err_info_3;

//********************************************************
//    data for framer
//********************************************************
	UINT32 dlinput_frm_0[23]={//所有待封装数据连续存储
		0x00000054,//所有待封装数据的总量
		0x0000c021,//封装各帧所用协议
		0x1c000101,//待封装数据起始
		0x02070208,
		0x00000602,
		0x04010000,
		0x0605dc05,
		0x43050000,
		0x23c00403,
		0x1c000101,//待封第2帧
		0x02070208,
		0x00000602,
		0x04010000,
		0x0605dc05,
		0x43050000,
		0x23c00403,
		0x1c000101,//待封第3帧
		0x02070208,
		0x00000602,
		0x04010000,
		0x0605dc05,
		0x43050000,
		0x23c00403
	};
	
	UINT32 dloutput_frm_0[51]={//封装后数据各帧分开存储
		0x0000003d,//封装后一帧长度
		0x237dff7e,//封装后一帧数据起始
		0x217d21c0,
		0x207d217d,
		0x287d3c7d,
		0x277d227d,
		0x227d227d,
		0x207d267d,
		0x207d207d,
		0x217d207d,
		0x257d247d,
		0x7d257ddc,
		0x7d207d26,
		0x43257d20,
		0x247d237d,
		0xd8b123c0,
		0x0000007e,
		0x0000003d,//封装后一帧长度
		0x237dff7e,//封装后一帧数据起始
		0x217d21c0,
		0x207d217d,
		0x287d3c7d,
		0x277d227d,
		0x227d227d,
		0x207d267d,
		0x207d207d,
		0x217d207d,
		0x257d247d,
		0x7d257ddc,
		0x7d207d26,
		0x43257d20,
		0x247d237d,
		0xd8b123c0,
		0x0000007e,
		0x0000003d,//封装后一帧长度
		0x237dff7e,//封装后一帧数据起始
		0x217d21c0,
		0x207d217d,
		0x287d3c7d,
		0x277d227d,
		0x227d227d,
		0x207d267d,
		0x207d207d,
		0x217d207d,
		0x257d247d,
		0x7d257ddc,
		0x7d207d26,
		0x43257d20,
		0x247d237d,
		0xd8b123c0,
		0x0000007e
	};
//********************************************************
//    data for deframer
//********************************************************	
	UINT32 ulinput_def_0[52]={//待解封装数据各帧连续存放
		0x000000cc,//待解封装数据各帧长度总和
		0x0045217e,//待解封装数据起始
		0xc4963e00,
		0x11800000,
		0x7d0ad856,
		0x0ae8005e,
		0x05653748,
		0x003500eb,
		0x948bab2a,
		0x00000137,
		0x00000001,
		0x04000000,
		0x656d6974,
		0x6e697707,
		0x73776f64,
		0x6d6f6303,
		0x00010000,
		0x7e5f5601,
		0x0045217e,//待解第2帧
		0xc4963e00,
		0x11800000,
		0x7d0ad856,
		0x0ae8005e,
		0x05653748,
		0x003500eb,
		0x948bab2a,
		0x00000137,
		0x00000001,
		0x04000000,
		0x656d6974,
		0x6e697707,
		0x73776f64,
		0x6d6f6303,
		0x00010000,
		0x7e5f5601,
		0x0045217e,//待解第3帧
		0xc4963e00,
		0x11800000,
		0x7d0ad856,
		0x0ae8005e,
		0x05653748,
		0x003500eb,
		0x948bab2a,
		0x00000137,
		0x00000001,
		0x04000000,
		0x656d6974,
		0x6e697707,
		0x73776f64,
		0x6d6f6303,
		0x00010000,
		0x7e5f5601
	};
	
	UINT32 uloutput_def_0[54]={//解出各帧存储起始地址Word对齐
		0x0000003e,//解出一帧的参考长度
		0x00002100,//解出一帧的参考协议
		0x3e000045,//解出一帧数据起始
		0x0000c496,
		0xd8561180,
		0xe8007e0a,
		0x6537480a,
		0x3500eb05,
		0x8bab2a00,
		0x00013794,
		0x00000100,
		0x00000000,
		0x6d697404,
		0x69770765,
		0x776f646e,
		0x6f630373,
		0x0100006d,
		0x00000100,
		0x0000003e,//解出一帧的参考长度
		0x00002100,//解出一帧的参考协议
		0x3e000045,//解出一帧数据起始
		0x0000c496,
		0xd8561180,
		0xe8007e0a,
		0x6537480a,
		0x3500eb05,
		0x8bab2a00,
		0x00013794,
		0x00000100,
		0x00000000,
		0x6d697404,
		0x69770765,
		0x776f646e,
		0x6f630373,
		0x0100006d,
		0x00000100,
		0x0000003e,//解出一帧的参考长度
		0x00002100,//解出一帧的参考协议
		0x3e000045,//解出一帧数据起始
		0x0000c496,
		0xd8561180,
		0xe8007e0a,
		0x6537480a,
		0x3500eb05,
		0x8bab2a00,
		0x00013794,
		0x00000100,
		0x00000000,
		0x6d697404,
		0x69770765,
		0x776f646e,
		0x6f630373,
		0x0100006d,
		0x00000100
	};
	//cacheDisable(0);
	//cacheDisable(1);/*需要确认此处是否需要，zuofenghua*/
//********************************************************
//    lli for framer
//********************************************************	
	for(i=0;i<23;i++)
	{
		set32(E_FRM_RAW_DATA_ADDR+4*i,dlinput_frm_0[i]);
	}
	
	for(i=0;i<51;i++)
	{
		set32(E_FRM_CHECK_DATA_ADDR+4*i,dloutput_frm_0[i]);
	}
#if _UNIT_DEBUG
		printf("=========================\n");
		printf("    UT_HDLC_FRAMER_DEFRAMER_TEST_BBIT\n");
		printf("=========================\n"); 
#endif
		frm_protocol = read32(frm_raw_data_addr - 0x4);		
		frm_raw_data_total_len = read32(frm_raw_data_addr - 0x8);
   		
		frm_residue0 = frm_raw_data_total_len%FRM_INFO_LEN_MAX_VALUE;

		frm_in_mainlli_num_min = (frm_raw_data_total_len/FRM_INFO_LEN_MAX_VALUE) + (frm_residue0 ? 1 : 0);
		
		if(IP_OR_PPP==1)
		{frm_in_mainlli_num = FRM_IN_MAINLLI_NUM;
		}
		else if(frm_in_mainlli_num_min==1)
		{frm_in_mainlli_num = FRM_IN_MAINLLI_NUM;
		}
		else
		{frm_in_mainlli_num = frm_in_mainlli_num_min;
		 frm_in_pkt_len = FRM_INFO_LEN_MAX_VALUE;
		 frm_in_pkt_len_last = (frm_residue0 ? frm_residue0 : FRM_INFO_LEN_MAX_VALUE);
			for(i=0;i<frm_in_mainlli_num;i++)
			{
				if(i==frm_in_mainlli_num-1)
				{
				 frm_in_pkt_len_array[i]=frm_in_pkt_len_last;
				}
				else
				{
				 frm_in_pkt_len_array[i]=frm_in_pkt_len;
				}
			}
		}
		
		frm_pkt_addr=frm_raw_data_addr;
		frm_sublli_addr=E_FRM_IN_SUB_LLI_ADDR;
		
		#ifdef _UNIT_DEBUG
		UINT32 in_mainlli_value_0,in_mainlli_value_1,in_mainlli_value_2;
		#endif
		for(i=0; i<frm_in_mainlli_num; i++)
		{
			frm_pkt_or_sublli_addr=(FRM_IN_LLI_1DOR2D_VALUE==0)?frm_pkt_addr:frm_sublli_addr;
				if(i==frm_in_mainlli_num-1)
				{
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i,frm_pkt_or_sublli_addr);
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i+4,frm_in_pkt_len_array[i]);
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i+8,0);
				}
				else
				{
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i,frm_pkt_or_sublli_addr);
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i+4,frm_in_pkt_len_array[i]);
				set32(E_FRM_IN_MAIN_LLI_ADDR+12*i+8,E_FRM_IN_MAIN_LLI_ADDR+12*(i+1));
				}
			frm_pkt_addr=frm_pkt_addr+frm_in_pkt_len_array[i];
			frm_sublli_addr=frm_sublli_addr+FRM_IN_SUBLLI_NUM*12;
			#ifdef _UNIT_DEBUG
			in_mainlli_value_0=read32(E_FRM_IN_MAIN_LLI_ADDR+12*i);
			in_mainlli_value_1=read32(E_FRM_IN_MAIN_LLI_ADDR+12*i+4);
			in_mainlli_value_2=read32(E_FRM_IN_MAIN_LLI_ADDR+12*i+8);
			printf("frm_pkt_or_sublli_addr is %x\n", in_mainlli_value_0);
			printf("frm_in_pkt_len is %x\n", in_mainlli_value_1);
			printf("frm_in_next_mainlli_addr is %x\n", in_mainlli_value_2);
			#endif
		}
		
		frm_blk_addr=frm_raw_data_addr;
		#ifdef _UNIT_DEBUG
		UINT32 in_sublli_value_0,in_sublli_value_1,in_sublli_value_2;
		#endif
		if(FRM_IN_LLI_1DOR2D_VALUE==1)
		{	for(i=0; i<frm_in_mainlli_num; i++)
			{
				frm_in_blk_len=frm_in_pkt_len_array[i]/FRM_IN_SUBLLI_NUM;
				frm_in_blk_len_last=frm_in_blk_len+frm_in_pkt_len_array[i]%FRM_IN_SUBLLI_NUM;
				for(j=0;j<FRM_IN_SUBLLI_NUM;j++)
				{
					frm_sublli_addr=E_FRM_IN_SUB_LLI_ADDR+12*(FRM_IN_SUBLLI_NUM*i+j);
					if(j==FRM_IN_SUBLLI_NUM-1)
					{
					set32(frm_sublli_addr,frm_blk_addr);
					set32(frm_sublli_addr+4,frm_in_blk_len_last);
					set32(frm_sublli_addr+8,0);
					frm_blk_addr=frm_blk_addr+frm_in_blk_len_last;
					}
					else
					{
					set32(frm_sublli_addr,frm_blk_addr);
					set32(frm_sublli_addr+4,frm_in_blk_len);
					set32(frm_sublli_addr+8,frm_sublli_addr+12);
					frm_blk_addr=frm_blk_addr+frm_in_blk_len;
					}
					#ifdef _UNIT_DEBUG
					in_sublli_value_0=read32(frm_sublli_addr);
					in_sublli_value_1=read32(frm_sublli_addr+4);
					in_sublli_value_2=read32(frm_sublli_addr+8);
					printf("frm_blk_addr is %x\n", in_sublli_value_0);
					printf("frm_in_blk_len is %x\n", in_sublli_value_1);
					printf("frm_in_next_sublli_addr is %x\n", in_sublli_value_2);
					#endif
				}
			}
		}
		
		frm_out_addr=E_FRM_OUT_SPC_ADDR;
		frm_outlli_addr=E_FRM_OUT_LLI_ADDR;
		for(i=0; i<frm_in_mainlli_num; i++)
		{
			frm_out_segment_dep=(frm_in_pkt_len_array[i]*2+13)/FRM_OUT_SEGMENT_NUM;
			frm_out_segment_dep_last=frm_out_segment_dep+(frm_in_pkt_len_array[i]*2+13)%FRM_OUT_SEGMENT_NUM;
			for(j=0;j<FRM_OUT_SEGMENT_NUM;j++)
			{
				frm_outlli_addr=E_FRM_OUT_LLI_ADDR+12*(FRM_OUT_SEGMENT_NUM*i+j);
				if(j==FRM_OUT_SEGMENT_NUM-1)
				{
#if _UNIT_DEBUG
				printf("frm_out_addr is %x\n", frm_out_addr);
#endif
				set32(frm_outlli_addr,frm_out_addr);
				set32(frm_outlli_addr+4,frm_out_segment_dep_last);
				set32(frm_outlli_addr+8,frm_outlli_addr+12);
				frm_out_addr=frm_out_addr+frm_out_segment_dep_last;
				}
				else
				{
#if _UNIT_DEBUG
				printf("frm_out_addr is %x\n", frm_out_addr);
#endif
				set32(frm_outlli_addr,frm_out_addr);
				set32(frm_outlli_addr+4,frm_out_segment_dep);
				set32(frm_outlli_addr+8,frm_outlli_addr+12);
				frm_out_addr=frm_out_addr+frm_out_segment_dep;
				}
			}
		}
		set32(frm_outlli_addr+8,0);

//********************************************************
//    lli for deframer
//********************************************************	
    for(i=0;i<52;i++)
	{
    	set32(E_DEF_RAW_DATA_ADDR+4*i,ulinput_def_0[i]);
		#ifdef _UNIT_DEBUG
		def_inputdata=read32(E_DEF_RAW_DATA_ADDR+4*i);
		printf("def_inputdata is %x\n", def_inputdata);
		#endif
	}
	
	for(i=0;i<54;i++)
	{
		set32(E_DEF_CHECK_DATA_ADDR+4*i,uloutput_def_0[i]);
		#ifdef _UNIT_DEBUG
		def_checkdata=read32(E_DEF_CHECK_DATA_ADDR+4*i);
		printf("check data is %x\n", def_checkdata);
		#endif
	}
#if _UNIT_DEBUG
		printf("=========================\n");
		printf("    UT_HDLC_DEFRAMER_DEFRAMER_TEST_BBIT\n");
		printf("=========================\n");	
#endif
		def_raw_data_total_len = read32(E_DEF_RAW_DATA_ADDR);
	
		def_residue0 = (def_raw_data_total_len)%DEF_IN_PKT_LEN_MAX_VALUE;
		
		def_in_lli_num_min = (def_raw_data_total_len/DEF_IN_PKT_LEN_MAX_VALUE) + (def_residue0 ? 1 : 0);
			
		if(def_in_lli_num_min==1)
		{def_in_lli_num = DEF_IN_LLI_NUM;
		 def_in_pkt_len = def_raw_data_total_len/DEF_IN_LLI_NUM;
		 def_in_pkt_len_last = def_in_pkt_len+def_raw_data_total_len%DEF_IN_LLI_NUM;
		}
		else
		{def_in_lli_num = def_in_lli_num_min;
		 def_in_pkt_len = DEF_IN_PKT_LEN_MAX_VALUE;
		 def_in_pkt_len_last = (def_residue0 ? def_residue0 : DEF_IN_PKT_LEN_MAX_VALUE);
		}
		#ifdef _UNIT_DEBUG
		printf("*****************\n");
		printf("def_residue0 is %d\n", def_residue0);
		printf("def_in_lli_num_min is %d\n", def_in_lli_num_min);
		printf("def_in_lli_num is %d\n", def_in_lli_num);
		printf("def_in_pkt_len is %d\n", def_in_pkt_len);
		printf("def_in_pkt_len_last is %d\n", def_in_pkt_len_last);
		printf("*****************\n");
		#endif
        
		for(i=0; i<def_in_lli_num; i++)
		{if(i==def_in_lli_num-1)
		 {
		 set32(E_DEF_IN_LLI_ADDR+12*i,def_raw_data_addr+def_in_pkt_len*i);
		 set32(E_DEF_IN_LLI_ADDR+12*i+4,def_in_pkt_len_last);
		 set32(E_DEF_IN_LLI_ADDR+12*i+8,0);
			#ifdef _UNIT_DEBUG
			printf("*****************\n");
			printf("i is %d\n", i);
			def_in_pkt_addr=read32(E_DEF_IN_LLI_ADDR+12*i);
			def_in_pkt_len=read32(E_DEF_IN_LLI_ADDR+12*i+4);
			def_in_lli_addr=read32(E_DEF_IN_LLI_ADDR+12*i+8);
			printf("def_in_pkt_addr is %x\n", def_in_pkt_addr);
			printf("def_in_pkt_len is %x\n", def_in_pkt_len);
			printf("def_in_lli_next_addr is %x\n", def_in_lli_addr);
			printf("*****************\n");
			#endif
		 }
		 else
		 {
		 set32(E_DEF_IN_LLI_ADDR+12*i,def_raw_data_addr+def_in_pkt_len*i);
		 set32(E_DEF_IN_LLI_ADDR+12*i+4,def_in_pkt_len);
		 set32(E_DEF_IN_LLI_ADDR+12*i+8,E_DEF_IN_LLI_ADDR+12*(i+1));
			 #ifdef _UNIT_DEBUG
			 printf("*****************\n");
			 printf("i is %d\n", i);
			 def_in_pkt_addr=read32(E_DEF_IN_LLI_ADDR+12*i);
			 def_in_pkt_len=read32(E_DEF_IN_LLI_ADDR+12*i+4);
			 def_in_lli_addr=read32(E_DEF_IN_LLI_ADDR+12*i+8);
			 printf("def_in_pkt_addr is %x\n", def_in_pkt_addr);
			 printf("def_in_pkt_len is %x\n", def_in_pkt_len);
			 printf("def_in_lli_next_addr is %x\n", def_in_lli_addr);
			 printf("*****************\n");
			 #endif
		 }
		}

for(n=0;n<6;n++)
	{
#if _UNIT_DEBUG
	printf("n is %x\n", n);
#endif
	def_over_first = 0x0;
    def_over_first = def_over_first;
	frm_raw_data_addr = E_FRM_RAW_DATA_ADDR+8;
	frm_check_data_addr = E_FRM_CHECK_DATA_ADDR+4;
	def_raw_data_addr = E_DEF_RAW_DATA_ADDR+4;
	def_check_data_addr = E_DEF_CHECK_DATA_ADDR+8;
	
//******************************************************
//     setting registers for framer
//******************************************************			
		   if(IP_OR_PPP==1)
		   {
		      frm_acfc = 0x1;		
			  frm_pfc  = 0x3;
		   }
		   else if(frm_protocol == 0xc021)
		   {
			  frm_acfc = 0x0;
		
			  frm_pfc  = 0x0;
		   }
		   else
		   {
			  frm_acfc = 0x1;
		
			  frm_pfc  = 0x1;
		   }
  
	        frm_cfg_value = ((frm_protocol)<<16)|(frm_pfc << 2)|(frm_acfc << 1) | FRM_IN_LLI_1DOR2D_VALUE;
	
	        set32(HDLC_FRM_CFG,  frm_cfg_value); 
			
			frm_accm = 0xffffffff; 

	        set32(HDLC_FRM_ACCM, frm_accm); // set accm register
			
			set32(FRM_IN_LLI_ADDR,E_FRM_IN_MAIN_LLI_ADDR);
			set32(FRM_OUT_LLI_ADDR,E_FRM_OUT_LLI_ADDR);
			set32(FRM_RPT_ADDR,E_FRM_RPT_ADDR);
			set32(FRM_RPT_DEP,frm_in_mainlli_num*16);
			
//******************************************************
//     setting registers for deframer
//******************************************************			
            def_uncompleted_ago=0;
			def_acfc = 1;
            def_pfc = 1;			
		    def_cfg_value = (def_pfc << 2)|(def_acfc << 1) | def_uncompleted_ago;		    
		    set32(HDLC_DEF_CFG,  def_cfg_value); 
			#ifdef _UNIT_DEBUG
			printf("*****************\n");
			printf("E_DEF_IN_LLI_ADDR %x\n", E_DEF_IN_LLI_ADDR);
			printf("*****************\n");
			#endif	    
		    set32(DEF_IN_LLI_ADDR,  E_DEF_IN_LLI_ADDR); 
			

			#ifdef _UNIT_DEBUG
		    def_in_lli_addr=read32(DEF_IN_LLI_ADDR);
			printf("*****************\n");
			printf("def_in_lli_addr is %x\n", def_in_lli_addr);
			printf("*****************\n");
			#endif
			
		    set32(DEF_IN_PKT_LEN_MAX,  DEF_IN_PKT_LEN_MAX_VALUE); 
			set32(DEF_OUT_SPC_ADDR,  E_DEF_OUT_SPC_ADDR);
			//set32(DEF_OUT_SPC_DEP,  DEF_OUT_SPC_DEP_VALUE);
			set32(DEF_RPT_ADDR,  E_DEF_RPT_ADDR);
			set32(DEF_RPT_DEP,  DEF_RPT_DEP_VALUE);	
			set32(DEF_OUT_SPC_DEP,  DEF_OUT_SPC_DEP_VALUE);
			#ifdef _UNIT_DEBUG
			def_in_lli_addr=read32(DEF_IN_LLI_ADDR);
			printf("*****************\n");
			printf("def_in_lli_addr is %x\n", def_in_lli_addr);
			printf("*****************\n");
			#endif
			
//******************************************************
//     setting registers for framer and deframer
//******************************************************			
			if(n==0||n==1)
			{
			hdlc_prior_ctrl=0x0;
			}
			if(n==2||n==3)
			{
			hdlc_prior_ctrl=0x1;
			}
			if(n==4||n==5)
			{
			hdlc_prior_ctrl=0x2;
			}
			axireq_timeout_en=1;
			axireq_timeout_value=0xff;
			prior_timeout_ctrl_value=(axireq_timeout_value<<16)|(axireq_timeout_en<<8)|hdlc_prior_ctrl;
			set32(PRIOR_TIMEOUT_CTRL,  prior_timeout_ctrl_value); 
			
			set32(HDLC_FRM_INT_CLR,0x0103FF00);
			set32(HDLC_DEF_INT_CLR,  0x0107FF00);
			if(n==0||n==3||n==4)
			{
			set32(HDLC_FRM_EN,0x0103FF01);
			//taskDelay(10);
			set32(HDLC_DEF_EN, 0x0107FF01);
			}
			if(n==1||n==2||n==5)
			{
			set32(HDLC_DEF_EN,0x0107FF01);
			set32(HDLC_FRM_EN, 0x0103FF01);
			}
			#ifdef _UNIT_DEBUG
			def_in_lli_addr=read32(DEF_IN_LLI_ADDR);
			printf("*****************\n");
			printf("def_in_lli_addr is %x\n", def_in_lli_addr);
			printf("*****************\n");
			#endif			
	  
//********************************************************
//     end of setting registers
//********************************************************
//************************************************
//  check result
//************************************************
		    frm_stat = 0x0;
			def_stat = 0x0;
		    while(((frm_stat & 0x00000003) == 0x0)||((def_stat & 0x0000003F) == 0x0))
		    { 
//		    	for (i = 0; i < 100; i ++)
//		    	{
//		    		DelayRandom();
//		    	}
				def_stat = read32(HDLC_DEF_STATUS);		    	
		        frm_stat = read32(HDLC_FRM_STATUS);
#ifdef _UNIT_DEBUG
printf("frm_stat is %x\n", frm_stat);
printf("def_stat is %x\n", def_stat);
#endif

if(((frm_stat & 0x00000003) != 0x0)&&((def_stat & 0x0000003F) != 0x0))
{
hdlc_def_raw_int=read32(HDLC_DEF_RAW_INT);
hdlc_def_raw_int=hdlc_def_raw_int;
#ifdef _UNIT_DEBUG
printf("*****************\n");
printf("hdlc_def_raw_int is %x\n", hdlc_def_raw_int);
printf("*****************\n");
#endif
}

				if((def_stat & 0x0000003f) == 0x3 || ((def_stat & 0x0000003e) == 0x6))
				{
				 if((frm_stat & 0x00000003) != 0x1)
				 {
				 def_over_first=0x1;
				 }
				}
				
			if(((def_stat & 0x0000003F) == 0x1)||((def_stat & 0x0000003F) == 0x8)||((def_stat & 0x0000003F) == 0x10))
		    {
				#ifdef _UNIT_DEBUG
		        printf("def_stat is %x\n", def_stat);
		        #endif
				
		        def_vld_num = (def_stat >> 8) & 0xffff;
		   
		        #ifdef _UNIT_DEBUG
		        printf("def_vld_num is %d\n", def_vld_num);
		        #endif
		   
		        def_report_addr = E_DEF_RPT_ADDR;
		   
		        for(j = 0; j < def_vld_num; j++)
		        {
			        def_report_value = read32(def_report_addr);
			        
			        #ifdef _UNIT_DEBUG
			        printf("report value is %x\n", def_report_value);
			        #endif
                                        
			        def_vld_frm_length[j] = def_report_value & 0x0000ffff;
					
					def_out_one_len = def_vld_frm_length[j];
					
                    def_protocol[j] = (def_report_value >> 16) & 0x0000ffff;
                    def_protocol[j] = def_protocol[j];
                    def_check_data_one_len=read32(def_check_data_addr-8);
					if(def_out_one_len != (def_check_data_one_len & 0xffff))
					{		
					printf("Error: expected  def_check_data_one_len: %x does not match actual def_out_one_len: %x !\n", def_check_data_one_len,def_out_one_len);
					def_e_num++;
					return 1;
					}
					
			        def_report_value = read32(def_report_addr + 4);
			        def_output_addr=def_report_value;
			        
			        #ifdef _UNIT_DEBUG
			        printf("output addr is %x\n", def_output_addr);
			        #endif
			        
					while(def_out_one_len > 0)
					{			  
					k = (UINT8)(read8(def_check_data_addr));		   
					#ifdef _UNIT_DEBUG 
					printf("check_data is %x\n", k);
					#endif
		    
					m = read8(def_output_addr);
		    
					#ifdef _UNIT_DEBUG 
					printf("addr is %x\n, output_data is %x\n\n", def_output_addr, m);
					#endif
		    
					if(k != (UINT8)m)
					{		
					printf("Error: expected %x: %x does not match actual %x: %x !\n", def_check_data_addr, k, def_output_addr, m);
					def_e_num++;
					return 1;
					}
					
					if(def_output_addr+1==E_DEF_OUT_SPC_ADDR+DEF_OUT_SPC_DEP_VALUE)
					{
					def_output_addr = E_DEF_OUT_SPC_ADDR;
					}
					else
					{
					def_output_addr = def_output_addr + 1;
					}
					
					def_check_data_addr = def_check_data_addr + 1;
					def_out_one_len = def_out_one_len - 1;
					}
					
					if((def_check_data_addr& 0x00000003)==0x0)
					{
					 def_check_data_addr=def_check_data_addr+8;
					}
					else
					{
					 def_check_data_addr=def_check_data_addr+8+4-def_check_data_addr%4;
					}					
			        def_report_addr += 8;
		        }
		        if((def_stat & 0x0000003F) == 0x1)
				{
				 //set32(HDLC_DEF_INT_CLR,  0x0107FF00);
		         set32(HDLC_DEF_INT_CLR,  0x00010000);
				 def_acfc = 1;
				 def_pfc = 1;			
				 def_cfg_value = (def_pfc << 2)|(def_acfc << 1) | def_uncompleted_ago;		    
				 set32(HDLC_DEF_CFG,  def_cfg_value);
				 set32(HDLC_DEF_GO_ON, 0x1);
				}
				if((def_stat & 0x0000003F) == 0x8)
				{
				 //set32(HDLC_DEF_INT_CLR,  0x0107FF00);
				 set32(HDLC_DEF_INT_CLR,  0x00020000);
				 set32(HDLC_DEF_GO_ON, 0x100);
				}
				if((def_stat & 0x0000003F) == 0x10)
				{
				 //set32(HDLC_DEF_INT_CLR,  0x0107FF00);
				 set32(HDLC_DEF_INT_CLR,  0x00040000);
				 set32(HDLC_DEF_GO_ON, 0x10000);
				}
		        def_stat = 0x0;
            }
		    }
#ifdef HDLC_DEGBU
			if(def_over_first==0x1)
			{
			printf("*************************************\n");
			printf("when n= %x, deframer over first\n", n);
			printf("*************************************\n");
			if(n==0||n==2||n==3)
			{
			printf("*************************************\n");
			printf("when n= %x, Error\n", n);
			printf("*************************************\n");
			}
			}
			else
			{
			printf("*************************************\n");
			printf("when n= %x, framer over first\n", n);
			printf("*************************************\n");
			if(n==1||n==4||n==5)
			{
			printf("*************************************\n");
			printf("when n= %x, Error\n", n);
			printf("*************************************\n");
			}
			}
#endif
			
			hdlc_frm_raw_int=read32(HDLC_FRM_RAW_INT);
			hdlc_frm_raw_int=hdlc_frm_raw_int;
			hdlc_frm_int_status=read32(HDLC_FRM_INT_STATUS);
			hdlc_frm_int_status=hdlc_frm_int_status;
			#ifdef _UNIT_DEBUG
			printf("hdlc_frm_raw_int is %x\n", hdlc_frm_raw_int);
			printf("hdlc_frm_int_status is %x\n", hdlc_frm_int_status);	
			#endif
			if((frm_stat & 0x00000003) == 0x2)
			{
			#ifdef _UNIT_DEBUG
			printf("frm_stat is %x\n", frm_stat);
			#endif
			hdlc_frm_raw_int=read32(HDLC_FRM_RAW_INT);
			hdlc_frm_int_status=read32(HDLC_FRM_INT_STATUS);
			#ifdef _UNIT_DEBUG
			printf("hdlc_frm_raw_int is %x\n", hdlc_frm_raw_int);
			printf("hdlc_frm_int_status is %x\n", hdlc_frm_int_status);
			#endif
			}
			
			if((frm_stat & 0x00000003) == 0x1)
			{
			#ifdef _UNIT_DEBUG
			printf("frm_stat is %x\n", frm_stat);
			#endif
			frm_vld_num=(frm_stat>>8)&0xff;
			frm_out_seg_num=(frm_stat>>16)&0xffff;
			frm_out_seg_num=frm_out_seg_num;
			#ifdef _UNIT_DEBUG
			printf("frm_vld_num is %d\n", frm_vld_num);
			printf("frm_out_seg_num is %d\n", frm_out_seg_num);			
			#endif
			frm_report_addr=E_FRM_RPT_ADDR;
			for(j = 0; j < frm_vld_num; j++)
			{		
				frm_report_value=read32(frm_report_addr);
				frm_output_addr=frm_report_value;				
				#ifdef _UNIT_DEBUG
				printf("output addr is %x\n", frm_output_addr);
				#endif
				
				frm_report_value = read32(frm_report_addr + 4);				
			    frm_vld_frm_length[j] = frm_report_value & 0x0000ffff;				
				frm_out_one_len = frm_vld_frm_length[j];
				#ifdef _UNIT_DEBUG
				printf("frm_out_one_len is %x\n", frm_out_one_len);
				#endif
				
                frm_check_data_one_len=read32(frm_check_data_addr-4);
				if(frm_out_one_len != (frm_check_data_one_len & 0xffff))
				{		
				printf("Error: expected  frm_check_data_one_len: %x does not match actual frm_out_one_len: %x !\n", frm_check_data_one_len,frm_out_one_len);
				frm_e_num++;
				return 1;
				}
					while(frm_out_one_len > 0)
					{			  
					k = (UINT8)(read8(frm_check_data_addr));		   
					#ifdef _UNIT_DEBUG 
					printf("check_data is %x\n", k);
					#endif
					m = read8(frm_output_addr);
		    
					#ifdef _UNIT_DEBUG 
					printf("addr is %x\n, output_data is %x\n\n", frm_output_addr, m);
					#endif
		    
					if(k != (UINT8)m)
					{		
					printf("Error: expected %x: %x does not match actual %x: %x !\n", frm_check_data_addr, k, frm_output_addr, m);
					frm_e_num++;
					return 1;
					}
		
					frm_output_addr = frm_output_addr + 1;//各输出数据存储分片之间衔接
					frm_check_data_addr = frm_check_data_addr + 1;
					frm_out_one_len = frm_out_one_len - 1;
					}
					
					if((frm_check_data_addr&0x00000003)==0x0)
					{
					 frm_check_data_addr=frm_check_data_addr+8;
					}
					else
					{
					 frm_check_data_addr=frm_check_data_addr+4+4-frm_check_data_addr%4;
					}					
			        frm_report_addr += 8;				
			}
			}
			
						
			if((def_stat & 0x00000020) == 0x20)
			{	
				#ifdef _UNIT_DEBUG
		        printf("def_stat is %x\n", def_stat);
		        #endif
				hdlc_def_raw_int=read32(HDLC_DEF_RAW_INT);
				hdlc_def_int_status=read32(HDLC_DEF_INT_STATUS);
				hdlc_def_int_status=hdlc_def_int_status;
#ifdef _UNIT_DEBUG
		        printf("hdlc_def_raw_int is %x\n", hdlc_def_raw_int);
		        printf("hdlc_def_int_status is %x\n", hdlc_def_int_status);				
#endif
		        
				def_in_lli_addr=read32(DEF_IN_LLI_ADDR);
				def_in_lli_addr=def_in_lli_addr;
				def_in_pkt_addr=read32(DEF_IN_PKT_ADDR);
				def_in_pkt_addr=def_in_pkt_addr;
				def_in_pkt_len=read32(DEF_IN_PKT_LEN);
			 	#ifdef _UNIT_DEBUG
		        printf("def_in_lli_addr is %x\n", def_in_lli_addr);
		        printf("def_in_pkt_addr is %x\n", def_in_pkt_addr);	
		        printf("def_in_pkt_len is %x\n", def_in_pkt_len);	
		        #endif
		        
			}
			
			
			
			
			
			
		    if((def_stat & 0x0000003f) == 0x3 || ((def_stat & 0x0000003e) == 0x6))
		    {
#ifdef _UNIT_DEBUG
		       printf("=========================\n");  
#endif		          
		       #ifdef _UNIT_DEBUG
		       printf("def_stat is %x\n", def_stat);
		       #endif
		       
			   	def_vld_num = (def_stat >> 8) & 0xffff;
		   
		        #ifdef _UNIT_DEBUG
		        printf("def_vld_num is %d\n", def_vld_num);
		        #endif
				
				def_uncompleted_now=(def_stat >> 2) & 0x1;
		        #ifdef _UNIT_DEBUG
		        printf("def_uncompleted_now is %x\n", def_uncompleted_now);
		        #endif
				
		        def_report_addr = E_DEF_RPT_ADDR;
		   
		        for(j = 0; j < def_vld_num+def_uncompleted_now; j++)
		        {         
			        def_report_value = read32(def_report_addr);
			        
			        #ifdef _UNIT_DEBUG
			        printf("report value is %x\n", def_report_value);
			        #endif
                                        
			        def_vld_frm_length[j] = def_report_value & 0x0000ffff;
					
					def_out_one_len = def_vld_frm_length[j];
					
                    def_protocol[j] = (def_report_value >> 16) & 0x0000ffff;
                    
                    def_check_data_one_len=read32(def_check_data_addr-8);
					if(def_out_one_len != (def_check_data_one_len & 0xffff))
					{		
					printf("Error: expected  def_check_data_one_len: %x does not match actual def_out_one_len: %x !\n", def_check_data_one_len,def_out_one_len);
					def_e_num++;
					return 1;
					}
			        def_report_value = read32(def_report_addr + 4);
			        def_output_addr=def_report_value;
			        
			        #ifdef _UNIT_DEBUG
			        printf("output addr is %x\n", def_output_addr);
			        #endif
			        
					while(def_out_one_len > 0)
					{			  
					k = (UINT8)(read8(def_check_data_addr));		   
					#ifdef _UNIT_DEBUG 
					printf("check_data is %x\n", k);
					#endif
		    
					m = read8(def_output_addr);
		    
					#ifdef _UNIT_DEBUG 
					printf("addr is %x\n, output_data is %x\n\n", def_output_addr, m);
					#endif
		    
					if(k != (UINT8)m)
					{		
					printf("Error: expected %x: %x does not match actual %x: %x !\n", def_check_data_addr, k, def_output_addr, m);
					def_e_num++;
					return 1;
					}
		
					if(def_output_addr+1==E_DEF_OUT_SPC_ADDR+DEF_OUT_SPC_DEP_VALUE)
					{
					def_output_addr = E_DEF_OUT_SPC_ADDR;
					}
					else
					{
					def_output_addr = def_output_addr + 1;
					}
					
					def_check_data_addr = def_check_data_addr + 1;
					def_out_one_len = def_out_one_len - 1;
					}
					
					if((def_check_data_addr&0x00000003)==0x0)
					{
					 def_check_data_addr=def_check_data_addr+8;
					}
					else
					{
					 def_check_data_addr=def_check_data_addr+8+4-def_check_data_addr%4;
					}					
			        def_report_addr += 8;
		        }
		       
		       def_err_ind[0] = (def_stat >> 24) & 0x00000001;
		       
		       def_err_ind[1] = (def_stat >> 25) & 0x00000001;
		       
		       def_err_ind[2] = (def_stat >> 26) & 0x00000001;
		       
		       def_err_ind[3] = (def_stat >> 27) & 0x00000001;
		       
		       def_err_ind[4] = (def_stat >> 28) & 0x00000001;
		       
		       def_err_ind[5] = (def_stat >> 29) & 0x00000001;
		       
		       def_err_ind[6] = (def_stat >> 30) & 0x00000001;
               
		       def_err_info_0 = read32(HDLC_DEF_ERR_INFO_0);
		       
		       def_err_info_1 = read32(HDLC_DEF_ERR_INFO_1);
		       
		       def_err_info_2 = read32(HDLC_DEF_ERR_INFO_2);
		       
		       def_err_info_3 = read32(HDLC_DEF_ERR_INFO_3);
		       
		       if(def_err_ind[0] == 1)
		       {
		    	   def_err_num[0] = def_err_info_0 & 0x0000ffff; 
		    	   def_err_num[0] = def_err_num[0];
#ifdef _UNIT_DEBUG
		    	   printf("err_0_num is %d\n", def_err_num[0]);
#endif
		       }
		       if(def_err_ind[1] == 1)
		       {
		           def_err_num[1] = (def_err_info_0 >> 16) & 0x0000ffff; 
#ifdef _UNIT_DEBUG		    	 
		    	   printf("err_1_num is %d\n", def_err_num[1]);
#endif
		       }
		       if(def_err_ind[2] == 1)
		       {
		    	   def_err_num[2] = def_err_info_1 & 0x0000ffff;
#ifdef _UNIT_DEBUG		    	   
		    	   printf("err_2_num is %d\n", def_err_num[2]);
#endif
		       }
		       if(def_err_ind[3] == 1)
		       {
		    	   def_err_num[3] = (def_err_info_1 >> 16)& 0x0000ffff; 
#ifdef _UNIT_DEBUG		    	   
		    	   printf("err_3_num is %d\n",def_err_num[3]);
#endif
		       }
		       if(def_err_ind[4] == 1)
		       { 
		    	   def_err_num[4] = def_err_info_2 & 0x0000ffff; 
#ifdef _UNIT_DEBUG		    	   
		    	   printf("err_4_num is %d\n",def_err_num[4]);
#endif
		       }
		       if(def_err_ind[5] == 1)
		       {
		    	   def_err_num[5] = (def_err_info_2 >> 16) & 0x0000ffff; 
#ifdef _UNIT_DEBUG		    	   
		    	   printf("err_5_num is %d\n",def_err_num[5]);
#endif
		       }
		       if(def_err_ind[6] == 1)
		       {
		    	   def_err_num[6] = def_err_info_3 & 0x0000ffff; 
#ifdef _UNIT_DEBUG		    	   
		    	   printf("err_6_num is %d\n",def_err_num[6]);
#endif
		        }
		    }
	}			
	if((frm_e_num==0)&&(def_e_num==0))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
