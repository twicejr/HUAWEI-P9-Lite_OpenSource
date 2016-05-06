

#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>
#include <linux/exportfs.h>
#include <linux/vfs.h>
#include <linux/random.h>
#include <linux/mount.h>
#include <linux/quotaops.h>
#include <linux/ctype.h>
#include <linux/cleancache.h>
#include <linux/rtc.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/freezer.h>

#include "ext4.h"
#include "ext4_dump_info.h"

#define DUMP_EXT4_BUFF 1024

struct feature {
	unsigned int	mask;
	const char	*string;
};

static struct feature feature_compat_list[] = {
	{EXT4_FEATURE_COMPAT_DIR_PREALLOC, "dir_prealloc " },
	{EXT4_FEATURE_COMPAT_HAS_JOURNAL, "has_journal " },
	{EXT4_FEATURE_COMPAT_IMAGIC_INODES, "imagic_inodes " },
	{EXT4_FEATURE_COMPAT_EXT_ATTR, "ext_attr " },
	{EXT4_FEATURE_COMPAT_DIR_INDEX, "dir_index " },
	{EXT4_FEATURE_COMPAT_RESIZE_INODE, "resize_inode " },
	{0, 0},
};

static struct feature feature_ro_compat_list[] = {
	{EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER, "sparse_super " },
	{EXT4_FEATURE_RO_COMPAT_LARGE_FILE, "large_file " },
	{EXT4_FEATURE_RO_COMPAT_HUGE_FILE, "huge_file " },
	{EXT4_FEATURE_RO_COMPAT_GDT_CSUM, "gdt_csum " },
	{EXT4_FEATURE_RO_COMPAT_DIR_NLINK, "dir_nlink " },
	{EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE, "extra_isize " },
	{0, 0},
};

static struct feature feature_incompat_list[] = {
	{EXT4_FEATURE_INCOMPAT_COMPRESSION, "compression " },
	{EXT4_FEATURE_INCOMPAT_FILETYPE, "filetype " },
	{EXT4_FEATURE_INCOMPAT_RECOVER, "needs_recovery " },
	{EXT4_FEATURE_INCOMPAT_JOURNAL_DEV, "journal_dev " },
	{EXT4_FEATURE_INCOMPAT_EXTENTS, "extent " },
	{EXT4_FEATURE_INCOMPAT_META_BG, "meta_bg " },
	{EXT4_FEATURE_INCOMPAT_64BIT, "64bit " },
	{EXT4_FEATURE_INCOMPAT_FLEX_BG, "flex_bg "},
	{0, 0},
};

static void ext4_dump_time(char *str, __le32 time)
{
	struct rtc_time tm;
	u32 t = le32_to_cpu(time);

	if (t) {
		rtc_time_to_tm(t, &tm);
		printk(KERN_CRIT "%s%d-%02d-%02d %02d:%02d:%02d UTC (%u)\n", str,
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec,
				(unsigned int)t);
	} else {
		printk(KERN_CRIT "%sn/a\n", str);
	}

}

static int add_to_buf(char *buf, size_t len, const char *str)
{
	size_t l;

	l = strlen(buf);

	if (l >= (len - 1)) {
		return -1;
	}
	strncpy(buf + l, str, len - l - 1);

	return 0;
}

/* print the ext4 superblock infomation to the kernel message,
 * it will be saved by DMD or panic log
 * simplified info of e2fsprogs tool: dumpe2fs
 * ext4 superblock struct locate in fs/ext4/ext4.h
 */
void dump_ext4_sb_info(struct super_block *sb)
{
	int inode_blocks_per_group;
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;
	struct feature *f;
	char buf[DUMP_EXT4_BUFF];
	char *str;

	if (es->s_volume_name[0]) {
		printk(KERN_CRIT "Filesystem volume name:   %s\n", es->s_volume_name);
	} else {
		printk(KERN_CRIT "Filesystem volume name:   <none>\n");
	}

	if (es->s_last_mounted[0]) {
		printk(KERN_CRIT "Last mounted on:          %s\n", es->s_last_mounted);
	} else {
		printk(KERN_CRIT "Last mounted on:          <not available>\n");
	}

	printk(KERN_CRIT "Filesystem magic number:  0x%04X\n", es->s_magic);

	///////////////////////////
	if (es->s_rev_level == EXT4_GOOD_OLD_REV) {
		str = "(original)";
	} else if (es->s_rev_level == EXT4_DYNAMIC_REV) {
		str = "(dynamic)";
	} else {
		str = "(unknown)";
	}
	snprintf(buf, DUMP_EXT4_BUFF, "Filesystem revision #:    %d %s", es->s_rev_level, str);
	printk(KERN_CRIT "%s\n", buf);

	///////////////////////////
	snprintf(buf, DUMP_EXT4_BUFF, "Filesystem features:      ");

	for (f = feature_compat_list; f->string; f++) {
		if (EXT4_HAS_COMPAT_FEATURE(sb, f->mask))
			add_to_buf(buf, DUMP_EXT4_BUFF, f->string);
	}

	for (f = feature_ro_compat_list; f->string; f++) {
		if (EXT4_HAS_RO_COMPAT_FEATURE(sb, f->mask)) {
			add_to_buf(buf, DUMP_EXT4_BUFF, f->string);
		}
	}

	for (f = feature_incompat_list; f->string; f++) {
		if (EXT4_HAS_INCOMPAT_FEATURE(sb, f->mask)) {
			add_to_buf(buf, DUMP_EXT4_BUFF, f->string);
		}
	}
	printk(KERN_CRIT "%s\n", buf);

	///////////////////////////
	if (es->s_flags) {
		snprintf(buf, DUMP_EXT4_BUFF, "Filesystem flags:         ");
		if (es->s_flags & EXT2_FLAGS_SIGNED_HASH)
			add_to_buf(buf, DUMP_EXT4_BUFF, "signed_directory_hash ");
		if (es->s_flags & EXT2_FLAGS_UNSIGNED_HASH)
			add_to_buf(buf, DUMP_EXT4_BUFF, "unsigned_directory_hash ");
		if (es->s_flags & EXT2_FLAGS_TEST_FILESYS)
			add_to_buf(buf, DUMP_EXT4_BUFF, "test_filesystem ");
		printk(KERN_CRIT "%s\n", buf);
	}

	///////////////////////////
	snprintf(buf, DUMP_EXT4_BUFF, "Filesystem state:        ");
	if (is_ext4_fs_dirty(sb)) {
		add_to_buf(buf, DUMP_EXT4_BUFF, " (Errors detected)");
	} else {
		add_to_buf(buf, DUMP_EXT4_BUFF, " (Unmounted cleanly)");
	}
	if (es->s_state & EXT4_ORPHAN_FS)
		add_to_buf(buf, DUMP_EXT4_BUFF, " (Orphans being recovered)");
	printk(KERN_CRIT "%s\n", buf);

	///////////////////////////
	snprintf(buf, DUMP_EXT4_BUFF, "Errors behavior:          ");
	switch (es->s_errors) {
		case EXT4_ERRORS_CONTINUE:
			add_to_buf(buf, DUMP_EXT4_BUFF, "Continue");
			break;
		case EXT4_ERRORS_RO:
			add_to_buf(buf, DUMP_EXT4_BUFF, "Remount read-only");
			break;
		case EXT4_ERRORS_PANIC:
			add_to_buf(buf, DUMP_EXT4_BUFF, "Panic");
			break;
		default:
			add_to_buf(buf, DUMP_EXT4_BUFF, "Unknown");
	}
	printk(KERN_CRIT "%s\n", buf);

	///////////////////////////
	printk(KERN_CRIT "Inode count:              %u\n", es->s_inodes_count);
	printk(KERN_CRIT "Block count:              %u\n", es->s_blocks_count_lo);
	printk(KERN_CRIT "Reserved block count:     %u\n", es->s_r_blocks_count_lo);
	printk(KERN_CRIT "Free blocks:              %u\n", es->s_free_blocks_count_lo);
	printk(KERN_CRIT "Free inodes:              %u\n", es->s_free_inodes_count);
	printk(KERN_CRIT "First block:              %u\n", es->s_first_data_block);
	printk(KERN_CRIT "Block size:               %lu\n", EXT4_BLOCK_SIZE(sb));
	printk(KERN_CRIT "Fragment size:            %u\n", es->s_log_cluster_size);

	if (es->s_reserved_gdt_blocks)
		printk(KERN_CRIT "Reserved GDT blocks:      %u\n", es->s_reserved_gdt_blocks);

	printk(KERN_CRIT "Blocks per group:         %u\n", es->s_blocks_per_group);
	printk(KERN_CRIT "Fragments per group:      %u\n", es->s_clusters_per_group);
	printk(KERN_CRIT "Inodes per group:         %u\n", es->s_inodes_per_group);

	inode_blocks_per_group = (((es->s_inodes_per_group *
					EXT4_INODE_SIZE(sb)) +
				EXT4_BLOCK_SIZE(sb) - 1) /
			EXT4_BLOCK_SIZE(sb));
	printk(KERN_CRIT "Inode blocks per group:   %u\n", inode_blocks_per_group);

	if (es->s_raid_stride)
		printk(KERN_CRIT "RAID stride:              %u\n",
				es->s_raid_stride);
	if (es->s_raid_stripe_width)
		printk(KERN_CRIT "RAID stripe width:        %u\n",
				es->s_raid_stripe_width);
	if (es->s_first_meta_bg)
		printk(KERN_CRIT "First meta block group:   %u\n",
				es->s_first_meta_bg);
	if (es->s_log_groups_per_flex)
		printk(KERN_CRIT "Flex block group size:    %u\n",
				1 << es->s_log_groups_per_flex);
	if (es->s_mkfs_time)
		ext4_dump_time("Filesystem created:       ", es->s_mkfs_time);

	ext4_dump_time("Last mount time:          ", es->s_mtime);
	ext4_dump_time("Last write time:          ", es->s_wtime);
	ext4_dump_time("Last check time:          ", es->s_lastcheck);

	printk(KERN_CRIT "Mount count:              %u\n", es->s_mnt_count);
	printk(KERN_CRIT "Maximum mount count:      %d\n", es->s_max_mnt_count);

	if (es->s_rev_level >= EXT4_DYNAMIC_REV) {
		printk(KERN_CRIT "First inode:              %d\n", es->s_first_ino);
		printk(KERN_CRIT "Inode size:	              %d\n", es->s_inode_size);
		if (es->s_min_extra_isize)
			printk(KERN_CRIT "Required extra isize:     %d\n",
				es->s_min_extra_isize);
		if (es->s_want_extra_isize)
			printk(KERN_CRIT "Desired extra isize:      %d\n",
				es->s_want_extra_isize);
	}

	if (es->s_journal_inum)
		printk(KERN_CRIT "Journal inode:            %u\n", es->s_journal_inum);
	if (es->s_journal_dev)
		printk(KERN_CRIT "Journal device:	          0x%04x\n", es->s_journal_dev);
	if (es->s_last_orphan)
		printk(KERN_CRIT "First orphan inode:       %u\n", es->s_last_orphan);

	///////////////////////////
	if (es->s_jnl_backup_type) {
		if (es->s_jnl_backup_type == 1) {
			printk(KERN_CRIT "Journal backup:           inode blocks\n");
		} else {
			printk(KERN_CRIT "Journal backup:           type %u\n", es->s_jnl_backup_type);
		}
	}
	///////////////////////////

	if (es->s_error_count)
		printk(KERN_CRIT "FS Error count:           %u\n", es->s_error_count);
	if (es->s_first_error_time) {
		ext4_dump_time("First error time:         ", es->s_first_error_time);
		printk(KERN_CRIT "First error function:     %s\n", es->s_first_error_func);
		printk(KERN_CRIT "First error line #:       %u\n", es->s_first_error_line);
		printk(KERN_CRIT "First error inode #:      %u\n", es->s_first_error_ino);
		printk(KERN_CRIT "First error block #:      %llu\n", es->s_first_error_block);
	}

	if (es->s_last_error_time) {
		ext4_dump_time("Last error time:          ", es->s_last_error_time);
		printk(KERN_CRIT "Last error function:      %s\n", es->s_last_error_func);
		printk(KERN_CRIT "Last error line #:        %u\n", es->s_last_error_line);
		printk(KERN_CRIT "Last error inode #:       %u\n", es->s_last_error_ino);
		printk(KERN_CRIT "Last error block #:       %llu\n", es->s_last_error_block);
	}
}

