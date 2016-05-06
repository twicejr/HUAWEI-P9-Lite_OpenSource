/*===========================================================================
修改历史

问题单号               修改人        日期              原因
DTS2012011606883        C00116387      2012/01/16    add kernel log function
DTS2012021603153        l00188955      2012/02/15    add time to kernel log
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <dirent.h>
#include "tarzip.h"

#include "pmom_cat.h"
#include "dpm_m3pm.h"
#include "cpufreq_regulator.h"
#include "ipc_clk.h"
#include "pm_parse.h"
#include "wakelock_parse.h"
#include "bbp_pmu.h"
#include "icc.h"
#include "nvim.h"
#include "rfile.h"
#include "dsp.h"
#include "tcxo.h"
#include "cosa.h"

/* Global Variables */
static const char * g_inputFileName = NULL;
static ENCODE_TYPE g_outputFileType = T_STRING;
static const char * g_outputFileName = NULL;
static int g_logRotateSizeKBytes = 0;                   // 0 means "no log rotation"
static int g_maxRotatedLogs = DEFAULT_MAX_ROTATED_LOGS; // 0 means "unbounded"
static int g_outFD = -1;
static int g_outByteCount = 0;
static int g_debugOption = 0;
static int g_maxCompressdFiles = 0;

static int openLogFile (const char *pathname)
{
    int ret;
    int file_fd;
    char cmd[MAX_CMD];
    file_fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, FILE_MODE);

    if ( -1 == file_fd)
    {
        fprintf(stderr,"open dir[%s] err %s:\n", pathname,strerror(errno));
        return -1;
    }
    ret = chmod(pathname, FILE_MODE);/* [false alarm]:屏蔽Fortify错误 */
    if ( -1 == ret )
    {
        fprintf(stderr,"chmod dir[%s] err %s:\n", pathname,strerror(errno));
    }
    snprintf(cmd, sizeof(cmd), "chown %s %s", FILE_OWN, pathname);
    system(cmd);
    return file_fd;
}
static void *compressThread(void *args)
{
	char *filesToCompress[MAX_FILE_NUM] = {0};
	char *compressDirName = NULL;
	char *compressedFileName = NULL;
	char *outputFileName = NULL;
	int err = -1;
	int i = 0;

	/* rotate compressed files */

	for (i = g_maxCompressdFiles - 1; i > 0; i--) {
		char *file0, *file1;

		asprintf(&file1, "%s-%d.tar.gz", g_outputFileName, i);
		asprintf(&file0, "%s-%d.tar.gz", g_outputFileName, i - 1);

		err = rename(file0, file1);
		if (err < 0 && errno != ENOENT) {
			perror("while rename compressed files");
		}

		free(file0);
		free(file1);
	}

	/* get compress dir name and log file name */

	compressDirName = (char *)args;
	outputFileName = strrchr(g_outputFileName, '/');
	outputFileName++;

	for (i = 0; i < g_maxRotatedLogs; i++) {
		asprintf(&filesToCompress[i], "%s/%s.%d", compressDirName, outputFileName, i + 1);
	}

	/* do compress */

	asprintf(&compressedFileName, "%s-0.tar.gz", g_outputFileName);
	tar_zip_files(g_maxRotatedLogs, (const char **)filesToCompress, compressedFileName, 0);
	free(compressedFileName);

	/* remove compressed logs */

	for (i = 0; i < g_maxRotatedLogs; i++) {
		err = unlink(filesToCompress[i]);
		if (err < 0) {
			perror("unlink failed");
		}
		free(filesToCompress[i]);
	}

	err = rmdir(compressDirName);
	if (err < 0) {
		perror("unlink failed");
	}
	free(compressDirName);

	return NULL;
}

static void compressLogs(void)
{
	char *compressDirName = NULL;
	char *compressFileName = NULL;
	char *outputFileName = NULL;
	char local_time[16] = {0};
	time_t now = -1;
	pthread_t tid = -1;
	int err = -1;
	int i = 0;

	/* create the compress dir */

	asprintf(&compressDirName, "%s_tmp", g_outputFileName);
	err = mkdir(compressDirName, BUG_REPORT_MODE);
	if (err < 0) {
		perror("couldn't create compress dir");
	}

	outputFileName = strrchr(g_outputFileName, '/');
	outputFileName++;

	/* move the logs to be compressed to the dir */

	for (i = g_maxRotatedLogs ; i > 0 ; i--) {
		char *file0, *file1;

		asprintf(&file0, "%s.%d", g_outputFileName, i);
		asprintf(&file1, "%s/%s.%d", compressDirName, outputFileName, i);

		err = rename(file0, file1);
		if (err < 0) {
			perror("while rename log files");
		}

		free(file0);
		free(file1);
	}

	/* create a thread to do the compress job */

	err = pthread_create(&tid, NULL, compressThread, (void *)compressDirName);
	if (err) {
		perror("create compress thread fail");
		exit(-1);
	}
}
static void rotateLogs()
{
    int err;
	char *file;
    char *file0, *file1;
    int i;

    // Can't rotate logs if we're not outputting to a file
    if (g_outputFileName == NULL) {
        return;
    }

    close(g_outFD);

    for (i = g_maxRotatedLogs ; i > 0 ; i--) {
        asprintf(&file1, "%s.%d", g_outputFileName, i);

        if (0==(i - 1)) {
            asprintf(&file0, "%s", g_outputFileName);
        } else {
            asprintf(&file0, "%s.%d", g_outputFileName, (i - 1));
        }
        if( g_debugOption ){
            fprintf(stderr, "%s: rename %s %s\n", __func__, file0, file1);
        }
        err = rename (file0, file1);

        if (err < 0 && errno != ENOENT) {
            perror("while rotating log files");
        }

        free(file1);
        free(file0);
    }
	asprintf(&file, "%s.%d", g_outputFileName, g_maxRotatedLogs);
	if (!access(file, F_OK) && g_maxCompressdFiles)
	{
		compressLogs();
	}
	free(file);
    g_outFD = openLogFile (g_outputFileName);

    if (g_outFD < 0) {
        perror ("couldn't open output file");
        exit(-1);
    }

    g_outByteCount = 0;

}

static char* strchrnul(const char* s, char c)
{
    while( *s != '\0' && (*s != c))
        s++;
    return (char*)s;
}
static void overlapping_strcpy(char *dst, const char *src)
{
    if(dst != src)
    {
        while((*dst = *src) != '\0')
        {
            dst++;
            src++;
        }
    }
}

static int mkdir_p(const char *sPathName, mode_t mode)
{
    size_t i;
    size_t len;
    char DirName[MAX_INPUT_PARA_LENGTH];

    if (strlen(sPathName) > MAX_INPUT_PARA_LENGTH-2)
    {
        return -1;
    }

    memset(DirName, 0x00, MAX_INPUT_PARA_LENGTH*sizeof(char));
    strncpy(DirName, sPathName, MAX_INPUT_PARA_LENGTH-2);
    len = strlen(DirName);
    if(DirName[len-1] != '/')
    {
        strcat(DirName, "/");
    }

    len = strlen(DirName);

    for (i=1; i<len; i++)
    {
        if (DirName[i] != '/')
        {
            continue;
        }

        DirName[i] = 0;
        if (0 != access(DirName, F_OK))
        {
            if (-1 == mkdir(DirName, mode))
            {
                fprintf(stderr, "%s: mkdir [%s]: %s.\n", __func__, strerror(errno), DirName);
                return -1;
            }

            if(-1 == chmod(DirName, mode))
            {
                fprintf(stderr, "%s: chmod [%s] err %s. \n", __func__, DirName,strerror(errno));
                return -1;
            }
        }
        DirName[i] = '/';

    }

    return 0;
}

struct pmom_cat_control g_pmom_cat;

#define  pmom_cat_pr_debug(fmt, ...) \
do {                               \
    if (g_debugOption)    \
        fprintf(stderr,  "<%s> [%d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
} while (0)

#define  pmom_cat_pr_info(fmt, ...) \
do {                               \
    if (g_debugOption)    \
        printf(fmt, ##__VA_ARGS__);\
} while (0)

int pmom_waketime_parse(char *in_buf, size_t len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	unsigned int *interval = (unsigned int *)in_buf;

	/* step1: 消息类型检查 */
	if(len != sizeof(*interval))
	{
		return PMOM_ERR;
	}

	/* step2: 格式化消息到out_buf: 以回车结束 */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,"wake_acore_interval=%dsec\n", *interval);
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}

int pmom_dummy_msg_parse(char *in_buf, size_t len, char *out_buf, unsigned int *out_ptr)
{
	unsigned int data_len = 0;
	unsigned int i        = 0;

	if (0 == len || NULL == in_buf)
	{
		return PMOM_OK;
	}

	if (len % 4 == 0)
	{
		for (i = 0; i < (len - 4); i += 4)
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, /* [false alarm]:屏蔽Fortify错误 */
			"0x%08x, ", *(u32 *)in_buf);
			in_buf   += 4;
			*out_ptr = *out_ptr + data_len;
		}

		/* 最后一个数据要加回车 */
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
		"0x%08x\n", *(u32 *)in_buf);
		in_buf += 4;
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		pmom_cat_pr_debug("err: non-4byte align\n");
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "non-4byte align:");
		*out_ptr = *out_ptr + data_len;

		for (i = 0; i < len - 1; i++)
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%2x ", *(u32 *)in_buf);
			in_buf ++;
			*out_ptr = *out_ptr + data_len;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%2x\n", *(u32 *)in_buf);
		in_buf ++;
		*out_ptr = *out_ptr + data_len;
	}

	return PMOM_OK;
}

int pmom_bin_msg_iterate(char *buf)
{
	struct pm_om_log_header *msg_head= (struct pm_om_log_header *)buf;
	return (sizeof(*msg_head) + msg_head->length);
}

void pmom_log_msg_parse(char *buf, struct pm_om_log_header *msg_head)
{
	int ret                 = PMOM_OK;
	char *magic_name        = NULL;
	unsigned int i          = 0;
	unsigned int data_len   = 0;
	unsigned int msg_magic  = 0;
	unsigned int msg_len    = 0;
	unsigned int msg_typeid = 0;
	unsigned int head_len   = sizeof(struct pm_om_log_header);
	struct tm *ptm          = NULL;
	struct timeval tv;

	/* step1: format date */
	gettimeofday(&tv, NULL);
	ptm = localtime(&(tv.tv_sec));
	if (ptm)
	{
		strftime(g_pmom_cat.timebuf, sizeof(g_pmom_cat.timebuf), "%m-%d %H:%M:%S", ptm);

		data_len = snprintf(&g_pmom_cat.str_buf[g_pmom_cat.str_wr], sizeof(g_pmom_cat.str_buf), /* [false alarm]:屏蔽Fortify错误 */
			"%s.%03ld ", g_pmom_cat.timebuf, tv.tv_usec / 1000);
		g_pmom_cat.str_wr += data_len;
	}

	/* step2: format message head */
	magic_name  = (char *)&msg_head->magic;
	msg_magic  = msg_head->magic;
	msg_len    = msg_head->length;
	msg_typeid = msg_head->typeid;

	data_len    = snprintf(&g_pmom_cat.str_buf[g_pmom_cat.str_wr], sizeof(g_pmom_cat.str_buf), /* [false alarm]:屏蔽Fortify错误 */
				"[0x%08x] [0x%08x] [%c%c%c%c, 0x%08x] ", msg_head->timestamp, msg_head->sn, 
				magic_name[0], magic_name[1], magic_name[2], magic_name[3], 
				msg_len);
	g_pmom_cat.str_wr += data_len;
	buf += head_len;

	ret = PMOM_OK;
	switch (msg_magic)
	{
		case PM_OM_MAGIC_CPUF:
			ret = cpufreq_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_REGU:
			ret = regulator_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_DPM:
			ret = dpm_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_PMM:
			ret = m3pm_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_ACLK:
			ret = clk_msg_parse(PM_LOG_ACORE, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_CCLK:
			ret = clk_msg_parse(PM_LOG_CCORE, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_AIPC:
			ret = ipc_msg_parse(PM_LOG_ACORE, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_CIPC:
			ret = ipc_msg_parse(PM_LOG_CCORE, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_PMA:
			ret = pm_msg_parse_acore(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_PMC:
			ret = pm_msg_parse_ccore(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_WAKE:
			ret = wakelock_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
        case PM_OM_MAGIC_BBP:
			ret = bbp_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
        case PM_OM_MAGIC_PMU:
			ret = pmu_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
        case PM_OM_MAGIC_NVA:
            ret = nvim_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
            break;
        case PM_OM_MAGIC_NVC:
            ret = nvim_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
            break;
		case PM_OM_MAGIC_AICC:
			ret = icc_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_CICC:
			ret = icc_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;

		case PM_OM_MAGIC_DSP:
			ret = dsp_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_ARFILE:
			ret = rfile_msg_parse(msg_typeid, buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_PMLG:
			ret = pmom_waketime_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
		case PM_OM_MAGIC_TCXO:
			ret = tcxo_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
			break;
        case PM_OM_MAGIC_COSA:
            ret = pm_cosa_main_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
            break;
		default:
			ret = PMOM_ERR;
			break;
	}

	if (ret != PMOM_OK)
	{
		pmom_dummy_msg_parse(buf, msg_len, g_pmom_cat.str_buf, &g_pmom_cat.str_wr);
	}

	return;
}

size_t pmom_msg_handle(char *buf, size_t len, ENCODE_TYPE out_file_type)
{
	struct pm_om_log_header *msg_head = NULL;
	size_t i         = 0;
	ssize_t nw       = 0;
	size_t read_off  = 0;
	size_t parse_len = 0;
	size_t head_len  = sizeof(*msg_head);
	size_t msg_len   = 0;

	pmom_cat_pr_debug("buf=%p, len=0x%x, head_len=0x%x, out_file_type=%d\n", buf, (unsigned int)len, (unsigned int)head_len, out_file_type);
	while (read_off < len)
	{
		msg_head = (struct pm_om_log_header *)buf;
		msg_len  = msg_head->length;
		if ((len - read_off) < head_len || (len - read_off) < (head_len + msg_len))
		{
			pmom_cat_pr_debug("quit: buf=0x%p, read_off=0x%x, left_data:\n", buf, (unsigned int)read_off);
			for (i = 0; i < (len - read_off + 20); i += 4)
			{
				pmom_cat_pr_info("0x%08x, ", *(u32 *)(buf + i));
			}
			pmom_cat_pr_info("0x%08x\n", *(u32 *)(buf + i));
			break;
		}
		if (T_STRING == out_file_type)
		{
			pmom_log_msg_parse(buf, msg_head);

			/* 处理后的消息写入文件 */
			if(0 != access(g_outputFileName, F_OK))
			{
				rotateLogs();
			}

			nw = write(g_outFD, g_pmom_cat.str_buf, g_pmom_cat.str_wr);
			g_pmom_cat.str_wr = 0;
		}
		else if (T_BINARY == out_file_type)
		{
			pmom_bin_msg_iterate(buf);

			/* 处理后的消息写入文件 */
			if(0 != access(g_outputFileName, F_OK))
			{
				rotateLogs();
			}

			nw = write(g_outFD, buf, read_off);
		}

		g_outByteCount += nw;
		if (g_logRotateSizeKBytes > 0 && (g_outByteCount / 1024) >= g_logRotateSizeKBytes )
		{
			pmom_cat_pr_debug("call rotateLogs\n");
			rotateLogs();
		}

		buf      += (head_len + msg_len);
		read_off += (head_len + msg_len);
	}

	return read_off;
}

void pmom_cat(const char * logfile, ENCODE_TYPE out_file_type)
{
	int  logfd        = -1;
	char *buf_src     = NULL;
	char *buf_dst     = NULL;
	char *buf         = NULL;
	ssize_t nr        = 0;
	ssize_t read_off  = 0;
	ssize_t left_size = 0;
	ssize_t i         = 0;

	memset((void *)&g_pmom_cat, 0, sizeof(g_pmom_cat));

	pmom_cat_pr_debug("entry\n");
	logfd = open(logfile, O_RDONLY, 0);
	if (logfd < 0)
	{
		perror(logfile);
		return;
	}

	buf = g_pmom_cat.raw_buf;
	while(1)
	{
		/* 读4KB */
		nr = read(logfd, buf + left_size, CAT_BUFSIZ - left_size);
		pmom_cat_pr_debug("nr=0x%x, buf=0x%p\n", (unsigned int)nr, buf);
		if(nr < 0)
		{
			sleep(1);
			fprintf(stderr, "read fail!reserved_buf_size = 0x%x\n", CAT_BUFSIZ);
			continue;
		}
		if (left_size > 0)
		{
			pmom_cat_pr_debug("read: \n" );
			for (i = 0; i < left_size+48; i += 4)
			{
				pmom_cat_pr_info("0x%08x, ", *(u32 *)(buf + i));
			}
			pmom_cat_pr_info("0x%08x\n", *(u32 *)(buf + i));
		}

		/* 消息处理 */
		read_off = pmom_msg_handle(buf, nr + left_size, out_file_type);
		if (read_off == 0 || read_off > CAT_BUFSIZ)
		{
			fprintf(stderr, "read_off= 0x%x, msg parse error\n", (unsigned int)read_off);
			for (i = 0; i < 100; i += 4)
			{
				pmom_cat_pr_info("0x%08x, ", *(u32 *)(buf + i));
			}
			fprintf(stderr, "\n");
			break;
		}

		/* 处理剩余非对齐的包 */
		left_size =  nr + left_size - read_off;
		pmom_cat_pr_debug("read_off=0x%x, left=0x%x\n\n", (unsigned int)read_off, (unsigned int)left_size);
		if (left_size > 0)
		{
			memcpy((void *)buf, (void *)(buf + read_off), left_size);
		}
	}

	close(logfd);
	if (nr < 0)
	{
		fprintf(stderr,"%s: invalid length\n", logfile);
		exit(EXIT_FAILURE);
	}
}

static int create_bugreports_dir(const char* bugreportfile)
{
    int ret = 0;
    char *pdir;
    char *pend;
    unsigned long tmplen ;
    char cmd[MAX_CMD];

    if( NULL == bugreportfile )
    {
        fprintf(stderr,"bugreport dir is invalide.\n");
        return MKDIR_ERR;
    }

    if(0 == strlen(bugreportfile) )
    {
        fprintf(stderr,"bugreport dir is invalide.\n");
        return MKDIR_ERR;
    }
    /* get the bugreport dir from bugreportfile
       eg: bugreportfile is /sdcard/bugreports/kmsgcat-log
       bugreports dir is /sdcard/bugreports */

    /* get the last '/' and it's the start position of the file name*/
    pend = strrchr( bugreportfile, '/');
    if( NULL == pend )
    {
	fprintf(stderr,"pend  is invalide.\n");
	return MKDIR_ERR;
    }
    tmplen = strlen(bugreportfile) - strlen(pend);
    pdir = (char*)malloc( (tmplen + 1) * sizeof(char) );
    if( NULL == pdir )
    {
        fprintf(stderr,"malloc memory fail when create bugreport dir[%s].\n", bugreportfile);
        return MKDIR_ERR;
    }
    memset( pdir, 0x00, sizeof( (tmplen + 1) * sizeof(char) ) );

    /* get the bugreports dir */
    strncpy( pdir, bugreportfile, tmplen );
    pdir[tmplen] = '\0';

    /* check the bugreport dir */
    if ( access( pdir, F_OK ) != 0 )
    {
        /*  the dir isn't exist, create the dir. */
        ret = mkdir_p(pdir, DIR_MODE);/* [false alarm]:屏蔽Fortify错误 */
        /* the dir create ok. */
        if( 0 == ret)
        {
            fprintf(stderr,"create bugreport dir[%s] ok.\n", pdir);
			chmod(pdir, DIR_MODE); /* [false alarm]:屏蔽Fortify错误 */
            snprintf(cmd, sizeof(cmd), "chown %s %s", DIR_OWN, pdir);
	        system(cmd);
            free( pdir );
            pdir = NULL;
            return MKDIR_OK;
        }
        /* the dir create fail. */
        else
        {
            free( pdir );
            pdir = NULL;
            perror("create bugreport fail!\n");
            return MKDIR_ERR;
        }
    }
    /* the bug report dir is exist. */
    else
    {
        fprintf(stderr,"bugreport dir[%s] exist.\n", pdir);
        ret = chmod(pdir, DIR_MODE);
        if (ret == -1){
            fprintf(stderr,"chmod dir[%s] err %s:\n", pdir,strerror(errno));

        }
	snprintf(cmd, sizeof(cmd), "chown %s %s", DIR_OWN, pdir);
	system(cmd);
        free( pdir );
        pdir = NULL;
        return MKDIR_OK;
    }
}

static void setupOutput()
{
    if (NULL == g_outputFileName) {
        g_outFD = STDOUT_FILENO;
    } else {
        struct stat statbuf;

        /* check the bugreport dir and if it isn't exist, create it.
           if create fail, give error info.*/
        if( MKDIR_ERR == create_bugreports_dir( g_outputFileName ))
        {
            fprintf(stderr,"create bugreports dir error!!\n");
        }

        g_outFD = openLogFile (g_outputFileName);

        if (g_outFD < 0) {
            perror ("couldn't open output file");
            exit(-1);
        }

        fstat(g_outFD, &statbuf);

        g_outByteCount = statbuf.st_size;
    }
}

static void show_help(const char *cmd)
{
    fprintf(stderr,"Usage: %s [options] \n", cmd);

    fprintf(stderr, "options include:\n"
        "  -i <input device node>   Device node from where data comes\n"
        "  -e <encode>   Log in which type, 'b' or 's', binary or string\n"
        "  -f <filename>   Log to file. Default to stdout\n"
        "  -r [<kbytes>]   Rotate log every kbytes. (16 if unspecified). Requires -f\n"
		"  -z <conut>      Sets max number of tarballs to <count>, default 5\n"
        "  -n <count>      Sets max number of rotated logs to <count>, default 4\n");

}

int main(int argc, char **argv)
{
    if (getuid() == 0) {
        umask(022);
    }

    if (2==argc && 0 == strcmp(argv[1], "--help")) {
        show_help(argv[0]);
        exit(0);
    }
	if (2==argc && 0 == strcmp(argv[1], "-d")){
        g_debugOption = 1;
		pmom_cat_pr_debug("debug on\n");
        exit(0);
    }

    for (;;) {
        int ret;
		ret = getopt(argc, argv, "d:i:e:f:n:r:z:");

        if (ret < 0) {
            break;
        }

        switch(ret) {
            case 'i':
                if (optarg == NULL){
                    g_inputFileName = CCORECAT_FILE;
                } else {
                    g_inputFileName = optarg;
                }
                fprintf(stderr,"g_inputFileName parameter [%s]\n", g_inputFileName);
                break;
            case 'e':
                fprintf(stderr,"g_outputFileType optarg [%s]\n", optarg);
                if (optarg == NULL){
                    g_outputFileType = T_STRING;
                } else if (!strcmp("s", optarg)){
                    g_outputFileType = T_STRING;
                } else if (!strcmp("b", optarg)){
                    g_outputFileType = T_BINARY;
                } else {
                        fprintf(stderr,"Invalid parameter to -e\n");
                        show_help(argv[0]);
                        exit(-1);
                }
                 fprintf(stderr,"g_outputFileType parameter [%d]\n", g_outputFileType);
                 break;
            case 'f':
                if (optarg == NULL) {
                    g_outputFileName = DEFAULT_LOG_FILE_PATH;
                } else {
                    // redirect output to a file
                    g_outputFileName = optarg;
                }
                break;
            case 'r':
                if (optarg == NULL) {
                    g_logRotateSizeKBytes = DEFAULT_LOG_ROTATE_SIZE_KBYTES;
                } else {
                    if (!isdigit(optarg[0])) {
                        fprintf(stderr,"Invalid parameter to -r\n");
                        show_help(argv[0]);
                        exit(-1);
                    }
                    g_logRotateSizeKBytes = atoi(optarg);
                }
                break;
			case 'z':
				if (optarg == NULL) {
					g_maxCompressdFiles = DEFAULT_MAX_COMPRESSED_FILES;
				} else {
					if (!isdigit(optarg[0])) {
						fprintf(stderr,"Invalid parameter to -r\n");
						show_help(argv[0]);
						exit(-1);
					}
					g_maxCompressdFiles = atoi(optarg);
				}
			break;
            case 'n':
                if (optarg == NULL) {
                    g_maxRotatedLogs = DEFAULT_MAX_ROTATED_LOGS;
                } else {
                if (!isdigit(optarg[0])) {
                    fprintf(stderr,"Invalid parameter to -r\n");
                    show_help(argv[0]);
                    exit(-1);
                }
                g_maxRotatedLogs = atoi(optarg);
                }
                if (g_maxRotatedLogs > MAX_FILE_NUM) {
                    g_maxRotatedLogs = MAX_FILE_NUM;
                }
                break;
              /*hide option for debug option*/
            case 'd':
                g_debugOption = 1;
                break;
            default:
                fprintf(stderr,"Unrecognized Option\n");
                show_help(argv[0]);
                exit(-1);
                break;
        }
    }

    if (g_logRotateSizeKBytes != 0 && NULL==g_outputFileName) {
        fprintf(stderr,"-r requires -f as well\n");
        show_help(argv[0]);
        exit(-1);
    }

    if( g_debugOption ){
        fprintf(stderr, "%s: g_outputFileName: %s, g_logRotateSizeKBytes: %d, g_maxRotatedLogs=%d\n",
            __func__, g_outputFileName, g_logRotateSizeKBytes, g_maxRotatedLogs);
    }
    setupOutput();

	pmom_cat(g_inputFileName, g_outputFileType);

    return 0;
}
