#ifndef __HI6555C_DEBUG_H__
#define __HI6555C_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define CONFIG_DEBUG_POP 1

/* Debug info */
#define ERROR_LEVEL     1
#define INFO_LEVEL      1
#define DEBUG_LEVEL     0

#define LOG_TAG "hi6555c"

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

#ifdef CONFIG_DEBUG_POP
enum hi6555c_debug_pop_op {
	HI6555C_POP_CLEAN     = 0, /* CLEAN */
	HI6555C_POP_DELAY_MS  = 1, /* DELAY */
	HI6555C_POP_DELAY_US  = 2, /* DELAY */
	HI6555C_POP_REG_WRITE = 3, /* REG WRITE */
};

struct hi6555c_debug_ps_cache {
	unsigned int reg;
	unsigned int val;
	enum hi6555c_debug_pop_op op;
};
#endif/*CONFIG_DEBUG_POP*/

#ifdef ENABLE_CODEC_DEBUG
extern int hi6555c_debug_init(struct snd_soc_codec *codec);
extern void hi6555c_debug_uninit(struct snd_soc_codec *codec);
extern void hi6555c_debug_reg_wr_cache(unsigned int reg, int val);
extern void hi6555c_debug_reg_rd_cache(unsigned int reg, unsigned int val);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
