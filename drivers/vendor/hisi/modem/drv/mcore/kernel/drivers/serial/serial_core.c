
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <serial_core.h>

static LIST_HEAD(uart_drivers);			/* linked list of uart drivers */
static LIST_HEAD(uart_devices);			/* linked list of uart devices */

static struct uart_port *uap;

/*
 *  driver
 */
int uart_register_driver(struct uart_driver *drv)
{
    unsigned long flags;
    
    local_irq_save(flags);
    list_add_tail(&drv->uart_drivers, &uart_drivers);
    local_irq_restore(flags);
    return 0;
}

/*lint --e{530}*/
static struct uart_driver *get_uart_driver(struct uart_port *port)
{
    struct uart_driver *drv;
    unsigned long flags;
    
    local_irq_save(flags);
    if (!list_empty(&uart_drivers)) {
        list_for_each_entry(drv, &uart_drivers, uart_drivers) {
            if (drv->periphid == port->periphid){
                local_irq_restore(flags);
                return drv;
            }
        }
    }
    local_irq_restore(flags);
    
    return NULL;
}

/*
 *  device
 */
int uart_register_device(struct uart_port *port)
{
    struct uart_driver *drv;
    unsigned long flags;
    
    local_irq_save(flags);    
    list_add_tail(&port->uart_devices, &uart_devices);
    local_irq_restore(flags);
    
    /*foreach drivers,get driver by pid, set p->driver= driver*/
    drv = get_uart_driver(port);
    if (NULL == drv)
        return -1;
    
    port->driver = drv;
    return 0;
}

struct uart_port *uart_get_device(unsigned int id)
{
    struct uart_port *port;
    unsigned long flags;
    
    local_irq_save(flags);  
    if (!list_empty(&uart_devices)) {
        list_for_each_entry(port, &uart_devices, uart_devices) {
            if (port->id == id){
                local_irq_restore(flags);
                return port;
            }
        }
    }
    local_irq_restore(flags);
    return NULL;
}

void uart_put_char(struct uart_port *port, unsigned char ch)
{
	if(port->driver && port->driver->ops && port->driver->ops->put_char)
		port->driver->ops->put_char(port, ch);
}

int uart_get_char(struct uart_port *port)
{
    int ch = 0;
	
	if(port->driver && port->driver->ops && port->driver->ops->get_char)
		ch = port->driver->ops->get_char(port);

	return ch;
}

void uart_start_tx(struct uart_port *port)
{
	if(port->driver && port->driver->ops && port->driver->ops->start_tx)
		port->driver->ops->start_tx(port);
}

int uart_suspend_port(void)
{ 
	if (!uap)
		return -1;

	if(uap->driver && uap->driver->ops && uap->driver->ops->suspend)
	{
		if (uap->driver->ops->suspend(uap))
			return -1;
	}
	return 0;
}

int uart_resume_port(void)
{ 
	if (!uap)
		return -1;
	
	if(uap->driver && uap->driver->ops && uap->driver->ops->resume)
	{
		if (uap->driver->ops->resume(uap))
			return -1;
	}

	return 0;
}

/*
 *  ldisc
 */
int uart_register_ldisc(struct uart_ldisc *ldisc)
{
    struct uart_port *port;
    unsigned long flags;

    /*foreach devices,get device by id, set port->ldisc= p*/
    port = uart_get_device(ldisc->id);
    if (NULL == port)
        return -1;

    uap = port;
    local_irq_save(flags);
    ldisc->port = port;
    port->ldisc = ldisc;
    local_irq_restore(flags);

    (void)port->driver->ops->startup(port);

    return 0;
}
 
int uart_unregister_ldisc(struct uart_ldisc *ldisc)
{
    struct uart_port *port;
    unsigned long flags;

    /*foreach devices,get device by id, set port->ldisc= p*/
    port = uart_get_device(ldisc->id);
    if (NULL == port)
        return -1;
    
    //port->driver->ops->shutdown(port);
    
    local_irq_save(flags);
    ldisc->port = NULL;
    port->ldisc = NULL;  
    local_irq_restore(flags);   

    return 0;  
}

