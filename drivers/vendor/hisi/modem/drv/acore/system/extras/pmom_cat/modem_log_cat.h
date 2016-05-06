#ifndef  __MODEM_LOG_CAT_H__
#define  __MODEM_LOG_CAT_H__

#ifdef __cplusplus
    extern "C" {
#endif 

#include <cutils/list.h>
#include <unistd.h>

#define BUG_REPORT_MODE                        0775
#define DIR_OWN                                "root:system"
#define FILE_OWN                               "root:system"
#define MAX_CMD                                256
#define DIR_MODE                               0775
#define FILE_MODE                              0664
#define MKDIR_ERR                              -1
#define MKDIR_OK                               0
#define MAX_INPUT_PARA_LENGTH                 (256)

#define MODEM_LOGGER_ENTRY_MAX_LEN            (5*1024)
#define MODEM_LOG_CAT_BUFSIZE                 (8*1024)             
#define MODEM_LOG_DEFAULT_ROTATE_KBYTE_SIZE   (16)
#define MODEM_LOG_DEFAULT_ROTATE_NUM          (4)
#define MODEM_LOG_DEFAULT_COMPRESS_NUM        (5)
#define MODEM_LOG_MAX_COMPRESS_NUM            (10)

enum MODEM_OUT_FILE_TYPE
{
    MODEM_T_STRING =0,
    MODEM_T_BINARY,
    MODEM_T_PARSER_STRING,
    MODEM_T_PARSER_BINARY,
    MODEM_T_MAX
};
#define  modem_log_pr_err(fmt, ...) \
do {							   \
	fprintf(stderr, "<%s> "fmt, __FUNCTION__, ##__VA_ARGS__);\
} while (0)

#ifdef pmom_debug
#define  modem_log_debug(fmt, ...) \
do {							   \
	if (1)	  \
		fprintf(stderr, "<%s> [%d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
} while (0)
	
#define  modem_log_info(fmt, ...) \
do {							   \
	if (0)	  \
		printf(fmt, ##__VA_ARGS__);\
} while (0)

#else

#define  modem_log_debug(fmt, ...)
#define  modem_log_info(fmt, ...)

#endif

/**
 * struct modem_log_input - input file infomation
 */
struct modem_log_input
{
	const char  *name; /* name with full path */
	int         fd ;   /* file discription */
};

/**
 * struct modem_log_input - output file infomation
 */
struct modem_log_output
{
	enum MODEM_OUT_FILE_TYPE  type;        /* output file type: g_outputFileType */
	const char           *name;            /* output file name: g_outputFileName */
	int                  fd ;              /* output file discription: g_outFD */
	int                  size_cnt;         /* file size: g_outByteCount */
	int                  rotate_size;      /* rotated file size: g_logRotateSizeKBytes */
	int                  rotate_threshold; /* rotated file number: g_maxRotatedLogs */
	int                  zip_threshold;    /* compressd file number: g_maxCompressdFiles */
	unsigned int         str_wr;           /* write offset of buffer */
};

/**
 * struct modem_logger_list - global info for modem logger
 */
struct modem_logger_list
{
	struct listnode node;                   /* list header of modem logger  */
	char raw_buf[MODEM_LOG_CAT_BUFSIZE];    /* which do not need to parser  */
	char parsed_buf[MODEM_LOG_CAT_BUFSIZE]; /* which need to parser  */
    char str_buf[MODEM_LOG_CAT_BUFSIZE+1];  /* buffer for write to log file  */
    char timebuf[32];                       /* time buffer  */
	int debug_enable;                       /* debug swith flag  */
};

/**
 * struct modem_logger - represents one log to handle
 */
struct modem_logger
{
	struct listnode node;                /* list node */
	struct modem_log_input  input_file;  /* input file infomation */
	struct modem_log_output output_file; /* output file infomation */
	struct modem_logger_list *top;       /* pointer to modem logger list header */
	short *revents;                      /* revents result of poll() */
};

void modem_log_rotate(struct modem_logger *logger);

#ifdef __cplusplus
}
#endif

#endif   /* __MODEM_LOG_CAT_H__ */

