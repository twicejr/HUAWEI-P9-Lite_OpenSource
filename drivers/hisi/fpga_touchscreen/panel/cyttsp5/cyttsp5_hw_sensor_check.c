


#include "cyttsp5_core.h"
#include "cyttsp5_regs.h"
#include "cyttsp5_hw.h"
#include "csv.h"

#include <linux/fs.h>

extern int cyttsp5_hw_reset(struct cyttsp5_core_data *cd);

atomic_t mmi_test_status = ATOMIC_INIT(0);
#define CYTTSP5_INPUT_ELEM_SZ (sizeof("0xHH") + 1)

struct cyttsp5_sensor_info_limit mmi_info_limit={0};
struct cyttsp5_core_commands *gcmd = NULL;
struct device *gdev = NULL;

#define TP_CONFIG_FILE_PATH "/system/etc/tp_test_parameters/"

struct cyttsp5_panel_info {
    u8 *product_name;
    u8 *chip_name;
    u8 panel_id;
    u8 *id2str;
};

static struct cyttsp5_panel_info hw_panel_info[] = {
    {"x1s","tma568", 0,"ofilm" },
    {"x1s","tma568", 1,"lens"  },
    {"Gemini","tma568",0,"ofilm"},
    {"Gemini","tma568",1,"lens"},
    {"mozart","CS448", 0,"ofilm"},
    {"mozart","CS448", 1,"truly"},
};

enum parser_state {
    START,
    OPENS_GETING,
    IDAC_GETING,
    LOCALPWC_GETING,
    MUTUAL_NOISE_GETING,
    MUTUAL_RAWDATA_GETING,
    SELF_NOISE_GETING,
    SELF_RAWDATA_GETING,
    SELF_LOCALPWC_GETING,
    END,
    ERROR,
};

struct parser_data {
    struct cyttsp5_sensor_info_limit *sensor_info;
    enum parser_state state;
    int *pCurFieldAddr;
    int iCurNum;
    int iMaxNum;
};

struct field_state {
    char *field;
    enum parser_state new_state;
};

static struct  field_state Field_OldState_NewState[]= {
    {"cyttsp5_sensor_opens",           OPENS_GETING         },
    {"cyttsp5_sensor_idac",            IDAC_GETING          },
    {"cyttsp5_sensor_localPWC",        LOCALPWC_GETING      },
    {"cyttsp5_sensor_mutual_noise",    MUTUAL_NOISE_GETING  },
    {"cyttsp5_sensor_mutual_rawdata",  MUTUAL_RAWDATA_GETING},
    {"cyttsp5_sensor_self_noise",      SELF_NOISE_GETING    },
    {"cyttsp5_sensor_self_rawdata",    SELF_RAWDATA_GETING  },
    {"cyttsp5_sensor_selflocalPWC",    SELF_LOCALPWC_GETING },
};

/*return 0 is ok!*/
static int parser_set_state(struct parser_data *data, char *field)
{
    enum parser_state new_state=ERROR;
    int i;
    int iRet = -1;
    int iTxNum = CSV_TX_NUM;
    int iRxMulTxNum = TX_MUL_RX_NUM;
    int iRxAddTxNum = TX_ADD_RX_NUM;

    if (!strcmp(field, "")){
        TS_LOG_ERR("%s: field is null !\n",__func__ );
        data->state = ERROR;
        return iRet;
    }

    for (i = 0; i < ARRAY_SIZE(Field_OldState_NewState); i++){
        if (!strcmp(field, Field_OldState_NewState[i].field))
        {
            new_state = Field_OldState_NewState[i].new_state;
        }
    }

    if( new_state==ERROR ){
        TS_LOG_ERR("%s, updata state error.  field is %s\n", __func__, field);
        data->state = ERROR;
        return iRet;
    }

    switch(new_state){
        case OPENS_GETING:
            data->pCurFieldAddr  = data->sensor_info->opens.min;
            data->iMaxNum= iRxMulTxNum*3+4;
            break;
        case IDAC_GETING:
            data->pCurFieldAddr  = data->sensor_info->idac.max;
            data->iMaxNum= iTxNum*3;
            break;
        case LOCALPWC_GETING:
            data->pCurFieldAddr  = data->sensor_info->localPWC.max;
            data->iMaxNum= iRxMulTxNum*2;
            break;
        case MUTUAL_NOISE_GETING:
            data->pCurFieldAddr  = data->sensor_info->mutual_noise.max;
            data->iMaxNum= iRxMulTxNum;
            break;
        case MUTUAL_RAWDATA_GETING:
            data->pCurFieldAddr  = data->sensor_info->mutual_rawdata.max;
            data->iMaxNum= iRxMulTxNum*2;
            break;
        case SELF_NOISE_GETING:
            data->pCurFieldAddr  = data->sensor_info->self_noise.max;
            data->iMaxNum= iRxAddTxNum;
            break;
        case SELF_RAWDATA_GETING:
            data->pCurFieldAddr  = data->sensor_info->self_rawdata.max;
            data->iMaxNum= iRxAddTxNum*2;
            break;
        case SELF_LOCALPWC_GETING:
            data->pCurFieldAddr  = &(data->sensor_info->selflocalPWC.self_gidac_max_rx);
            data->iMaxNum= 4+iRxAddTxNum*3;
            break;
        default:
            data->state = ERROR;
            break;
    }

    data->iCurNum = 0;
    data->state = new_state;
    iRet = 0;

    return iRet;
}


static void tp_field_read_callback(void *s, size_t len, void *d)
{
    struct parser_data *data = (struct parser_data *)d;
    char *field = (char *)s;
    int ret;
    int idata = 0;

    //used for check field like ",,"
    if (!strcmp(field, ""))
        return;

    if (data->state == ERROR){
        TS_LOG_ERR("%s: state is ERROR !\n",__func__ );
        return;
    }

    TS_LOG_DEBUG("%s,  current field is %s,  current state is %d.\n", __func__, field, data->state);

    //get current value
    switch (data->state) {
        case START:
            //set current state and current need get data num, and the data offset address
            ret = parser_set_state(data, field);
            if (!ret){
                //print the current field. error has printed.
                TS_LOG_INFO("%s: START field: %s\n", __func__, field);
            }
        break;

    default:
        if( (data->state == END)  || (data->state == ERROR) ){
            TS_LOG_INFO("%s,  END OR ERROR state is %d.\n", __func__, data->state);
            return;
        }

        if(  (data->state == OPENS_GETING)  || (data->state == IDAC_GETING)
            || (data->state == LOCALPWC_GETING)  || (data->state == MUTUAL_NOISE_GETING)
            || (data->state == MUTUAL_RAWDATA_GETING)  || (data->state == SELF_NOISE_GETING)
            || (data->state == SELF_RAWDATA_GETING)  || (data->state == SELF_LOCALPWC_GETING)  ){
            //ok
            TS_LOG_DEBUG("%s,  state is %d.\n", __func__, data->state);
        }
        else{//error
            TS_LOG_ERR("%s,  error state is %d.\n", __func__, data->state);
            return;
        }

        ret = sscanf(field, "%d", &idata);
        if (ret == 1) {
            TS_LOG_DEBUG("%s: state is %d, index is %d, data is %d\n", __func__, data->state, data->iCurNum, idata);

            data->pCurFieldAddr[data->iCurNum] = idata;
            data->iCurNum++;
            if( data->iMaxNum==  data->iCurNum){
                if(data->state == SELF_LOCALPWC_GETING){
                    data->state = END;//the last data is get, then set sate is END.
                }
                else{
                    data->state = START; //begin get the name of struct member
                    data->iCurNum = 0;
                    data->iMaxNum = 0;
                    data->pCurFieldAddr = NULL;
                }
            }
            return;
        } else {
            TS_LOG_ERR("%s: Single value field parse failed for %s\n", __func__, field);
            data->state = ERROR;
            return;
        }

        break;
    }
}


static void parser_init(struct parser_data *data,
        struct cyttsp5_sensor_info_limit *current_info)
{
    data->sensor_info= current_info;
    data->state = START;
    data->pCurFieldAddr = NULL;
    data->iCurNum = 0;
    data->iMaxNum = 0;
}


int tp_configuration_get(char *filename, struct cyttsp5_sensor_info_limit *sensor_info)
{
    struct csv_parser p;
    uint8_t buffer[1024];
    size_t bytes_read;
    struct parser_data data;
    int ret=-1;
    struct file *config_file=NULL;
    mm_segment_t fs;

    fs =get_fs();
    set_fs(KERNEL_DS);

    config_file = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(config_file)){
        TS_LOG_ERR("%s,  filp_open error, file name is %s.\n", __func__, filename);
        ret = -1;
        goto exit;
    }

    TS_LOG_DEBUG("%s,  filp_open %s success.\n", __func__, filename);

    ret = csv_init(&p, CSV_APPEND_NULL);
    if (ret) {
        TS_LOG_ERR("%s,  csv_init error!\n", __func__);
        ret = -1;
        goto close;
    }

    parser_init(&data, sensor_info);

    TS_LOG_DEBUG("%s,  parser_init complete.\n", __func__);

    while(1){

        bytes_read = vfs_read(config_file, buffer, sizeof(buffer), &(config_file->f_pos));

        if(bytes_read <= 0) {
            TS_LOG_ERR("%s read file: %s  ERROR or end! \n", __func__, filename);
            break;
        }

        if (csv_parse(&p, buffer, bytes_read, tp_field_read_callback,
                NULL, &data) != bytes_read) {
            TS_LOG_ERR("%s Error parsing file: %s.\n", __func__, csv_strerror(csv_error(&p)));
            ret = -csv_error(&p);
            goto finish;
        }

        //check if all data has get complete
        if(data.state ==  END) {
            TS_LOG_INFO("%s,  all need data has get success !\n", __func__);
            break;
        }
    }

    TS_LOG_DEBUG("%s csv_parse end !\n", __func__);

    csv_fini(&p, tp_field_read_callback, NULL, &data);

finish:

    csv_free(&p);

close:
    filp_close(config_file, NULL);
exit:
    set_fs(fs);

    return ret;
}

void print_oneline_rxnumdata(int i, int *pData)
{
    TS_LOG_INFO("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
        %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
        %d, %d, %d, %d \n", \
        pData[i+0], pData[i+1], pData[i+2], pData[i+3], pData[i+4],pData[i+5], pData[i+6], pData[i+7], pData[i+8], pData[i+9], \
        pData[i+10], pData[i+11], pData[i+12], pData[i+13], pData[i+14],pData[i+15], pData[i+16], pData[i+17], pData[i+18], pData[i+19], \
        pData[i+20], pData[i+21], pData[i+22], pData[i+23]);
}

void print_oneline_txnumdata(int i, int *pData)
{
    TS_LOG_INFO("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
        %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
        %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
        %d, %d, %d, %d, %d, %d\n", \
        pData[i+0], pData[i+1], pData[i+2], pData[i+3], pData[i+4],pData[i+5], pData[i+6], pData[i+7], pData[i+8], pData[i+9], \
        pData[i+10], pData[i+11], pData[i+12], pData[i+13], pData[i+14],pData[i+15], pData[i+16], pData[i+17], pData[i+18], pData[i+19], \
        pData[i+20], pData[i+21], pData[i+22], pData[i+23], pData[i+24],pData[i+25], pData[i+26], pData[i+27], pData[i+28], pData[i+29], \
        pData[i+30], pData[i+31], pData[i+32], pData[i+33], pData[i+34],pData[i+35]);
}


void mmi_info_limit_print(struct cyttsp5_sensor_info_limit *mmi_info)
{

    int iRxNum = CSV_RX_NUM;
    int iRxMulTxNum = CSV_RX_NUM*CSV_TX_NUM;

    int  i =0;
    int *pData = NULL;

    //printf opens;
    pData = mmi_info->opens.min;
    TS_LOG_INFO("%s,  opens.min data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }
    pData = mmi_info->opens.ebye_rx;
    TS_LOG_INFO("%s,  opens.ebye_rx data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }
    TS_LOG_INFO("%s,  opens.ebye_rx_allowed_max data is %d\n", __func__, mmi_info->opens.ebye_rx_allowed_max);
    TS_LOG_INFO("%s,  opens.ebye_rx_allowed_max_num data is %d\n", __func__, mmi_info->opens.ebye_rx_allowed_max_num);
    pData = mmi_info->opens.ebye_tx;
    TS_LOG_INFO("%s,  opens.ebye_tx data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }
    TS_LOG_INFO("%s,  opens.ebye_tx_allowed_max data is %d\n", __func__, mmi_info->opens.ebye_tx_allowed_max);
    TS_LOG_INFO("%s,  opens.ebye_tx_allowed_max_num data is %d\n", __func__, mmi_info->opens.ebye_tx_allowed_max_num);

    //printf idac;
    pData = mmi_info->idac.max;
    TS_LOG_INFO("%s,  idac data max is \n", __func__);
    print_oneline_txnumdata(0, pData);
    pData = mmi_info->idac.min;
    TS_LOG_INFO("%s,  idac data min is \n", __func__);
    print_oneline_txnumdata(0, pData);
    pData = mmi_info->idac.delta;
    TS_LOG_INFO("%s,  idac data delta is \n", __func__);
    print_oneline_txnumdata(0, pData);

    //printf local pwc;
    pData = mmi_info->localPWC.max;
    TS_LOG_INFO("%s,  localPWC.max data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }
    pData = mmi_info->localPWC.min;
    TS_LOG_INFO("%s,  localPWC.min data  is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }

    //printf nutual noise;
    pData = mmi_info->mutual_noise.max;
    TS_LOG_INFO("%s,  mutual_noise.max data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }

    //printf nutual rawdata;
    pData = mmi_info->mutual_rawdata.max;
    TS_LOG_INFO("%s,  mutual_rawdata.max data is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }
    pData = mmi_info->mutual_rawdata.min;
    TS_LOG_INFO("%s,  mutual_rawdata.min data  is \n", __func__);
    for(i=0; i<iRxMulTxNum;i+=iRxNum) {
        print_oneline_rxnumdata(i, pData);
    }

    //printf self noise;
    pData = mmi_info->self_noise.max;
    TS_LOG_INFO("%s,  self_noise.max data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);

    //printf self rawdata;
    pData = mmi_info->self_rawdata.max;
    TS_LOG_INFO("%s,  self_rawdata.max data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);
    pData = mmi_info->self_rawdata.min;
    TS_LOG_INFO("%s,  self_rawdata.min data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);

    //printf self localpwc;
    TS_LOG_INFO("%s,  selflocalPWC.self_gidac_max_rx data is %d \n", __func__, mmi_info->selflocalPWC.self_gidac_max_rx);
    TS_LOG_INFO("%s,  selflocalPWC.self_gidac_max_tx data is %d \n", __func__, mmi_info->selflocalPWC.self_gidac_max_tx);
    TS_LOG_INFO("%s,  selflocalPWC.self_gidac_min_rx data is %d \n", __func__, mmi_info->selflocalPWC.self_gidac_min_rx);
    TS_LOG_INFO("%s,  selflocalPWC.self_gidac_min_tx data is %d \n", __func__, mmi_info->selflocalPWC.self_gidac_min_tx);
    pData = mmi_info->selflocalPWC.max;
    TS_LOG_INFO("%s,  selflocalPWC.max data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);
    pData = mmi_info->selflocalPWC.min;
    TS_LOG_INFO("%s,  selflocalPWC.max data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);
    pData = mmi_info->selflocalPWC.delta;
    TS_LOG_INFO("%s,  selflocalPWC.delta data(rx->tx) is \n", __func__);
    print_oneline_rxnumdata(0, pData);
    print_oneline_txnumdata(0, pData+iRxNum);

    TS_LOG_INFO("%s,  END.\n", __func__);
}

static int cyttsp5_get_sensor_info(struct device *dev)
{
    int retval = 0;
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_device_access_data *dad = cyttsp5_get_device_access_data(dev);
    char config_file_name[100]={0};
    const char *product_name = cd->cpdata->product_name;
    const char *chip_name = cd->cpdata->chip_name;
    u8 panel_id = cd->panel_id;
    char CIndex[2] = {0};
    int i=0;
    int length=0;

    int hw_mmi_index = dad->hw_mmi_index;
    //get tx number & rx number by systeninfo.
    mmi_info_limit.tx_num = cd->sysinfo.sensing_conf_data.electrodes_y;
    mmi_info_limit.rx_num = cd->sysinfo.sensing_conf_data.electrodes_x;

    TS_LOG_INFO("%s,tx_num = %d, rx_num = %d,hw_mmi_index = %d.\n", __func__,
                mmi_info_limit.tx_num,mmi_info_limit.rx_num,hw_mmi_index);

    if(mmi_info_limit.tx_num <= 0 || mmi_info_limit.rx_num <= 0){
        TS_LOG_ERR("%s,get tx number & rx number by systeninfo error.\n", __func__);
        retval = -EINVAL;
        goto out;
    }

    TS_LOG_INFO("%s,product_name is %s, chip_name is %s, panel_id is %d.\n", __func__, product_name, chip_name, panel_id);

    //get file name. the format is product_name_chip_name_PanelStr_index.csv(eg: Gemini_TMA568_ofilm_0.csv)
    strncat(config_file_name,TP_CONFIG_FILE_PATH, strlen(TP_CONFIG_FILE_PATH));
    strncat(config_file_name,product_name,strlen(product_name));
    strncat(config_file_name,"_",strlen("_"));
    strncat(config_file_name,chip_name,strlen(chip_name));
    strncat(config_file_name,"_",strlen("_"));

    //get panel string
    length = sizeof(hw_panel_info)/sizeof(struct cyttsp5_panel_info);
    for(i = 0; i < length; i++) {
        if(panel_id == hw_panel_info[i].panel_id) {
            retval = strncasecmp(hw_panel_info[i].product_name, product_name, strlen(hw_panel_info[i].product_name));
            if(retval == 0) {
                retval = strncasecmp(hw_panel_info[i].chip_name, chip_name, strlen(hw_panel_info[i].chip_name));
                if(retval == 0) {
                    strncat(config_file_name,hw_panel_info[i].id2str,strlen(hw_panel_info[i].id2str));
                }
            }
        }
    }

    strncat(config_file_name,"_",strlen("_"));
    CIndex[0] = (char)(hw_mmi_index+'0');
    strncat(config_file_name,CIndex,1);
    strcat(config_file_name,".csv");

    TS_LOG_INFO("%s, config_file_name is %s.\n", __func__, config_file_name);

    retval = tp_configuration_get(config_file_name,  &mmi_info_limit);

    if (retval) {
        TS_LOG_ERR("%s, Fail getting configuration.\n", __func__);
        goto out;
    }

    mmi_info_limit_print(&mmi_info_limit);

out:
    return retval;
}

int cyttsp5_get_mmi_test_limit(struct device_node *node)
{
    //no need parse dts data
    return 0;
}

u8 cyttsp5_command_status(struct device *dev)
{
    struct cyttsp5_device_access_data *dad = cyttsp5_get_device_access_data(dev);
    return dad->status;
}

int cyttsp5_command_response(struct device *dev,u8 *buf)
{
    int ret = -1;
    ssize_t num_read;
    //struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
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

int cyttsp5_send_command(struct device *dev,char *buf)
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

    rc = gcmd->nonhid_cmd->user_cmd(dev, 1, CY_MAX_PRBUF_SIZE,
            dad->response_buf, length, dad->ic_buf,
            &dad->response_length);
    if (rc) {
        dad->response_length = 0;
        TS_LOG_ERR("%s: Failed to store command\n", __func__);
    } else {
        dad->status = 1;
    }

exit:
    mutex_unlock(&dad->sysfs_lock);
    TS_LOG_DEBUG("%s: return rc = %d\n", __func__, rc);
    return rc;
}

static int cyttsp5_change_scan_status(struct device *dev,int value)
{
    int ret = -1;

    char *Command_function[] = {
        "0x04 0x00 0x05 0x00 0x2F 0x00 0x03",  //Suspend Scan
        "0x04 0x00 0x05 0x00 0x2F 0x00 0x2A",  //Panel Scan
        "0x04 0x00 0x05 0x00 0x2F 0x00 0x04"   //Resume scan
    };

    if(value != 0 && value != 1 && value != 2){
        TS_LOG_ERR( "%s Input value is error,value = %d.\n",__func__,value);
        return -1;
    }

    ret = cyttsp5_send_command(dev,Command_function[value]);
    if (ret < 0) {
        TS_LOG_ERR( "%s Failed to change scan status.\n",__func__);
        return -1;
    }

    return 0;
}

static void cyttsp5_build_test_command(struct device *dev,char *cmd,char *data_id,int data_len)
{
    int i,j;
    int readlength = 0;
    char *cmd_head = "0x04 0x00 0x0A 0x00 0x2F 0x00 ";
    char tmp_cmd_str[CY_READ_CMD_MAX_LEN] = {0};
    char tmp_cmd[32] = {0};
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    /*
    Data ID As show:
    0x00 Mutual-cap Raw Data
    0x01 Mutual-cap Baseline Data
    0x02 Mutual-cap Difference/Signal Data
    0x03 Self-cap Raw Data
    0x04 Self-cap Baseline Data
    0x05 Self-cap Difference/Signal Data
    */

    /*read 0x64 bytes once*/

    /* "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B|0x00 0x00|0x64 0x00|0x00" */
    /*************************************|read len |offset   |*******/
    /**************Command Head **********|lsb, msb |lsb, msb | Data ID|*/

    /* read raw data command
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0x00 0x00 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0x64 0x00 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0xc8 0x00 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0x2C 0x01 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0x90 0x01 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0xF4 0x01 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0x58 0x02 0x64 0x00 0x00",
    "0x04 0x00 0x0A 0x00 0x2F 0x00 0x2B 0xBC 0x02 0x0E 0x00 0x00"
    */

    TS_LOG_DEBUG("Enter %s,cmd = %s,data_id = %s,data_len = %d.\n",
                    __func__,cmd,data_id,data_len);

    memset(tmp_cmd,0,sizeof(tmp_cmd));
    memset(tmp_cmd_str,0,sizeof(tmp_cmd_str));

    for(i = 0,j = 0;i < data_len;i += CY_READ_DATA_LEN,j++){
        if(data_len - i > CY_READ_DATA_LEN){
            readlength = CY_READ_DATA_LEN;
        }else{
            readlength = data_len - i;
        }

        strncpy(tmp_cmd_str,cmd_head,sizeof(tmp_cmd_str));
        strncat(tmp_cmd_str,cmd,sizeof(tmp_cmd_str));
        snprintf(tmp_cmd,PAGE_SIZE," 0x%02X 0x%02X 0x%02X 0x%02X ", i%256,i/256,readlength,0);
        strncat(tmp_cmd_str,tmp_cmd,sizeof(tmp_cmd_str));
        strncat(tmp_cmd_str,data_id,sizeof(tmp_cmd_str));

        strncpy(dad->read_cmd[j],(const char *)tmp_cmd_str,sizeof(dad->read_cmd[j]));

        TS_LOG_DEBUG("%s,read_cmd[%d] = %s.\n",__func__,j,dad->read_cmd[j]);

        memset(tmp_cmd,0,sizeof(tmp_cmd));
        memset(tmp_cmd_str,0,sizeof(tmp_cmd_str));
    }
}

static int cyttsp5_get_SensorData(struct device *dev,char *id,char *cmd,
                int data_len,int data_byte,int other)
{
    int i,j;
    int ret = -1;
    int read_times = 0;
    u8 tmp_buf[CY_READ_DATA_LEN * 2 + CY_DATA_HEAD_LEN] = { 0 };
    char *open_test_command =  "0x04 0x00 0x07 0x00 0x2F 0x00 0x26 0x03 0x00";
    int tx_num = 0;
    int rx_num = 0;
    int index = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    memset(dad->read_cmd,0,sizeof(dad->read_cmd));
    memset(dad->data_buf,0,sizeof(dad->data_buf));

    tx_num = mmi_info_limit.tx_num;
    rx_num = mmi_info_limit.rx_num;

    if(data_len <= CY_READ_DATA_LEN){
        read_times = 1;
    }else{
        read_times = (tx_num * rx_num + tx_num + 2)/CY_READ_DATA_LEN + 1;
    }

    cyttsp5_build_test_command(dev,cmd,id,data_len);

    //Suspend Scan
    ret = cyttsp5_change_scan_status(dev,0);
    if (ret < 0 ) {
        TS_LOG_ERR("%s Failed to suspend scan.\n",__func__);
        return  -1;
    }

    mdelay(30);

    //Panel Scan
    ret = cyttsp5_change_scan_status(dev,1);
    if (ret < 0 ) {
        TS_LOG_ERR( "%s Failed to scan panel once.\n",__func__);
        goto exit;
    }

    mdelay(30);

    //OPEN TEST
    if(other == CYTTSP5_GET_OPENS){
        ret = cyttsp5_send_command(dev,open_test_command);
        if(ret < 0){
            TS_LOG_ERR("%s Failed to send command.\n",__func__);
            goto exit;
        }
    }

    for(i = 0;i < read_times;i++){
        memset(tmp_buf,0,sizeof(tmp_buf));
        mdelay(30);
        ret = cyttsp5_send_command(dev,dad->read_cmd[i]);
        if(ret < 0 ){
            TS_LOG_ERR("%s Failed to send command.\n",__func__);
            goto exit;
        }

        mdelay(30);

        ret = cyttsp5_command_response(dev,tmp_buf);
        if(ret < 0){
            TS_LOG_ERR("%s Failed to get response.\n",__func__);
            goto exit;
        }

        for(j = CY_DATA_HEAD_LEN;j < dad->response_length;j += data_byte){
            index = i * CY_READ_DATA_LEN + (j - CY_DATA_HEAD_LEN)/data_byte;
            if(data_byte == CYTTSP5_DATA_ONE_BYTE){
                dad->data_buf[index]  = (int)tmp_buf[j];
            }else if(data_byte == CYTTSP5_DATA_TWO_BYTE){
                dad->data_buf[index] = (int)get_unaligned_le16(&tmp_buf[j]);
            }
            if(dad->data_buf[index] > 32767){
                dad->data_buf[index] -= 65535;
            }
        }
    }

    //Print data
    for(i = 0; i < data_len; i++) {
        if((i+1)%mmi_info_limit.rx_num == 0) {
            printk("%6d\n", dad->data_buf[i]);
        } else {
            printk("%6d", dad->data_buf[i]);
        }
    }

exit:
    //Resume scan
    cyttsp5_change_scan_status(dev,2);
    return ret;
}


static int cyttsp5_get_rawdata(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int check_flag = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    struct cyttsp5_sensor_mutual_rawdata m_rawdata = mmi_info_limit.mutual_rawdata;
    int length = mmi_info_limit.tx_num * mmi_info_limit.rx_num;
    int j =0;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;

    TS_LOG_DEBUG("%s, length = %d.\n",__func__,length);

    ret = cyttsp5_get_SensorData(dev,"0x00","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    j=0;
    for(i = 0;i < length;i++){
        if(dad->data_buf[i] > m_rawdata.max[j]
        || dad->data_buf[i] < m_rawdata.min[j]){
            TS_LOG_ERR( "%s check is failed. dad->data_buf[%d] is %d\n",__func__, i, dad->data_buf[i]);
            check_flag = -1;
            break;
        }

        //jump over null data
        if( (i+1)%mmi_info_limit.rx_num == 0 ) {
            j += iDiff;
        }
        j++;
    }

    return check_flag;

exit:
    return -1;
}

static int cyttsp5_get_self_rawdata(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int check_flag = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int length = mmi_info_limit.tx_num + mmi_info_limit.rx_num;
    int j =0;
    struct cyttsp5_sensor_self_rawdata s_rawdata = mmi_info_limit.self_rawdata;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;

    ret = cyttsp5_get_SensorData(dev,"0x03","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    j = 0;
    for(i = 0;i < length;i++){
        if(dad->data_buf[i] > s_rawdata.max[j] || dad->data_buf[i] < s_rawdata.min[j]){
            TS_LOG_ERR( "%s check is failed. dad->data_buf[%d] is %d. s_rawdata[%d] min %d- max %d \n",__func__, i, dad->data_buf[i],  j, s_rawdata.min[j], s_rawdata.max[j]);
            check_flag = -1;
            break;
        }
        //jump over null data
        if( (i+1) == mmi_info_limit.rx_num ) {
            j += iDiff;
        }
        j++;
    }

    return check_flag;

exit:
    return -1;

}

static int cyttsp5_get_mutual_noise(struct device *dev)
{
    int i,k;
    int ret = -1;
    int * max_raw = NULL;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int length = mmi_info_limit.tx_num * mmi_info_limit.rx_num;

    struct cyttsp5_sensor_mutual_noise mut_noise = mmi_info_limit.mutual_noise;
    int j =0;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;

    max_raw = kzalloc(sizeof(int) * length,GFP_KERNEL);
    if(max_raw == NULL){
        TS_LOG_ERR( "%s: Error, kzalloc\n", __func__);
        return -1;
    }

    //get 5 max value
    for (k = 0; k < 5; k++) {
        ret = cyttsp5_get_SensorData(dev,"0x00","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
        if (ret < 0) {
            TS_LOG_ERR( "%s get rawdata failed.\n",__func__);
            goto exit;
        }
        if (k ==0 ) {
            memcpy(max_raw,dad->data_buf,sizeof(int) * length);
        } else {
            for (i = 0; i < length; i++) {
                max_raw[i] = max(dad->data_buf[i],max_raw[i]);
            }
        }
    }

    j =0;
    for (i = 0; i < length; i++) {
        if(mut_noise.max[j] < max_raw[i]) {
            TS_LOG_ERR( "%s mutual noise check  failed. max_raw[%d] is %d, mut_noise.max[%d] is %d \n",__func__, i, max_raw[i], j, mut_noise.max[j]);
            goto exit;
        }
        //jump over null data
        if( (i+1)%mmi_info_limit.rx_num == 0 ) {
            j += iDiff;
        }
        j++;
    }

exit:
    kfree(max_raw);
    max_raw = NULL;
    return ret;
}


static int cyttsp5_get_self_noise(struct device *dev)
{
    int i,k;
    int ret = 0;
    int * max_raw = NULL;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int length = mmi_info_limit.tx_num + mmi_info_limit.rx_num;
    int j =0;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;
    struct cyttsp5_sensor_self_noise s_noise = mmi_info_limit.self_noise;

    max_raw = kzalloc(sizeof(int) * length,GFP_KERNEL);
    if(max_raw == NULL){
        TS_LOG_ERR( "%s: Error, kzalloc\n", __func__);
        return -1;
    }

    for (k = 0; k < 5; k++) {
        ret = cyttsp5_get_SensorData(dev,"0x03","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
        if (ret < 0) {
            TS_LOG_ERR( "%s get self rawdata failed.\n",__func__);
            goto exit;
        }
        if (k == 0) {
            memcpy(max_raw,dad->data_buf,sizeof(int) * length);
        } else {
            for (i = 0; i < length; i++) {
                max_raw[i] = max(dad->data_buf[i],max_raw[i]);
            }
        }
    }

    j =0;
    for (i = 0; i < length; i++) {
        if(s_noise.max[j] < max_raw[i]) {
            TS_LOG_ERR( "%s self noise check  failed.  max_raw[%d] is %d, s_noise.max[%d] is %d \n",__func__, i, max_raw[i], j, s_noise.max[j]);
            goto exit;
        }
        //jump over null data
        if( (i+1) == mmi_info_limit.rx_num ) {
            j += iDiff;
        }
        j++;
    }

exit:
    kfree(max_raw);
    max_raw = NULL;
    return ret;
}

static int cyttsp5_get_LocalPWC(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int check_flag = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = mmi_info_limit.tx_num;
    int rx_num = mmi_info_limit.rx_num;
    int length = tx_num * rx_num;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;
    int j =0;
    int iHeadNum = tx_num + 4-tx_num%4;
    struct cyttsp5_sensor_localPWC localPWC = mmi_info_limit.localPWC;

    //this command also read GlobalGIDAC
    ret = cyttsp5_get_SensorData(dev,"0x00","0x24",length + (tx_num + 4-tx_num%4),
                                    CYTTSP5_DATA_ONE_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    j =0;
    for(i = 0;i < length;i++){
       if(dad->data_buf[iHeadNum+i] > localPWC.max[j] || dad->data_buf[iHeadNum+i] < localPWC.min[j]){
            TS_LOG_ERR( "%s check is failed. dad->data_buf[%d] is %d, localPWC[%d] max[%d] min[%d]\n",
                __func__, i, dad->data_buf[iHeadNum+i], j, localPWC.max[j], localPWC.min[j]);
            check_flag = -1;
            break;
        }
        if( (i+1)%mmi_info_limit.rx_num == 0 ) {
            j += iDiff;
        }
        j++;
    }

    return check_flag;

exit:
    return -1;
}

static int cyttsp5_get_GlobalGIDAC(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int range_flag = 0;
    int delta_flag = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = mmi_info_limit.tx_num;

    struct cyttsp5_sensor_idac idac =     mmi_info_limit.idac;

    //the data length which will be readed must be a multiple of 4.
    ret = cyttsp5_get_SensorData(dev,"0x00","0x24",tx_num + 4-tx_num%4,CYTTSP5_DATA_ONE_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    //we can only check the real tx num
    for(i = 0;i < tx_num;i++){
        if(dad->data_buf[i] > idac.max[i] || dad->data_buf[i] < idac.min[i]){
            TS_LOG_ERR( "%s check is failed, dad->data_buf[%d] is %d, idac max[%d] min[%d].\n",
                __func__, i, dad->data_buf[i], idac.max[i], idac.min[i]);
            range_flag = -1;
            goto exit;
        }
    }

    for(i = 0;i < tx_num-1;i++){
        if(abs(dad->data_buf[i] - dad->data_buf[i+1]) > idac.delta[i]){
            TS_LOG_ERR( "%s uniformity check is failed,  delta data is [%d]%d-%d.\n",__func__, i, dad->data_buf[i], dad->data_buf[i+1]);
            delta_flag = -1;
            break;
        }
    }

    return delta_flag;

exit:
    return -1;
}

static int cyttsp5_get_SelfLocalPWC(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int tx_flag = 0;
    int rx_flag = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = mmi_info_limit.tx_num;
    int rx_num = mmi_info_limit.rx_num;
    int rx_add_tx = rx_num+tx_num;

    int j =0;
    int iDiff = CSV_RX_NUM-rx_num;
    int iHeadNum = 2;

    struct cyttsp5_sensor_selflocalPWC sPWC = mmi_info_limit.selflocalPWC;

    ret = cyttsp5_get_SensorData(dev,"0x01","0x24",tx_num + rx_num + 2,CYTTSP5_DATA_ONE_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }


   if( (dad->data_buf[0] > sPWC.self_gidac_max_rx ) || (dad->data_buf[0] < sPWC.self_gidac_min_rx) ) {
        TS_LOG_ERR( "%s  Self-cap Global iDAC check rx is failed. value is %d\n",__func__, dad->data_buf[0] );
        rx_flag = -1;
        goto exit;
    }

    if( (dad->data_buf[1] > sPWC.self_gidac_max_tx) || (dad->data_buf[1] < sPWC.self_gidac_min_tx) ) {
        TS_LOG_ERR( "%s  Self-cap Global iDAC check tx is failed. value is %d\n",__func__, dad->data_buf[1] );
        tx_flag = -1;
        goto exit;
    }

    //check current value is between max and min
    j=0;
    for(i = 0;i < rx_add_tx;i++){
        if( (dad->data_buf[iHeadNum+i] > sPWC.max[j]) || (dad->data_buf[iHeadNum+i] < sPWC.min[j]) ) {
            if(i<rx_num){
                TS_LOG_ERR( "%s  Self-cap Local PWC rx %d check is failed. value is %d. sPWC[%d] min %d-max %d.\n",__func__, i, dad->data_buf[iHeadNum+i], j, sPWC.min[j], sPWC.max[j] );
                rx_flag = -1;
            }
            else{
                TS_LOG_ERR( "%s  Self-cap Local PWC tx %d check is failed. value is %d. sPWC[%d] min %d-max %d.\n",__func__, i, dad->data_buf[iHeadNum+i],  j, sPWC.min[j], sPWC.max[j] );
                tx_flag = -1;
            }
            goto exit;
        }

        if( (i+1) == mmi_info_limit.rx_num ){
            j += iDiff;
        }
        j++;
    }

    //check all near value is in delta scope
    j=0;
    for(i = 0;i < rx_add_tx-1;i++){
        if( (i+1) == mmi_info_limit.rx_num ) {
            j += iDiff+1;
            continue;
        }
        if(abs(dad->data_buf[iHeadNum+i] - dad->data_buf[iHeadNum+i+1]) > sPWC.delta[j]) {
            if(i<rx_num){
                TS_LOG_ERR( "%s  Self-cap Local PWC delta rx %d check is failed. value is %d-%d. sPWC[%d] delta %d.\n",__func__, i, dad->data_buf[iHeadNum+i], dad->data_buf[iHeadNum+i+1], j, sPWC.delta[j] );
                rx_flag = -1;
            }
            else{
                TS_LOG_ERR( "%s  Self-cap Local PWC delta tx %d check is failed. value is %d-%d. sPWC[%d] delta %d.\n",__func__, i, dad->data_buf[iHeadNum+i],  dad->data_buf[iHeadNum+i+1], j, sPWC.delta[j] );
                tx_flag = -1;
            }
            goto exit;
        }
        j++;
    }

    ret = (tx_flag < 0 ||  rx_flag < 0)  ? -1  : 0;

    return ret;

exit:
    return -1;
}

static int cyttsp5_get_OPENS(struct device *dev)
{
    int ret  = -1;
    int i = 0;
    int * opens_diff = NULL;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = mmi_info_limit.tx_num;
    int rx_num = mmi_info_limit.rx_num;
    int length = tx_num * rx_num;
    int j =0;
    int iDiff = CSV_RX_NUM-mmi_info_limit.rx_num;
    struct cyttsp5_sensor_opens sen_opens = mmi_info_limit.opens;

    int rx_allowed_max = sen_opens.ebye_rx_allowed_max;
    int rx_allowed_max_num = sen_opens.ebye_rx_allowed_max_num;
    int tx_allowed_max = sen_opens.ebye_tx_allowed_max;
    int tx_allowed_max_num = sen_opens.ebye_tx_allowed_max_num;
    int iCount = 0;

    opens_diff = kzalloc(sizeof(int) * length,GFP_KERNEL);
    if(opens_diff == NULL){
        TS_LOG_ERR( "%s: Error, kzalloc\n", __func__);
        return -1;
    }

    ret = cyttsp5_get_SensorData(dev,"0x03","0x27",length, CYTTSP5_DATA_ONE_BYTE, 1);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    //check min
    j=0;
    for(i = 0;i< length ;i++) {
        if( dad->data_buf[i] < sen_opens.min[j]){
            TS_LOG_ERR("%s Opens MIN LIMITS error. %d data is %d, sen_opens.min[%d] is %d\n",__func__, i, dad->data_buf[i], j, sen_opens.min[j] );
            goto exit;
        }
        //jump over null data
        if( (i+1)%mmi_info_limit.rx_num == 0){
            j += iDiff;
        }
        j++;
    }

    //rx uniformity
    for(i = 0;i< length -1 ;i++) {
        if((i+1)%rx_num != 0){
            opens_diff[i] = (int)(dad->data_buf[i] - dad->data_buf[i+1]);//左右相减
        }else{
            opens_diff[i] = 0;
        }
    }

    iCount = 0;
    j=0;
    for(i = 0;i< length-1 ;i++) {  //差值需要考虑
        //uniformity E-By-E

        //not check the last row diff value
        if( (i+1)%mmi_info_limit.rx_num == 0){
            //jump over null data and last 0
            j += iDiff+1;
            continue;
        }

        if(abs(opens_diff[i]) > sen_opens.ebye_rx[j]){
            TS_LOG_ERR( "%s rx uniformity E-By-E check is failed, opens_diff[%d] is %d, sen_opens.ebye_rx[%d] is %d\n",__func__, i, opens_diff[i], j, sen_opens.ebye_rx[j]);
            goto exit;
        }

        //check whether the allowed max data num is ok
        if( abs(opens_diff[i]) > rx_allowed_max ) {
            iCount++;
            if( iCount > rx_allowed_max_num) {
                TS_LOG_ERR( "%s allowed max data num check failed, num is %d, allowed num is %d\n",__func__, iCount, rx_allowed_max_num);
                goto exit;
            }
        }

        j++;
    }

    //tx uniformity
    for(i = 0;i< rx_num * (tx_num -1); i++) {
        opens_diff[i] = (int)(dad->data_buf[i] - dad->data_buf[i + rx_num]);//上下相减
    }

    iCount = 0;
    j=0;
    for(i = 0; i< rx_num * (tx_num -1); i++) {
        //uniformity E-By-E
        if(abs(opens_diff[i]) > sen_opens.ebye_tx[j]){
            TS_LOG_ERR( "%s tx uniformity E-By-E check is failed, opens_diff[%d] is %d, sen_opens.ebye_tx[%d] is %d.\n",__func__, i, opens_diff[i], j, sen_opens.ebye_tx[j]);
            goto exit;
        }

        //check whether the allowed max data num is ok
        if( abs(opens_diff[i]) > tx_allowed_max ) {
            iCount++;
            if( iCount > tx_allowed_max_num) {
                TS_LOG_ERR( "%s allowed max data num check failed, num is %d, allowed num is %d\n",__func__, iCount, tx_allowed_max_num);
                goto exit;
            }
        }

        //jump over null data
        if( (i+1)%mmi_info_limit.rx_num == 0 ) {
            j += iDiff;
        }
        j++;
    }

    kfree(opens_diff);
    opens_diff = NULL;
    return 0;

exit:
    kfree(opens_diff);
    opens_diff = NULL;
    return -1;
}

static int cyttsp5_get_mutual_baseline(struct device *dev)
{
    int ret  = -1;

    int length = mmi_info_limit.tx_num * mmi_info_limit.rx_num;
    //struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    ret = cyttsp5_get_SensorData(dev,"0x01","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    return ret;

exit:
    return -1;
}

static int cyttsp5_get_self_baseline(struct device *dev)
{
    int ret  = -1;

    int length = mmi_info_limit.tx_num + mmi_info_limit.rx_num;

    ret = cyttsp5_get_SensorData(dev,"0x04","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    return ret;

exit:
    return -1;
}

static int cyttsp5_get_mutual_diff(struct device *dev)
{
    int ret  = -1;

    int length = mmi_info_limit.tx_num * mmi_info_limit.rx_num;

    ret = cyttsp5_get_SensorData(dev,"0x02","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    return ret;

exit:
    return -1;
}

static int cyttsp5_get_self_diff(struct device *dev)
{
    int ret  = -1;

    int length = mmi_info_limit.tx_num + mmi_info_limit.rx_num;

    ret = cyttsp5_get_SensorData(dev,"0x05","0x2B",length,CYTTSP5_DATA_TWO_BYTE,0);
    if(ret < 0){
        TS_LOG_ERR("%s error.\n",__func__);
        goto exit;
    }

    return ret;

exit:
    return -1;
}

static int cyttsp5_short_test(struct device *dev)
{
    int ret = -1;
    int i = 0;
    int check_flag = 1;
    u8 data_buf[100] = {0};
    char* short_command = "0x04 0x00 0x07 0x00 0x2F 0x00 0x26 0x04 0x00";
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    memset(dad->data_buf, 0, sizeof(dad->data_buf));
    //Suspend Scan
    ret = cyttsp5_change_scan_status(dev,0);
    if(ret < 0 ){
        TS_LOG_ERR( "%s Failed to suspend scan.\n",__func__);
        return -1;
    }

    //SHORT TEST
    mdelay(30);
    ret = cyttsp5_send_command(dev,short_command);
    if(ret < 0){
        TS_LOG_ERR("%s Failed to send command.\n",__func__);
        goto exit;
    }

    mdelay(30);
    ret = cyttsp5_command_response(dev,data_buf);
    if(ret < 0){
        TS_LOG_ERR( "%s Failed to get response.\n",__func__);
        goto exit;
    }

    for (i = 0; i < 7; i++) {
        dad->data_buf[i] = data_buf[i];
    }
    if (data_buf[0] == 0x07
        && data_buf[2] == 0x1F
        && (data_buf[4] == 0xA6 || data_buf[4] == 0x26)) {
            if (data_buf[5] != 0x0 || data_buf[6] != 0x0) {
                TS_LOG_ERR("%s Short test failed.\n",__func__);
                check_flag = 0;
        }
    } else {
        TS_LOG_ERR("%s Short test failed.\n",__func__);
        check_flag = 0;
    }

exit:
    //Resume scan
    cyttsp5_change_scan_status(dev,2);

    if (check_flag == 0) {
        for (i = 0; i < 7; i++) {
            printk("0x%2x ", data_buf[i]);
        }
        printk("\n");

        return -2;
    }

    return ret;
}

static int cyttsp5_get_system_info(struct device *dev)
{
    int ret = -1;
    int i = 0;
    u8 data_buf[51] = {0};/*short need read 51*/
    char* systeminfo_command = "0x04 0x00 0x05 0x00 0x2F 0x00 0x02";
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    memset(data_buf, 0, sizeof(data_buf));
    memset(dad->data_buf, 0, sizeof(dad->data_buf));

    //Send Opens Test command to command sysfs node.
    ret = cyttsp5_send_command(dev,systeminfo_command);
    if (ret < 0) {
        TS_LOG_ERR("%s Failed to send command.\n",__func__);
        goto exit;
    }

    mdelay(30);

    ret = cyttsp5_command_response(dev,data_buf);
    if(ret < 0){
        TS_LOG_ERR( "%s Failed to get response.\n",__func__);
        goto exit;
    }


    for (i = 0; i < 51; i++) {
        dad->data_buf[i] = data_buf[i];
    }

exit:

    return ret;
}

static int cyttsp5_i2c_check(struct device *dev)
{
    int rc = 0;
    char *ping_cmd = "0x04 0x00 0x05 0x00 0x2F 0x00 0x00";
    char data_buf[5] = {0};
    //struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    rc = cyttsp5_send_command(dev,ping_cmd);
    if(rc < 0){
        TS_LOG_ERR("%s Failed to send command.\n",__func__);
        goto exit;
    }

    rc = cyttsp5_command_response(dev,data_buf);
    if(rc < 0){
        TS_LOG_ERR( "%s Failed to get response.\n",__func__);
        goto exit;
    }

    if(  data_buf[0] == 0x05 && data_buf[1] == 0x00
     &&  data_buf[2] == 0x1F && data_buf[3] == 0x00
     && (data_buf[4] == 0x80 || data_buf[4] == 0x00)){
        rc = 0;
    }else{
        rc  = -1;
    }

exit:

    return rc;
}


#define PRINT_SENSOR_DATA(index,length_long,rx_num,data_buf,m) \
do{ \
   for (index = 0; index < length_long; index++) {\
       if((index + 1) % rx_num == 0){\
           seq_printf(m, "%6d\n", data_buf[index]);\
       }else{\
           seq_printf(m, "%6d", data_buf[index]);\
       }\
   }\
   seq_printf(m, "\n"); \
}while(0);

static int cyttsp5_proc_data_print(struct device *dev,int *data_buf,struct seq_file *m)
{
    int index = 0;
    char *temp = NULL;
     int tx_num = mmi_info_limit.tx_num;
    int rx_num = mmi_info_limit.rx_num;
    int length_long = mmi_info_limit.tx_num * mmi_info_limit.rx_num;
    int length_short = mmi_info_limit.tx_num + mmi_info_limit.rx_num;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    if(data_buf == NULL){
        TS_LOG_INFO("%s data_buf is NULL.\n",__func__);
        return 0;
    }

    switch (dad ->check_index) {
    case CYTTSP_MUTUAL_RAWDATA:
        seq_printf(m, "Mutual RawData:\n");
        PRINT_SENSOR_DATA(index,length_long,rx_num,data_buf,m);
        break;
    case CYTTSP_MUTUAL_DIFF:
        seq_printf(m, "Mutual Diff Data:\n");
        PRINT_SENSOR_DATA(index,length_long,rx_num,data_buf,m);
        break;
    case CYTTSP_MUTUAL_NOISE:
        seq_printf(m, "Mutual Noise Data:\n");
        PRINT_SENSOR_DATA(index,length_long,rx_num,data_buf,m);
        break;
    case CYTTSP_MUTUAL_BASELINE:
        seq_printf(m, "Mutual BaseLine Data:\n");
        PRINT_SENSOR_DATA(index,length_long,rx_num,data_buf,m);
        break;
    case CYTTSP_MUTUAL_LOCALPWC:
        seq_printf(m, "Mutual LocalPWC Data:\n");
        for (index = tx_num + 4-tx_num%4; index < length_long + tx_num + 4-tx_num%4; index++) {
            if((index + 1 - (tx_num + 4-tx_num%4)) % rx_num == 0){
                seq_printf(m, "%4d\n", data_buf[index]);
            }else{
                seq_printf(m, "%4d", data_buf[index]);
            }
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_GLOBAL_IDAC:
        seq_printf(m, "Global iDAC Data:\n");
        for (index = 0; index < tx_num + 4-tx_num%4; index++) {
            seq_printf(m, "%4d", data_buf[index]);
        }
        seq_printf(m, "\n");
        seq_printf(m, "Global iDAC Diff:\n");
        for (index = 0; index < tx_num + 4-tx_num%4 -1; index++) {
            seq_printf(m, "%4d", data_buf[index] - data_buf[index + 1]);
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_SELF_RAWDATA:
        seq_printf(m, "Self RawData:\n");
        PRINT_SENSOR_DATA(index,length_short,rx_num,data_buf,m);
        break;
    case CYTTSP_SELF_BASELINE:
        seq_printf(m, "Self BaseLine Data:\n");
        PRINT_SENSOR_DATA(index,length_short,rx_num,data_buf,m);
        break;
    case CYTTSP_SELF_DIFF:
        seq_printf(m, "Self Diff Data:\n");
        PRINT_SENSOR_DATA(index,length_short,rx_num,data_buf,m);
        break;
    case CYTTSP_SELF_NOISE:
        seq_printf(m, "Self Noise Data:\n");
        PRINT_SENSOR_DATA(index,length_short,rx_num,data_buf,m);
        break;;
    case CYTTSP_SHORT_INFO:
        seq_printf(m, "Short Info:\n");
        for (index = 0; index < 7; index++) {
            seq_printf(m, "%6d", data_buf[index]);
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_SELF_LOCALPWC:
        seq_printf(m, "Self TX iDAC:%4d.\n", data_buf[0]);
        seq_printf(m, "Self RX iDAC:%4d.\n", data_buf[1]);

        seq_printf(m, "Self TX LocalPWC:\n");
        for (index = 2;index < tx_num + 2; index++) {
            seq_printf(m, "%4d", data_buf[index]);
        }

        seq_printf(m, "\nTX Diff:\n");
        for (index = 2;index < tx_num + 1; index++) {
            seq_printf(m, "%4d", data_buf[index] - data_buf[index + 1]);
        }

        seq_printf(m, "\nSelf RX LocalPWC:\n");
        for (index = tx_num + 2;index < tx_num + rx_num + 2; index++) {
            seq_printf(m, "%4d", data_buf[index]);
        }

        seq_printf(m, "\nRX Diff:\n");
        for (index = tx_num + 2;index < tx_num + rx_num + 1; index++) {
            seq_printf(m, "%4d", data_buf[index] - data_buf[index + 1]);
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_OPENS_DATA:
        seq_printf(m, "Opens Data:\n");
        for (index = 0; index < length_long; index++) {
            if((index + 1) % rx_num == 0){
                seq_printf(m, "%4d\n", data_buf[index]);
            }else{
                seq_printf(m, "%4d", data_buf[index]);
            }
        }

        seq_printf(m, "\nRX Diff:\n");
        for(index = 0;index < length_long ;index++) {
            if((index + 1) % rx_num != 0){
                seq_printf(m, "%4d",(int)(data_buf[index] - data_buf[index+1]));
            } else {
                seq_printf(m, "%4d\n",0);
            }
        }
        seq_printf(m, "\nTX Diff:\n");
        for (index = 0; index < length_long - rx_num; index++) {
            if((index + 1) % rx_num == 0){
                seq_printf(m, "%4d\n",(int)(data_buf[index] - data_buf[index + rx_num]));
            }else{
                seq_printf(m, "%4d",(int)(data_buf[index] - data_buf[index + rx_num]));
            }
        }

        for (index = length_long - rx_num; index < length_long; index++) {
            seq_printf(m, "%4d",0);
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_SYSTEM_INFO:
        seq_printf(m, "System Info Data:\n");
        for (index = 0;index < 51; index++) {
            if((index + 1) == rx_num){
                seq_printf(m, "%4d\n", data_buf[index]);
            }else{
                seq_printf(m, "%4d", data_buf[index]);
            }
        }
        seq_printf(m, "\n");
        break;
    case CYTTSP_I2C_PING:
        temp = strstr(dad->check_result,"0P");
        if(temp == NULL){
            seq_printf(m, "I2C Check is failed.\n");
        }else{
            seq_printf(m, "I2C Check is successful.\n");
        }
        break;
    default:
        return -1;
    }
    return 0;
}

static struct cyttsp5_check_func_ cyttsp5_check_func[] = {
    {CYTTSP_I2C_PING, cyttsp5_i2c_check},
    {CYTTSP_MUTUAL_RAWDATA, cyttsp5_get_rawdata},
    {CYTTSP_GLOBAL_IDAC,cyttsp5_get_GlobalGIDAC},
    {CYTTSP_MUTUAL_LOCALPWC,cyttsp5_get_LocalPWC},
    {CYTTSP_OPENS_DATA,cyttsp5_get_OPENS},
    {CYTTSP_SELF_LOCALPWC,cyttsp5_get_SelfLocalPWC},
    {CYTTSP_SELF_RAWDATA,cyttsp5_get_self_rawdata},
    {CYTTSP_SHORT_INFO, cyttsp5_short_test},
    {CYTTSP_MUTUAL_BASELINE, cyttsp5_get_mutual_baseline},
    {CYTTSP_SELF_BASELINE, cyttsp5_get_self_baseline},
    {CYTTSP_MUTUAL_DIFF, cyttsp5_get_mutual_diff},
    {CYTTSP_SELF_DIFF, cyttsp5_get_self_diff},
    {CYTTSP_MUTUAL_NOISE, cyttsp5_get_mutual_noise},
    {CYTTSP_SELF_NOISE, cyttsp5_get_self_noise},
    {CYTTSP_SYSTEM_INFO, cyttsp5_get_system_info},
    {CYTTSP_CHECK_MAX, NULL},
};

int cyttsp5_check_items(struct device *dev,enum cyttsp5_sensor_check item, bool reset,int *data_buf)
{
    int retry = 0;
    int check_flag = -1;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    if (item < CYTTSP_I2C_PING || item >= CYTTSP_CHECK_MAX) {
        TS_LOG_ERR("%s: invalid input item\n", __func__);
        return -EINVAL;
    }

    if (cyttsp5_check_func[item].func) {
        for(retry = 0; retry < CHECK_RETRY_TIMES; retry++) {
            check_flag = cyttsp5_check_func[item].func(dev);
            if (check_flag >= 0) {
                break;
            } else {
                printk("%s:check item:%d, %dtimes failed\n",__func__, item, retry+1);
                if (reset) {
                    //cyttsp5_hw_reset_export();
                    msleep(500);
                }
            }
        }
    }

    if(data_buf != NULL){
        memcpy(data_buf,dad->data_buf,sizeof(int) * CY_MAX_RAW_DATA_LEN);
    }

    return check_flag;
}

#define CHECK_RESULT_SET(dev,flag,value) \
do {\
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);\
    strncat(dad->check_result,value,strlen(value));\
    if(flag >= 0){\
        strncat(dad->check_result,"P-",strlen("P-"));\
    }else{\
        strncat(dad->check_result,"F-",strlen("F-"));\
    }\
}while(0)

static void cyttsp5_sensor_check(struct device *dev,int *buf[CYTTSP_CHECK_MAX],int *check_count)
{
    int test_flag = 0;
    int index = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);

    cyttsp5_hw_reset(cd);
    msleep(200);

    //I2C Ping check
    dad->check_index = CYTTSP_I2C_PING;
    test_flag = cyttsp5_check_items(dev,CYTTSP_I2C_PING, 1,NULL);
    CHECK_RESULT_SET(dev,test_flag,"0");
    if(test_flag < 0){
        TS_LOG_INFO("%s: i2c check fail.\n",__func__);
        return;
    }

    //Global iDAC check
    dad->check_index = CYTTSP_GLOBAL_IDAC;
    test_flag = cyttsp5_check_items(dev,CYTTSP_GLOBAL_IDAC, 1,buf[CYTTSP_GLOBAL_IDAC]);
    CHECK_RESULT_SET(dev,test_flag,"1");

    //short check
    dad->check_index = CYTTSP_SHORT_INFO;
    test_flag = cyttsp5_check_items(dev,CYTTSP_SHORT_INFO, 0,buf[CYTTSP_SHORT_INFO]);
    CHECK_RESULT_SET(dev,test_flag,"2");

    //Mutual cap check
    dad->check_index = CYTTSP_MUTUAL_RAWDATA;
    test_flag = cyttsp5_check_items(dev,CYTTSP_MUTUAL_RAWDATA, 1,buf[CYTTSP_MUTUAL_RAWDATA]);
    CHECK_RESULT_SET(dev,test_flag,"3");

     //LocalPWC check
    dad->check_index = CYTTSP_MUTUAL_LOCALPWC;
    test_flag = cyttsp5_check_items(dev,CYTTSP_MUTUAL_LOCALPWC, 1,buf[CYTTSP_MUTUAL_LOCALPWC]);
    CHECK_RESULT_SET(dev,test_flag,"4");

    //Opens check
    dad->check_index = CYTTSP_OPENS_DATA;
    test_flag = cyttsp5_check_items(dev,CYTTSP_OPENS_DATA, 0,buf[CYTTSP_OPENS_DATA]);
    CHECK_RESULT_SET(dev,test_flag,"5");

    //Self LocalPWC check
    dad->check_index = CYTTSP_SELF_LOCALPWC;
    test_flag = cyttsp5_check_items(dev,CYTTSP_SELF_LOCALPWC, 1,buf[CYTTSP_SELF_LOCALPWC]);
    CHECK_RESULT_SET(dev,test_flag,"6");

    //Self cap check
    dad->check_index = CYTTSP_SELF_RAWDATA;
    test_flag = cyttsp5_check_items(dev,CYTTSP_SELF_RAWDATA,1,buf[CYTTSP_SELF_RAWDATA]);
    CHECK_RESULT_SET(dev,test_flag,"7");

    cyttsp5_hw_reset(cd);
    msleep(200);

    *check_count = index;

    dad->check_index = CYTTSP_CHECK_MAX;

}

static void cyttsp5_sensor_data_print(struct device *dev,int *data_buf[CYTTSP_CHECK_MAX],
                    struct seq_file *m)
{
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    //I2C Ping check
    dad->check_index = CYTTSP_I2C_PING;
    cyttsp5_proc_data_print(dev,NULL,m);

    //Global iDAC check
    dad->check_index = CYTTSP_GLOBAL_IDAC;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_GLOBAL_IDAC],m);

    //short check
    dad->check_index = CYTTSP_SHORT_INFO;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_SHORT_INFO],m);

    //Mutual cap check
    dad->check_index = CYTTSP_MUTUAL_RAWDATA;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_MUTUAL_RAWDATA],m);

    //LocalPWC check
    dad->check_index = CYTTSP_MUTUAL_LOCALPWC;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_MUTUAL_LOCALPWC],m);

    //Opens check
    dad->check_index = CYTTSP_OPENS_DATA;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_OPENS_DATA],m);

    //Self LocalPWC check
    dad->check_index = CYTTSP_SELF_LOCALPWC;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_SELF_LOCALPWC],m);

    //Self cap check
    dad->check_index = CYTTSP_SELF_RAWDATA;
    cyttsp5_proc_data_print(dev,data_buf[CYTTSP_SELF_RAWDATA],m);

}


static int cyttsp5_rawdata_proc_show(struct seq_file *m, void *v)
{
    int index;
    int error = 0;
    struct device *dev = gdev;
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = cd->sysinfo.sensing_conf_data.electrodes_y;
    int rx_num = cd->sysinfo.sensing_conf_data.electrodes_x;
    int *tmp_buf[CYTTSP_CHECK_MAX];
    int check_count = 0;

    if(atomic_read(&mmi_test_status)){
        return -1;
    }

    atomic_set(&mmi_test_status, 1);

    TS_LOG_INFO("rawdata_proc_show, buffer size = %ld\n", m->size);
    if(m->size <= RAW_DATA_SIZE) {
        m->count = m->size;
        goto out;
    }

    error = cyttsp5_get_sensor_info(dev);
    if(error < 0){
        TS_LOG_ERR("%s Failed to get sensor info.\n",__func__);
        return -EINVAL;
    }

    for(index = 0; index < CYTTSP_CHECK_MAX;index++){
        tmp_buf[index] = kzalloc(sizeof(int) * CY_MAX_RAW_DATA_LEN, GFP_KERNEL);
        if(tmp_buf[index] == NULL){
        for (index--; index >= 0 ; index--)
            kfree(tmp_buf[index]);
            TS_LOG_ERR( "%s: failed to create sysfs interface\n", __func__);
            return -ENODEV;
        }
    }

    memset(dad->check_result,0,sizeof(dad->check_result));

    cyttsp5_sensor_check(dev,tmp_buf,&check_count);

    seq_printf(m, "result:%s\n",dad->check_result);
    seq_printf(m, "Sensor Info: tx: %d, rx : %d\n",tx_num, rx_num);

    cyttsp5_sensor_data_print(dev,tmp_buf,m);

    dad->check_index = CYTTSP_CHECK_MAX;
    error = 0;

    for(index = 0; index < CYTTSP_CHECK_MAX;index++){
        kfree(tmp_buf[index]);
    }

out:
    atomic_set(&mmi_test_status, 0);
    TS_LOG_INFO("rawdata_proc_show done.\n");
    return error;
}


static void cyttsp5_sensor_check_all(struct device *dev,int *buf[CYTTSP_CHECK_MAX],int *check_count)
{
    int test_flag = 0;
    int index = 0;
    char str[8] = {0};
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    for(index = 0;index < CYTTSP_CHECK_MAX;index++){
        dad->check_index = index;
        test_flag = cyttsp5_check_items(dev,dad->check_index,0,buf[index]);
        snprintf(str,sizeof(str),"%d",dad->check_index);
        CHECK_RESULT_SET(dev,test_flag,str);
    }

    *check_count = index;
    dad->check_index = CYTTSP_CHECK_MAX;
}

static void cyttsp5_sensor_data_print_all(struct device *dev,int *data_buf[CYTTSP_CHECK_MAX],
                    struct seq_file *m)

{
    int index = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);

    for(index = 0;index < CYTTSP_CHECK_MAX;index++){
        dad->check_index = index;
        cyttsp5_proc_data_print(dev,data_buf[index],m);
    }

    dad->check_index = CYTTSP_CHECK_MAX;
}



static int cyttsp5_sensor_data_proc_show(struct seq_file *m, void *v)
{
    int index;
    struct device *dev = gdev;
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    int tx_num = cd->sysinfo.sensing_conf_data.electrodes_y;
    int rx_num = cd->sysinfo.sensing_conf_data.electrodes_x;
    int error = 0;
    int check_count = 0;
    int *tmp_buf[CYTTSP_CHECK_MAX];

    if(atomic_read(&mmi_test_status)){
        return -1;
    }

    atomic_set(&mmi_test_status, 1);

    TS_LOG_INFO("rawdata_proc_show, buffer size = %ld\n", m->size);
    if(m->size <= RAW_DATA_SIZE) {
        m->count = m->size;
        goto out;
    }

    error = cyttsp5_get_sensor_info(dev);
    if(error < 0){
        TS_LOG_ERR("%s Failed to get sensor info.\n",__func__);
        return -EINVAL;
    }

    for(index = 0; index < CYTTSP_CHECK_MAX;index++){
        tmp_buf[index] = kzalloc(sizeof(int) * CY_MAX_RAW_DATA_LEN, GFP_KERNEL);
        if(tmp_buf[index] == NULL){
        for (index--; index >= 0 ; index--)
            kfree(tmp_buf[index]);
            TS_LOG_ERR( "%s: failed to create sysfs interface\n", __func__);
            return -ENODEV;
        }
    }

    memset(dad->check_result,0,sizeof(dad->check_result));

    cyttsp5_sensor_check_all(dev,tmp_buf,&check_count);

    seq_printf(m, "Test reselt:%s\n",dad->check_result);
    seq_printf(m, "Sensor Info: tx: %d, rx : %d\n",tx_num, rx_num);

    cyttsp5_sensor_data_print_all(dev,tmp_buf,m);

    dad->check_index = CYTTSP_CHECK_MAX;
    error = 0;

out:
    atomic_set(&mmi_test_status, 0);
    TS_LOG_INFO("rawdata_proc_show done.\n");
    return error;
}


static int cyttsp5_data_proc_show(struct seq_file *m, void *v)
{
    int error = 0;
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(gdev);
    struct device *dev = gdev;

    if(atomic_read(&mmi_test_status)){
        return -1;
    }

    atomic_set(&mmi_test_status, 1);

    TS_LOG_INFO("cyttsp5_data_proc_show, buffer size = %ld\n", m->size);
    if(m->size <= RAW_DATA_SIZE/4) {
        m->count = m->size;
        goto out;
    }

    error = cyttsp5_get_sensor_info(dev);
    if(error < 0){
        TS_LOG_ERR("%s Failed to get sensor info.\n",__func__);
        return -EINVAL;
    }

    error = cyttsp5_proc_data_print(dev,dad->data_buf,m);

out:
    atomic_set(&mmi_test_status, 0);
    TS_LOG_INFO("cyttsp5_data_proc_show done.\n");
    return error;
}


static int cyttsp5_rawdata_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, cyttsp5_rawdata_proc_show, NULL);
}

static const struct file_operations cyttsp5_rawdata_proc_fops = {
    .open        = cyttsp5_rawdata_proc_open,
    .read        = seq_read,
    .llseek        = seq_lseek,
    .release    = single_release,
};


static int cyttsp5_sensor_data_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, cyttsp5_sensor_data_proc_show, NULL);
}

static const struct file_operations cyttsp5_sensor_data_proc_fops = {
    .open        = cyttsp5_sensor_data_proc_open,
    .read        = seq_read,
    .llseek        = seq_lseek,
    .release    = single_release,
};

static int cyttsp5_data_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, cyttsp5_data_proc_show, NULL);
}

static const struct file_operations cyttsp5_data_proc_fops = {
    .open        = cyttsp5_data_proc_open,
    .read        = seq_read,
    .llseek        = seq_lseek,
    .release    = single_release,
};


void cyttsp5_procfs_create(void)
{
    if (!proc_mkdir("touchscreen", NULL)){
        TS_LOG_ERR("%s: Error, failed to creat procfs.\n",__func__);
        return;
    }
    proc_create("touchscreen/rawdata", 0444, NULL, &cyttsp5_rawdata_proc_fops);
    proc_create("touchscreen/dumpdata", 0444, NULL, &cyttsp5_sensor_data_proc_fops);
    proc_create("touchscreen/data", 0444, NULL, &cyttsp5_data_proc_fops);
    return;
}
