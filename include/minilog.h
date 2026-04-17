#ifndef __MINILOG_H
#define	__MINILOG_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_LOG	1

extern FILE *g_log_file;
void app_start_log(const char *pLogPath);
extern void app_write_log(FILE *stream,const char *file_name,const int line,const char *fmt,...);
void app_stop_log();
	
#ifdef DEBUG_LOG
#define log_dbg(args...)		\
		do					\
		{		\
			app_write_log(g_log_file,__FILE__,__LINE__,##args);   \
		}while(0) 
#else
#define log_dbg(args,...)
#endif

#ifdef __cplusplus
}
#endif


#endif
