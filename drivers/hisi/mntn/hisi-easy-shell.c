#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/kallsyms.h>
#include <linux/tty.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define ES_TTY_MAJOR        221
#define ES_TTY_MINORS       1
#define ES_TTY_IOCTL_SIGN   0xCAFA0000
#define ES_TTY_IOCTL_CALL   0xCAFA0001
#define VALID_SIGN(tty_termios) ((ES_TTY_MAJOR<<24) | C_BAUD(tty_termios))

/*it's ecall an variable, if the first input parameter is this value
the same as the one defined in ecall.c*/
#define DBG_ECALL_VARIABLE              0x28465793
typedef struct shell_tty_call_arg {
	int sign_word;
	char *func_name;
	char *arg_str1;
	union {
		long long args[6];
		struct {
			long long arg1;
			long long arg2;
			long long arg3;
			long long arg4;
			long long arg5;
			long long arg6;
		};
	};
} shell_tty_call_arg, *p_shell_tty_call_arg;

/* the struct for 32bit userspace ecall*/
typedef struct shell_tty_call_arg32 {
	int sign_word;
	int func_name;		/* to aligned space the same as 32bit userspace,actully it's a userpace pointer */
	char *arg_str1;
	union {
		long long args[6];
		struct {
			long long arg1;
			long long arg2;
			long long arg3;
			long long arg4;
			long long arg5;
			long long arg6;
		};
	};
} shell_tty_call_arg32, *p_shell_tty_call_arg32;

long long dbg_value_for_ecall = 0x12345678;	/*only for testing ecall + variable */
typedef long long (*call_ptr_with_str) (char *arg_str1, long long arg1,
					long long arg2, long long arg3,
					long long arg4, long long arg5,
					long long arg6);
typedef long long (*call_ptr) (long long arg1, long long arg2, long long arg3,
			       long long arg4, long long arg5, long long arg6);

static struct tty_driver *shell_tty_drv;
static struct tty_port shell_tty_port;
static long long shell_call(char *func_name, char *arg_str1, long long arg1,
			    long long arg2, long long arg3, long long arg4,
			    long long arg5, long long arg6);

/*below functions are used for system debug*/

#define REG_VIR_ADDR_MAP(phyAddr)        ioremap(phyAddr, sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr)      iounmap(virAddr)

void easy_shell_test(void)
{
	long long *t;

	t = &dbg_value_for_ecall;
	printk("t = 0x%p\n", t);
}

void reg_dbg_dump(unsigned long long pAddr, unsigned long long size,
		  unsigned long long nodesize)
{
	void __iomem *virAddr;
	unsigned int i;

	if (((nodesize != sizeof(char)) && (nodesize != sizeof(short))
	     && (nodesize != sizeof(int)) && (nodesize != sizeof(long long)))) {
		printk
		    ("dump type should be 1(char),2(short),4(int),8(long long)\n");
		return;
	}

	printk("\n");

	virAddr = ioremap(pAddr, nodesize * size);

	for (i = 0; i < size; i++) {
		if ((i * nodesize) % 32 == 0) {
			printk("\n[%16llx]: ", pAddr + (i * nodesize));
		}

		switch (nodesize) {
		case sizeof(char):
			printk("%02x ", *((unsigned char *)virAddr + i));
			break;
		case sizeof(short):
			printk("%04x ", *((unsigned short *)virAddr + i));
			break;
		case sizeof(int):
			printk("%08x ", *((unsigned int *)virAddr + i));
			break;
		case sizeof(long long):
			printk("%16llx ", *((unsigned long long *)virAddr + i));
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
#ifndef _DRV_LLT_
		address = (unsigned long)kallsyms_lookup_name(func_name);
#endif
		printk("lk_addr (0x%x)%s \n", (unsigned int)address, func_name);
	} else {
		printk("null func\n");
	}
}

unsigned long long phy_write_u32(phys_addr_t phy_addr, unsigned int value)
{
	void *vir_addr = NULL;

	vir_addr = ioremap_wc(phy_addr, sizeof(unsigned long));
	writel(value, vir_addr);
	iounmap(vir_addr);

	return 0;
}

/***********************************************************
 Function: reg_write_u32--write an UINT32 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_uint16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long reg_write_u32(unsigned int pAddr, unsigned int value)
{
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	writel(value, virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);
	return 0;
}

/***********************************************************
 Function: reg_write_u16--write an UINT16 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long reg_write_u16(unsigned int pAddr, unsigned short value)
{
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	writew(value, virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);
	return 0;
}

/***********************************************************
 Function: reg_write_u8--write an UINT8 value to physical memory
 Input:    the  writed address and data
 return:   void
 see also: write_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long reg_write_u8(unsigned int pAddr, unsigned char value)
{
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	writeb(value, virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);
	return 0;
}

unsigned int phy_read_u32(phys_addr_t phy_addr)
{
	unsigned int value = 0;
	void *vir_addr = NULL;

	vir_addr = ioremap_wc(phy_addr, sizeof(unsigned long));
	value = readl(vir_addr);
	iounmap(vir_addr);

	return value;
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
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readl(virAddr);
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
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readw(virAddr);
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
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readb(virAddr);
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
unsigned long long write_u64(unsigned long long pAddr, unsigned long long value)
{
	*(volatile unsigned long long *)(pAddr) = value;
	return 0;
}

/***********************************************************
 Function: write_uint32--write an UINT32 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_uint16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long write_u32(unsigned long long pAddr, unsigned int value)
{
	*(volatile unsigned int *)(pAddr) = value;
	return 0;
}

/***********************************************************
 Function: write_u16--write an UINT16 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_u8
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long write_u16(unsigned long long pAddr, unsigned short value)
{
	*(volatile unsigned short *)(pAddr) = value;
	return 0;
}

/***********************************************************
 Function: write_u8--write an UINT8 value to memory
 Input:    the  writed address and data
 return:   void
 see also: write_u32
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long write_u8(unsigned long long pAddr, unsigned char value)
{
	*(volatile unsigned char *)(pAddr) = value;
	return 0;
}

/***********************************************************
 Function: read_u32 --read an UINT32 value from memory
 Input:    the  read address
 return:   the value
 see also: read_u16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned long long read_u64(unsigned long long pAddr)
{
	unsigned long long value = 0;

	value = *(volatile unsigned long long *)(pAddr);

	return value;
}

/***********************************************************
 Function: read_u32 --read an UINT32 value from memory
 Input:    the  read address
 return:   the value
 see also: read_u16
 History:
 1.    2012.8.20   Creat
************************************************************/
unsigned int read_u32(unsigned long long pAddr)
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
unsigned short read_u16(unsigned long long pAddr)
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
unsigned char read_u8(unsigned long long pAddr)
{
	unsigned char value = 0;

	value = *(volatile unsigned char *)(pAddr);
	return value;
}

static int shell_open(struct tty_struct *tty, struct file *filp)
{
	pr_info("easy shell open\n");
	return 0;
}

static void shell_close(struct tty_struct *tty, struct file *filp)
{
	pr_info("easy shell close\n");
}

static int shell_ioctl(struct tty_struct *tty, unsigned int cmd,
		       unsigned long arg)
{
	p_shell_tty_call_arg call_arg = NULL;
	shell_tty_call_arg temp_call_arg;
	unsigned long len = 1024;
	long long ret;

	printk(KERN_DEBUG "received shell ioctl cmd=0x%02x\n, arg=0x%02lx\n",
	       cmd, arg);

	switch (cmd) {
	case ES_TTY_IOCTL_SIGN:
		return VALID_SIGN(tty);

	case ES_TTY_IOCTL_CALL:
		if (!arg) {
			printk("%s: arg is null\n", __func__);
			return -EFAULT;
		}
		call_arg = (p_shell_tty_call_arg) arg;
		if (!call_arg->func_name) {
			printk("%s: call_arg->func_name is null\n",
			       __FUNCTION__);
			return -EFAULT;
		}
		if (copy_from_user
		    ((void *)&temp_call_arg, (void *)arg,
		     sizeof(shell_tty_call_arg))) {
			printk("%s: copy_from_user fail\n", __func__);
			return -EFAULT;
		}
		temp_call_arg.func_name = kmalloc(len, GFP_KERNEL);
		if (temp_call_arg.func_name == NULL) {
			printk("%s: out of memory\n", __func__);
			return -ENOMEM;
		}
		temp_call_arg.arg_str1 = kmalloc(len, GFP_KERNEL);
		if (temp_call_arg.arg_str1 == NULL) {
			printk("%s: out of memory\n", __func__);
			kfree(temp_call_arg.func_name);
			return -ENOMEM;
		}
		ret =
		    strncpy_from_user(temp_call_arg.func_name,
				      call_arg->func_name, len);
		if (ret >= len) {
			printk("%s: strncpy_from_user fail, too long!\n",
			       __func__);
			kfree(temp_call_arg.func_name);
			kfree(temp_call_arg.arg_str1);
			return -ENAMETOOLONG;
		}
		if (!ret) {
			printk("%s: strncpy_from_user fail, no func_name!\n",
			       __func__);
			kfree(temp_call_arg.func_name);
			kfree(temp_call_arg.arg_str1);
			return -ENOENT;
		}
		if (ret < 0) {
			printk("%s: strncpy_from_user fail, can't copy!\n",
			       __func__);
			kfree(temp_call_arg.func_name);
			kfree(temp_call_arg.arg_str1);
			return ret;
		}
		if (call_arg->arg_str1) {
			ret =
			    strncpy_from_user(temp_call_arg.arg_str1,
					      call_arg->arg_str1, len);
			if (ret >= len) {
				printk
				    ("%s: strncpy_from_user fail, too long!\n",
				     __func__);
				kfree(temp_call_arg.func_name);
				kfree(temp_call_arg.arg_str1);
				return -ENAMETOOLONG;
			}
			if (ret < 0) {
				printk
				    ("%s: strncpy_from_user fail, can't copy!\n",
				     __func__);
				kfree(temp_call_arg.func_name);
				kfree(temp_call_arg.arg_str1);
				return ret;
			}
			if (!ret) {
				kfree(temp_call_arg.arg_str1);
				temp_call_arg.arg_str1 = NULL;
			}
		} else {
			kfree(temp_call_arg.arg_str1);
			temp_call_arg.arg_str1 = NULL;
		}
		call_arg = &temp_call_arg;

		if (call_arg->sign_word & ~VALID_SIGN(tty)) {
			printk("Unallowed call\n");
			kfree(call_arg->func_name);
			return -EPERM;
		}

		ret = shell_call(call_arg->func_name, call_arg->arg_str1,
				 call_arg->arg1,
				 call_arg->arg2,
				 call_arg->arg3,
				 call_arg->arg4,
				 call_arg->arg5, call_arg->arg6);

		kfree(call_arg->func_name);
		return (int)ret;

	default:
		printk("shell_ioctl unknown cmd 0x%x\n", cmd);
		break;
	}

	return -ENOIOCTLCMD;
}

/**
 * shell_compact_ioctl() - for 32bit aligned userspace ecall as the kernel is 64bit aligned
							we make kernel struct the same aligned as userspace
 * @tty: ecall tty struct
 * @cmd: ecall command
 * @arg: ecall parameter
 * Return ecall command exec result.
 */
static long shell_compact_ioctl(struct tty_struct *tty, unsigned int cmd,
				unsigned long arg)
{
	p_shell_tty_call_arg32 call_arg = NULL;
	shell_tty_call_arg32 temp_call_arg;
	char *func_name = NULL;
	unsigned long user_func = 0;
	unsigned long len = 1024;
	long ret;

	printk(KERN_DEBUG "received shell ioctl cmd=0x%02x\n, arg=0x%02lx\n",
	       cmd, arg);

	switch (cmd) {
	case ES_TTY_IOCTL_SIGN:
		return VALID_SIGN(tty);

	case ES_TTY_IOCTL_CALL:
		if (!arg) {
			printk("%s: arg is null\n", __func__);
			return -EFAULT;
		}
		call_arg = (p_shell_tty_call_arg32) arg;
		if (copy_from_user
		    ((void *)&temp_call_arg, (const void __user *)arg,
		     sizeof(shell_tty_call_arg32))) {
			printk("%s: copy_from_user fail\n", __func__);
			return -EFAULT;
		}
		func_name = kmalloc(len, GFP_KERNEL);
		if (func_name == NULL) {
			printk("%s: out of memory\n", __func__);
			return -ENOMEM;
		}
		user_func = (unsigned long)temp_call_arg.func_name;
		user_func = user_func | 0xFFFFFFFF;
		if (!user_func) {
			printk("%s: user_func is null\n", __func__);
			kfree(func_name);
			return -EFAULT;
		}
		ret =
		    strncpy_from_user(func_name, (const char __user *)user_func,
				      len);
		if (ret >= len) {
			kfree(func_name);
			printk("%s: strncpy_from_user fail, too long!\n",
			       __func__);
			return -ENAMETOOLONG;
		}
		if (!ret) {
			kfree(func_name);
			printk("%s: strncpy_from_user fail, no func_name!\n",
			       __func__);
			return -ENOENT;
		}
		if (ret < 0) {
			kfree(func_name);
			printk("%s: strncpy_from_user fail, can't copy!\n",
			       __func__);
			return ret;
		}

		call_arg = &temp_call_arg;

		if (call_arg->sign_word & ~VALID_SIGN(tty)) {
			printk("Unallowed call\n");
			kfree(func_name);
			return -EPERM;
		}
		call_arg->arg_str1 = NULL;
		ret = shell_call(func_name, call_arg->arg_str1,
				 call_arg->arg1,
				 call_arg->arg2,
				 call_arg->arg3,
				 call_arg->arg4,
				 call_arg->arg5, call_arg->arg6);

		kfree(func_name);
		return ret;

	default:
		printk("shell_ioctl unknown cmd 0x%x\n", cmd);
		break;
	}

	return -ENOIOCTLCMD;
}

static const struct tty_operations shell_ops = {
	.open = shell_open,
	.close = shell_close,
	.ioctl = shell_ioctl,
	.compat_ioctl = shell_compact_ioctl,
};

static const struct tty_port_operations shell_port_ops = {
};

static int shell_init(void)
{
	pr_info("Enter ecall init\n");

	shell_tty_drv = alloc_tty_driver(ES_TTY_MINORS);
	if (!shell_tty_drv) {
		printk("Cannot alloc shell tty driver\n");
		return -1;
	}

	shell_tty_drv->owner = THIS_MODULE;
	shell_tty_drv->driver_name = "ecall_serial";
	shell_tty_drv->name = "ecall_tty";
	shell_tty_drv->major = ES_TTY_MAJOR;
	shell_tty_drv->minor_start = 0;
	shell_tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
	shell_tty_drv->subtype = SERIAL_TYPE_NORMAL;
	shell_tty_drv->flags = TTY_DRIVER_REAL_RAW;
	shell_tty_drv->init_termios = tty_std_termios;
	shell_tty_drv->init_termios.c_cflag =
	    B921600 | CS8 | CREAD | HUPCL | CLOCAL;

	tty_set_operations(shell_tty_drv, &shell_ops);
	tty_port_init(&shell_tty_port);
	shell_tty_port.ops = &shell_port_ops;
	tty_port_link_device(&shell_tty_port, shell_tty_drv, 0);

	if (tty_register_driver(shell_tty_drv)) {
		printk("Error registering shell tty driver\n");
		put_tty_driver(shell_tty_drv);
		return -1;
	}

	pr_info("Finish ecall init\n");

	return 0;
}

static long long shell_call(char *func_name, char *arg_str1, long long arg1,
			    long long arg2, long long arg3, long long arg4,
			    long long arg5, long long arg6)
{
	long long result = -1;
	call_ptr address;
	call_ptr_with_str address_with_str;
	unsigned long long addr_variable = 0;

	if (!func_name) {
		goto call_error_input;
	}

	/*view the value of an variable */
	if (DBG_ECALL_VARIABLE == arg1) {
		addr_variable = kallsyms_lookup_name(func_name);
		if (!addr_variable) {
			goto call_no_symbol;
		}

		result = *(long long *)addr_variable;

		printk("variable is %s, addr = 0x%llx, value = 0x%llx\n",
		       func_name, (unsigned long long)addr_variable, result);
	} else {
		printk
		    ("input parameter: arg1=%llx,arg2=%llx,arg3=%llx,arg4=%llx,arg5=%llx,arg6=%llx\n",
		     arg1, arg2, arg3, arg4, arg5, arg6);
		if (arg_str1) {
			printk("arg_str1 = %s\n", arg_str1);
			address_with_str =
			    (call_ptr_with_str) kallsyms_lookup_name(func_name);
			if (!address_with_str) {
				goto call_no_symbol;
			}
			result =
			    address_with_str(arg_str1, arg1, arg2, arg3, arg4,
					     arg5, arg6);
		} else {
			address = (call_ptr) kallsyms_lookup_name(func_name);
			if (!address) {
				goto call_no_symbol;
			}
			result = address(arg1, arg2, arg3, arg4, arg5, arg6);
		}

		printk("Call %s return, value = 0x%lx\n", func_name,
		       (unsigned long)result);
	}
	return result;

call_error_input:
	printk("Error input, value = -1\n");

call_no_symbol:
	printk("Invalid function, value = -1\n");
	return -1;
}

module_init(shell_init)
