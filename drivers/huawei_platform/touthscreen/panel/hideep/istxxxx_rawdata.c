#include "ist520e.h"
#include "istxxxx_rawdata.h"

extern struct ist510e *g_istxxxx_data;
extern struct ts_data g_ts_data;

#define HIDEEP_READ_IMAGE_REPEAT 3
#define HIDEEP_CHECK_READ	0X000C
#define HIDEEP_STATE_TIME_OUT	200
#define OPM_SCAN_ONCE 0x99
#define OPM_SCAN_ONCE_IMAGES 0x817

static void rotate_rawdata_abcd2adcb(int column, int row, int *data_start)
{
	int *rawdatabuf_temp = NULL;
	int row_index, column_index;
	int row_size = 0;
	int column_size = 0;
	int i = 0;

	TS_LOG_INFO("\n");
	rawdatabuf_temp = (int *)kzalloc(row*column*sizeof(int), GFP_KERNEL);
	if (!rawdatabuf_temp) {
		TS_LOG_ERR("Failed to alloc buffer for rawdatabuf_temp\n");
		return;
	}

	memcpy(rawdatabuf_temp, data_start, row*column*sizeof(int));
	row_size = row;
	column_size = column;
	for (column_index = column_size - 1; column_index >= 0; column_index--) {
		for (row_index = row_size - 1; row_index >= 0; row_index --) {
			data_start[i++] = rawdatabuf_temp[row_index*column_size+column_index];
		}
	}
	if (rawdatabuf_temp) {
		kfree(rawdatabuf_temp);
		rawdatabuf_temp = NULL;
	}
	return;
}

int hideep_get_image_by_cmd(u16 vr_addr, u8 vr_data)
{
	struct ist510e *ts   = g_istxxxx_data;
	struct ist510e_debug_dev *dev = &ts->debug_dev;
	int ret=0;
	int i = 0;
	unsigned char value = 0;
	
	TS_LOG_DEBUG("hideep_get_image_by_cmd enter\n");
	ret = hideep_i2c_write(ts,vr_addr,1,(u8*)&vr_data);
	if(ret<0){
		goto hideep_get_image_command_err;
	}
	for(i = 0;i<100; i++){
		mdelay(10);
		ret = hideep_i2c_read (ts, HIDEEP_CHECK_READ, 1, &value);
		if(ret<0){
			goto hideep_get_image_command_err;
		}
		TS_LOG_DEBUG("read state = 0x%x\n",value);
		if(value){
			TS_LOG_INFO("state =%d is ready\n", value);
			break;
		}
	}
	if(!value){
		TS_LOG_ERR("checking change mode time out!\n");
		goto hideep_get_image_command_err;
	}
	hideep_get_image(ts);
	mdelay(10);
	TS_LOG_INFO("dev->im_buff[0] = 0x%02x\n",dev->im_buff[0]);
	return 0;

hideep_get_image_command_err:
	TS_LOG_ERR("send command error\n");
	return -1;
}

static int tx_rx_slope_2d(struct ts_rawdata_info *info)
{
	int rx = 0;
	int tx = 0;
	int i = 0;
	int j= 0;
	s32 *ps32;
	s32 p1,p2,p3;
	int fail_node = 0;

	TS_LOG_INFO("%sTX slope\n",__func__);
	rx = info->buff[0];
	tx = info->buff[1];
	ps32 = (s32*)&info->buff[2];

	for(i = 0; i < tx; i++){
		for(j = 0; j < rx-1; j++){
			p1 = *(ps32+i*rx+j);
			p2 = *(ps32+i*rx+j+1);
			p3 = p1-p2;
			TS_LOG_DEBUG("p3 = %d\n",p3);
			if((p3 > 500)||(p3 < -500)){
				TS_LOG_ERR("i = %d, j = %d, p1 = %d, p2 = %d, p3 = %d\n", i,j,p1,p2,p3);
				fail_node++;
			}
		}
	}
	TS_LOG_INFO("%sRX slope\n",__func__);
	for(i = 0; i < rx; i++){
		for(j = 0; j < tx-1; j++){
			p1 = *(ps32+j*rx+i);
			p2 = *(ps32+(j+1)*rx+i);
			p3 = p1-p2;
			TS_LOG_DEBUG("p3 = %d\n",p3);
			if((p3 > 500)||(p3 < -500)){
				TS_LOG_ERR("i = %d, j = %d, p1 = %d, p2 = %d, p3 = %d\n", i,j,p1,p2,p3);
				fail_node++;
			}
		}
	}
	TS_LOG_INFO("fail_node = %d\n", fail_node);
	return fail_node;
}

static int hideep_get_2d_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd, char * mmm)
{
	int ret = 0;
	struct ist510e *ts   = g_istxxxx_data;
	struct ist510e_debug_dev *dev = &ts->debug_dev;
	struct ts_device_data *data= ts->huawei_ts_data;
	int rx = 0;
	int tx = 0;
	int i = 0;
	int j = 0;
	s16 *ps;
	int *ps_buf;
	const s16 * p16_base;
	int min = 0xffff;
	int max = -1;
	int sum = 0;
	int index = 0;
	int fail_node = 0;

	TS_LOG_INFO("%s enter\n", __func__);
	index = 0;
	rx = info->buff[0];
	tx = info->buff[1];

	dev->im_size = rx*tx*2+8;
	dev->im_buff = kmalloc(dev->im_size, GFP_KERNEL);
	if(NULL == dev->im_buff){
		ret = 0;
		TS_LOG_ERR("can't alloc memory\n");
		goto hideep_get_2d_rawdata_alloc_err;
	}
	i = 0;
	do{
		hideep_get_image_by_cmd(OPM_SCAN_ONCE_IMAGES,1);
		if('G' == dev->im_buff[0]){
			TS_LOG_INFO("read out images\n");
			break;
		}
	}while(++i<HIDEEP_READ_IMAGE_REPEAT);
	if(i>=HIDEEP_READ_IMAGE_REPEAT){
		ret = 0xff00;
		TS_LOG_ERR("can NOT read out image\n");
		goto hideep_get_2d_rawdata_image_err;
	}
	ps = (s16*)(dev->im_buff + 8);
	ps_buf = &info->buff[2];
	p16_base = hideep_c_rawdata_database;
	for(j = 0; j < tx; j++){
		for(i = 0; i < rx; i++){
			if(min > *ps)
				min = *ps;
			if(max < *ps)
				max = *ps;
			sum += *ps;
			if((*ps > (*p16_base + data->raw_limit_buf[index]))||
				(*ps < (*p16_base + data->raw_limit_buf[index+1]))){
					TS_LOG_INFO("NG data = %d, (%d, %d)\n", *ps, *p16_base + data->raw_limit_buf[index], *p16_base + data->raw_limit_buf[index+1]);
					fail_node++;
			}else{
				TS_LOG_DEBUG("PASS data = %d, (%d, %d)\n", *ps, *p16_base + data->raw_limit_buf[index], *p16_base + data->raw_limit_buf[index+1]);
			}
			*ps_buf = *ps;
			ps++;
			ps_buf++;
			p16_base++;
		}
	}
	if(fail_node){
		ret = 0;
	}
	else{
		ret = 1;
	}
	i=strlen(mmm);
	snprintf(mmm+i,1024-i,"[%4d,%4d,%4d]",sum/(tx*rx),max,min);
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
	return ret;
	
hideep_get_2d_rawdata_image_err:
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
hideep_get_2d_rawdata_alloc_err:
	return ret;
}

static int hideep_get_2d_diff(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd, char * mmm)
{
	int ret = 0;
	struct ist510e *ts   = g_istxxxx_data;
	struct ist510e_debug_dev *dev = &ts->debug_dev;
	struct ts_device_data *data= ts->huawei_ts_data;
	int rx = 0;
	int tx = 0;
	int i = 0;
	int j = 0;
	s16 *ps;
	int *ps_buf;
	const s16 * p16_base;
	int min = 0xffff;
	int max = -1;
	int sum = 0;
	int index = 0;
	int fail_node = 0;

	TS_LOG_INFO("%s enter\n", __func__);
	index = 2;
	rx = info->buff[0];
	tx = info->buff[1];
	dev->im_size = rx*tx*2+8;
	dev->im_buff = kmalloc(dev->im_size, GFP_KERNEL);
	if(NULL == dev->im_buff){
		ret = 0;
		TS_LOG_ERR("can't alloc memory\n");
		goto hideep_get_2d_diff_alloc_err;
	}
	i = 0;
	do{
		hideep_get_image_by_cmd(OPM_SCAN_ONCE_IMAGES,4);
		if('G' == dev->im_buff[0]){
			TS_LOG_INFO("read out images\n");
			break;
		}
	}while(++i<HIDEEP_READ_IMAGE_REPEAT);
	if(i>=HIDEEP_READ_IMAGE_REPEAT){
		ret = 0xff00;
		TS_LOG_ERR("can NOT read out image\n");
		goto hideep_get_2d_diff_image_err;
	}
	ps = (s16*)(dev->im_buff + 8);
	ps_buf = &info->buff[rx*tx+2];
	p16_base = hideep_c_diffdata_database;
	for(j = 0; j < tx; j++){
		for(i = 0; i < rx; i++){
			if(min > *ps)
				min = *ps;
			if(max < *ps)
				max = *ps;
			sum += *ps;
			if((*ps > (*p16_base + data->raw_limit_buf[index]))||
				(*ps < (*p16_base + data->raw_limit_buf[index+1]))){
					TS_LOG_INFO("NG data = %d, (%d, %d)\n", *ps, *p16_base + data->raw_limit_buf[index], *p16_base + data->raw_limit_buf[index+1]);
					fail_node++;
			}else{
				TS_LOG_DEBUG("PASS data = %d, (%d, %d)\n", *ps, *p16_base + data->raw_limit_buf[index], *p16_base + data->raw_limit_buf[index+1]);
			}
			*ps_buf = *ps;
			ps++;
			ps_buf++;
			p16_base++;
		}
	}
	if(fail_node){
		ret = 0;
	}
	else{
		ret = 2;
	}
	i=strlen(mmm);
	snprintf(mmm+i,1024-i,"[%4d,%4d,%4d]",sum/(tx*rx),max,min);
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
	return ret;
	
hideep_get_2d_diff_image_err:
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
hideep_get_2d_diff_alloc_err:
	return ret;
}

static int hideep_get_3d_rawdata_diff(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd, char * mmm)
{
	int ret = 0;
	struct ist510e *ts   = g_istxxxx_data;
	struct ist510e_debug_dev *dev = &ts->debug_dev;
	struct ts_device_data *data= ts->huawei_ts_data;
	int rx = 0;
	int tx = 0;
	int i = 0;
	int j = 0;
	s32 *ps;  //hideep 3d raw data type is s32.
	const s32 * p32_base;
	int *ps_buf;

	int min = 0xffff;
	int max = -1;
	int sum = 0;
	int index = 0;
	int fail_node = 0;

	TS_LOG_INFO("%s enter\n", __func__);
	index = 4;
	rx = info->buff_3d[0];
	tx = info->buff_3d[1];
	//dev->im_size = rx*tx*4+8;
	dev->im_size = 64*3+8;
	dev->im_buff = kmalloc(dev->im_size, GFP_KERNEL);
	if(NULL == dev->im_buff){
		ret = 0;
		TS_LOG_ERR("can't alloc memory\n");
		goto hideep_get_3d_rawdata_diff_alloc_err;
	}
	i = 0;
	do{
		hideep_get_image_by_cmd(OPM_SCAN_ONCE_IMAGES,7);
		if('G' == dev->im_buff[0]){
			TS_LOG_INFO("read out images\n");
			break;
		}
	}while(++i<HIDEEP_READ_IMAGE_REPEAT);
	if(i>=HIDEEP_READ_IMAGE_REPEAT){
		ret = 0xff00;
		TS_LOG_ERR("can NOT read out image\n");
		goto hideep_get_3d_rawdata_diff_image_err;
	}
	ps = (s32*)(&dev->im_buff[0] + 8);
	ps_buf = (s32*)&info->buff_3d[2];
	p32_base = hideep_c_3d_rawdata_database;
	
	min = *ps;
	max = *ps;
	sum = 0;
	for(j = 0; j < tx; j++){
		for(i = 0; i < rx; i++){
			if((j==tx-1)&&(i==rx-1))
				break;
			if(min > *ps)
				min = *ps;
			if(max < *ps)
				max = *ps;
			sum += *ps;
			if((*ps > (*p32_base + data->raw_limit_buf[index]))||
				(*ps < (*p32_base + data->raw_limit_buf[index+1]))){
					TS_LOG_INFO("NG data = %d, (%d, %d)\n", *ps, *p32_base + data->raw_limit_buf[index], *p32_base + data->raw_limit_buf[index+1]);
					fail_node++;
			}else{
				TS_LOG_DEBUG("PASS data = %d, (%d, %d)\n", *ps, *p32_base + data->raw_limit_buf[index], *p32_base + data->raw_limit_buf[index+1]);
			}
			*ps_buf = *ps;
			ps++;
			ps_buf++;
			p32_base++;
		}
	}
	if(fail_node){
		ret = 0;
	}
	else{
		ret = 4;
	}
	i=strlen(mmm);
	snprintf(mmm+i,1024-i,"[%4d,%4d,%4d]",sum/(tx*rx),max,min);

	//3D diff.
	index = 6;
	ps = (s32*)(dev->im_buff + 8 +64*2);
	ps_buf = &info->buff_3d[rx*tx+2];
	p32_base = hideep_c_3d_diffdata_database;
	min = *ps;
	max = *ps;
	sum = 0;
	for(j = 0; j < tx; j++){
		for(i = 0; i < rx; i++){
			if((j==tx-1)&&(i==rx-1))
				break;
			if(min > *ps)
				min = *ps;
			if(max < *ps)
				max = *ps;
			sum += *ps;
			if((*ps > (*p32_base + data->raw_limit_buf[index]))||
				(*ps < (*p32_base + data->raw_limit_buf[index+1]))){
					TS_LOG_INFO("NG data = %d, (%d, %d)\n", *ps, *p32_base + data->raw_limit_buf[index], *p32_base + data->raw_limit_buf[index+1]);
					fail_node++;
			}else{
				TS_LOG_DEBUG("PASS data = %d, (%d, %d)\n", *ps, *p32_base + data->raw_limit_buf[index], *p32_base + data->raw_limit_buf[index+1]);
			}
			*ps_buf = *ps;
			ps++;
			ps_buf++;
			p32_base++;
		}
	}
	if(fail_node){
		ret += 0;
	}
	else{
		ret += 8;
	}
	i=strlen(mmm);
	snprintf(mmm+i,1024-i,"[%4d,%4d,%4d];",sum/(tx*rx),max,min);
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
	return ret;
	
hideep_get_3d_rawdata_diff_image_err:
	if(dev->im_buff){
		kfree(dev->im_buff);
		dev->im_buff = NULL;
	}
hideep_get_3d_rawdata_diff_alloc_err:
	return ret;
}


int hideep_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd)
{
	int ret = 0, raw_ret=0, diff_ret=0;
	struct ist510e *ts   = g_istxxxx_data;
	struct ist510e_debug_dev *dev = &ts->debug_dev;
	struct ts_device_data *gdev = g_ts_data.chip_data;
	u8 *str_mms_buf;
	struct ts_easy_wakeup_info *gesture_info;
	int i = 0, column = 0, row = 0;
	unsigned char vr_buff = 0;
	unsigned short vr_addr =0;
	int	retry_reading = 0;

	gesture_info = &g_istxxxx_data->huawei_ts_data->easy_wakeup_info;
	TS_LOG_INFO("hideep_get_rawdata enter, ts->dev_state = %d\n", ts->dev_state);
	if((ISTCORE_PWR_NORMAL != ts->dev_state)&&
		(TS_GESTURE_MODE != gesture_info->sleep_mode)){
		TS_LOG_ERR("hideep_get_rawdata is not in normal mode \n");
		ret = -3;
		goto hideep_get_rawdata_state_err;
	}
	if((TS_GESTURE_MODE == gesture_info->sleep_mode)&&
		(true == gesture_info->off_motion_on)){
		TS_LOG_ERR("hideep_get_rawdata is not in normal mode \n");
		ret = -4;
		goto hideep_get_rawdata_state_err;
	}
	str_mms_buf = NULL;
	info->buff[0] = HIDEEP_RX_COUNT;
	info->buff[1] = HIDEEP_TX_COUNT;
	info->buff_3d[0] = HIDEEP_RX_3D_COUNT;
	info->buff_3d[1] = HIDEEP_TX_3D_COUNT;
	info->used_size = HIDEEP_RX_COUNT * HIDEEP_TX_COUNT *2 +2;
	info->used_size_3d = HIDEEP_RX_3D_COUNT * HIDEEP_TX_3D_COUNT *2 +2;

	str_mms_buf = kmalloc(1024, GFP_KERNEL);
	if(str_mms_buf == NULL){
		TS_LOG_ERR("can't alloc memory\n");
		goto hideep_get_rawdata_alloc_err;
	}
	TS_LOG_DEBUG("hideep_get_rawdata t = %d, r = %d\n",info->buff[1],info->buff[0]);
	TS_LOG_DEBUG("hideep_get_rawdata t = %d, r = %d(3d)\n",info->buff_3d[1],info->buff_3d[0]);
	mutex_lock(&ts->dev_mutex);

reading_rawdata_retry:
	memset(str_mms_buf,0,1024);
	dev->im_r_en = 1;
	TS_LOG_INFO("x,y rawdata enter\n");
	//reading x,y rawdata....
	memcpy(info->result,"0P",strlen("0P"));
	column = info->buff[0];
	row = info->buff[1];
	vr_addr = 0;
	vr_buff = OPM_SCAN_ONCE;
	msleep(500);
	ret = hideep_i2c_write(ts, vr_addr, 1,&vr_buff);
	for(i = 0;i<100; i++){
		mdelay(10);
		ret = hideep_i2c_read (ts, vr_addr, 1, &vr_buff);
		TS_LOG_INFO("vr_buff = 0x%x\n",vr_buff);
		if(vr_buff == 0x10)
			break;
	}
	if(vr_buff !=0x10){
		TS_LOG_ERR("checking change mode time out!\n");
		goto hideep_get_rawdata_rd_err;
	}
	raw_ret = hideep_get_2d_rawdata(info, out_cmd, str_mms_buf);
	TS_LOG_INFO("raw_ret = 0x%x", raw_ret);
	raw_ret |= hideep_get_2d_diff(info, out_cmd, str_mms_buf);
	TS_LOG_INFO("raw_ret = 0x%x", raw_ret);
	raw_ret |= hideep_get_3d_rawdata_diff(info, out_cmd, str_mms_buf);
	TS_LOG_INFO("raw_ret = 0x%x", raw_ret);
	/* 2d raw data & 3d raw data both correct, we return P, else return F */
	if ((raw_ret&5)!=0x5){
		if((raw_ret & 5)!=1){
			TS_LOG_INFO("2D rawdata error.\n");
		}else{
			TS_LOG_INFO("3D rawdata error.\n");
		}
		strncat(info->result, "-1F", MAX_STR_LEN);
	}else{
		strncat(info->result, "-1P", MAX_STR_LEN);
	}

	/* hideep should give the judge condition */
	if(tx_rx_slope_2d(info)){
		TS_LOG_INFO("slope.\n");
		strncat(info->result, "-2F", MAX_STR_LEN);
	}else{
		strncat(info->result, "-2P", MAX_STR_LEN);
	}

	/* 2d diff data & 3d diff data both correct, we return P, else return F */
	if ((raw_ret&0x0a)!=0x0a){
		if((raw_ret & 0x0a)!=2){
			TS_LOG_INFO("2D diff error.\n");
		}else{
			TS_LOG_INFO("3D diff error.\n");
		}
		strncat(info->result, "-3F", MAX_STR_LEN);
	}else{
		strncat(info->result, "-3P", MAX_STR_LEN);
	}

	/* hideep should give the judge condition */
	strncat(info->result, "-4P", MAX_STR_LEN);

	if((raw_ret & 0xff00) == 0xff00){
		TS_LOG_INFO("retry_reading = %d", retry_reading);
		retry_reading++;
		if(retry_reading<=3){
			memset(info->result,0,TS_RAWDATA_RESULT_MAX);
			goto reading_rawdata_retry;
		}
	}
	i = strlen(info->result);
	memcpy(info->result+i,str_mms_buf,strlen(str_mms_buf)+1);
	dev->im_r_en = 0;

	if (g_ts_data.chip_data->rawdata_arrange_swap){
		rotate_rawdata_abcd2adcb(column, row, info->buff+2+column*row);
		rotate_rawdata_abcd2adcb(column, row, info->buff+2);
	}

hideep_get_rawdata_rd_err:
	dev->i_rdy = 0;
	vr_buff = OPM_TOUCH_A;
	ret = hideep_i2c_write(ts, 0, 1,&vr_buff);
	out_cmd->command = TS_INVAILD_CMD;
	mutex_unlock(&ts->dev_mutex);
hideep_get_rawdata_alloc_err:
	if(str_mms_buf) {
		kfree(str_mms_buf);
		str_mms_buf = NULL;
	}
	hideep_reset_ic();
	mdelay(60);
	if (gdev->ops->chip_after_resume)
		gdev->ops->chip_after_resume((void *)&g_ts_data.feature_info);
hideep_get_rawdata_state_err:
	TS_LOG_INFO("%s end....\n", __func__);
	return ret;
}
