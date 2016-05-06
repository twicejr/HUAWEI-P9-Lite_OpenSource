/*************************************************************
* Filename:    hisi_battery_data.c
*
* Discription:  driver for battery.
* Copyright:    (C) 2014 huawei.
*
* revision history:
*
*
**************************************************************/
#include <linux/power/hisi/hisi_battery_data.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/string.h>
#include <linux/slab.h>
/*lint -e451*/
#include <asm/bug.h>
/*lint +e451*/
#include <linux/module.h>
#include <dsm/dsm_pub.h>

/* #define HISI_BATTERY_DATA_DEBUG */

#ifdef hwlog_info
#define HWLOG_TAG hisi_battery_data
HWLOG_REGIST();
#else
#define hwlog_info(fmt, args...) do { printk(KERN_INFO "[hisi_battery_data]" fmt, ## args); } while (0)
#define hwlog_warn(fmt, args...) do { printk(KERN_WARNING "[hisi_battery_data]" fmt, ## args); } while (0)
#define hwlog_err(fmt, args...)  do { printk(KERN_ERR "[hisi_battery_data]" fmt, ## args); } while (0)
#endif

#ifdef HISI_BATTERY_DATA_DEBUG
#define hisi_bat_info(fmt, args...) do { hwlog_info(fmt, ## args); } while (0)
#else
#define hisi_bat_info(fmt, args...) do {} while (0)
#endif

/***************************static variable definition***********************************/
static struct hisi_coul_battery_data **p_data = NULL;
static unsigned int hisi_bat_data_size = 0;	/* used to store number of bat types defined in DTS */
/* used to judege whether bat_drv works fine or not, 1 means yes,0 means no */
static int bat_param_status = 0;
static int temp_points[] = { -20, -10, 0, 25, 40, 60 };

#if defined(CONFIG_HUAWEI_DSM)
static struct dsm_dev dsm_battery_detect = {
	.name = "dsm_battery_detect",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};

static struct dsm_client *battery_detect_dclient = NULL;
#endif

struct hisi_coul_battery_data *get_battery_data(unsigned int id_voltage)
{
	int i;
	int dsm_error_found = -1;
	int dsm_error_offset = 0;

	if (!bat_param_status) {
		hwlog_err("battery param is invalid\n");
		return NULL;
	}
#if defined(CONFIG_HUAWEI_DSM)
	if (!dsm_client_ocuppy(battery_detect_dclient)) {
		dsm_error_found++;
	}
#endif
	for (i = 0; i < hisi_bat_data_size; i++) {
		if ((id_voltage > p_data[i]->id_identify_min) && (id_voltage <= p_data[i]->id_identify_max)) {
			if ((id_voltage < p_data[i]->id_voltage_min) || (id_voltage > p_data[i]->id_voltage_max)) {
				dsm_error_found++;
				dsm_error_offset = 0;
#if defined(CONFIG_HUAWEI_DSM)
				dsm_client_record(battery_detect_dclient, "Battery id voltage:%d is out of normal range:[%d~%d],identify range:[%d~%d]!\n",
						  id_voltage,
						  p_data[i]->id_voltage_min,
						  p_data[i]->id_voltage_max,
						  p_data[i]->id_identify_min,
						  p_data[i]->id_identify_max);
#endif
			}
			break;
		}
	}
	if (i == hisi_bat_data_size) {
		i = 0;
		dsm_error_found++;
		dsm_error_offset = 1;
#if defined(CONFIG_HUAWEI_DSM)
		dsm_client_record(battery_detect_dclient, "Battery id voltage:%d is invalid. Use the default battery params!\n", id_voltage);
#endif
	}
	if (dsm_error_found > 0) {
#if defined(CONFIG_HUAWEI_DSM)
		dsm_client_notify(battery_detect_dclient, DSM_BATTERY_DETECT_ERROR_NO + dsm_error_offset);
#endif
	} else if (!dsm_error_found) {
#if defined(CONFIG_HUAWEI_DSM)
		dsm_client_unocuppy(battery_detect_dclient);
#endif
	} else {
		hwlog_err("dsm battery_detect_dclient ocuppy failed!\n");
	}
	hwlog_info("current battery name is %s\n", p_data[i]->batt_brand);
	return p_data[i];
}

static int get_dat(struct device_node *np, struct hisi_coul_battery_data *pdat)
{
	int ret = 0;
	int i, j;
	const char *chrg_data_string = NULL;
	int array_len = 0;

	ret = of_property_read_u32(np, "fcc", &(pdat->fcc));
	if (ret) {
		hwlog_err("get fcc failed\n");
		return -EINVAL;
	}
	hisi_bat_info("fcc is %u\n", pdat->fcc);

	ret = of_property_read_u32(np, "id_identify_min", (unsigned int *)(&(pdat->id_identify_min)));
	if (ret) {
		hwlog_err("get id_identify_min failed\n");
		return -EINVAL;
	}
	hisi_bat_info("id_identify_min is %d\n", pdat->id_identify_min);

	ret = of_property_read_u32(np, "id_identify_max", (unsigned int *)(&(pdat->id_identify_max)));
	if (ret) {
		hwlog_err("get id_identify_max failed\n");
		return -EINVAL;
	}
	hisi_bat_info("id_identify_max is %d\n", pdat->id_identify_max);

	ret = of_property_read_u32(np, "id_voltage_min", (unsigned int *)(&(pdat->id_voltage_min)));
	if (ret) {
		hwlog_err("get id_voltage_min failed\n");
		return -EINVAL;
	}
	hisi_bat_info("id_voltage_min is %d\n", pdat->id_voltage_min);

	ret = of_property_read_u32(np, "id_voltage_max", (unsigned int *)(&(pdat->id_voltage_max)));
	if (ret) {
		hwlog_err("get id_voltage_max failed\n");
		return -EINVAL;
	}
	hisi_bat_info("id_voltage_max is %d\n", pdat->id_voltage_max);

	ret = of_property_read_u32(np, "default_rbatt_mohm", (unsigned int *)(&(pdat->default_rbatt_mohm)));
	if (ret) {
		hwlog_err("get default_rbatt_mohm failed\n");
		return -EINVAL;
	}
	hisi_bat_info("default_rbatt_mohm is %d\n", pdat->default_rbatt_mohm);
	/* vbat_max */
	ret = of_property_read_u32(np, "vbat_max", (unsigned int *)(&(pdat->vbatt_max)));
	if (ret) {
		hwlog_err("get vbat_max failed\n");
		return -EINVAL;
	}
	hisi_bat_info("vbat_max is %d\n", pdat->vbatt_max);
	/* temp_para */
	array_len = of_property_count_strings(np, "temp_para");
	if ((array_len <= 0) || (array_len % TEMP_PARA_TOTAL != 0)
	    || (array_len > TEMP_PARA_LEVEL * TEMP_PARA_TOTAL)) {
		hwlog_err("temp_para is invaild,please check temp_para number!!\n");
		return -EINVAL;
	}
	pdat->chrg_para->temp_len = array_len;
	for (i = 0; i < array_len; i++) {
		ret = of_property_read_string_index(np, "temp_para", i, &chrg_data_string);
		if (ret) {
			hwlog_err("get temp_para failed\n");
			return -EINVAL;
		}
		pdat->chrg_para->temp_data[i / (TEMP_PARA_TOTAL)][i % (TEMP_PARA_TOTAL)] = simple_strtol(chrg_data_string, NULL, 10);
		hisi_bat_info("chrg_para->temp_data[%d][%d] = %d\n",
			i / (TEMP_PARA_TOTAL),
			i % (TEMP_PARA_TOTAL),
			pdat->chrg_para->temp_data[i / (TEMP_PARA_TOTAL)][i % (TEMP_PARA_TOTAL)]);
	}
	/* vbat_para */
	array_len = of_property_count_strings(np, "vbat_para");
	if ((array_len <= 0) || (array_len % VOLT_PARA_TOTAL != 0)
	    || (array_len > VOLT_PARA_LEVEL * VOLT_PARA_TOTAL)) {
		hwlog_err("vbat_para is invaild,please check vbat_para number!!\n");
		return -EINVAL;
	}
	pdat->chrg_para->volt_len = array_len;
	for (i = 0; i < array_len; i++) {
		ret = of_property_read_string_index(np, "vbat_para", i, &chrg_data_string);
		if (ret) {
			hwlog_err("get vbat_para failed\n");
			return -EINVAL;
		}
		pdat->chrg_para->volt_data[i / (VOLT_PARA_TOTAL)][i % (VOLT_PARA_TOTAL)] = simple_strtol(chrg_data_string, NULL, 10);
		hisi_bat_info("chrg_para->volt_data[%d][%d] = %d\n",
			i / (VOLT_PARA_TOTAL), 
			i % (VOLT_PARA_TOTAL),
			pdat->chrg_para->volt_data[i / (VOLT_PARA_TOTAL)][i % (VOLT_PARA_TOTAL)]);
	}

	/* segment_para */
	array_len = of_property_count_strings(np, "segment_para");
	if ((array_len <= 0) || (array_len % SEGMENT_PARA_TOTAL != 0)
	    || (array_len > SEGMENT_PARA_LEVEL * SEGMENT_PARA_TOTAL)) {
		hwlog_err("segment_para is invaild,please check segment_para number!!\n");
		return -EINVAL;
	}
	pdat->chrg_para->segment_len = array_len;
	for (i = 0; i < array_len; i++) {
		ret = of_property_read_string_index(np, "segment_para", i, &chrg_data_string);
		if (ret) {
			hwlog_err("get segment_para failed\n");
			return -EINVAL;
		}
		pdat->chrg_para->segment_data[i / (SEGMENT_PARA_TOTAL)][i % (SEGMENT_PARA_TOTAL)] = simple_strtol(chrg_data_string, NULL, 10);
		hisi_bat_info("chrg_para->segment_data[%d][%d] = %d\n",
			i / (SEGMENT_PARA_TOTAL),
			i % (SEGMENT_PARA_TOTAL),
			pdat->chrg_para->segment_data[i / (SEGMENT_PARA_TOTAL)][i % (SEGMENT_PARA_TOTAL)]);
	}

	/* batt_brand */
	ret = of_property_read_string(np, "batt_brand", (const char **)(&(pdat->batt_brand)));
	if (ret) {
		hwlog_err("get batt_brand failed\n");
		return -EINVAL;
	}
	hisi_bat_info("batt_brand is %s\n", pdat->batt_brand);
	/* fcc_temp */
	pdat->fcc_temp_lut->cols = TEMP_SAMPLING_POINTS;
	for (i = 0; i < pdat->fcc_temp_lut->cols; i++) {
		pdat->fcc_temp_lut->x[i] = temp_points[i];
		ret = of_property_read_u32_index(np, "fcc_temp", i, (unsigned int *)(&(pdat->fcc_temp_lut->y[i])));
		if (ret) {
			hwlog_err("get fcc_temp[%d] failed\n", i);
			return -EINVAL;
		}
		hisi_bat_info("fcc_temp[%d] is %d\n", i, pdat->fcc_temp_lut->y[i]);
	}
	/* fcc_sf */
	ret = of_property_read_u32(np, "fcc_sf_cols", (unsigned int *)(&(pdat->fcc_sf_lut->cols)));
	if (ret) {
		hwlog_err("get fcc_sf_cols failed\n");
		return -EINVAL;
	}
	hisi_bat_info("fcc_sf_cols is %d\n", pdat->fcc_sf_lut->cols);
	for (i = 0; i < pdat->fcc_sf_lut->cols; i++) {
		ret = of_property_read_u32_index(np, "fcc_sf_x", i, (unsigned int *)(&(pdat->fcc_sf_lut->x[i])));
		if (ret) {
			hwlog_err("get fcc_sf_x[%d] failed\n", i);
			return -EINVAL;
		}
		hisi_bat_info("fcc_sf_x[%d] is %d\n", i, pdat->fcc_sf_lut->x[i]);
		ret = of_property_read_u32_index(np, "fcc_sf_y", i, (unsigned int *)(&(pdat->fcc_sf_lut->y[i])));
		if (ret) {
			hwlog_err("get fcc_sf_y[%d] failed\n", i);
			return -EINVAL;
		}
		hisi_bat_info("fcc_sf_y[%d] is %d\n", i, pdat->fcc_sf_lut->y[i]);
	}
	/* pc_sf_lut */
	ret = of_property_read_u32(np, "pc_sf_rows", (unsigned int *)(&(pdat->pc_sf_lut->rows)));
	if (ret) {
		hwlog_err("get pc_sf_rows failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_sf_rows is %d\n", pdat->pc_sf_lut->rows);
	ret = of_property_read_u32(np, "pc_sf_cols", (unsigned int *)(&(pdat->pc_sf_lut->cols)));
	if (ret) {
		hwlog_err("get pc_sf_cols failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_sf_cols is %d\n", pdat->pc_sf_lut->cols);
	ret = of_property_read_u32(np, "pc_sf_row_entries", (unsigned int *)(&(pdat->pc_sf_lut->row_entries[0])));
	if (ret) {
		hwlog_err("get pc_sf_row_entries failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_sf_row_entries is %d\n", pdat->pc_sf_lut->row_entries[0]);
	ret = of_property_read_u32(np, "pc_sf_percent", (unsigned int *)(&(pdat->pc_sf_lut->percent[0])));
	if (ret) {
		hwlog_err("get pc_sf_percent failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_sf_percent is %d\n", pdat->pc_sf_lut->percent[0]);
	ret = of_property_read_u32(np, "pc_sf_sf", (unsigned int *)(&(pdat->pc_sf_lut->sf[0][0])));
	if (ret) {
		hwlog_err("get pc_sf_sf failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_sf_sf is %d\n", pdat->pc_sf_lut->sf[0][0]);
	/* rbat_sf */
	ret = of_property_read_u32(np, "rbatt_sf_rows", (unsigned int *)(&(pdat->rbatt_sf_lut->rows)));
	if (ret) {
		hwlog_err("get rbatt_sf_rows failed\n");
		return -EINVAL;
	}
	hisi_bat_info("rbatt_sf_rows is %d\n", pdat->rbatt_sf_lut->rows);
	ret = of_property_read_u32(np, "rbatt_sf_cols", (unsigned int *)(&(pdat->rbatt_sf_lut->cols)));
	if (ret) {
		hwlog_err("get rbatt_sf_cols failed\n");
		return -EINVAL;
	}
	hisi_bat_info("rbatt_sf_cols is %d\n", pdat->rbatt_sf_lut->cols);
	for (i = 0; i < pdat->rbatt_sf_lut->rows; i++) {
		ret = of_property_read_u32_index(np, "rbatt_sf_percent", i, (unsigned int *)(&(pdat->rbatt_sf_lut->percent[i])));
		if (ret) {
			hwlog_err("get rbatt_sf_percent[%d] failed\n", i);
			return -EINVAL;
		}
		hisi_bat_info("rbatt_sf_percent[%d] is %d\n", i, pdat->rbatt_sf_lut->percent[i]);
	}
	for (i = 0; i < pdat->rbatt_sf_lut->cols; i++) {
		pdat->rbatt_sf_lut->row_entries[i] = temp_points[i];
	}
	for (i = 0; i < pdat->rbatt_sf_lut->cols; i++) {	/* 6 */
		for (j = 0; j < pdat->rbatt_sf_lut->rows; j++) {    /* 28 */
			ret = of_property_read_u32_index(np, "rbatt_sf_sf", j * 6 + i, (unsigned int *)(&(pdat->rbatt_sf_lut->sf[j][i])));
			if (ret) {
				hwlog_err("get rbatt_sf_sf[%d] failed\n", j * 6 + i);
				return -EINVAL;
			}
			hisi_bat_info("rbatt_sf_sf[%d] is %d\n", j * 6 + i, pdat->rbatt_sf_lut->sf[j][i]);
		}
	}
	/* pc_temp_ocv */
	ret = of_property_read_u32(np, "pc_temp_ocv_rows", (unsigned int *)(&(pdat->pc_temp_ocv_lut->rows)));
	if (ret) {
		hwlog_err("get pc_temp_ocv_rows failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_temp_ocv_rows is %d\n", pdat->pc_temp_ocv_lut->rows);
	ret = of_property_read_u32(np, "pc_temp_ocv_cols", (unsigned int *)(&(pdat->pc_temp_ocv_lut->cols)));
	if (ret) {
		hwlog_err("get pc_temp_ocv_cols failed\n");
		return -EINVAL;
	}
	hisi_bat_info("pc_temp_ocv_cols is %d\n", pdat->pc_temp_ocv_lut->cols);
	for (i = 0; i < pdat->pc_temp_ocv_lut->rows - 1; i++) {
		ret = of_property_read_u32_index(np, "pc_temp_ocv_percent", i, (unsigned int *)(&(pdat->pc_temp_ocv_lut->percent[i])));
		if (ret) {
			hwlog_err("get pc_temp_ocv_percent[%d] failed\n", i);
			return -EINVAL;
		}
		hisi_bat_info("pc_temp_ocv_percent[%d] is %d\n", i, pdat->pc_temp_ocv_lut->percent[i]);
	}
	for (i = 0; i < pdat->pc_temp_ocv_lut->cols; i++) {
		pdat->pc_temp_ocv_lut->temp[i] = temp_points[i];
	}
	for (i = 0; i < pdat->pc_temp_ocv_lut->cols; i++) {	/* 6 */
		for (j = 0; j < pdat->pc_temp_ocv_lut->rows; j++) {	/* 29 */
			ret = of_property_read_u32_index(np, "pc_temp_ocv_ocv", j * 6 + i, (unsigned int *)(&(pdat->pc_temp_ocv_lut->ocv[j][i])));
			if (ret) {
				hwlog_err("get pc_temp_ocv_ocv[%d] failed\n", j * 6 + i);
				return -EINVAL;
			}
			hisi_bat_info("rbatt_sf_sf[%d] is %d\n", j * 6 + i, pdat->pc_temp_ocv_lut->ocv[j][i]);
		}
	}
	return ret;
}

static int get_mem(struct hisi_coul_battery_data **p)
{
	struct hisi_coul_battery_data *pdat;

	pdat = (struct hisi_coul_battery_data *)kzalloc(sizeof(struct hisi_coul_battery_data), GFP_KERNEL);
	if (NULL == pdat) {
		hwlog_err("alloc pdat failed\n");
		return -ENOMEM;
	}

	pdat->fcc_temp_lut = (struct single_row_lut *)kzalloc(sizeof(struct single_row_lut), GFP_KERNEL);
	if (NULL == pdat->fcc_temp_lut) {
		hwlog_err("alloc pdat->fcc_temp_lut failed\n");
		goto get_mem_fail_0;
	}

	pdat->fcc_sf_lut = (struct single_row_lut *)kzalloc(sizeof(struct single_row_lut), GFP_KERNEL);
	if (NULL == pdat->fcc_sf_lut) {
		hwlog_err("alloc pdat->fcc_sf_lut failed\n");
		goto get_mem_fail_1;
	}

	pdat->pc_temp_ocv_lut = (struct pc_temp_ocv_lut *)kzalloc(sizeof(struct pc_temp_ocv_lut), GFP_KERNEL);
	if (NULL == pdat->pc_temp_ocv_lut) {
		hwlog_err("alloc pdat->pc_temp_ocv_lut failed\n");
		goto get_mem_fail_2;
	}

	pdat->pc_sf_lut = (struct sf_lut *)kzalloc(sizeof(struct sf_lut), GFP_KERNEL);
	if (NULL == pdat->pc_sf_lut) {
		hwlog_err("alloc pdat->pc_sf_lut failed\n");
		goto get_mem_fail_3;
	}

	pdat->rbatt_sf_lut = (struct sf_lut *)kzalloc(sizeof(struct sf_lut), GFP_KERNEL);
	if (NULL == pdat->rbatt_sf_lut) {
		hwlog_err("alloc pdat->rbatt_sf_lut failed\n");
		goto get_mem_fail_4;
	}

	pdat->chrg_para = (struct chrg_para_lut *)kzalloc(sizeof(struct chrg_para_lut), GFP_KERNEL);
	if (NULL == pdat->chrg_para) {
		hwlog_err("alloc pdat->chrg_para failed\n");
		goto get_mem_fail_5;
	}

	*p = pdat;
	return 0;
get_mem_fail_5:
	kfree(pdat->rbatt_sf_lut);
get_mem_fail_4:
	kfree(pdat->pc_sf_lut);
get_mem_fail_3:
	kfree(pdat->pc_temp_ocv_lut);
get_mem_fail_2:
	kfree(pdat->fcc_sf_lut);
get_mem_fail_1:
	kfree(pdat->fcc_temp_lut);
get_mem_fail_0:
	kfree(pdat);
	return -ENOMEM;
}

static void free_mem(struct hisi_coul_battery_data **p)
{
	struct hisi_coul_battery_data *pdat = *p;

	if (NULL == pdat) {
		hwlog_err("pointer pd is already NULL\n");
		return;
	}
	if (NULL != pdat->fcc_temp_lut) {
		kfree(pdat->fcc_temp_lut);
		pdat->fcc_temp_lut = NULL;
	}
	if (NULL != pdat->fcc_sf_lut) {
		kfree(pdat->fcc_sf_lut);
		pdat->fcc_sf_lut = NULL;
	}
	if (NULL != pdat->pc_temp_ocv_lut) {
		kfree(pdat->pc_temp_ocv_lut);
		pdat->pc_temp_ocv_lut = NULL;
	}
	if (NULL != pdat->pc_sf_lut) {
		kfree(pdat->pc_sf_lut);
		pdat->pc_sf_lut = NULL;
	}
	if (NULL != pdat->rbatt_sf_lut) {
		kfree(pdat->rbatt_sf_lut);
		pdat->rbatt_sf_lut = NULL;
	}
	if (NULL != pdat->chrg_para) {
		kfree(pdat->chrg_para);
		pdat->chrg_para = NULL;
	}
	kfree(pdat);
	*p = NULL;
}

static int hisi_battery_data_probe(struct platform_device *pdev)
{
	int retval;
	unsigned int i;
	struct device_node *np;
	struct device_node *bat_node;
	/* get device node for battery module */

	bat_param_status = 0;
	np = pdev->dev.of_node;
	if (NULL == np) {
		hwlog_err("get device node failed\n");
		goto fatal_err;
	}
	/* get numeber of types */
	for (i = 0;; ++i) {
		if (!of_parse_phandle(np, "batt_name", i))
			break;

	}
	if (0 == i) {
		hwlog_err("hisi_bat_data_size is zero\n");
		goto fatal_err;
	}
	hisi_bat_data_size = i;
	hwlog_info("hisi_bat_data_size = %u\n", hisi_bat_data_size);

	/* alloc memory to store pointers(point to battery data) */
	p_data = (struct hisi_coul_battery_data **)kzalloc(hisi_bat_data_size * sizeof(struct hisi_coul_battery_data *), GFP_KERNEL);
	if (!p_data) {
		hwlog_err("alloc memory for p_data failed\n");
		goto fatal_err;
	}

	for (i = 0; i < hisi_bat_data_size; ++i) {
		retval = get_mem(&(p_data[i]));
		if (retval) {
			hwlog_err("get_mem[%d] failed\n", i);
			goto fatal_err;
		}
		bat_node = of_parse_phandle(np, "batt_name", i);
		if (NULL == bat_node) {
			hwlog_err("get bat_node failed\n");
			goto fatal_err;
		}
		retval = get_dat(bat_node, p_data[i]);
		if (retval) {
			hwlog_err("get_dat[%d] failed\n", i);
			goto fatal_err;
		}
	}
	platform_set_drvdata(pdev, p_data);
	bat_param_status = 1;
#if defined(CONFIG_HUAWEI_DSM)
	if (!battery_detect_dclient)
		battery_detect_dclient = dsm_register_client(&dsm_battery_detect);

#endif
	hwlog_info("probe ok\n");
	return 0;
fatal_err:
	if (NULL != p_data) {
		for (i = 0; i < hisi_bat_data_size; ++i)
			free_mem(&(p_data[i]));

		kfree(p_data);
	}
	p_data = NULL;
	BUG();
	return -EINVAL;
}

static int hisi_battery_data_remove(struct platform_device *pdev)
{
	int i;
	struct hisi_coul_battery_data **di = platform_get_drvdata(pdev);

	if (di) {
		for (i = 0; i < hisi_bat_data_size; ++i)
			free_mem(&(di[i]));

		kfree(di);
	}
	p_data = NULL;
	return 0;
}

static struct of_device_id hisi_bat_match_table[] = {
	{
	 .compatible = "hisi_battery",
	 .data = NULL,
	 },
	{
	 },
};

static struct platform_driver hisi_bat_driver = {
	.probe = hisi_battery_data_probe,
	.remove = hisi_battery_data_remove,
	.driver = {
		   .name = "hisi_battery",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(hisi_bat_match_table),
		   },
};

int __init hisi_battery_init(void)
{
	return platform_driver_register(&hisi_bat_driver);
}

void __exit hisi_battery_exit(void)
{
	platform_driver_unregister(&hisi_bat_driver);
}

fs_initcall(hisi_battery_init);
module_exit(hisi_battery_exit);
MODULE_AUTHOR("HISILICON");
MODULE_DESCRIPTION("hisi battery module driver");
MODULE_LICENSE("GPL");
