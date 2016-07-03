static size_t ion_client_total(struct ion_client *client)
{
	size_t size = 0;
	struct rb_node *n;

	mutex_lock(&client->lock);
	for (n = rb_first(&client->handles); n; n = rb_next(n)) {
		struct ion_handle *handle = rb_entry(n,
				struct ion_handle, node);
		if (!(handle->import) && (handle->buffer->heap->type !=
					ION_HEAP_TYPE_CARVEOUT)) {
			if (handle->buffer->cpudraw_sg_table)
				size += handle->buffer->cpu_buffer_size;
			else
				size += handle->buffer->size;
		}
	}
	mutex_unlock(&client->lock);
	return size;
}

int hisi_ion_memory_info(bool verbose)
{
	struct rb_node *n;
	struct ion_device *dev = get_ion_device();

	if (!dev)
		return -1;
	pr_info("ion total size:%d\n", atomic_long_read(&ion_total_size));
	if (!verbose)
		return 0;
	down_read(&dev->lock);
	for (n = rb_first(&dev->clients); n; n = rb_next(n)) {
		struct ion_client *client = rb_entry(n,
				struct ion_client, node);
		size_t size = ion_client_total(client);

		if (!size)
			continue;
		if (client->task) {
			char task_comm[TASK_COMM_LEN];

			get_task_comm(task_comm, client->task);
			pr_info("%16.s %16u %16zu\n",
				task_comm, client->pid, size);
		} else {
			pr_info("%16.s %16u %16zu\n",
				client->name, client->pid, size);
		}
	}
	up_read(&dev->lock);
	mutex_lock(&dev->buffer_lock);
	for (n = rb_first(&dev->buffers); n; n = rb_next(n)) {
		struct ion_buffer *buffer = rb_entry(n, struct ion_buffer,
				node);

		if (!buffer->handle_count &&
			(buffer->heap->type != ION_HEAP_TYPE_CARVEOUT))
			pr_info("%16.s %16u %16zu\n", buffer->task_comm,
				buffer->pid, buffer->size);
	}
	mutex_unlock(&dev->buffer_lock);
	return 0;
}
