
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include "load_image.h"
#include <linux/slab.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>
#include <linux/libfdt.h>
#include <linux/of.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/mutex.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/hifidrvinterface.h>
#include "device_tree.h"
#include <partition.h>
#include <hisi_partition.h>
#include <linux/hisi/kirin_partition.h>
#include <teek_client_api.h>
#include <teek_client_id.h>

#define SECBOOT_BUFLEN  		  (0x100000)
#define ALIGNED_64BYTE_VALUE(value)  ((((value) + 63) / 64) * 64)

static  u8 SECBOOT_BUFFER[SECBOOT_BUFLEN]; /*1M Bytes*/
typedef enum SVC_SECBOOT_IMG_TYPE SECBOOT_IMG_TYPE;
typedef enum SVC_SECBOOT_CMD_ID SECBOOT_CMD_TYPE;

static struct mutex load_image_lock;

/*
 * Function name:TEEK_init.
 * Discription:Init the TEEC and get the context
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ context: context.
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
static s32 TEEK_init(TEEC_Session *session, TEEC_Context *context)
{
    TEEC_Result result;
    TEEC_UUID svc_uuid = TEE_SERVICE_SECBOOT;
    TEEC_Operation operation = {0};
    u8 package_name[] = "sec_boot";
    u32 root_id = 0;

    result = TEEK_InitializeContext(
            NULL,
            context);

	if (result != TEEC_SUCCESS) {
		sec_print_err("TEEK_InitializeContext failed!\n");
        result = SEC_ERROR;
        goto error;
    }

    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&root_id);
    operation.params[2].tmpref.size = sizeof(root_id);
    operation.params[3].tmpref.buffer = (void *)(package_name);
    operation.params[3].tmpref.size = strlen(package_name) + 1;
    result = TEEK_OpenSession(
            context,
            session,
            &svc_uuid,
            TEEC_LOGIN_IDENTIFY,
            NULL,
            &operation,
            NULL);

    if (result != TEEC_SUCCESS)
    {
        sec_print_err("TEEK_OpenSession failed!\n");
        result = SEC_ERROR;
        TEEK_FinalizeContext(context);
    }

error:

    return result;
}


/*
 * Function name:reset_soc_image.
 * Discription:reset the core in sec_OS, like modem and hifi core  .
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the core to reset.
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
s32 reset_soc_image(TEEC_Session *session,
		  SECBOOT_IMG_TYPE  image)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_NONE,
						TEEC_NONE,
						TEEC_NONE);

    operation.params[0].value.a = image; /*MODEM/HIFI*/
    result = TEEK_InvokeCommand(
                                session,
                               SECBOOT_CMD_ID_RESET_IMAGE ,
                                &operation,
                                &origin);
    if (result != TEEC_SUCCESS) {
		sec_print_err("reset  failed, result is 0x%x!\n", result);
		result = SEC_ERROR;
	}

	return result;
}

/*
 * Function name:start_soc_image.
 * Discription:start the image verification, if success, unreset the soc
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the image to verification and unreset
 *      @ run_addr: the image entry address
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
s32 verify_soc_image(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        u32 run_addr,SECBOOT_CMD_TYPE type)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_NONE,
						TEEC_NONE);

     operation.params[0].value.a = image;
     operation.params[1].value.a = run_addr;
     operation.params[1].value.b = 0;/*SECBOOT_LOCKSTATE , not used currently*/
     result = TEEK_InvokeCommand(
                                    session,
                                    type,
                                    &operation,
                                    &origin);
     if (result != TEEC_SUCCESS){
		sec_print_err("start  failed, result is 0x%x!\n", result);
		result = SEC_ERROR;
	}
	return result;
}



/*
 * Function name:trans_vrl_to_os.
 * Discription:transfer vrl data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ buf: the buf in  kernel to transfer
 *      @ size: the size to transfer.
 * return value:
 *      @ TEEC_SUCCESS-->success, others--> failed.
 */
static s32 trans_vrl_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
		  void * buf,
		  const unsigned int size)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_MEMREF_TEMP_INPUT,
						TEEC_NONE,
						TEEC_NONE);

	operation.params[0].value.a = image;
	operation.params[1].tmpref.buffer = (void *)buf;
	operation.params[1].tmpref.size = size;

	result = TEEK_InvokeCommand(
				session,
				SECBOOT_CMD_ID_COPY_VRL_TYPE,
				&operation,
				&origin);
	if (result != TEEC_SUCCESS) {
		sec_print_err("invoke failed!\n");
		result = SEC_ERROR;
	}

	return result;
}

/*
 * Function name:trans_data_to_os.
 * Discription:transfer image data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ run_addr: the image entry address.
 *      @ buf: the buf in  kernel to transfer
 *      @ offset: the offset to run_addr.
 *      @ size: the size to transfer.
 * return value:
 *      @ TEEC_SUCCESS-->success, others--> failed.
 */
static s32 trans_data_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        u32 run_addr,
		  void * buf,
		  const unsigned int offset,
		  const unsigned int size)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_NONE);

	operation.params[0].value.a = image;
	operation.params[1].value.a = run_addr;
	operation.params[1].value.b = offset;
	operation.params[2].value.a = (u32)virt_to_phys(buf);
	operation.params[2].value.b = size;

	result = TEEK_InvokeCommand(
				session,
				SECBOOT_CMD_ID_COPY_DATA_TYPE,
				&operation,
				&origin);
	if (result != TEEC_SUCCESS) {
		sec_print_err("invoke failed!\n");
		result = SEC_ERROR;
	}

	return result;
}

int bsp_read_bin(const char *partion_name, unsigned int offset,
				unsigned int length, char *buffer)
{
	int ret          = -1;
	char *pathname   = NULL;
	struct file *fp;
	mm_segment_t fs;
	loff_t pos = 0;

	if ((NULL == partion_name) || (NULL == buffer)) {
		sec_print_err("partion_name(%p) or buffer(%p) is null", partion_name, buffer);
		return SEC_ERROR;
	}

    /*get resource*/
	pathname = kmalloc(PART_NAMELEN, GFP_KERNEL);
	if (!pathname) {
		sec_print_err("pathname malloc failed\n");
		return SEC_ERROR;
	}

	ret = flash_find_ptn((const char *)partion_name, pathname);
	if (ret < 0) {
		sec_print_err("partion_name(%s) is not in partion table!\n", partion_name);
		goto error;
	}

	fp = filp_open(pathname, O_RDONLY, 0600);
	if (IS_ERR(fp)) {
		sec_print_err("filp_open(%s) failed", pathname);
		goto error;
	}

	ret = vfs_llseek(fp, offset, SEEK_SET);
	if (ret < 0) {
		sec_print_err("seek ops failed, ret %d", ret);
		goto error2;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	pos = fp->f_pos;
	ret = vfs_read(fp, (char __user *)buffer, length, &pos);
	if (ret != length) {
		sec_print_err("read ops failed, ret=%d(len=%d)", ret, length);
		set_fs(fs);
		goto error2;
	}
	set_fs(fs);

	filp_close(fp, NULL);


    /*free resource*/
	if (NULL != pathname) {
		kfree(pathname);
		pathname = NULL;
	}

	return SEC_OK;

error2:
	filp_close(fp, NULL);

error:
    /*释放资源2*/
	if (NULL != pathname) {
		kfree(pathname);
		pathname = NULL;
	}

	sec_print_err("failed");
	return SEC_ERROR;

}

/*
 * Function name:load_data_to_os.
 * Discription:cut the  image data to 1M per block, and trans them to  sec_OS.
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ part_name: image's partition name.
 *      @ run_addr: the image entry address.
 *      @ offset: the offset to run_addr.
 *      @ sizeToRead: total  size of the image.
 * return value:
 *      @ SEC_OK-->success, others--> failed.
 */
static s32 load_data_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        char* part_name,
                        u32 run_addr,
                        u32 offset,
                        u32 sizeToRead)
{
	u32 read_bytes;
	u32 end_bytes;
	u32 copy_bytes;
	u32 timers;
	u32 i;
	s32 ret = SEC_ERROR;

	/*make size aligned with 64 bytes*/
	sizeToRead = ALIGNED_64BYTE_VALUE(sizeToRead);

	/*split the size to be read to each 1M bytes.*/
	timers = sizeToRead / SECBOOT_BUFLEN;
	if (sizeToRead % SECBOOT_BUFLEN)
	timers = timers + 1;

	end_bytes = sizeToRead;

	mutex_lock(&load_image_lock);
	/*call flash_read each time to read to memDst.*/
	for (i = 0; i < timers; i++)
	{
		if (end_bytes >= SECBOOT_BUFLEN)
			read_bytes = SECBOOT_BUFLEN;
		else
			read_bytes = end_bytes;

		if (bsp_read_bin(part_name, offset + i * SECBOOT_BUFLEN, read_bytes, (void *)SECBOOT_BUFFER)) {
			sec_print_err("%s: err: flash_read\n", __func__);
			mutex_unlock(&load_image_lock);
			return SEC_ERROR;
		}

		if (end_bytes >= SECBOOT_BUFLEN) {
			if (SECBOOT_BUFLEN != read_bytes) {
				sec_print_err("%s: err: SECBOOT_BUFLEN:%d != read_bytes:%d\r\n", __func__, SECBOOT_BUFLEN, read_bytes);
				mutex_unlock(&load_image_lock);
				return SEC_ERROR;
			}
			copy_bytes = SECBOOT_BUFLEN;
		} else {
			if (end_bytes > read_bytes) {
				sec_print_err("%s: err: end_bytes:%d!= read_bytes:%d\r\n", __func__, end_bytes, read_bytes);
				mutex_unlock(&load_image_lock);
				return SEC_ERROR;
			}
			copy_bytes = end_bytes;
		}

		ret = trans_data_to_os(session, image, run_addr, (void *)(SECBOOT_BUFFER), (i * SECBOOT_BUFLEN), copy_bytes);
		if (SEC_ERROR == ret)
		{
			sec_print_err("image trans to os is failed, error code 0x%x\r\n", ret);
			mutex_unlock(&load_image_lock);
			return SEC_ERROR;
		}

		end_bytes -= copy_bytes;
	}
	mutex_unlock(&load_image_lock);

	if (0 != end_bytes) {
		sec_print_err("%s: end_bytes = 0x%x\n", __func__, end_bytes);
		return SEC_ERROR;
	}

	return SEC_OK;
}


/*
 * Function name:load_vrl_from_partition_to_os.
 * Discription:load modem  image's VRL  data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 load_vrl_to_os(TEEC_Session *session,
					BSP_CORE_TYPE_E ecoretype,
					char *partion_name)
{
     s32 ret = SEC_ERROR;
	 int vrl_index = 0;

	if (NULL != partion_name) {
		vrl_index = flash_get_ptn_index(partion_name);
		if (vrl_index < 0) {
			sec_print_err("fail to find image ptn\r\n");
			return SEC_ERROR;
		}
	} else {
		sec_print_err("image type is error!\n");
		return SEC_ERROR;
	}

	mutex_lock(&load_image_lock);
	/*get image vrl info*/
	ret  = bsp_read_bin((const char *)PTN_VRL_NAME, (vrl_index * VRL_SIZE), VRL_SIZE, (void *)SECBOOT_BUFFER);
	if (ret < 0)
	{
		sec_print_err("fail to read the vrl of image,error code 0x%x\r\n", ret);
		mutex_unlock(&load_image_lock);
		return SEC_ERROR;
	}

	/* trans the vrl to secure os. */
	ret = trans_vrl_to_os(session,(SECBOOT_IMG_TYPE)ecoretype, (void *)SECBOOT_BUFFER, VRL_SIZE);
	if (SEC_ERROR == ret)
	{
		sec_print_err("image vrl trans to secureos is failed, error code 0x%x\r\n", ret);
		mutex_unlock(&load_image_lock);
		return SEC_ERROR;
	}
	mutex_unlock(&load_image_lock);

	return SEC_OK;
}

s32 check_image_type(BSP_CORE_TYPE_E ecoretype)
{
	switch (ecoretype) {
	case BSP_CCORE:
	case BSP_HIFI:
	case BSP_BBE:
	case BSP_CDSP:
		return SEC_OK;
		break;
	case BSP_CCORE_TAS:
	case BSP_CCORE_WAS:
	case BSP_CCORE_CAS:
	default:
		return SEC_ERROR;
	}
}

/*
 * Function name:get_image_addr_and_size
 * Discription:get image_addr and image_size
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 get_image_addr_and_size(BSP_CORE_TYPE_E ecoretype, u32 *image_addr,
						u32 *image_size, u32 head_size,
						char *image_name)
{
	void *header = NULL;
	s32 ret = SEC_OK;

	header = kmalloc(head_size, GFP_KERNEL);
	if (NULL  == header) {
		sec_print_err("%s header malloc fail\n", image_name);
		ret = SEC_ERROR;
		goto err_out;
	}
	memset((void*)header, 0, head_size);

	/*get the elf*/
	ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
	if (SEC_ERROR == ret) {
		sec_print_err("fail to read %s head of image\n", image_name);
		goto err_out;
	}

	switch (ecoretype)
	{
		case BSP_CCORE:
			*image_size = ((struct image_head *)header)->image_length+head_size;
			*image_addr = ((struct image_head *)header)->load_addr-head_size;
			break;
		case BSP_HIFI:
			*image_size = ((struct drv_hifi_image_head *)header)->image_size;
			*image_addr = HIFI_RUN_ADDR;
			break;
		case BSP_BBE:
			*image_size = ((struct image_head *)header)->image_length+head_size;
			*image_addr = DDR_TLPHY_IMAGE_ADDR-head_size;
			break;
		case BSP_CDSP:
			*image_size = ((struct dsp_bin_header_stru *)header)->ulFileSize;
			*image_addr = DDR_TLPHY_IMAGE_ADDR;
			break;
		default:
			sec_print_err("ecoretype is error!\n");
			ret = SEC_ERROR;
			goto err_out;
	}

err_out:
	if (header) {
		kfree(header);
		header = NULL;
	}
	return ret;
}

s32 get_imgname_and_headsize(BSP_CORE_TYPE_E ecoretype, char *image_name, u32 *head_size)
{
	if (NULL == image_name) {
		sec_print_err("image_name is null!\n");
		return SEC_ERROR;
	}

	switch (ecoretype)
	{
		case BSP_CCORE:
			strncpy(image_name, PTN_MODEM_NAME, PART_NAMELEN);
			image_name[PART_NAMELEN - 1] = '\0';
			if (NULL != head_size) {
				*head_size = sizeof(struct image_head);
			}
			break;
		case BSP_HIFI:
			strncpy(image_name, PTN_HIFI_NAME, PART_NAMELEN);
			image_name[PART_NAMELEN - 1] = '\0';
			if (NULL != head_size) {
				*head_size = sizeof(struct drv_hifi_image_head);
			}
			break;
		case BSP_BBE:
			strncpy(image_name, PTN_MODEM_DSP_NAME, PART_NAMELEN);
			image_name[PART_NAMELEN - 1] = '\0';
			if (NULL != head_size) {
				*head_size = sizeof(struct image_head);
			}
			break;
		case BSP_CDSP:
			strncpy(image_name, PTN_MODEM_XDSP_NAME, PART_NAMELEN);
			image_name[PART_NAMELEN - 1] = '\0';
			if (NULL != head_size) {
				*head_size = sizeof(struct dsp_bin_header_stru);
			}
			break;
		default:
			sec_print_err("ecoretype is error!\n");
			return SEC_ERROR;
	}

	return SEC_OK;
}

/*
 * Function name:load_image_data
 * Discription:load image data to secos according by ecoretype
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ image addr--> success, others--> failed.
 */
s32 load_image_data(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
	u32 image_size = 0;
	u32 image_addr = 0;
	u32 head_size = 0;
	s32 ret = SEC_ERROR;
	char image_name[PART_NAMELEN] = {0};

	ret = get_imgname_and_headsize(ecoretype, image_name, &head_size);
	if (SEC_OK != ret)
	{
		sec_print_err("get %s image name fail\n", image_name);
		return ret;
	}

	ret = get_image_addr_and_size(ecoretype, &image_addr, &image_size, head_size, image_name);
	if (SEC_OK != ret)
	{
		sec_print_err("get %s image size fail\n", image_name);
		return ret;
	}

	ret = load_data_to_os(session, (SECBOOT_IMG_TYPE)ecoretype, image_name,
					image_addr, 0, image_size);
	if (SEC_OK != ret)
	{
		sec_print_err("load %s data to secureos fail\n", image_name);
		return ret;
	}

	return image_addr;
}

#ifdef CONFIG_MODEMID_HI3650
int get_modemid(unsigned int *modemid)
{
	int ret = 0;
	struct device_node *np = NULL;

	np = of_find_compatible_node(NULL, NULL, CHIP_COMPITABLE_STR);
	if (NULL == np) {
		sec_print_err("-----can not find %s node by compatible\n", CHIP_COMPITABLE_STR);
		return SEC_ERROR;
	}

	ret = of_property_read_u32(np, MODEMID_STR, modemid);
	if (SEC_OK == ret) {
		sec_print_info("find modemid by dts: %x\n", *modemid);
		return SEC_OK;
	} else {
		sec_print_err("-----can not find %s node by compatible node\n", MODEMID_STR);
		return SEC_ERROR;
	}
}

unsigned int get_dtb_entry(unsigned int modemid, struct modem_dt_table_t *dt_hdr, struct modem_dt_entry_t *dt_entry_ccore)
{
	uint32_t i;
	uint8_t sec_id[4] = {0};
	struct modem_dt_entry_t *dt_entry_ptr = NULL;

	sec_id[0] = MODEMID_K_BITS(modemid);
	sec_id[1] = MODEMID_H_BITS(modemid);
	sec_id[2] = MODEMID_M_BITS(modemid);
	sec_id[3] = MODEMID_L_BITS(modemid);


	/* 获取与modemid匹配的acore/ccore dt_entry 指针,复用dtctool，modem config.dts中将boardid配置为对应modem_id值 */
	dt_entry_ptr = (struct modem_dt_entry_t *)((char *)dt_hdr + sizeof(struct modem_dt_table_t));
	for (i = 0; i < dt_hdr->num_entries; i++) {
		if ((dt_entry_ptr->boardid[0] == sec_id[0]) &&
		(dt_entry_ptr->boardid[1] == sec_id[1]) &&
		(dt_entry_ptr->boardid[2] == sec_id[2]) &&
		(dt_entry_ptr->boardid[3] == sec_id[3])) {
			sec_print_info("[%d],modemid(0x%x, 0x%x, 0x%x, 0x%x)\n",
				i, dt_entry_ptr->boardid[0], dt_entry_ptr->boardid[1], dt_entry_ptr->boardid[2], dt_entry_ptr->boardid[3]);

			memcpy((void *)dt_entry_ccore, (void *)dt_entry_ptr, sizeof(modem_dt_entry_t));
			break;
	    }
		dt_entry_ptr++;
	}

	if (i == dt_hdr->num_entries) {
		sec_print_err("fail to find modem_dt_entry\n");
		return SEC_ERROR;
    }

	return SEC_OK;
}

s32 load_and_verify_dtb_data(TEEC_Session *session)
{
    s32 ret = SEC_ERROR;
    u32 head_size = BSP_MODEM_DTB_HEADER;
	u32 modem_id = 0;
    struct modem_dt_table_t *header = NULL;
	struct modem_dt_entry_t dt_entry_ptr = {{0}};
    const char *image_name = PTN_MODEM_DTB_NAME;

    header  = (struct modem_dt_table_t *)kmalloc(head_size, GFP_KERNEL);
    if(NULL == header)
    {
       sec_print_err("dtb header malloc fail\n");
       goto err_out;
    }
    memset((void*)header, 0, head_size);

    /*get the elf*/
    ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
    if (SEC_ERROR == ret)
    {
       sec_print_err("fail to read the head of modem dtb image\n");
       ret = SEC_ERROR;
       goto err_out;
    }

	ret = get_modemid(&modem_id);
	if (SEC_OK != ret)
    {
       sec_print_err("fail to get modem id\n");
       ret = SEC_ERROR;
       goto err_out;
    }

	memset((void *)&dt_entry_ptr, 0, sizeof(dt_entry_ptr));
	ret = get_dtb_entry(modem_id, header, &dt_entry_ptr);
    if (SEC_ERROR == ret)
    {
		sec_print_err("fail to get_dtb_entry\n");
		ret = SEC_ERROR;
		goto err_out;
    }

	if (0 != dt_entry_ptr.vrl_size) {
		mutex_lock(&load_image_lock);
		if (dt_entry_ptr.vrl_size > SECBOOT_BUFLEN) {
			sec_print_err("modem dtb vrl size is error\n");
			ret = SEC_ERROR;
			mutex_unlock(&load_image_lock);
			goto err_out;
		}

		ret = bsp_read_bin((const char*)PTN_MODEM_DTB_NAME, dt_entry_ptr.vrl_offset, dt_entry_ptr.vrl_size, SECBOOT_BUFFER);
	    if (SEC_ERROR == ret) {
			sec_print_err("fail to read the dtb image\n");
			ret = SEC_ERROR;
			mutex_unlock(&load_image_lock);
			goto err_out;
	    }

		/* trans the vrl to secure os. */
		ret = trans_vrl_to_os(session, MODEM_DTB, (void *)SECBOOT_BUFFER, VRL_SIZE);
		if (SEC_ERROR == ret)
		{
			sec_print_err("image vrl trans to secureos is failed, error code 0x%x\r\n", ret);
			ret = SEC_ERROR;
			mutex_unlock(&load_image_lock);
	        goto err_out;
		}
		mutex_unlock(&load_image_lock);
    }

	/* trans the dtb data to secure os. */
	ret = load_data_to_os(session, MODEM_DTB, PTN_MODEM_DTB_NAME, DDR_MCORE_DTS_ADDR, dt_entry_ptr.dtb_offset, dt_entry_ptr.dtb_size);
    if (SEC_ERROR == ret)
    {
        sec_print_err("fail to load modem dtb image\n");
        ret = SEC_ERROR;
        goto err_out;
    }

	if (0 != dt_entry_ptr.vrl_size) {
        ret = verify_soc_image(session, MODEM_DTB, DDR_MCORE_DTS_ADDR, SECBOOT_CMD_ID_VERIFY_DATA_TYPE);
		if (SEC_ERROR == ret) {
			sec_print_err("fail to verify modem dtb image\n");
            ret = SEC_ERROR;
            goto err_out;
        }
    }

	sec_print_info("success to load and verify modem dtb image\n");
err_out:
    if (header)
    {
        kfree(header);
        header = NULL;
    }
    return ret;
}
#endif
/*
 * Function name:bsp_reset_request.
 * Discription:reset the modem/hifi in SEC_OS.
 * Parameters:
 *      @ SECBOOT_IMG_TYPE image type.
 *Called in:
 *      @ modem/hifi_reset_set
 * return value:
 *      @ SEC_OK-->success, others-->failed.
 */
int bsp_reset_request(BSP_CORE_TYPE_E ecoretype)
{
	TEEC_Session session;
	TEEC_Context context;
	s32 ret = SEC_ERROR;

	ret = TEEK_init(&session, &context);
	if (SEC_ERROR == ret) {
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

	ret = reset_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype);
	if (SEC_ERROR == ret) {
		sec_print_err("reset_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}

/*
 * Function name:bsp_image_seccheck.
 * Discription:local seccheck for modem/dsp.
 * Parameters:
 *      @ BSP_CORE_TYPE_E image type.
 *Called in:
 *      @ modem/dsp start
 * return value:
 *      @ SEC_OK-->success, others-->failed.
*/
int bsp_image_seccheck (BSP_CORE_TYPE_E ecoretype)
{
    s32 ret = SEC_ERROR;
    TEEC_Session session;
    TEEC_Context context;
	char image_name[PART_NAMELEN] = {0};

	ret = check_image_type(ecoretype);
	if (SEC_ERROR == ret) {
		sec_print_err("ecoretype is error!\n");
		return SEC_ERROR;
	}

    /*TEEK_init do prepare for start SecureOs*/
    ret = TEEK_init(&session, &context);
	if (SEC_ERROR == ret) {
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

#ifdef CONFIG_MODEMID_HI3650
	if (BSP_CCORE == ecoretype) {
		sec_print_err("load_and_verify_dtb_data %x!\n", ecoretype);
		ret = load_and_verify_dtb_data(&session);
		if (SEC_ERROR == ret) {
			sec_print_err("load_and_verify_dtb_data fail!\n");
			goto err_out;
		}
	}
#endif

	ret = get_imgname_and_headsize(ecoretype, image_name, NULL);
	if (SEC_OK != ret) {
		sec_print_err("get %s image name fail\n", image_name);
		return ret;
	}

	ret = load_vrl_to_os(&session, ecoretype, image_name);
	if (SEC_ERROR == ret) {
		sec_print_err("load_vrl_to_os fail result 0x%x!\n", ret);
		goto err_out;
	}

	/*end of trans all data, start verify, if success, unreset the SOC*/
	ret = verify_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype, 0, SECBOOT_CMD_ID_VERIFY_DATA_TYPE_LOCAL);
	if (SEC_ERROR == ret) {
		sec_print_err("start_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}


/*
 * Function name:load_check_sec_image.
 * Discription:load the image to secureOS and the SecureOS verify it.
 * Parameters:
 *      @ void.
 *Called in:
 *      @ ccorereset_task
 * return value:
 *      @ SEC_OK-->success, others-->failed.
 */
int bsp_reset_loadimage (BSP_CORE_TYPE_E ecoretype)
{
	TEEC_Session session;
	TEEC_Context context;
	s32 ret = SEC_ERROR;
	u32 image_addr = 0;
	char image_name[PART_NAMELEN] = {0};

	ret = check_image_type(ecoretype);
	if (SEC_ERROR == ret) {
		sec_print_err("ecoretype is error!\n");
		return SEC_ERROR;
	}

	ret = TEEK_init(&session, &context);
	if (SEC_ERROR == ret) {
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

	ret = reset_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype);
	if (SEC_ERROR == ret) {
		sec_print_err("reset_soc_image fail!\n");
		goto err_out;
	}

#ifdef CONFIG_MODEMID_HI3650
	if (BSP_CCORE == ecoretype) {
		ret = load_and_verify_dtb_data(&session);
		if (SEC_ERROR == ret) {
			sec_print_err("load_and_verify_dtb_data fail!\n");
			goto err_out;
		}
	}
#endif

	ret = get_imgname_and_headsize(ecoretype, image_name, NULL);
	if (SEC_ERROR == ret) {
		sec_print_err("get %s image name fail\n", image_name);
		return ret;
	}

	ret = load_vrl_to_os(&session, ecoretype, image_name);
	if (SEC_ERROR == ret) {
		sec_print_err("load_vrl_to_os fail!\n");
		goto err_out;
	}

	ret = load_image_data(&session, ecoretype);
	if (SEC_ERROR == ret) {
			sec_print_err("load image fail!\n");
			goto err_out;
	} else {
		image_addr = ret;
	}

	/*end of trans all data, start verify, if success, unreset the SOC*/
	ret = verify_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype, image_addr, SECBOOT_CMD_ID_VERIFY_DATA_TYPE);
	if (SEC_ERROR == ret) {
		sec_print_err("start_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}

/*
 * Function name:bsp_load_and_verify_image.
 * Discription:load the image to secureOS and the SecureOS verify it.
 * Parameters:
 *      @ void.
 *Called in:
 *      @ ccorereset_task
 * return value:
 *      @ SEC_OK-->success, others-->failed.
 */
int bsp_load_and_verify_image(struct load_image_info *img_info)
{
	TEEC_Session session;
	TEEC_Context context;
	s32 ret = SEC_ERROR;

	ret = TEEK_init(&session, &context);
	if (SEC_ERROR == ret) {
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

	ret = reset_soc_image(&session, img_info->ecoretype);
	if (SEC_ERROR == ret) {
		sec_print_err("reset_soc_image fail!\n");
		goto err_out;
	}

	ret = load_vrl_to_os(&session, img_info->ecoretype, img_info->partion_name);
	if (SEC_ERROR == ret) {
		sec_print_err("load_vrl_to_os fail!\n");
		goto err_out;
	}

	ret = load_data_to_os(&session, img_info->ecoretype, img_info->partion_name,
						img_info->image_addr, 0, img_info->image_size);
	if (SEC_ERROR == ret) {
		sec_print_err("load %s data to secureos fail, error code 0x%x\r\n", img_info->partion_name, ret);
		goto err_out;
	}

	/*end of trans all data, start verify, if success, unreset the SOC*/
	ret = verify_soc_image(&session, img_info->ecoretype, img_info->image_addr, SECBOOT_CMD_ID_VERIFY_DATA_TYPE);
	if (SEC_ERROR == ret) {
		sec_print_err("start_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}

static int __init load_image_init(void)
{
	mutex_init(&load_image_lock);
	return SEC_OK;
}

/*
 * Function name:bsp_reset_core_notify.
 * Description:notify the remote processor MODEM is going to reset.
 * Parameters:
 *      @ ecoretype: the core to be notified.
 *      @ cmdtype: to send to remote processor.
 *      @ timeout_ms: max time to wait, ms.
 *      @ retval: the ack's value get from the remote processor.
 *Called in:
 *      @ modem is going to reset. <reset_balong.c>
 *Return value:
 *      @ BSP_RESET_NOTIFY_REPLY_OK-->the remote processor give response in time.
 *      @ BSP_RESET_NOTIFY_SEND_FAILED-->the parameter is wrong or other rproc_sync_send's self error.
 *      @ BSP_RESET_NOTIFY_TIMEOUT-->after wait timeout_ms's time, the remote processor give no response.
*/
int bsp_reset_core_notify(BSP_CORE_TYPE_E ecoretype, unsigned int cmdtype, unsigned int timeout_ms, unsigned int *retval)
{
	int retry;
	int ret = BSP_RESET_NOTIFY_REPLY_OK;
	rproc_id_t rproc_id;
	rproc_msg_t tx_buffer[2];
	rproc_msg_t ack_buffer[2];

	if(BSP_HIFI == ecoretype)
	{
		tx_buffer[0] = 32 << 8;/*the INT_SRC_NUM to hifi*/
		rproc_id = HISI_RPROC_HIFI_MBX29;
	}
	else if(BSP_LPM3 == ecoretype)
	{
		tx_buffer[0] = (0<<24|9<<16|3<<8);
		rproc_id = HISI_RPROC_LPM3_MBX16;
	}
	else
	{
		sec_print_err("wrong ecoretype\n");
		return BSP_RESET_NOTIFY_SEND_FAILED;
	}

	/*300ms's timeout is fixed in RPROC_SYNC_SEND*/
	retry = timeout_ms/MAILBOX_MANUACK_TIMEOUT + 1;
	tx_buffer[1] = cmdtype;

	do
	{
		ret = RPROC_SYNC_SEND(rproc_id, tx_buffer, 2, ack_buffer, 2);
		if (0 == ret)
		{
			/*the send is reponsed by the remote process, break out*/
			*retval = ack_buffer[1];
			break;
		}
		else if(-ETIMEOUT == ret)
		{
			/*the timeout will print out, below message to tell it's normal*/
			retry--;
			ret = BSP_RESET_NOTIFY_TIMEOUT;
			sec_print_err("the remote process is getting up, the ipc timeout is normal\n");
			continue;
		}
		else
		{
			ret = BSP_RESET_NOTIFY_SEND_FAILED;
			sec_print_err("bad parameter or other error\n");
			break;
		}
	} while(retry);

    return ret;
}

fs_initcall_sync(load_image_init);

MODULE_AUTHOR("j00245221");
MODULE_DESCRIPTION("Load image driver");
MODULE_VERSION("1.0");
