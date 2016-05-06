
#ifndef  __PARAM_TO_SEC_OS_H__
#define  __PARAM_TO_SEC_OS_H__

#ifdef __cplusplus
extern "C"
{
#endif

void set_param_cfg_to_sec(void);

#define BALONG_PARAM_BASE_ADDR        (0x365FF800)    /* 0x365FF800--0x365FF8FF */
#define PARAM_MAGIC_OFFSET            (0x0)           /* 魔数:判断参数有效性 */
#define PARAM_CFG_OFFSET              (0x8)           /* 配置参数存放基地址*/

typedef struct tag_PARAM_CFG
{
    unsigned int   magic;                   /* 魔数，标识配置参数的状态 */
    unsigned int   protect_barrier_size;    /* 预留(4K)防止被踩，初始化为全F */
    unsigned int   param_cfg_size;          /* 配置参数预留(16K)大小 */
    unsigned int   icc_channel_base_addr;
    unsigned int   icc_channel_max_size;

}g_param_cfg;


#ifdef __cplusplus
}
#endif

#endif   /* __PARAM_TO_SEC_OS_H__ */

