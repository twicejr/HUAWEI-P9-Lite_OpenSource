#ifndef   MNTN_WATCHPOINT_H
#define    MNTN_WATCHPOINT_H
enum acpu_num{
 ACPU0 ,
 ACPU1 ,
 ACPU2 ,
 ACPU3 ,
};

enum watchpoint_type{
       WP_RESERVED,
       WP_MATCH_READ,
       WP_MATCH_WRITE,
       WP_MATCH_ALL
};

typedef struct watchpoint{
        unsigned int addr;   
	unsigned int point_type;
	unsigned int addr_mask_bits;
	void*  user_param;
	int (*watchpoint_callback)(unsigned int addr, void* regs,void* user_param);
}watchpoint_t;

/*watchpoint operation method*/
extern int  set_debug_watchpoint(unsigned int cpu,  watchpoint_t* wp );
extern int  clear_debug_watchpoint(unsigned int  cpu, unsigned int addr);
extern int  clear_debug_watchpoint_all_cpus(unsigned int addr);
extern int  set_debug_watchpoint_all_cpus(watchpoint_t * wp);
#endif
