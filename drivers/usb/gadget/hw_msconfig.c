/*
 * huawei mass storage autorun and lun config
 *
 */

static ssize_t autorun_store(
	struct device *device, struct device_attribute *attr,
	const char *buff, size_t size)
{
	if(size>MS_STG_SET_LEN || buff==NULL){
		pr_err("mass_storage: autorun_store buff error\n");
		return -EINVAL;
	}
	if(0!=strcmp(buff, "enable") && 0!=strcmp(buff ,"disable")){
		pr_err("mass_storage: autorun_store para error '%s'\n", buff);
		return -EINVAL;
	}
	strlcpy(autorun, buff, sizeof(autorun));

	return size;
}

static ssize_t autorun_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", autorun);
}

static DEVICE_ATTR(autorun, S_IWUSR|S_IRUSR, autorun_show, autorun_store);

static ssize_t luns_store(
	struct device *device, struct device_attribute *attr,
	const char *buff, size_t size)
{
	if(size>MS_STG_SET_LEN || buff==NULL){
		pr_err("mass_storage: luns_store buff error\n");
		return -EINVAL;
	}
	strlcpy(luns, buff, sizeof(luns));

	return size;
}

static ssize_t luns_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", luns);
}

static DEVICE_ATTR(luns, S_IWUSR|S_IRUSR, luns_show, luns_store);