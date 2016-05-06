/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"


#define HISI_DSS_LAYERBUF_FREE	"hisi-dss-layerbuf-free"


////////////////////////////////////////////////////////////////////////////////
//
// layerbuffer handle, for offline compose
//
int hisifb_layerbuf_lock_offline(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, struct list_head *plock_list)
{
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	int i = 0;
	int m = 0;
	struct hisifb_layerbuf *node = NULL;
	bool add_tail = false;

	BUG_ON(pov_req == NULL);
	BUG_ON(hisifd == NULL);
	BUG_ON(plock_list == NULL);

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			add_tail = false;

			if (layer->dst_rect.y < pov_h_block->ov_block_rect.y)
				continue;

			if (layer->img.shared_fd < 0)
				continue;

			if ((layer->img.phy_addr == 0) &&
				(layer->img.vir_addr == 0) &&
				(layer->img.afbc_payload_addr == 0)) {
				HISI_FB_ERR("fb%d, layer_idx(%d), chn_idx(%d), no buffer!\n",
					hisifd->index, layer->layer_idx, layer->chn_idx);
				continue;
			}

		#ifdef CONFIG_DSS_MMBUF_FENCE_USED
			if ((layer->img.mmbuf_base > 0) && (layer->img.mmbuf_size > 0)) {
				add_tail = true;
			}
		#endif

			if (add_tail) {
				node = kzalloc(sizeof(struct hisifb_layerbuf), GFP_KERNEL);
				if (node == NULL) {
					HISI_FB_ERR("fb%d, layer_idx(%d), failed to kzalloc!\n", hisifd->index, layer->layer_idx);

				#ifdef CONFIG_DSS_MMBUF_FENCE_USED
					if ((layer->img.mmbuf_base > 0) && (layer->img.mmbuf_size > 0)) {
						hisi_dss_mmbuf_free(hisifd->mmbuf_gen_pool,
							layer->img.mmbuf_base, layer->img.mmbuf_size);
						return -1;
					}
				#endif

					continue;
				}

				node->shared_fd = layer->img.shared_fd;
				node->frame_no = pov_req->frame_no;
				node->ion_handle = NULL;
				node->has_map_iommu = false;
				node->timeline = 0;
				//mmbuf
				node->mmbuf.addr = layer->img.mmbuf_base;
				node->mmbuf.size = layer->img.mmbuf_size;

				list_add_tail(&node->list_node, plock_list);

				if (g_debug_layerbuf_sync) {
					HISI_FB_INFO("fb%d, frame_no=%d, layer_idx(%d), shared_fd=%d, ion_handle=%p, "
						"has_map_iommu=%d, timeline=%d, mmbuf(0x%x, %d).\n",
						hisifd->index, node->frame_no, i, node->shared_fd, node->ion_handle,
						node->has_map_iommu, node->timeline,
						node->mmbuf.addr, node->mmbuf.size);
				}
			}
		}
	}

	return 0;
}

void hisifb_layerbuf_unlock_offline(struct hisi_fb_data_type *hisifd,
	struct list_head *plock_list)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(plock_list == NULL);

	hisifb_layerbuf_unlock(hisifd, plock_list);
}


////////////////////////////////////////////////////////////////////////////////
//
// layerbuffer handle, for online compose
//
int hisifb_layerbuf_lock(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, struct list_head *plock_list)
{
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	int i = 0;
	int m = 0;
	struct hisifb_layerbuf *node = NULL;
	struct ion_handle *ionhnd = NULL;
	struct iommu_map_format iommu_format;
	bool add_tail = false;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON(plock_list == NULL);

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			add_tail = false;
			ionhnd = NULL;

			if (layer->dst_rect.y < pov_h_block->ov_block_rect.y)
				continue;

			if (layer->img.shared_fd < 0)
				continue;

			if ((layer->img.phy_addr == 0) &&
				(layer->img.vir_addr == 0) &&
				(layer->img.afbc_payload_addr == 0)) {
				HISI_FB_ERR("fb%d, layer_idx%d, chn_idx%d, no buffer!\n",
					hisifd->index, layer->layer_idx, layer->chn_idx);
				continue;
			}

			if (layer->img.shared_fd >= 0) {
				ionhnd = ion_import_dma_buf(hisifd->ion_client, layer->img.shared_fd);
				if (IS_ERR(ionhnd)) {
					ionhnd = NULL;
					HISI_FB_ERR("fb%d, layer_idx%d, failed to ion_import_dma_buf, ionclient %p, share_fd %d!\n",
						hisifd->index, i, hisifd->ion_client, layer->img.shared_fd);
				} else {
					if (layer->img.mmu_enable == 1) {
						memset(&iommu_format, 0, sizeof(struct iommu_map_format));
						ion_map_iommu(hisifd->ion_client, ionhnd, &iommu_format);
					}
					add_tail = true;
				}
			}

		#ifdef CONFIG_DSS_MMBUF_FENCE_USED
			if ((layer->img.mmbuf_base > 0) && (layer->img.mmbuf_size > 0)) {
				add_tail = true;
			}
		#endif

			if (add_tail) {
				node = kzalloc(sizeof(struct hisifb_layerbuf), GFP_KERNEL);
				if (node == NULL) {
					HISI_FB_ERR("fb%d, layer_idx%d, failed to kzalloc!\n",
						hisifd->index, layer->layer_idx);

					if (ionhnd) {
						ion_free(hisifd->ion_client, ionhnd);
						ionhnd = NULL;
					}

				#ifdef CONFIG_DSS_MMBUF_FENCE_USED
					if ((layer->img.mmbuf_base > 0) && (layer->img.mmbuf_size > 0)) {
						hisi_dss_mmbuf_free(hisifd->mmbuf_gen_pool,
							layer->img.mmbuf_base, layer->img.mmbuf_size);
						return -1;
					}
				#endif

					continue;
				}

				node->shared_fd = layer->img.shared_fd;
				node->frame_no = pov_req->frame_no;
				node->ion_handle = ionhnd;
				node->has_map_iommu = (ionhnd && (layer->img.mmu_enable == 1)) ? true : false;
				node->timeline = 0;
				//mmbuf
				node->mmbuf.addr = layer->img.mmbuf_base;
				node->mmbuf.size = layer->img.mmbuf_size;

				node->vir_addr = layer->img.vir_addr;
				node->chn_idx = layer->chn_idx;

				list_add_tail(&node->list_node, plock_list);

				if (g_debug_layerbuf_sync) {
					HISI_FB_INFO("fb%d, frame_no=%d, layer_idx(%d), shared_fd=%d, ion_handle=%p, "
						"has_map_iommu=%d, timeline=%d, mmbuf(0x%x, %d).\n",
						hisifd->index, node->frame_no, i, node->shared_fd, node->ion_handle,
						node->has_map_iommu, node->timeline,
						node->mmbuf.addr, node->mmbuf.size);
				}
			}
		}
	}

	return 0;
}

void hisifb_layerbuf_flush(struct hisi_fb_data_type *hisifd,
	struct list_head *plock_list)
{
	struct hisifb_layerbuf *node, *_node_;
	unsigned long flags = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(hisifd->ion_client == NULL);
	BUG_ON(plock_list == NULL);

	spin_lock_irqsave(&(hisifd->buf_sync_ctrl.layerbuf_spinlock), flags);
	hisifd->buf_sync_ctrl.layerbuf_flushed = true;
	list_for_each_entry_safe(node, _node_, plock_list, list_node) {
		list_del(&node->list_node);
		list_add_tail(&node->list_node, &(hisifd->buf_sync_ctrl.layerbuf_list));
	}
	spin_unlock_irqrestore(&(hisifd->buf_sync_ctrl.layerbuf_spinlock), flags);
}

void hisifb_layerbuf_unlock(struct hisi_fb_data_type *hisifd,
	struct list_head *pfree_list)
{
	struct hisifb_layerbuf *node, *_node_;

	BUG_ON(hisifd == NULL);
	BUG_ON(hisifd->ion_client == NULL);
	BUG_ON(hisifd->mmbuf_gen_pool == NULL);
	BUG_ON(pfree_list == NULL);


	list_for_each_entry_safe(node, _node_, pfree_list, list_node) {
		list_del(&node->list_node);

		if (g_debug_layerbuf_sync) {
			HISI_FB_INFO("fb%d, frame_no=%d, share_fd=%d, ion_handle=%p, has_map_iommu=%d, "
				"timeline=%d, mmbuf(0x%x, %d).vir_addr = 0x%llx, chn_idx = %d\n",
				hisifd->index, node->frame_no, node->shared_fd, node->ion_handle, node->has_map_iommu,
				node->timeline, node->mmbuf.addr, node->mmbuf.size, node->vir_addr, node->chn_idx);
		}

	#ifdef CONFIG_DSS_MMBUF_FENCE_USED
		if ((node->mmbuf.addr > 0) && (node->mmbuf.size > 0)) {
			hisi_dss_mmbuf_free(hisifd->mmbuf_gen_pool, node->mmbuf.addr, node->mmbuf.size);
			node->mmbuf.addr = 0;
			node->mmbuf.size= 0;
		}
	#endif

		node->timeline = 0;
		if (node->ion_handle) {
			if (node->has_map_iommu) {
				ion_unmap_iommu(hisifd->ion_client, node->ion_handle);
			}
			ion_free(hisifd->ion_client, node->ion_handle);
		}
		kfree(node);
	}
}

void hisifb_layerbuf_lock_exception(struct hisi_fb_data_type *hisifd,
	struct list_head *plock_list)
{
	unsigned long flags = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(plock_list == NULL);

	spin_lock_irqsave(&(hisifd->buf_sync_ctrl.layerbuf_spinlock), flags);
	hisifd->buf_sync_ctrl.layerbuf_flushed = false;
	spin_unlock_irqrestore(&(hisifd->buf_sync_ctrl.layerbuf_spinlock), flags);

	hisifb_layerbuf_unlock(hisifd, plock_list);
}

static void hisifb_layerbuf_unlock_work(struct work_struct *work)
{
	struct hisifb_buf_sync *pbuf_sync = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	unsigned long flags;
	struct hisifb_layerbuf *node, *_node_;
	struct list_head free_list;

	pbuf_sync = container_of(work, struct hisifb_buf_sync, free_layerbuf_work);
	BUG_ON(pbuf_sync == NULL);
	hisifd = container_of(pbuf_sync, struct hisi_fb_data_type, buf_sync_ctrl);
	BUG_ON(hisifd == NULL);
	BUG_ON(hisifd->ion_client == NULL);

	INIT_LIST_HEAD(&free_list);
	spin_lock_irqsave(&pbuf_sync->layerbuf_spinlock, flags);
	list_for_each_entry_safe(node, _node_, &pbuf_sync->layerbuf_list, list_node) {
		if (node->timeline >= 2) {
			list_del(&node->list_node);
			list_add_tail(&node->list_node, &free_list);
		}
	}
	spin_unlock_irqrestore(&pbuf_sync->layerbuf_spinlock, flags);

	hisifb_layerbuf_unlock(hisifd, &free_list);
}


////////////////////////////////////////////////////////////////////////////////
//
// buf sync fence
//
#ifdef CONFIG_BUF_SYNC_USED
#define BUF_SYNC_TIMEOUT_MSEC	(2 * MSEC_PER_SEC)
#define BUF_SYNC_FENCE_NAME	"hisi-dss-fence"
#define BUF_SYNC_TIMELINE_NAME	"hisi-dss-timeline"


int hisifb_buf_sync_create_fence(struct hisi_fb_data_type *hisifd, unsigned value)
{
	int fd = -1;
	struct sync_fence *fence = NULL;
	struct sync_pt *pt = NULL;

	BUG_ON(hisifd == NULL);

	fd = get_unused_fd();
	if (fd < 0) {
		HISI_FB_ERR("get_unused_fd failed!\n");
		return fd;
	}

	pt = sw_sync_pt_create(hisifd->buf_sync_ctrl.timeline, value);
	if (pt == NULL) {
		return -ENOMEM;
	}

	fence = sync_fence_create(BUF_SYNC_FENCE_NAME, pt);
	if (fence == NULL) {
		sync_pt_free(pt);
		return -ENOMEM;
	}

	sync_fence_install(fence, fd);

	return fd;
}

int hisifb_buf_sync_wait(int fence_fd)
{
	int ret = 0;
	struct sync_fence *fence = NULL;

	fence = sync_fence_fdget(fence_fd);
	if (fence == NULL){
		HISI_FB_ERR("fence_fd=%d, sync_fence_fdget failed!\n", fence_fd);
		return -EINVAL;
	}

	ret = sync_fence_wait(fence, BUF_SYNC_TIMEOUT_MSEC);
	if (ret == -ETIME) {
		HISI_FB_ERR("fence timeout on fence_fd=%d", fence_fd);
		ret = sync_fence_wait(fence, BUF_SYNC_TIMEOUT_MSEC);
		if (ret < 0) {
			HISI_FB_ERR("fence_fd=%d, error waiting on fence: 0x%x\n", fence_fd, ret);
		}
	}
	sync_fence_put(fence);

	return ret;
}

int hisifb_buf_sync_handle_offline(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	dss_wb_layer_t *wb_layer = NULL;
	int i = 0;
	int m = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);

	if (pov_req->wb_enable) {
		for (i = 0; i < pov_req->wb_layer_nums; i++) {
			wb_layer = &(pov_req->wb_layer_infos[i]);

			if (wb_layer->acquire_fence >= 0) {
				hisifb_buf_sync_wait(wb_layer->acquire_fence);
			}
		}
	}

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);

			if (layer->dst_rect.y < pov_h_block->ov_block_rect.y)
				continue;

			if (layer->acquire_fence >= 0) {
				hisifb_buf_sync_wait(layer->acquire_fence);
			}
		}
	}

	return 0;
}

int hisifb_buf_sync_handle(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	int i = 0;
	int m = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);

			if (layer->dst_rect.y < pov_h_block->ov_block_rect.y)
				continue;

			if (layer->acquire_fence >= 0) {
				hisifb_buf_sync_wait(layer->acquire_fence);
			}
		}
	}

	return 0;
}

void hisifb_buf_sync_signal(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_layerbuf *node = NULL;
	struct hisifb_layerbuf *_node_ = NULL;

	BUG_ON(hisifd == NULL);

	//HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	spin_lock(&hisifd->buf_sync_ctrl.refresh_lock);
	if (hisifd->buf_sync_ctrl.refresh) {
		sw_sync_timeline_inc(hisifd->buf_sync_ctrl.timeline, hisifd->buf_sync_ctrl.refresh);
		hisifd->buf_sync_ctrl.refresh = 0;
	}
	spin_unlock(&hisifd->buf_sync_ctrl.refresh_lock);

	spin_lock(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));
	list_for_each_entry_safe(node, _node_, &(hisifd->buf_sync_ctrl.layerbuf_list), list_node) {
		if (hisifd->buf_sync_ctrl.layerbuf_flushed) {
			node->timeline++;
		}
	}
	hisifd->buf_sync_ctrl.layerbuf_flushed = false;
	spin_unlock(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));

	queue_work(hisifd->buf_sync_ctrl.free_layerbuf_queue, &(hisifd->buf_sync_ctrl.free_layerbuf_work));

	//HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}

void hisifb_buf_sync_suspend(struct hisi_fb_data_type *hisifd)
{
	unsigned long flags;

	spin_lock_irqsave(&hisifd->buf_sync_ctrl.refresh_lock,flags);
	sw_sync_timeline_inc(hisifd->buf_sync_ctrl.timeline, hisifd->buf_sync_ctrl.refresh + 1);
	hisifd->buf_sync_ctrl.refresh = 0;
	hisifd->buf_sync_ctrl.timeline_max++;
	spin_unlock_irqrestore(&hisifd->buf_sync_ctrl.refresh_lock,flags);
}

void hisifb_buf_sync_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	spin_lock_init(&hisifd->buf_sync_ctrl.refresh_lock);
	hisifd->buf_sync_ctrl.refresh = 0;
	hisifd->buf_sync_ctrl.timeline_max = 1;
	hisifd->buf_sync_ctrl.timeline =
		sw_sync_timeline_create(BUF_SYNC_TIMELINE_NAME);
	if (hisifd->buf_sync_ctrl.timeline == NULL) {
		HISI_FB_ERR("cannot create time line!");
		return ; /* -ENOMEM */
	}

	// handle free layerbuf
	spin_lock_init(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));
	INIT_LIST_HEAD(&(hisifd->buf_sync_ctrl.layerbuf_list));
	hisifd->buf_sync_ctrl.layerbuf_flushed = false;

	INIT_WORK(&(hisifd->buf_sync_ctrl.free_layerbuf_work), hisifb_layerbuf_unlock_work);
	hisifd->buf_sync_ctrl.free_layerbuf_queue = create_singlethread_workqueue(HISI_DSS_LAYERBUF_FREE);
	if (!hisifd->buf_sync_ctrl.free_layerbuf_queue) {
		HISI_FB_ERR("failed to create free_layerbuf_queue!\n");
		return ;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}

void hisifb_buf_sync_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->buf_sync_ctrl.timeline) {
		sync_timeline_destroy((struct sync_timeline *)hisifd->buf_sync_ctrl.timeline);
		hisifd->buf_sync_ctrl.timeline = NULL;
	}

	if (hisifd->buf_sync_ctrl.free_layerbuf_queue) {
		destroy_workqueue(hisifd->buf_sync_ctrl.free_layerbuf_queue);
		hisifd->buf_sync_ctrl.free_layerbuf_queue = NULL;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}
#else
int hisifb_buf_sync_wait(int fence_fd)
{
	return 0;
}

int hisifb_buf_sync_handle_offline(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	return 0;
}

int hisifb_buf_sync_handle(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	return 0;
}

void hisifb_buf_sync_signal(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_layerbuf *node = NULL;
	struct hisifb_layerbuf *_node_ = NULL;

	BUG_ON(hisifd == NULL);

	//HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	spin_lock(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));
	list_for_each_entry_safe(node, _node_, &(hisifd->buf_sync_ctrl.layerbuf_list), list_node) {
		if (hisifd->buf_sync_ctrl.layerbuf_flushed) {
			node->timeline++;
		}
	}
	hisifd->buf_sync_ctrl.layerbuf_flushed = false;
	spin_unlock(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));

	queue_work(hisifd->buf_sync_ctrl.free_layerbuf_queue, &(hisifd->buf_sync_ctrl.free_layerbuf_work));

	//HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}

void hisifb_buf_sync_suspend(struct hisi_fb_data_type *hisifd)
{
}

void hisifb_buf_sync_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// handle free layerbuf
	spin_lock_init(&(hisifd->buf_sync_ctrl.layerbuf_spinlock));
	INIT_LIST_HEAD(&(hisifd->buf_sync_ctrl.layerbuf_list));
	hisifd->buf_sync_ctrl.layerbuf_flushed = false;

	INIT_WORK(&(hisifd->buf_sync_ctrl.free_layerbuf_work), hisifb_layerbuf_unlock_work);
	hisifd->buf_sync_ctrl.free_layerbuf_queue = create_singlethread_workqueue(HISI_DSS_LAYERBUF_FREE);
	if (!hisifd->buf_sync_ctrl.free_layerbuf_queue) {
		HISI_FB_ERR("failed to create free_layerbuf_queue!\n");
		return ;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}

void hisifb_buf_sync_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->buf_sync_ctrl.free_layerbuf_queue) {
		destroy_workqueue(hisifd->buf_sync_ctrl.free_layerbuf_queue);
		hisifd->buf_sync_ctrl.free_layerbuf_queue = NULL;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
}
#endif
