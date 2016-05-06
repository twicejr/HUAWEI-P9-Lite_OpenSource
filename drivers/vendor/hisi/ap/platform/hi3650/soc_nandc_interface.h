/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_nandc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:21
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_NANDC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_NANDC_INTERFACE_H__
#define __SOC_NANDC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：数据读写数目寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_DATANUM_UNION */
#define SOC_NANDC_NFC_DATANUM_ADDR(base)              ((base) + (0x00))

/* 寄存器说明：等待控制寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_WSC_UNION */
#define SOC_NANDC_NFC_WSC_ADDR(base)                  ((base) + (0x04))

/* 寄存器说明：器件配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_DEVCFG_UNION */
#define SOC_NANDC_NFC_DEVCFG_ADDR(base)               ((base) + (0x08))

/* 寄存器说明：命令配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_CMDCFG_UNION */
#define SOC_NANDC_NFC_CMDCFG_ADDR(base)               ((base) + (0x0C))

/* 寄存器说明：命令寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_COM_UNION */
#define SOC_NANDC_NFC_COM_ADDR(base)                  ((base) + (0x10))

/* 寄存器说明：地位地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_ADDRL_UNION */
#define SOC_NANDC_NFC_ADDRL_ADDR(base)                ((base) + (0x14))

/* 寄存器说明：高位地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_ADDRH_UNION */
#define SOC_NANDC_NFC_ADDRH_ADDR(base)                ((base) + (0x18))

/* 寄存器说明：NANDC buffer配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_BUFEN_UNION */
#define SOC_NANDC_NFC_BUFEN_ADDR(base)                ((base) + (0x1C))

/* 寄存器说明：buffer读写控制寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_BUFCTRL_UNION */
#define SOC_NANDC_NFC_BUFCTRL_ADDR(base)              ((base) + (0x20))

/* 寄存器说明：中断使能寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_INTEN_UNION */
#define SOC_NANDC_NFC_INTEN_ADDR(base)                ((base) + (0x24))

/* 寄存器说明：中断状态寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_INTSTATUS_UNION */
#define SOC_NANDC_NFC_INTSTATUS_ADDR(base)            ((base) + (0x28))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_INTCLR_UNION */
#define SOC_NANDC_NFC_INTCLR_ADDR(base)               ((base) + (0x2C))

/* 寄存器说明：读启动寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_STARTRD_UNION */
#define SOC_NANDC_NFC_STARTRD_ADDR(base)              ((base) + (0x30))

/* 寄存器说明：cs don’t care模式使能寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_CSDNEN_UNION */
#define SOC_NANDC_NFC_CSDNEN_ADDR(base)               ((base) + (0x34))

/* 寄存器说明：锁起始地址1配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_SA1_UNION */
#define SOC_NANDC_NFC_LOCK_SA1_ADDR(base)             ((base) + (0x38))

/* 寄存器说明：锁存结束地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_ED1_UNION */
#define SOC_NANDC_NFC_LOCK_ED1_ADDR(base)             ((base) + (0x3C))

/* 寄存器说明：锁起始地址2配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_SA2_UNION */
#define SOC_NANDC_NFC_LOCK_SA2_ADDR(base)             ((base) + (0x40))

/* 寄存器说明：锁存结束地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_ED2_UNION */
#define SOC_NANDC_NFC_LOCK_ED2_ADDR(base)             ((base) + (0x44))

/* 寄存器说明：锁起始地址2配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_SA3_UNION */
#define SOC_NANDC_NFC_LOCK_SA3_ADDR(base)             ((base) + (0x48))

/* 寄存器说明：锁存结束地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_ED3_UNION */
#define SOC_NANDC_NFC_LOCK_ED3_ADDR(base)             ((base) + (0x4C))

/* 寄存器说明：锁起始地址1配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_SA4_UNION */
#define SOC_NANDC_NFC_LOCK_SA4_ADDR(base)             ((base) + (0x50))

/* 寄存器说明：锁存结束地址配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_LOCK_ED4_UNION */
#define SOC_NANDC_NFC_LOCK_ED4_ADDR(base)             ((base) + (0x54))

/* 寄存器说明：Flashlock使能寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_ADDR(base)     ((base) + (0x58))

/* 寄存器说明：Flashlock控制寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_ADDR(base)     ((base) + (0x5C))

/* 寄存器说明：Flashlock命令配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_FLASHLOCK_COM1_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_COM1_ADDR(base)       ((base) + (0x60))

/* 寄存器说明：Flashlock命令配置寄存器
   位域定义UNION结构:  SOC_NANDC_NFC_FLASHLOCK_COM2_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_COM2_ADDR(base)       ((base) + (0x64))





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_NANDC_NFC_DATANUM_UNION
 结构说明  : NFC_DATANUM 寄存器结构定义。地址偏移量:0x00，初值:0x00000840，宽度:32
 寄存器说明: 数据读写数目寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_num : 12; /* bit[0-11] : 读写byte的数目。0：读写0个byte。
                                                    缺省读写2112 (528*4) byte。 */
        unsigned int  reserved : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_DATANUM_UNION;
#endif
#define SOC_NANDC_NFC_DATANUM_data_num_START  (0)
#define SOC_NANDC_NFC_DATANUM_data_num_END    (11)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_WSC_UNION
 结构说明  : NFC_WSC 寄存器结构定义。地址偏移量:0x04，初值:0x0000F333，宽度:32
 寄存器说明: 等待控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wt_pulse        : 4;  /* bit[0-3]  : NandFlash写信号低电平宽度。
                                                           4’b0000，一个时钟周期
                                                           ～
                                                           4’b1111：16个时钟周期 */
        unsigned int  rd_pulse        : 4;  /* bit[4-7]  : NandFlash读信号低电平宽度。
                                                           4’b0000，一个时钟周期
                                                           ～
                                                           4’b1111：16个时钟周期 */
        unsigned int  rdwt_high       : 4;  /* bit[8-11] : NandFlash读/写信号高电平宽度
                                                           4’b0001，2个时钟周期
                                                           ～
                                                           4’b1111：16个时钟周期
                                                           注：不能配置为0。 */
        unsigned int  wait_busy       : 4;  /* bit[12-15]: NandFlash命令或最后一个地址到busy状态的延时。
                                                           4’h0，2个时钟周期。
                                                           4’hF：32个时钟周期 */
        unsigned int  cs_wait_wide_wr : 4;  /* bit[16-19]: cs don’t care情况下ready/busy信号拉低后到cs无效的延迟时间：
                                                           4’h0，0个时钟周期。
                                                           4’hF：15个时钟周期 */
        unsigned int  reserved        : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_WSC_UNION;
#endif
#define SOC_NANDC_NFC_WSC_wt_pulse_START         (0)
#define SOC_NANDC_NFC_WSC_wt_pulse_END           (3)
#define SOC_NANDC_NFC_WSC_rd_pulse_START         (4)
#define SOC_NANDC_NFC_WSC_rd_pulse_END           (7)
#define SOC_NANDC_NFC_WSC_rdwt_high_START        (8)
#define SOC_NANDC_NFC_WSC_rdwt_high_END          (11)
#define SOC_NANDC_NFC_WSC_wait_busy_START        (12)
#define SOC_NANDC_NFC_WSC_wait_busy_END          (15)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_START  (16)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_END    (19)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_DEVCFG_UNION
 结构说明  : NFC_DEVCFG 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 器件配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_size : 1;  /* bit[0]   : NandFlash的页大小。
                                                    0：512 byte/page
                                                    1：2K byte/page。
                                                    复位值由管脚nand_page_size取反决定 */
        unsigned int  bus_wide  : 1;  /* bit[1]   : NandFlash的数据线宽度。
                                                    0：8bit。1：16bit。
                                                    复位值由管脚nand_bus_wide决定。 */
        unsigned int  reserved  : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_DEVCFG_UNION;
#endif
#define SOC_NANDC_NFC_DEVCFG_page_size_START  (0)
#define SOC_NANDC_NFC_DEVCFG_page_size_END    (0)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_START   (1)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_END     (1)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_CMDCFG_UNION
 结构说明  : NFC_CMDCFG 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 命令配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_num      : 3;  /* bit[0-2]  : Controller发给NandFlash的地址拍数。
                                                         缺省值由管脚nand_addr_num[1:0]决定，关系如下。
                                                         nand_addr_num＝0——address cycles＝5；nand_addr_num＝1——address cycles＝4；nand_addr_num＝2——address cycles＝3。 */
        unsigned int  reserved_0    : 1;  /* bit[3]    : 保留 */
        unsigned int  ca_sequence   : 1;  /* bit[4]    : Controller发给NandFlash的命令地址格式
                                                         0：发送“comand1＋地址”
                                                         1：发送“comand1＋地址＋command2”。
                                                         复位值由管脚nand_page_size决定。nand_page_size等于0：复位值为0。nand_page_size等于1：复位值为1。 */
        unsigned int  com_only      : 1;  /* bit[5]    : 0：Controller发送命令地址后，根据Controller当前的读写状态，启动读写数据状态机。
                                                         1：Controller只发送命令地址，不启动读写数据状态机。 */
        unsigned int  rdwt_mode     : 1;  /* bit[6]    : 0：从NandFlash读数据
                                                         1：向NandFlash写数据 */
        unsigned int  busy_not_care : 1;  /* bit[7]    : 0：在busy状态下不能向nand flash发送命令；
                                                         1：在busy状态下可以向nand flash发送命令 */
        unsigned int  cs_sel        : 2;  /* bit[8-9]  : CS select。
                                                         00：选择cs0_n；
                                                         01：选择cs1_n；
                                                         10：选择cs2_n；
                                                         11：选择cs3_n。 */
        unsigned int  reserved_1    : 2;  /* bit[10-11]: 保留 */
        unsigned int  ebi_n         : 1;  /* bit[12]   : 0：CS don’t care时EBI不拉低；
                                                         1：CS don’t care时EBI也拉低。 */
        unsigned int  reserved_2    : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_CMDCFG_UNION;
#endif
#define SOC_NANDC_NFC_CMDCFG_addr_num_START       (0)
#define SOC_NANDC_NFC_CMDCFG_addr_num_END         (2)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_START    (4)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_END      (4)
#define SOC_NANDC_NFC_CMDCFG_com_only_START       (5)
#define SOC_NANDC_NFC_CMDCFG_com_only_END         (5)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_START      (6)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_END        (6)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_START  (7)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_END    (7)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_START         (8)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_END           (9)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_START          (12)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_END            (12)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_COM_UNION
 结构说明  : NFC_COM 寄存器结构定义。地址偏移量:0x10，初值:0x00003000，宽度:32
 寄存器说明: 命令寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command1 : 8;  /* bit[0-7]  : Controller发给NandFlash的第一个命令 */
        unsigned int  command2 : 8;  /* bit[8-15] : Controller发给NandFlash的第二个命令 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_COM_UNION;
#endif
#define SOC_NANDC_NFC_COM_command1_START  (0)
#define SOC_NANDC_NFC_COM_command1_END    (7)
#define SOC_NANDC_NFC_COM_command2_START  (8)
#define SOC_NANDC_NFC_COM_command2_END    (15)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_ADDRL_UNION
 结构说明  : NFC_ADDRL 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 地位地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_l : 32; /* bit[0-31]: NANDFlash低32bit地址。 */
    } reg;
} SOC_NANDC_NFC_ADDRL_UNION;
#endif
#define SOC_NANDC_NFC_ADDRL_addr_l_START  (0)
#define SOC_NANDC_NFC_ADDRL_addr_l_END    (31)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_ADDRH_UNION
 结构说明  : NFC_ADDRH 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 高位地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_h   : 8;  /* bit[0-7] : NANDFlash高16bit地址。 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_ADDRH_UNION;
#endif
#define SOC_NANDC_NFC_ADDRH_addr_h_START    (0)
#define SOC_NANDC_NFC_ADDRH_addr_h_END      (7)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_BUFEN_UNION
 结构说明  : NFC_BUFEN 寄存器结构定义。地址偏移量:0x1C，初值:0x00000006，宽度:32
 寄存器说明: NANDC buffer配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  boot_mode_n     : 1;  /* bit[0]   : 0：NandFlash Controller处于boot模式。
                                                          1：NandFlash Controller处于normal模式。 */
        unsigned int  ecc_bypass      : 1;  /* bit[1]   : 0：ECC校验使能。1：ECC校验禁止。 */
        unsigned int  secc_bypass     : 1;  /* bit[2]   : 0：LSN数据ECC校验使能。
                                                          1：LSN数据ECC校验禁止。 */
        unsigned int  ecc_crct_bypass : 1;  /* bit[3]   : 0：ECC 1bit纠错使能。
                                                          1：ECC 1bit纠错禁止。 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_BUFEN_UNION;
#endif
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_START      (0)
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_END        (0)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_START       (1)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_END         (1)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_START      (2)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_END        (2)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_START  (3)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_END    (3)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_BUFCTRL_UNION
 结构说明  : NFC_BUFCTRL 寄存器结构定义。地址偏移量:0x20，初值:0x0000000F，宽度:32
 寄存器说明: buffer读写控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffer_ready : 4;  /* bit[0-3] : 每个bit对应一个buffer。
                                                       读数据时，从NandFlash读取的数据，写到从bit0开始，第一个状态为1的buffer，到最后一个状态为1的buffer。
                                                       写数据时，从bit0开始，第一个bit为1的buffer的数据写到NandFlash */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_BUFCTRL_UNION;
#endif
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_START  (0)
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_END    (3)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_INTEN_UNION
 结构说明  : NFC_INTEN 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: 中断使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cod_done_cs0_en        : 1;  /* bit[0]    : Controller向CS0外接器件发送完命令和地址后，使能产生中断 */
        unsigned int  read_done_cs0_en       : 1;  /* bit[1]    : CS0外接器件读操作结束，使能产生中断 */
        unsigned int  write_done_cs0_en      : 1;  /* bit[2]    : CS0外接器件写操作结束，使能产生中断 */
        unsigned int  reserved_0             : 1;  /* bit[3]    : 保留位 */
        unsigned int  cod_done_cs1_en        : 1;  /* bit[4]    : Controller向CS1外接器件发送完命令和地址后，使能产生中断 */
        unsigned int  read_done_cs1_en       : 1;  /* bit[5]    : CS1外接器件读操作结束，使能产生中断 */
        unsigned int  write_done_cs1_en      : 1;  /* bit[6]    : CS1外接器件写操作结束，使能产生中断 */
        unsigned int  reserved_1             : 1;  /* bit[7]    : 保留位 */
        unsigned int  cod_done_cs2_en        : 1;  /* bit[8]    : Controller向CS2外接器件发送完命令和地址后，使能产生中断 */
        unsigned int  read_done_cs2_en       : 1;  /* bit[9]    : CS2外接器件读操作结束，使能产生中断 */
        unsigned int  write_done_cs2_en      : 1;  /* bit[10]   : CS2外接器件写操作结束，使能产生中断 */
        unsigned int  reserved_2             : 1;  /* bit[11]   : 保留位 */
        unsigned int  cod_done_cs3_en        : 1;  /* bit[12]   : Controller向CS3外接器件发送完命令和地址后，使能产生中断 */
        unsigned int  read_done_cs3_en       : 1;  /* bit[13]   : CS3外接器件读操作结束，使能产生中断 */
        unsigned int  write_done_cs3_en      : 1;  /* bit[14]   : Ecc 2bits 使能报错中断：
                                                                  如果bit[21]为1，指示1bit中断，那么bit[14]同时指示为0，才是真正的1bit error中断；
                                                                  如果bit[21]为1，指示1bit中断，而bit[14]也为1，那么不是1bit error的情况，而是2bits error报错为1bit error的情况； */
        unsigned int  reserved_3             : 1;  /* bit[15]   : 保留 */
        unsigned int  allbufferready_en      : 1;  /* bit[16]   : 读状态下，所有buffer数据有效，使能产生中断 */
        unsigned int  buffer1_ready_en       : 1;  /* bit[17]   : 读状态下，buffer1数据有效，使能产生中断。 */
        unsigned int  buffer2_ready_en       : 1;  /* bit[18]   : 读状态下，buffer2数据有效，使能产生中断。 */
        unsigned int  buffer3_ready_en       : 1;  /* bit[19]   : 读状态下，buffer3数据有效，使能产生中断。 */
        unsigned int  buffer4_ready_en       : 1;  /* bit[20]   : 读状态下，buffer4数据有效，使能产生中断信号。 */
        unsigned int  data_ecc_1bit_error_en : 1;  /* bit[21]   : ecc校验1bit出错，使能产生中断信号 */
        unsigned int  data_ecc_2bit_error_en : 1;  /* bit[22]   : ecc校验2bit以上出错，使能产生中断信号 */
        unsigned int  lsn_ecc_1bit_error_en  : 1;  /* bit[23]   : lsn 数据ecc校验1bit出错，使能产生中断信号 */
        unsigned int  lsn_ecc_2bit_error_en  : 1;  /* bit[24]   : lsn 数据ecc校验2bit以上出错，使能产生中断信号 */
        unsigned int  flashlock_error_en     : 1;  /* bit[25]   : 非法改写flashlock内容出错，使能产生中断信号 */
        unsigned int  reserved_4             : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_INTEN_UNION;
#endif
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_START         (0)
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_END           (0)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_START        (1)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_END          (1)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_START       (2)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_END         (2)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_START         (4)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_END           (4)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_START        (5)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_END          (5)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_START       (6)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_END         (6)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_START         (8)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_END           (8)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_START        (9)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_END          (9)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_START       (10)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_END         (10)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_START         (12)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_END           (12)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_START        (13)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_END          (13)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_START       (14)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_END         (14)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_START       (16)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_END         (16)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_START        (17)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_END          (17)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_START        (18)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_END          (18)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_START        (19)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_END          (19)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_START        (20)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_END          (20)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_START  (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_END    (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_START  (22)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_END    (22)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_START   (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_END     (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_START   (24)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_END     (24)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_START      (25)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_END        (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_INTSTATUS_UNION
 结构说明  : NFC_INTSTATUS 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cod_done_cs0        : 1;  /* bit[0]    : Controller向CS0外接器件发送完命令和地址后，产生中断信号 */
        unsigned int  read_done_cs0       : 1;  /* bit[1]    : CS0外接器件读操作结束，产生中断 */
        unsigned int  write_done_cs0      : 1;  /* bit[2]    : CS0外接器件写操作结束，产生中断信号 */
        unsigned int  reserved_0          : 1;  /* bit[3]    : 保留 */
        unsigned int  cod_done_cs1        : 1;  /* bit[4]    : Controller向CS1外接器件发送完命令和地址后，产生中断信号 */
        unsigned int  read_done_cs1       : 1;  /* bit[5]    : CS1外接器件读操作结束，产生中断信号 */
        unsigned int  write_done_cs1      : 1;  /* bit[6]    : CS1外接器件写操作结束，产生中断信号 */
        unsigned int  reserved_1          : 1;  /* bit[7]    : 保留 */
        unsigned int  cod_done_cs2        : 1;  /* bit[8]    : Controller向CS2外接器件发送完命令和地址后，产生中断信号 */
        unsigned int  read_done_cs2       : 1;  /* bit[9]    : CS2外接器件读操作结束，产生中断信号 */
        unsigned int  write_done_cs2      : 1;  /* bit[10]   : CS2外接器件写操作结束，产生中断信号 */
        unsigned int  reserved_2          : 1;  /* bit[11]   : 保留 */
        unsigned int  cod_done_cs3        : 1;  /* bit[12]   : Controller向CS3外接器件发送完命令和地址后，产生中断信号 */
        unsigned int  read_done_cs3       : 1;  /* bit[13]   : CS3外接器件读操作结束，产生中断信号 */
        unsigned int  write_done_cs3      : 1;  /* bit[14]   : CS3外接器件写操作结束，产生中断信号 */
        unsigned int  reserved_3          : 1;  /* bit[15]   : 保留 */
        unsigned int  allbufferready      : 1;  /* bit[16]   : 读状态下，所有buffer数据有效，产生中断信号 */
        unsigned int  buffer1_ready       : 1;  /* bit[17]   : 读状态下，buffer1数据有效，产生中断信号。 */
        unsigned int  buffer2_ready       : 1;  /* bit[18]   : 读状态下，buffer2数据有效，产生中断信号。 */
        unsigned int  buffer3_ready       : 1;  /* bit[19]   : 读状态下，buffer3数据有效，产生中断信号。 */
        unsigned int  buffer4_ready       : 1;  /* bit[20]   : 读状态下，buffer4数据有效，产生中断信号。 */
        unsigned int  data_ecc_1bit_error : 1;  /* bit[21]   : ecc校验1bit出错，产生中断信号 */
        unsigned int  data_ecc_2bit_error : 1;  /* bit[22]   : ecc校验2bit以上出错，产生中断信号 */
        unsigned int  lsn_ecc_1bit_error  : 1;  /* bit[23]   : lsn 数据ecc校验1bit以上出错，产生中断信号 */
        unsigned int  lsn_ecc_2bit_error  : 1;  /* bit[24]   : lsn 数据ecc校验2bit以上出错，产生中断信号 */
        unsigned int  flashlock_error     : 1;  /* bit[25]   : 非法改写flashlock内容出错，产生中断信号 */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_INTSTATUS_UNION;
#endif
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_START         (0)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_END           (0)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_START        (1)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_END          (1)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_START       (2)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_END         (2)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_START         (4)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_END           (4)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_START        (5)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_END          (5)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_START       (6)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_END         (6)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_START         (8)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_END           (8)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_START        (9)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_END          (9)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_START       (10)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_END         (10)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_START         (12)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_END           (12)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_START        (13)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_END          (13)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_START       (14)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_END         (14)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_START       (16)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_END         (16)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_START        (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_END          (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_START        (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_END          (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_START        (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_END          (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_START        (20)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_END          (20)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_START  (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_END    (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_START  (22)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_END    (22)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_START   (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_END     (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_START   (24)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_END     (24)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_START      (25)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_END        (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_INTCLR_UNION
 结构说明  : NFC_INTCLR 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command_done_cs0    : 1;  /* bit[0]    : 清除Controller向CS0外接器件发送完命令和地址后产生的中断 */
        unsigned int  read_done_cs0       : 1;  /* bit[1]    : 清除CS0外接器件读操作结束产生的中断 */
        unsigned int  write_done_cs0      : 1;  /* bit[2]    : 清除CS0外接器件写操作结束产生清除中断 */
        unsigned int  reserved_0          : 1;  /* bit[3]    : 保留位 */
        unsigned int  command_done_cs1    : 1;  /* bit[4]    : 清除Controller向CS1外接器件发送完命令和地址后产生的中断 */
        unsigned int  read_done_cs1       : 1;  /* bit[5]    : 清除CS1外接器件读操作结束产生的中断 */
        unsigned int  write_done_cs1      : 1;  /* bit[6]    : 清除CS1外接器件写操作结束产生的中断 */
        unsigned int  reserved_1          : 1;  /* bit[7]    : 保留位 */
        unsigned int  command_done_cs2    : 1;  /* bit[8]    : 清除Controller向CS2外接器件发送完命令和地址后产生的中断 */
        unsigned int  read_done_cs2       : 1;  /* bit[9]    : 清除CS2外接器件读操作结束产生的中断 */
        unsigned int  write_done_cs2      : 1;  /* bit[10]   : 清除CS2外接器件写操作结束产生的中断 */
        unsigned int  reserved_2          : 1;  /* bit[11]   : 保留位 */
        unsigned int  command_done_cs3    : 1;  /* bit[12]   : 清除Controller向CS3外接器件发送完命令和地址后产生的中断 */
        unsigned int  read_done_cs3       : 1;  /* bit[13]   : 清除CS3外接器件读操作结束产生的中断 */
        unsigned int  write_done_cs3      : 1;  /* bit[14]   : 清除Ecc 2bits 报错产生的中断：
                                                               如果bit[21]为1，指示1bit中断，那么bit[14]同时指示为0，才是真正的1bit error中断；
                                                               如果bit[21]为1，指示1bit中断，而bit[14]也为1，那么不是1bit error的情况，而是2bits error报错为1bit error的情况； */
        unsigned int  reserved_3          : 1;  /* bit[15]   : 保留位 */
        unsigned int  all_buffer_ready    : 1;  /* bit[16]   : 清除读状态下，所有buffer数据有效产生的中断 */
        unsigned int  buffer1_ready       : 1;  /* bit[17]   : 清除读状态下，buffer1数据有效产生的中断。  */
        unsigned int  buffer2_ready       : 1;  /* bit[18]   : 清除读状态下，buffer2数据有效产生的中断。 */
        unsigned int  buffer3_ready       : 1;  /* bit[19]   : 清除读状态下，buffer3数据有效产生的中断。 */
        unsigned int  buffer4_ready       : 1;  /* bit[20]   : 清除读状态下，buffer4数据有效产生的中断 */
        unsigned int  data_ecc_1bit_error : 1;  /* bit[21]   : 清楚ecc校验1bit以上出错产生的中断 */
        unsigned int  data_ecc_2bit_error : 1;  /* bit[22]   : 清除ecc校验2bit以上出错产生的中断 */
        unsigned int  lsn_err_1bit_error  : 1;  /* bit[23]   : 清除lsn 数据ecc校验1bit出错产生的中断 */
        unsigned int  lsn_err_2bit_error  : 1;  /* bit[24]   : 清除lsn 数据ecc校验2bit以上出错产生的中断 */
        unsigned int  flashlock_error     : 1;  /* bit[25]   : 清除非法改写flashlock内容出错产生的中断 */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_INTCLR_UNION;
#endif
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_START     (0)
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_END       (0)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_START        (1)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_END          (1)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_START       (2)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_END         (2)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_START     (4)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_END       (4)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_START        (5)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_END          (5)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_START       (6)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_END         (6)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_START     (8)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_END       (8)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_START        (9)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_END          (9)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_START       (10)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_END         (10)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_START     (12)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_END       (12)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_START        (13)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_END          (13)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_START       (14)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_END         (14)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_START     (16)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_END       (16)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_START        (17)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_END          (17)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_START        (18)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_END          (18)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_START        (19)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_END          (19)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_START        (20)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_END          (20)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_START  (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_END    (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_START  (22)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_END    (22)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_START   (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_END     (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_START   (24)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_END     (24)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_START      (25)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_END        (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_STARTRD_UNION
 结构说明  : NFC_STARTRD 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 读启动寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  write_only_self_clear : 1;  /* bit[0]   : 启动读数据状态机 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_STARTRD_UNION;
#endif
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_START  (0)
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_END    (0)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_CSDNEN_UNION
 结构说明  : NFC_CSDNEN 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: cs don’t care模式使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csdnen   : 1;  /* bit[0]   : 使能nand flash controller的cs don’t care工作模式 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_CSDNEN_UNION;
#endif
#define SOC_NANDC_NFC_CSDNEN_csdnen_START    (0)
#define SOC_NANDC_NFC_CSDNEN_csdnen_END      (0)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_SA1_UNION
 结构说明  : NFC_LOCK_SA1 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 锁起始地址1配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr1 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved              : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_SA1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_START  (0)
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_ED1_UNION
 结构说明  : NFC_LOCK_ED1 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 锁存结束地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr1 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved            : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_ED1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_START  (0)
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_SA2_UNION
 结构说明  : NFC_LOCK_SA2 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: 锁起始地址2配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr2 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved              : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_SA2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_START  (0)
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_ED2_UNION
 结构说明  : NFC_LOCK_ED2 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: 锁存结束地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr2 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved            : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_ED2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_START  (0)
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_SA3_UNION
 结构说明  : NFC_LOCK_SA3 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 锁起始地址2配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr3 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved              : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_SA3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_START  (0)
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_ED3_UNION
 结构说明  : NFC_LOCK_ED3 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: 锁存结束地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr3 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved            : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_ED3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_START  (0)
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_SA4_UNION
 结构说明  : NFC_LOCK_SA4 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 锁起始地址1配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr4 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved              : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_SA4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_START  (0)
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_LOCK_ED4_UNION
 结构说明  : NFC_LOCK_ED4 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: 锁存结束地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr4 : 26; /* bit[0-25] : 表示flashlock起始地址，高2比特表示flash片选，低24比特表示nandflash的row地址 */
        unsigned int  reserved            : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_LOCK_ED4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_START  (0)
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_END    (25)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION
 结构说明  : NFC_FLASHLOCK_ENABLE 寄存器结构定义。地址偏移量:0x58，初值:0x00000003，宽度:32
 寄存器说明: Flashlock使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_whole_enable : 1;  /* bit[0]   : flashlock全局使能/去使能，默认flashlock全局使能. */
        unsigned int  flashlock_enable       : 1;  /* bit[1]   : 表示flashlock使能/去使能，默认flashlock使能. */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_END    (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_START        (1)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_END          (1)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION
 结构说明  : NFC_FLASHLOCK_CONTRL 寄存器结构定义。地址偏移量:0x5C，初值:0x00000000，宽度:32
 寄存器说明: Flashlock控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashloc_control : 1;  /* bit[0]   : 表示flashlock模式：
                                                           0表示：lock模式；
                                                           1表示：lock-down模式
                                                           该比特一次性写1配置 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_END    (0)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_FLASHLOCK_COM1_UNION
 结构说明  : NFC_FLASHLOCK_COM1 寄存器结构定义。地址偏移量:0x60，初值:0x85816060，宽度:32
 寄存器说明: Flashlock命令配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  block_command1 : 8;  /* bit[0-7]  : 表示flashlock block操作命令寄存器1 */
        unsigned int  block_command2 : 8;  /* bit[8-15] : 表示flashlock block操作命令寄存器2 */
        unsigned int  page_command1  : 8;  /* bit[16-23]: 表示flashlock page操作命令寄存器1 */
        unsigned int  page_command2  : 8;  /* bit[24-31]: 表示flashlock page操作命令寄存器2 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM1_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_END    (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_START  (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_END    (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_START   (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_END     (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_START   (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_END     (31)


/*****************************************************************************
 结构名    : SOC_NANDC_NFC_FLASHLOCK_COM2_UNION
 结构说明  : NFC_FLASHLOCK_COM2 寄存器结构定义。地址偏移量:0x64，初值:0x85858585，宽度:32
 寄存器说明: Flashlock命令配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_command3 : 8;  /* bit[0-7]  : 表示flashlock page操作命令寄存器3 */
        unsigned int  page_command4 : 8;  /* bit[8-15] : 表示flashlock page操作命令寄存器4 */
        unsigned int  page_command5 : 8;  /* bit[16-23]: 表示flashlock page操作命令寄存器5 */
        unsigned int  page_command6 : 8;  /* bit[24-31]: 表示flashlock page操作命令寄存器6 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM2_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_END    (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_START  (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_END    (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_START  (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_END    (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_START  (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_END    (31)






/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_nandc_interface.h */
