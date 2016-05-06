

#ifndef __PLAT_UART_H__
#define __PLAT_UART_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include <linux/serial_core.h>
#include "plat_type.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
typedef  enum {
    STATE_TTY_TX = 0,
    STATE_TTY_RX = 1,
    STATE_UART_TX = 2,
    STATE_UART_RX = 3,
}UART_STATE_INDEX;
/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
struct ps_uart_state_s {
    uint32 tty_tx_cnt;
    uint32 tty_rx_cnt;
    struct uart_icount uart_cnt;
};
/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern int32 plat_uart_init(void);
extern int32 plat_uart_exit(void);
extern int32 open_tty_drv(void *pm_data);
extern int32 release_tty_drv(void *pm_data);
extern int32 ps_change_uart_baud_rate(int64 baud_rate, uint8 enable_flowctl);
extern void ps_uart_tty_tx_add(uint32 cnt);
extern void ps_uart_state_pre(struct tty_struct *tty);
extern void ps_uart_state_dump(struct tty_struct *tty);
extern uint32 ps_uart_state_cur(uint32 index);
#endif

