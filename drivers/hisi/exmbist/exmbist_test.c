/********************************************************************************
 File name  : exmbist_test.c
 Version    : 1.00
 Author     :
 Description: exmbist module
********************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/ctype.h>

#include "soc_ddrc_dmc_interface.h"
#include "exmbist_test.h"
#include "exmbist_wrap_top.h"
#include "exmbist_api_drv.h"

static char *g_Conf_file = "/system/bin/exmbist_conf.cfg";
char *g_Log_file = "/data/exmbist_result.log";
extern int exmbist_init_flag;
extern ExmCtx g_austin_exmbist;
void __iomem *g_exm_reg_base;
struct timeval g_tv0, g_tv1;
int exmbist_break = 0;

struct exm_fsm_state g_exm_cur_fsm_state ;
char g_user_input_buf[256];

extern unsigned int hisi_pmic_reg_read (int reg_addr);
extern void hisi_pmic_reg_write(int addr, int val);

static ssize_t exmbist_result_show(struct kobject *obj, struct kobj_attribute *atty, char *buf);
static ssize_t exmbist_result_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);
static ssize_t exmbist_entry_show(struct kobject *obj, struct kobj_attribute *atty, char *buf);
static ssize_t exmbist_entry_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

static struct kobj_attribute exmbist_result_attribute =
    __ATTR(test_result, 0666, exmbist_result_show, exmbist_result_store);

static struct kobj_attribute exmbist_entry_attribute =
    __ATTR(test_entry, 0666, exmbist_entry_show, exmbist_entry_store);

static struct attribute *attrs[] = {
    &exmbist_entry_attribute.attr,
    &exmbist_result_attribute.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject  *exmbist_adapter_kobj;

//PMIC_HRST_REG2_ADDR  bit0用作是否需要预留内存空间; 
//启动测试时apk配置bit0为1，重启单板，进入xloader, xloader预留空间后清楚该标志位;再次重启预留空间恢复

struct ddr_test_func_def fpga_ddr_test_func[] =
{
	{(DDR_TEST_FUNC_UNIT)exm_default_conf_file, func_name_me(exm_default_conf_file)},
	{(DDR_TEST_FUNC_UNIT)exm_parse_conf_file, func_name_me(exm_parse_conf_file)},
	{(DDR_TEST_FUNC_UNIT)exm_set_test_loop_cnt, func_name_me(exm_set_test_loop_cnt)},	
    {(DDR_TEST_FUNC_UNIT)exm_init, func_name_me(exm_init)},
	{(DDR_TEST_FUNC_UNIT)exm_set_cmd, func_name_me(exm_set_cmd)},
	{(DDR_TEST_FUNC_UNIT)exm_rank_algo_run, func_name_me(exm_rank_algo_run)},
	{(DDR_TEST_FUNC_UNIT)exm_all_space_algo_run, func_name_me(exm_all_space_algo_run)},
	{(DDR_TEST_FUNC_UNIT)exm_close, func_name_me(exm_close)},
	{(DDR_TEST_FUNC_UNIT)exm_set_pmu_enable, func_name_me(exm_set_pmu_enable)},
	/*u can add new test function here*/
};

unsigned int num_of_func_list = NELEMENTS(fpga_ddr_test_func);
static unsigned char ddr_density_buf[10];

struct mmc_hw_test_debugfs_entry {
    struct dentry *exm_test_entry;
	struct dentry *exm_test_result_entry;
	int status;
	
} g_exm_test_debugfs_entries = {NULL, NULL};

extern exmbist_uint32 exm_util_wait_bist_pass (ExmCtx * ctx);

//sysfs file node
static ssize_t exmbist_entry_show(struct kobject *obj, struct kobj_attribute *atty, char *buf)
{
    return 0;
}
static ssize_t exmbist_entry_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    char input_buf[256] = {0};

    printk(KERN_ERR "exm_test_write!!!\n");

    if (count >= sizeof(input_buf))
    {
        return -EINVAL;
    }

    memcpy(input_buf, buf, count);
    input_buf[count] = '\0';
    
    if (g_exm_cur_fsm_state.exmbist_thread != NULL)
    {
        memcpy(g_user_input_buf, input_buf, count);
        printk(KERN_ERR "wakeup exmbist_thread!!!\n");
        wake_up_process(g_exm_cur_fsm_state.exmbist_thread);
    }

    return count;
}

static ssize_t exmbist_result_show(struct kobject *obj, struct kobj_attribute *atty, char *buf)
{
    snprintf(buf, strlen(buf), "%d", g_exm_cur_fsm_state.final_result);
    printk(KERN_ERR "exm_test_result_read %s !!!\n" ,buf);

    return strlen(buf);
}

static ssize_t exmbist_result_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    return 0;
}

static int  exmbist_test_kobj(void)
{
    int retval = 0;
    
    printk("create exmbist_test_entry\n");
    
    exmbist_adapter_kobj = kobject_create_and_add("exmbist_test", kernel_kobj);
    if(!exmbist_adapter_kobj)
    {
        printk("exmbist_test kobj create error\n");
        return -ENOMEM;
    }
    retval = sysfs_create_group( exmbist_adapter_kobj, &attr_group);
    if(retval)
    {
        kobject_put(exmbist_adapter_kobj);
    }
    return retval;
}

int exm_set_pmu_enable(void)
{
    unsigned int pmic_reg_value;

    pmic_reg_value = hisi_pmic_reg_read(0x103);
    pmic_reg_value = pmic_reg_value | 0x1;
    hisi_pmic_reg_write(0x103, pmic_reg_value);

    printk("exm_set_pmu_enable is 0x%x\n", pmic_reg_value);

    return 0;
}

int exm_set_exmbist_break(void)
{
	exmbist_break = 1;
	
	return 0;
}

int exm_ddr_density_get(void)
{
	int density;

	density = (int)simple_strtol(ddr_density_buf, NULL, 0);
	printk("density is 0x%x\n", density);
	
	return density;
}

static int __init early_parse_ddr_density_cmdline(char *arg)
{
	int len = 0;

	memset(ddr_density_buf, 0, sizeof(ddr_density_buf));
	if (arg) {
		len = strlen(arg);

		if (len > sizeof(ddr_density_buf)) {
			len = sizeof(ddr_density_buf);
		}
		memcpy(ddr_density_buf, arg, len);
	} else {
		printk("%s : arg is NULL\n", __func__);
	}

	return 0;
}
early_param("ddr_density", early_parse_ddr_density_cmdline);


static int exmbist_parse_dt(struct platform_device *pdev)
{
    struct device_node *np = pdev->dev.of_node;
    unsigned int start_addr = 0;
    unsigned int end_addr = 0;

    if (of_property_read_u32(np, "start_addr", &start_addr)) {
        printk("hisi,start_addr not found\n");
		return EXM_ERROR;
    }

    //if (of_property_read_u32(np, "hisi,end_addr", &end_addr)) {
    if (of_property_read_u32(np, "end_addr", &end_addr)) {
        printk("hisi,end_addr not found\n");
		return EXM_ERROR;
    }

    printk("dts start_addr = 0x%x \n", start_addr);
    printk("dts end_addr   = 0x%x \n", end_addr);
    exm_set_phy_addr_range(start_addr, end_addr);

    return EXM_OK;
}

#if 0
unsigned int exmbist_log_createfile(char* g_Log_file)
{   
	mm_segment_t old_fs;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

    if(NULL != g_exm_cur_fsm_state.mbist_log_file)
    {
        filp_close(g_exm_cur_fsm_state.mbist_log_file, NULL);
    	set_fs(old_fs);
    }
    g_exm_cur_fsm_state.mbist_log_file = NULL;

	printk(KERN_ERR "exmbist log file %s open\n", g_Log_file);
	g_exm_cur_fsm_state.mbist_log_file = filp_open(g_Log_file, O_CREAT | O_RDWR, 0644);
    if(IS_ERR(g_exm_cur_fsm_state.mbist_log_file))
	{
		printk(KERN_ERR "exmbist log file 0x%x\n", (unsigned long)(g_exm_cur_fsm_state.mbist_log_file));
		printk(KERN_ERR "exmbist log file %s open failed\n", g_Log_file);
		return EXM_ERROR;
    }

    set_fs(old_fs);	
	printk(KERN_ERR "exmbist log file %s open success!\n", g_Log_file);

    return EXM_OK;
}

unsigned int exmbist_util_log_closefile(struct file* mbist_log_file)
{
    unsigned int uiret = EXM_OK;
	mm_segment_t old_fs;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

    if(NULL != mbist_log_file)
    {
		/* Close the file */
		filp_close(mbist_log_file, NULL);
		set_fs(old_fs);
    }
	
    mbist_log_file = NULL;
    return uiret;
}

unsigned int exmbist_util_log_record(struct file* mbist_log_file, char *szFun, unsigned int ulLogLevel, const char * format,...)
{
    va_list   argument;
	char temp_buf[1024] = {0};
	int len = 0;
	ssize_t ret;
    mm_segment_t  fs = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);

	va_start(argument, format );
    len = vsnprintf(temp_buf, 1024-1, format, argument);
    va_end(argument);

#if 0
    if(ERR == len)
    {
        printk(KERN_ERR "\r\n exmbist_util_log_record: vnsprintf return error\r\n");
        return EXM_ERROR;
    }
#endif

	ret = vfs_write(mbist_log_file, temp_buf, sizeof(temp_buf), &mbist_log_file->f_pos);
	if (ret != len) 
	{
		printk(KERN_ERR "%s write to log file exception.\n" , temp_buf);
		set_fs(fs);
        return EXM_ERROR;
	}

    set_fs(fs);
	return EXM_OK;
}
#endif

void exm_log_record(char* log_file, char* buf)
{
	struct file *fp = NULL;
	mm_segment_t oldfs = get_fs();
	size_t len = strlen(buf);
	ssize_t ret;
	
	//printk(KERN_ERR "START exm_log_record.\n");
	
	set_fs(KERNEL_DS);

	fp = filp_open(log_file, O_CREAT|O_APPEND|O_RDWR, 0666);
	if (IS_ERR(fp)) {
		printk(KERN_ERR "%s open log file %s error", __func__, log_file);
		goto file_out;
	}

	if (fp->f_pos < (4*1024*1024L)) 
	{  //4M max
		ret = vfs_write(fp, buf, len, &fp->f_pos);
		if (ret != len) 
		{
			printk(KERN_ERR "write to log file exception.\n");
			goto file_out;
		}
		printk(KERN_ERR "write len %lu  %s to log file ok.\n", len, buf);
	}
	else
	{
		printk(KERN_ERR "%s log file %s is larger than 4MB", __func__, log_file);
		filp_close(fp, NULL);
	}

file_out:
	if (!IS_ERR(fp))
	{
		filp_close(fp, NULL);
	}
	
	set_fs(oldfs);

	return;
}

/* some basic functions */
unsigned exm_hex2unsigned(const char *x)
{
    unsigned n = 0;

    while(*x) {
        switch(*x) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            n = (n << 4) | ((unsigned char)(*x) - '0');
            break;
        case 'a': case 'b': case 'c':
        case 'd': case 'e': case 'f':
            n = (n << 4) | ((unsigned char)(*x) - 'a' + 10);//lint !e834
            break;
        case 'A': case 'B': case 'C':
        case 'D': case 'E': case 'F':
            n = (n << 4) | ((unsigned char)(*x) - 'A' + 10);//lint !e834
            break;
        default:
            return n;
        }
        x++;
    }

    return n;
}


void exm_args_parse(const char* sub_cmd, char*  func_name, unsigned int* arg)
{
	char* temp_cmd = (char*)sub_cmd;
	unsigned int i;
	unsigned int func_name_len = 0;

	/*function name*/
	while (isspace(*temp_cmd))
	{
		temp_cmd++;
	}
	
	strcpy(func_name, temp_cmd);

	while(!isspace(*temp_cmd)) 
	{
		func_name_len++;
		temp_cmd++;
	}
	func_name[func_name_len+1] = '\0';

	for (i=0; i < 4; i++) 
	{
		while (isspace(*temp_cmd))
			temp_cmd++;
		
		if (*temp_cmd == '0' && (*(temp_cmd+1) == 'x' || *(temp_cmd+1) == 'X'))
			temp_cmd += 2;
		
		arg[i] = exm_hex2unsigned(temp_cmd);
		
		while (*temp_cmd != ' ' && *temp_cmd != '\0')
			temp_cmd++;
	}

	printk(KERN_ERR "exm_args_parse func_name %s\n", func_name);
}

static int exm_read_line(struct file *fp, char *buffer, loff_t *pos)
{
    int result = -1;
    int bytes_read = 0;

    while ((result = vfs_read(fp, &buffer[bytes_read], 1, pos)) == 1) {
        if (buffer[bytes_read] == '\r') {
            buffer[bytes_read] = '\0';
            bytes_read++;
        } else if (buffer[bytes_read] == '\n') {
            buffer[bytes_read] = '\0';
            bytes_read++;
            break;
        }
        bytes_read++;
    }
	/* Return the number of bytes read */
    if (result == -1)
        return result;
    else
        return bytes_read;
} /* readline */

int exm_test_func_parse(char* func_name, unsigned int len, unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
	unsigned int i, ret;

	//printk(KERN_ERR "num_of_func_list %d\n", num_of_func_list);
	for (i=0; i<num_of_func_list; i++) 
	{
		//printk(KERN_ERR "func_name %s  fpga_ddr_test_func[%d].test_func_name %s  len %d\n", func_name, i, fpga_ddr_test_func[i].test_func_name, len);
		if (0 == strncmp(func_name, fpga_ddr_test_func[i].test_func_name, len)) 
		{
			//printk(KERN_ERR "func_name %s ==== fpga_ddr_test_func[%d].test_func_name %s  len %d\n", func_name, i, fpga_ddr_test_func[i].test_func_name, len);
			break;
		}
	}

	if (i >= num_of_func_list) 
	{
		printk(KERN_ERR "can't find test func %s\n", func_name);
		return EXM_ERROR;
	}

	//printk(KERN_INFO "start function %s\n", fpga_ddr_test_func[i].test_func_name);
	//printk(KERN_INFO "arg0: 0x%x\narg1: 0x%x\n", arg0, arg1);
	//printk(KERN_INFO "arg2: 0x%x\narg3: 0x%x\n", arg2, arg3);

	ret = (*(fpga_ddr_test_func[i].test_func))(arg0, arg1, arg2, arg3);
	//printk(KERN_ERR "test_func : func %s test %s\n", fpga_ddr_test_func[i].test_func_name, (ret==EXM_OK) ? "success":"fail");

	return ret;
}

void exm_set_phy_addr_range(unsigned int phy_addr_range_min, unsigned int phy_addr_range_max)
{
	g_exm_cur_fsm_state.phy_addr_range_max = phy_addr_range_max;
	g_exm_cur_fsm_state.phy_addr_range_min = phy_addr_range_min;
}

unsigned int exm_get_ap_addr_min(void)
{
	//printk(KERN_ERR "phy_addr_range_min address 0x%x\n", g_exm_cur_fsm_state.phy_addr_range_min);
	return g_exm_cur_fsm_state.phy_addr_range_min;
}

unsigned int exm_get_ap_addr_max(void)
{
	//printk(KERN_ERR "phy_addr_range_max address 0x%x\n", g_exm_cur_fsm_state.phy_addr_range_max);
	return g_exm_cur_fsm_state.phy_addr_range_max;
}

void __iomem * exm_get_reg_base(void)
{
	return g_exm_reg_base;
}

unsigned int exm_get_exmbist_addr_min(void)
{
	//printk(KERN_ERR "phy_addr_range_min address 0x%x\n", g_exm_cur_fsm_state.phy_addr_range_min);
	return ap_addr_to_exm_addr(g_exm_cur_fsm_state.phy_addr_range_min);
}

unsigned int exm_get_exmbist_addr_max(void)
{
	//printk(KERN_ERR "phy_addr_range_max address 0x%x\n", g_exm_cur_fsm_state.phy_addr_range_max);
	return ap_addr_to_exm_addr(g_exm_cur_fsm_state.phy_addr_range_max);
}

#if 0
unsigned int exm_get_exmbist_addr_max_ex(void)
{
	unsigned int ch_num;
	DDR_TYPE ddr_type;
	unsigned int ch_test_range;
	
	ddr_type = get_ddr_version();

	printk("ddr type is %d\n", ddr_type);

	if (DRAM_TYPE_LPDDR3 == ddr_type)
	{
		ch_num = 2;
	}
	else if (DRAM_TYPE_LPDDR4 == ddr_type)
	{
		ch_num = 4;
	}

	ch_test_range = (exm_get_ap_addr_max()-exm_get_ap_addr_min())/ ch_num;

	

		
}
#endif

int exm_set_test_loop_cnt(unsigned int loop_cnt)
{
	g_exm_cur_fsm_state.loop_cnt = loop_cnt;
	return EXM_OK;
}

int exm_parse_conf_file(void)
{
	struct file* fp = NULL;
	mm_segment_t old_fs;
    char input_buf[256] = {0};
	char func_name[256] = {0};
	loff_t pos = 0;
	loff_t loop_start_pos  = 0;
    int bytes_read = 0;
	int ret = EXM_OK;
	unsigned int arg[4] = {0};
	int loop_cnt = 0;
	unsigned int error_stop = 0;

    exm_ddr_self_adapter();
    
	fp = filp_open(g_Conf_file, O_RDONLY, 0644);
    if(IS_ERR(fp))
	{
		printk(KERN_ERR "Conf file %s open failed\n", g_Conf_file);
		return EXM_ERROR;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
	do_gettimeofday(&g_tv0);

	for(;;)
	{
		do_gettimeofday(&g_tv1);
		if (g_tv1.tv_sec - g_tv0.tv_sec > 2400)  //40mins
		{
			printk(KERN_ERR "time is up\n");
			break;
		}
		
		memset(input_buf, 0, 256);
		//printk(KERN_ERR "Conf file pos %d\n", pos);
		bytes_read = exm_read_line(fp, input_buf, &pos);
		if (bytes_read == -1)
		{
			printk(KERN_ERR "Conf file %s read EOF or error\n", g_Conf_file);
			break;
		}
		
		if(strlen(input_buf) == 1 || strlen(input_buf) == 0)
		{
			//printk(KERN_ERR "exm_read_line NULL line\n");
			break;
		}
			
		exm_args_parse(input_buf, func_name, arg);		// parse debugfs input parse
		if (!strncmp(func_name, EXM_LOOP_START_CMD, strlen(EXM_LOOP_START_CMD)))	//loop cmd
		{
			loop_cnt = arg[0];
			g_exm_cur_fsm_state.loop_cnt = loop_cnt;
			loop_start_pos = pos;
			//printk(KERN_ERR "loop count %d  loop_start_pos %d\n", loop_cnt, loop_start_pos);
			continue;
		}

		if (!strncmp(func_name, EXM_LOOP_END_CMD, strlen(EXM_LOOP_END_CMD)))	//loop cmd
		{
			//printk(KERN_ERR "cur loop count %d\n", loop_cnt);
			if (loop_cnt > 0)
			{
				vfs_llseek(fp, loop_start_pos, SEEK_SET);
				pos = fp->f_pos;
				//printk(KERN_ERR "return to loop_start_pos %d\n", loop_start_pos);
			}
			loop_cnt--;
			msleep(100);
			continue;
		}

		if (!strncmp(func_name, EXM_OCCUR_ERROR_STOP, strlen(EXM_OCCUR_ERROR_STOP))	)
		{
			error_stop = EXM_ERROR_STOP;
			continue;
		}
		
		ret = exm_test_func_parse(func_name, strlen(func_name)-1, arg[0], arg[1], arg[2], arg[3]);
		if (ret != EXM_OK)
		{
			if (ret == 14)
			{
                  //printk(KERN_ERR "qxq14\n");
			      break;  
			}
		    
			if (error_stop == EXM_ERROR_STOP)
			{
				//printk(KERN_ERR "exmbist function  %s excuted fail, test will stop\n", func_name);
				g_exm_cur_fsm_state.final_result = EXM_ERROR;
				break;
			}
			else
			{
				//printk(KERN_ERR "exmbist function  %s excuted fail ,test will continue!\n", func_name);
				g_exm_cur_fsm_state.final_result = EXM_ERROR;
				continue;
			}
		}

		//printk(KERN_INFO "exmbist function  %s excuted EXM_OK \n", func_name);
		memset(func_name, 0, 256);
		msleep(20);
	}

    /* Close the file */
    filp_close(fp, NULL);
    set_fs(old_fs);
	//printk(KERN_ERR "exmbist closed config file \n");

	return EXM_OK;
}

int exm_default_conf_file(void)  //fs存在问题 需要检视
{
	struct file* fp = NULL;
	mm_segment_t old_fs;
    char input_buf[256] = {0};
	char func_name[256] = {0};
	loff_t pos;
    int bytes_read = 0;
	int ret;
	unsigned int arg[4] = {0};
	unsigned int loop_cnt = 0;
	
	fp = filp_open(g_Conf_file, O_RDONLY, 0644);
    if(IS_ERR(fp))
	{
		printk(KERN_ERR "Conf file %s open failed\n", g_Conf_file);
		return EXM_ERROR;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

	if (g_exm_cur_fsm_state.loop_cnt == 0)
	{
		g_exm_cur_fsm_state.loop_cnt = 1;
	}

	pos = 0;

	for (loop_cnt = 0; loop_cnt < g_exm_cur_fsm_state.loop_cnt; loop_cnt++)
	{
		//printk(KERN_ERR "loop_cnt %d  total_loop_cnt %d\n", loop_cnt, g_exm_cur_fsm_state.loop_cnt);
		vfs_llseek(fp, 0, SEEK_SET);
		pos = fp->f_pos;
		for(;;)
		{
			memset(input_buf, 0, 256);
			bytes_read = exm_read_line(fp, input_buf, &pos);
			if (bytes_read == -1)
			{
				printk(KERN_ERR "Conf file %s read EOF or error\n", g_Conf_file);
				break;
			}

			if(strlen(input_buf) == 1 || strlen(input_buf) == 0)
			{
				printk(KERN_ERR "exm_read_line NULL line\n");
				break;
			}
			
			exm_args_parse(input_buf, func_name, arg);		// parse debugfs input parse

			ret = exm_test_func_parse(func_name, strlen(func_name)-1, arg[0], arg[1], arg[2], arg[3]);
			if (ret != EXM_OK)
			{
				printk(KERN_ERR "exmbist function  %s excuted fail \n", func_name);
				g_exm_cur_fsm_state.final_result = EXM_ERROR;
				break;
			}

			printk(KERN_INFO "exmbist function  %s excuted EXM_OK \n", func_name);
			memset(func_name, 0, 256);
		}

		g_exm_cur_fsm_state.cur_loop_cnt = loop_cnt;
	}

	printk(KERN_ERR "exmbist close config file \n");
    /* Close the file */
    filp_close(fp, NULL);
    set_fs(old_fs);
	printk(KERN_ERR "exmbist closed config file \n");

	return EXM_OK;
	
}

int exm_resume_cont_exec(void)
{
	struct file* fp = NULL;
	mm_segment_t old_fs;
    char input_buf[256] = {0};
	char func_name[256] = {0};
	loff_t pos;
    int bytes_read = 0;
	int ret;
	unsigned int arg[4] = {0};
	unsigned int loop_cnt = 0;
	
	fp = filp_open(g_Conf_file, O_RDONLY, 0644);
    if(IS_ERR(fp))
	{
		printk(KERN_ERR "Conf file %s open failed\n", g_Conf_file);
		return EXM_ERROR;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

	pos = 0;
	
	for (loop_cnt = g_exm_cur_fsm_state.cur_loop_cnt; loop_cnt < g_exm_cur_fsm_state.loop_cnt; loop_cnt++)
	{
		vfs_llseek(fp, 0, SEEK_SET);
		pos = fp->f_pos;
		for(;;)
		{
			memset(input_buf, 0, 256);
			bytes_read = exm_read_line(fp, input_buf, &pos);
			if (bytes_read == -1)
			{
				printk(KERN_ERR "Conf file %s read EOF or error\n", g_Conf_file);
			    /* Close the file */
			    filp_close(fp, NULL);
			    set_fs(old_fs);
				break;
			}

			exm_args_parse(input_buf, func_name, arg);		// parse debugfs input parse

			ret = exm_test_func_parse(func_name, strlen(func_name)-1, arg[0], arg[1], arg[2], arg[3]);
			if (ret != EXM_OK)
			{
				printk(KERN_ERR "exmbist function  %s excuted fail \n", func_name);
				break;
			}

			printk(KERN_INFO "exmbist function  %s excuted EXM_OK \n", func_name);

			vfs_llseek(fp, pos, SEEK_SET);
		}

		g_exm_cur_fsm_state.cur_loop_cnt = loop_cnt;
	}

    /* Close the file */
    filp_close(fp, NULL);
    set_fs(old_fs);

	return EXM_OK;
	
}

static int exm_test_show(struct seq_file *m, void *v)
{
	return 0;
}

static int exm_test_open(struct inode *inode, struct file *file)
{
	return single_open(file, exm_test_show, inode->i_private);

	//struct exm_fsm_state* fsm_state = inode->i_private;
	//file->private_data = fsm_state;
}

static ssize_t exm_test_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
    char input_buf[256] = {0};
	
	//printk(KERN_ERR "exm_test_write!!!\n");

    if (count >= sizeof(input_buf))
    {
        return -EINVAL;
    }
	
	if (copy_from_user(input_buf, buf, count))
    {
        return -EFAULT;
    }
	
	input_buf[count] = '\0';
	if (g_exm_cur_fsm_state.exmbist_thread != NULL)
	{
		memcpy(g_user_input_buf, input_buf, count);
		printk(KERN_ERR "wakeup exmbist_thread!!!\n");
		wake_up_process(g_exm_cur_fsm_state.exmbist_thread);
	}
	
	return count;
}

static const struct file_operations exm_test_fops_test = {
    .open		= exm_test_open,
    .read		= seq_read,
    .write		= exm_test_write,
    .llseek		= seq_lseek,
    .release	= single_release,
};

//static int exm_result_show(struct seq_file *m, void *v)
//{
//	return 0;
//}

static int exm_test_result_open(struct inode *inode, struct file *filp)
{
	struct exm_fsm_state* fsm_state = inode->i_private;

	filp->private_data = fsm_state;

	printk(KERN_ERR "exm_test_result_open!!!\n");
	return 0;
	//return single_open(filp, exm_test_show, inode->i_private);
}

static ssize_t exm_test_result_read(struct file *filp, char __user *ubuf,
				     size_t cnt, loff_t *ppos)
{
    char buf[64] = {0};
	struct exm_fsm_state *fsm_state = filp->private_data;

	if (!fsm_state)
		return cnt;

    snprintf(buf, sizeof(buf), "%d", fsm_state->final_result);
	printk(KERN_ERR "exm_test_result_read %s !!!\n" ,buf);
	
    return simple_read_from_buffer(ubuf, cnt, ppos,
            buf, sizeof(buf));

}

static ssize_t exm_test_result_write(struct file *filp,
				      const char __user *ubuf, size_t cnt,
				      loff_t *ppos)
{
	struct exm_fsm_state *fsm_state = filp->private_data;
	int value;

	if (!fsm_state){
		return cnt;
	}

	(void)sscanf(ubuf, "%d", &value);
	
	fsm_state->final_result = value;
	printk(KERN_ERR "exm_test_result_write %s !!!\n" ,ubuf);

	return cnt;
}

static const struct file_operations exm_test_result_fops = {
	.open		= exm_test_result_open,
	.read		= exm_test_result_read,
	.write		= exm_test_result_write,
};

void exm_add_debugfs(void)
{
	struct dentry *root;
	const char* exm_debugfs_dir = "exmbist";

	root = debugfs_create_dir(exm_debugfs_dir, NULL);
	if (IS_ERR(root))
	{
		/* Don't complain -- debugfs just isn't enabled */
		return;
	}
	
	if (!root)
	{
		/* Complain -- debugfs is enabled, but it failed to
		 * create the directory. */
		goto err_root;
	}
	
	g_exm_test_debugfs_entries.exm_test_entry = debugfs_create_file("test_entry", S_IFREG|S_IRWXU|S_IRGRP|S_IROTH, root, &g_exm_cur_fsm_state, &exm_test_fops_test);
	if (!g_exm_test_debugfs_entries.exm_test_entry)
	{
		goto err_node;
	}

	g_exm_test_debugfs_entries.exm_test_result_entry = debugfs_create_file("test_result", S_IRUSR, root, &g_exm_cur_fsm_state, &exm_test_result_fops);
	if (!g_exm_test_debugfs_entries.exm_test_result_entry)
	{
		goto err_node;
	}

	return;

err_node:
	debugfs_remove_recursive(root);
	
err_root:
	printk(KERN_ERR "failed to initialize exmbist debugfs\n");
	
}

void exmbist_process(void)
{
	char func_name[256] = {0};
	unsigned int arg[4] = {0};
	unsigned int ret;

    printk(KERN_ERR "exmbist_process wakeup.\n");

	do
	{
		if ((g_exm_cur_fsm_state.cur_loop_cnt < g_exm_cur_fsm_state.loop_cnt) && (g_exm_cur_fsm_state.exm_hold == EXM_HOLD_UP))
		{
            printk(KERN_ERR "exmbist_process wakeup exm_resume_cont_exec.\n");
            printk(KERN_ERR "loop_cnt %d  cur_loop_cnt %d.\n", g_exm_cur_fsm_state.loop_cnt, g_exm_cur_fsm_state.cur_loop_cnt);

			exm_resume_cont_exec();
		}
		else
		{
			exm_args_parse(g_user_input_buf, func_name, arg);		// parse debugfs input parse

			ret = exm_test_func_parse(func_name, strlen(func_name)-1, arg[0], arg[1], arg[2], arg[3]);
			
			if (ret != EXM_OK)
			{
				printk(KERN_ERR "exmbist function  %s excuted fail \n", func_name);
			}
			else
			{
				printk(KERN_INFO "exmbist function  %s excuted EXM_OK \n", func_name);
			}
		}
		set_current_state (TASK_INTERRUPTIBLE);
		schedule();
	}while (!kthread_should_stop());
}

static int exm_test_probe(struct platform_device *pdev)
{
	struct hi3650_exmbist_dev *d;
	struct resource *res = NULL;
	int ret = 0;

	printk(KERN_ERR "EXMBIST: ddr exmbist test probe \n");

	ret = exmbist_parse_dt(pdev);
	if (EXM_OK != ret)
	{
		printk("EXMBIST: ddr exmbist status disable \n");
		return ENODEV;
	}

	d = devm_kzalloc(&pdev->dev, sizeof(struct hi3650_exmbist_dev), GFP_KERNEL);
	if (!d) 
	{
		dev_err(&pdev->dev, "mem alloc failed for ddr exmbist data\n");
		return -ENOMEM;
	}

	/* NOTE: driver uses the static register mapping */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
	{
		printk("EXMBIST: platform_get_resource failed\n");
		return -EINVAL;
	}
	
	d->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!d->base)
	{
		return -EADDRNOTAVAIL;
	}

	g_exm_reg_base = d->base;

	d->platform_dev = &pdev->dev;

	spin_lock_init(&d->state_lock);

	//exm_ddr_self_adapter();
    exmbist_test_kobj();
    
	//exm_add_debugfs();


	//exm_log_record(g_Log_file, "SUCCESS"); //test
	
	//exmbist_log_createfile(g_Log_file);
	//exmbist_util_log_closefile(g_exm_cur_fsm_state.mbist_log_file);
	
    if(g_exm_cur_fsm_state.exmbist_thread == NULL)
	{
        g_exm_cur_fsm_state.exmbist_thread = kthread_create((void*)exmbist_process, NULL, "exmbist_process");
        if (IS_ERR(g_exm_cur_fsm_state.exmbist_thread)) 
		{
            printk("Create exmbist_process_thread failed\n");
            g_exm_cur_fsm_state.exmbist_thread = NULL;
            return EXM_ERROR;
        }
    }

	return ret;
}

static int exm_test_remove(struct platform_device *pdev)
{
	return 0;
}

static int exm_test_suspend(struct platform_device *pdev, pm_message_t state)
{
    pr_info("%s +\n", __func__);
	
    if (exmbist_init_flag)
	{
            printk(KERN_ERR "exm_test_suspend reset.\n");
            g_exm_cur_fsm_state.exm_hold = EXM_HOLD_UP;
	        (void) exm_drv_half_reset (&g_austin_exmbist);
	        msleep(10);
	        (void) exm_drv_half_reset (&g_austin_exmbist);
            //exm_algo_run(0x1, 1);
	}
	
	return EXM_OK;
}

static int exm_test_resume(struct platform_device *pdev)
{
	pr_info("%s -\n", __func__);

	if (exmbist_init_flag)
	{
        printk(KERN_ERR "exm_test_resume continue.\n");
        g_exm_cur_fsm_state.exm_hold = 0;

        //exm_algo_run(0x2, 1);

	if ((g_exm_cur_fsm_state.cur_loop_cnt < g_exm_cur_fsm_state.loop_cnt - 1)
			&& NULL != g_exm_cur_fsm_state.exmbist_thread)
		{
			wake_up_process(g_exm_cur_fsm_state.exmbist_thread);
		}
	}
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id hs_exmbist_of_match[] = {
	{ .compatible = "hisilicon,hi3650-exmbist", },
	{},
};
MODULE_DEVICE_TABLE(of, hs_exmbist_of_match);
#endif

static struct platform_driver hs_exmbist_test_driver = {
	.probe		= exm_test_probe,
	.remove		= exm_test_remove,
#ifdef CONFIG_PM
	.suspend 	= exm_test_suspend,
	.resume 	= exm_test_resume,
#endif
	.driver		= {
		.name	= "hi3650-exmbist",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hs_exmbist_of_match),
	},
};

module_platform_driver(hs_exmbist_test_driver);

MODULE_DESCRIPTION("hisi hi3650 exmbist test driver");
MODULE_ALIAS("platform:hi3650-exmbist");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

