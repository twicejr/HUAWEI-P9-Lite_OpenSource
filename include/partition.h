#ifndef _PARTITION_H_
#define _PARTITION_H_

#include "hisi_partition.h"

typedef struct partition {
	char name[PART_NAMELEN];
	unsigned int length;
	unsigned int flags;
}PARTITION;

typedef struct ptable_type {
    char* ptable_name;
    unsigned int ptable_part_type;
}PTABLE_TYPE;

enum {
	BOOT_PART = 0x1,
	EMMC_USER_PART = 0x0,
};

#if defined(CONFIG_HISI_PARTITION_HI3650)
static const struct partition partition_table[] =
{
    {PART_XLOADER,           256,      BOOT_PART},
    {PART_PTABLE,            512,      EMMC_USER_PART}, /* ptable           512K */
    {PART_VRL,               256,      EMMC_USER_PART}, /* VRL              256K p1*/
    {PART_VRL_BACKUP,        256,      EMMC_USER_PART}, /* VRL backup       256K p2*/
    {PART_FW_LPM3,           256,      EMMC_USER_PART}, /* mcuimage         256K p3*/
    {PART_FRP,               768,      EMMC_USER_PART}, /* frp              768K p4*/
    {PART_FASTBOOT,          4*1024,   EMMC_USER_PART}, /* fastboot         4M   p5*/
    {PART_MODEMNVM_FACTORY,  4*1024,   EMMC_USER_PART}, /* modemnvm factory 4M   p6*/
    {PART_NVME,              6*1024,   EMMC_USER_PART}, /* nvme             6M   p7*/
    {PART_OEMINFO,           64*1024,  EMMC_USER_PART}, /* oeminfo          64M  p8*/
    {PART_SPLASH,            8*1024,   EMMC_USER_PART}, /* splash           8M   p9*/
    {PART_MODEMNVM_BACKUP,   4*1024,   EMMC_USER_PART}, /* modemnvm backup  4M   p10*/
    {PART_MODEMNVM_IMG,      8*1024,   EMMC_USER_PART}, /* modemnvm img     8M   p11*/
    {PART_MODEMNVM_SYSTEM,   4*1024,   EMMC_USER_PART}, /* modemnvm system  4M   p12*/
    {PART_SECURE_STORAGE,    32*1024,  EMMC_USER_PART}, /* secure storage   32M  p13*/
    {PART_3RDMODEMNVM,       16*1024,  EMMC_USER_PART}, /* 3rdmodemnvm      16M  p14*/
    {PART_3RDMODEMNVMBKP,    16*1024,  EMMC_USER_PART}, /* 3rdmodemnvmback  16M  p15*/
    {PART_PERSIST,           2*1024,   EMMC_USER_PART}, /* persist          2M   p16*/
    {PART_RESERVED1,         14*1024,  EMMC_USER_PART}, /* reserved1        14M  p17*/
    {PART_MODEM_OM,          32*1024,  EMMC_USER_PART}, /* modem om         32M  p18*/
    {PART_SPLASH2,           64*1024,  EMMC_USER_PART}, /* splash2          64M  p19*/
    {PART_MISC,              2*1024,   EMMC_USER_PART}, /* misc             2M   p20*/
    {PART_MODEMNVM_UPDATE,   24*1024,  EMMC_USER_PART}, /* modemnvm update  24M  p21*/
    {PART_RECOVERY2,         64*1024,  EMMC_USER_PART}, /* recovery2        64M  p22*/
    {PART_RESERVED2,         64*1024,  EMMC_USER_PART}, /* reserved2        64M  p23*/
    {PART_TEEOS,             4*1024,   EMMC_USER_PART}, /* teeos            4M   p24*/
    {PART_TRUSTFIRMWARE,     2*1024,   EMMC_USER_PART}, /* trustfirmware    2M   p25*/
    {PART_SENSORHUB,         16*1024,  EMMC_USER_PART}, /* sensorhub        16M  p26*/
    {PART_FW_HIFI,           12*1024,  EMMC_USER_PART}, /* hifi             12M  p27*/
    {PART_BOOT,              32*1024,  EMMC_USER_PART}, /* boot             32M  p28*/
    {PART_RECOVERY,          64*1024,  EMMC_USER_PART}, /* recovery         64M  p29*/
    {PART_DTS,               64*1024,  EMMC_USER_PART}, /* dtimage          64M  p30*/
    {PART_MODEM,             64*1024,  EMMC_USER_PART}, /* modem            64M  p31*/
    {PART_MODEM_DSP,         16*1024,  EMMC_USER_PART}, /* modem_dsp        16M  p32*/
    {PART_MODEM_DTB,         8*1024,   EMMC_USER_PART}, /* modem_dtb        8M   p33*/
    {PART_DFX,               16*1024,  EMMC_USER_PART}, /* dfx              16M  p34*/
    {PART_3RDMODEM,          64*1024,  EMMC_USER_PART}, /* 3rdmodem         64M  p35*/
    {PART_CACHE,             256*1024, EMMC_USER_PART}, /* cache            256M p36*/
    {PART_HISITEST0,         2*1024,   EMMC_USER_PART}, /* hisitest0        2M   p37*/
    {PART_HISITEST1,         2*1024,   EMMC_USER_PART}, /* hisitest1        2M   p38*/
    {PART_SYSTEM,            2560*1024,EMMC_USER_PART}, /* system           2560M p40*/
    {PART_CUST,              512*1024, EMMC_USER_PART}, /* cust             512M  p41*/
    {PART_HISITEST2,         4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p39*/
    {PART_USERDATA,          4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
    {"0", 0, 0},                                        /* total 8204M*/
};

#elif defined (CONFIG_HISI_PARTITION_HI6250)
static const struct partition partition_table[] =
{
    {PART_XLOADER,           256,      BOOT_PART},
    {PART_PTABLE,            512,      EMMC_USER_PART}, /* ptable           512K */
    {PART_VRL,               256,      EMMC_USER_PART}, /* VRL              256K p1*/
    {PART_VRL_BACKUP,        256,      EMMC_USER_PART}, /* VRL backup       256K p2*/
    {PART_FW_LPM3,           256,      EMMC_USER_PART}, /* mcuimage         256K p3*/
    {PART_FRP,               768,      EMMC_USER_PART}, /* frp              768K p4*/
    {PART_FASTBOOT,          4*1024,   EMMC_USER_PART}, /* fastboot         4M   p5*/
    {PART_MODEMNVM_FACTORY,  4*1024,   EMMC_USER_PART}, /* modemnvm factory 4M   p6*/
    {PART_NVME,              6*1024,   EMMC_USER_PART}, /* nvme             6M   p7*/
    {PART_OEMINFO,           64*1024,  EMMC_USER_PART}, /* oeminfo          64M  p8*/
    {PART_RESERVED3,         4*1024,   EMMC_USER_PART}, /* reserved3        4M   p9*/
    {PART_MODEMNVM_BACKUP,   4*1024,   EMMC_USER_PART}, /* modemnvm backup  4M   p10*/
    {PART_MODEMNVM_IMG,      8*1024,   EMMC_USER_PART}, /* modemnvm img     8M   p11*/
    {PART_MODEMNVM_SYSTEM,   4*1024,   EMMC_USER_PART}, /* modemnvm system  4M   p12*/
    {PART_SECURE_STORAGE,    32*1024,  EMMC_USER_PART}, /* secure storage   32M  p13*/
    {PART_RESERVED4,         2*1024,   EMMC_USER_PART}, /* reserved4        2M   p14*/
    {PART_RESERVED5,         2*1024,   EMMC_USER_PART}, /* reserved5        2M   p15*/
    {PART_PERSIST,           2*1024,   EMMC_USER_PART}, /* persist          2M   p16*/
    {PART_RESERVED1,         14*1024,  EMMC_USER_PART}, /* reserved1        14M  p17*/
    {PART_MODEM_OM,          32*1024,  EMMC_USER_PART}, /* modem om         32M  p18*/
    {PART_SPLASH2,           64*1024,  EMMC_USER_PART}, /* splash2          64M  p19*/
    {PART_MISC,              2*1024,   EMMC_USER_PART}, /* misc             2M   p20*/
    {PART_MODEMNVM_UPDATE,   24*1024,  EMMC_USER_PART}, /* modemnvm update  24M  p21*/
    {PART_RECOVERY2,         64*1024,  EMMC_USER_PART}, /* recovery2        64M  p22*/
    {PART_RESERVED2,         60*1024,  EMMC_USER_PART}, /* reserved2        60M  p23*/
    {PART_TEEOS,             4*1024,   EMMC_USER_PART}, /* teeos            4M   p24*/
    {PART_TRUSTFIRMWARE,     2*1024,   EMMC_USER_PART}, /* trustfirmware    2M   p25*/
    {PART_SENSORHUB,         16*1024,  EMMC_USER_PART}, /* sensorhub        16M  p26*/
    {PART_FW_HIFI,           12*1024,  EMMC_USER_PART}, /* hifi             12M  p27*/
    {PART_BOOT,              32*1024,  EMMC_USER_PART}, /* boot             32M  p28*/
    {PART_RECOVERY,          64*1024,  EMMC_USER_PART}, /* recovery         64M  p29*/
    {PART_DTS,               32*1024,  EMMC_USER_PART}, /* dtimage          32M  p30*/
    {PART_MODEM_FW,          96*1024,  EMMC_USER_PART}, /* modem_fw         96M  p31*/
    {PART_RESERVED7,         2*1024,   EMMC_USER_PART}, /* reserved7        2M   p32*/
    {PART_RESERVED8,         2*1024,   EMMC_USER_PART}, /* reserved8        2M   p33*/
    {PART_DFX,               16*1024,  EMMC_USER_PART}, /* dfx              16M  p34*/
    {PART_RESERVED6,         4*1024,   EMMC_USER_PART}, /* reserved6        4M   p35*/
    {PART_CACHE,             256*1024, EMMC_USER_PART}, /* cache            256M p36*/
    {PART_HISITEST0,         2*1024,   EMMC_USER_PART}, /* hisitest0        2M   p37*/
    {PART_HISITEST1,         2*1024,   EMMC_USER_PART}, /* hisitest1        2M   p38*/
    {PART_HISITEST2,         4*1024,   EMMC_USER_PART}, /* hisitest2        4M   p39*/
    {PART_SYSTEM,            2560*1024,EMMC_USER_PART}, /* system           2560M p40*/
    {PART_CUST,              512*1024, EMMC_USER_PART}, /* cust             512M  p41*/
    {PART_USERDATA,          4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
    {"0", 0, 0},                                        /* Total  8112M*/
};

#elif defined CONFIG_HISI_PARTITION_HI3660
static const struct partition partition_table[] =
{
    {PART_XLOADER,          256,      BOOT_PART},
    {PART_PTABLE,           512,      EMMC_USER_PART}, /* ptable           512K */
    {PART_VRL,              256,      EMMC_USER_PART}, /* VRL              256K p1*/
    {PART_VRL_BACKUP,       256,      EMMC_USER_PART}, /* VRL backup       256K p2*/
    {PART_FW_LPM3,          256,      EMMC_USER_PART}, /* mcuimage         256K p3*/
    {PART_FRP,              768,      EMMC_USER_PART}, /* frp              768K p4*/
    {PART_FASTBOOT,         4*1024,   EMMC_USER_PART}, /* fastboot         4M   p5*/
    {PART_MODEMNVM_FACTORY, 4*1024,   EMMC_USER_PART}, /* modemnvm factory 4M   p6*/
    {PART_NVME,             6*1024,   EMMC_USER_PART}, /* nvme             6M   p7*/
    {PART_OEMINFO,          64*1024,  EMMC_USER_PART}, /* oeminfo          64M  p8*/
    {PART_RESERVED3,        4*1024,   EMMC_USER_PART}, /* reserved         4M   p9*/
    {PART_MODEMNVM_BACKUP,  4*1024,   EMMC_USER_PART}, /* modemnvm backup  4M   p10*/
    {PART_MODEMNVM_IMG,     8*1024,   EMMC_USER_PART}, /* modemnvm img     8M   p11*/
    {PART_MODEMNVM_SYSTEM,  4*1024,   EMMC_USER_PART}, /* modemnvm system  4M   p12*/
    {PART_SECURE_STORAGE,   32*1024,  EMMC_USER_PART}, /* secure storage   32M  p13*/
    {PART_HISEE_IMG,        10*1024,  EMMC_USER_PART}, /* hisee_img        10M  p14*/
    {PART_ISP_BOOT,         2*1024,   EMMC_USER_PART}, /* isp_boot         2M   p15*/
    {PART_PERSIST,          2*1024,   EMMC_USER_PART}, /* persist          2M   p16*/
    {PART_ISP_FIRMWARE,     14*1024,  EMMC_USER_PART}, /* isp_firmware     14M  p17*/
    {PART_MODEM_OM,         32*1024,  EMMC_USER_PART}, /* modem om         32M  p18*/
    {PART_SPLASH2,          64*1024,  EMMC_USER_PART}, /* splash2          64M  p19*/
    {PART_MISC,             2*1024,   EMMC_USER_PART}, /* misc             2M   p20*/
    {PART_MODEMNVM_UPDATE,  24*1024,  EMMC_USER_PART}, /* modemnvm update  24M  p21*/
    {PART_RECOVERY2,        64*1024,  EMMC_USER_PART}, /* recovery2        64M  p22*/
    {PART_RESERVED2,        60*1024,  EMMC_USER_PART}, /* reserved2        60M  p23*/
    {PART_TEEOS,            8*1024,   EMMC_USER_PART}, /* teeos            8M   p24*/
    {PART_TRUSTFIRMWARE,    2*1024,   EMMC_USER_PART}, /* trustfirmware    2M   p25*/
    {PART_SENSORHUB,        16*1024,  EMMC_USER_PART}, /* sensorhub        16M  p26*/
    {PART_FW_HIFI,          12*1024,  EMMC_USER_PART}, /* hifi             12M  p27*/
    {PART_BOOT,             32*1024,  EMMC_USER_PART}, /* boot             32M  p28*/
    {PART_RECOVERY,         64*1024,  EMMC_USER_PART}, /* recovery         64M  p29*/
    {PART_DTS,              32*1024,  EMMC_USER_PART}, /* dtimage          32M  p30*/
    {PART_MODEM_FW,         96*1024,  EMMC_USER_PART}, /* modemi_fw        96M  p31*/
    {PART_ISP_DTS,          32*1024,  EMMC_USER_PART}, /* isp_dts          32M  p32*/
    {PART_HISEE_FS,         4*1024,   EMMC_USER_PART}, /* hisee_fs         4M   p33*/
    {PART_DFX,              16*1024,  EMMC_USER_PART}, /* dfx              16M  p34*/
    {PART_RESERVED1,        8*1024,   EMMC_USER_PART},  /* reserved1        8M  p35*/
    {PART_CACHE,            256*1024, EMMC_USER_PART}, /* cache            256M p36*/
    {PART_HISITEST0,        2*1024,   EMMC_USER_PART}, /* hisitest0        2M   p37*/
    {PART_HISITEST1,        2*1024,   EMMC_USER_PART}, /* hisitest1        2M   p38*/
    {PART_HISITEST2,        4*1024,   EMMC_USER_PART}, /* hisitest2        4M   p39*/
    {PART_SYSTEM,           2560*1024,EMMC_USER_PART}, /* system           2560M p40*/
    {PART_CUST,             512*1024, EMMC_USER_PART}, /* cust             512M p41*/
    {PART_USERDATA,         4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
    {"0", 0, 0},                                       /* Total  8112M*/
};
#endif

#endif

