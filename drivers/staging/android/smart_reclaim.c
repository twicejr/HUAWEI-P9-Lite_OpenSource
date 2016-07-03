/*
 * drivers/staging/android/smart_reclaim.c
 *
 * Copyright (C) huawei company
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/slab.h>

/* User knob to show soft reclaim feature */
static char *soft_reclaim = ".apk .dex .jar .odex";
module_param_named(soft_reclaim, soft_reclaim, charp, S_IRUGO);

/* Below function is same as "madvise_dontneed() in mm/advise.c */
static long sshrinker_madvise_dontneed(struct vm_area_struct * vma,
			     unsigned long start, unsigned long end)
{
	if (vma->vm_flags & (VM_LOCKED|VM_HUGETLB|VM_PFNMAP)) {
		return -EINVAL;
	}
	if (unlikely(vma->vm_flags & VM_NONLINEAR)) {
		struct zap_details details = {
			.nonlinear_vma = vma,
			.last_index = ULONG_MAX,
		};
		zap_page_range(vma, start, end - start, &details);
	} else {
		zap_page_range(vma, start, end - start, NULL);
	}
	return 0;
}

const char *get_path_ext(const char *path) {
	const char *dot = NULL;
	if (path == NULL) {
		return NULL;
	}
	dot = strrchr(path, '.');
	if (!dot || dot == path) {
		return NULL;
	}
	return dot + 1;
}

static bool is_soft_vma(struct vm_area_struct *vma) {
	char *path;
	const char* suffix;
	bool ret = false;
	if (!vma->vm_file) {
		goto out;
	}
	if (vma->anon_vma) {
		/*
		 * For some readonly or rw vma, a file mapping that has
		 * had some COW done. Since pages might have been
		 * written, if free, the data will loss
		*/
		goto out;
	}
	path = vma->vm_file->f_path.dentry->d_name.name;
	//see the path is soft_reclaim
	suffix = get_path_ext(path);
	if (suffix != NULL && strstr(soft_reclaim, suffix)) {
		//printk("need to reclaim vma path=%s\n", path);
		ret = true;
	}
out:
	return ret;
}

void smart_soft_shrink(struct mm_struct *mm)
{
	struct vm_area_struct *vma;

	down_read(&mm->mmap_sem);
	for (vma = mm->mmap ; vma; vma = vma->vm_next) {
		if (is_soft_vma(vma)) {
			sshrinker_madvise_dontneed(vma, vma->vm_start , vma->vm_end);
		}
	}
	up_read(&mm->mmap_sem);
}

static int __init smart_reclaim_init(void)
{
	return 0;
}

static void __exit smart_reclaim_exit(void)
{
	return;
}

module_init(smart_reclaim_init);
module_exit(smart_reclaim_exit);

MODULE_LICENSE("GPL");