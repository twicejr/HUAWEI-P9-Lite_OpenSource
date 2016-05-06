/*
 * ext_modem.h
 *
 */
#ifndef EXT_MODEM_H
#define EXT_MODEM_H

#include <linux/init.h>
#include <linux/semaphore.h>
#include <linux/workqueue.h>
#include <linux/wait.h>

#define WAIT_APCP_BUS_RESUME_TIMEOUT 2000
#define MAX_WAIT_BUS_RESUME_TIMES 6


typedef enum bus_type_e
{
    MODEM_BUS_SPI = 0,
    MODEM_BUS_SDIO,
    MODEM_BUS_MAX_NUM,
} bus_type_et;

enum flow_ctrl_state_e
{
    HARDWARE_FLOW_CTRL_DISABLE = 0,
    HARDWARE_FLOW_CTRL_ENABLE
};

enum ap_bus_resume_status
{
    AP_BUS_SUSPEND,
    AP_BUS_RESUMED,
};

typedef void (*pf_mdm_reset_handle)(void);

typedef struct modem_bus
{
    bus_type_et m_bus_type;
    unsigned int m_fifo_size;
    int (*pfm_bus_write)(void* pt_buf, size_t t_len);
    int (*pfm_bus_read)(void* pt_buf, size_t t_len);
    int (*pfm_bus_lock)(int t_lock);
    int (*pfm_bus_irq_enable)(int t_enable);
} modem_bus_t;

/* data struct of modem common driver */
typedef struct ext_modem
{
    modem_bus_t* pm_cur_bus; /* point to current board actual bus used */
    unsigned int m_mdm_bus_ready; /* check whether modem spi or sdio bus is ready or not */

    struct semaphore m_bus_sema; /* used semaphore as bus lock */

    atomic_t m_ap_resume_atom; /* atomic flag to mark ap host resumed */
    wait_queue_head_t m_ap_resume_waitq; /* waitqueue used for wait ap host resumed */

    struct workqueue_struct* pm_reset_wq; /* workqueue thread for modem reset */
    struct work_struct m_reset_work; /* modem reset work */
    pf_mdm_reset_handle m_arr_reset_handle[MODEM_BUS_MAX_NUM];
} ext_modem_t;

void modem_bus_register(modem_bus_t* pt_bus);
void modem_register_reset_handle(bus_type_et t_type, pf_mdm_reset_handle pt_handle);
void modem_reset_handle(void);
int wait_ap_bus_resumed(void);
int modem_write(char* pt_pkt_buf, int t_len);
int modem_read(char* pt_buf, int t_include_head, int t_head_size, int t_len);
unsigned int get_modem_bus_state(void);
void set_modem_bus_state(unsigned int t_ready);
void set_ap_bus_suspend(void);
void set_ap_bus_resumed(void);

int ext_modem_init(void);
void ext_modem_exit(void);

#endif
