#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

#include "tarzip.h"
#include "modem_dmesg_cat.h"

static char* strchrnul(const char* s, char c)
{
	while( *s != '\0' && (*s != c))
		s++;
	return (char*)s;
}
static void overlapping_strcpy(char *dst, const char *src)
{
	if(dst != src){
		while((*dst = *src) != '\0'){
			dst++;
			src++;
		}
	}
}

void modem_dmesg_cat(struct modem_logger *logger)
{
	char *buf         = NULL;
	char *start = NULL;
	char *newline = NULL;
	struct timeval tv;
	struct tm *ptm;
	size_t bsize = MODEM_LOG_CAT_BUFSIZE;
	ssize_t nr, nw, read_off  = 0;
	int timestamp = 0;
	int used = 0;
	struct modem_logger_list *logger_list = logger->top;

	buf = logger_list->raw_buf;
	start = buf + used;

	modem_log_debug("[%s]: begin, timestamp=0x%x\n", logger->input_file.name, timestamp);
	nr = read(logger->input_file.fd, start, (bsize - 1) - used);
	if(nr < 0)
	{
		if (errno == EINTR) 
		{
			perror("kmsgcat read failure!\n");
			sleep(1);
			return;
		}
	}

	read_off = 0;
	start[nr] = '\0';
	start = buf;

	if (0 == timestamp) {
		if (0 != access(logger->output_file.name, F_OK)) {
			modem_log_rotate(logger);
		}

		while (read_off < nr) {
			do {
				nw = write (logger->output_file.fd, start + read_off, nr - read_off);
			} while (nw < 0 && nw == EINTR);

			if (nw < 0) {
				break;
			}
			read_off += nw ;
		}
	} else {
		for(; ;) {
			nw = 0;
			newline = strchrnul(start, '\n');
			if(*newline == '\0') {
				/* incomplete line, move it to the front of buf */
				overlapping_strcpy(buf, start);
				used = newline - start;
				if((size_t)used < bsize-1)
					break;
				used = 0;
				newline = NULL;
			} else {
				*newline++ = '\0';
			}

			if(*start) {
				/* get UTC time */
				gettimeofday(&tv, NULL);

				/* get local time */
				ptm = localtime(&(tv.tv_sec));
				if (ptm) {
					/* make timestamp format like logcat's */
					strftime(logger_list->timebuf, sizeof(logger_list->timebuf), "%m-%d %H:%M:%S", ptm);
					snprintf(logger_list->str_buf, sizeof(logger_list->str_buf), "%s.%03ld %s\n", logger_list->timebuf, tv.tv_usec / 1000, start);
				} else {
					/* actually, localtime() should be success each time */
					snprintf(logger_list->str_buf, sizeof(logger_list->str_buf), "%s\n", start);
				}

				if(0 != access(logger->output_file.name, F_OK)) {
					modem_log_rotate(logger);
				}
				nw = write(logger->output_file.fd, logger_list->str_buf, strlen(logger_list->str_buf));
			}
			if(!newline) {
				break;
			}
			start = newline;
			read_off += nw;
		}//for(;;) parser each line
	}// if (timestamp == 0)

	modem_log_debug("[%s]: end, nr=0x%x, read_off=0x%x\n\n", logger->input_file.name, (unsigned int)nr, (unsigned int)read_off);

	logger->output_file.size_cnt += read_off;
	if (logger->output_file.rotate_size > 0 && (logger->output_file.size_cnt / 1024) >= logger->output_file.rotate_size ) {
		modem_log_debug("kmsgcat rotate file\n");
		modem_log_rotate(logger);
	}
}