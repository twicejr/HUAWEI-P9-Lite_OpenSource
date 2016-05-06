/*
* hissc.h   --  HISSC ALSA Soc codec driver
*/

#ifndef _HISSC_H
#define _HISSC_H


/*****************************************************************************
* MACRO DEFINE BEGIN
*****************************************************************************/

#define PAGE_SoCCODEC              0x0000
#define PAGE_SmartStarCODEC        0x1000
#define PAGE_SmartStarHKADC        0x2000
#define PAGE_PeriSCTRL             0x3000
#define PAGE_PMCTRL                0x4000
#define PAGE_MISCCODEC             0x7000
#define PAGE_VIRCODEC              0x8000

#define PAGE_TYPE_MASK             0xF000
#define PAGE_VALUE_MASK            0x0FFF

/* codec page */
#define HISSC_PAGE_0_START         (PAGE_SoCCODEC + 0x00)
#define HISSC_PAGE_0_END           (PAGE_SoCCODEC + 0x88)
#define HISSC_PAGE_0C_START        (PAGE_SoCCODEC + 0xE8)
#define HISSC_PAGE_0C_END          (PAGE_SoCCODEC + 0xFC)
#define HISSC_PAGE_1_START         (PAGE_SmartStarCODEC + 0x1b0)
#define HISSC_PAGE_1_END           (PAGE_SmartStarCODEC + 0x1e4)
#define HISSC_PAGE_2_START         (PAGE_SmartStarHKADC + 0x00)
#define HISSC_PAGE_2_END           (PAGE_SmartStarHKADC + 0x09)
#define HISSC_PAGE_4_START         (PAGE_PMCTRL + 0x29)
#define HISSC_PAGE_4_END           (PAGE_PMCTRL + 0x31)
#define HISSC_PAGE_4C_START        (PAGE_PMCTRL + 0x69)
#define HISSC_PAGE_4C_END          (PAGE_PMCTRL + 0x6B)
#define HISSC_PAGE_4L_START        (PAGE_PMCTRL + 0x71)
#define HISSC_PAGE_4L_END          (PAGE_PMCTRL + 0x87)
#define HISSC_PAGE_4L1                  (PAGE_PMCTRL + 0x71)
#define HISSC_PAGE_4L5                  (PAGE_PMCTRL + 0x76)
#define HISSC_PAGE_4L12                 (PAGE_PMCTRL + 0x7D)
#define HISSC_PAGE_4L15                 (PAGE_PMCTRL + 0x80)
#define HISSC_PAGE_4L18                 (PAGE_PMCTRL + 0x83)

/* tools interface */
#define HISSC_CLASSD_POWER_IF    (0x11)
#define HISSC_CODEC_SOCCLK_IF    (0x278)
#define HISSC_ECO_DISABLE_IF     (0xfff)
#define HISSC_DISABLE        (0)
#define HISSC_ENABLE         (1)

/* virtual reg */
#define HISSC_DDR_CODEC_VIR0_ADDR             ((PAGE_VIRCODEC) + (0x00))
#define HISSC_DDR_CODEC_VIR1_ADDR             ((PAGE_VIRCODEC) + (0x01))

#define DDR_CODEC_BIT0  0
#define DDR_CODEC_BIT1  1
#define DDR_CODEC_BIT2  2
#define DDR_CODEC_BIT3  3
#define DDR_CODEC_BIT4  4
#define DDR_CODEC_BIT5  5
#define DDR_CODEC_BIT6  6
#define DDR_CODEC_BIT7  7
#define DDR_CODEC_BIT8  8
#define DDR_CODEC_BIT9  9
#define DDR_CODEC_BIT10 10
#define DDR_CODEC_BIT11 11
#define DDR_CODEC_BIT12 12
#define DDR_CODEC_BIT13 13
#define DDR_CODEC_BIT14 14
#define DDR_CODEC_BIT15 15
#define DDR_CODEC_BIT16 16
#define DDR_CODEC_BIT17 17
#define DDR_CODEC_BIT18 18
#define DDR_CODEC_BIT19 19
#define DDR_CODEC_BIT20 20
#define DDR_CODEC_BIT21 21
#define DDR_CODEC_BIT22 22
#define DDR_CODEC_BIT23 23
#define DDR_CODEC_BIT24 24
#define DDR_CODEC_BIT25 25
#define DDR_CODEC_BIT26 26
#define DDR_CODEC_BIT27 27
#define DDR_CODEC_BIT28 28
#define DDR_CODEC_BIT29 29
#define DDR_CODEC_BIT30 30
#define DDR_CODEC_BIT31 31

#define INVALID_REG                 0xE000
#define INVALID_REG_VALUE           0xFFFFFFFF


#define HISSC_OFF          0
#define HISSC_ON           1
#define HISSC_ECO_ON       2


/* eco mode */
#define HISSC_EXIT              0
#define HISSC_ENTER             1
#define HISSC_DELAY_ENTER       2

#define HISSC_VERSION      0x30
#define STATUS_OK    0
#define STATUS_ERROR 1

#ifdef CONFIG_DEBUG_FS
/* catch size */
#define REG_CACHE_NUM_MAX       1024
#define REG_CACHE_FLAG_WRITE    (0x01 << 16)
#define REG_CACHE_FLAG_READ     (0x02 << 16)
#define REG_CACHE_FLAG_MASK     (0xFF << 16)

#define HISSC_DBG_SIZE_PAGE         2048
#define HISSC_DBG_SIZE_WIDGET       8192
#define HISSC_DBG_SIZE_PATH         16384
/* single line max size is
time,w reg val
8(time) +3 +4(reg) +1 +8(val) +1 = 25
min size is
time,r reg
8(time) +3 +4(reg) +1 = 16
so allocate 6 pages(=24K)
*/
#define HISSC_DBG_SIZE_CACHE        (24*REG_CACHE_NUM_MAX)
#endif

/* Debug info */
#define ERROR_LEVEL     1
#define INFO_LEVEL      1
#define DEBUG_LEVEL     0

#define LOG_TAG "hissc"
#ifndef LOG_TAG
#define LOG_TAG "hissc"
#endif

#if INFO_LEVEL
#define logi(fmt, ...) pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logi(fmt, ...)
#endif

#if DEBUG_LEVEL
#define logd(fmt, ...) pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logd(fmt, ...)
#endif

#if ERROR_LEVEL
#define loge(fmt, ...) pr_err(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define loge(fmt, ...)
#endif

#endif /* _HISSC_H */
