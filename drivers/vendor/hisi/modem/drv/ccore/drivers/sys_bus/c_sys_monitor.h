#ifndef __C_SYS_MONITOR_H__
#define __C_SYS_MONITOR_H__

#define MAX_SYS_CHAN_NUM    8
#define MAX_SYS_PORT_NUM    8


#define CNT_STATE_INT  0x8
#define PORT_SEL       0x1C
#define CNT_ID         0x100
#define ID_ADDR_DES    0x104
#define ID_ADDR_DES_M  0x108
#define READ_BYTES_ID  0x1E8
#define WRITE_BYTES_ID 0x1F0

struct sys_monitor{
    struct device_node  *of_node;
    u32 base_addr;
    u64 totaltime;
    u64 start_t;
    u64 end_t;
};

struct sys_amon_chan{
    const char* name;
    u32 chan_id;        /* chan id 指示用于监控的资源号 */
    u32 use_flag;       /* 指示当前chan是否可使用 */
    u32 reset_flag;     /* 复位标志，匹配到监控条件是否复位 */
    u32 opt_type;       /* 监控类型，01:读，10:写，11:读写，其余值:不监控 */
    u32 port;           /* 监控端口 */
    u32 id_enable;      /* 是否id 使能*/
    u32 cnt_id;
    u32 cnt_id_mask;
    u32 adr_enable;     /* 是否addresss使能*/
    u32 start_addr;     /* 监控起始地址 */
    u32 end_addr;       /* 监控结束地址 */
    u32 read_bytes[2];
    u32 write_bytes[2];
};

enum sys_amon_enable{
    SYS_AMON_ID_ENABLE = 0,
    SYS_AMON_ADR_ENABLE = 1,
    SYS_AMON_BOTH_ENABLE = 2,
    SYS_AMON_NONE_ENABLE = 3
};

void sys_monitor_init(void);
void sys_mon_help(void);
u32 sys_mon_config_id(u32 id, u32 enable, u32 start_addr, u32 end_addr);
u32 sys_mon_config_port(u32 port, u32 start_addr, u32 end_addr);
void sys_mon_one_free(u32 chan);
void sys_mon_all_free(void);
void sys_mon_result(void);
void sys_mon_result_and_start(void);
void sys_mon_start(void);
void sys_mon_chan_info(void);

#endif /* __C_SYS_EDMA_H__ */
