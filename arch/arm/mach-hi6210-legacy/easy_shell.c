#include <linux/module.h>
#include <linux/string.h>
#include <linux/kallsyms.h>
#include <linux/tty.h>
#include <linux/io.h>

#define ES_TTY_MAJOR		220
#define ES_TTY_MINORS		1
#define ES_TTY_IOCTL_SIGN	0xCAFA0000
#define ES_TTY_IOCTL_CALL	0xCAFA0001
#define VALID_SIGN(tty_termios)	((ES_TTY_MAJOR<<24) | C_BAUD(tty_termios))

typedef struct shell_tty_call_arg {
	int sign_word;
	char *func_name;
	union {
		int args[6];
		struct {
			int arg1;
			int arg2;
			int arg3;
			int arg4;
			int arg5;
			int arg6;
		};
	};
}shell_tty_call_arg, *p_shell_tty_call_arg;

typedef int (*call_ptr)(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

static struct tty_driver *shell_tty_drv;

static int shell_call(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

/*below functions are used for system debug*/

#define REG_VIR_ADDR_MAP(phyAddr)        ioremap(phyAddr,sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr)      iounmap(virAddr)

void reg_dbg_dump(unsigned int pAddr, unsigned int size, unsigned int nodesize)
{
    unsigned int virAddr;
    unsigned int i;

    if (((nodesize != sizeof(char))&&(nodesize != sizeof(short))
           &&(nodesize != sizeof(int)))) {
        printk("dump type should be 1(char),2(short),4(int)\n");
        return;
    }

    printk("\n");

    virAddr = ioremap(pAddr,nodesize*size);

    for (i=0;i<size;i++) {
        if ((i*nodesize)%16 == 0) {
            printk("\n[%08x]: ",pAddr + (i*nodesize));
        }

        switch (nodesize) {
            case sizeof(char):
                printk("%02x ",*((unsigned char*)virAddr + i));
                break;
            case sizeof(short):
                printk("%04x ",*((unsigned short*)virAddr + i));
                break;
            case sizeof(int):
                printk("%08x ",*((unsigned int*)virAddr + i));
                break;
            default:
                break;
        }
    }

    printk("\n");
    iounmap(virAddr);

}

void lkup(char *func_name)
{
    unsigned long address;
    if (func_name) {
	    address = (unsigned long) kallsyms_lookup_name(func_name);
	    printk("lk_addr (0x%x)%s \n",address,func_name);
	} else {
	    printk("null func\n");
	}
}





/***********************************************************
 Function: reg_write_u32--write an UINT32 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_uint16
 History:
 1.    2012.8.20   Creat
************************************************************/
void reg_write_u32(unsigned int pAddr, unsigned int value)
{
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    *(volatile unsigned int *)(virAddr)=value;
    REG_VIR_ADDR_UNMAP(virAddr);
}

/***********************************************************
 Function: reg_write_u16--write an UINT16 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
void reg_write_u16(unsigned int pAddr, unsigned short value)
{
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    *(volatile unsigned short *)(virAddr)=value;
    REG_VIR_ADDR_UNMAP(virAddr);
}

/***********************************************************
 Function: reg_write_u8--write an UINT8 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
void reg_write_u8(unsigned int pAddr, unsigned char value)
{
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    *(volatile unsigned char *)(virAddr)=value;
    REG_VIR_ADDR_UNMAP(virAddr);
}

/***********************************************************
 Function: reg_read_u32 --read an UINT32 value from physical memory
 Input:    the  read address
 return:   the value
 see also: read_u16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned int reg_read_u32(unsigned int pAddr)
{
    unsigned int value = 0;
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    value = *(volatile unsigned int *)(virAddr);
    REG_VIR_ADDR_UNMAP(virAddr);

    return value;
}

/***********************************************************
 Function: reg_read_u16 --read an UINT16 value from physical memory
 Input:    the  read address
 return:   the value
 see also: read_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned short reg_read_u16(unsigned int pAddr)
{
    unsigned short value = 0;
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    value = *(volatile unsigned short *)(virAddr);
    REG_VIR_ADDR_UNMAP(virAddr);

    return value;
}

/***********************************************************
 Function: reg_read_u8 --read an UINT8 value from physical memory
 Input:    the  read address
 return:   the value
 see also: read_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned char reg_read_u8(unsigned int pAddr)
{
    unsigned char value = 0;
    unsigned int virAddr = 0;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    value = *(volatile unsigned char *)(virAddr);
    REG_VIR_ADDR_UNMAP(virAddr);

    return value;
}

/***********************************************************
 Function: write_uint32--write an UINT32 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_uint16
 History:
 1.    2012.8.20   Creat
************************************************************/
void write_u32(unsigned int pAddr, unsigned int value)
{
    *(volatile unsigned int *)(pAddr)=value;
}

/***********************************************************
 Function: write_u16--write an UINT16 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
void write_u16(unsigned int pAddr, unsigned short value)
{
    *(volatile unsigned short *)(pAddr)=value;
}

/***********************************************************
 Function: write_u8--write an UINT8 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
void write_u8(unsigned int pAddr, unsigned char value)
{
    *(volatile unsigned char *)(pAddr)=value;
}

/***********************************************************
 Function: read_u32 --read an UINT32 value from memory
 Input:    the  read address
 return:   the value
 see also: read_u16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned int read_u32(unsigned int pAddr)
{
    unsigned int value = 0;
    value = *(volatile unsigned int *)(pAddr);
    return value;
}

/***********************************************************
 Function: read_u16 --read an UINT16 value from memory
 Input:    the  read address
 return:   the value
 see also: read_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned short read_u16(unsigned int pAddr)
{
    unsigned short value = 0;
    value = *(volatile unsigned short *)(pAddr);
    return value;
}

/***********************************************************
 Function: read_u8 --read an UINT8 value from memory
 Input:    the  read address
 return:   the value
 see also: read_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned char read_u8(unsigned int pAddr)
{
    unsigned char value = 0;
    value = *(volatile unsigned char *)(pAddr);
    return value;
}
static int shell_open(struct tty_struct *tty, struct file *filp)
{
    printk("easy shell open \n");
    return 0;
}

static void shell_close(struct tty_struct *tty, struct file *filp)
{
    printk("easy shell close \n");
}

static int shell_ioctl(struct tty_struct *tty, unsigned int cmd, unsigned long arg)
{
	p_shell_tty_call_arg call_arg = NULL;

	switch (cmd)
	{
	case ES_TTY_IOCTL_SIGN:
		return VALID_SIGN(tty);

	case ES_TTY_IOCTL_CALL:
		call_arg = (p_shell_tty_call_arg) arg;
		if (call_arg->sign_word & ~VALID_SIGN(tty)) {
			printk("Unallowed call\n");
			return -EPERM;
		}

		return shell_call(call_arg->func_name,
				call_arg->arg1,
				call_arg->arg2,
				call_arg->arg3,
				call_arg->arg4,
				call_arg->arg5,
				call_arg->arg6);

	default:
		printk("shell_ioctl unknown cmd 0x%x %s\n", cmd,call_arg->func_name);
		break;
	}

	return -ENOIOCTLCMD;
}

static struct tty_operations shell_ops = {
    .open  = shell_open,
    .close = shell_close,
    .ioctl = shell_ioctl,
};

int shell_init()
{
	printk("Enter ecall init\n");

    shell_tty_drv = alloc_tty_driver(ES_TTY_MINORS);
    if (!shell_tty_drv) {
        printk("Cannot alloc shell tty driver\n");
        return -1;
    }

    shell_tty_drv->owner = THIS_MODULE;
    shell_tty_drv->driver_name = "es_serial";
    shell_tty_drv->name = "es_tty";
    shell_tty_drv->major = ES_TTY_MAJOR;
    shell_tty_drv->minor_start = 0;
    shell_tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
    shell_tty_drv->subtype = SERIAL_TYPE_NORMAL;
    shell_tty_drv->flags = TTY_DRIVER_REAL_RAW;
    shell_tty_drv->init_termios = tty_std_termios;
    shell_tty_drv->init_termios.c_cflag = B921600 | CS8 | CREAD | HUPCL | CLOCAL;

    tty_set_operations(shell_tty_drv, &shell_ops);

    if (tty_register_driver(shell_tty_drv)) {
        printk("Error registering shell tty driver\n");
        put_tty_driver(shell_tty_drv);
        return -1;
    }

	printk("Finish ecall init\n");

	return 0;
}

static int shell_call(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
	int result = -1;
	call_ptr address;

	if (!func_name)
		goto call_error_input;

	address = (call_ptr) kallsyms_lookup_name(func_name);
	if (!address)
		goto call_no_symbol;

	result = address(arg1, arg2, arg3, arg4, arg5, arg6);

	printk("Call %s return, value = 0x%x\n", func_name, result);
	return result;

call_error_input:
	printk("Error input, value = -1\n");

call_no_symbol:
	printk("Invalid function, value = -1\n");
	return -1;
}

module_init(shell_init)

