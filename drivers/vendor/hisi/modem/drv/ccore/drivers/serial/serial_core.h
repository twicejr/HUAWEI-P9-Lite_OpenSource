
#ifndef SERIAL_CORE_H
#define SERIAL_CORE_H
 
#include <osl_list.h>
#include "../console/console.h"

struct uart_port;

struct uart_ops {
    unsigned int (*tx_empty)(struct uart_port *);
    void		 (*set_mctrl)(struct uart_port *, unsigned int mctrl);
    unsigned int (*get_mctrl)(struct uart_port *);
    void		 (*stop_tx)(struct uart_port *);
    void		 (*start_tx)(struct uart_port *);
    void		 (*throttle)(struct uart_port *);
    void		 (*unthrottle)(struct uart_port *);
    void		 (*send_xchar)(struct uart_port *, char ch);
    void		 (*stop_rx)(struct uart_port *);
    void		 (*enable_ms)(struct uart_port *);
    void		 (*break_ctl)(struct uart_port *, int ctl);
    int		     (*startup)(struct uart_port *);
    void		 (*shutdown)(struct uart_port *);
    void		 (*flush_buffer)(struct uart_port *);
    void		 (*set_termios)(struct uart_port *);
    void		 (*set_ldisc)(struct uart_port *, int new);
    void		 (*put_char)(struct uart_port *, unsigned char);
    int		     (*get_char)(struct uart_port *);
    int 	     (*suspend)(struct uart_port *);
    int  	     (*resume)(struct uart_port *);
};

struct uart_driver {
    struct uart_ops	*ops;
    unsigned int periphid;
    const char	 *driver_name;
    struct list_head uart_drivers;
};

struct uart_ldisc{
	struct console * bind_con;
    unsigned int  (*tx_chars)(char *ch);     /* Tx callback */
    unsigned int  (*rx_chars)(char *ch);     /* Rx callback */
    unsigned int  id;
    struct uart_port *port;
};

struct uart_port {
    unsigned int        id;
    unsigned int        base_addr;		/* read/write[bwl] */
    unsigned int        irq;			/* irq number */
    unsigned int        baudrate;	    /* baud rate */
    unsigned int        uartclk;		/* base uart clock */
    unsigned int        periphid;
    struct uart_driver  *driver;
    struct uart_ldisc   *ldisc;
    struct list_head    uart_devices;
};

/*
 *  driver
 */
int uart_register_driver(struct uart_driver *drv);

/*
 *  device
 */
int uart_register_device(struct uart_port *port);

struct uart_port *uart_get_device(unsigned int id);

void uart_put_char(struct uart_port *port, unsigned char ch);

int uart_get_char(struct uart_port *port);

void uart_start_tx(struct uart_port *port);

/*
 *  ldisc
 */
int uart_register_ldisc(struct uart_ldisc *ldisc);
 
int uart_unregister_ldisc(struct uart_ldisc *ldisc);

/*
 *  change baudrate
 */
void uart_change_baudrate(unsigned int baudrate);

#endif /* SERIAL_CORE_H */

