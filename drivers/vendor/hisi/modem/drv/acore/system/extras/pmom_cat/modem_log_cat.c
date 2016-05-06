#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <poll.h>

#include "pm_log_cat.h"
#include "modem_dmesg_cat.h"
#include "tarzip.h"
#include "modem_log_cat.h"

struct compress_argv
{
	struct modem_logger *logger;
	char *compress_dir_name;
};

struct argv_cnt
{
	unsigned int ni;
	unsigned int ne;
	unsigned int nf;
	unsigned int nr;
	unsigned int nz;
	unsigned int nn;
};

struct modem_logger_list g_modem_log_cat;

#define modem_log_pr_err_once pr_err_once

#define logger_for_each(logger, logger_list) \
		for (logger = node_to_item((logger_list)->node.next, struct modem_logger, node); \
			 logger != node_to_item(&(logger_list)->node, struct modem_logger, node); \
			 logger = node_to_item((logger)->node.next, struct modem_logger, node))

void modem_list_init(struct listnode *node)
{
	node->next = node;
	node->prev = node;
}

void modem_list_add_tail(struct listnode *head, struct listnode *item)
{
	item->next = head;
	item->prev = head->prev;
	head->prev->next = item;
	head->prev = item;
}

void modem_list_add_head(struct listnode *head, struct listnode *item)
{
	item->next = head->next;
	item->prev = head;
	head->next->prev = item;
	head->next = item;
}

void modem_list_remove(struct listnode *item)
{
	item->next->prev = item->prev;
	item->prev->next = item->next;
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
	if(DirName[len-1] != '/') {
		strcat(DirName, "/");
	}

	len = strlen(DirName);

	for (i=1; i<len; i++) {
		if (DirName[i] != '/') {
			continue;
		}

		DirName[i] = 0;
		if (0 != access(DirName, F_OK)) {
			if (-1 == mkdir(DirName, mode)) {
				modem_log_pr_err("%s: mkdir [%s]: %s.\n", __func__, strerror(errno), DirName);
				return -1;
			}

			if(-1 == chmod(DirName, mode)) {
				modem_log_pr_err("%s: chmod [%s] err %s. \n", __func__, DirName,strerror(errno));
				return -1;
			}
		}
		DirName[i] = '/';

	}

	return 0;
}

static int modem_log_create_bugreports_dir(const char* bugreportfile)
{
	int ret = 0;
	char *pdir;
	char *pend;
	unsigned long tmplen ;
	char cmd[MAX_CMD];

	if( NULL == bugreportfile ) {
		perror("bugreport dir is invalide.\n");
		return MKDIR_ERR;
	}

	if(0 == strlen(bugreportfile) ) {
		perror("bugreport dir is invalide.\n");
		return MKDIR_ERR;
	}

	/* get the last '/' and it's the start position of the file name*/
	pend = strrchr( bugreportfile, '/');
	if( NULL == pend ) {
		perror("pend  is invalide.\n");
		return MKDIR_ERR;
	}
	tmplen = strlen(bugreportfile) - strlen(pend);
	pdir = (char*)malloc( (tmplen + 1) * sizeof(char) );
	if( NULL == pdir ) {
		modem_log_pr_err("malloc memory fail when create bugreport dir[%s].\n", bugreportfile);
		return MKDIR_ERR;
	}
	memset( pdir, 0x00, sizeof( (tmplen + 1) * sizeof(char) ) );

	/* get the bugreports dir */
	strncpy( pdir, bugreportfile, tmplen );
	pdir[tmplen] = '\0';

	/* check the bugreport dir */
	if ( access( pdir, F_OK ) != 0 ) {
		/*	the dir isn't exist, create the dir. */
		ret = mkdir_p(pdir, DIR_MODE);
		/* the dir create ok. */
		if( 0 == ret) {
			modem_log_pr_err("create bugreport dir[%s] ok.\n", pdir);
			chmod(pdir, DIR_MODE);
			snprintf(cmd, sizeof(cmd), "chown %s %s", DIR_OWN, pdir);
			system(cmd);
			free( pdir );
			pdir = NULL;
			return MKDIR_OK;
		} else {
			free( pdir );
			pdir = NULL;
			perror("create bugreport fail!\n");
			return MKDIR_ERR;
		}
	} else { /* the bug report dir is exist. */
		modem_log_pr_err("bugreport dir[%s] exist.\n", pdir);
		ret = chmod(pdir, DIR_MODE);
		if (ret == -1){
			modem_log_pr_err("chmod dir[%s] err %s:\n", pdir,strerror(errno));
		}
		snprintf(cmd, sizeof(cmd), "chown %s %s", DIR_OWN, pdir);
		system(cmd);
		free( pdir );
		pdir = NULL;
		return MKDIR_OK;
	}
}
	
static int modem_log_open_output_file(const char *pathname)
{
	int ret;
	int file_fd;
	char cmd[MAX_CMD];
	file_fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, FILE_MODE);

	if ( -1 == file_fd) {
		modem_log_pr_err("open dir[%s] err %s:\n", pathname,strerror(errno));
		return -1;
	}
	ret = chmod(pathname, FILE_MODE);
	if ( -1 == ret ) {
		modem_log_pr_err("chmod dir[%s] err %s:\n", pathname,strerror(errno));
	}
	snprintf(cmd, sizeof(cmd), "chown %s %s", FILE_OWN, pathname);
	system(cmd);
	return file_fd;
}

static void show_logger_info(struct modem_logger *dev_log)
{
	printf("input_file.fd               : 0x%x\n", dev_log->input_file.fd);
	printf("input_file.name             : %s\n", dev_log->input_file.name);
	printf("output_file.fd              : 0x%x\n", dev_log->output_file.fd);
	printf("output_file.name            : %s\n", dev_log->output_file.name);
	printf("output_file.size_cnt        : %d\n", dev_log->output_file.size_cnt);
	printf("output_file.rotate_size     : %d\n", dev_log->output_file.rotate_size);
	printf("output_file.rotate_threshold: %d\n", dev_log->output_file.rotate_threshold);
	printf("output_file.zip_threshold   : %d\n", dev_log->output_file.zip_threshold);
	printf("output_file.str_wr          : 0x%x\n", dev_log->output_file.str_wr);
}

int modem_logger_open(struct modem_logger_list *logger_list)
{
	struct modem_logger *logger;
	int  logfd = -1;

	modem_log_debug("entry\n");

	logger_for_each(logger, logger_list) {
		logfd = open(logger->input_file.name , O_RDWR | O_NONBLOCK, 0);
		if (logfd < 0) {
			modem_log_pr_err("open input file[%s] fail\n", logger->input_file.name);
			continue;
		}

		logger->input_file.fd = logfd;
		if (NULL == logger->output_file.name) {
			logger->output_file.fd = STDOUT_FILENO;
		} else {
			struct stat statbuf;

			/* check the bugreport dir and if it isn't exist, create it. if create fail, give error info.*/
			if( MKDIR_ERR == modem_log_create_bugreports_dir(logger->output_file.name))
			{
				perror("create bugreports dir error!\n");
			}

			logfd = modem_log_open_output_file(logger->output_file.name);
			if (logfd < 0) {
				modem_log_pr_err("open output file[%s] fail\n", logger->output_file.name);
				continue;
			}

			fstat(logfd, &statbuf);

			logger->output_file.fd = logfd;
			logger->output_file.str_wr = 0;
			logger->output_file.size_cnt = statbuf.st_size;
		}

		show_logger_info(logger);
	}/* end logger_for_each */

	if (list_empty(&logger_list->node)) {
		return -1;
	}
	return 0;
}

static void *modem_log_compress_thread(void *args)
{
	char *compress_file_num[MAX_FILE_NUM] = {0};
	char *compress_dir_name = NULL;
	char *compress_file_name = NULL;
	char *output_filename = NULL;
	int err = -1;
	int i = 0;
	struct compress_argv *compress_arg = (struct compress_argv *)args;
	struct modem_log_output *output = &compress_arg->logger->output_file;


	for (i = output->zip_threshold - 1; i > 0; i--) {
		char *file0, *file1;

		asprintf(&file1, "%s-%d.tar.gz", output->name, i);
		asprintf(&file0, "%s-%d.tar.gz", output->name, i - 1);

		err = rename(file0, file1);
		if (err < 0 && errno != ENOENT) {
			modem_log_pr_err("rename fail while compressing\n");
		}

		free(file0);
		free(file1);
	}

	/* get compress dir name and log file name */
	compress_dir_name = compress_arg->compress_dir_name;
	output_filename = strrchr(output->name, '/');
	output_filename++;

	for (i = 0; i < output->rotate_threshold; i++) {
		asprintf(&compress_file_num[i], "%s/%s.%d", compress_dir_name, output_filename, i + 1);
	}

	/* do compress */
	asprintf(&compress_file_name, "%s-0.tar.gz", output->name);
	tar_zip_files(output->rotate_threshold, (const char **)compress_file_num, compress_file_name, 0);
	free(compress_file_name);

	/* remove compressed logs */
	for (i = 0; i < output->rotate_threshold; i++) {
		err = unlink(compress_file_num[i]);
		if (err < 0) {
			perror("unlink failed");
		}
		free(compress_file_num[i]);
	}

	err = rmdir(compress_dir_name);
	if (err < 0) {
		perror("unlink failed");
	}
	free(compress_dir_name);

	return NULL;
}

static void modem_log_compress(struct modem_logger *logger)
{
	char *dir_name = NULL;
	char *compress_file_name = NULL;
	char *output_file_name = NULL;
	char local_time[16] = {0};
	time_t now = -1;
	pthread_t tid = -1;
	int err = -1;
	int i = 0;
	struct modem_log_output *output = &logger->output_file;
	struct compress_argv compress_arg;

	/* create the compress dir */

	asprintf(&dir_name, "%s_tmp", output->name);
	err = mkdir(dir_name, BUG_REPORT_MODE);
	if (err < 0) {
		perror("couldn't create compress dir");
	}

	output_file_name = strrchr(output->name, '/');
	output_file_name++;

	/* move the logs to be compressed to the dir */
	for (i = output->rotate_threshold; i > 0 ;i--) {
		char *file0, *file1;

		asprintf(&file0, "%s.%d", output->name, i);
		asprintf(&file1, "%s/%s.%d", dir_name, output_file_name, i);

		err = rename(file0, file1);
		if (err < 0) {
			modem_log_pr_err("rename fail while moving\n");
		}

		free(file0);
		free(file1);
	}

	compress_arg.logger = logger;
	compress_arg.compress_dir_name = dir_name;
	err = pthread_create(&tid, NULL, modem_log_compress_thread, (void *)&compress_arg);
	if (err) {
		modem_log_pr_err( "create compress thread fail for %s\n", output->name);
	}
}

void modem_log_rotate(struct modem_logger *logger)
{
	int err;
	char *file;
	char *file0, *file1;
	int i;

	struct modem_log_output *output = &logger->output_file;
	if (NULL == output->name) {
		return;
	}

	close(output->fd);

	for (i = output->rotate_threshold; i > 0; i--) {
		asprintf(&file1, "%s.%d", output->name, i);

		if (0==(i - 1)) {
			asprintf(&file0, "%s", output->name);
		} else {
			asprintf(&file0, "%s.%d", output->name, (i - 1));
		}
		modem_log_debug("%s: rename %s %s\n", __func__, file0, file1);

		err = rename (file0, file1);
		if (err < 0 && errno != ENOENT) {
			modem_log_pr_err("rename fail while rotating");
		}

		free(file1);
		free(file0);
	}
	asprintf(&file, "%s.%d", output->name, output->rotate_threshold);
	if (!access(file, F_OK) && output->zip_threshold)
	{
		modem_log_compress(logger);
	}
	free(file);
	output->fd = modem_log_open_output_file(output->name);

	if (output->fd < 0) {
		modem_list_remove(&logger->node);
		perror ("couldn't open output file");
	}

	output->size_cnt = 0;

}

void modem_log_cat(struct modem_logger_list *logger_list)
{
	nfds_t nfds;
	struct pollfd *p, *pollfds = NULL;
	struct modem_logger *logger;
	ssize_t left_size = 0;

	modem_log_debug("entry\n");

	nfds = 0;
	logger_for_each(logger, logger_list) {
		++nfds;
	}

	modem_log_debug("%d nfds prepare to alloc\n\n", nfds);
	pollfds = calloc(nfds, sizeof(struct pollfd));
	if (!pollfds) {
		perror("no pollfds\n");
		exit(-1);
	}

	p = pollfds;
	logger_for_each(logger, logger_list) {
		p->fd = logger->input_file.fd;
		p->events = POLLIN;
		logger->revents = &p->revents;
		++p;
	}

	while(1) {
		int result;
		/* wait forever, if no data */
		result = TEMP_FAILURE_RETRY(poll(pollfds, nfds, -1));
		if (result <= 0)
		{
			modem_log_debug("modem log cat poll error\n");
		}
		else
		{
			modem_log_debug("modem log cat poll ok\n");
		}

		logger_for_each(logger, logger_list) {
			if (!(*(logger->revents) & POLLIN)) {
				modem_log_debug("[%s]no data to handle\n", logger->input_file.name);
				continue;
			}
			enum MODEM_OUT_FILE_TYPE log_type = logger->output_file.type;
			modem_log_debug("[%s]: log_type=%d, revents=0x%x, pollin=0x%x\n", logger->input_file.name, log_type, *(logger->revents), POLLIN);
			if (MODEM_T_PARSER_STRING == log_type || MODEM_T_PARSER_BINARY == log_type) {
				pmom_cat(logger, &left_size);
			} else {
				modem_dmesg_cat(logger);
			}
		}
	} /* while(1) */

	free(pollfds);
	logger_for_each(logger, logger_list) {
		close(logger->input_file.fd);
		close(logger->output_file.fd);
	}
	modem_log_pr_err("exit\n");
}

static void show_help(const char *cmd)
{
	modem_log_pr_err("Usage: %s [options] \n", cmd);

	modem_log_pr_err( "options include:\n"
		"  -i <input device node>	Device node from where data comes\n"
		"  -e <encode>	 Log in which type, 'b' or 's', 'pb' or 'ps', represens binary or string, parser binary or parser string\n"
		"  -f <filename>   Log to file. Default to stdout\n"
		"  -r [<kbytes>]   Rotate log every kbytes. (16 if unspecified). Requires -f\n"
		"  -z <count>	   Sets max number of tarballs to <count>, default 5\n"
		"  -n <count>	   Sets max number of rotated logs to <count>, default 4\n");
}

int main(int argc, char **argv)
{
	int ret;
	struct argv_cnt  argv_count;
	struct modem_logger log_device;
	struct modem_logger *logger;

	if (getuid() == 0) {
		umask(022);
	}

	if (2==argc && 0 == strcmp(argv[1], "--help")) {
		show_help(argv[0]);
		exit(0);
	}

	memset(&g_modem_log_cat, 0, sizeof(g_modem_log_cat));
	modem_list_init(&g_modem_log_cat.node);
	memset(&argv_count, 0, sizeof(argv_count));

	for (;;) {
		ret = getopt(argc, argv, "d:i:e:f:n:r:z:");

		if (ret < 0) {
			break;
		}

		switch(ret) {
			case 'i':
				if (optarg == NULL){
					goto out;
				} else {
					log_device.input_file.name = optarg;
				}
				argv_count.ni++;
				break;
			case 'e':
				if (!strcmp("s", optarg)){
					log_device.output_file.type = MODEM_T_STRING;
				} else if (!strcmp("b", optarg)){
					log_device.output_file.type = MODEM_T_BINARY;
				} else if (!strcmp("pms", optarg)){
					log_device.output_file.type = MODEM_T_PARSER_STRING;
				} else if (!strcmp("pmb", optarg)){
					log_device.output_file.type = MODEM_T_PARSER_BINARY;
				} else {
					goto out;
				}
				argv_count.ne++;
				break;
			case 'f':
				if (optarg == NULL) {
					goto out;
				} else {
					log_device.output_file.name = optarg;
				}
				argv_count.nf++;
				break;
			case 'r':
				if (optarg == NULL) {
					log_device.output_file.rotate_size = MODEM_LOG_DEFAULT_ROTATE_KBYTE_SIZE;
				} else {
					if (!isdigit(optarg[0])) {
						goto out;
					}
					log_device.output_file.rotate_size = atoi(optarg);
				}
				argv_count.nr++;
				break;
			case 'z':
				if (optarg == NULL) {
					log_device.output_file.zip_threshold = MODEM_LOG_DEFAULT_COMPRESS_NUM;
				} else {
					if (!isdigit(optarg[0])) {
						goto out;
					}
					log_device.output_file.zip_threshold = atoi(optarg);
				}
				argv_count.nz++;
				break;
			case 'n':
				if (optarg == NULL) {
					log_device.output_file.rotate_threshold = MODEM_LOG_DEFAULT_COMPRESS_NUM;
				} else {
				if (!isdigit(optarg[0])) {
					goto out;
				}
				log_device.output_file.rotate_threshold = atoi(optarg);
				}
				if (log_device.output_file.rotate_threshold > MODEM_LOG_MAX_COMPRESS_NUM) {
					log_device.output_file.rotate_threshold = MODEM_LOG_MAX_COMPRESS_NUM;
				}
				argv_count.nn++;
				break;
			default:
				modem_log_pr_err( "Unrecognized Option %c\n", ret);
				show_help(argv[0]);
				exit(-1);
				break;
		}/* end switch */

		if (argv_count.ni && argv_count.ni == argv_count.ne && argv_count.ne == argv_count.nf) {
			logger = calloc(1, sizeof(*logger));
			if (!logger) {
				perror("no memory\n");
				exit(-1);
			}

			modem_log_debug("%d logs to be handled\n", argv_count.ni);

			memcpy(logger, &log_device, sizeof(log_device));
			logger->top = &g_modem_log_cat;
			logger->output_file.str_wr = 0;

			modem_list_add_tail(&g_modem_log_cat.node, &logger->node);
		}
	}/* end for(;;) */

	if (modem_logger_open(&g_modem_log_cat)) {
		perror("no file to operation!\n");
		exit(-1);
	}

	modem_log_cat(&g_modem_log_cat);

	return 0;
out:
	modem_log_pr_err( "Invalid parameter to -%c\n", ret);
	show_help(argv[0]);
	exit(-1);
}

