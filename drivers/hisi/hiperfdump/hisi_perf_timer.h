/*use dual timer5 which clock name is clk_timclk6 in dts*/
#define RES_SIZE    0x1000
#define TIMER5_BASE 0xFFF19000
#define TIMER5_IRQ  90
#define TIMER_NAME "clk_timer5_a"

struct hisi_bw_dump {
    void (*hisi_moudle_dump_stop)(void);
    void (*hisi_moudle_dump_print)(void);
    void (*hisi_moudle_dump_restart)(void);
};

int hisi_bw_timer_set_callback(struct hisi_bw_dump moudle_callback);
void hisi_bw_timer_clear_callback(void);

int hisi_bw_timer_init(int bind_cpu_id);
int hisi_bw_timer_deinit(void);
int hisi_pm_bw_on_timer(unsigned int seconds, unsigned int useconds);
