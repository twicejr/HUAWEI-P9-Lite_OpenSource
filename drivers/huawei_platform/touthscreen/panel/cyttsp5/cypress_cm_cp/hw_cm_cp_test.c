/******************************************************************************
 * @file hw_cm_cp_test.c
 *
 * version.h
 *
 * @version 0.0.1
 * @authors 
 *
 *****************************************************************************//*
 * Copyright (2014), Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, associated documentation and materials ("Software") is owned
 * by Cypress Semiconductor Corporation ("Cypress") and is protected by and
 * subject to worldwide patent protection (United States and foreign), United
 * States copyright laws and international treaty provisions. Therefore, unless
 * otherwise specified in a separate license agreement between you and Cypress,
 * this Software must be treated like any other copyrighted material.
 * Reproduction, modification, translation, compilation, or representation of
 * this Software in any other form (e.g., paper, magnetic, optical, silicon) is
 * prohibited without Cypress's express written permission.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or use
 * of Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use as critical components in any products
 * where a malfunction or failure may reasonably be expected to result in
 * significant injury or death ("High Risk Product"). By including Cypress's
 * product in a High Risk Product, the manufacturer of such system or
 * application assumes all risk of such use and in doing so indemnifies Cypress
 * against all liability.
 *
 * Use of this Software may be limited by and subject to the applicable Cypress
 * software license agreement.
 *****************************************************************************/
#include "../cyttsp5_regs.h"
#include "../cyttsp5_core.h"
#include "csv.h"
#include "cm_cp_test.h"
#include <linux/proc_fs.h>
 
 struct cyttsp5_panel_info {
    u8 *product_name;
    u8 *chip_name;
    u8 panel_id;
    u8 *id2str;
 };
 
 static struct cyttsp5_panel_info hw_panel_info[] = {
    {"x1s","tma568", 0,"ofilm" },
    {"x1s","tma568", 1,"lens"    },
    {"Gemini","tma568",0,"ofilm"},
    {"Gemini","tma568",1,"lens"},
    {"mozart","CS448", 0,"ofilm"},
    {"mozart","CS448", 1,"truly"},
    {"liszt","CS448", 1,"truly"},
    {"liszt","CS448", 0,"mutto"},
    {"T2A","CS448", 0,"ofilm"},
    {"T2A","CS448", 3,"mutto"},
    {"Nemo","CS445A", 0,"oflim"},
    {"Nemo","CS445A", 18,"toptouch"},
 };

#define CM_CP_TEST_SUCCESS 0
#define CM_CP_TEST_FAILED -1

 enum tp_test_result
{
    TP_FAIL,
    TP_PASS,
    TP_UNKNOWN,
    TP_INV_DEV,
};

#define CONFIG_NAME_LENGTH 100
atomic_t mmi_test_status_cyttsp5 = ATOMIC_INIT(0);
#define RAW_DATA_SIZE (PAGE_SIZE * 32)
static struct cyttsp5_core_commands *cmd;

#define TP_CONFIG_FILE_PATH "/system/etc/tp_test_parameters/"

extern struct device *gdev;
extern void cyttsp5_start_wd_timer(struct cyttsp5_core_data *cd);
extern void cyttsp5_stop_wd_timer(struct cyttsp5_core_data *cd);

int cyttsp5_command_response_cyttsp5(struct device *dev,u8 *buf)
{
    int ret = -1;
    ssize_t num_read;
    struct cyttsp5_device_access_data *dad = cyttsp5_get_device_access_data(dev);

    mutex_lock(&dad->sysfs_lock);
    if (!dad->status) {
        goto error;
    }

    num_read = dad->response_length;

    memcpy(buf,dad->response_buf,num_read);
    if (num_read > 2)/* when length <= 2 we can't get any data*/
        ret = num_read;
error:
    mutex_unlock(&dad->sysfs_lock);
    return ret;
}

int cyttsp5_send_command_cyttsp5(struct device *dev,char *buf)
{
    struct cyttsp5_device_access_data *dad
        = cyttsp5_get_device_access_data(dev);
    ssize_t length = 0;
    int rc = -1;

    mutex_lock(&dad->sysfs_lock);
    dad->status = 0;
    dad->response_length = 0;

    length = cyttsp5_ic_parse_input(dev, buf, strlen(buf), dad->ic_buf,
            CY_MAX_PRBUF_SIZE);
    if (length <= 0) {
        TS_LOG_ERR("%s: %s Group Data store\n", __func__,"Malformed input for");
        goto exit;
    }

    /* write ic_buf to log */
    cyttsp5_pr_buf(dev, dad->ic_buf, length, "ic_buf");

    rc = cmd->nonhid_cmd->user_cmd(dev, 1, CY_MAX_PRBUF_SIZE,
            dad->response_buf, length, dad->ic_buf,
            &dad->response_length);
    if (rc) {
        dad->response_length = 0;
        TS_LOG_ERR("%s: Failed to store command\n", __func__);
    } else {
        dad->status = 1;
    }
    TS_LOG_DEBUG("%s send cmd  ok.\n",__func__);

exit:
    mutex_unlock(&dad->sysfs_lock);
    TS_LOG_DEBUG("%s: return rc = %d\n", __func__, rc);
    return rc;
}



static int cyttsp5_get_tp_config_file(struct device *dev, char *parameter_file, char *config_file)
{
    int error = 0;
    u8 panel_id = 0;
    int length = 0;
    int i = 0;

    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    const char *product_name = cd->cpdata->product_name;
    const char *chip_name = cd->cpdata->chip_name;

    if(parameter_file == NULL || config_file == NULL) {
        TS_LOG_ERR("%s: paramaters is invalid\n",
                __func__);
        return -EINVAL;
    }

    cmd = cyttsp5_get_commands();
    if (!cmd) {
        error = -EINVAL;
        TS_LOG_ERR("%s Failed to cyttsp5_get_commands.\n",__func__);
        goto out;
    };
 
    error = cmd->nonhid_cmd->get_panel_id(dev, 1, &panel_id);
    if (error < 0) {
        error = -EINVAL;
        TS_LOG_ERR("%s Failed to get panel id.\n",__func__);
        goto out;
    }
    TS_LOG_INFO("%s, panel_id = %d\n", __func__, panel_id);
    TS_LOG_INFO("%s, product_name = %s,chip_name=%s\n", __func__, product_name,chip_name);
    //get tp parameter_file        liszt_parameters.csv
    strncat(parameter_file,TP_CONFIG_FILE_PATH, strlen(TP_CONFIG_FILE_PATH));
    strncat(parameter_file,product_name,strlen(product_name));
    strncat(parameter_file,"_",strlen("_"));
    strncat(parameter_file,"parameters.csv",strlen("parameters.csv"));
    TS_LOG_INFO("%s, parameters = %s\n", __func__, parameter_file);

    //get tp config_file    liszt_truly_input_format.csv
    strncat(config_file,TP_CONFIG_FILE_PATH, strlen(TP_CONFIG_FILE_PATH));
    strncat(config_file,product_name,strlen(product_name));
    strncat(config_file,"_",strlen("_"));

    length = sizeof(hw_panel_info)/sizeof(struct cyttsp5_panel_info);
    for(i = 0; i < length; i++) {
        if(panel_id == hw_panel_info[i].panel_id) {
            error = strncasecmp(hw_panel_info[i].product_name, product_name, strlen(hw_panel_info[i].product_name));
            if(error == 0) {
                error = strncasecmp(hw_panel_info[i].chip_name, chip_name, strlen(hw_panel_info[i].chip_name));
                if(error == 0) {
                    strncat(config_file,hw_panel_info[i].id2str,strlen(hw_panel_info[i].id2str));
                }
            }
        }
    }
 
    strncat(config_file,"_",strlen("_"));
    strncat(config_file,"input_format.csv",strlen("input_format.csv"));

    TS_LOG_INFO("%s, config_file = %s\n", __func__, config_file);
    error = 0;
out:
    return error;
}


     
int cyttsp5_cm_cp_test(struct seq_file *m, void *v)
{
    int error = 0;
    struct device *dev = gdev;
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    char parameter_filename[CONFIG_NAME_LENGTH] = {0};
    char config_filename[CONFIG_NAME_LENGTH] = {0};
    struct file *config_file = NULL;
    struct file *parameter_file = NULL;
    bool run_cm_test = true, run_cp_test = true;    
    bool cm_test_pass = 1;
    bool cp_test_pass = 1; 
    int vdda = 2800;    
    int cp_ret=0;
    int cm_ret=0;
    mm_segment_t fs;

    if(atomic_read(&mmi_test_status_cyttsp5)){
        TS_LOG_ERR("%s cm_cp_test already has been called.\n",__func__);
        seq_printf(m, "1F;-software_reason", strlen("1F;-software_reason"));
        return -1;
    }

    atomic_set(&mmi_test_status_cyttsp5, 1);
    TS_LOG_INFO("%s, cm_cp_test proc buffer size:%u\n", __func__, (unsigned int)m->size);
    if(m->size <= RAW_DATA_SIZE/4) {
        m->count = m->size;
        goto out;
    }
    error = cyttsp5_get_tp_config_file(dev,parameter_filename, config_filename);
    if(error < 0){
        TS_LOG_ERR("%s, get tp config failed\n",__func__);
        seq_printf(m, "1F;-software_reason", strlen("1F;-software_reason"));
        goto out;
    }
    //open config name
    fs =get_fs();
    set_fs(KERNEL_DS);
    config_file = filp_open(config_filename, O_RDONLY, 0);
    if (IS_ERR(config_file)){
        TS_LOG_ERR("%s,  filp_open error, file name is %s.\n", __func__, config_filename);
        error = -1;
        seq_printf(m, "1F;-software_reason", strlen("1F;-software_reason"));
        goto exit_open_config_file;
    }
    TS_LOG_DEBUG("%s,  filp_open %s success.\n", __func__, config_filename);

    parameter_file = filp_open(parameter_filename, O_RDONLY, 0);
    if (IS_ERR(parameter_file)){
        TS_LOG_ERR("%s,  filp_open error, file name is %s.\n", __func__, parameter_filename);
        error = -1;
	seq_printf(m, "1F;-software_reason", strlen("1F;-software_reason"));
        goto exit_open_parameter_file;
    }
    TS_LOG_DEBUG("%s,  filp_open %s success.\n", __func__, parameter_filename);
    cyttsp5_stop_wd_timer(cd);

   seq_printf(m, "1P-", strlen("1P-") );

    error = cm_cp_test_run(NULL, parameter_file, config_file,
                        m, vdda, run_cm_test, run_cp_test,
                        &cm_test_pass, &cp_test_pass);

    if (run_cm_test){
          if (cm_test_pass){
              TS_LOG_INFO("%s:PASS: Cm test\n" ,__FUNCTION__ );
              cm_ret = TP_PASS;
          } else {
              TS_LOG_ERR("%s:FAIL: Cm test\n", __FUNCTION__ );
              cm_ret = TP_FAIL;
          }
    }
    if (run_cp_test){
         if (cp_test_pass){
             TS_LOG_INFO("%s:PASS: Cp test\n" ,__FUNCTION__ );
             cp_ret = TP_PASS;
         }else {
             TS_LOG_ERR("%s:FAIL: Cp test\n", __FUNCTION__ );
             cp_ret = TP_FAIL;
        }
    }
    if( (error == 0) && cm_ret &&cp_ret) {
        TS_LOG_INFO("%s, cm_cp_test success\n", __func__);
    }
    else {
        TS_LOG_ERR("%s, cm_cp_test failed\n", __func__);
    }

    cyttsp5_start_wd_timer(cd);

    filp_close(parameter_file, NULL);
exit_open_parameter_file:
    filp_close(config_file, NULL);
exit_open_config_file:
    set_fs(fs);
out:
    atomic_set(&mmi_test_status_cyttsp5, 0);
    TS_LOG_INFO("%s, cm_cp_test proc done\n", __func__);
    return error;
}

static int cyttsp5_cm_cp_open(struct inode *inode, struct file *file)
{
    return single_open(file, cyttsp5_cm_cp_test, NULL);
}

static const struct file_operations cyttsp5_cm_cp_proc_fops = {
    .open		 = cyttsp5_cm_cp_open,
    .read		 = seq_read,
    .llseek 	   = seq_lseek,
    .release	= single_release,
};

void cyttsp5_mmitest_procfs_create(void)
{
    if (!proc_mkdir("touchscreen", NULL)){
        TS_LOG_ERR("%s: Error, failed to creat procfs.\n",__func__);
        return;
    }
    proc_create("touchscreen/tp_capacitance_data", 0444, NULL, &cyttsp5_cm_cp_proc_fops);
    return;
}


