#ifndef _LOG_EXCEPTION_H
#define _LOG_EXCEPTION_H


#define LOG_EXCEPTION_FS "/dev/hwlog_exception"

#if defined (CONFIG_LOG_EXCEPTION)
extern int log_to_exception(char* tag, char* msg);
#else
#define log_to_exception(tag, msg)	(-ENOENT)
#endif

#define log_exception		log_to_exception


#endif	//#ifndef _LOG_EXCEPTION_H
