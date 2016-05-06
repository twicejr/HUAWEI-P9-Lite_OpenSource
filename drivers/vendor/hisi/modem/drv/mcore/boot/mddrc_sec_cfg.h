

#ifndef __MDDRC_SEC_H__
#define __MDDRC_SEC_H__

#include <osl_types.h>
/* 722 开始增加安全特性 
  如果以后平台差异不大，则共用该头文件 
  如果以后平台有较大差异，则各平台单独定义头文件 */


/*"当前区域的大小。
6'd15： 64KB；
6'd16：128KB；此时.bits.rgn_base_addr[   0]必须配置为零；
6'd17：256KB；此时.bits.rgn_base_addr[ 1:0]必须配置为零；
6'd18：512KB；此时.bits.rgn_base_addr[ 2:0]必须配置为零；
6'd19：  1MB；此时.bits.rgn_base_addr[ 3:0]必须配置为零；
6'd20：  2MB；此时.bits.rgn_base_addr[ 4:0]必须配置为零；
6'd21：  4MB；此时.bits.rgn_base_addr[ 5:0]必须配置为零；
6'd22：  8MB；此时.bits.rgn_base_addr[ 6:0]必须配置为零；
6'd23： 16MB；此时.bits.rgn_base_addr[ 7:0]必须配置为零；
6'd24： 32MB；此时.bits.rgn_base_addr[ 8:0]必须配置为零；
6'd25： 64MB；此时.bits.rgn_base_addr[ 9:0]必须配置为零；
6'd26：128MB；此时.bits.rgn_base_addr[10:0]必须配置为零；
6'd27：256MB；此时.bits.rgn_base_addr[11:0]必须配置为零；
6'd28：512MB；此时.bits.rgn_base_addr[12:0]必须配置为零；
6'd29：  1GB；此时.bits.rgn_base_addr[13:0]必须配置为零；
6'd30：  2GB；此时.bits.rgn_base_addr[14:0]必须配置为零；
6'd31：  4GB；此时.bits.rgn_base_addr[15:0]必须配置为零；
6'd32：  8GB；此时.bits.rgn_base_addr[16:0]必须配置为零；
6'd33： 16GB；此时.bits.rgn_base_addr[17:0]必须配置为零；
6'd34： 32GB；此时.bits.rgn_base_addr[18:0]必须配置为零；
6'd35： 64GB；此时.bits.rgn_base_addr[19:0]必须配置为零；
6'd36：128GB；此时.bits.rgn_base_addr[20:0]必须配置为零；
6'd37：256GB；此时.bits.rgn_base_addr[21:0]必须配置为零；
6'd38：512GB；此时.bits.rgn_base_addr[22:0]必须配置为零；
6'd39：1TB；  此时.bits.rgn_base_addr[23:0]必须配置为零。
注意：
1.rgn0不可配置，默认覆盖整个地址空间；
2.为每个区域配置的区域大小，
累加上其区域起始地址后，
不允许超出总的地址空间大小。" */
#define DDR_RGN_SIZE_64KB     (15)
#define DDR_RGN_SIZE_128KB    (16)
#define DDR_RGN_SIZE_256KB    (17)
#define DDR_RGN_SIZE_512KB    (18)
#define DDR_RGN_SIZE_1MB      (19)
#define DDR_RGN_SIZE_2MB      (20)
#define DDR_RGN_SIZE_4MB      (21)
#define DDR_RGN_SIZE_8MB      (22)
#define DDR_RGN_SIZE_16MB     (23)
#define DDR_RGN_SIZE_32MB     (24)
#define DDR_RGN_SIZE_64MB     (25)
#define DDR_RGN_SIZE_128MB    (26)
#define DDR_RGN_SIZE_256MB    (27)
#define DDR_RGN_SIZE_512MB    (28)
#define DDR_RGN_SIZE_1GB      (29)

/* 当前区域的安全权限属性。
sp[3]：安全读属性；
sp[2]：安全写属性；
sp[1]：非安全读属性；
sp[0]：非安全写属性；
sp[n]=0：禁止访问；
sp[n]=1：允许访问。*/ 
#define __DDR_SEC_R__    	(0x1<<3)
#define __DDR_SEC_W__    	(0x1<<2)
#define __DDR_UNSEC_R__    	(0x1<<1)
#define __DDR_UNSEC_W__    	(0x1<<0)
#define DDR_RGN_ATTR_SP_SEC		(__DDR_SEC_R__|__DDR_SEC_W__)
#define DDR_RGN_ATTR_SP_UNSEC	(__DDR_SEC_R__|__DDR_SEC_W__|__DDR_UNSEC_R__|__DDR_UNSEC_W__)


typedef union
{
	struct
	{
		u32 rgn_base_addr	: 24; 	/* 23:0 */
		u32 rgn_size		: 6;	/* 29:24 */
		u32 reserved1 		: 1;	/* 30:30 */
		u32 reg_en 			: 1;	/* 31:31 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_MAP;


typedef union
{
	struct
	{
		u32 spp				: 4;   /* 3:0 */
		u32 security_inv	: 1;   /* 4:4 */
		u32 reserved1 		: 3;   /* 7:5 */
		u32 mid_en 			: 1;   /* 8:8 */
		u32 mid_inv			: 1;   /* 9:9 */
		u32 reserved2 		: 6;   /* 15:10 */
		u32 subrgn_disable	: 16;  /* 31:16 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_ATTRIB;

#define DDR_RGN_MAP_BASE_ADDR(addr) ((addr)>>8)

#define DDR_SEC_BASE_ADDR	(0x90040000)
#define DDR_SEC_RGN_MAP_ADDR(ports, regions) 		(0x500+0x200*ports+0x10*regions)
#define DDR_SEC_RGN_ATTRIB_ADDR(ports, regions) 	(0x504+0x200*ports+0x10*regions)
#define DDR_SEC_MID_WR_ADDR(ports, regions) 		(0x508+0x200*ports+0x10*regions)
#define DDR_SEC_MID_RD_ADDR(ports, regions) 		(0x50c+0x200*ports+0x10*regions)


#define DDR_RGN_NUMBER	(16)

#define REGION_CONFIG_COMM(region,base_addr,size,ssp,sub_rgn)	\
do {	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_base_addr 	= (base_addr >> 16);	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_size 			= size;			\
	ddr_reg_sec_rgn_maps[region].bits.reg_en			= 1;			\
	ddr_reg_sec_rgn_attribs[region].bits.spp 			= ssp;			\
	ddr_reg_sec_rgn_attribs[region].bits.subrgn_disable	= sub_rgn;		\
}while (0)
    
#define REGION_CONFIG_REG(region,port)	\
do {    \
    writel(ddr_reg_sec_rgn_maps[region].reg_val   , DDR_SEC_BASE_ADDR + DDR_SEC_RGN_MAP_ADDR(port,region));\
    writel(ddr_reg_sec_rgn_attribs[region].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_ATTRIB_ADDR(port,region));\
}while (0)


#ifdef CONFIG_DDR_SECURITY
void mddrc_sec_cfg(void);
#else
static inline void mddrc_sec_cfg(void){}
#endif


#endif /* __MDDRC_SEC_H__ */
