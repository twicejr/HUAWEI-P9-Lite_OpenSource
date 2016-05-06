#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/cred.h>
#include <linux/mm.h>
#include <linux/utsname.h>
#include <linux/mman.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/prctl.h>
#include <linux/highuid.h>
#include <linux/fs.h>
#include <linux/perf_event.h>
#include <linux/resource.h>
#include <linux/kernel.h>
#include <linux/kexec.h>
#include <linux/capability.h>
#include <linux/device.h>
#include <linux/key.h>
#include <linux/times.h>
#include <linux/posix-timers.h>
#include <linux/security.h>
#include <linux/suspend.h>
#include <linux/tty.h>
#include <linux/signal.h>
#include <linux/cn_proc.h>
#include <linux/getcpu.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/seccomp.h>
#include <linux/cpu.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/fs_struct.h>
#include <linux/gfp.h>
#include <linux/syscore_ops.h>
#include <linux/version.h>
#include <linux/ctype.h>

#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/user_namespace.h>

#include <linux/kmsg_dump.h>
#include <generated/utsrelease.h>

#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/unistd.h>

#include <check_root.h>

#define ANDROID_THIRD_PART_APK_UID 10000
#define AID_SHELL		   2000

/* uncomment this for force stop setXid */
// #define CONFIG_CHECKROOT_FORCE_STOP

struct checkroot_ref_cnt checkroot_ref;

static int checkroot_risk_id(int curr_id, int flag)
{
	const struct cred *now;
	now = current_cred();

	if (curr_id <= ANDROID_THIRD_PART_APK_UID && curr_id != AID_SHELL) {
		return 0;
	}
	printk(KERN_EMERG "check_root: Uid %d, Gid %d, try to Privilege Escalate\n",
			now->uid, now->gid);

#ifdef DCHECK_ROOT_FORCE    
	check_setuid(flag);
#endif

#ifdef CONFIG_CHECKROOT_FORCE_STOP
	return 1;
#else
	if (flag & CHECKROOT_SETUID_FLAG) {
		checkroot_ref.setuid++;
	}
	if (flag & CHECKROOT_SETGID_FLAG) {
		checkroot_ref.setgid++;
	}
	if (flag & CHECKROOT_SETRESUID_FLAG) {
		checkroot_ref.setresuid++;
	}
	if (flag & CHECKROOT_SETRESGID_FLAG) {
		checkroot_ref.setresgid++;
	}
	return 0;
#endif
}

int checkroot_setuid(uid_t uid)
{
	return checkroot_risk_id((int)uid, CHECKROOT_SETUID_FLAG);
}

int checkroot_setgid(gid_t gid)
{
	return checkroot_risk_id((int)gid, CHECKROOT_SETGID_FLAG);
}

int checkroot_setresuid(uid_t uid)
{
	return checkroot_risk_id((int)uid, CHECKROOT_SETRESUID_FLAG);
}

int checkroot_setresgid(gid_t gid)
{
	return checkroot_risk_id((int)gid, CHECKROOT_SETRESGID_FLAG);
}

static int checkroot_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "setuid %d\nsetgid %d\nsetresuid %d\nsetresgid %d\nrt_status %d\n",
			checkroot_ref.setuid, checkroot_ref.setgid,
			checkroot_ref.setresuid, checkroot_ref.setresgid, 
			checkroot_ref.drt_status);

	return 0;
}

static int checkroot_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, checkroot_proc_show, NULL);
}

static const struct file_operations checkroot_proc_fops = {
	.open		= checkroot_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_checkroot_init(void)
{
	memset(&checkroot_ref, 0, sizeof(checkroot_ref));
	proc_create("check_root", 0, NULL, &checkroot_proc_fops);

	return 0;
}
module_init(proc_checkroot_init);
