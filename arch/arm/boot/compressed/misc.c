

unsigned int __machine_arch_type;

#include <linux/compiler.h>	/* for inline */
#include <linux/types.h>
#include <linux/linkage.h>
#include "soc_baseaddr_interface.h"
#include "soc_ao_sctrl_interface.h"


#ifdef CONFIG_SRECORDER

#include <linux/srecorder.h>


/*----local macroes------------------------------------------------------------------*/

#define CRASH_REASON_POWER_COLLAPSE "Crash reason: powercollapse "
#define CRASH_DEFAULT_TIME_POWER_COLLAPSE "Crash time: Unknown\n"
#define LOG_BUF_MASK(log_buf_len) ((log_buf_len) - 1)


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/

static const unsigned long s_crc32tab[256] =
{
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};


/*----local function prototypes---------------------------------------------------------*/

#ifdef CONFIG_POWERCOLLAPSE
#ifdef CONFIG_DUMP_LOGCAT
static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src, logcat_buf_info *plogcat_buf_info);
#else
static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src);
#endif
#endif
static inline int strcpy_valid_char(char *pdst, char *psrc, int bytes_to_write);
static inline void copy_data(char *pdst, char *psrc, int bytes_to_copy);
static inline int str_len(char *psrc);
static inline void write_info_header(unsigned long header_addr, srecorder_info_type_e type,
    unsigned long data_len, char *keyword);
static unsigned long get_crc32(unsigned char const *pbuf, unsigned long data_len);
static inline unsigned long dump_dmesg(char *pdst, char *psrc, unsigned log_end, unsigned log_buf_len);
static inline unsigned long dump_need_reparsed_dmesg(char *pdst, char *psrc, unsigned log_buf_len);
#ifdef CONFIG_DUMP_LOGCAT
static inline unsigned long dump_logcat(char *pdst, logcat_buf_info *plogcat_buf_info, int count);
#endif
static inline void do_nothing(void)
{
    return;
}
#endif /* CONFIG_SRECORDER */
static void putstr(const char *ptr);
extern void error(char *x);

#include CONFIG_UNCOMPRESS_INCLUDE

#ifdef CONFIG_DEBUG_ICEDCC

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K) || defined(CONFIG_CPU_V7)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c0, c1, 0" : "=r" (status));
	} while (status & (1 << 29));

	asm("mcr p14, 0, %0, c0, c5, 0" : : "r" (ch));
}


#elif defined(CONFIG_CPU_XSCALE)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c14, c0, 0" : "=r" (status));
	} while (status & (1 << 28));

	asm("mcr p14, 0, %0, c8, c0, 0" : : "r" (ch));
}

#else

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c0, c0, 0" : "=r" (status));
	} while (status & 2);

	asm("mcr p14, 0, %0, c1, c0, 0" : : "r" (ch));
}

#endif

#define putc(ch)	icedcc_putc(ch)
#endif

static void putstr(const char *ptr)
{
	char c;

    if ('A' != *(volatile int *)SOC_AO_SCTRL_SC_RESERVED31_ADDR(SOC_AO_SCTRL_BASE_ADDR)){
        return;
    }

	while ((c = *ptr++) != '\0') {
		if (c == '\n')
			putc('\r');
		putc(c);
	}

	flush();
}

/*
 * gzip declarations
 */
extern char input_data[];
extern char input_data_end[];

unsigned char *output_data;

unsigned long free_mem_ptr;
unsigned long free_mem_end_ptr;

#ifndef arch_error
#define arch_error(x)
#endif

void error(char *x)
{
	arch_error(x);

	putstr("\n\n");
	putstr(x);
	putstr("\n\n -- System halted");

	while(1);	/* Halt */
}

asmlinkage void __div0(void)
{
	error("Attempting division by 0!");
}

extern int do_decompress(u8 *input, int len, u8 *output, void (*error)(char *x));


#ifdef CONFIG_SRECORDER
void *__memcpy(void *dest, const void *src, size_t count)
{
    char *tmp = dest;
    const char *s = src;

    while (count--)
    {
        *tmp++ = *s++;
    }

    return dest;
}


void *__memset(void *s, int c, size_t count)
{
    char *xs = s;

    while (count--)
    {
        *xs++ = c;
    }

    return s;
}


/**
    @function: static inline int strcpy_valid_char(char *pdst, char *psrc, int bytes_to_write)
    @brief: write bytes_to_write bytes data form psrc to pdst

    @param: pdst
    @param: psrc
    @param: bytes_to_write

    @return: the bytes have been written to the pdst

    @note:
*/
static inline int strcpy_valid_char(char *pdst, char *psrc, int bytes_to_write)
{
    int i = 0;
    int j = 0;
    char c = 0;

    for (i = 0; i < bytes_to_write; i++)
    {
        c = *(psrc + i);

        /*if (c > 127 || 0 == c)
        {
            continue;
        }*/

        *(pdst + j) = c;
        j++;
    }

    return j;
}


/**
    @function: static inline void copy_data(char *pdst, char *psrc, int bytes_to_copy)
    @brief: copy data form psrc to pdst

    @param: pdst
    @param: psrc
    @param: bytes_to_copy

    @return: none

    @note:
*/
static inline void copy_data(char *pdst, char *psrc, int bytes_to_copy)
{
    while (bytes_to_copy-- > 0)
    {
        *pdst++ = *psrc++;
    }
}


/**
    @function: static inline int str_len(char *psrc)
    @brief: calculate the string's length

    @param: psrc

    @return: length of the string

    @note:
*/
static inline int str_len(char *psrc)
{
    char *ptemp = psrc;

    for (ptemp = psrc; '\0' != *psrc; psrc++)
    {
        ;
    }

    return psrc - ptemp;
}


/**
    @function: static inline void write_info_header(unsigned long header_addr,
        srecorder_info_type_e type, unsigned long data_len, char *keyword)
    @brief: header including check 12 bytes check header and the keyword of for every type of log

    @param: header_addr header start address
    @param: type log type
    @param: data_len lengh of the valid data including keyword and the content for every type of log
    @param: keyword log's description

    @return: none

    @note:
*/
static inline void write_info_header(unsigned long header_addr,
    srecorder_info_type_e type, unsigned long data_len, char *keyword)
{
    unsigned long buf[2] = {0, 0};
    int keyword_len = str_len(keyword);
    srecorder_info_header_t info_header;

    buf[0] = (unsigned long)type;
    buf[1] = (unsigned long)data_len;
    info_header.type = type;
    info_header.data_len = data_len;
    info_header.crc32 = get_crc32((unsigned char *)buf, sizeof(buf));

    /* 1. write header */
    copy_data((char *)header_addr, (char *)&info_header, sizeof(srecorder_info_header_t));

    /* 2. write keyword */
    strcpy_valid_char((char *)(header_addr + sizeof(srecorder_info_header_t)), keyword, keyword_len);

    /* 3. write \n */
    copy_data((char *)(header_addr + sizeof(srecorder_info_header_t) + keyword_len), "\n", 1); /* 1 is the length of "\n" */
}


/**
    @function: unsigned long get_crc32(unsigned char const *pbuf, unsigned long data_len)
    @brief: Use CRC32 to do data check

    @param: pbuf data buffer to be checked
    @param: data_len buffer length

    @return: CRC32 value

    @note:
*/
static unsigned long get_crc32(unsigned char const *pbuf, unsigned long data_len)
{
    unsigned int crc32;
    unsigned long i = 0;

    if (unlikely(NULL == pbuf))
    {
        return CRC32_SEED_VALUE;
    }

    /* calculate the CRC32 value */
    crc32 = CRC32_SEED_VALUE;
    for (i = 0; i < data_len; i++)
    {
        crc32 = (crc32 >> 8) ^ s_crc32tab[(crc32 & 0xFF) ^ pbuf[i]];
    }

    return crc32 ^= CRC32_SEED_VALUE;
}


static inline unsigned long dump_need_reparsed_dmesg(char *pdst, char *psrc, unsigned log_buf_len)
{
    unsigned long data_len = 0;
    unsigned long keyword_len = 0;
    unsigned long log_header_size = sizeof(srecorder_info_header_t);
    char *pstart = NULL;
    if (unlikely(NULL == pdst || NULL == psrc))
    {
        return 0;
    }
    keyword_len = str_len(DMESG_KEYWORD) + 1; /* 1 - length of \n */
    pstart = (char *)((unsigned long)pdst + log_header_size + keyword_len);
    __memcpy(pstart, psrc, log_buf_len);
    data_len = log_buf_len;
    write_info_header((unsigned long)pdst, DMESG_BIT2, keyword_len + data_len, DMESG_KEYWORD);
    return (log_header_size + keyword_len + data_len);
}
/**
    @function: static inline unsigned long dump_dmesg(char *pdst, char *psrc, unsigned log_end, unsigned log_buf_len)
    @brief: dump dmesg

    @param: pdst physical start address of the SRecorder's reserved memory zone.
    @param: psrc temp buffer to store the dmesg.
    @param: log_end kernel ring buffer write index.
    @param: log_buf_len length of kernel ring buffer.

    @return: data length

    @note:
*/
static inline unsigned long dump_dmesg(char *pdst, char *psrc, unsigned log_end, unsigned log_buf_len)
{
    int data_len = 0;
    int keyword_len = 0;
    int log_header_size = sizeof(srecorder_info_header_t);
    char *pstart = NULL;

    if (unlikely(NULL == pdst || NULL == psrc))
    {
        return 0;
    }

    log_end &= LOG_BUF_MASK(log_buf_len);
    keyword_len = str_len(DMESG_KEYWORD) + 1; /* 1 - length of \n */
    pstart = (char *)((unsigned long)pdst + log_header_size + keyword_len);
    data_len = strcpy_valid_char(pstart, psrc + log_end - 1, (log_buf_len - log_end));
    data_len += strcpy_valid_char(pstart + data_len, psrc, log_end);
    write_info_header((unsigned long)pdst, DMESG_BIT2, keyword_len + data_len, DMESG_KEYWORD);

    return (log_header_size + keyword_len + data_len);
}


#ifdef CONFIG_POWERCOLLAPSE
#ifdef CONFIG_DUMP_LOGCAT
/**
    @function: static inline unsigned long dump_logcat(char *pdst, logcat_buf_info *plogcat_buf_info, int count, int write_header)
    @brief: dump logcat to the temp buffer

    @param: pdst temp buffer addr.
    @param: plogcat_buf_info logcat buf info.
    @param: count logcat log cat count.
    @param: write_header write header and save as a individual type.

    @return: data length

    @note:
*/
static inline unsigned long dump_logcat(char *pdst, logcat_buf_info *plogcat_buf_info, int count)
{
    int data_copyed = 0;
    int i = 0;
    int data_len = 0;
    int keyword_len = 0;
    int log_header_size = sizeof(srecorder_info_header_t);
    char *pstart = NULL;

    keyword_len = str_len(LOGCAT_KEYWORD) + 1; /* 1 - length of \n */
        pstart = (char *)((unsigned long)pdst + log_header_size + keyword_len);

    plogcat_buf_info[LOGCAT_MAIN].desc = "\n*********** log main ***********\n";
    plogcat_buf_info[LOGCAT_SYSTEM].desc = "\n*********** log system ***********\n";
    plogcat_buf_info[LOGCAT_EVENTS].desc = "\n*********** log events ***********\n";
    plogcat_buf_info[LOGCAT_RADIO].desc = "\n*********** log radio ***********\n";
    for (i = 0; i < count; i++)
    {
        data_copyed = strcpy_valid_char(pstart + data_len, (char *)plogcat_buf_info[i].desc, str_len(plogcat_buf_info[i].desc));
        data_len += data_copyed;
            data_copyed = strcpy_valid_char(pstart + data_len, (char *)plogcat_buf_info[i].log_buf, (int)plogcat_buf_info[i].log_buf_len);
            data_len += data_copyed;
    }

        write_info_header((unsigned long)pdst, LOGCAT_BIT9, keyword_len + data_len, LOGCAT_KEYWORD);

    return (log_header_size + keyword_len + data_len);
}
#endif


#ifdef CONFIG_DUMP_LOGCAT
/**
    @function: static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src, logcat_buf_info *plogcat_buf_info)
    @brief: dump log to the temp buffer

    @param: src physical start address of the SRecorder's reserved memory zone.
    @param: dst temp buffer to store the dmesg.
    @param: plogcat_buf_info logcat buf info.

    @return: none

    @note:
*/
static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src, logcat_buf_info *plogcat_buf_info)
#else
/**
    @function: static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src)
    @brief: dump log to the temp buffer

    @param: src physical start address of the SRecorder's reserved memory zone.
    @param: dst temp buffer to store the dmesg.

    @return: none

    @note:
*/
static inline void dump_abnormal_reset_log(unsigned long dst, unsigned long src)
#endif
{
    psrecorder_reserved_mem_header_t pheader = (psrecorder_reserved_mem_header_t)dst;
    int mem_header_size = sizeof(srecorder_reserved_mem_header_t);
    int log_header_size = sizeof(srecorder_info_header_t);
    int data_len = 0;
    int keyword_len = 0;
    char *pstart = NULL;
    unsigned long log_header_start_addr = 0x0;
    unsigned long dmesg_header_addr = 0x0;

    __memcpy((void *)dst, (void *)src, mem_header_size);

    /* 1.check the validity of the key info */
    if (!((get_crc32((unsigned char *)pheader, mem_header_size - sizeof(pheader->crc32)
        - sizeof(pheader->reserved)) == pheader->crc32)
        && ABNORMAL_RESET == pheader->reset_flag
        && INVALID_SRECORDER_MAGIC_NUM == pheader->magic_num
        && ((unsigned long)(-1) != pheader->log_buf)))
    {
        return;
    }

    /* 2. dump crash reason */
    log_header_start_addr = dst + mem_header_size;
    keyword_len = str_len(CRASH_REASON_KEYWORD) + 1; /* 1 - length of \n */
    pstart = (char *)(log_header_start_addr + log_header_size + keyword_len);
    data_len = strcpy_valid_char(pstart, CRASH_REASON_POWER_COLLAPSE, str_len(CRASH_REASON_POWER_COLLAPSE));
    data_len += strcpy_valid_char(pstart + data_len, CRASH_DEFAULT_TIME_POWER_COLLAPSE, str_len(CRASH_DEFAULT_TIME_POWER_COLLAPSE));
    write_info_header(log_header_start_addr, CRASH_REASON_TIME_BIT0, keyword_len + data_len, CRASH_REASON_KEYWORD);
    log_header_start_addr += (log_header_size + keyword_len + data_len);
    pheader->data_length += (log_header_size + keyword_len + data_len);

    /* 3. dump dmesg and logcat */
    dmesg_header_addr = log_header_start_addr;
    if (SRECORDER_KERNEL_LOG_NEED_NOT_BE_REPARSED == pheader->log_need_reparsed)
    {
    data_len = dump_dmesg((char *)dmesg_header_addr, (char *)pheader->log_buf,
        *(unsigned *)pheader->log_end, pheader->log_buf_len);
    }
    else if (SRECORDER_KERNEL_LOG_NEED_BE_REPARSED == pheader->log_need_reparsed)
    {
        data_len = dump_need_reparsed_dmesg((char *)dmesg_header_addr, (char *)pheader->log_buf, pheader->log_buf_len);
        pheader->log_first_idx = *(unsigned long*)(pheader->log_first_idx_phys_addr);
        pheader->log_next_idx = *(unsigned long*)(pheader->log_next_idx_phys_addr);
        __memcpy((void *)pheader->log_next_seq, (void *)(pheader->log_next_seq_phys_addr), sizeof(pheader->log_next_seq));
    }
    else
    {
        data_len = 0;
        do_nothing();
    }
    pheader->data_length += data_len;
#ifdef CONFIG_DUMP_LOGCAT
    if (0x0 != (pheader->dump_ctrl_bits[LOGCAT_BIT9 / 32] & (((unsigned long)1 << (LOGCAT_BIT9 % 32)))))
    {
        data_len = dump_logcat((char *)(dmesg_header_addr + data_len), plogcat_buf_info, LOGCAT_TYPE_MAX);
        pheader->data_length += data_len;
    }
    /* 3. dump dmesg */
#endif

    /* 4. update the reset_flasg and magic_num of the mem info header */
    pheader->reset_flag = NORMAL_RESET;
    pheader->magic_num = SRECORDER_MAGIC_NUM;
    pheader->crc32 = get_crc32((unsigned char *)pheader, mem_header_size
        - sizeof(pheader->crc32) - sizeof(pheader->reserved));
}
#endif
#endif
void
decompress_kernel(unsigned long output_start, unsigned long free_mem_ptr_p,
		unsigned long free_mem_ptr_end_p,
		int arch_id)
{
	int ret;

	output_data		= (unsigned char *)output_start;
	free_mem_ptr		= free_mem_ptr_p;
	free_mem_end_ptr	= free_mem_ptr_end_p;
	__machine_arch_type	= arch_id;

#ifdef CONFIG_SRECORDER
    do
    {
        srecorder_reserved_mem_header_t *pmem_header = NULL;
        int mem_header_len = sizeof(srecorder_reserved_mem_header_t);
        int mem_info_len = sizeof(platform_special_reserved_mem_info_t);
        unsigned long temp_buf = (unsigned long)(CONFIG_KERNEL_LOAD_PHYS_OFFSET
                + CONFIG_SRECORDER_TEMPBUF_ADDR_FROM_PHYS_OFFSET);

        platform_special_reserved_mem_info_t *pmem_info = (platform_special_reserved_mem_info_t *)
            (CONFIG_KERNEL_LOAD_PHYS_OFFSET + CONFIG_SRECORDER_SPECIAL_MEM_ADDR_FROM_PHYS_OFFSET);
        unsigned long boot_crc32 = 0x0;

        /* 1, check the validity of the reserved buffer */
        boot_crc32 = get_crc32((unsigned char*)pmem_info, (unsigned long)(mem_info_len - sizeof(pmem_info->crc32)));
        if ((NULL == (void *)pmem_info->srecorder_log_buf) 
            || (pmem_info->crc32 != boot_crc32)
            || (pmem_info->srecorder_log_buf != pmem_info->srecorder_log_buf_bak)
            || (pmem_info->srecorder_log_buf_len != pmem_info->srecorder_log_buf_len_bak))
        {
            /* avoid copy invalid data */
            ((srecorder_reserved_mem_header_t *)temp_buf)->magic_num = SRECORDER_ATAG_ZONE_DAMAGED;
            ((srecorder_reserved_mem_header_t *)temp_buf)->reserved_mem_size = boot_crc32;
            break;
        }

        /* check nff */


            /* |mem_header | prev_log | nff_log_header | nff_log_keyword | nff_log */

            /* add boot nff reason and time */

            /* dump dmesg */

            /* dump logcat */


        /* 2, check the validity of SRecorder's reserved memory header */
        pmem_header = (srecorder_reserved_mem_header_t *)pmem_info->srecorder_log_buf;
        boot_crc32 = get_crc32((unsigned char *)pmem_header, (unsigned long)(mem_header_len
            - sizeof(pmem_header->crc32)  - sizeof(pmem_header->reserved)));
        __memcpy((void *)temp_buf, pmem_header, mem_header_len);
        if (pmem_header->crc32 != boot_crc32)
        {
            /* avoid copy invalid data */
            ((srecorder_reserved_mem_header_t *)temp_buf)->magic_num = SRECORDER_RESERVED_ZONE_DAMAGED;
            ((srecorder_reserved_mem_header_t *)temp_buf)->reserved_mem_size = boot_crc32;
            break;
        }

        /* 3, process according to reset mode */
        if (ABNORMAL_RESET == pmem_header->reset_flag)
        {
#ifdef CONFIG_POWERCOLLAPSE
#ifdef CONFIG_DUMP_LOGCAT
            dump_abnormal_reset_log(temp_buf, pmem_info->srecorder_log_buf, &(pmem_info->logcat_buf_info[0]));
#else
            dump_abnormal_reset_log(temp_buf, pmem_info->srecorder_log_buf);
#endif
#endif
        }
        else if (NORMAL_RESET == pmem_header->reset_flag)
        {
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
            __memcpy((void *)temp_buf, (void *)pmem_info->srecorder_log_buf, pmem_header->data_length + mem_header_len);
            if (SRECORDER_MAGIC_NUM != pmem_header->magic_num)
            {
                break;
            }

		/* kmsg has been saved when system crash */
            pmem_header = (psrecorder_reserved_mem_header_t)temp_buf;
            if (SRECORDER_KERNEL_LOG_NEED_NOT_BE_REPARSED == pmem_header->log_need_reparsed)
            {
                pmem_header->data_length += dump_dmesg((char *)(temp_buf + pmem_header->data_length + mem_header_len), 
                    (char *)pmem_header->log_buf, *(unsigned *)pmem_header->log_end, pmem_header->log_buf_len);
            }
            else if (SRECORDER_KERNEL_LOG_NEED_BE_REPARSED == pmem_header->log_need_reparsed)
            {
                pmem_header->data_length += dump_need_reparsed_dmesg((char *)(temp_buf 
                    + pmem_header->data_length + mem_header_len), (char *)pmem_header->log_buf, pmem_header->log_buf_len);
                pmem_header->log_first_idx = *(unsigned long*)(pmem_header->log_first_idx_phys_addr);
                pmem_header->log_next_idx = *(unsigned long*)(pmem_header->log_next_idx_phys_addr);
                __memcpy((void *)pmem_header->log_next_seq, (void *)(pmem_header->log_next_seq_phys_addr), 
                    sizeof(pmem_header->log_next_seq));
            }
            else
            {
                do_nothing();
            }
            pmem_header->crc32 = get_crc32((unsigned char *)pmem_header, mem_header_len 
                - sizeof(pmem_header->crc32) - sizeof(pmem_header->reserved));
#else
            ((srecorder_reserved_mem_header_t *)temp_buf)->magic_num = SRECORDER_DUMP_LOG_TO_STORAGECARD;
#endif
        }
        else
        {
            do_nothing();
        }

        /* 4, clean reserved buffer */
        __memset(pmem_info, 0, mem_info_len);
    } while (0);
#endif
	arch_decomp_setup();

	putstr("Uncompressing Linux...");
	ret = do_decompress(input_data, input_data_end - input_data,
			    output_data, error);
	if (ret)
		error("decompressor returned an error");
	else
		putstr(" done, booting the kernel.\n");
}
