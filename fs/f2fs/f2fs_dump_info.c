

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/statfs.h>
#include <linux/buffer_head.h>
#include <linux/backing-dev.h>
#include <linux/kthread.h>
#include <linux/parser.h>
#include <linux/mount.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/random.h>
#include <linux/exportfs.h>
#include <linux/blkdev.h>
#include <linux/f2fs_fs.h>
#include <linux/sysfs.h>

#include "f2fs.h"

/* Display on console */
#define DISP(fmt, ptr, member)				\
	do {						\
		printk("F2FS-fs:%-30s\t\t" fmt, #member, ((ptr)->member));	\
	} while (0)

#define DISP_u32(ptr, member)						\
	do {								\
		printk("F2FS-fs:%-30s" "\t\t[0x%8x : %u]\n",		\
			#member, ((ptr)->member), ((ptr)->member));	\
	} while (0)

#define DISP_u64(ptr, member)						\
	do {								\
		printk("F2FS-fs:%-30s" "\t\t[0x%8llx : %llu]\n",		\
			#member, ((ptr)->member), ((ptr)->member));	\
	} while (0)


/* print the f2fs superblock infomation to the kernel message,
 * it will be saved by DMD or panic log
 * simplified info of f2fs tool: fsck.f2fs
 * f2fs superblock struct locate in kernel/include/linux/f2fs_fs.h
 */
void f2fs_print_raw_sb_info(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *sb = NULL;

	if (sbi == NULL) {
		return;
	}

	sb = F2FS_RAW_SUPER(sbi);

	if (sb == NULL) {
		return;
	}

	printk("\n");
	printk("+--------------------------------------------------------+\n");
	printk("| Super block                                            |\n");
	printk("+--------------------------------------------------------+\n");

	DISP_u32(sb, magic);
	DISP_u32(sb, major_ver);
	DISP_u32(sb, minor_ver);
	DISP_u32(sb, log_sectorsize);
	DISP_u32(sb, log_sectors_per_block);

	DISP_u32(sb, log_blocksize);
	DISP_u32(sb, log_blocks_per_seg);
	DISP_u32(sb, segs_per_sec);
	DISP_u32(sb, secs_per_zone);
	DISP_u32(sb, checksum_offset);
	DISP_u64(sb, block_count);

	DISP_u32(sb, section_count);
	DISP_u32(sb, segment_count);
	DISP_u32(sb, segment_count_ckpt);
	DISP_u32(sb, segment_count_sit);
	DISP_u32(sb, segment_count_nat);

	DISP_u32(sb, segment_count_ssa);
	DISP_u32(sb, segment_count_main);
	DISP_u32(sb, segment0_blkaddr);

	DISP_u32(sb, cp_blkaddr);
	DISP_u32(sb, sit_blkaddr);
	DISP_u32(sb, nat_blkaddr);
	DISP_u32(sb, ssa_blkaddr);
	DISP_u32(sb, main_blkaddr);

	DISP_u32(sb, root_ino);
	DISP_u32(sb, node_ino);
	DISP_u32(sb, meta_ino);
	DISP_u32(sb, cp_payload);
	DISP_u32(sb, feature);
	DISP("%s", sb, version);
	printk("\n\n");
}

void f2fs_print_ckpt_info(struct f2fs_sb_info *sbi)
{
	struct f2fs_checkpoint *cp = NULL;

	if (sbi == NULL) {
		return;
	}

	cp = F2FS_CKPT(sbi);

	if (cp == NULL) {
		return;
	}

	printk("\n");
	printk("+--------------------------------------------------------+\n");
	printk("| Checkpoint                                             |\n");
	printk("+--------------------------------------------------------+\n");

	DISP_u64(cp, checkpoint_ver);
	DISP_u64(cp, user_block_count);
	DISP_u64(cp, valid_block_count);
	DISP_u32(cp, rsvd_segment_count);
	DISP_u32(cp, overprov_segment_count);
	DISP_u32(cp, free_segment_count);

	DISP_u32(cp, alloc_type[CURSEG_HOT_NODE]);
	DISP_u32(cp, alloc_type[CURSEG_WARM_NODE]);
	DISP_u32(cp, alloc_type[CURSEG_COLD_NODE]);
	DISP_u32(cp, cur_node_segno[0]);
	DISP_u32(cp, cur_node_segno[1]);
	DISP_u32(cp, cur_node_segno[2]);

	DISP_u32(cp, cur_node_blkoff[0]);
	DISP_u32(cp, cur_node_blkoff[1]);
	DISP_u32(cp, cur_node_blkoff[2]);


	DISP_u32(cp, alloc_type[CURSEG_HOT_DATA]);
	DISP_u32(cp, alloc_type[CURSEG_WARM_DATA]);
	DISP_u32(cp, alloc_type[CURSEG_COLD_DATA]);
	DISP_u32(cp, cur_data_segno[0]);
	DISP_u32(cp, cur_data_segno[1]);
	DISP_u32(cp, cur_data_segno[2]);

	DISP_u32(cp, cur_data_blkoff[0]);
	DISP_u32(cp, cur_data_blkoff[1]);
	DISP_u32(cp, cur_data_blkoff[2]);

	DISP_u32(cp, ckpt_flags);
	DISP_u32(cp, cp_pack_total_block_count);
	DISP_u32(cp, cp_pack_start_sum);
	DISP_u32(cp, valid_node_count);
	DISP_u32(cp, valid_inode_count);
	DISP_u32(cp, next_free_nid);
	DISP_u32(cp, sit_ver_bitmap_bytesize);
	DISP_u32(cp, nat_ver_bitmap_bytesize);
	DISP_u32(cp, checksum_offset);
	DISP_u64(cp, elapsed_time);

	DISP_u32(cp, sit_nat_version_bitmap[0]);
	printk("\n\n");
}

