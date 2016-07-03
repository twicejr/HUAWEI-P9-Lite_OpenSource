

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CTF_INTERFACE_H__
#define __SOC_CTF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：电压扫描寄存器。
   位域定义UNION结构:  SOC_CTF_VSCAN_UNION */
#define SOC_CTF_VSCAN_ADDR(base)                      ((base) + (0x000))

/* 寄存器说明：标识寄存器0。
   位域定义UNION结构:  SOC_CTF_PTN0_UNION */
#define SOC_CTF_PTN0_ADDR(base)                       ((base) + (0x010))

/* 寄存器说明：标识寄存器1。
   位域定义UNION结构:  SOC_CTF_PTN1_UNION */
#define SOC_CTF_PTN1_ADDR(base)                       ((base) + (0x014))

/* 寄存器说明：标识寄存器2。
   位域定义UNION结构:  SOC_CTF_PTN2_UNION */
#define SOC_CTF_PTN2_ADDR(base)                       ((base) + (0x018))

/* 寄存器说明：标识寄存器3。
   位域定义UNION结构:  SOC_CTF_PTN3_UNION */
#define SOC_CTF_PTN3_ADDR(base)                       ((base) + (0x01C))

/* 寄存器说明：标识寄存器4。
   位域定义UNION结构:  SOC_CTF_PTN4_UNION */
#define SOC_CTF_PTN4_ADDR(base)                       ((base) + (0x020))

/* 寄存器说明：标识寄存器5。
   位域定义UNION结构:  SOC_CTF_PTN5_UNION */
#define SOC_CTF_PTN5_ADDR(base)                       ((base) + (0x024))

/* 寄存器说明：标识寄存器6。
   位域定义UNION结构:  SOC_CTF_PTN6_UNION */
#define SOC_CTF_PTN6_ADDR(base)                       ((base) + (0x028))

/* 寄存器说明：标识寄存器7。
   位域定义UNION结构:  SOC_CTF_PTN7_UNION */
#define SOC_CTF_PTN7_ADDR(base)                       ((base) + (0x02C))

/* 寄存器说明：SGI中断屏蔽寄存器。
   位域定义UNION结构:  SOC_CTF_SGIMASK_UNION */
#define SOC_CTF_SGIMASK_ADDR(base)                    ((base) + (0x040))

/* 寄存器说明：PPI中断屏蔽寄存器。
   位域定义UNION结构:  SOC_CTF_PPIMASK_UNION */
#define SOC_CTF_PPIMASK_ADDR(base)                    ((base) + (0x044))

/* 寄存器说明：核间共享中断屏蔽寄存器。
   位域定义UNION结构:  SOC_CTF_SPIMASK_UNION */
#define SOC_CTF_SPIMASK_ADDR(base)                    ((base) + (0x048))

/* 寄存器说明：SGI中断分组寄存器。
   位域定义UNION结构:  SOC_CTF_SGIGROUP_UNION */
#define SOC_CTF_SGIGROUP_ADDR(base)                   ((base) + (0x04C))

/* 寄存器说明：PPI中断分组寄存器。
   位域定义UNION结构:  SOC_CTF_PPIGROUP_UNION */
#define SOC_CTF_PPIGROUP_ADDR(base)                   ((base) + (0x050))

/* 寄存器说明：核间共享中断分组寄存器。
   位域定义UNION结构:  SOC_CTF_SPIGROUP_UNION */
#define SOC_CTF_SPIGROUP_ADDR(base)                   ((base) + (0x054))

/* 寄存器说明：APB写入冲突指示寄存器。
   位域定义UNION结构:  SOC_CTF_APB_WR_ERR_UNION */
#define SOC_CTF_APB_WR_ERR_ADDR(base)                 ((base) + (0x058))

/* 寄存器说明：核间共享中断使能寄存器。
   位域定义UNION结构:  SOC_CTF_SPI_INT_EN_UNION */
#define SOC_CTF_SPI_INT_EN_ADDR(base)                 ((base) + (0x060))

/* 寄存器说明：核间共享中断清除寄存器。
   位域定义UNION结构:  SOC_CTF_SPI_INT_CLR_UNION */
#define SOC_CTF_SPI_INT_CLR_ADDR(base)                ((base) + (0x064))

/* 寄存器说明：核间共享中断原始状态寄存器。
   位域定义UNION结构:  SOC_CTF_SPI_RAWSTAT_UNION */
#define SOC_CTF_SPI_RAWSTAT_ADDR(base)                ((base) + (0x068))

/* 寄存器说明：核间共享中断目标寄存器0。
   位域定义UNION结构:  SOC_CTF_SPITARG0_UNION */
#define SOC_CTF_SPITARG0_ADDR(base)                   ((base) + (0x070))

/* 寄存器说明：核间共享中断目标寄存器1。
   位域定义UNION结构:  SOC_CTF_SPITARG1_UNION */
#define SOC_CTF_SPITARG1_ADDR(base)                   ((base) + (0x0074))

/* 寄存器说明：核间共享中断目标寄存器2。
   位域定义UNION结构:  SOC_CTF_SPITARG2_UNION */
#define SOC_CTF_SPITARG2_ADDR(base)                   ((base) + (0x078))

/* 寄存器说明：核间共享中断目标寄存器3。
   位域定义UNION结构:  SOC_CTF_SPITARG3_UNION */
#define SOC_CTF_SPITARG3_ADDR(base)                   ((base) + (0x07C))

/* 寄存器说明：SGI中断产生寄存器。
   位域定义UNION结构:  SOC_CTF_SGIG_UNION */
#define SOC_CTF_SGIG_ADDR(base, N)                    ((base) + (0x000 + 0x400 + 0x80*(N)))

/* 寄存器说明：SGIPending状态寄存器0。
   位域定义UNION结构:  SOC_CTF_SGIPSTAT0_UNION */
#define SOC_CTF_SGIPSTAT0_ADDR(base, N)               ((base) + (0x004 + 0x400 + 0x80*(N)))

/* 寄存器说明：SGIPending状态寄存器1。
   位域定义UNION结构:  SOC_CTF_SGIPSTAT1_UNION */
#define SOC_CTF_SGIPSTAT1_ADDR(base, N)               ((base) + (0x008 + 0x400 + 0x80*(N)))

/* 寄存器说明：PPIPending状态寄存器。
   位域定义UNION结构:  SOC_CTF_PPIPSTAT_UNION */
#define SOC_CTF_PPIPSTAT_ADDR(base, N)                ((base) + (0x00C + 0x400 + 0x80*(N)))

/* 寄存器说明：核间共享中断Pending状态寄存器。
   位域定义UNION结构:  SOC_CTF_SPIPSTAT_UNION */
#define SOC_CTF_SPIPSTAT_ADDR(base, N)                ((base) + (0x010 + 0x400 + 0x80*(N)))

/* 寄存器说明：中断确认寄存器。
   位域定义UNION结构:  SOC_CTF_IAR_UNION */
#define SOC_CTF_IAR_ADDR(base, N)                     ((base) + (0x040 + 0x400 + 0x80*(N)))

/* 寄存器说明：中断结束寄存器。
   位域定义UNION结构:  SOC_CTF_EOIR_UNION */
#define SOC_CTF_EOIR_ADDR(base, N)                    ((base) + (0x044 + 0x400 + 0x80*(N)))

/* 寄存器说明：中断信号寄存器。
   位域定义UNION结构:  SOC_CTF_OUTSTAT_UNION */
#define SOC_CTF_OUTSTAT_ADDR(base, N)                 ((base) + (0x048 + 0x400 + 0x80*(N)))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CTF_VSCAN_UNION
 结构说明  : VSCAN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 电压扫描寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctf_vscan_en : 1;  /* bit[0]   : 仅允许被APB_MCU接口访问，不允许被APB_CPU接口访问。指示当前ACPU是否处于电压扫描模式。复位值为0。 0：非电压扫描模式； 1：电压扫描模式。 */
        unsigned int  reserved     : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_CTF_VSCAN_UNION;
#endif
#define SOC_CTF_VSCAN_ctf_vscan_en_START  (0)
#define SOC_CTF_VSCAN_ctf_vscan_en_END    (0)


/*****************************************************************************
 结构名    : SOC_CTF_PTN0_UNION
 结构说明  : PTN0 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten0 : 32; /* bit[0-31]: 相应的Core在完成测试代码后将指定pattern写入到对应的标识寄存器，以供LPM3从LP_PERI_APB总线APB接口读取CTF内部的寄存器值，判断ACPU是否在当前电压能正确执行测试代码。 */
    } reg;
} SOC_CTF_PTN0_UNION;
#endif
#define SOC_CTF_PTN0_patten0_START  (0)
#define SOC_CTF_PTN0_patten0_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN1_UNION
 结构说明  : PTN1 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN1_UNION;
#endif
#define SOC_CTF_PTN1_patten1_START  (0)
#define SOC_CTF_PTN1_patten1_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN2_UNION
 结构说明  : PTN2 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN2_UNION;
#endif
#define SOC_CTF_PTN2_patten2_START  (0)
#define SOC_CTF_PTN2_patten2_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN3_UNION
 结构说明  : PTN3 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN3_UNION;
#endif
#define SOC_CTF_PTN3_patten3_START  (0)
#define SOC_CTF_PTN3_patten3_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN4_UNION
 结构说明  : PTN4 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten4 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN4_UNION;
#endif
#define SOC_CTF_PTN4_patten4_START  (0)
#define SOC_CTF_PTN4_patten4_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN5_UNION
 结构说明  : PTN5 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten5 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN5_UNION;
#endif
#define SOC_CTF_PTN5_patten5_START  (0)
#define SOC_CTF_PTN5_patten5_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN6_UNION
 结构说明  : PTN6 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten6 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN6_UNION;
#endif
#define SOC_CTF_PTN6_patten6_START  (0)
#define SOC_CTF_PTN6_patten6_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PTN7_UNION
 结构说明  : PTN7 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 标识寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten7 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN7_UNION;
#endif
#define SOC_CTF_PTN7_patten7_START  (0)
#define SOC_CTF_PTN7_patten7_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SGIMASK_UNION
 结构说明  : SGIMASK 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: SGI中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgimask  : 8;  /* bit[0-7] : Each bit corresponds to SGI INTID 7~0.Active low. 0: mask（mask有效）; 1: not mask（mask无效）. */
        unsigned int  reserved : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_CTF_SGIMASK_UNION;
#endif
#define SOC_CTF_SGIMASK_sgimask_START   (0)
#define SOC_CTF_SGIMASK_sgimask_END     (7)


/*****************************************************************************
 结构名    : SOC_CTF_PPIMASK_UNION
 结构说明  : PPIMASK 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: PPI中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppimask  : 2;  /* bit[29-30]: Each bit corresponds to PPI INTID 30~29 0: mask（mask有效）; 
                                                    1: not mask（mask无效）. */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIMASK_UNION;
#endif
#define SOC_CTF_PPIMASK_ppimask_START   (29)
#define SOC_CTF_PPIMASK_ppimask_END     (30)


/*****************************************************************************
 结构名    : SOC_CTF_SPIMASK_UNION
 结构说明  : SPIMASK 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spimask  : 16; /* bit[0-15] : Each bit corresponds to SPI INTID 47~32 */
        unsigned int  reserved : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIMASK_UNION;
#endif
#define SOC_CTF_SPIMASK_spimask_START   (0)
#define SOC_CTF_SPIMASK_spimask_END     (15)


/*****************************************************************************
 结构名    : SOC_CTF_SGIGROUP_UNION
 结构说明  : SGIGROUP 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: SGI中断分组寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgigroup : 8;  /* bit[0-7] : Each bit corresponds to SGI INTID 7~0; 
                                                   0：以安全中断FIQ的形式 1：以非安全中断IRQ的形式送给相应的core interface。 */
        unsigned int  reserved : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_CTF_SGIGROUP_UNION;
#endif
#define SOC_CTF_SGIGROUP_sgigroup_START  (0)
#define SOC_CTF_SGIGROUP_sgigroup_END    (7)


/*****************************************************************************
 结构名    : SOC_CTF_PPIGROUP_UNION
 结构说明  : PPIGROUP 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: PPI中断分组寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppigroup : 2;  /* bit[29-30]: Each bit corresponds to PPI INTID 30~29; 0：以安全中断FIQ的形式 1：以非安全中断IRQ的形式送给相应的core interface。 */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIGROUP_UNION;
#endif
#define SOC_CTF_PPIGROUP_ppigroup_START  (29)
#define SOC_CTF_PPIGROUP_ppigroup_END    (30)


/*****************************************************************************
 结构名    : SOC_CTF_SPIGROUP_UNION
 结构说明  : SPIGROUP 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断分组寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spigroup : 16; /* bit[0-15] : Each bit corresponds to SPI INTID 47~32; 0：以安全中断FIQ的形式 1：以非安全中断IRQ的形式送给相应的core interface。 */
        unsigned int  reserved : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIGROUP_UNION;
#endif
#define SOC_CTF_SPIGROUP_spigroup_START  (0)
#define SOC_CTF_SPIGROUP_spigroup_END    (15)


/*****************************************************************************
 结构名    : SOC_CTF_APB_WR_ERR_UNION
 结构说明  : APB_WR_ERR 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: APB写入冲突指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_wr_err : 1;  /* bit[0]   : APB_MCU和APB_CPU同时写入同一地址的写操作冲突指示。读清。 0: 无冲突；
                                                     1：有冲突 */
        unsigned int  reserved   : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_CTF_APB_WR_ERR_UNION;
#endif
#define SOC_CTF_APB_WR_ERR_apb_wr_err_START  (0)
#define SOC_CTF_APB_WR_ERR_apb_wr_err_END    (0)


/*****************************************************************************
 结构名    : SOC_CTF_SPI_INT_EN_UNION
 结构说明  : SPI_INT_EN 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_int_en : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_en[15:0] corresponds to SPI INTID 47~32. 0：对应的SPI INTID中断pending状态不变；1：对应的SPI INTID中断pending状态使能。  */
        unsigned int  reserved            : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_INT_EN_UNION;
#endif
#define SOC_CTF_SPI_INT_EN_mcu2acpu_raw_int_en_START  (0)
#define SOC_CTF_SPI_INT_EN_mcu2acpu_raw_int_en_END    (15)


/*****************************************************************************
 结构名    : SOC_CTF_SPI_INT_CLR_UNION
 结构说明  : SPI_INT_CLR 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_int_clr : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_clr[15:0] corresponds to SPI INTID 47~32. 0：不清除对应的SPI INTID中断； 1：清除对应的SPI INTID中断。 */
        unsigned int  reserved             : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_INT_CLR_UNION;
#endif
#define SOC_CTF_SPI_INT_CLR_mcu2acpu_raw_int_clr_START  (0)
#define SOC_CTF_SPI_INT_CLR_mcu2acpu_raw_int_clr_END    (15)


/*****************************************************************************
 结构名    : SOC_CTF_SPI_RAWSTAT_UNION
 结构说明  : SPI_RAWSTAT 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断原始状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_status : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_status[15:0] corresponds to SPI INTID 47~32. LPM3通过配置mcu2acpu_raw_int_en将mcu2acpu_raw_status对应Bit置高；ACPU通过配置mcu2acpu_raw_int_clr将mcu2acpu_raw_status对应Bit拉低。 */
        unsigned int  reserved            : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_RAWSTAT_UNION;
#endif
#define SOC_CTF_SPI_RAWSTAT_mcu2acpu_raw_status_START  (0)
#define SOC_CTF_SPI_RAWSTAT_mcu2acpu_raw_status_END    (15)


/*****************************************************************************
 结构名    : SOC_CTF_SPITARG0_UNION
 结构说明  : SPITARG0 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断目标寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 32, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 33, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 34, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: 用于指示将核间共享中断发送到哪几个Core. InterfaceFor SPI INTID 35, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID35 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG0_UNION;
#endif
#define SOC_CTF_SPITARG0_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG0_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG0_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG0_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG0_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG0_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG0_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG0_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SPITARG1_UNION
 结构说明  : SPITARG1 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断目标寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 36, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 37, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 38, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 39, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID39 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG1_UNION;
#endif
#define SOC_CTF_SPITARG1_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG1_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG1_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG1_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG1_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG1_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG1_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG1_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SPITARG2_UNION
 结构说明  : SPITARG2 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断目标寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 40, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 41, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 42, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 43, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID43 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG2_UNION;
#endif
#define SOC_CTF_SPITARG2_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG2_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG2_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG2_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG2_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG2_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG2_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG2_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SPITARG3_UNION
 结构说明  : SPITARG3 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断目标寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 44, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 45, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 46, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 47, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID47 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG3_UNION;
#endif
#define SOC_CTF_SPITARG3_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG3_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG3_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG3_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG3_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG3_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG3_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG3_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SGIG_UNION
 结构说明  : SGIG 寄存器结构定义。地址偏移量:0x000 + 0x400 + 0x80*(N)，初值:0x00000000，宽度:32
 寄存器说明: SGI中断产生寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgig_id           : 3;  /* bit[0-2]  : The Interrupt ID of the SGI to forward to the specified CPU interfaces. The value of this field is the Interrupt ID, in the range 0-7, for example a value of 3'b011 specifiies interrupt ID 3. */
        unsigned int  reserved_0        : 13; /* bit[3-15] : reserved */
        unsigned int  sgi_cputargetlist : 8;  /* bit[16-23]: CPU Core N (N: 0~7)的SGI中断产生。Each bit of CPUTargetList[7:0] refers to the corresponding CPU interface, for example CPUTargetList[0] corresponds to CPU interface 0. Setting a bit to 1 indicates that the interrupt must be forwarded to the corresponding interface. */
        unsigned int  reserved_1        : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_CTF_SGIG_UNION;
#endif
#define SOC_CTF_SGIG_sgig_id_START            (0)
#define SOC_CTF_SGIG_sgig_id_END              (2)
#define SOC_CTF_SGIG_sgi_cputargetlist_START  (16)
#define SOC_CTF_SGIG_sgi_cputargetlist_END    (23)


/*****************************************************************************
 结构名    : SOC_CTF_SGIPSTAT0_UNION
 结构说明  : SGIPSTAT0 寄存器结构定义。地址偏移量:0x004 + 0x400 + 0x80*(N)，初值:0x00000102，宽度:32
 寄存器说明: SGIPending状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgid0_status : 8;  /* bit[0-7]  : Each bit of sgiid0[7:0] refers to the corresponding source CPU ID for SGI INTID 0. */
        unsigned int  sgid1_status : 8;  /* bit[8-15] : Each bit of sgiid0[15:8] refers to the corresponding source CPU ID for SGI INTID 1. */
        unsigned int  sgid2_status : 8;  /* bit[16-23]: Each bit of sgiid1[23:16] refers to the corresponding source CPU ID for SGI INTID 2. */
        unsigned int  sgid3_status : 8;  /* bit[24-31]: Each bit of sgiid0[31:24] refers to the corresponding source CPU ID for SGI INTID 3. */
    } reg;
} SOC_CTF_SGIPSTAT0_UNION;
#endif
#define SOC_CTF_SGIPSTAT0_sgid0_status_START  (0)
#define SOC_CTF_SGIPSTAT0_sgid0_status_END    (7)
#define SOC_CTF_SGIPSTAT0_sgid1_status_START  (8)
#define SOC_CTF_SGIPSTAT0_sgid1_status_END    (15)
#define SOC_CTF_SGIPSTAT0_sgid2_status_START  (16)
#define SOC_CTF_SGIPSTAT0_sgid2_status_END    (23)
#define SOC_CTF_SGIPSTAT0_sgid3_status_START  (24)
#define SOC_CTF_SGIPSTAT0_sgid3_status_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_SGIPSTAT1_UNION
 结构说明  : SGIPSTAT1 寄存器结构定义。地址偏移量:0x008 + 0x400 + 0x80*(N)，初值:0x00000102，宽度:32
 寄存器说明: SGIPending状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgid4_status : 8;  /* bit[0-7]  : Each bit of sgiid0[7:0] refers to the corresponding source CPU ID for SGI INTID 4. */
        unsigned int  sgid5_status : 8;  /* bit[8-15] : Each bit of sgiid0[15:8] refers to the corresponding source CPU ID for SGI INTID 5. */
        unsigned int  sgid6_status : 8;  /* bit[16-23]: Each bit of sgiid1[23:16] refers to the corresponding source CPU ID for SGI INTID 6. */
        unsigned int  sgid7_status : 8;  /* bit[24-31]: Each bit of sgiid0[31:24] refers to the corresponding source CPU ID for SGI INTID 7. */
    } reg;
} SOC_CTF_SGIPSTAT1_UNION;
#endif
#define SOC_CTF_SGIPSTAT1_sgid4_status_START  (0)
#define SOC_CTF_SGIPSTAT1_sgid4_status_END    (7)
#define SOC_CTF_SGIPSTAT1_sgid5_status_START  (8)
#define SOC_CTF_SGIPSTAT1_sgid5_status_END    (15)
#define SOC_CTF_SGIPSTAT1_sgid6_status_START  (16)
#define SOC_CTF_SGIPSTAT1_sgid6_status_END    (23)
#define SOC_CTF_SGIPSTAT1_sgid7_status_START  (24)
#define SOC_CTF_SGIPSTAT1_sgid7_status_END    (31)


/*****************************************************************************
 结构名    : SOC_CTF_PPIPSTAT_UNION
 结构说明  : PPIPSTAT 寄存器结构定义。地址偏移量:0x00C + 0x400 + 0x80*(N)，初值:0x00000000，宽度:32
 寄存器说明: PPIPending状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppistatus : 2;  /* bit[29-30]: 指示PPI中断的当前状态
                                                     bit 30: PPI ID30 - Non-secure physical timer event
                                                     bit 29: PPI ID29- Secure physical timer event  */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIPSTAT_UNION;
#endif
#define SOC_CTF_PPIPSTAT_ppistatus_START  (29)
#define SOC_CTF_PPIPSTAT_ppistatus_END    (30)


/*****************************************************************************
 结构名    : SOC_CTF_SPIPSTAT_UNION
 结构说明  : SPIPSTAT 寄存器结构定义。地址偏移量:0x010 + 0x400 + 0x80*(N)，初值:0x00000000，宽度:32
 寄存器说明: 核间共享中断Pending状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spistatus : 16; /* bit[0-15] : 指示SPI中断的当前状态 */
        unsigned int  reserved  : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIPSTAT_UNION;
#endif
#define SOC_CTF_SPIPSTAT_spistatus_START  (0)
#define SOC_CTF_SPIPSTAT_spistatus_END    (15)


/*****************************************************************************
 结构名    : SOC_CTF_IAR_UNION
 结构说明  : IAR 寄存器结构定义。地址偏移量:0x040 + 0x400 + 0x80*(N)，初值:0x000003FF，宽度:32
 寄存器说明: 中断确认寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iar_intid : 10; /* bit[0-9]  : 中断号 */
        unsigned int  iar_cpuid : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回发出中断请求的CPU接口编号；对于所有其他中断，该域返回0 */
        unsigned int  reserved  : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_CTF_IAR_UNION;
#endif
#define SOC_CTF_IAR_iar_intid_START  (0)
#define SOC_CTF_IAR_iar_intid_END    (9)
#define SOC_CTF_IAR_iar_cpuid_START  (10)
#define SOC_CTF_IAR_iar_cpuid_END    (12)


/*****************************************************************************
 结构名    : SOC_CTF_EOIR_UNION
 结构说明  : EOIR 寄存器结构定义。地址偏移量:0x044 + 0x400 + 0x80*(N)，初值:0x000003FF，宽度:32
 寄存器说明: 中断结束寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  eoir_intid : 10; /* bit[0-9]  : 中断号，与GICC_IAR一致 */
        unsigned int  eoir_cpuid : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域与GICC_IAR一致；对于所有其他中断，该域无效 */
        unsigned int  reserved   : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_CTF_EOIR_UNION;
#endif
#define SOC_CTF_EOIR_eoir_intid_START  (0)
#define SOC_CTF_EOIR_eoir_intid_END    (9)
#define SOC_CTF_EOIR_eoir_cpuid_START  (10)
#define SOC_CTF_EOIR_eoir_cpuid_END    (12)


/*****************************************************************************
 结构名    : SOC_CTF_OUTSTAT_UNION
 结构说明  : OUTSTAT 寄存器结构定义。地址偏移量:0x048 + 0x400 + 0x80*(N)，初值:0x00000003，宽度:32
 寄存器说明: 中断信号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nfiq_stat : 1;  /* bit[0]   : 输出至CPU CoreN的FIQ信号。active low。 */
        unsigned int  nirq_stat : 1;  /* bit[1]   : 输出至CPU CoreN的IRQ信号。Active low。 */
        unsigned int  reserved  : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_CTF_OUTSTAT_UNION;
#endif
#define SOC_CTF_OUTSTAT_nfiq_stat_START  (0)
#define SOC_CTF_OUTSTAT_nfiq_stat_END    (0)
#define SOC_CTF_OUTSTAT_nirq_stat_START  (1)
#define SOC_CTF_OUTSTAT_nirq_stat_END    (1)






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

#endif /* end of soc_ctf_interface.h */
