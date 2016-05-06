#include <linux/types.h>
#include <linux/errno.h>
#include <linux/console.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/irq_work.h>
#include <linux/cpu.h>

DECLARE_WAIT_QUEUE_HEAD(boot_log_wait);

#define BOOT_LOG_PENDING_WAKEUP   0x01
#define __BOOT_LOG_BUF_LEN  (1 << 19)

static char boot_log_buf[__BOOT_LOG_BUF_LEN];
static int boot_log_buf_len = __BOOT_LOG_BUF_LEN;

static u32 boot_log_write_idx;
static u32 boot_log_read_idx;

static DEFINE_PER_CPU(int, boot_log_pending);

static void wake_up_boot_log_work_func(struct irq_work *irq_work)
{
    int pending = __this_cpu_xchg(boot_log_pending, 0);

    if (pending & BOOT_LOG_PENDING_WAKEUP)
        wake_up_interruptible(&boot_log_wait);
}

static DEFINE_PER_CPU(struct irq_work, wake_up_boot_log_work) = {
    .func = wake_up_boot_log_work_func,
    .flags = IRQ_WORK_LAZY,
};

void wake_up_boot_log(void)
{
    preempt_disable();
    if (waitqueue_active(&boot_log_wait)) {
        this_cpu_or(boot_log_pending, BOOT_LOG_PENDING_WAKEUP);
        irq_work_queue(&__get_cpu_var(wake_up_boot_log_work));
    }
    preempt_enable();
}

/*
 * boot_log_lock just protects "boot_log_info" during
 * calls to _boot_log_register()
 */
static DEFINE_RAW_SPINLOCK(boot_log_lock);

static void boot_log_console_write(struct console *con, const char *msg, u32 len)
{
    u32 cnt, left_size;
    unsigned long flags;
    if (oops_in_progress) {
        if (!raw_spin_trylock_irqsave(&boot_log_lock, flags))
            return;
    } else {
       raw_spin_lock_irqsave(&boot_log_lock, flags);
    }


    /*return if buff was full*/
    if (boot_log_buf_len == boot_log_write_idx) {
        raw_spin_unlock_irqrestore(&boot_log_lock, flags);
        return;
    }

    left_size = boot_log_buf_len - boot_log_write_idx;
    cnt = len > left_size ? left_size : len;
    memcpy(boot_log_buf + boot_log_write_idx, msg, cnt);
    boot_log_write_idx += cnt;
    raw_spin_unlock_irqrestore(&boot_log_lock, flags);

    wake_up_boot_log();
}

int boot_log_console_read(char __user *buff, u32 size)
{
    int error;
    u32 left_size = 0;
    u32 read_len;
    u32 uncpy_len = 0;
    unsigned long flags;

    if (boot_log_read_idx == boot_log_buf_len) {
        boot_log_read_idx = 0;
        return -ENOSPC;
    }

    if (!buff || size < 0) {
        return -EINVAL;
    }
    if (!size) {
        return 0;
    }
    if (!access_ok(VERIFY_WRITE, buff, size)) {
        return -EFAULT;
    }
    error = wait_event_interruptible(boot_log_wait,
                boot_log_write_idx != boot_log_read_idx);
    if (error) {
        return error;
    }
    raw_spin_lock_irqsave(&boot_log_lock, flags);
    left_size = boot_log_write_idx - boot_log_read_idx;
    read_len = size > left_size ? left_size : size;
    if ((uncpy_len = copy_to_user(buff, boot_log_buf + boot_log_read_idx, read_len)) != 0) {
        if (!read_len) {
            read_len = -EFAULT;
        } else {
            boot_log_read_idx += read_len - uncpy_len;
        }
    } else {
        boot_log_read_idx += read_len;
    }
    raw_spin_unlock_irqrestore(&boot_log_lock, flags);
    return read_len;
}

static struct console boot_log_console = {
    .name   = "boot_log",
    .write  = boot_log_console_write,
    .flags  = CON_PRINTBUFFER | CON_ENABLED | CON_ANYTIME,
    .index  = -1,
};

static void boot_log_register_console(void)
{
    register_console(&boot_log_console);
}


int boot_log_register(void)
{
    boot_log_register_console();
    return 0;
}

