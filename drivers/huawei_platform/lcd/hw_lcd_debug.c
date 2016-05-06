/* kernel\drivers\video\msm\mdss\lcd_hw_debug.c
 * this file is used by the driver team to change the
 * LCD init parameters by putting a config file in the mobile,
 * this function can make the LCD parameter debug easier.
 *
 * Copyright (C) 2010 HUAWEI Technology Co., ltd.
 *
 * Date: 2013/12/6
 * By vaibhav
 *
 */

#include "hw_lcd_debug.h"
#include <asm/uaccess.h>
#include <linux/ctype.h>
#define IS_VALID_CHAR(_ch) ((_ch >= '0' && _ch <= '9')?1:\
                            (_ch >= 'a' && _ch <= 'f')?1:(_ch >= 'A' && _ch <= 'F'))?1:0

#define HEX_BASE ((char)16)

#define VCC_LCDBIAS_NAME        "vcc_lcdbias"
#define VCC_LCD_VSN_NAME        "lcd_vsn"
#define VCC_LCD_VSP_NAME        "lcd_vsp"

static int g_mipiclk = 0;
static int g_mipiclk_enable = 0;
static int g_initcode_enable = 0;
static int g_initcode_flag = 0;
static int g_vsp_vsn_enable = 0;

struct dsi_panel_cmds g_panel_cmds;

static int g_panel_bias = 5400000;
static int g_panel_vsp = 5400000;
static int g_panel_vsn = 5400000;

/*esd debug*/
struct esd_debug g_esd_debug;

lcd_dbg_cmds g_cmd_list[] = {
	{LCD_DBG_MIPI_CLK, "set_mipi_clock"},
	{LCD_DBG_INIT_CODE, "set_init_param"},
	{LCD_DBG_PANEL_VSP_VSN, "set_panel_vsp_vsn"},
	{LCD_DBG_ESD_ENABLE, "lcd_esd_debug_enable"},
	{LCD_DBG_ESD_RECOVER_TEST, "lcd_esd_recover_test"},
	{LCD_DBG_ESD_RESET, "lcd_esd_debug_reset"},
	{LCD_DBG_ESD_BL_ENABLE, "lcd_esd_debug_bl_enable"},
	{LCD_DBG_ESD_BL_SET, "lcd_esd_debug_bl_set"},
	{LCD_DBG_ESD_CHECK_REG, "lcd_esd_debug_check_reg"},
	{LCD_DBG_ESD_CHECK_VALUE, "lcd_esd_debug_check_value"},
};
static char hex_char_to_value(char ch)
{
	switch (ch) {
		case 'a' ... 'f':
			ch = 10 + (ch - 'a');
			break;
		case 'A' ... 'F':
			ch = 10 + (ch - 'A');
			break;
		case '0' ... '9':
			ch = ch - '0';
			break;
	}
	return ch;
}

static int fget_dtsi_style(unsigned char* buf, int max_num, int fd, off_t* fd_seek)
{
	int cur_seek = *fd_seek;
	unsigned char ch = '\0';
	unsigned char last_char = 'Z';
	int j = 0;

	sys_lseek(fd, (off_t)0, 0);

	while (j < max_num) {
		if ((unsigned)sys_read(fd, &ch, 1) != 1) {
			HISI_FB_DEBUG("\nits end of file %d : len = %d\n",  __LINE__, j);
			return j;
		} else {
			if (!IS_VALID_CHAR(ch)) {
				last_char = 'Z';
				cur_seek++;
				sys_lseek(fd, (off_t)cur_seek, 0);
				continue;
			}

			if (last_char != 'Z') {
				/*two char value is possible like F0, so make it a single char*/
				--j;
				buf[j] = (buf[j] * HEX_BASE) + hex_char_to_value(ch);
				last_char = 'Z';
			} else {
				buf[j] = hex_char_to_value(ch);
				last_char = buf[j];
			}

			j++;
			cur_seek++;
			sys_lseek(fd, (off_t)cur_seek, 0);
		}
	}

	if (j >= max_num) {
		HISI_FB_DEBUG("Buffer is not enough\n");
		j *= -1;
	}

	*fd_seek = cur_seek;
	return j;
}

static bool lcd_resolve_dtsi_config_file(int fd, void** para_table, uint32_t* para_num)
{
	off_t fd_seek = 0;
	int num = 0;
	unsigned char* lcd_config_table = NULL;
	lcd_config_table = kzalloc(HW_LCD_CONFIG_TABLE_MAX_NUM, 0);

	if (NULL ==  lcd_config_table) {
		goto kalloc_err;
	}

	sys_lseek(fd, (off_t)0, 0);

	num = fget_dtsi_style(lcd_config_table, HW_LCD_CONFIG_TABLE_MAX_NUM, fd, &fd_seek);
	if (num <= 0) {
		HISI_FB_ERR("read failed with error return:%d\n", num);
		goto debug_init_read_fail;
	}

	*para_num = num;
	*para_table = lcd_config_table;
	return TRUE;

debug_init_read_fail:
	kfree(lcd_config_table);
	lcd_config_table = NULL;

kalloc_err:
	para_table = NULL;
	*para_num = 0;
	return FALSE;
}

bool lcd_debug_malloc_dtsi_para(void** para_table, uint32_t* para_num)
{
	int ret = 0 ;
	int fd = 0 ;
	void* table_tmp = NULL;
	int num_tmp = 0 ;
	mm_segment_t fs;

	if (NULL == para_table) {
		return FALSE;
	}

	fs = get_fs();     /* save previous value */
	set_fs (get_ds()); /* use kernel limit */

	fd = sys_open((const char __force*) HW_LCD_INIT_TEST_PARAM, O_RDONLY, 0);
	if (fd < 0) {
		HISI_FB_ERR("%s file doesn't exsit\n", HW_LCD_INIT_TEST_PARAM);
		set_fs(fs);
		return FALSE;
	}

	HISI_FB_DEBUG( "Config file %s opened. \n", HW_LCD_INIT_TEST_PARAM);

	//resolve the config file
	ret = lcd_resolve_dtsi_config_file(fd, &table_tmp, &num_tmp);
	sys_close(fd);
	set_fs(fs);

	*para_table = table_tmp;
	*para_num = (uint32_t)num_tmp;

	if (FALSE == ret) {
		HISI_FB_ERR("failed to read the init code into memory\n");
		return FALSE;
	}
	*para_table = table_tmp;

	HISI_FB_DEBUG("init code is copied into memory\n");
	return TRUE;
}

static void print_cmds(struct dsi_cmd_desc* cmds, int cnt)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < cnt; ++i) {
		HISI_FB_DEBUG("%02x ", cmds->dtype);
		HISI_FB_DEBUG("%02x ", cmds->vc);
		HISI_FB_DEBUG("%02x ", cmds->wait);
		HISI_FB_DEBUG("%02x ", cmds->waittype);
		HISI_FB_DEBUG("%02x ", cmds->dlen);
		for (j = 0; j < cmds->dlen; ++j) {
			HISI_FB_DEBUG("%02x ", cmds->payload[j]);
		}

		HISI_FB_DEBUG("\n");
		cmds++;
	}
}

int hw_parse_dsi_cmds(struct dsi_panel_cmds* pcmds)
{
	int blen = 0, len = 0;
	char* buf = NULL, *bp = NULL;
	struct dsi_ctrl_hdr* dchdr;
	struct dsi_cmd_desc* cmds_temp;
	int i = 0, cnt = 0;

	memset(pcmds, sizeof(struct dsi_panel_cmds), 0);

	if (!lcd_debug_malloc_dtsi_para((void**)&buf, &blen)) {
		HISI_FB_ERR("failed\n");
		return -ENOMEM;
	}

	/* scan dcs commands */
	bp = buf;
	len = blen;
	cnt = 0;
	while (len > sizeof(*dchdr)) {
		dchdr = (struct dsi_ctrl_hdr*)bp;
		//      dchdr->dlen = ntohs(dchdr->dlen);
		if (dchdr->dlen > len) {
			HISI_FB_ERR("dtsi cmd=%x error, len=%d, cnt=%d\n", dchdr->dtype, dchdr->dlen, cnt);
			return -ENOMEM;
		}
		bp += sizeof(*dchdr);
		len -= sizeof(*dchdr);
		bp += dchdr->dlen;
		len -= dchdr->dlen;
		cnt++;
	}

	if (len != 0) {
		HISI_FB_ERR("dcs_cmd=%x len=%d error!\n", buf[0], blen);
		kfree(buf);
		return -ENOMEM;
	}

	pcmds->cmds = kzalloc(cnt * sizeof(struct dsi_cmd_desc),
	                      GFP_KERNEL);
	if (!pcmds->cmds) {
		kfree(buf);
		return -ENOMEM;
	}

	pcmds->cmd_cnt = cnt;
	cmds_temp = pcmds->cmds;
	bp = buf;
	len = blen;
	for (i = 0; i < cnt; i++) {
		dchdr = (struct dsi_ctrl_hdr*)bp;
		len -= sizeof(*dchdr);
		bp += sizeof(*dchdr);
		cmds_temp->dtype = dchdr->dtype;
		cmds_temp->vc = dchdr->vc;
		cmds_temp->wait = dchdr->wait;
		cmds_temp->waittype = dchdr->waittype;
		cmds_temp->dlen = dchdr->dlen;
		cmds_temp->payload = bp;
		cmds_temp++;
		bp += dchdr->dlen;
		len -= dchdr->dlen;
	}
	cmds_temp = pcmds->cmds;
	pcmds->bp = buf;
	//  print_cmds(cmds_temp, pcmds->cmd_cnt);

	HISI_FB_DEBUG("cmd_cnt=%d\n", pcmds->cmd_cnt);

	return 0;
}

bool hw_free_dsi_cmds(struct dsi_panel_cmds* pcmds)
{

	if (pcmds->cmds)
	{ kfree(pcmds->cmds); }
	if (pcmds->bp)
	{ kfree(pcmds->bp); }
	pcmds->cmds = NULL;
	pcmds->bp = NULL;
	HISI_FB_DEBUG("The new LCD config region has been freed\n");
	return TRUE;
}


static void lcd_dbg_set_mipiclk(int clk)
{
	g_mipiclk =     clk;
}

static void lcd_dbg_enable_mipiclk(int enable)
{
	g_mipiclk_enable = enable;
}

static void lcd_dbg_enable_initcode(int enable)
{
	g_initcode_enable = enable;
}

static void lcd_dbg_enable_vsp_vsn(int enable)
{
	g_vsp_vsn_enable = enable;
}

int is_enable_initcode_debug(void)
{
	return g_initcode_enable;
}

int is_enable_mipiclk_debug(void)
{
	return g_mipiclk_enable;
}

int is_enable_vsp_vsn_debug(void)
{
	return g_vsp_vsn_enable;
}

int get_mipiclk_debug(void)
{
	return g_mipiclk;
}

void lcd_debug_set_vsp_vsn(struct vcc_desc* cmds, int cnt)
{
	int i = 0;
	struct vcc_desc* cm = NULL;

	cm = cmds;
	for (i = 0; i < cnt; i++) {
		if (cm->dtype == DTYPE_VCC_SET_VOLTAGE) {
			if (0 == strncmp(cm->id, VCC_LCDBIAS_NAME, strlen(cm->id))) {
				cm->min_uV = g_panel_bias;
				cm->max_uV = g_panel_bias;
			} else if (0 == strncmp(cm->id, VCC_LCD_VSP_NAME, strlen(cm->id))) {
				cm->min_uV = g_panel_vsp;
				cm->max_uV = g_panel_vsp;
			} else if (0 == strncmp(cm->id, VCC_LCD_VSN_NAME, strlen(cm->id))) {
				cm->min_uV = g_panel_vsn;
				cm->max_uV = g_panel_vsn;
			}
		}
		cm++;
	}
}

/* convert string to lower case */
/* return: 0 - success, negative - fail */
static int str_to_lower(char* str)
{
	char* tmp = str;

	/* check param */
	if (NULL == tmp) {
		return -1;
	}

	while (*tmp != '\0') {
		*tmp = tolower(*tmp);
		tmp++;
	}

	return 0;
}

/* check if string start with sub string */
/* return: 0 - success, negative - fail */
static int str_start_with(char* str, char* sub)
{
	/* check param */
	if (NULL == str || NULL == sub) {
		return -1;
	}

	return (0 == strncmp(str, sub, strlen(sub)) ? 0 : -1);
}

/* open function */
static int lcd_dbg_open(struct inode* inode, struct file* file)
{
	/* non-seekable */
	file->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);
	return 0;
}

/* release function */
static int lcd_dbg_release(struct inode* inode, struct file* file)
{
	return 0;
}

/* read function */
/* show usage or print last read result */
static ssize_t lcd_dbg_read(struct file* file,  char __user* buff, size_t count, loff_t* ppos)
{
	int len = 0;
	int ret_len = 0;
	char* cur;
	char lcd_debug_buf[1024];
	int buf_len = sizeof(lcd_debug_buf);

	cur = lcd_debug_buf;
	if (*ppos)
	{ return 0; }
	/* show usage */
	len = snprintf(cur, buf_len, "Usage: \n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"set_init_param:1\" > hw_lcd_debug to open set init parameter\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"set_init_param:0\" > hw_lcd_debug to close set init parameter\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"set_mipi_clock:486\" > hw_lcd_debug to set mipi clock\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_enable:0/1\" > hw_lcd_debug to set mipi clock\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"set_panel_vsp_vsn:5400000\" > hw_lcd_debug to set vsp/vsn voltage\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_reset:1\" > hw_lcd_debug to reset esd debug\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_bl_enable:0/1\" > hw_lcd_debug to disable/enable write backlight enable\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_bl_set:0/1\" > hw_lcd_debug to disable/enable write backlight\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_check_reg:0x0a,0x0b,...\" > hw_lcd_debug to set check reg\n");
	buf_len -= len;
	cur += len;

	len = snprintf(cur, buf_len, "\teg. echo \"lcd_esd_debug_check_value:0x9c,0x00,...\" > hw_lcd_debug to set reg value\n");
	buf_len -= len;
	cur += len;

	ret_len = sizeof(lcd_debug_buf) - buf_len;
	/* copy to user */
	if (copy_to_user(buff, lcd_debug_buf, ret_len))
	{ return -EFAULT; }

	*ppos += ret_len;   // increase offset
	return ret_len;
}

/* write function */
static ssize_t lcd_dbg_write(
    struct file* file,
    const char __user* buff,
    size_t count,
    loff_t* ppos)
{
	char* cur, *ptr1, *ptr2;
	int ret = 0;
	int cmd_type = -1;
	int cnt = 0, i;
	int val;
	int reg = 0;
	char lcd_debug_buf[256];
	int length = sizeof(g_cmd_list) / sizeof(lcd_dbg_cmds);

	cur = lcd_debug_buf;
	if (copy_from_user(lcd_debug_buf, buff, count))
	{ return -EFAULT; }

	lcd_debug_buf[count] = 0;
	/* convert to lower case */
	if (0 != str_to_lower(cur)) {
		goto err_handle;
	}

	HISI_FB_DEBUG("cur=%s,count=%d!\n", cur, count);

	/* get cmd type */
	for (i = 0; i < length; i++) {
		if (0 == str_start_with(cur, g_cmd_list[i].pstr)) {
			cmd_type = g_cmd_list[i].type;
			cur += strlen(g_cmd_list[i].pstr);
			break;
		}
		HISI_FB_DEBUG("g_cmd_list[%d].pstr=%s\n", i, g_cmd_list[i].pstr);
	}

	if (i >= length) {
		HISI_FB_ERR("cmd type not find!\n");  // not support
		goto err_handle;
	}
	switch (cmd_type) {
		case LCD_DBG_MIPI_CLK:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			lcd_dbg_enable_mipiclk(1);
			lcd_dbg_set_mipiclk(val);
			break;
		case LCD_DBG_INIT_CODE:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			lcd_dbg_enable_initcode(val);
			hw_free_dsi_cmds(&g_panel_cmds);
			if (val == 1) {
				ret = hw_parse_dsi_cmds(&g_panel_cmds);
				if (ret != 0) {
					hw_free_dsi_cmds(&g_panel_cmds);
					lcd_dbg_enable_initcode(0);
					HISI_FB_ERR("decode parameter error!\n");
					goto err_handle;
				}
				HISI_FB_DEBUG("decode parameter succ!\n");
			}
			break;

		case LCD_DBG_PANEL_VSP_VSN:
			lcd_dbg_enable_vsp_vsn(1);
			cur++;
			ret = strict_strtoul(cur, 0, &val);
			if (ret) {
				HISI_FB_ERR("strict_strtoul error!\n");
				goto err_handle;
			}
			g_panel_bias = val;
			g_panel_vsp = val;
			g_panel_vsn = val;
			HISI_FB_DEBUG("g_panel_vsp = %d!\n", g_panel_vsp);
			break;
		case LCD_DBG_ESD_ENABLE:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			g_esd_debug.esd_enable = val;
			HISI_FB_DEBUG("g_esd_debug.esd_enable = %d\n", g_esd_debug.esd_enable);
			break;
		case LCD_DBG_ESD_RECOVER_TEST:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			g_esd_debug.esd_recover_test = val;
			break;
		case LCD_DBG_ESD_RESET:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			if (val) {
				memset(&g_esd_debug, 0, sizeof(struct esd_debug));
			}
			HISI_FB_DEBUG("g_esd_debug reset\n");
			break;
		case LCD_DBG_ESD_BL_ENABLE:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			g_esd_debug.esd_bl_enable = val;
			HISI_FB_DEBUG("g_esd_debug.esd_bl_enable = %d\n", g_esd_debug.esd_bl_enable);
			break;
		case LCD_DBG_ESD_BL_SET:
			cnt = sscanf(cur, ":%d", &val);
			if (cnt != 1) {
				HISI_FB_ERR("get param fail!\n");
				goto err_handle;
			}
			g_esd_debug.esd_bl_set = val;
			HISI_FB_DEBUG("g_esd_debug.esd_bl_set = %d\n", g_esd_debug.esd_bl_set);
			break;
		case LCD_DBG_ESD_CHECK_REG:
			ptr1 = ptr2 = (cur + 1);
			ptr2 = strchr(ptr2, ',');
			if (ptr2) {
				*ptr2 = 0;
				ptr2++;
			}
			while (ptr1) {
				ret = strict_strtoul(ptr1, 0, &val);
				if (ret) {
					HISI_FB_ERR("strict_strtoul error, buf=%s", ptr1);
					return ret;
				}
				if (g_esd_debug.check_count >= 8) {
					HISI_FB_ERR("check reg is too much.\n", val);
					break;
				}
				g_esd_debug.esd_check_reg[g_esd_debug.check_count++] = val;
				ptr1 = ptr2;
				if (ptr2) {
					ptr2 = strchr(ptr2, ',');
					if (ptr2) {
						*ptr2 = 0;
						ptr2++;
					}
				}
				HISI_FB_DEBUG("g_esd_debug.esd_check_reg=0x%x.\n", val);
			}
			break;
		case LCD_DBG_ESD_CHECK_VALUE:
			ptr1 = ptr2 = (cur + 1);
			ptr2 = strchr(ptr2, ',');
			if (ptr2) {
				*ptr2 = 0;
				ptr2++;
			}
			while (ptr1) {
				ret = strict_strtoul(ptr1, 0, &val);
				if (ret) {
					HISI_FB_ERR("strict_strtoul error, buf=%s", ptr1);
					return ret;
				}
				if (cnt >= 8) {
					HISI_FB_ERR("check reg is too much.\n", val);
					break;
				}
				g_esd_debug.esd_reg_value[cnt++] = val;
				ptr1 = ptr2;
				if (ptr2) {
					ptr2 = strchr(ptr2, ',');
					if (ptr2) {
						*ptr2 = 0;
						ptr2++;
					}
				}
				HISI_FB_DEBUG("g_esd_debug.esd_check_reg=0x%x.\n", val);
			}
			break;

		default:
			HISI_FB_ERR("cmd type not support!\n");  // not support
			ret = -1;
			break;
	}
	/* finish */
	if (ret) {
		HISI_FB_ERR("fail\n");
		goto err_handle;
	} else {
		return count;
	}
err_handle:
	return -EFAULT;
}

static const struct file_operations lcd_debug_fops = {
	.open = lcd_dbg_open,
	.release = lcd_dbg_release,
	.read = lcd_dbg_read,
	.write = lcd_dbg_write,
};

/*
 * debugfs
 *
 */
/* init lcd debugfs interface */
int lcd_debugfs_init(void)
{
	static char already_init = 0;  // internal flag
	struct dentry* dent = NULL;

	/* judge if already init */
	if (already_init) {
		HISI_FB_ERR("(%d): already init\n", __LINE__);
		return 0;
	}

	/* create dir */
	dent = debugfs_create_dir("lcd-dbg", NULL);
	if (IS_ERR_OR_NULL(dent)) {
		HISI_FB_ERR("(%d): debugfs_create_dir fail, error %ld\n", __LINE__, PTR_ERR(dent));
		dent = NULL;
		goto err_create_dir;
	}

	/* create reg_dbg_mipi node */
	if (NULL == debugfs_create_file("hw_lcd_debug", 0644, dent, 0, &lcd_debug_fops)) {
		HISI_FB_ERR("(%d): debugfs_create_file: lcd_dbg fail\n", __LINE__);
		goto err_create_mipi;
	}

	already_init = 1;  // set flag
	return 0;

err_create_mipi:
	if (dent) {
		debugfs_remove_recursive(dent);
		dent = NULL;
	}
err_create_dir:
	return -1;
}
