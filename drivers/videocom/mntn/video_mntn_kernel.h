

#ifndef _VIDEO_MNTN_KERNEL_H_
#define _VIDEO_MNTN_KERNEL_H_
#include <linux/types.h>
#include "video_mntn_types.h"


extern mntn_data_save_module  g_mntn_video_save_data_module[];
extern mntn_log_module_t  g_mntn_log_module_id[];


void mntn_save_data(mntn_data_module_id_type ModuleId, void *Buffer, const int Size, int Width, int Hight, char *SaveTypes);

void init_mntn_video_module(void);

extern void mntn_test(void);

extern void init_mntn_log_module(void);
extern int  mntn_video_print(uint32_t module_id, uint8_t log_level, char *fmt, ...);

#define mntn_print_log(module_id, log_level, fmt, ...) mntn_video_print(module_id, log_level, "<2>" "[%s]" fmt "\n", g_mntn_log_module_id[module_id].module_name, ##__VA_ARGS__)

bool is_log_module_valid(uint32_t module_id, const char *name, uint8_t default_level);
void clear_mntn_log_module(void);
bool register_mntn_log_module(uint32_t module_id, const char *name, uint8_t default_level);
bool is_data_module_valid(unsigned moduleId, const char *moduleName, int frameNum,mntn_data_save_type imageOrVideo);
bool register_mntn_video_save_data_module(unsigned moduleId, const char *moduleName, unsigned frameNum,mntn_data_save_type imageOrVideo);
void clear_mntn_video_save_data_module(void);


#endif

/**************************************************************************************************/
